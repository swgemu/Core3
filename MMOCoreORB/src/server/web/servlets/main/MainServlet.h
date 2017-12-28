/*
 * MainServlet.h
 *
 *  Created on: July 8, 2011
 *      Author: kyle
 */

#ifndef MAINSERVLET_H_
#define MAINSERVLET_H_

#include "../Servlet.h"
#include "server/web/servlets/main/../../servlets/Servlet.h"
#include "system/lang/String.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

class MainServlet: public Servlet {
public:
	MainServlet(String context);
	virtual ~MainServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* MAINSERVLET_H_ */
