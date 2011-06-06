/*
 * HttpSession.cpp
 *
 *  Created on: Jun 2, 2011
 *      Author: kyle
 */

#include "HttpSession.h"

HttpSession::HttpSession(const struct mg_request_info *request_info) {
	// TODO Auto-generated constructor stub
	authenticated = false;

	requestMethod = String(request_info->request_method);
	uri = String(request_info->uri);
	httpVersion = String(request_info->http_version);
	queryString = String(request_info->query_string);
	remoteUser = String(request_info->remote_user);
	logMessage = String(request_info->log_message);
	remoteIp = (uint32) request_info->remote_ip;
	remotePort = (short) request_info->remote_port;
	statusCode = (short) request_info->status_code;
	ssl = request_info->is_ssl == 1;

	updateHeaders(request_info->http_headers);
}

HttpSession::~HttpSession() {
	// TODO Auto-generated destructor stub
}

void HttpSession::update(const struct mg_request_info *request_info) {

}

void HttpSession::updateHeaders(const struct mg_request_info::mg_header headers[]) {

}
