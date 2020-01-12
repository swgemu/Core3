/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : RESTEndpoint.h
 * @created     : Tue Jan  7 12:39:03 UTC 2020
 */

#pragma once

#include "engine/engine.h"
#include <regex>

namespace web {
 namespace json {
  class value;
 }
 namespace http {
  class http_request;
 }
}

namespace server {
 namespace web3 {
 class APIRequest;

 using namespace web;
 using namespace web::http;

class RESTEndpoint {
	public:
		class InvalidEndpoint : public Exception {
		 public:
			InvalidEndpoint(const String& msg) : Exception(msg) {
			}
		};

	private:
		std::regex mRegEx;
		String mRegExStr;
		ArrayList<String> mPathFieldNames;
		Function<void(APIRequest& apiRequest)> mHandler;

	public:
		RESTEndpoint() {
		}

		RESTEndpoint(const String &regex, ArrayList<String> pathFieldNames, Function<void(APIRequest& apiRequest)> handler);

		void setRegEx(const String &regex);
		void setPathFieldNames(ArrayList<String> pathFieldNames);
		void setHandler(Function<void(APIRequest& apiRequest)> handler);
		String toString() const;
		bool isMatch(const String& endpointKey) const;
		int getWeight() const;
		HashTable<String, String> getPathFields(const String& endpointKey) const;
		void handle(APIRequest& apiRequest) const;
		String toStringData() const;
};

}
}
