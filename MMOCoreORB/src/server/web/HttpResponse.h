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

namespace server {
namespace web {

class HttpResponse {
private:
	StringBuffer out;
	String docType;

	HttpSession* session;
public:
	HttpResponse(HttpSession* session);
	virtual ~HttpResponse();

	void update();

	void print(String item);
	void println(String line);

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
