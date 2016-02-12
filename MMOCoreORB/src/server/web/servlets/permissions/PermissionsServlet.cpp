/*
 * PermissionsServlet.h
 *
 *  Created on: May 11, 2012
 *      Author: Itac
 */

#include "PermissionsServlet.h"
#include "../../WebServer.h"
#include "server/zone/managers/player/PermissionLevelList.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureObject.h"

PermissionsServlet::PermissionsServlet(String context) :
Servlet(context) {
	// TODO Auto-generated constructor stub

}

PermissionsServlet::~PermissionsServlet() {
	// TODO Auto-generated destructor stub
}

void PermissionsServlet::handleGet(HttpRequest* request, HttpResponse* response) {
	PermissionLevelList* permissionLevelList = PermissionLevelList::instance();
	response->println("HTTP/1.1 200 OK");
	response->println("Content-Type: text/html\r\n");
	response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	response->println("	<head>");
	response->println("		<title>SWGEmu Set Account Permissions</title>");
	response->println("		<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />");
	response->println("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\" />");
	response->println("	</head>");
	response->println("	<body>");
	response->println("		<div class=\"login_box\">");
	response->println("			<h1>Set Account Permissions</h1>");
	response->println("			<form name=\"permissions\" action=\"permissions\" method=\"POST\">");
	response->println("				<label for=\"accountName\">Account Name:</label><div class=\"textbox_container\"><input type=\"text\" name=\"accountName\" id=\"permissions_accountName\" class=\"textbox\" /></div>");
	response->println("				<label for=\"level\">Permissions Level:</label><div class=\"textbox_container\"><select name=\"level\" id=\"permissions_level\" class=\"textbox\">");
	for(int i = 0; i < permissionLevelList->size(); ++i) {
		Reference<PermissionLevel*> level = permissionLevelList->get(i);
		response->println("					<option>" + level->getName() + "</option>");
	}
	response->println("				</select>");
	response->println("				<label for=\"applyToAll\">Apply to All Characters:</label><div class=\"textbox_container\"><input type=\"checkbox\" name=\"applyToAll\" id=\"permissions_applyToAll\" value=\"true\" /></div>");
	response->println("				<input type=\"submit\" value=\"Update\" class=\"submit\" />");
	response->println("			</form>");
	response->println("		</div>");
	response->println("	</body>");
	response->println("</html>");
}

void PermissionsServlet::handlePost(HttpRequest* request, HttpResponse* response) {
	PlayerManager* playerManager = server->getPlayerManager();
	bool applyToAll = false;
	String accountName = request->getParameter("accountName");
	String levelName = request->getParameter("level");
	int level = PermissionLevelList::instance()->getLevelNumber(levelName);

	if(request->getParameter("applyToAll") == "true")
		applyToAll = true;

	ManagedReference<Account*> account = AccountManager::getAccount(accountName);
	if(account == NULL) {
		response->println("HTTP/1.1 200 OK\r\n");
		response->println("Content-Type: text/html\r\n\r\n");
		response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN " "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
		response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
		response->println("	<head>");
		response->println("		<title>SWGEmu Web Server Login</title>");
		response->println("		<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />");
		response->println("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\" />");
		response->println("	</head>");
		response->println("	<body>");
		response->println("		<div class=\"login_box\">");
		response->println("			<h1>Account doesn't exist.</h1>");
		response->println("			<a href=\"permissions\"> Click here to return </a>");
		response->println("		</div>");
		response->println("	</body>");
		response->println("</html>");
	}

	Locker locker(account);
	account->setAdminLevel(level);
	locker.release();

	if(applyToAll == true) {
		Reference<CharacterList*> characterList = account->getCharacterList();
		for(int i = 0; i < characterList->size(); ++i) {
			ManagedReference<CreatureObject* > targetCreature = NULL;
			CharacterListEntry* entry = &characterList->get(i);

			targetCreature = playerManager->getPlayer(entry->getFirstName());
			playerManager->updatePermissionLevel(targetCreature, level);
		}
	}

	response->println("HTTP/1.1 200 OK\r\n");
	response->println("Content-Type: text/html\r\n\r\n");
	response->println("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN " "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">");
	response->println("<html xmlns=\"http://www.w3.org/1999/xhtml\">");
	response->println("	<head>");
	response->println("		<title>SWGEmu Web Server Login</title>");
	response->println("		<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\" />");
	response->println("		<link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\" />");
	response->println("	</head>");
	response->println("	<body>");
	response->println("		<div class=\"login_box\">");
	response->println("			<h1>Account updated.</h1>");
	response->println("			<a href=\"permissions\"> Click here to return </a>");
	response->println("		</div>");
	response->println("	</body>");
	response->println("</html>");
}
