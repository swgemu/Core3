/*
 * AccountServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#include "AccountServlet.h"

namespace server {
namespace web {
class HttpRequest;
class HttpResponse;
}  // namespace web
}  // namespace server

AccountServlet::AccountServlet(String context) :
	Servlet(context) {
	// TODO Auto-generated constructor stub

}

AccountServlet::~AccountServlet() {
	// TODO Auto-generated destructor stub
}

void AccountServlet::handleGet(HttpRequest* request, HttpResponse* response) {


}

void AccountServlet::handlePost(HttpRequest* request, HttpResponse* response) {

}
