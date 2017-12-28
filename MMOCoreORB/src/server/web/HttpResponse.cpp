/*
 * HttpResponse.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#include "HttpResponse.h"

#include <stddef.h>

#include "WebServer.h"
#include "server/web/servlets/../HttpResponse.h"
#include "server/web/session/HttpSession.h"
#include "system/lang/String.h"
#include "system/lang/StringBuffer.h"

HttpResponse::HttpResponse(HttpSession* session) {
	// TODO Auto-generated constructor stub
	docType = "html";
	this->session = session;

	conn = NULL;
}

HttpResponse::~HttpResponse() {
	// TODO Auto-generated destructor stub
}

void HttpResponse::update(struct mg_connection *conn) {
	this->conn = conn;
	out.deleteAll();
}

void HttpResponse::forwardTo(String context) {
	WebServer::instance()->forward(conn, context, session->getRequest());
}

void HttpResponse::print(String item) {
	out << item;
}

void HttpResponse::println(String line) {
	out << line << "\r\n";
}

String HttpResponse::generatePage() {
	return out.toString();
}
