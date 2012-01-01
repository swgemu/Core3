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
#include "servlets/main/MainServlet.h"

mg_context *WebServer::ctx;
int WebServer::sessionTimeout;

WebServer::WebServer() {

	configManager = NULL;

	// Lookup zone to have access to playerobjects
	zoneServer = cast<ZoneServer*>(DistributedObjectBroker::instance()->lookUp("ZoneServer"));

	// Lookup login for account info
	loginServer = cast<LoginServer*>(DistributedObjectBroker::instance()->lookUp("LoginServer"));

	sessionTimeout = 600;

	setLogging(true);
	setLoggingName("Webserver");

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

	LoginServlet* loginServlet = new LoginServlet("login");
	MainServlet* mainServlet = new MainServlet("main");
}

void WebServer::whitelistInit() {

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
		"error_log_file", errorLog,
		"access_log_file", webLog,
		"listening_ports", ports,
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
	if(!validateAccess(request_info->remote_ip)) {

		displayUnauthorized(conn);
		info("Unauthorized login attempt from " + ipLongToString((uint32)request_info->remote_ip));
		return (void*)1;
	}

	HttpSession* session = getSession(conn, request_info);

	Servlet* servlet = contexts.get(session->getRequest()->getBaseContext());

	/// If the session isn't valid, only the login servlet is Accessable
	if(!validateSession(session)) {
		servlet = contexts.get("login");
	}

	/// If it's a CSS request
	if(session->getRequest()->getUri().indexOf(".css") == session->getRequest()->getUri().length() - 4) {
		return 0;
	}

	if(servlet != NULL) {

		servlet->handleRequest(conn, session->getRequest(), session->getResponse());

	} else {

		displayNotFound(conn);
	}

	return (void*)1;
}

void WebServer::dispatch(String location, HttpRequest* request, HttpResponse* response) {

	Servlet* servlet = contexts.get(location);

	if(servlet != NULL) {
		servlet->handleGet(request, response);
		return;
	}
}

/**
 * Find existing session, or create new one if one doesn't exist
 * or has timed out
 */
HttpSession* WebServer::getSession(struct mg_connection *conn, const struct mg_request_info *request_info) {

	HttpSession* session = NULL;

	if(activeSessions.contains(request_info->remote_ip)) {
		session = activeSessions.get((uint64)request_info->remote_ip);

		if(session->hasExpired()) {
			activeSessions.drop(request_info->remote_ip);
			info("Deleting session for " + ipLongToString(request_info->remote_ip));
			delete session;
		}

	} else {

		session = new HttpSession();
		activeSessions.put(request_info->remote_ip, session);
		info("New session created for " + ipLongToString(request_info->remote_ip));

	}

	session->update(request_info);

	/// Get Post Data
	int length = Integer::valueOf(session->getRequest()->getHeader("Content-Length")) + 1;

	/// Ensure no stack corruption
	if(length > 0 && length < 1000) {

		char* postData = new char[length];

		mg_read(conn, &postData, length);

		//postData[length - 1] = '\0';

		System::out << postData << endl;

		session->getRequest()->updatePostData(String(postData));

		delete [] postData;

	} else if(length >= 1000) {
		error("Post data length was too long" + length);
	}
	info("Updated session for " + ipLongToString(request_info->remote_ip));

	return session;
}

/**
 * Check session IP against valid ip addresses to deny access
 */
bool WebServer::validateAccess(long remoteIp) {

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

	out.append("Access denied");

	mg_printf(conn, out.toString());
}

void WebServer::displayNotFound(struct mg_connection *conn) {

	StringBuffer out;

	out.append("404: Page not found");

	mg_printf(conn, out.toString());
}

bool WebServer::validateSession(HttpSession* session) {

	if(session->isValid())
		return true;

	return false;
}

void WebServer::displayLogin(StringBuffer* out) {
	out->append("Please login");
}

bool WebServer::authorize(HttpSession* session) {

	/*Account* account = loginServer->getAccountManager()->validateAccountCredentials(NULL, username, password);

	if(account == NULL) {
		info("Attemped login by " + username +", account doesn't exist");
		return false;
	}

	if(account->getAdminLevel() == PlayerObject::NORMALPLAYER ||
			!authorizedUsers.contains(username)) {
-
		error("User is not authorized for web access: " + username);
		return false;
	}

	WebCredentials* credentials = authorizedUsers.get(username);

	if(credentials->contains(ipLongToString((long)session->getRemoteIp()))) {
		return true;
	}
	else
		return false;*/
	return false;
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
