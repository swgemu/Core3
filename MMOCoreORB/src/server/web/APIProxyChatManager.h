/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : APIProxyChatManager.h
 * @created     : Sun Mar  8 19:03:07 UTC 2020
 */

#pragma once

#include "BaseAPIProxy.h"

namespace server {
 namespace web3 {
	class APIRequest;

	class APIProxyChatManager : public BaseAPIProxy {
	public:
		APIProxyChatManager() : BaseAPIProxy("ChatManager")  {
		}

		server::chat::ChatManager *getChatManager() const;
		void handle(APIRequest& apiRequest);
	private:
		String expandTo(String toExpr, Function<String(String playerName)> process, bool skipOffline = true) const;
	};
 }
}
