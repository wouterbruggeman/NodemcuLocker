#include "httpserver.h"

HTTPServer::HTTPServer(){
	_webserver = new ESP8266WebServer();
	this->initPages();
	_webserver->begin();
}

void HTTPServer::wifiInit(char *ssid, char *password){
	WiFi.softAP(ssid, password);
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
	/*_webserver->on("/", handlePageRequest);
	_webserver->onNotFound(handlePageNotFound);*/
}

void HTTPServer::showWebpage(int page){

}

void HTTPServer::handlePageRequest(){
	/*int pageID = 0;
	if((_webserver.args() != 0) && (_webserver.argName[0] != "page")){
		pageID = _webserver.arg(0).toInt();
	}*/

	//Load the page with pageID
	//Look up filename in enum
}

void HTTPServer::handlePageNotFound(){
	String webpage = "<h1>404</h1>";
	_webserver->send(404, "text/html", webpage);
}


