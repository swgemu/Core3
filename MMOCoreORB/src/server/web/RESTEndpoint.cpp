/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : RESTEndpoint.cpp
 * @created     : Tue Jan  7 12:39:03 UTC 2020
 */

#ifdef WITH_REST_API

#include "RESTEndpoint.h"
#include "APIRequest.h"

using namespace std;
using namespace server::web3;

RESTEndpoint::RESTEndpoint(const String &regex, ArrayList<String> pathFieldNames, Function<void(APIRequest& apiRequest)> handler)
	: mRegExStr(regex), mPathFieldNames(pathFieldNames), mHandler(handler) {

		mRegEx = std::regex(regex.toCharArray());
}

void RESTEndpoint::setRegEx(const String &regex) {
	mRegExStr = regex;
	mRegEx = std::regex(regex.toCharArray());
}

void RESTEndpoint::setPathFieldNames(ArrayList<String> pathFieldNames) {
	mPathFieldNames = pathFieldNames;
}

void RESTEndpoint::setHandler(Function<void(APIRequest& apiRequest)> handler) {
	mHandler = handler;
}

String RESTEndpoint::toString() const {
	StringBuffer buf;

	buf << "[RESTEndpoint] " << mRegExStr;

	if (mPathFieldNames.size() > 0) {
		buf << " fieldNames:";
		auto sep = " ";
		for (auto fieldName : mPathFieldNames) {
			buf << sep << fieldName;
			sep = ", ";
		}
	}

	return buf.toString();
}

String RESTEndpoint::toStringData() const {
	return toString();
}

bool RESTEndpoint::isMatch(const String& endpointKey) const {
	return std::regex_search(endpointKey.toCharArray(), mRegEx);
}

int RESTEndpoint::getWeight() const {
	return mRegExStr.length();
}

HashTable<String, String> RESTEndpoint::getPathFields(const String& endpointKey) const {
	HashTable<String, String> pathFields;

	if (mPathFieldNames.size() == 0) {
		return pathFields;
	}

	ArrayList<String> matches;
	std::cmatch reMatches;

	if (!std::regex_match (endpointKey.toCharArray(), reMatches, mRegEx))
		return pathFields;

	if ((reMatches.size() - 1) != mPathFieldNames.size()) {
		StringBuffer buf;

		buf << mRegExStr << " - Matched " << reMatches.size() << " field(s), expected " << mPathFieldNames.size();

		throw InvalidEndpoint(buf.toString());
	}

	for (int i = 0;i < mPathFieldNames.size();i++) {
		pathFields.put(mPathFieldNames.get(i), String(reMatches[i+1]));
	}

	return pathFields;
}

void RESTEndpoint::handle(APIRequest& apiRequest) const {
	apiRequest.setPathFields(getPathFields(apiRequest.getEndpointKey()));

	mHandler(apiRequest);
}

#endif // WITH_REST_API
