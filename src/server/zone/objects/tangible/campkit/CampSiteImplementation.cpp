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

#include "engine/engine.h"

#include "../../../objects.h"

#include "../../../managers/planet/PlanetManager.h"
#include "../../../Zone.h"
#include "../../../ZoneProcessServerImplementation.h"

#include "CampSiteImplementation.h"
#include "../../area/CampActiveArea.h"
#include "../terminal/camp/CampTerminalImplementation.h"
#include "events/CampDespawnEvent.h"
#include "events/CampAbandonEvent.h"

CampSiteImplementation::CampSiteImplementation(Player* player, uint64 oid,CampKit* campKit) : CampSiteServant(oid, MISC) {
	objectID = oid;

	objectCRC = 0;

	name = UnicodeString("0");;
	defaultName = "";

	terminal = NULL;
	campOwner = player;

	campArea = NULL;
	visitor = new VisitorList();
	currentXP = 0.0f;
	campType = campKit->getCampType();

	maxXP = campKit->getXP();
	duration = campKit->getDuration();
	campModifier = 0;
	abandoned = false;
	abandonEvent = NULL;
	despawnEvent = NULL;

	init();
}

CampSiteImplementation::~CampSiteImplementation() {
	campArea = NULL;
	despawnEvent = NULL;
	if (abandonEvent != NULL)
		abandonEvent->endNow();

	abandonEvent = NULL;
	visitor = NULL;
}

void CampSiteImplementation::init() {
	container = NULL;
	zone = NULL;

	persistent = false;
	updated = false;

	building = NULL;

	objectCount = 0;

	objectType = SceneObjectImplementation::TANGIBLE;
	objectSubType = TangibleObjectImplementation::MISC;

	equipped = false;

	pvpStatusBitmask = 0;

	switch(campType) {
		case 0:
			name = UnicodeString("Basic Camp");
			defaultName = "basic_name";
			objectCRC = 144155712;
			campModifier = 60;
			break;
		case 1:
			name = UnicodeString("Improved Camp");
			defaultName = "improved_name";
			objectCRC = 1100661709;
			campModifier = 70;
			break;
		case 2:
			name = UnicodeString("Quality Camp");
			defaultName = "quality_name";
			objectCRC = 2592959322;
			campModifier = 80;
			break;
		case 3:
			name = UnicodeString("Luxury Camp");
			defaultName = "luxury_name";
			objectCRC = 3548384471;
			campModifier = 100;
			break;
		case 4:
			name = UnicodeString("Elite Camp");
			defaultName = "elite_name";
			objectCRC = 1634615374;
			campModifier = 120;
			break;
		default:
			name = UnicodeString("Basic Camp");
			defaultName = "basic_name";
			objectCRC = 144155712;
			campModifier = 60;
			break;
	}
}

void CampSiteImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	BaseMessage* inso3 = new BuildingObjectMessage3((CampSite*) _this);
	client->sendMessage(inso3);

	BaseMessage* inso6 = new BuildingObjectMessage6((CampSite*) _this);
	client->sendMessage(inso6);

	if (doClose)
		SceneObjectImplementation::close(client);

}

void CampSiteImplementation::generateAttributes(SceneObject* obj) {
}

void CampSiteImplementation::parseItemAttributes() {
}

void CampSiteImplementation::addHeaderAttributes(AttributeListMessage* alm) {
}

void CampSiteImplementation::addFooterAttributes(AttributeListMessage* alm) {
}

void CampSiteImplementation::addAttributes(AttributeListMessage* alm) {
}

/*
 * Despawns the camp.
 * \param player The camps owner.
 */
void CampSiteImplementation::removeCampArea() {
	if (!abandoned && campOwner != NULL) {
		campOwner->sendSystemMessage("@camp:error_camp_disband");

		campOwner->setCamp(NULL);

		calculateXP();

		String type = "camp";
		campOwner->addXp(type,currentXP, true);

		StringBuffer msg;

		campOwner->sendSystemMessage(msg.toString());

		//TODO: check area, insert & remove include activation
	}

	PlanetManager* planetManager = campOwner->getZone()->getPlanetManager();
	planetManager->removeActiveAreaTrigger(campArea);
	campArea = NULL;

	terminal->removeFromZone();
	terminal->finalize();
	terminal = NULL;

	for (int i = 0 ; i < campObjects.size() ; i++) {
		SceneObject* scno = campObjects.get(i);
		scno->removeFromZone();
		scno->finalize();
	}



}

/*
 * Creates an CampActiveArea around the camp.
 */
void CampSiteImplementation::createCampArea() {
	campOwner->sendSystemMessage("@camp:camp_complete");
	Zone* zone = campOwner->getZone();

	PlanetManager* planetManager = zone->getPlanetManager();
	campArea = planetManager->spawnActiveArea(new CampActiveArea(getPositionX(),  getPositionY(),  getPositionZ(), 5.0f, _this));

	despawnEvent = new CampDespawnEvent(_this,getDuration() * 1000);
	server->addEvent(despawnEvent);

	spawnCampItems();

}

void CampSiteImplementation::spawnCampItems() {
	float x = getPositionX();
	float z = getPositionZ();
	float y = getPositionY();

	switch(campType) {
		case 0:
			terminal = new CampTerminal(_this,campOwner->getNewItemID(),(x + 1.5f),z , (y - 1.3f));
			terminal->setDirection(0.0f, 0.0f, -0.6f, 0.7f);
			terminal->insertToZone(campOwner->getZone());
			addCampObject(campOwner->getNewItemID(), 2127813712, (x + 4), z, y, 0.0f, 0.0f, -0.6f, 0.7f);
			addCampObject(campOwner->getNewItemID(), 1850708683, x, z, (y+1), 0.0f, 0.0f, 0.0f, 0.0f);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		default:
			break;
	}
}

void CampSiteImplementation::addCampObject(uint64 oid, uint32 ocrc, float x, float z, float y,float oX, float oZ,float oY, float oW) {
	TangibleObject* tObj = new TangibleObject(oid,TangibleObjectImplementation::CAMPSITE);
	tObj->setObjectCRC(ocrc);
	tObj->initializePosition(x,z,y);
	tObj->setDirection(oX,oZ,oY,oW);
	tObj->insertToZone(campOwner->getZone());
	campObjects.add(tObj);
}
/*
 * Disbands the camp.
 */
void CampSiteImplementation::disbandCamp() {
	despawnEvent->endNow();
}

/*
 * abandons the camp.
 */
void CampSiteImplementation::abandonCamp() {
	abandoned = true;
	abandonEvent = NULL;
	campOwner->setCamp(NULL);
	campOwner->sendSystemMessage("@camp:sys_abandoned_camp");
}

/*
 * abandons the camp.
 */
void CampSiteImplementation::abortAbandonPhase() {
	abandonEvent->endNow();
	abandonEvent = NULL;
}

/*
 * Handles a player entering the camp.
 * \param player The player entering the camp.
 */
void CampSiteImplementation::enterNotification(Player* player) {
	if (abandoned)
		return;

	if (player == campOwner && abandonEvent != NULL) {
		abortAbandonPhase();
	}

	player->sendSystemMessage("@camp:camp_enter");
	player->setCampModifier(campModifier);

	Time enterTime;
	visitor->put(player->getObjectID(),enterTime.getTime());

}

/*
 * Handles a player leaving the camp.
 * \param player The player leaving the camp.
 */
void CampSiteImplementation::exitNotificaton(Player* player) {
	if (abandoned)
		return;

	if (player == campOwner && !abandoned) {
		abandonEvent = new CampAbandonEvent(_this,1000);
		server->addEvent(abandonEvent);
	}

	player->sendSystemMessage("@camp:camp_exit");
	player->setCampModifier(0);

	addXP(player->getObjectID());
	visitor->put(player->getObjectID(),0);
}

/*
 * Calculates the xp.
 */
void CampSiteImplementation::calculateXP() {
	if (abandoned)
		return;

	if(!visitor->isEmpty()) {
		uint64 playerID = 0;

		while (visitor->hasNext()) {
			playerID = visitor->getNextKey();
			addXP(playerID);
		}
	}

	if (currentXP > maxXP)
		currentXP = maxXP;
}

/*
 * Adds the xp related to the players visit.
 * \param player The player.
 */
void CampSiteImplementation::addXP(uint64 playerID) {
	if (abandoned)
		return;

	Time current;
	uint64 enterTime = visitor->get(playerID);
	if (enterTime > 0) {
		uint64 time = 1 + current.getTime() - enterTime;

		float xp = (1.0f * time / duration) * maxXP;
		currentXP += xp;
	}
}
