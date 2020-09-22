/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIRequest.cpp
 * @created     : Sun Jan  5 11:26:18 UTC 2020
 */

#ifdef WITH_REST_API

#include "engine/engine.h"
#include "APIRequest.h"
#include "APIRequestStatus.h"
#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace server::web3;

/*
** Example request mapped to APIRequest taxonomy
**
** POST URI    : /v1/admin/console/shutdown?args=10 BODY: {"test"=123}
** Endpoint Key: POST:/v1/admin/console/shutdown
**
** APIRequest members:
**  mEndpointKey: RESTEndpoint("POST:/v1/admin/console/(\\w+)", {"command"},...
**  mPathFields : {"command"="shutdown"}
**  mQueryFields: {"args"="10"}
**  mRequestJSON: {"test"="123"}
*/

APIRequest::APIRequest(http_request gatewayRequest, const String endpointKey, Logger& logger) {
	uint64 trxid = (System::getMikroTime() << 8) | System::random(255);
	mTrxId = String::hexvalueOf(trxid);
	mGatewayRequest = gatewayRequest;
	mParsedRequestJSON = false;
	mReplied = false;
	mFailed = false;
	mEndpointKey = endpointKey;
	setLoggingName("APIRequest " + mTrxId);
	setLoggerCallback([this, &logger] (Logger::LogLevel level, const char* msg) -> int {
		StringBuffer buf;

		buf << "[" << getLoggingName() << "] " << msg;

		logger.log(buf.toString().toCharArray(), level, false);

		return Logger::SUCCESS;
	});
	parseQueryFields();
}

APIRequest::~APIRequest() {
}

String APIRequest::toString() const {
	StringBuffer buf;

	buf << "[APIRequest]"
		<< " " << mTrxId
		<< ": replied: " << mReplied
		<< ", endpointKey: " << mEndpointKey
		<< ", pathFields: {"
		;

	auto pathFieldIter = mPathFields.iterator();
	auto sep = "";

	while(pathFieldIter.hasNext()) {
		String fieldName, fieldValue;
		pathFieldIter.getNextKeyAndValue(fieldName, fieldValue);

		buf << sep << "\"" << fieldName << ":\"" << fieldValue << "\"";
		sep = ", ";
	}

	buf << "}, queryFields: {";

	auto queryFieldIter = mQueryFields.iterator();
	sep = "";

	while(queryFieldIter.hasNext()) {
		String fieldName, fieldValue;
		queryFieldIter.getNextKeyAndValue(fieldName, fieldValue);

		buf << sep << "\"" << fieldName << "\":\"" << fieldValue << "\"";
		sep = ", ";
	}

	buf << "}, requestJSON: " << mRequestJSON.dump();

	if (mReplied) {
		auto resultStr = String(mResult.serialize());

		if (resultStr.length() > 900) {
			resultStr = resultStr.subString(0, 900) + "...";
		}

		buf << " result: " << resultStr;
	}

	return buf.toString();
}

String APIRequest::toStringData() const {
	return toString();
}

bool APIRequest::stringToBool(const String& boolStr) const {
	return boolStr.toLowerCase() == "true" || boolStr == "1";
}

bool APIRequest::hasPathField(const String& fieldName) const {
	return mPathFields.containsKey(fieldName);
}

const String& APIRequest::getPathFieldString(const String& fieldName, bool required, const String& defaultValue) {
	if (!hasPathField(fieldName)) {
		if (!required) {
			return defaultValue;
		} else {
			auto msg = "Missing required path field [" + fieldName + "]";
			fail(msg);
			throw APIRequestException(msg);
		}
	}

	return mPathFields.get(fieldName);
}

uint64_t APIRequest::getPathFieldUnsignedLong(const String& fieldName, bool required, uint64_t defaultValue) {
	if (required) {
		return UnsignedLong::valueOf(getPathFieldString(fieldName, true));
	} else if (!hasPathField(fieldName)) {
		return defaultValue;
	}

	return UnsignedLong::valueOf(getPathFieldString(fieldName, false));
}

bool APIRequest::parseQueryFields() {
	try {
		const auto& uri = mGatewayRequest.relative_uri();

		auto query_vars = uri::split_query(uri.query());

		for (auto entry : query_vars) {
			mQueryFields.put(entry.first, uri::decode(entry.second));
		}

		return true;
	} catch (http_exception const & e) {
		fail("Exception parsing Query String", "parseQueryFields Exception: " + String(e.what()));
	}

	return false;
}

bool APIRequest::hasQueryField(const String& fieldName) const {
	return mQueryFields.containsKey(fieldName);
}

const String& APIRequest::getQueryFieldString(const String& fieldName, bool required, const String& defaultValue) {
	if (!hasQueryField(fieldName)) {
		if (!required) {
			return defaultValue;
		} else {
			auto msg = "Missing required query field [" + fieldName + "]";
			fail(msg);
			throw APIRequestException(msg);
		}
	}

	return mQueryFields.get(fieldName);
}

uint64_t APIRequest::getQueryFieldUnsignedLong(const String& fieldName, bool required, uint64_t defaultValue) {
	if (required) {
		return UnsignedLong::valueOf(getQueryFieldString(fieldName, true));
	} else if (!hasQueryField(fieldName)) {
		return defaultValue;
	}

	return UnsignedLong::valueOf(getQueryFieldString(fieldName, false));
}

bool APIRequest::getQueryFieldBool(const String& fieldName, bool required, bool defaultValue) {
	if (required) {
		return stringToBool(getQueryFieldString(fieldName, true));
	} else if (!hasQueryField(fieldName)) {
		return defaultValue;
	}

	return stringToBool(getQueryFieldString(fieldName, false));
}

bool APIRequest::parseRequestJSON(bool failOnError, bool failOnEmpty) {
	if (mParsedRequestJSON)
		return true;

	try {
		auto jvalue = mGatewayRequest.extract_json().get();

		if (jvalue.is_null() && failOnEmpty) {
			fail("Invalid or missing JSON body");
			return false;
		}

		// Marshal from cpprest native json to JSONSerializationType
		mRequestJSON = JSONSerializationType::parse(jvalue.serialize());
		mParsedRequestJSON = true;

		return true;
	} catch (http_exception const & e) {
		if (failOnError) {
			fail("Exception parsing JSON Body.", "parseBodyJSON Exception: " + String(e.what()));
		}
	}

	return false;
}

bool APIRequest::hasRequestField(const String& fieldName) const {
	if (!mParsedRequestJSON) {
		throw APIRequestException("hasRequestField called before parseRequestJSON");
	}

	return mRequestJSON.contains(fieldName.toCharArray());
}

const String APIRequest::getRequestFieldString(const String& fieldName, bool required, const String& defaultValue) {
	if (!hasRequestField(fieldName)) {
		if (!required) {
			return defaultValue;
		} else {
			auto msg = "Missing required request field [" + fieldName + "]";
			fail(msg);
			throw APIRequestException(msg);
		}
	}

	auto jvalue = mRequestJSON[fieldName];

	if (jvalue.is_string()) {
		return String(jvalue);
	} else {
		return String(jvalue.get<std::string>());
	}
}

uint64_t APIRequest::getRequestFieldUnsignedLong(const String& fieldName, bool required, uint64_t defaultValue) {
	if (!hasRequestField(fieldName)) {
		if (!required) {
			return defaultValue;
		} else {
			auto msg = "Missing required request field [" + fieldName + "]";
			fail(msg);
			throw APIRequestException(msg);
		}
	}

	auto jvalue = mRequestJSON[fieldName];

	if (jvalue.is_string()) {
		return UnsignedLong::valueOf(jvalue.get<std::string>());
	}

	return jvalue.get<uint64_t>();
}

bool APIRequest::getRequestFieldBool(const String& fieldName, bool required, bool defaultValue) {
	if (!hasRequestField(fieldName)) {
		if (!required) {
			return defaultValue;
		} else {
			auto msg = "Missing required request field [" + fieldName + "]";
			fail(msg);
			throw APIRequestException(msg);
		}
	}

	auto jvalue = mRequestJSON[fieldName];

	if (jvalue.is_string()) {
		return stringToBool(jvalue.get<std::string>());
	}

	return jvalue.get<bool>();
}

void APIRequest::reply(JSONSerializationType result, const String& status, APIRequestStatusValue status_code) {
	if (mReplied) {
		throw APIRequestException("Duplicate reply attempt: " + status);
	}

	mReplied = true;
	result["status"] = status;
	result["status_code"] = (APIRequestStatusValue)(status_code);

	if (!result.contains("debug")) {
		result["debug"] = JSONSerializationType::object();
		result["debug"]["req_time_ms"] = getElapsedTimeMS();
		result["trx_id"] = mTrxId;
	}

#if DEBUG_RESTAPI
	result["debug"]["endpoint_key"] = mEndpointKey;

	if (mParsedRequestJSON) {
		result["debug"]["request_fields"] = mRequestJSON;
	}

	auto pathFieldsJSON = JSONSerializationType::object();
	auto pathFieldIter = mPathFields.iterator();

	while(pathFieldIter.hasNext()) {
		String fieldName, fieldValue;
		pathFieldIter.getNextKeyAndValue(fieldName, fieldValue);
		pathFieldsJSON[fieldName] = fieldValue;
	}

	result["debug"]["path_fields"] = pathFieldsJSON;

	auto queryFieldsJSON = JSONSerializationType::object();
	auto queryFieldIter = mQueryFields.iterator();

	while(queryFieldIter.hasNext()) {
		String fieldName, fieldValue;
		queryFieldIter.getNextKeyAndValue(fieldName, fieldValue);
		queryFieldsJSON[fieldName] = fieldValue;
	}

	result["debug"]["query_fields"] = queryFieldsJSON;
#endif // DEBUG_RESTAPI

	http_response response(status_codes::Accepted);

	response.set_status_code(status_code);

	mResult = json::value::parse(result.dump());

	response.set_body(mResult);

#if DEBUG_RESTAPI
	debug() << "RESPONSE " << toString();
#endif // DEBUG_RESTAPI

	mGatewayRequest.reply(response);
}

void APIRequest::success(JSONSerializationType result, APIRequestStatusValue status_code) {
	mFailed = false;

	reply(result, "OK", status_code);
}

void APIRequest::fail(const String& userMessage, const String& logMessage, const APIRequestStatusValue status_code) {
	mFailed = true;

	error() << "FAILED Status=" << status_code << " - " << (logMessage.isEmpty() ? userMessage : logMessage);

	JSONSerializationType result;

	result["error_message"] = userMessage;

	reply(result, "ERROR", status_code);
}

#endif // WITH_REST_API
