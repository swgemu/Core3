/*
 * HttpSession.cpp
 *
 *  Created on: Jun 2, 2011
 *      Author: kyle
 */

#include "HttpSession.h"
#include "../WebServer.h"
///#include "../HttpRequest.h"
//#include "../HttpResponse.h"

HttpSession::HttpSession() {
	// TODO Auto-generated constructor stub
	authenticated = false;

	request = new HttpRequest(this);
	response = new HttpResponse(this);

	sessionId = generateRandomKey(48);
	canSetId = true;

	timestamp = 0;

	ip = 0;

	canSetId = false;

	setLoggingName("HttpSession_" + sessionId);
	setLogging(true);
	setInfoLogLevel();

	debug("Session Created");
}

HttpSession::~HttpSession() {
	// TODO Auto-generated destructor stub

	debug("Session Destroyed");

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

void HttpSession::update(struct mg_connection *conn, const struct mg_request_info *request_info) {

	request->update(request_info);
	response->update(conn);

	updateTimestamp();
}

void HttpSession::updateTimestamp() {
	timestamp = time(0);
}

String HttpSession::generateRandomKey(int length) {
	StringBuffer value;

	for(int i = 0; i < length; ++i) {
		char character = System::random(122 - 48) + 48;
		while (character < 48 || (character > 57 && character < 65) ||
				character > 122 || (character > 89 && character < 97)) {
			character = System::random(122 - 48) + 48;
		}

		value << character;
	}

	return value.toString();
}
