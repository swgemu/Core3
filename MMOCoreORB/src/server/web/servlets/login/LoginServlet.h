/*
 * LoginServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef LOGINSERVLET_H_
#define LOGINSERVLET_H_

#include "../Servlet.h"
#include "server/web/servlets/login/../../servlets/Servlet.h"
#include "system/lang/String.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

class LoginServlet: public Servlet {
public:
	LoginServlet(String context);
	virtual ~LoginServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* LOGINSERVLET_H_ */
