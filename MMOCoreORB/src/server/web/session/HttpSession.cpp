/*
 * HttpSession.cpp
 *
 *  Created on: Jun 2, 2011
 *      Author: kyle
 */

#include "HttpSession.h"
#include "../WebServer.h"

HttpSession::HttpSession() {
	// TODO Auto-generated constructor stub
	authenticated = false;

	request = new HttpRequest();
	response = new HttpResponse();
}

HttpSession::~HttpSession() {
	// TODO Auto-generated destructor stub

	delete request;
	delete response;
}

bool HttpSession::hasExpired() {
	if(time(0) - timestamp > WebServer::sessionTimeout * 60) {
		authenticated = false;
		return true;
	}
	return false;
}

bool HttpSession::isValid() {
	return authenticated;
}

void HttpSession::update(const struct mg_request_info *request_info) {

	request->update(request_info);
	response->update();

	updateTimestamp();
}

void HttpSession::updateTimestamp() {
	timestamp = time(0);
}
