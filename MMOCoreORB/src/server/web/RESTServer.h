/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : theanswer (theanswer@Victors-MacBook-Pro.local)
 * @file        : RESTServer
 * @created     : Sunday Nov 11, 2018 11:27:17 CET
 */

#pragma once

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "system/thread/atomic/AtomicBoolean.h"

namespace web {
 namespace json {
  class value;
 }
 namespace http {
  class http_request;
 }
}

namespace server {
 namespace web3 {
 class APIRequest;
 class APIProxyPlayerManager;
 class RESTEndpoint;

 using namespace web;
 using namespace web::http;

 class RESTServer : public Logger {
 protected:
	AtomicBoolean doRun;
	uint16 port;

 private:
	ArrayList<RESTEndpoint> apiEndpoints;
	APIProxyPlayerManager* proxyPlayerManager;

	void registerEndpoints();
	bool check_auth(http_request& request);
	void routeRequest(http_request& request);
	void handlePlayerManagerRequest(APIRequest& request);

 public:
	RESTServer();
	~RESTServer();

	void start();

	void stop();
};

}
}
#endif // WITH_REST_API
