/*
 * HttpRequest.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef HTTPREQUEST_H_
#define HTTPREQUEST_H_

#include "engine/engine.h"
#include "mongoose/mongoose.h"

struct HttpHeader {
	String name;
	String value;
};

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
	Vector<HttpHeader*> headers;

	Vector<String> contexts;

public:
	HttpRequest();
	virtual ~HttpRequest();

	void update(const struct mg_request_info *request_info);

	String getBaseContext();

private:

	void updateHeaders(const struct mg_request_info::mg_header incomingheaders[]);

};

#endif /* HTTPREQUEST_H_ */
