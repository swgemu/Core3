/*
 * MessageData.h
 *
 *  Created on: 21/07/2009
 *      Author: TheAnswer
 */

#ifndef MESSAGECALLBACK_H_
#define MESSAGECALLBACK_H_

#include "engine/engine.h"
#include "../ZoneClientSession.h"

namespace server {
namespace zone {
	class ZoneProcessServerImplementation;

namespace packets {

	class MessageCallback {
	protected:
		ReferenceSlot<ZoneClientSession*> client;
		ZoneProcessServerImplementation* server;

	public:
		MessageCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) {
			MessageCallback::client = client;
			MessageCallback::server = server;
		}

		virtual ~MessageCallback() {

		}

		virtual void parse(Message* message) = 0;

		virtual void execute() = 0;

		inline ZoneClientSession* getClient() {
			return client.get();
		}

		inline ZoneProcessServerImplementation* getServer() {
			return server;
		}
	};

}
}
}

using namespace server::zone::packets;


#endif /* MESSAGECALLBACK_H_ */
