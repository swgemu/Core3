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

#ifndef TICKETCOLLECTORIMPLEMENTATION_H_
#define TICKETCOLLECTORIMPLEMENTATION_H_

#include "../Inventory.h"

#include "../ticket/Ticket.h"

#include "../../creature/shuttle/ShuttleCreature.h"

#include "TicketCollector.h"

class TicketCollectorImplementation : public TicketCollectorServant {
	ShuttleCreature* shuttle;
	
public:
	TicketCollectorImplementation(ShuttleCreature* shutle, uint64 objid, const unicode& n, const string& tempn, float x, float z, float y) 
			: TicketCollectorServant(objid, TERMINAL) {
		objectCRC = 0xFCF0B40D;

		name = n;
		
		templateTypeName = "terminal_name";
		templateName = tempn;

		initializePosition(x , z, y);
		
		shuttle = shutle;
	}
	
	int useObject(Player* player) {
		// Pre: player unlocked
		player->wlock();
		
		if (player->isInCombat()) {
			player->unlock();
			return 0;
		}
		
		if (!checkTime(shuttle, player)) {
			player->unlock();
			return 0;	
		}
			
		string city = shuttle->getCity();
		string planet = shuttle->getPlanet();
			
		Inventory* inventory = player->getInventory();
		
		for (int i = 0; i < inventory->objectsSize(); ++i) {
			SceneObject* obj = inventory->getObject(i);
			
			if (!obj->isTangible())
				continue;
			
			TangibleObject* item = (TangibleObject*) obj;

			if (item->isTicket()) {
				Ticket* ticket = (Ticket*)item;
				
				if ((ticket->getDeparturePoint() == city) &&  (ticket->getDeparturePlanet() == planet)) {
					player->removeInventoryItem(item->getObjectID());
					
					shuttle->sendPlayerTo(player, ticket->getArrivalPoint());
														
					//delete ticket;
					
					player->unlock();
					return 1;
				}
			}
		}
		
		player->unlock();
		
		player->sendSystemMessage("You do not have a ticket to board this shuttle.");
		return 0;
	}
	
	bool checkTime(ShuttleCreature* shuttle, Player* player) {
		int landTime = shuttle->getArrivalTime();
			
		if (landTime > 0) {
			int min = landTime / 60;
			int seconds = (landTime % 60);
								
			stringstream arrivalTime;
			arrivalTime << "The next shuttle will be ready to board in " << min << " minutes and " << seconds << " seconds";
			player->sendSystemMessage(arrivalTime.str());

			return false;
		} else if (landTime > -20) {
			stringstream arrivalTime;
			arrivalTime << "The next shuttle is about to begin boarding";
			player->sendSystemMessage(arrivalTime.str());

			return false;
		}

		return true;
	}
	
};

#endif /*TICKETCOLLECTOR_H_*/
