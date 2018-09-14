#include "httpserver.h"
#include "FS.h"

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

	//If the requested page does not exist, show the 404 page
	if(!SPIFFS.exists(filename)){
		filename = String("/404.html");
		statusCode = 404;
	}

	//Load the page
	File f = SPIFFS.open(filename, "r");
	char buffer[f.size() - sizeof(filename)];
	f.readBytes(buffer, f.size());
	f.close();

	//Send the webpage to the user
	_webserver->send(statusCode, HTML_DATA_TYPE, buffer);
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
	}


}

void HTTPServer::handlePageNotFound(){
	this->showPage("404.html", 404);
}
