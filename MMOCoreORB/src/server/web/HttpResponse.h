/*
 * HttpResponse.h
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include "engine/engine.h"

class HttpResponse {
private:
	StringBuffer out;
	String docType;
public:
	HttpResponse();
	virtual ~HttpResponse();

	void update();

	void print(String item);
	void println(String line);

	String generatePage();

	void setDocType(String value) {
		docType = value;
	}
};

#endif /* HTTPRESPONSE_H_ */
