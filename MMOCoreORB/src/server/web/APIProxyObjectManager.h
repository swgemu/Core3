/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyObjectManager.h
 * @created     : Sat Apr 11 10:30:48 UTC 2020
 */

#pragma once

#include "BaseAPIProxy.h"

namespace server {
 namespace web3 {
	class APIRequest;

	class APIProxyObjectManager : public BaseAPIProxy {
	public:
		APIProxyObjectManager() : BaseAPIProxy("Object")  {
		}

		void handle(APIRequest& apiRequest);
	private:
		void handleGET(APIRequest& apiRequest);
		void handlePUT(APIRequest& apiRequest);
		void handleDELETE(APIRequest& apiRequest);
		int writeObjectJSON(uint64 oid, bool recursive, bool parents, JSONSerializationType& objects, int maxDepth);
		int deleteObject(APIRequest& apiRequest, uint64 oid, bool refundADK, String& resultMessage);
		bool updateObject(APIRequest& apiRequest, uint64 oid, String& resultMessage);
		String exportJSON(ManagedObject* obj, const String& exportNote);
	};
 }
}
