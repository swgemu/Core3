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
#include "../../ZoneClientSession.h"

#include "../../packets.h"
#include "../../objects.h"

#include "MissionObject.h"
#include "MissionObjectImplementation.h"

MissionObjectImplementation::MissionObjectImplementation(uint64 oid) : SceneObjectImplementation(oid, MISSION) {
	objectCRC = 0xDF064E7A; //0x7a,0x4e,0x06,0xdf,

	objectType = SceneObjectImplementation::MISSION;

	stringstream name;
	name << "MissionObject :" << oid;
	setLoggingName(name.str());

	setLogging(false);
	setGlobalLogging(true);

	init();
}

MissionObjectImplementation::~MissionObjectImplementation() {
}

void MissionObjectImplementation::init() {
	dbKey = "";

	terminalMask = 0;

	//MISO3:
	typeStr = ""; //3
	descKey = 0; //4
	titleKey = 0; //4
	difficultyLevel = 0; //5
	//6:
		destX = 0.0f;
		destY = 0.0f;
		destPlanetCrc = 0;
	//
	//creatorName = ""; //7 UNICODE
	rewardAmount = 0; //8
	//9:
		targetX = 0.0f;
		targetY = 0.0f;
		targetPlanetCrc = 0;
	//
	depictedObjCrc = 0; //10 (0A)
	descriptionStf = ""; //11 (0B)
	titleStf = ""; //12 (0C)
	refreshCount = 0x01; //13 (0D)
	typeCrc = 0; //14 (0E)
}

void MissionObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	create(client);

	BaseMessage* miso3 = new MissionObjectMessage3((MissionObject*) _this);
	client->sendMessage(miso3);

	BaseMessage* miso6 = new MissionObjectMessage6((MissionObject*) _this);
	client->sendMessage(miso6);

	if (doClose) {
		close(client);
	}
}

void MissionObjectImplementation::sendDeltaTo(Player* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	MissionObjectDeltaMessage3* dmiso3 = new MissionObjectDeltaMessage3((MissionObject*) _this);

	dmiso3->updateDescriptionStf(); //11 (0B)
	dmiso3->updateDescKey(); //4
	dmiso3->updateDifficultyLv(); //5
	dmiso3->updateDestination(); //6
	dmiso3->updateCreator(); //7
	dmiso3->updateTypeCrc(); //14 (0E)
	dmiso3->updateReward(); //8
	dmiso3->updateTarget(); //9
	dmiso3->updateDepictedObject(); //10 (0A)
	dmiso3->updateTitleStf(); //12 (0C)
	dmiso3->updateTitleKey(); //4
	dmiso3->updateRefreshCount(player->nextMisoRFC()); //13 (0D)

	dmiso3->close();

	client->sendMessage(dmiso3);
}

void MissionObjectImplementation::doLinkToPlayer(Player* player) {
	player->sendMessage(link(player->getDatapad()->getObjectID(), 0xFFFFFFFF));
}

//Use this function to remove the mission from the player.
//This does NOT remove the actual mission Object from the pool
void MissionObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}

