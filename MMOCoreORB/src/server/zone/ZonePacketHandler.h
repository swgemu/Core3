/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ZONEPACKETHANDLER_H_
#define ZONEPACKETHANDLER_H_

#include "engine/engine.h"
#include "MessageCallbackFactory.h"

#include "packets/MessageCallback.h"
#include "packets/object/ObjectControllerMessageCallback.h"

namespace server {
namespace zone {

	class ZoneClientSession;
	class ZoneProcessServer;
	class ZoneServer;

	class ZonePacketHandler : public Logger, public Object {
		Reference<ZoneProcessServer*> processServer;

		Reference<ZoneServer*> server;

		MessageCallbackFactory<MessageCallback* (ZoneClientSession*, ZoneProcessServer*), uint32> messageCallbackFactory;

	public:
		ZonePacketHandler();
		ZonePacketHandler(const String& s, ZoneProcessServer* serv);

		~ZonePacketHandler();

		void registerMessages();
		void registerObjectControllerMessages();

		Task* generateMessageTask(ZoneClientSession* client, Message* pack) const;
	};

	}
}

using namespace server::zone;

#endif /*ZONEPACKETHANDLER_H_*/
