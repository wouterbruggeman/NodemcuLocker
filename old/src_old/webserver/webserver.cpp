#include "webserver.h"

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "../rfid/rfid.h"
#include "../memory/memory.h"
#include "../main.h"

#ifdef ESP8266
	extern "C" {
	#include "user_interface.h"
}
#endif

const String header =
"<html><head><title>Locker</title><style>body{margin:0;padding:0;}"
"button{background-color:#4CAF50;width:50%;border:none;padding:16;text-align:center;"
"text-decoration:none;display:inline-block;font-size:16;color:white;margin:0 0 5 5;}"
".blue_btn{background-color:#008CBA}.red_btn{background-color:#f44336}"
".tag{background-color:#8c8c8c;color:#ffffff;width:100%;font-weight:bold;padding:16 0 16 16;"
"box-sizing:border-box;font-size:16;margin:0 0 5 0;}#info{padding:2% 0 0 5%;"
"background-color:black;color:#bcbcbc;padding-bottom:10%;}.g{color:#0afc2e;}"
"</style></head><meta name='viewport' content='width=device-width, initial-scale=1.0'><body>"
"<a href='/'><button class='blue_btn' style='width:100%;margin:0;'>Main menu</button></a>";
const String footer = "</body></html>";
const String requestLastID = "<script>function req(){var x=new XMLHttpRequest();"
"x.onreadystatechange=function(){if(this.readyState==4 && this.status==200){"
"document.getElementById('lasttag').innerHTML=this.responseText;}};"
"x.open('GET','lasttag',true);x.send();setTimeout(req, 2000);}req();</script>";

ESP8266WebServer webserver(80);

String charToHex(char c){
	String hex;
	for(int i = 1; i >= 0; i--){
		char nibble = c >> (i<<2);
		nibble = nibble & 0x0F;

		if(nibble > 9){
			nibble += HEX_UPPERCASE - 10;
			hex += nibble;
		}else{
			nibble += 48;
			hex += nibble;
		}
	}
	return hex;
}

String showMainMenu(){
	String page;;
	page += "<div class='tag'><p id='lasttag'></p></div>";
	page += "<div class='tag'>Main functions</div>";
	page += "<a href='?action=1'><button class='blue_btn'>Open Lock</button></a><br>";
	page += "<div class='tag'>RFID functions</div>";
	page += "<a href='?action=2'><button>Add RFID</button></a><br>";
	page += "<a href='?action=3'><button class='red_btn'>Remove RFID</button></a><br>";
	page += "<div class='tag'>EEPROM functions</div>";
	page += "<a href='/eepromdump'><button>Dump EEPROM</button></a><br>";
	page += "<a href='?action=4'><button>Defrag EEPROM</button></a><br>";
	page += "<a href='?action=5'><button class='red_btn'>Format EEPROM</button></a><br>";
	page += "<div class='tag'>Other</div>";
	page += "<a href='/sysinfo'><button>View system info</button></a><br>";
	page += requestLastID;
	return page;
}

void handleRootPage(){
	String webpage = header;

	if((webserver.args() != 0) && (webserver.argName(0) == "action")){
		int arg = webserver.arg(0).toInt();
		#ifdef DEBUG_MODE
			Serial.print("Action: ");
			Serial.println(arg, DEC);
		#endif
		if(arg != 0){
			switch(arg){
				case 1:
					openLock();
					break;
				case 2:
					addRFID();
					break;
				case 3:
					removeRFID();
					break;
				case 4:
					defragMemory();
					break;
				case 5:
					formatMemory();
					break;
				default:
					break;
			}
		}
	}

	webpage += showMainMenu();
	webpage += footer;
	webserver.send(200, DATA_TYPE, webpage);

	//Enable the wifi for some time
	enableWifi();
}

void handleEEPROMDumpPage(){
	String webpage = header;
	webpage += "<div id='info'>";

	for(int i = 0; i < EEPROM_SIZE; i++){
		char byte = EEPROM.read(i);
		bool positive = ((byte == MEM_UID) && ((i % 5) == 0));

		if(positive){
			webpage += EEPROM_POSITIVE_PREFIX;
		}

		webpage += charToHex(byte);
		webpage += " ";
		if(((i+1) % 5) == 0){
			webpage += "<br>";
		}

		if(positive){
			webpage += EEPROM_POSITIVE_SUFFIX;
		}
	}
	webpage +="</div>";

	//show the response to the user
	webpage += footer;
	webserver.send(200, DATA_TYPE, webpage);
}

void handleSystemInformationPage(){
	String webpage = header;
	webpage += "<div id='info'>";

	webpage += "<b>CPU frequency:</b><br>";
	webpage += system_get_cpu_freq();
	webpage += "MHz<hr><b>Free heap size:</b><br>";
	webpage += system_get_free_heap_size();
	webpage += " bytes<br><hr><b>Program size:</b><br>";
	webpage += ESP.getSketchSize();
	webpage += " bytes<br><hr><b>Free program size:</b><br>";
	webpage += ESP.getFreeSketchSpace();
	webpage += " bytes<br><hr><b>Milliseconds alive:</b><br>";
	webpage += millis();
	webpage += "<br><hr><b>Days alive:</b><br>";
	webpage += millis() / 1000 / 60 / 60 / 24;
	webpage += "<br><hr><b>RFID reader status:</b><br>";
	if(readerIsConnected()){
		webpage += "Connected.";
	}else{
		webpage += "Disconnected.";
	}
	webpage += "<br><hr><b>Compile time:</b><br>";
	webpage += __TIME__;
	webpage += "<br>";
	webpage += __DATE__;
	webpage += "<br><hr><b>Debug mode:</b><br>";
	#ifdef DEBUG_MODE
		webpage += "Enabled.";
	#else
		webpage += "Disabled.";
	#endif


	webpage += "</div>";
	webpage += footer;
	webserver.send(200, DATA_TYPE, webpage);
}

void handleLastTagRequest(){
	char tag[4];
	bool tagIsKnown = getLastTag(tag);

	//header and footer are not required for ajax requests.
	String webpage = "Last tag: ";
	if(tagIsKnown){
		webpage += EEPROM_POSITIVE_PREFIX;
	}

	for(int i = 0; i < 4; i++){
		webpage += charToHex(tag[i]);
		webpage += " ";
	}

	if(tagIsKnown){
		webpage += EEPROM_POSITIVE_SUFFIX;
	}
	webserver.send(200, DATA_TYPE, webpage);
}

void handleNotFoundPage(){
	String webpage = header + "<h1>404!</h1>" + footer;
	webserver.send(404, DATA_TYPE, webpage);
}

//other functions
void setupWebserver(){
	//list all pages below
	webserver.on("/", handleRootPage);
	webserver.on("/eepromdump", handleEEPROMDumpPage);
	webserver.on("/sysinfo", handleSystemInformationPage);
	webserver.on("/lasttag", handleLastTagRequest);
	webserver.onNotFound(handleNotFoundPage);

	//start the webserver
	webserver.begin();

	#ifdef DEBUG_MODE
		Serial.println("HTTP server started");
	#endif
}

void handleWebserver(){
	webserver.handleClient();
}
