/*
 * IsVendorOwnerMessageCallback.h
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#ifndef ISVENDOROWNERMESSAGECALLBACK_H_
#define ISVENDOROWNERMESSAGECALLBACK_H_

#include "../MessageCallback.h"

#include "IsVendorOwnerResponseMessage.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.h"

#include "server/zone/Zone.h"

class IsVendorOwnerMessageCallback : public MessageCallback {
	uint64 oid;

public:
	IsVendorOwnerMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

		oid = 0;
	}

	void parse(Message* message) {
		//characterID = message->parseLong(6);
		//System::out << message->toStringData() << endl;
		oid = message->parseLong();
	}

	void run() {
		ManagedReference<SceneObject*> bazaar = server->getZoneServer()->getObject(oid);

		if (bazaar == NULL)
			return;

		Zone* zone = bazaar->getZone();

		if (zone == NULL)
			return;

		if (bazaar->isBazaarTerminal()) {
			ActiveArea* area = bazaar->getActiveRegion();

			if (area == NULL) {
				bazaar->error("NULL AREA FOR THIS BAZAAR");

				return;
			}

			String bazaarRegion = area->getObjectName()->getStringID();
			//String bazaarRegion = ((BazaarTerminal*) bazaar.get())->getBazaarRegion();
			String planetString = Planet::getPlanetName(zone->getZoneID());

			//client->getPlayer()->info(String("sending for bazaar region ") + bazaarRegion, true);
			IsVendorOwnerResponseMessage* msg = new IsVendorOwnerResponseMessage(false, oid, planetString, bazaarRegion, 0, 0);
			client->sendMessage(msg);
		}
	}
};


#endif /* ISVENDOROWNERMESSAGECALLBACK_H_ */
