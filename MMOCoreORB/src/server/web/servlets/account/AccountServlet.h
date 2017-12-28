/*
 * AccountServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef ACCOUNTSERVLET_H_
#define ACCOUNTSERVLET_H_

#include "../Servlet.h"
#include "server/web/servlets/account/../../servlets/Servlet.h"
#include "system/lang/String.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

class AccountServlet: public Servlet {
public:
	AccountServlet(String context);
	virtual ~AccountServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* ACCOUNTSERVLET_H_ */
