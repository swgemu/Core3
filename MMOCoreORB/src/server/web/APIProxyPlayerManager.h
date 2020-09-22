/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyPlayerManager.h
 * @created     : Sun Jan  5 11:26:18 UTC 2020
 */

#pragma once

#include "BaseAPIProxy.h"

namespace server {
 namespace web3 {
	class APIRequest;

	class APIProxyPlayerManager : public BaseAPIProxy {
	public:
		APIProxyPlayerManager() : BaseAPIProxy("PlayerManager")  {
		}

		server::zone::managers::player::PlayerManager* getPlayerManager();
		void handle(APIRequest& apiRequest);
		void lookupCharacter(APIRequest& apiRequest);
	};
 }
}
