#include "AdminServlet.h"
#include "../../WebServer.h"

AdminServlet::AdminServlet(const String& context) :
	Servlet(context) {
}

AdminServlet::~AdminServlet() {
}

void AdminServlet::handleGet(HttpRequest* request, HttpResponse* response) {
	ResultSet* result;

	try {
		result = ServerDatabase::instance()->executeQuery("SELECT DISTINCT account_id, ip, COUNT(*) FROM account_ips WHERE timestamp >= DATE_SUB(timestamp, INTERVAL 1 DAY) GROUP BY ip HAVING COUNT(*) > 2 ORDER BY COUNT(*) DESC");
	} catch (DatabaseException& e) {
		response->println(e.getMessage());
		return;
	}

	response->println("HTTP/1.1 200 OK");
	response->println("Content-Type: text/html");
	response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	response->println("	<head>");
	response->println("	 <title>SWGEmu Multiple Account Administration</title>");
	response->println("	 <meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />");
	response->println("	 <link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\" />");
	response->println("	</head>");
	response->println("	<body>");
	response->println("  <table cellspacing=\"0\" cellpadding=\"0\" border=\"0\">");
	response->println("   <caption>Suspect List</caption>");
	response->println("   <tr>");
	response->println("    <th>IP Address</th>");
	response->println("    <th>Count</th>");
	response->println("   </tr>");

	if (result->size() > 0) {
		while (result->next()) {
			String ip = "<a href=\"http://ip-lookup.net/?ip=";
			ip += String::valueOf(result->getString(1));
			ip += "\">";
			ip += String::valueOf(result->getString(1));
			ip += "</a>";
			response->println("   <tr>");
			response->println("    <td>" + ip + "</td>");
			response->println("    <td>" + String::valueOf(result->getInt(2)) + "</td>");
			response->println("   <tr>");
		}
	} else {
		response->println("   <tr>");
		response->println("    <td>No suspects found.</td>");
		response->println("   <tr>");
	}

	delete result;
	result = NULL;

	response->println("	</body>");
	response->println("</html>");
}

void AdminServlet::handlePost(HttpRequest* request, HttpResponse* response) {

}
