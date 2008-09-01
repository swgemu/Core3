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

#include "TicketCollectorImplementation.h"

#include "../Inventory.h"

#include "../ticket/Ticket.h"

#include "../../creature/shuttle/ShuttleCreature.h"
#include "../../player/sui/listbox/SuiListBoxImplementation.h"

#include "../../../Zone.h"
#include "../../../managers/item/ItemManager.h"

#include "../../../packets.h"

TicketCollectorImplementation::TicketCollectorImplementation(ShuttleCreature* shutle, uint64 objid, const unicode& n,
		const string& tempn, float x, float z, float y) :
	TicketCollectorServant(objid, TICKETCOLLECTOR) {
	objectCRC = 0xFCF0B40D;

	name = n;

	templateTypeName = "terminal_name";
	templateName = tempn;

	initializePosition(x, z, y);

	shuttle = shutle;

	stringstream loggingname;
	loggingname << "TicketCollector = 0x" << objid;
	setLoggingName(loggingname.str());

	setLogging(false);
	setGlobalLogging(true);
}

int TicketCollectorImplementation::useObject(Player* player) {
	// Pre: player wlocked
	// Post: player wlocked
	if (player->isMounted()) {
		player->sendSystemMessage("travel", "no_pets");
		return 0;
	}

	if (player->isInCombat())
		return 0;

	if (!checkTime(shuttle, player))
		return 0;

	string city = shuttle->getCity();
	string planet = shuttle->getPlanet();

	Inventory* inventory = player->getInventory();

	SuiListBox* sui = new SuiListBox(player, 0xAFAF);
	sui->setPromptTitle("@travel:ticket_collector_name");
	sui->setPromptText("@travel:boarding_ticket_selection");
	sui->setCancelButton(true);

	for (int i = 0; i < inventory->objectsSize(); ++i) {
		SceneObject* obj = inventory->getObject(i);

		if (!obj->isTangible())
			continue;

		TangibleObject* item = (TangibleObject*) obj;

		if (item->isTicket()) {
			Ticket* ticket = (Ticket*) item;

			if (ticket->getDeparturePoint() == shuttle->getCity()) {
				stringstream line;
				line << ticket->getArrivalPlanet() << " - " << ticket->getArrivalPoint();

				sui->addMenuItem(line.str(), ticket->getObjectID());
			}
		}
	}

	if (sui->getMenuSize() == 0) {
		sui->finalize();

		player->sendSystemMessage("travel", "no_ticket");
	} else {
		player->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());
	}

	return 0;
}

bool TicketCollectorImplementation::checkTime(ShuttleCreature* shuttle, Player* player) {
	int landTime = shuttle->getArrivalTime();

	if (landTime > 0) {
		int min = landTime / 60;
		int seconds = (landTime % 60);

		if (min > 0) {
			stringstream arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << min << " minutes and " << seconds << " seconds";
			player->sendSystemMessage(arrivalTime.str());
		} else {
			stringstream arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << seconds << " seconds";
			player->sendSystemMessage(arrivalTime.str());

		}

		return false;
	} else if (landTime > -20) {
		stringstream arrivalTime;
		arrivalTime << "The next shuttle is about to begin boarding";
		player->sendSystemMessage(arrivalTime.str());

		return false;
	}

	return true;
}

void TicketCollectorImplementation::useTicket(Player* player, Ticket* ticket) {
	// Pre: player wlocked
	// Post: player wlocked
	if (player->isMounted()) {
		player->sendSystemMessage("travel", "no_pets");
		return;
	}

	if (player->isInCombat())
		return;

	if (!checkTime(shuttle, player))
		return;

	string city = shuttle->getCity();
	string planet = shuttle->getPlanet();

	if ((ticket->getDeparturePoint() == city) &&  (ticket->getDeparturePlanet() == planet)) {
		player->removeInventoryItem(ticket->getObjectID());

		Zone* zone = player->getZone();

		if (zone != NULL) {
			ZoneServer* zoneServer = zone->getZoneServer();

			ItemManager* itemManager;
			if (zoneServer != NULL && ((itemManager = zoneServer->getItemManager()) != NULL)) {

				itemManager->deletePlayerItem(player, ticket, false);
			}
		}

		shuttle->sendPlayerTo(player, ticket);

		ticket->finalize();
		return;
	}

	player->sendSystemMessage("travel", "wrong_shuttle");
	return;
}
