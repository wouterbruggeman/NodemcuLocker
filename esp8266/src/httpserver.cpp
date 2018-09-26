#include "httpserver.h"
#include "FS.h"
#include "filenames.h"

HTTPServer::HTTPServer(const char *ssid, const char *password,
		CardDatabase *acceptedCards, Nano *nano){
	_ssid = ssid;
	_password = password;
	_acceptedCards = acceptedCards;
	_nano = nano;
	_webserver = new ESP8266WebServer();
}

void HTTPServer::init(){
	WiFi.softAP(_ssid, _password);
	this->initPages();
	enableWifi();
}

void HTTPServer::enableWifi(){
	WiFi.enableAP(true);
}

void HTTPServer::disableWifi(){
	WiFi.enableAP(false);
}

void HTTPServer::loop(){
	_webserver->handleClient();
}

void HTTPServer::initPages(){
	_webserver->on("/", HTTP_GET, std::bind(&HTTPServer::pageRequest, this));
	_webserver->onNotFound(std::bind(&HTTPServer::notFoundRequest, this));
	_webserver->begin();
}

void HTTPServer::showPage(String filename, int statusCode = 200){
	//Add prefix
	filename = String("/" + filename + ".html");

	Serial.print("Filename: ");
	Serial.println(filename);

	//If the requested page does not exist, show the 404 page
	if(!SPIFFS.exists(filename)){
		filename = String("/404.html");
		statusCode = 404;
	}



	/*
	//Generate the page:
	int totalPageSize = 0;
	int pageSize, headerSize, footerSize;

	//Limit ram usage by creating just one small array
	int biggestArraySize = 0;

	File fileHeader = SPIFFS.open(FILE_HTML_HEADER, "r");
	headerSize = fileHeader.size();
	totalPageSize += headerSize;
	biggestArraySize = headerSize;

	File filePage = SPIFFS.open(filename, "r");
	pageSize = filePage.size();
	totalPageSize += pageSize;
	if(biggestArraySize < pageSize){
		biggestArraySize = pageSize;
	}

	File fileFooter = SPIFFS.open(FILE_HTML_FOOTER, "r");
	footerSize = fileFooter.size();
	totalPageSize += footerSize;
	if(biggestArraySize < footerSize){
		biggestArraySize = footerSize;
	}
	//Create buffer for all the content.
	char contentBuffer[totalPageSize];
	//Create one array for everything to limit ram usage
	char buffer[biggestArraySize];


	//Assemble the pages
	fileHeader.readBytes(buffer, headerSize);
	for(unsigned int i = 0; i < headerSize; i++){
		contentBuffer[i] = buffer[i];
	}
	fileHeader.close();

	//Read the next file into the buffer
	filePage.readBytes(buffer, pageSize);
	for(unsigned int i = 0; i < pageSize; i++){
		contentBuffer[headerSize + i] = buffer[i];
	}
	filePage.close();

	//Read next
	fileFooter.readBytes(buffer, footerSize);
	for(unsigned int i = 0; i < footerSize; i++){
		contentBuffer[headerSize + pageSize + i] = buffer[i];
	}
	fileFooter.close();


	Serial.println("TotalBuffer: ");
	for(unsigned int i= 0; i < totalPageSize; i++){
		Serial.print(contentBuffer[i]);
	}*/




	//Send the webpage to the user
	_webserver->send(statusCode, HTML_DATA_TYPE, contentBuffer);
}

void HTTPServer::pageRequest(HTTPServer *server){
	//Redirect the request to a member function
	server->handlePageRequest();
}

void HTTPServer::notFoundRequest(HTTPServer *server){
	server->handlePageNotFound();
}

void HTTPServer::handlePageRequest(){

	//If there are no arguments
	if(_webserver->args() == 0){
		//Show the index page
		this->showPage("index");
		return;
	}

	//Check if a pagename was given
	if(_webserver->argName(0) == "page"){
		//Show the page
		this->showPage(String(_webserver->arg(0)));
		return;
	}

	//If there was no pagename given, the request isn't a usual request
	if(_webserver->argName(0) == "action"){
		//Show the required data
		this->handleActionRequest(String(_webserver->arg(0)).toInt());
	}
}

void HTTPServer::handleActionRequest(int action){
	char *contentBuffer = NULL;
	switch(action){
		case 0:
			break;
		default:
			break;
	}

	_webserver->send(200, HTML_DATA_TYPE, contentBuffer);
	delete contentBuffer;
}

void HTTPServer::handlePageNotFound(){
	this->showPage("404.html", 404);
}
