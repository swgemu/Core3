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

class HttpSession {
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

public:
    HttpSession();
	virtual ~HttpSession();

	void update(const struct mg_request_info *request_info);

	bool hasExpired();

    bool isValid();

    HttpRequest* getRequest() {
    	return request;
    }

    HttpResponse* getResponse() {
    	return response;
    }

    String getUser() {
    	return user;
    }

private:

	void updateTimestamp();

};

#endif /* HTTPSESSION_H_ */
