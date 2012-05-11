/*
 * PermissionsServlet.h
 *
 *  Created on: May 11, 2012
 *      Author: Itac
 */

#ifndef PERMISSIONSSERVLET_H_
#define PERMISSIONSSERVLET_H_

#include "../Servlet.h"

class PermissionsServlet: public Servlet {
public:
	PermissionsServlet(String context);
	virtual ~PermissionsServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* PERMISSIONSSERVLET_H_ */
