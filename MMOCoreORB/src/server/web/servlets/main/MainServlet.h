/*
 * MainServlet.h
 *
 *  Created on: July 8, 2011
 *      Author: kyle
 */

#ifndef MAINSERVLET_H_
#define MAINSERVLET_H_

#include "server/web/servlets/Servlet.h"

class MainServlet: public Servlet {
public:
	MainServlet(String context);
	virtual ~MainServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* MAINSERVLET_H_ */
