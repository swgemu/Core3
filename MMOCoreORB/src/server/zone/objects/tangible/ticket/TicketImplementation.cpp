/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "TicketImplementation.h"

#include "../../player/Player.h"
#include "../../../packets/scene/AttributeListMessage.h"

#include "../ticketcollector/TicketCollector.h"

#include "../../../Zone.h"

TicketImplementation::TicketImplementation(Player* player, uint32 tempCRC,
		const UnicodeString& n, const String& tempn, const String& dpPlanet,
		const String& dpPoint, const String& arPlanet, const String& arPoint)
			: TicketServant(player->getNewItemID(), TRAVELTICKET) {
	objectCRC = tempCRC;

	customName = n;

	departurePlanet = dpPlanet;
	departurePoint = dpPoint;
	arrivalPlanet = arPlanet;
	arrivalPoint = arPoint;

	//Replace Underscores with spaces
	departurePoint = departurePoint.replaceAll("_", " ");
	arrivalPoint = arrivalPoint.replaceAll("_", " ");

	itemAttributes->setStringAttribute("departurePlanet", departurePlanet);
	itemAttributes->setStringAttribute("departurePoint", departurePoint);

	itemAttributes->setStringAttribute("arrivalPlanet", arrivalPlanet);
	itemAttributes->setStringAttribute("arrivalPoint", arrivalPoint);

	templateTypeName = "wearables_name";
	templateName = tempn;

	ply = player;

	setParent((TangibleObject*) player->getInventory(), 0xFFFFFFFF);

	setLogging(false);
	setGlobalLogging(true);
}

TicketImplementation::TicketImplementation(uint64 objectid, uint32 tempCRC, const UnicodeString& n, const String& tempn) :
	TicketServant(objectid, TRAVELTICKET) {

	objectCRC = tempCRC;

	customName = n;
	templateTypeName = "wearables_name";
	templateName = tempn;

}

void TicketImplementation::parseItemAttributes() {
	departurePlanet = itemAttributes->getStringAttribute("departurePlanet");
	departurePoint = itemAttributes->getStringAttribute("departurePoint");

	arrivalPlanet = itemAttributes->getStringAttribute("arrivalPlanet");
	arrivalPoint = itemAttributes->getStringAttribute("arrivalPoint");
}

void TicketImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* tattr = new AttributeListMessage(_this);

	addAttributes(tattr);
	player->sendMessage(tattr);
}

int TicketImplementation::useObject(Player* player) {
	//Pre player wlocked

	Zone* zone = player->getZone();
	if (zone == NULL)
		return 0;

	try {
		zone->lock();

		int size = player->inRangeObjectCount();

		for (int i = 0; i < size; ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) player->getInRangeObject(i))->_getStub());

			if (object->isTangible()) {
				TangibleObject* tano = (TangibleObject*) object;

				if (tano->isTicketCollector() && player->isInRange(tano, 5)) {
					zone->unlock();

					try {
						TicketCollector* col = (TicketCollector*) tano;
						col->useTicket(player, _this);
					} catch (Exception& e) {
						error(e.getMessage());
						e.printStackTrace();
					} catch (...) {
						error("unreported exception in int TicketImplementation::useObject(Player* player)");
					}

					return 1;
				}
			}
		}

		zone->unlock();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();

		zone->unlock();
	} catch (...) {
		zone->unlock();
		error("unreported exception in int TicketImplementation::useObject(Player* player)");
	}

	player->sendSystemMessage("travel", "boarding_too_far");

	return 0;
}

void TicketImplementation::addAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("travel_departure_planet", getDeparturePlanet());
	alm->insertAttribute("travel_departure_point", getDeparturePoint());
	alm->insertAttribute("travel_arrival_planet", getArrivalPlanet());
	alm->insertAttribute("travel_arrival_point", getArrivalPoint());
}
