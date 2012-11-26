/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "WebServer.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "servlets/login/LoginServlet.h"
#include "servlets/logs/LogsServlet.h"
#include "servlets/main/MainServlet.h"
#include "servlets/character/CharacterServlet.h"
#include "servlets/account/AccountServlet.h"
#include "servlets/permissions/PermissionsServlet.h"
#include "servlets/admin/AdminServlet.h"

mg_context *WebServer::ctx;
int WebServer::sessionTimeout;

WebServer::WebServer() {

	configManager = NULL;

	// Lookup zone to have access to playerobjects
	zoneServer = cast<ZoneServer*>(DistributedObjectBroker::instance()->lookUp("ZoneServer"));

	// Default Time in minutes, value is in script
	sessionTimeout = 10;

	setLogging(true);
	setLoggingName("Webserver");
	setInfoLogLevel();

}

WebServer::~WebServer() {

	while(authorizedUsers.size() > 0) {
		delete authorizedUsers.remove(0).getValue();
	}

	while(contexts.size() > 0) {
		delete contexts.remove(0).getValue();
	}

	while(activeSessions.size() > 0) {
		delete activeSessions.remove(0).getValue();
	}

}

void WebServer::start(ConfigManager* conf) {

	info("Starting", true);

	configManager = conf;

	init();
}

void WebServer::stop() {
	mg_stop(ctx);
}

void WebServer::init() {

	registerBaseContexts();

	whitelistInit();

	mongooseMgrInit();
}

void WebServer::registerBaseContexts() {
	addContext("login", new LoginServlet("login"));
	addContext("main", new MainServlet("main"));
	addContext("logs", new LogsServlet("logs"));
	addContext("character", new CharacterServlet("character"));
	addContext("account", new AccountServlet("account"));
	addContext("permissions", new PermissionsServlet("permissions"));
	addContext("admin", new AdminServlet("admin"));
}

void WebServer::whitelistInit() {

	authorizedUsers.removeAll();
	authorizedIpAddresses.removeAll();

	info("Parsing access whitelist 'conf/webusers.lst'", true);

	if(zoneServer == NULL) {
		error("Zone server lookup failed, unable to verify users for access");
		return;
	}

	File* webusersFile = new File("conf/webusers.lst");

	try {
		FileReader webusersReader(webusersFile);

		String line, username, ipaddress;

		while (webusersReader.readLine(line)) {
			String entry = line.trim().toLowerCase();

			if(entry.indexOf("--") != -1)
				entry = entry.subString(0, entry.indexOf("--")).trim();

			if(entry.isEmpty())
				continue;

			StringTokenizer tokenizer(entry);
			tokenizer.setDelimeter(";");

			if(tokenizer.hasMoreTokens()) {
				tokenizer.getStringToken(username);
			} else {
				error("Whitelist entry error for " + line);
				continue;
			}

			if(tokenizer.hasMoreTokens()) {
				tokenizer.getStringToken(ipaddress);
			} else {
				error("Whitelist ip error for " + username);
				continue;
			}

			if(isValidIp(ipaddress)) {

				authorizedIpAddresses.add(ipaddress);

				WebCredentials* credentials;

				if(authorizedUsers.contains(username)) {
					credentials = authorizedUsers.get(username);
					credentials->addInetAddress(ipaddress);
				} else {
					credentials = new WebCredentials(username, ipaddress);
					authorizedUsers.put(username, credentials);
				}
			} else {
				error("IP address is invalid for: " + username + " IP: " + ipaddress);
			}
		}
	} catch (FileNotFoundException&e ) {

		error("Whitelist not found");

	}

	delete webusersFile;
}

void WebServer::mongooseMgrInit() {

	String errorLog = configManager->getWebErrorLog();
	String webLog = configManager->getWebAccessLog();
	String ports = configManager->getWebPorts();
	sessionTimeout = configManager->getWebSessionTimeout();

	const char *options[] = {
		"error_log_file", errorLog.toCharArray(),
		"access_log_file", webLog.toCharArray(),
		"listening_ports", ports.toCharArray(),
		"enable_directory_listing", "no",
		"document_root", "../doc/www",
		NULL
	};

	ctx = mg_start(&uriHandler, NULL, options);

	if(ctx == NULL)
		info("Failed to initialize", true);
	else
		info("Initialized", true);
}

bool WebServer::addContext(String context, Servlet* servlet) {
	if(!contexts.contains(context)) {
		contexts.put(context, servlet);
		servlet->setZoneServer(zoneServer);
		return true;
	}
	error("addContext - Context already exists: " + context);
	return false;
}

void* WebServer::uriHandler(
		enum mg_event event,
	    struct mg_connection *conn,
	    const struct mg_request_info *request_info)
{
	return WebServer::instance()->handleRequest(conn, request_info);
}

void* WebServer::handleRequest(struct mg_connection *conn, const struct mg_request_info *request_info) {

	/// First we validate the IP address to see if we should proceed
//	if(!validateIPAccess(request_info->remote_ip)) {
//
//		displayUnauthorized(conn);
//		info("Unauthorized access attempt from " + ipLongToString((uint32)request_info->remote_ip));
//		return (void*)1;
//	}

	HttpSession* session = getSession(conn, request_info);

	/// If it's a CSS request grant request
	if(session->getRequest()->getUri().indexOf(".css") == session->getRequest()->getUri().length() - 4) {
		return 0;
	}

	String context = session->getRequest()->getBaseContext();
	Servlet* servlet = contexts.get(context);

	/// If the session isn't valid, only the login servlet is Accessable
	if((servlet == NULL || servlet->getContext() != "login") && !session->isAuthenticated()) {
		session->debug("NOT Authenticated forwarding to /login");
		forward(conn, "/login", session->getRequest());
		return (void*)1;
	} else if (session->isAuthenticated()) {

		/*if(!validateCookie(request_info->remote_ip, session)) {
			displayUnauthorized(conn);
			info("Unauthorized login attempt from " + ipLongToString((uint32)request_info->remote_ip));
			return (void*)1;
		}*/

		if(servlet != NULL && servlet->getContext() == "login") {
			forward(conn, "/main", session->getRequest());
			return (void*)1;
		}

		if(servlet != NULL)
			session->debug("Authenticated for /" + servlet->getContext());
	}

	if(servlet != NULL) {

		servlet->handleRequest(conn, session->getRequest(), session->getResponse());

	} else {

		displayNotFound(conn);
	}

	return (void*)1;
}

void WebServer::dispatch(String location, HttpSession* session) {

	Servlet* servlet = contexts.get(location);

	if(servlet != NULL) {

		servlet->handleGet(session->getRequest(), session->getResponse());
	}
}

void WebServer::forward(struct mg_connection *conn, String context, HttpRequest* request) {

	StringBuffer content;

	content << "HTTP/1.1 301 Moved Permanently\r\n";
	content << "Location: " + context + "\r\n\r\n";
	content << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN " "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n";
	content << "<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n";
	content << "<head>\r\n";
	content << "</head>\r\n";
	content << "<body>\r\n";
	content << "</body>\r\n";
	content << "</html>";

	mg_printf(conn, content.toString().toCharArray());
}

/**
 * Find existing session, or create new one if one doesn't exist
 * or has timed out
 */
HttpSession* WebServer::getSession(struct mg_connection *conn, const struct mg_request_info *request_info) {

	HttpSessionList* sessionList = NULL;
	HttpSession* session = NULL;
	bool foundSession = false;

	if(activeSessions.contains(request_info->remote_ip)) {
		sessionList = activeSessions.get((uint64)request_info->remote_ip);

		for(int i = 0; i < sessionList->size(); ++i) {
			session = sessionList->get(i);

			if(session == NULL)
				continue;

			String sessionId = session->getSessionId();
			String requestSessionId = session->getRequest()->getHeader("Cookie");

			if(requestSessionId.contains(sessionId)) {
				foundSession = true;
				break;
			}

			session = NULL;
		}

		if(session != NULL && session->hasExpired()) {
			sessionList->drop(session->getSessionId());
			delete session;

			if(sessionList->isEmpty()) {
				activeSessions.drop(request_info->remote_ip);
				delete sessionList;
			}
		}

		if(session != NULL)
			session->update(conn, request_info);

	}

	if (session == NULL) {

		session = new HttpSession();
		session->update(conn, request_info);
		session->setSessionIp(request_info->remote_ip);

		sessionList = activeSessions.get((uint64) request_info->remote_ip);
		if (sessionList == NULL) {
			sessionList = new HttpSessionList();
			activeSessions.put(request_info->remote_ip, sessionList);
		}

		String requestSessionId = session->getRequest()->getHeader("Cookie");

		if(!requestSessionId.isEmpty()) {
			session->setSessionId(requestSessionId);
		}

		sessionList->put(session->getSessionId(), session);

	}

	/// Get Post Data
	int length = Integer::valueOf(session->getRequest()->getHeader("Content-Length")) + 1;

	/// Ensure no stack corruption
	if(length > 0 && length < 1024) {

		char* postDataBuffer = new char[1024];

		mg_read(conn, postDataBuffer, 1024);

		postDataBuffer[length - 1] = '\0';

		session->getRequest()->updatePostData(postDataBuffer);

		delete [] postDataBuffer;

	} else if(length >= 1000) {
		error("Post data length was too long: " + String::valueOf(length));
	}

	debug("Using session: " + session->getSessionId());

	return session;
}

/**
 * Check session IP against valid ip addresses to deny access
 */
bool WebServer::validateIPAccess(long remoteIp) {

	for(int i = 0; i < authorizedIpAddresses.size(); ++i) {
		long authorizedAddress = ipStringToLong(authorizedIpAddresses.get(i));

		if(remoteIp == authorizedAddress) {
			return true;
		}
	}

	return false;
}

void WebServer::displayUnauthorized(struct mg_connection *conn) {

	StringBuffer out;

	out.append("HTTP/1.1 200 OK\r\n");
	out.append("Content-Type: text/html\r\n\r\n");
	out.append("Access denied");

	mg_printf(conn, out.toString().toCharArray());
}

void WebServer::displayNotFound(struct mg_connection *conn) {

	StringBuffer out;

	out.append("HTTP/1.1 200 OK\r\n");
	out.append("Content-Type: text/html\r\n\r\n");
	out.append("404: Page not found");

	mg_printf(conn, out.toString().toCharArray());
}

void WebServer::displayLogin(StringBuffer* out) {
	out->append("Please login");
}

bool WebServer::authorize(HttpSession* session) {

	ManagedReference<Account*> account = validateAccountCredentials(NULL,
			session->getUserName(), session->getPassword());

	/// Remove Password
	session->setPassword("");

	if(account == NULL) {
		return false;
	}

	if(account->getAdminLevel() == PlayerObject::NORMALPLAYER ||
			!authorizedUsers.contains(session->getUserName())) {

		error("User is not authorized for web access: " + session->getUserName());
		return false;
	}

//	WebCredentials* credentials = authorizedUsers.get(session->getUserName());
//
//	String address = ipLongToString((long)session->getSessionIp());
//
//	if(credentials->contains(address)) {
		session->setAuthenticated(true);
		info("Successful Login: " + session->getUserName());
		return true;
//	}
//
//	info("Failed Login: " + session->getUserName());
//
//	return false;
}

ManagedReference<Account*> WebServer::validateAccountCredentials(LoginClient* client, const String& username, const String& password) {


	ManagedReference<Account*> account = zoneServer->getPlayerManager()->getAccount(username);

	if(account == NULL)
		return NULL;

	StringBuffer query;
	query << "SELECT a.password, a.salt FROM accounts a WHERE a.username = '" << username << " 'LIMIT 1;";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	String dbPassword;
	String dbSalt;

	if (result->next()) {
		dbPassword = result->getString(0);
		dbSalt = result->getString(1);
	} else {
		return NULL;
	}

	String inputtedPassword = Crypto::SHA256Hash(configManager->getDBSecret() + password + dbSalt);

	if(inputtedPassword == dbPassword) {
		return account;
	}

	error("Invalid Password");
	return NULL;
}

bool WebServer::isLocalHost(String address) {
	return address == "127.0.0.1";
}

bool WebServer::isLocalHost(long address) {
	return address == 2130706433;
}

bool WebServer::isValidIp(String address) {

	if(ipStringToLong(address) != 0)
		return true;
	else
		return false;
}

uint32 WebServer::ipStringToLong(String address) {

	long returnAddress = 0;
	int tokencount = 0;

	StringTokenizer ipAddress(address);
	ipAddress.setDelimeter(".");


	while(ipAddress.hasMoreTokens()) {
		try {

			int octet = ipAddress.getIntToken();
			tokencount++;

			if(tokencount == 5)
				return 0;

			if(octet >= 0 && octet <= 255) {

				returnAddress += (octet << (32 - (tokencount * 8)));

			} else {
				return 0;
			}

		} catch (const Exception& e) {
			return 0;
		}
	}

	if(tokencount == 4)
		return returnAddress;
	else
		return 0;
}

String WebServer::ipLongToString(long address) {

	StringBuffer ipAddress;
	short octet1, octet2, octet3, octet4;
	octet1 = (address >> 24);
	octet2 = (address >> 16) & 0xFF;
	octet3 = (address >> 8) & 0xFF;
	octet4 = (address >> 0) & 0xFF;

	ipAddress << octet1 << "." << octet2 << "." << octet3 << "." << octet4;

	return ipAddress.toString();
}
