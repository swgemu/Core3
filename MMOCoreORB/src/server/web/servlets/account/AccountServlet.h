/*
 * AccountServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef ACCOUNTSERVLET_H_
#define ACCOUNTSERVLET_H_

#include "../Servlet.h"

class AccountServlet: public Servlet {
public:
	AccountServlet(String context);
	virtual ~AccountServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* ACCOUNTSERVLET_H_ */
