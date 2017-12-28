/*
 * LogsServlet.h
 *
 *  Created on: Mar 18, 2012
 *      Author: kyle
 */

#ifndef LOGSSERVLET_H_
#define LOGSSERVLET_H_

#include "../Servlet.h"
#include "server/web/servlets/logs/../../servlets/Servlet.h"
#include "system/lang/String.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

class LogsServlet: public Servlet {
public:
	LogsServlet(String context);
	virtual ~LogsServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* LOGSSERVLET_H_ */
