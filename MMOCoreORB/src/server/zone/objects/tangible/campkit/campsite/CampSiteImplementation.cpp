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

#include "../../../../objects.h"

#include "../../../../managers/planet/PlanetManager.h"
#include "../../../../Zone.h"
#include "../../../../ZoneProcessServerImplementation.h"

#include "CampSiteImplementation.h"
#include "../../../area/CampActiveArea.h"
#include "../../terminal/camp/CampTerminalImplementation.h"
#include "../events/CampDespawnEvent.h"
#include "../events/CampAbandonEvent.h"

CampSiteImplementation::CampSiteImplementation(Player* player, uint64 oid,CampKit* campKit) : CampSiteServant(oid, CAMPSITE) {
	objectID = oid;

	objectCRC = 0x897A440;

	name = UnicodeString("0");;
	defaultName = "";

	campOwner = player;

	campArea = NULL;
	areaRange = 10.0f;
	visitor = new VisitorList();
	recoveries = NULL;
	currentXP = 0.0f;
	campType = campKit->getCampType();

	maxXP = campKit->getXP();
	duration = campKit->getDuration();
	campModifier = 0;
	abandoned = false;
	abandonEvent = NULL;
	despawnEvent = NULL;
	initializePosition(player->getPositionX(),player->getPositionZ(),player->getPositionY());

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

void CampSiteImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	BaseMessage* inso3 = new TangibleObjectMessage3((CampSite*) _this);
	client->sendMessage(inso3);

	BaseMessage* inso6 = new TangibleObjectMessage6((CampSite*) _this);
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
		campOwner->addXp(type,(int)currentXP, true);

		StringBuffer msg;

		campOwner->sendSystemMessage(msg.toString());

	}

	campArea->forceTriggerExit();
	PlanetManager* planetManager = campOwner->getZone()->getPlanetManager();
	planetManager->removeActiveAreaTrigger(campArea);
	campArea = NULL;

	if (abandonEvent != NULL)
		abandonEvent->endNow();

	abandonEvent = NULL;

	for (int i = 0 ; i < campObjects.size() ; i++) {
		SceneObject* scno = campObjects.get(i);
		scno->removeFromZone();
		scno->finalize();
	}

	deactivateRecovery();
}

/*
 * Creates an CampActiveArea around the camp.
 */
void CampSiteImplementation::createCampArea() {
	campOwner->sendSystemMessage("@camp:camp_complete");
	Zone* zone = campOwner->getZone();

	PlanetManager* planetManager = zone->getPlanetManager();
	campArea = planetManager->spawnActiveArea(new CampActiveArea(getPositionX(),  getPositionY(),  getPositionZ(), areaRange, _this));
	campArea->forceTriggerEnter();

	//despawnEvent = new CampDespawnEvent(_this,getDuration() * 1000);

	despawnEvent = new CampDespawnEvent(_this,(duration * 1000));
	server->addEvent(despawnEvent);

	spawnCampItems();
	insertToZone(campOwner->getZone());
}

void CampSiteImplementation::addCampObject(uint64 oid, uint32 ocrc, float x, float z, float y,float oX, float oZ,float oY, float oW) {
	TangibleObject* tObj = new TangibleObject(oid,TangibleObjectImplementation::CAMPSITE);
	tObj->setObjectCRC(ocrc);
	tObj->initializePosition(x,z,y);
	tObj->setDirection(oX,oZ,oY,oW);
	tObj->insertToZone(campOwner->getZone());
	campObjects.add(tObj);
}

void CampSiteImplementation::addCampObject(uint64 oid, uint32 ocrc, const UnicodeString& n, float x, float z, float y,float oX, float oZ,float oY, float oW) {
	TangibleObject* tObj = new TangibleObject(oid,TangibleObjectImplementation::CAMPSITE);
	tObj->setCustomName(n);
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
	abandoned = true;
}

/*
 * abandons the camp.
 */
void CampSiteImplementation::abandonCamp() {
	if (abandoned)
		return;

	abandoned = true;
	abandonEvent = NULL;
	campOwner->setCamp(NULL);
	campOwner->sendSystemMessage("@camp:sys_abandoned_camp");
	SceneObject* scno = campObjects.get(0);
	if (scno != NULL && scno->isTangible()) {
		TangibleObject* tObj = (TangibleObject*) scno;
		tObj->setCustomName(UnicodeString("Abandoned Camp"));
	}
	//update terminal name
	for (int i = 0; i < inRangeObjectCount(); i++) {
		SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_this);
		if (object->isPlayer()) {
			Player* player = (Player*) object;
			campObjects.get(0)->sendTo(player);
			//player->setCampModifier(0);
			//player->setCampAggroMod(0);
		}
	}

	campArea->forceTriggerExit();

	deactivateRecovery();

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
	if (abandoned) {
		player->setCampModifier(0);
		return;
	}

	if (player == campOwner && abandonEvent != NULL) {
		abortAbandonPhase();
	}

	player->sendSystemMessage("@camp:camp_enter");
	player->setCampModifier(campModifier);
	player->setCampAggroMod(aggroMod);

	CampRecoveryEvent* recoveryEvent = new CampRecoveryEvent(player,_this);
	server->addEvent(recoveryEvent,300000);
	recoveries->put(player->getObjectID(),recoveryEvent);

	Time enterTime;
	visitor->put(player->getObjectID(),enterTime.getTime());
}

/*
 * Handles a player leaving the camp.
 * \param player The player leaving the camp.
 */
void CampSiteImplementation::exitNotificaton(Player* player) {
	if (player == campOwner && !abandoned) {
		abandonEvent = new CampAbandonEvent(_this,60000);
		server->addEvent(abandonEvent);
	}

	player->setCampModifier(0);
	player->setCampAggroMod(0);

	CampRecoveryEvent* event = recoveries->getEvent(player->getObjectID());

	if (event != NULL)
		event->leaveCamp();

	if (!abandoned) {
		player->sendSystemMessage("@camp:camp_exit");
		addXP(player->getObjectID());
	}

	visitor->put(player->getObjectID(),0);
}

/*
 * Calculates the xp.
 */
void CampSiteImplementation::calculateXP() {
	if (abandoned)
		return;

	if (!visitor->isEmpty()) {
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

		float xp = (1.0f * time / 720) * maxXP;

		currentXP += xp;
	}
}

void CampSiteImplementation::reactiveRecovery(Player* player) {
	CampRecoveryEvent* recoveryEvent = recoveries->getEvent(player->getObjectID());
	if (recoveryEvent != NULL && !recoveryEvent->isQueued())
		server->addEvent(recoveryEvent,300000);
}

void CampSiteImplementation::deactivateRecovery() {
	uint64 playerID = 0;

	while (recoveries->hasNext()) {
		playerID = recoveries->getNextKey();

		// deactivate for all player, visited the camp (players not in area, logout)
		recoveries->getEvent(playerID)->leaveCamp();

	}
}
