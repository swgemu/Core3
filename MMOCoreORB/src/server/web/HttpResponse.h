/*
 * HttpResponse.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include "engine/engine.h"
#include "session/HttpSession.h"
#include "mongoose/mongoose.h"

namespace server {
namespace web {

class HttpResponse {
private:
	StringBuffer out;
	String docType;

	HttpSession* session;

	struct mg_connection *conn;
public:
	HttpResponse(HttpSession* session);
	virtual ~HttpResponse();

	void update(struct mg_connection *conn);

	void print(String item);
	void println(String line);

	void forwardTo(String context);

	String generatePage();

	void setDocType(String value) {
		docType = value;
	}

	HttpSession* getSession() {
		return session;
	}
};

} // End namespace web
} // End Namespace server

#endif /* HTTPRESPONSE_H_ */
