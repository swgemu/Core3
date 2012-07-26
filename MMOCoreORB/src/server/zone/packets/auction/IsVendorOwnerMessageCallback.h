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
		String vendorRegion = zone->getZoneName();


		ManagedReference<CityRegion*> cityRegion = sceno->getCityRegion();
		if(cityRegion != NULL)
			vendorRegion = cityRegion->getRegionName();


		IsVendorOwnerResponseMessage* msg = new IsVendorOwnerResponseMessage(sceno, player, planetString, vendorRegion);
		client->sendMessage(msg);

	}
};


#endif /* ISVENDOROWNERMESSAGECALLBACK_H_ */
