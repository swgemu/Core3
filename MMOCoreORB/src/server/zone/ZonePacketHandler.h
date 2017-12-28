/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONEPACKETHANDLER_H_
#define ZONEPACKETHANDLER_H_

#include <stddef.h>

#include "MessageCallbackFactory.h"
#include "engine/core/ManagedReference.h"
#include "engine/engine.h"
#include "engine/log/Logger.h"
#include "packets/MessageCallback.h"
#include "packets/object/ObjectControllerMessageCallback.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "system/lang/Object.h"
#include "system/lang/String.h"
#include "system/platform.h"

namespace engine {
namespace core {
class Task;
}  // namespace core
namespace service {
class Message;
}  // namespace service
}  // namespace engine

namespace server {
namespace zone {

	class ZoneClientSession;
	class ZoneProcessServer;
	class ZoneServer;
namespace packets {
class MessageCallback;
}  // namespace packets

	class ZonePacketHandler : public Logger, public Object {
		ManagedReference<ZoneProcessServer*> processServer;

		ManagedReference<ZoneServer*> server;

		MessageCallbackFactory<MessageCallback* (ZoneClientSession*, ZoneProcessServer*), uint32> messageCallbackFactory;

	public:
		ZonePacketHandler() : Logger() {
			server = NULL;
		}

		ZonePacketHandler(const String& s, ZoneProcessServer* serv);

		~ZonePacketHandler() {
			delete ObjectControllerMessageCallback::objectMessageControllerFactory;
		}

		void registerMessages();
		void registerObjectControllerMessages();

		Task* generateMessageTask(ZoneClientSession* client, Message* pack);
	};

	}
}

using namespace server::zone;

#endif /*ZONEPACKETHANDLER_H_*/
