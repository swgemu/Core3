/*
 * HttpSession.cpp
 *
 *  Created on: Jun 2, 2011
 *      Author: kyle
 */

#include "HttpSession.h"
#include "../WebServer.h"

HttpSession::HttpSession(const struct mg_request_info *request_info) {
	// TODO Auto-generated constructor stub
	authenticated = false;

	update(request_info);
}

HttpSession::~HttpSession() {
	// TODO Auto-generated destructor stub
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

	updateTimestamp();
}

void HttpSession::updateTimestamp() {
	timestamp = time(0);
}
