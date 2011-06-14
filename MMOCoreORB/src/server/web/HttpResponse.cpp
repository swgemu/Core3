/*
 * HttpResponse.cpp
 *
 *  Created on: Jun 1, 2011
 *      Author: kyle
 */

#include "HttpResponse.h"

HttpResponse::HttpResponse() {
	// TODO Auto-generated constructor stub
	docType = "html";
}

HttpResponse::~HttpResponse() {
	// TODO Auto-generated destructor stub
}

void HttpResponse::update() {
	out.deleteAll();
}

void HttpResponse::print(String item) {
	out << item;
}

void HttpResponse::println(String line) {
	out << line << "\r\n";
}

String HttpResponse::generatePage() {
	StringBuffer page;
	page << "HTTP/1.1 200 OK\r\n";
	page << "Content-Type: text/html\r\n\r\n";
	page << "<!doctype " << docType << ">\r\n";
	page << "<html lang='en'>\r\n";
	page << "<body>\r\n";
	page << out.toString() << "\r\n";
	page << "</body>\r\n";
	page << "</html>\r\n";
	return page.toString();
}
