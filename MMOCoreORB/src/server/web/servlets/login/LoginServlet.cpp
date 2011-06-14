/*
 * LoginServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#include "LoginServlet.h"

LoginServlet::LoginServlet(String context) : Servlet(context) {
	// TODO Auto-generated constructor stub

}

LoginServlet::~LoginServlet() {
	// TODO Auto-generated destructor stub
}

void LoginServlet::processRequest(HttpRequest* request, HttpResponse* response) {
	response->print("Login found");
}
