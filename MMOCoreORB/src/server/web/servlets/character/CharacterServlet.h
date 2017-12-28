/*
 * CharacterServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef CHARACTERSERVLET_H_
#define CHARACTERSERVLET_H_

#include "../Servlet.h"
#include "server/web/servlets/character/../../servlets/Servlet.h"
#include "system/lang/String.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

class CharacterServlet: public Servlet {
public:
	CharacterServlet(String context);
	virtual ~CharacterServlet();

	void handleGet(HttpRequest* request, HttpResponse* response);
	void handlePost(HttpRequest* request, HttpResponse* response);
};

#endif /* CHARACTERSERVLET_H_ */
