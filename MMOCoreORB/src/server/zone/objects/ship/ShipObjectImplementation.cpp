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

#include "../../Zone.h"
#include "../../ZoneClient.h"

#include "../creature/CreatureObject.h"
#include "../creature/CreatureObjectImplementation.h"

#include "../../packets.h"
#include "../../objects.h"

#include "ShipObject.h"
#include "ShipObjectImplementation.h"


ShipObjectImplementation::ShipObjectImplementation(uint64 oid, Player* SOwner) : ShipObjectServant(oid, SHIP) {
	owner = SOwner;

	objectType = SceneObjectImplementation::SHIP;

	init();
}

ShipObjectImplementation::~ShipObjectImplementation() {
}

void ShipObjectImplementation::init() {
	shipBody = NULL; //note to self: let the ShipManager take care of the ship ITNO

	stfName = "";
	ownerName = owner->getCharacterName();

	activeComponentListSize = 0;

	//SHIP1
	unkShip1UpdateCnt = 0;
	unkShip1UpdateCnt2 = 0;
	energyDrainUpdateCnt = 0;
	compMassUpdateCnt = 0;
	unkShip1UpdateCnt3 = 0;
	shieldChargeRate = 0.0f;
	capacitorChargeRate = 0.0f;
	totalEnergy = 0.0f;

	//SHIP3
	chassisCur = 0.0f;
	chassisMax = 0.0f;
	curArmorUpdateCnt = 0;
	maxArmorUpdateCnt = 0;
	curHitpointsUpdateCnt = 0;
	maxHitpointsUpdateCnt = 0;
	//unkUpdateCnt = 0;
	frontshieldMax = 0.0f;
	backshieldMax = 0.0f;

	//SHIP4
	totalMass = 0.0f;

	//SHIP6
	crcUpdateCnt = 0;
	maxSpeed = 45.0f; //450 top speed for testing
	frontshieldCur = 0.0f;
	backshieldCur = 0.0f;

}

void ShipObjectImplementation::sendToOwner(bool inSpace) {
	ZoneClient* client = owner->getClient();

	create(client);

	if(inSpace)
		link(client, owner);

	BaseMessage* ship3 = new ShipObjectMessage3((ShipObject*) _this);
	client->sendMessage(ship3);

	BaseMessage* ship6 = new ShipObjectMessage6((ShipObject*) _this);
	client->sendMessage(ship6);

	BaseMessage* ship1 = new ShipObjectMessage1((ShipObject*) _this);
	client->sendMessage(ship1);

	BaseMessage* ship4 = new ShipObjectMessage4((ShipObject*) _this);
	client->sendMessage(ship4);

	close(client);
}

void ShipObjectImplementation::sendTo(Player* targetPlayer, bool inSpace, bool doClose) {
	ZoneClient* client = targetPlayer->getClient();
	if (client == NULL)
		return;

	create(client);

	if(inSpace)
		link(client, owner);

	BaseMessage* ship3 = new ShipObjectMessage3((ShipObject*) _this);
	client->sendMessage(ship3);

	BaseMessage* ship6 = new ShipObjectMessage6((ShipObject*) _this);
	client->sendMessage(ship6);

	if (doClose)
		close(client);
}

void ShipObjectImplementation::addComponent(ShipComponent* tsc) {
	componentList.add(tsc);
	calcActiveComponentListSize();
}

void ShipObjectImplementation::removeComponent(int compId) {
	//componentList.get(compId)->unload();
	calcActiveComponentListSize();
}





