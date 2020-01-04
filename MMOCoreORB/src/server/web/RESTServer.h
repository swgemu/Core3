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
 using namespace web;
 using namespace web::http;

 class RESTServer : public Logger {
 protected:
	AtomicBoolean doRun;
	uint16 port;

 private:
	VectorMap<String, Function<void(http_request request, Vector<String> matches)>> apiEndpoints;

	void registerEndpoints();
	void routeRequest(http_request request);
	void error_response(http_request request, String errorMessage);
	void success_response(http_request request, json::value result);
	bool check_auth(http_request request);
	const String getJsonString(json::value jvalue, const String& fieldName, bool required=true, const String& defaultValue="");
	uint64_t getJsonUnsignedLong(json::value jvalue, const String& fieldName, bool required=true, uint64_t defaultValue=0);

 public:
	RESTServer();
	~RESTServer();

	void start();

	void stop();
};

class InvalidRequest : public Exception {
 public:
	InvalidRequest(const String& msg) : Exception(msg) {
	}
};

}
}
#endif // WITH_REST_API
