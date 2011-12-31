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

#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include "engine/engine.h"
#include "../zone/ZoneServer.h"
#include "../login/LoginServer.h"
#include "../login/account/Account.h"
#include "../login/account/AccountManager.h"
#include "../conf/ConfigManager.h"
#include "mongoose/mongoose.h"
#include "servlets/Servlet.h"
#include "WebCredentials.h"

namespace server {
namespace web {
namespace session {
class HttpSession;
}
}
}

class WebServer : public Singleton<WebServer>, public Logger, public Object {
private:
	ManagedReference<ZoneServer*> zoneServer;
	ManagedReference<LoginServer*> loginServer;

	ConfigManager* configManager;

	static struct mg_context *ctx;

	VectorMap<String, Servlet*> contexts;
	VectorMap<String, WebCredentials*> authorizedUsers;
	VectorMap<uint64, HttpSession* > activeSessions;
	Vector<String> authorizedIpAddresses;

public:
	static int sessionTimeout;

public:
	WebServer();

	~WebServer();

	void start(ConfigManager* conf);

	void stop();

	bool addContext(String context, Servlet* servlet);

	static void* uriHandler(enum mg_event event,
		    struct mg_connection *conn,
		    const struct mg_request_info *request_info);

	bool authorize(HttpSession* session);

	void dispatch(String location, HttpRequest* request, HttpResponse* response);

private:

	void init();

	void registerBaseContexts();

	void whitelistInit();

	void mongooseMgrInit();


	void* handleRequest(struct mg_connection *conn, const struct mg_request_info *request_info);

	HttpSession* getSession(struct mg_connection *conn, const struct mg_request_info *request_info);

	bool validateAccess(long remoteIp);

	void displayUnauthorized(struct mg_connection *conn);

	void displayNotFound(struct mg_connection *conn);

	bool validateSession(HttpSession* session);

	void displayUnauthorized(StringBuffer* out);

	void displayLogin(StringBuffer* out);

	bool isValidIp(String address);

	bool isLocalHost(long address);

	bool isLocalHost(String address);

	uint32 ipStringToLong(String address);

	String ipLongToString(long address);
};

#endif /* WEBSERVER_H_ */
