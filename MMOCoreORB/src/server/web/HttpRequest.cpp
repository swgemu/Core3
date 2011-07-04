/*
 * HttpRequest.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#include "HttpRequest.h"
#include "mongoose/mongoose.h"

HttpRequest::HttpRequest() {
	// TODO Auto-generated constructor stub

}

HttpRequest::~HttpRequest() {
	// TODO Auto-generated destructor stub
}

void HttpRequest::update(const struct mg_request_info *request_info) {

	requestMethod = String(request_info->request_method);
	uri = String(request_info->uri);

	StringTokenizer tokenizer(uri);
	tokenizer.setDelimeter("/");

	while(tokenizer.hasMoreTokens()) {
		String token;
		tokenizer.getStringToken(token);
		contexts.add(token);
	}

	httpVersion = String(request_info->http_version);
	remoteIp = (uint64) request_info->remote_ip;
	remotePort = (short) request_info->remote_port;
	statusCode = (short) request_info->status_code;
	ssl = request_info->is_ssl == 1;

	headers.removeAll();
	for(int i = 0; i < request_info->num_headers; ++i) {
		headers.put(request_info->http_headers[i].name, request_info->http_headers[i].value);
	}
}

void HttpRequest::updatePostData(String data) {

	parameters.removeAll();

	StringTokenizer tokenizer(data);
	tokenizer.setDelimeter("&");

	while(tokenizer.hasMoreTokens()) {
		String nextPair;
		tokenizer.getStringToken(nextPair);

		StringTokenizer pair(nextPair);
		pair.setDelimeter("=");

		if(pair.hasMoreTokens()) {
			String key;
			pair.getStringToken(key);

			if(pair.hasMoreTokens()) {
				String value;
				pair.getStringToken(value);

				if(!pair.hasMoreTokens()) {
					parameters.put(key, value);
				}
			}
		}
	}
}

String HttpRequest::getBaseContext() {
	return contexts.get(0);
}
