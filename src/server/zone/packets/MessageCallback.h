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

#include "server/zone/ZoneProcessServerImplementation.h"

namespace server {
namespace zone {
namespace packets {

	class MessageCallback : public Task {
	protected:
		Reference<ZoneClientSession*> client;

		ZoneProcessServerImplementation* server;

	public:
		MessageCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) {
			MessageCallback::client = client;
			MessageCallback::server = server;
		}

		virtual ~MessageCallback() {

		}

		virtual void parse(Message* message) = 0;

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
