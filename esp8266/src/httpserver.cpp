#include "httpserver.h"

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
	//TODO: https://stackoverflow.com/questions/39803135/c-unresolved-overloaded-function-type
	_webserver->begin();
}

void HTTPServer::pageRequest(HTTPServer *server){
	//Redirect the request to a member function
	server->handlePageRequest();
}

void HTTPServer::handlePageRequest(){
	/*int pageID = 0;
	if((_webserver.args() != 0) && (_webserver.argName[0] != "page")){
		pageID = _webserver.arg(0).toInt();
	}*/

	//Load the page with pageID
	//Look up filename in enum

	_webserver->send(200, "text/html", "Hello world!");
}
