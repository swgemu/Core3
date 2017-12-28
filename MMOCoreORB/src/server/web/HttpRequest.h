/*
 * HttpRequest.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include <algorithm>

#include "engine/engine.h"
#include "mongoose/mongoose.h"
#include "session/HttpSession.h"
#include "system/lang/String.h"
#include "system/platform.h"
#include "system/util/Vector.h"
#include "system/util/VectorMap.h"

namespace server {
namespace web {

namespace session {
class HttpSession;
}  // namespace session

class HttpRequest {
private:
	/// Request members
	String requestMethod;
	String uri;
	String httpVersion;
	uint64 remoteIp;
	short remotePort;
	short statusCode;
	bool ssl;
	String userData;

	Vector<String> contexts;

	VectorMap<String, String> headers;

	VectorMap<String, String> parameters;

	HttpSession* session;

public:
	HttpRequest(HttpSession* session);
	virtual ~HttpRequest();

	void update(const struct mg_request_info *request_info);

	String getBaseContext();

	String getUri() {
		return uri;
	}

	String getRequestMethod() {
		return requestMethod;
	}

	String getHeader(String key) {
		key = key.toLowerCase();

		if(headers.contains(key))
			return headers.get(key);
		return "";
	}

	String getParameter(String key) {
		key = key.toLowerCase();
		if(parameters.contains(key))
			return parameters.get(key);
		return "";
	}

	uint64 getRemoteIp() {
		return remoteIp;
	}

	HttpSession* getSession() {
		return session;
	}

	void updatePostData(String data);

private:

};

} // End namespace web
} // End Namespace server

#endif /* HTTPREQUEST_H_ */
