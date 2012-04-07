/*
 * CharacterServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef CHARACTERSERVLET_H_
#define CHARACTERSERVLET_H_

#include "../Servlet.h"

class CharacterServlet: public Servlet {
public:
	CharacterServlet(String context);
	virtual ~CharacterServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* CHARACTERSERVLET_H_ */
