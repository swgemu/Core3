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

struct HttpHeader {
	String name;
	String value;
};

class HttpSession {
public:
	bool authenticated;
	String requestMethod;
	String uri;
	String httpVersion;
	String queryString;
	String remoteUser;
	String logMessage;
	uint32 remoteIp;
	short remotePort;
	short statusCode;
	bool ssl;
	Vector<HttpHeader*> headers;
	uint32 timestamp;

    HttpSession(const struct mg_request_info *request_info);
	virtual ~HttpSession();

	void update(const struct mg_request_info *request_info);

	void updateHeaders(const struct mg_request_info::mg_header headers[]);

    bool isValid()
    {
        return authenticated;
    }

    Vector<HttpHeader*> getHeaders() const
    {
        return headers;
    }

    String getHttpVersion() const
    {
        return httpVersion;
    }

    String getLogMessage() const
    {
        return logMessage;
    }

    String getQueryString() const
    {
        return queryString;
    }

    uint32 getRemoteIp() const
    {
        return remoteIp;
    }

    short getRemotePort() const
    {
        return remotePort;
    }

    String getRemoteUser() const
    {
        return remoteUser;
    }

    String getRequestMethod() const
    {
        return requestMethod;
    }

    bool getSsl() const
    {
        return ssl;
    }

    short getStatusCode() const
    {
        return statusCode;
    }

    String getUri() const
    {
        return uri;
    }

};

#endif /* HTTPSESSION_H_ */
