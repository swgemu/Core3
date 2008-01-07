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

#include "../../ZoneClient.h"
#include "../creature/CreatureObject.h"

#include "../player/Player.h"
#include "../scene/SceneObjectImplementation.h"

#include "../../Zone.h"

#include "../../packets.h"

#include "TangibleObjectImplementation.h"

#include "../building/BuildingObject.h"
#include "../building/cell/CellObject.h"


TangibleObjectImplementation::TangibleObjectImplementation(uint64 oid, int tp) 
		: TangibleObjectServant(oid) {
	initialize();
	
	objectSubType = tp;
	
	pvpStatusBitmask = 0;
}

TangibleObjectImplementation::TangibleObjectImplementation(uint64 oid, const unicode& n, const string& tempname, uint32 tempCRC, int tp) 
		: TangibleObjectServant(oid) {
	initialize();
	
	objectCRC = tempCRC;
	
	name = n;

	objectSubType = tp;
	
	pvpStatusBitmask = 0;
}

TangibleObjectImplementation::TangibleObjectImplementation(CreatureObject* creature, const unicode& n, const string& tempname, uint32 tempCRC, int tp) 
		: TangibleObjectServant() {
	initialize();
	
	name = n;
	
	objectCRC = tempCRC;
	objectID = creature->getNewItemID();

	objectSubType = tp;
}

void TangibleObjectImplementation::initialize() { 
	container = NULL;
	zone = NULL;
	
	persistent = false;
	updated = false;
	
	building = NULL;

	objectCount = 0;
	
	conditionDamage = 0;
	maxCondition = 6000;
	
	objectType = SceneObjectImplementation::TANGIBLE;
	
	equipped = false;
	
	pvpStatusBitmask = 0;
}

void TangibleObjectImplementation::insertToZone(Zone* zone) {
	TangibleObjectImplementation::zone = zone;
	
	/*if (container != NULL) {
		if (container->isCell())
			building = (BuildingObject*) container->getParent();
	}*/

	try {
		zone->lock();
		
		zone->registerObject((TangibleObject*) _this);
	
		zone->insert(this);
		zone->inRange(this, 128);
		
		zone->unlock();
	} catch (...) {
		cout << "exception TangibleObject::insertToZone(Zone* zone)\n";

		zone->unlock();
	}
}

void TangibleObjectImplementation::removeFromZone() {
	if (zone == NULL)
		return;
	
	try {
		zone->lock();

    	for (int i = 0; i < inRangeObjectCount(); ++i) {
			QuadTreeEntry* obj = getInRangeObject(i);
			
			if (obj != this)
				obj->removeInRangeObject(this);
		}

		removeInRangeObjects();

		zone->remove(this);
		zone->deleteObject(objectID);
		
		zone->unlock();
		
		zone = NULL;
	} catch (...) {
		cout << "exception TangibleObject::removeFromZone(bool doLock)\n";

		zone->unlock();
	}
}

void TangibleObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (container != NULL)
		link(client, container);

	Message* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);

	Message* tano6 = new TangibleObjectMessage6((TangibleObject*) _this);
	client->sendMessage(tano6);
	
	if (pvpStatusBitmask != 0) {
		UpdatePVPStatusMessage* msg = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);
		client->sendMessage(tano6);
	}

	if (doClose)
		SceneObjectImplementation::close(client);
	
}

void TangibleObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;
	
	destroy(client);
}

void TangibleObjectImplementation::close(Player* player) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::close(client);
}


void TangibleObjectImplementation::repairItem(Player* player) {
	int roll = System::random(100);
	int decayRate = 100;
	stringstream txt;
	
	txt << "The repair was ";
	if (roll < 10) {
		txt << "a critical failure!";
		decayRate = 75;
	}
	else if (roll < 20) {
		txt << "a failure.";
		decayRate = 50;					
	}
	else if (roll < 80) {
		txt << "a success.";
		decayRate = 20;					
	}
	else {
		txt << "an amazing success.";
		decayRate = 5;					
	}				
	player->sendSystemMessage(txt.str());

	maxCondition = (maxCondition - (maxCondition/100*decayRate));
	conditionDamage = 0;
	updated = 1;

	sendTo(player);
	
}

void TangibleObjectImplementation::decay(int decayRate) {
	conditionDamage = conditionDamage + (maxCondition/100*decayRate);

	if (conditionDamage > maxCondition)
		conditionDamage = maxCondition;
	
	updated = 1;
	
}
