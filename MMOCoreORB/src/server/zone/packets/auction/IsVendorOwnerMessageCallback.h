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
#include "server/zone/objects/region/CityRegion.h"

#include "server/zone/Zone.h"

class IsVendorOwnerMessageCallback : public MessageCallback {
	uint64 oid;

public:
	IsVendorOwnerMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

		oid = 0;
	}

	void parse(Message* message) {
		oid = message->parseLong();
	}

	void run() {
		ManagedReference<SceneObject*> sceno = server->getZoneServer()->getObject(oid);

		if (sceno == NULL)
			return;

		Zone* zone = sceno->getZone();

		if (zone == NULL)
			return;

		CreatureObject* player = cast<CreatureObject*>( client->getPlayer().get().get());

		if (player == NULL)
			return;

		String planetString = zone->getZoneName();
		String vendorRegion = ""; // TODO: Vendors don't have regions impl yet.

		//TODO: Relook at this! - POLONEL
		if (sceno->isTerminal() && (cast<Terminal*>(sceno.get()))->isBazaarTerminal()) {
			ManagedReference<CityRegion*> cityRegion = sceno->getCityRegion();

			if (cityRegion == NULL) {
				sceno->error("NULL AREA FOR THIS TERMINAL");

				vendorRegion = "";
				//return;
			} else
				vendorRegion = cityRegion->getRegionName();

		}

		IsVendorOwnerResponseMessage* msg = new IsVendorOwnerResponseMessage(sceno, player, planetString, vendorRegion, 0);
		client->sendMessage(msg);

	}
};


#endif /* ISVENDOROWNERMESSAGECALLBACK_H_ */
