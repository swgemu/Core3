/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyGuildManager.h
 * @created     : Sun Apr 12 12:39:01 UTC 2020
 */

#pragma once

#include "BaseAPIProxy.h"

namespace server {
 namespace web3 {
	class APIRequest;

	class APIProxyGuildManager : public BaseAPIProxy {
	public:
		APIProxyGuildManager() : BaseAPIProxy("PlayerManager")  {
		}

		server::zone::managers::guild::GuildManager* getGuildManager();
		void handle(APIRequest& apiRequest);
		void lookupGuild(APIRequest& apiRequest);
	};
 }
}
