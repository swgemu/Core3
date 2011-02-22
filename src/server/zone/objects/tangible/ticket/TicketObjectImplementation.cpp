/*
 * TicketObjectImplementation.cpp
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#include "TicketObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/Zone.h"

void TicketObjectImplementation::fillAttributeList(AttributeListMessage* alm, PlayerCreature* object) {
	alm->insertAttribute("travel_departure_planet", "@planet_n:" + departurePlanet);
	alm->insertAttribute("travel_departure_point", departurePoint);
	alm->insertAttribute("travel_arrival_planet", "@planet_n:" + arrivalPlanet);
	alm->insertAttribute("travel_arrival_point", arrivalPoint);
}


int TicketObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	//Pre player wlocked

	if (selectedID != 20)
		return 0;

	Zone* zone = player->getZone();
	if (zone == NULL)
		return 0;

	try {
		zone->rlock();

		int size = player->inRangeObjectCount();

		for (int i = 0; i < size; ++i) {
			SceneObject* object = (SceneObject*) player->getInRangeObject(i);

			if (object->isTangibleObject()) {
				TangibleObject* tano = (TangibleObject*) object;

				if (tano->isTicketCollector() && player->isInRange(tano, 5)) {
					zone->runlock();

					try {
						TicketCollector* col = (TicketCollector*) tano;
						col->useTicket(player, _this);
					} catch (Exception& e) {
						error(e.getMessage());
						e.printStackTrace();
					}

					return 1;
				}
			}
		}

		zone->runlock();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		zone->runlock();
	} catch (...) {
		zone->runlock();

		error("unreported exception in int TicketImplementation::useObject(Player* player)");

		throw;
	}

	player->sendSystemMessage("travel", "boarding_too_far");

	return 0;
}

