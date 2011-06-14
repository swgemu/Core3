/*
 * LoginServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef LOGINSERVLET_H_
#define LOGINSERVLET_H_

#include "../Servlet.h"

class LoginServlet: public Servlet {
public:
	LoginServlet(String context);
	virtual ~LoginServlet();

	void processRequest(HttpRequest* request, HttpResponse* response);
};

#endif /* LOGINSERVLET_H_ */
