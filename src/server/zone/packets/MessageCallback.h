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

#include "server/zone/ZoneProcessServer.h"

namespace server {
namespace zone {
namespace packets {

	class MessageCallback : public Task, Logger {
	protected:
		Reference<ZoneClientSession*> client;

		ManagedReference<ZoneProcessServer*> server;

	public:
		MessageCallback(ZoneClientSession* client, ZoneProcessServer* server) {
			MessageCallback::client = client;
			MessageCallback::server = server;

			setLoggingName("MessageCallback");
		}

		virtual ~MessageCallback() {
		}

		virtual void parse(Message* message) = 0;

		bool parseMessage(Message* packet) {
			try {

				parse(packet);

			} catch (Exception& e) {
				error("exception while parsing message in ZonePacketHandler");
				error(e.getMessage());
				e.printStackTrace();

				return false;
			}

			return true;
		}

		inline ZoneClientSession* getClient() {
			return client.get();
		}

		inline ZoneProcessServer* getServer() {
			return server;
		}

	};

}
}
}

using namespace server::zone::packets;


#endif /* MESSAGECALLBACK_H_ */
