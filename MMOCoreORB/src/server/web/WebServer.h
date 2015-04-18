/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include "engine/engine.h"
#include "server/zone/ZoneServer.h"
#include "server/login/LoginServer.h"
#include "server/login/account/Account.h"
#include "server/login/account/AccountManager.h"
#include "server/conf/ConfigManager.h"
#include "mongoose/mongoose.h"
#include "servlets/Servlet.h"
#include "WebCredentials.h"
#include "session/HttpSessionList.h"

namespace server {
namespace web {
namespace session {
class HttpSession;
}
}
}
using namespace server::web::session;

namespace server {
 namespace web {

class WebServer : public Singleton<WebServer>, public Logger, public Object {
private:
	ManagedReference<ZoneServer*> zoneServer;

	ConfigManager* configManager;

	static struct mg_context *ctx;

	VectorMap<String, Servlet*> contexts;
	VectorMap<String, WebCredentials*> authorizedUsers;
	VectorMap<uint64, HttpSessionList*> activeSessions;
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

	void dispatch(String location, HttpSession* session);

	void forward(struct mg_connection *conn, String content, HttpRequest* request);

private:

	void init();

	void registerBaseContexts();

	void whitelistInit();

	void mongooseMgrInit();


	void* handleRequest(struct mg_connection *conn, const struct mg_request_info *request_info);

	ManagedReference<Account*> validateAccountCredentials(LoginClient* client, const String& username, const String& password);


	HttpSession* getSession(struct mg_connection *conn, const struct mg_request_info *request_info);

	bool validateIPAccess(long remoteIp);

	void displayUnauthorized(struct mg_connection *conn);

	void displayNotFound(struct mg_connection *conn);

	void displayUnauthorized(StringBuffer* out);

	void displayLogin(StringBuffer* out);

	bool isValidIp(String address);

	bool isLocalHost(long address);

	bool isLocalHost(String address);

	uint32 ipStringToLong(String address);

	String ipLongToString(long address);
};

}
}

using namespace server::web;


#endif /* WEBSERVER_H_ */
