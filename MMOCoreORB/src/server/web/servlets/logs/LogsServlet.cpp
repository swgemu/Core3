/*
 * LogsServlet.cpp
 *
 *  Created on: Mar 18, 2012
 *      Author: kyle
 */

#include "LogsServlet.h"
#include "../../WebServer.h"

LogsServlet::LogsServlet(String context) :
	Servlet(context) {
	// TODO Auto-generated constructor stub

}

LogsServlet::~LogsServlet() {
	// TODO Auto-generated destructor stub
}

void LogsServlet::handleGet(HttpRequest* request, HttpResponse* response) {

	response->println("HTTP/1.1 200 OK");
	response->println("Content-Type: text/html\r\n");
	response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	response->println("<head>");
	response->println("	<title>SWGEmu Log Viewer</title>");
	response->println("</head>");
	response->println("<body>");
	response->println("<h2>Log Viewer<h2>");
	response->println("</body>");
	response->println("</html>");
}

void LogsServlet::handlePost(HttpRequest* request, HttpResponse* response) {
	handleGet(request, response);
}
