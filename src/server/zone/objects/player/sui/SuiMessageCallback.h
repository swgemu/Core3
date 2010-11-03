/*
 * SuiMessageCallback.h
 *
 *  Created on: Nov 3, 2010
 *      Author: crush
 */

#ifndef SUIMESSAGECALLBACK_H_
#define SUIMESSAGECALLBACK_H_

#include "server/zone/packets/MessageCallback.h"

namespace server {
namespace zone {
namespace objects {
namespace player {

	class PlayerCreature;

namespace sui {

	class SuiBox;

	class SuiMessageCallback : public MessageCallback {
	public:
		SuiMessageCallback(ZoneClientSession* client, ZoneProcessServer* server)
			: MessageCallback(client, server) {
		}

		void parse(Message* message) {

		}

		void run() {

		}

		/**
		 * @param player The player that this suibox is assigned to.
		 * @param suiBox The actual SuiBox object.
		 * @param cancelPressed Was the cancel button pressed, or was the sui box closed via a similar method. (this might actually be more of a dialogResult type variable)
		 * @param args A vector of UnicodeStrings containing the arguments passed to the sui box from the client.
		 */
		virtual void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) = 0;
	};

}
}
}
}
}

using namespace server::zone::objects::player::sui;

#endif /* SUIMESSAGECALLBACK_H_ */
