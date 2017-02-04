/*
 * VetHarvesterDeedImplementation.cpp
 *
 *  Created on: Feb 13, 2016
 *      Author: gregslomin
 */

#include "server/zone/objects/tangible/deed/vetharvester/VetHarvesterDeed.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/ZoneServer.h"

void VetHarvesterDeedImplementation::initializeTransientMembers() {
	DeedImplementation::initializeTransientMembers();

	setLoggingName("VetHarvesterDeed");
}

void VetHarvesterDeedImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* creature) {
	DeedImplementation::fillObjectMenuResponse(menuResponse, creature);

	if (!isASubChildOf(creature))
		return;
  
	menuResponse->addRadialMenuItem(20, 3, "@ui_radial:convert_harvester"); //use
}

int VetHarvesterDeedImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20) // not use object
		return 1;

	if (player != NULL)
		useObject(player);

	return 0;
}

int VetHarvesterDeedImplementation::useObject(CreatureObject* creature) {

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	ZoneServer *zone = creature->getZoneServer();

	if (ghost == NULL || zone == NULL)
		return 0;

	if (!isASubChildOf(creature))
		return 0;

	uint64 targetID = creature->getTargetID();

	ManagedReference<TangibleObject*> targetObject = zone->getObject(targetID).castTo<TangibleObject*>();

	if (targetObject == NULL || !targetObject->isHarvesterObject())
		return 0;

	ManagedReference<HarvesterObject*> harvester = targetObject.castTo<HarvesterObject*>();

	if (harvester == NULL || !harvester->isOwnerOf(creature))
		return 0;

	if (harvester->isSelfPowered()) {
		creature->sendSystemMessage("@veteran:harvester_already_selfpowered");
		return 0;
	}

	StringIdChatParameter messageBody("veteran", "harvester_converted"); // Your harvester %TT has been converted to use 0 power.
	messageBody.setTT(harvester->getObjectID());

	ManagedReference<ChatManager*> cman = zone->getChatManager();

	cman->sendMail("system", "@veteran:harvester_converted_subject", messageBody, creature->getFirstName());

	Core::getTaskManager()->executeTask([=] () {
		Locker locker(harvester);
		harvester->setSelfPowered(true);
	}, "SetSelfPoweredLambda");

	destroyDeed();

	return 1;
}

void VetHarvesterDeedImplementation::destroyDeed() {
	if (parent.get() != NULL) {
		destroyObjectFromWorld(true);
	}

	if (isPersistent())
		destroyObjectFromDatabase(true);
}
