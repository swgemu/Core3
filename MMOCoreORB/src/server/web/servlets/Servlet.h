/*
 * Servlet.h
 *
 *  Created on: May 31, 2011
 *      Author: kyle
 */

#ifndef SERVLET_H_
#define SERVLET_H_

#include "engine/engine.h"
#include "../HttpRequest.h"
#include "../HttpResponse.h"

class Servlet : Logger {
public:
	Servlet(String context);
	virtual ~Servlet();

	virtual void processRequest(HttpRequest* request, HttpResponse* response) = 0;

	void handleRequest(struct mg_connection *conn, HttpRequest* request, HttpResponse* response);
private:
	void outputResponse(struct mg_connection *conn, HttpResponse* response);

};

#endif /* SERVLET_H_ */
