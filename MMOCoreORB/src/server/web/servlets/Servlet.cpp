/*
 * WebComponent.cpp
 *
 *  Created on: May 31, 2011
 *      Author: kyle
 */

#include "../WebServer.h"
#include "Servlet.h"
#include "../mongoose/mongoose.h"

Servlet::Servlet(String context) {

	setLogging(true);
	setLoggingName("Webserver:" + context);

	if(!WebServer::instance()->addContext(context, this)) {
		error("Context already exists");
	}
}

Servlet::~Servlet() {
	// TODO Auto-generated destructor stub
}

void Servlet::handleRequest(struct mg_connection *conn, HttpRequest* request, HttpResponse* response) {

	processRequest(request, response);

	outputResponse(conn, response);

}

void Servlet::outputResponse(struct mg_connection *conn, HttpResponse* response) {
	mg_printf(conn, response->generatePage().toCharArray());
}
