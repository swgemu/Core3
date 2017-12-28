/*
 * CharacterServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#include "CharacterServlet.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

CharacterServlet::CharacterServlet(String context) :
	Servlet(context) {
	// TODO Auto-generated constructor stub

}

CharacterServlet::~CharacterServlet() {
	// TODO Auto-generated destructor stub
}

void CharacterServlet::handleGet(HttpRequest* request, HttpResponse* response) {

}

void CharacterServlet::handlePost(HttpRequest* request, HttpResponse* response) {


}
