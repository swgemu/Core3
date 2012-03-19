/*
 * LogsServlet.h
 *
 *  Created on: Mar 18, 2012
 *      Author: kyle
 */

#ifndef LOGSSERVLET_H_
#define LOGSSERVLET_H_

#include "../Servlet.h"

class LogsServlet: public Servlet {
public:
	LogsServlet(String context);
	virtual ~LogsServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* LOGSSERVLET_H_ */
