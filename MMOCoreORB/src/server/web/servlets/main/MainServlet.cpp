/*
 * MainServlet.cpp
 *
 *  Created on: July 8, 2011
 *      Author: kyle
 */

#include "MainServlet.h"
#include "../../WebServer.h"

MainServlet::MainServlet(String context) :
	Servlet(context) {
	// TODO Auto-generated constructor stub

}

MainServlet::~MainServlet() {
	// TODO Auto-generated destructor stub
}

void MainServlet::handleGet(HttpRequest* request, HttpResponse* response) {
	response->println("Dashboard");
}

void MainServlet::handlePost(HttpRequest* request, HttpResponse* response) {


}
