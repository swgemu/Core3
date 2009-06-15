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

#include "CreatureObjectImplementation.h"
#include "player/PlayerObject.h"

#include "../../../packets/creature/CreatureObjectDeltaMessage6.h"
#include "../../../packets/creature/CreatureObjectMessage1.h"
#include "../../../packets/creature/CreatureObjectMessage3.h"
#include "../../../packets/creature/CreatureObjectMessage4.h"
#include "../../../packets/creature/CreatureObjectMessage6.h"
#include "../../../packets/creature/UpdatePVPStatusMessage.h"
#include "../../../packets/zone/CmdStartScene.h"
#include "../../../packets/zone/ParametersMessage.h"
#include "../../../packets/zone/unkByteFlag.h"

CreatureObjectImplementation::CreatureObjectImplementation(uint64 objectid, int type)
		: CreatureObjectServant(objectid, type) {
	complexity = 10.0f;
	volume = 0x0085E5CA; //TODO: Why is it this value?

	templatePath = "";
	performanceAnimation = "";

	height = 1.0f;
	pvpStatusBitmask = 0x10;
	factionRank = FactionRankList[0];
	species = SpeciesList[0];

	speed = DEFAULT_SPEED;
	turnRadius = 1.0f;
	terrainNegotiation = 1.0f;
	acceleration = DEFAULT_ACCEL;
	deceleration = 1.0f;

	statesBitmask = 0;
	listeningToID = 0;
	updateCounterGroupInvite = 0;
	groupInviterID = 0;

	level = 0;

	updateCounterAction = 0;
	updateCounterHAM = 0;
	updateCounterHAMMax = 0;
	updateCounterHAMBase = 0;
	updateCounterWounds = 0;
	updateCounterEncumbrance = 0;
	updateCounterPerformance = 0;
	updateCounterEquipment = 0;

	attributes[CreatureAttribute::HEALTH] = 1000;
	attributes[CreatureAttribute::STRENGTH] = 1000;
	attributes[CreatureAttribute::CONSTITUTION] = 1000;
	attributes[CreatureAttribute::ACTION] = 1000;
	attributes[CreatureAttribute::QUICKNESS] = 1000;
	attributes[CreatureAttribute::STAMINA] = 1000;
	attributes[CreatureAttribute::MIND] = 1000;
	attributes[CreatureAttribute::FOCUS] = 1000;
	attributes[CreatureAttribute::WILLPOWER] = 1000;

	attributesBase[CreatureAttribute::HEALTH] = 1000;
	attributesBase[CreatureAttribute::STRENGTH] = 1000;
	attributesBase[CreatureAttribute::CONSTITUTION] = 1000;
	attributesBase[CreatureAttribute::ACTION] = 1000;
	attributesBase[CreatureAttribute::QUICKNESS] = 1000;
	attributesBase[CreatureAttribute::STAMINA] = 1000;
	attributesBase[CreatureAttribute::MIND] = 1000;
	attributesBase[CreatureAttribute::FOCUS] = 1000;
	attributesBase[CreatureAttribute::WILLPOWER] = 1000;

	attributesMax[CreatureAttribute::HEALTH] = 1000;
	attributesMax[CreatureAttribute::STRENGTH] = 1000;
	attributesMax[CreatureAttribute::CONSTITUTION] = 1000;
	attributesMax[CreatureAttribute::ACTION] = 1000;
	attributesMax[CreatureAttribute::QUICKNESS] = 1000;
	attributesMax[CreatureAttribute::STAMINA] = 1000;
	attributesMax[CreatureAttribute::MIND] = 1000;
	attributesMax[CreatureAttribute::FOCUS] = 1000;
	attributesMax[CreatureAttribute::WILLPOWER] = 1000;

	wounds[CreatureAttribute::HEALTH] = 0;
	wounds[CreatureAttribute::STRENGTH] = 0;
	wounds[CreatureAttribute::CONSTITUTION] = 0;
	wounds[CreatureAttribute::ACTION] = 0;
	wounds[CreatureAttribute::QUICKNESS] = 0;
	wounds[CreatureAttribute::STAMINA] = 0;
	wounds[CreatureAttribute::MIND] = 0;
	wounds[CreatureAttribute::FOCUS] = 0;
	wounds[CreatureAttribute::WILLPOWER] = 0;

	encumbranceHealth = 0;
	encumbranceAction = 0;
	encumbranceMind = 0;

	shockWounds = 0;

	posture = CreaturePosture::UPRIGHT;

	moodID = 0;
	moodName = "";

	stationary = false;
}

CreatureObjectImplementation::~CreatureObjectImplementation() {
}


//Sending of packets

/**
 * This method sends this object to the specified player's client.
 * \param player The player whos client will be receiving this objects packet data.
 * \param close Should we close the scene?
 */
void CreatureObjectImplementation::sendTo(PlayerObject* player, bool close) {
	ReferenceSlot<ZoneClientSession> client = player->getClient();

	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	//if (parent != NULL)
		//TODO: Link the object to its parent

	if (player == _this) {
		BaseMessage* creo1 = new CreatureObjectMessage1(_this);
		client->sendMessage(creo1);
	}

	BaseMessage* creo3 = new CreatureObjectMessage3(_this);
	client->sendMessage(creo3);

	if (player == _this) {
		BaseMessage* creo4 = new CreatureObjectMessage4(_this);
		client->sendMessage(creo4);
	}

	BaseMessage* creo6 = new CreatureObjectMessage6(_this);
	client->sendMessage(creo6);

	BaseMessage* upvps = new UpdatePVPStatusMessage(_this);
	client->sendMessage(upvps);

	if (close)
		SceneObjectImplementation::close(client);
}

/**
 * This methods sends this object to its player owner.
 * \param player The player owner requesting the packets.
 * \param close Should we close the scene?
 */
void CreatureObjectImplementation::sendToOwner(PlayerObject* player, bool close) {
	ReferenceSlot<ZoneClientSession> client = player->getClient();

	if (client == NULL)
		return;

	BaseMessage* unkbf = new unkByteFlag();
	client->sendMessage(unkbf);

	BaseMessage* cmdss = new CmdStartScene(_this);
	client->sendMessage(cmdss);

	BaseMessage* param = new ParametersMessage();
	client->sendMessage(param);

	//TODO: Building sendto

	sendTo(player, close);
}


/*************************************************************************
 * Modifier Effects
 *************************************************************************/
void CreatureObjectImplementation::addModifierEffect(ModifierEffect* modeffect, bool activate) {

}
void CreatureObjectImplementation::removeModifierEffect(ModifierEffect* modeffect) {

}
ModifierEffect* CreatureObjectImplementation::getModifierEffect(const String& modeffectname) {
	return NULL;
}
bool CreatureObjectImplementation::hasModifierEffect(const String& modeffectname) {
	return false;
}
float CreatureObjectImplementation::getModifier(const String& modname) {
	return 0.0f;
}
bool CreatureObjectImplementation::hasModifier(const String& modname) {
	return false;
}



/*************************************************************************
 * General Actions
 *************************************************************************/
void CreatureObjectImplementation::groupInvite(PlayerObject* player) {

}
void CreatureObjectImplementation::groupJoin(PlayerObject* player) {

}
void CreatureObjectImplementation::groupLeave(PlayerObject* player) {

}
void CreatureObjectImplementation::groupKick(PlayerObject* player) {

}
void CreatureObjectImplementation::groupDisband(PlayerObject* player) {

}
void CreatureObjectImplementation::groupDecline(PlayerObject* player) {

}
void CreatureObjectImplementation::follow(TangibleObject* target) {

}
void CreatureObjectImplementation::stopFollowing(TangibleObject* target) {

}
void CreatureObjectImplementation::imageDesign(CreatureObject* target) {

}
void CreatureObjectImplementation::diagnose(CreatureObject* target) {

}
void CreatureObjectImplementation::tendDamage(CreatureObject* target) {

}
void CreatureObjectImplementation::tendWound(CreatureObject* target) {

}
void CreatureObjectImplementation::healWound(CreatureObject* target, uint8 woundtype) {

}
void CreatureObjectImplementation::healDamage(CreatureObject* target) {

}
void CreatureObjectImplementation::healState(CreatureObject* target, uint8 statetype) {

}
void CreatureObjectImplementation::healEnhance(CreatureObject* target, uint8 enhancetype) {

}
void CreatureObjectImplementation::healFirstAid(CreatureObject* target) {

}
void CreatureObjectImplementation::healCurePoison(CreatureObject* target) {

}
void CreatureObjectImplementation::healCureDisease(CreatureObject* target) {

}
void CreatureObjectImplementation::healApplyPoison(CreatureObject* target) {

}
void CreatureObjectImplementation::healApplyDisease(CreatureObject* target) {

}
void CreatureObjectImplementation::performanceListen(CreatureObject* target) {

}
void CreatureObjectImplementation::performanceWatch(CreatureObject* target) {

}
void CreatureObjectImplementation::performanceStopListening(CreatureObject* target) {

}
void CreatureObjectImplementation::performanceStopWatching(CreatureObject* target) {

}










/**
 * Updates the creatures current target and updates all nearby players.
 * \param targetid The objectid of the new target.
 */
void CreatureObjectImplementation::updateTargetObject(uint64 targetid, bool updateclients) {
	if (zone == NULL)
		return;

	if (targetObject != NULL && targetid == targetObject->getObjectID())
		return;

	SceneObject* targetobj = zone->lookupObject(targetid);

	if (targetobj == NULL)
		return;

	info("Updating target.");

	targetObject = targetobj;

	if (updateclients) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateTargetID(targetid);
		dcreo6->close();

		broadcastMessage(dcreo6);
	}
}

void CreatureObjectImplementation::updateTargetObject(SceneObject* target, bool updateclients) {
	if (target == NULL || targetObject == target)
		return;

	info("Updating target.");

	targetObject = target;

	if (updateclients) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateTargetID(target->getObjectID());
		dcreo6->close();

		broadcastMessage(dcreo6);
	}
}
