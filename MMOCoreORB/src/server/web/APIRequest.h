/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIRequest.h
 * @created     : Sun Jan  5 11:26:18 UTC 2020
 */

#pragma once

#include "RESTServer.h"
#include "APIRequestStatus.h"

#include <cpprest/http_listener.h>
#include <cpprest/json.h>

namespace server {
 namespace web3 {
	class APIRequestException : public Exception {
	public:
		APIRequestException(const String& msg) : Exception(msg) {
		}
	};

	using namespace web;
	using namespace web::http;

	class APIRequest : public Logger {
	private:
		Time mStartTime;
		String mTrxId;
		http_request mGatewayRequest;
		String mEndpointKey;
		HashTable<String, String> mPathFields;
		HashTable<String, String> mQueryFields;
		JSONSerializationType mRequestJSON;
		json::value mResult;

		bool mReplied;
		bool mFailed;
		bool mParsedRequestJSON;

		bool parseQueryFields();
		void reply(JSONSerializationType result, const String& status, APIRequestStatusValue status_code);
		bool stringToBool(const String& boolStr) const;

	public:
		APIRequest(http_request gatewayRequest, const String endpointKey, Logger& logger);
		~APIRequest();

		String toString() const;
		String toStringData() const;

		inline bool isMethodGET() const {
			return mGatewayRequest.method() == "GET";
		}

		inline bool isMethodPUT() const {
			return mGatewayRequest.method() == "PUT";
		}

		inline bool isMethodPOST() const {
			return mGatewayRequest.method() == "POST";
		}

		inline bool isMethodDELETE() const {
			return mGatewayRequest.method() == "DELETE";
		}

		inline void setPathFields(HashTable<String, String> pathFields) {
			mPathFields = pathFields;
		}

		inline const HashTable<String, String>& getPathFields() const {
			return mPathFields;
		}

		inline const HashTable<String, String>& getQueryFields() const {
			return mQueryFields;
		}

		inline const String& getEndpointKey() const {
			return mEndpointKey;
		}

		inline const String& getTrxId() const {
			return mTrxId;
		}

		inline const JSONSerializationType& getRequestJSON() const {
			return mRequestJSON;
		}

		inline int64 getElapsedTimeMS() const {
			return mStartTime.miliDifference();
		}

		bool hasPathField(const String& fieldName) const;
		const String& getPathFieldString(const String& fieldName, bool required=true, const String& defaultValue="");
		uint64_t getPathFieldUnsignedLong(const String& fieldName, bool required=true, uint64_t defaultValue=0);

		bool hasQueryField(const String& fieldName) const;
		const String& getQueryFieldString(const String& fieldName, bool required=true, const String& defaultValue="");
		uint64_t getQueryFieldUnsignedLong(const String& fieldName, bool required=true, uint64_t defaultValue=0);
		bool getQueryFieldBool(const String& fieldName, bool required=true, bool defaultValue=false);

		bool parseRequestJSON(bool failOnError=true, bool failOnEmpty=true);
		bool hasRequestField(const String& fieldName) const;
		const String getRequestFieldString(const String& fieldName, bool required=true, const String& defaultValue="");
		uint64_t getRequestFieldUnsignedLong(const String& fieldName, bool required=true, uint64_t defaultValue=0);
		bool getRequestFieldBool(const String& fieldName, bool required=true, bool defaultValue=false);

		void success(JSONSerializationType result, APIRequestStatusValue status_code=APIRequestStatus::OK);
		void fail(const String& userMessage, const String& logMessage="", const APIRequestStatusValue status_code=APIRequestStatus::BadRequest);
	};
 }
}
