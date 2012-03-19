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
	response->println("HTTP/1.1 200 OK");
	response->println("Content-Type: text/html\r\n");
	response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	response->println("<head>");
	response->println("	<title>SWGEmu Dashboard</title>");
	response->println("</head>");
	response->println("<body>");
	response->println("<h3>Menu</h3>");
	response->println("<a href='/logs'>Log Viewer</a>");
	response->println("</body>");
	response->println("</html>");
}

void MainServlet::handlePost(HttpRequest* request, HttpResponse* response) {
	handleGet(request, response);
}
