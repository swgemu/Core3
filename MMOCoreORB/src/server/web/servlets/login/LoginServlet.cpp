/*
 * LoginServlet.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#include "LoginServlet.h"
#include "../../WebServer.h"

LoginServlet::LoginServlet(String context) :
	Servlet(context) {
	// TODO Auto-generated constructor stub

}

LoginServlet::~LoginServlet() {
	// TODO Auto-generated destructor stub
}

void LoginServlet::handleGet(HttpRequest* request, HttpResponse* response) {

	response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	response->println("	<head>");
	response->println("		<title>SWGEmu Web Server Login</title>");
	response->println("		<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />");
	response->println("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\" />");
	response->println("	</head>");
	response->println("	<body>");
	response->println("		<div class=\"login_box\">");
	response->println("			<h1>Authentication Required</h1>");
	response->println("			<form name=\"login\" action=\"login\" method=\"POST\">");
	response->println("				<label for=\"username\">Username</label><div class=\"textbox_container\"><input type=\"text\" name=\"username\" id=\"login_username\" class=\"textbox\" /></div>");
	response->println("				<label for=\"password\">Password</label><div class=\"textbox_container\"><input type=\"password\" name=\"password\" id=\"login_password\" class=\"textbox\" /></div>");
	response->println("				<input type=\"submit\" value=\"Login\" class=\"submit\" />");
	response->println("			</form>");
	response->println("		</div>");
	response->println("	</body>");
	response->println("</html>");
}

void LoginServlet::handlePost(HttpRequest* request, HttpResponse* response) {

	HttpSession* session = request->getSession();
	/*session->setUserName(request->getParameter("username"));
	session->setPassword(request->getParameter("password"));
	session->setRemoteIp(request->getRemoteIp());

	bool authorized = WebServer::instance()->authorize(session);

	if(authorized) {
		WebServer::instance()->dispatch("main", session);
		return;
	}*/

	response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	response->println("	<head>");
	response->println("		<title>SWGEmu Web Server Login</title>");
	response->println("		<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />");
	response->println("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\" />");
	response->println("	</head>");
	response->println("	<body>");
	response->println("		<div class=\"login_box\">");
	response->println("			<h1>You are not authorized</h1>");
	response->println("		</div>");
	response->println("	</body>");
	response->println("</html>");
}
