/*
 * PermissionsServlet.h
 *
 *  Created on: May 11, 2012
 *      Author: Itac
 */

#ifndef PERMISSIONSSERVLET_H_
#define PERMISSIONSSERVLET_H_

#include "../Servlet.h"
#include "server/web/servlets/permissions/../../servlets/Servlet.h"
#include "system/lang/String.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

class PermissionsServlet: public Servlet {
public:
	PermissionsServlet(String context);
	virtual ~PermissionsServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* PERMISSIONSSERVLET_H_ */
