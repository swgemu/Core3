/*
 * WebComponent.cpp
 *
 *  Created on: May 31, 2011
 *      Author: kyle
 */

#include "Servlet.h"

#include "../mongoose/mongoose.h"
#include "server/web/servlets/../HttpRequest.h"
#include "server/web/servlets/../HttpResponse.h"
#include "server/web/servlets/../servlets/Servlet.h"
#include "server/zone/ZoneServer.h"
#include "system/lang/Exception.h"
#include "system/lang/String.h"

Servlet::Servlet(String contxt) {

	context = contxt;

	setLogging(true);
	setLoggingName("Webserver:" + context);
}

Servlet::~Servlet() {
	// TODO Auto-generated destructor stub
}

void Servlet::handleRequest(struct mg_connection *conn, HttpRequest* request, HttpResponse* response) {

	try {

		if(request->getRequestMethod() == "GET") {

			handleGet(request, response);

		} else if (request->getRequestMethod() == "POST") {

			handlePost(request, response);

		} else {

			response->println("Webserver doesn't handle request type:" + request->getRequestMethod());
			error("Webserver doesn't handle request type:" + request->getRequestMethod());
		}
	} catch(Exception& e) {
		error("Unhandled Exception:" + e.getMessage());
	}

	outputResponse(conn, response);
}

void Servlet::outputResponse(struct mg_connection *conn, HttpResponse* response) {
	mg_printf(conn, response->generatePage().toCharArray());
}
