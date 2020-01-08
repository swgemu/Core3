/*
                Copyright <SWGEmu>
        See file COPYING for copying conditions.*/

/**
 * @author      : lordkator (lordkator@swgemu.com)
 * @file        : BaseAPIProxy.h
 * @created     : Sun Jan  5 13:11:39 UTC 2020
 */

#pragma once

#include "engine/engine.h"
#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"

namespace server {
 namespace web3 {
	class BaseAPIProxy {
		private:
			String mManagerName;

		public:
			BaseAPIProxy(const String& managerName) {
				mManagerName = managerName;
			}

			static server::zone::ZoneServer* getZoneServer() {
				return ServerCore::getZoneServer();
			}
	};
 }
}
