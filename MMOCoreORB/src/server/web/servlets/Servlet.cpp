/*
 * WebComponent.cpp
 *
 *  Created on: May 31, 2011
 *      Author: kyle
 */

#include "Servlet.h"
#include "../mongoose/mongoose.h"
#include "../WebServer.h"

Servlet::Servlet(String contxt) {

	context = contxt;

	setLogging(true);
	setLoggingName("Webserver:" + context);
}

Servlet::~Servlet() {
	// TODO Auto-generated destructor stub
}

void Servlet::handleRequest(struct mg_connection *conn, HttpRequest* request, HttpResponse* response) {

	if(request->getRequestMethod() == "GET") {

		handleGet(request, response);

	} else if (request->getRequestMethod() == "POST") {

		handlePost(request, response);

	} else {

		error("Error: Webserver doesn't handle request type:" + request->getRequestMethod());
	}

	outputResponse(conn, response);
}

void Servlet::outputResponse(struct mg_connection *conn, HttpResponse* response) {
	mg_printf(conn, response->generatePage().toCharArray());
}
