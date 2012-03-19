/*
 * HttpSession.h
 *
 *  Created on: Jun 2, 2011
 *      Author: kyle
 */

#ifndef HTTPSESSION_H_
#define HTTPSESSION_H_

#include "engine/engine.h"
#include "../mongoose/mongoose.h"

namespace server {
namespace web {

class HttpRequest;
class HttpResponse;

}
}
using namespace server::web;

namespace server {
namespace web {
namespace session {

class HttpSession : public Logger {
private:

	/// The request
	HttpRequest* request;

	/// The response
	HttpResponse* response;

	/// Request members
	bool authenticated;

	/// Last Activity
	uint64 timestamp;

	/// Current user - Core3 Account Name
	String user;

	/// Current users password
	String password;

	/// Session id
	String sessionId;

	/// ip
	long ip;

	bool canSetId;


public:
    HttpSession();
	virtual ~HttpSession();

	void update(struct mg_connection *conn, const struct mg_request_info *request_info);

	bool hasExpired();

    HttpRequest* getRequest() {
    	return request;
    }

    HttpResponse* getResponse() {
    	return response;
    }

    String getUserName() {
    	return user;
    }

    void setUserName(String value) {
     	user = value;
    }

    String getPassword() {
    	return password;
    }

    void setPassword(String value) {
     	password = value;
    }

    String getSessionId() {
    	return sessionId;
    }

    void setSessionId(String value) {

    	if(!canSetId)
    		return;

    	sessionId = value.replaceFirst("name=", "");
    	canSetId = false;

    	debug("Found existing session, updating: " + sessionId);

    	setLoggingName("HttpSession_" + sessionId);
    }

    long getSessionIp() {
    	return ip;
    }

    void setSessionIp(long value) {
     	ip = value;
     }

    bool isAuthenticated() {
    	return authenticated == true;
    }

    void setAuthenticated(bool auth) {
     	authenticated = auth;
    }

private:

	void updateTimestamp();

	String generateRandomKey(int length);

};

}
}
}
using namespace server::web::session;

#endif /* HTTPSESSION_H_ */
