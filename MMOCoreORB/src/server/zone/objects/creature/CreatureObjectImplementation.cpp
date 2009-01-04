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
#include "../../ZoneProcessServerImplementation.h"

#include "../../ZoneClientSession.h"

#include "../../objects.h"
#include "../../packets.h"


#include "events/CreatureBurstRunOverEvent.h"
#include "events/DizzyFallDownEvent.h"
#include "events/WoundTreatmentOverEvent.h"
#include "events/InjuryTreatmentOverEvent.h"
#include "events/StateTreatmentOverEvent.h"
#include "events/ConditionTreatmentOverEvent.h"
#include "events/MaskScentEvent.h"

#include "../../objects/player/Races.h"

#include "skills/PassiveSkill.h"
#include "skills/EntertainerSkill.h"
#include "skills/CamoSkill.h"

#include "../../managers/skills/SkillManager.h"

CreatureObjectImplementation::CreatureObjectImplementation(uint64 oid) : CreatureObjectServant(oid + 0x15, NONPLAYERCREATURE) {
	objectType = NONPLAYERCREATURE;

	positionCounter = 0;

	inventory = NULL;
	lootContainer = NULL;

	weaponSpeedModifier = 1;
	centeredBonus = 0;

	creatureSkillsCount = 0;
	creatureSkills.setInsertPlan(SortedVector<Skill*>::NO_DUPLICATE);
	creatureSkills.setNullValue(NULL);

	damageMap.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);
	damageMap.setNullValue(0);

	stfName = "species";

	boneType = "";
	hideType = "";
	meatType = "";

	actionCounter = 0;

	// CREO1 operands
	cashCredits = 25000;
	bankCredits = 25000;

	// CREO3 operands
	postureState = CreaturePosture::UPRIGHT;
	stateBitmask = oldStateBitmask = 0;
	creatureBitmask = 0x80;

	conditionDamage = 0;
	maxCondition = 0;
	mount = NULL;
	creatureLinkID = 0;

	height = 1.0f;

	// CREO4 operands
	speed = DEFAULT_SPEED;
	acceleration = DEFAULT_ACCELERATION;
	skillModsCounter = 0;
	skillModBonusCounter = 0;

	// CREO6 operands
	defenderUpdateCounter = 0;
	defenderID = 0;

	moodid = 0;
	mood = Races::getMood(moodid);
	moodStr = Races::getMoodStr(mood);

	weaponObject = NULL;
	targetObject = NULL;
	hairObj = NULL;

	hamUpdateCounter = 0;
	hamMaxUpdateCounter = 0;
	hamBaseUpdateCounter = 0;
	hamEncumbUpdateCounter = 0;
	woundsUpdateCounter = 0;

	baseHealth = 1000;
	baseStrength = 500;
	baseConstitution = 500;
	baseAction = 1000;
	baseQuickness = 500;
	baseStamina = 500;
	baseMind = 1000;
	baseFocus = 500;
	baseWillpower = 500;

	health = 3000;
	strength = 3000;
	constitution = 3000;
	action = 3000;
	quickness = 3000;
	stamina = 3000;
	mind = 3000;
	focus = 3000;
	willpower = 3000;

	healthMax = 3000;
	strengthMax = 3000;
	constitutionMax = 3000;
	actionMax = 3000;
	quicknessMax = 3000;
	staminaMax = 3000;
	mindMax = 3000;
	focusMax = 3000;
	willpowerMax = 3000;

	healthEncumbrance = 0;
	actionEncumbrance = 0;
	mindEncumbrance = 0;

	// ent
	performanceCounter = 0;

	instrumentID = 0;
	performanceName = "";

	doDancing = false;
	doPlayingMusic = false;
	doListening = false;
	doWatching = false;

	watchID = 0;
	listenID = 0;

	danceBuffDuration = 0.0f;
	musicBuffDuration = 0.0f;

	danceBuffStrength = 0.0f;
	musicBuffStrength = 0.0f;

	listeners.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);
	watchers.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);

	// wounds
	healthWounds = 0;
	strengthWounds = 0;
	constitutionWounds = 0;
	actionWounds = 0;
	quicknessWounds = 0;
	staminaWounds = 0;
	mindWounds = 0;
	focusWounds = 0;
	willpowerWounds = 0;

	// AKA Battle Fatigue
	shockWounds = 0;

	// misc
	pvpStatusBitmask = 0x10;
	faction = 0;
	factionRank = 0;

	// combat
	fireDotType = 0;
	fireDotStrength = 0;

	poisonDotType = 0;
	poisonDotStrength = 0;

	diseaseDotType = 0;
	diseaseDotStrength = 0;

	bleedingDotType = 0;
	bleedingDotStrength = 0;

	accuracy = 0;

	sittingOnObject = false;

	damageBonus = 0;
	defenseBonus = 0;

	queuedStates.setInsertPlan(SortedVector<uint32>::NO_DUPLICATE);

	//guild stuff
	guild = NULL;

	//Group
	groupInviteCount = 0;

	groupId = 0;
	groupInviterID = 0;

	group = NULL;

	dizzyFallDownEvent = new DizzyFallDownEvent(this);

	lastMovementUpdateStamp = 0;
	ignoreMovementTests = 5;

	level = 0;

	//Powerboost
	pbHA = 0;
	pbMind = 0;
	pbTick = 0;
	pbBonus = 0;
	pbCounter = 0;

	// Buffs
	healthBuff = false;
	strengthBuff = false;
	constitutionBuff = false;
	actionBuff = false;
	quicknessBuff = false;
	staminaBuff = false;
	mindBuff = false;
	focusBuff = false;
	willpowerBuff = false;


	//Medical Timers
	doWoundTreatment = true;
	doInjuryTreatment = true;
	doStateTreatment = true;
	doConditionTreatment = true;

	woundTreatmentEvent = NULL;
	injuryTreatmentEvent = NULL;
	stateTreatmentEvent = NULL;
	conditionTreatmentEvent = NULL;

	frozen = false;
	templateString = "";

	camoType = 11;
	maskScentEvent = NULL;
	maskScent = 0;

	ferocity = 0;
	baby = false;
}

CreatureObjectImplementation::~CreatureObjectImplementation() {
	if (dizzyFallDownEvent != NULL) {
		if (dizzyFallDownEvent->isQueued())
			server->removeEvent(dizzyFallDownEvent);

		delete dizzyFallDownEvent;
		dizzyFallDownEvent = NULL;
	}

	if (woundTreatmentEvent != NULL) {
		if (woundTreatmentEvent->isQueued()) {
			doWoundTreatment = true;
			server->removeEvent(woundTreatmentEvent);
		}

		delete woundTreatmentEvent;
		woundTreatmentEvent = NULL;
	}

	if (maskScentEvent != NULL) {
		if (maskScentEvent->isQueued()) {
			server->removeEvent(maskScentEvent);
		delete maskScentEvent;
		maskScentEvent = NULL;
		}
	}

	if (injuryTreatmentEvent != NULL) {
		if (injuryTreatmentEvent->isQueued()) {
			doInjuryTreatment = true;
			server->removeEvent(injuryTreatmentEvent);
		}

		delete injuryTreatmentEvent;
		injuryTreatmentEvent = NULL;
	}

	if (stateTreatmentEvent != NULL) {
		if (stateTreatmentEvent->isQueued()) {
			doStateTreatment = true;
			server->removeEvent(stateTreatmentEvent);
		}

		delete stateTreatmentEvent;
		stateTreatmentEvent = NULL;
	}

	if (conditionTreatmentEvent != NULL) {
		if (conditionTreatmentEvent->isQueued()) {
			doConditionTreatment = true;
			server->removeEvent(conditionTreatmentEvent);
		}

		delete conditionTreatmentEvent;
		conditionTreatmentEvent = NULL;
	}

	if (lootContainer != NULL) {
		lootContainer->finalize();
		lootContainer = NULL;
	}

	if (inventory != NULL) {
		info("undeploying creature object inventory");

		inventory->finalize();
		inventory = NULL;
	}
}

void CreatureObjectImplementation::sendToOwner(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	BaseMessage* ubf = new unkByteFlag();
	client->sendMessage(ubf);

	info("CmdStartScene");
	BaseMessage* css = new CmdStartScene(_this);
	client->sendMessage(css);

	BaseMessage* pmm = new ParametersMessage();
	client->sendMessage(pmm);

	if (parent != NULL)
	{
		if (parent != NULL && parent->isCell()) {
			BuildingObject* building = (BuildingObject*) parent->getParent();
			info("sending building to client through CreatureObjectImplementation::sendToOwner");
			building->sendTo((Player*)_this, false);
		} else
			parent->sendTo((Player*)_this, false);
	}

	sendTo(player, doClose);
}

void CreatureObjectImplementation::sendTo(Player* player, bool doClose) {
	info("CreatureObjectImplementation::sendTo");
	ReferenceSlot<ZoneClientSession> client = player->getClient();
	if (client == NULL)
		return;

	/*StringBuffer msg;
	msg << "sending TO:[" << player->getFirstName() << "]";
	info(msg.toString(), true);*/

	if (player == (Player*) _this && group != NULL)
		group->sendTo(player);

	create(client);

	if (parent != NULL)
		client->sendMessage(link(parent));

	if (player == (Player*) _this) {
		BaseMessage* creo1 = new CreatureObjectMessage1(this);
		client->sendMessage(creo1);
	}

	BaseMessage* creo3 = new CreatureObjectMessage3(_this);
	client->sendMessage(creo3);

	if (player == (Player*) _this) {
		BaseMessage* creo4 = new CreatureObjectMessage4(this);
		client->sendMessage(creo4);
	}

	BaseMessage* creo6 = new CreatureObjectMessage6(_this);
	client->sendMessage(creo6);

	sendFactionStatusTo(player);

	if (doClose)
		close(client);
}

void CreatureObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	destroy(client);
}

void CreatureObjectImplementation::sendItemsTo(Player* player) {
	if (inventory == NULL)
		return;

	inventory->sendTo(player, false);

	for (int i = 0; i < inventory->objectsSize(); ++i) {
		SceneObject* item = inventory->getObject(i);

		if (player == (Player*) _this)
			item->sendTo(player);
		else if (item->isTangible() && ((TangibleObject*) item)->isEquipped())
			item->sendTo(player);
	}

	inventory->close(player);

	if (hairObj != NULL)
		hairObj->sendTo(player);
}

//NOTE: This function is about to get completely revamped
void CreatureObjectImplementation::sendFactionStatusTo(Player* player, bool doTwoWay) {
	const uint32 AGRO_FLAGS = CreatureFlag::ATTACKABLE + CreatureFlag::AGGRESSIVE + CreatureFlag::ENEMY;

	if (this->isRebel() || this->isImperial()) {
		if (this->isNonPlayerCreature()) {
			if (this->isAttackableBy(player))
				player->sendMessage(new UpdatePVPStatusMessage(_this, pvpStatusBitmask + AGRO_FLAGS));
			else
				player->sendMessage(new UpdatePVPStatusMessage(_this, pvpStatusBitmask));
		} else if (this->isPlayer()) {
			PlayerImplementation * thisPlayer = (PlayerImplementation *) this;

			if (thisPlayer->hatesFaction(player->getFaction()) && thisPlayer->isOvert() && player->isOvert())
				player->sendMessage(new UpdatePVPStatusMessage(_this, pvpStatusBitmask + AGRO_FLAGS));
			else
				player->sendMessage(new UpdatePVPStatusMessage(_this, pvpStatusBitmask));
		} else //Don't know what other option there is, but just in case
			player->sendMessage(new UpdatePVPStatusMessage(_this, pvpStatusBitmask));

	} else {
		player->sendMessage(new UpdatePVPStatusMessage(_this, pvpStatusBitmask));
	}

	if (doTwoWay && isPlayer()) {
		((PlayerImplementation *) player->_getImplementation())->sendFactionStatusTo((Player *) _this, false);
	}
}

void CreatureObjectImplementation::doCombatAnimation(CreatureObject* defender, uint32 animcrc, uint8 hit) {
	CombatAction* action = new CombatAction(_this, defender, animcrc, hit);

	broadcastMessage(action);
}

void CreatureObjectImplementation::doAnimation(const String& anim) {
	Animation* msg = new Animation(_this, anim);

	broadcastMessage(msg);
}

void CreatureObjectImplementation::playEffect(const String& file, const String& aux) {
	PlayClientEffectObjectMessage* effect = new PlayClientEffectObjectMessage(_this, file, aux);

	int rangeLimit = 128;

	if (inRangeObjectCount() > 40)
		rangeLimit = 70;

	broadcastMessage(effect, rangeLimit);
}

void CreatureObjectImplementation::showFlyText(const String& file, const String& aux, uint8 red, uint8 green, uint8 blue) {
	ShowFlyText* fly = new ShowFlyText(_this, file, aux, red, green, blue);

	int rangeLimit = 128;

	if (inRangeObjectCount() > 40)
		rangeLimit = 70;

	broadcastMessage(fly, rangeLimit);
}

void CreatureObjectImplementation::sendCombatSpam(CreatureObject* defender, TangibleObject* item, uint32 damage, const String& skill, bool areaSpam) {
	try {
		//info("sending combat spam");

		zone->lock();

		bool needLimiting = inRangeObjectCount() > 40;

		if (areaSpam)
		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer() && isInRange(object, 70)) {
				Player* player = (Player*) object;

				CombatSpam* msg = new CombatSpam(_this, defender, item, damage, "cbt_spam", skill, player);
				player->sendMessage(msg);
			}
		}
		else if (isPlayer()) {
			CombatSpam* msg = new CombatSpam(_this, defender, item, damage, "cbt_spam", skill, _this);
			((Player*)_this)->sendMessage(msg);
		}

		zone->unlock();

		//info("combat spam sent");
	} catch (...) {
		error("exception CreatureObject::sendCombatSpam(CreatureObject* defender, TangibleObject* item, uint32 damage, const String& skill)");

		zone->unlock();
	}
}

void CreatureObjectImplementation::setPosture(uint8 state, bool overrideDizzy, bool objectInteraction, float objX, float objY, float objZ) {
	if (!overrideDizzy && isDizzied() && (postureState != CreaturePosture::UPRIGHT))
		state = CreaturePosture::KNOCKEDDOWN;

	if (state != postureState) {
		postureState = state;

		//Now we need to check for entertainer stuff.
		if (doDancing)
			stopDancing();
		else if (doPlayingMusic)
			stopPlayingMusic();

		//Remove meditative state if needed.
		if (isMeditating() && postureState != CreaturePosture::SITTING) {
			updateMood(Races::getMood(moodid));
			clearState(CreatureState::ALERT);
			updateStates();
		}

		Vector<BaseMessage*> msgs;
		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updatePosture();

		if (objectInteraction == false) {
			PostureMessage* octrl = new PostureMessage(_this);
			msgs.add(octrl);

			//Now we need to check if they are sitting on a chair
			if (isSittingOnObject()) {
				setSittingOnObject(false);
				clearState(CreatureState::SITTINGONCHAIR);

				dcreo3->updateState();
			 }
		} else {
			SitOnObject* soo = new SitOnObject(_this, objX, objY, objZ);
			msgs.add(soo);

			setState(CreatureState::SITTINGONCHAIR);
			setSittingOnObject(true);

			dcreo3->updateState();
		}

		dcreo3->close();
		msgs.add(dcreo3);

		broadcastMessages(msgs);

		if (postureState == CreaturePosture::PRONE)
			updateSpeed(2.688, 0.7745);
		else if (postureState == CreaturePosture::UPRIGHT)
			updateSpeed(5.376, 1.549f);
	}
}

void CreatureObjectImplementation::setCombatState() {
	lastCombatAction.update();

	if (!(stateBitmask & CreatureState::COMBAT)) {
		stateBitmask |= CreatureState::COMBAT;

		if (stateBitmask & CreatureState::PEACE)
			stateBitmask &= ~CreatureState::PEACE;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updateCreatureBitmask(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3);

		if (postureState == CreaturePosture::SITTING)
			setPosture(CreaturePosture::UPRIGHT);
	}
}

void CreatureObjectImplementation::setDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	ManagedReference<SceneObject> temp = NULL;

	int i = 0;
	for (; i < defenderList.size(); i++) {
		if (defenderList.get(i) == defender) {
			if (i == 0)
				return;

			temp = defenderList.get(0);

			defenderList.set(0, defender);
			defenderList.set(i, temp);

			break;
		}
	}

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6((CreatureObject*) _this);
	if (temp != NULL) {
		dcreo6->startDefenderUpdate(2);
		dcreo6->setDefender(i, temp->getObjectID());
		dcreo6->setDefender(0, defender->getObjectID());
	} else {
		dcreo6->startDefenderUpdate(1);
		dcreo6->addDefender(defenderList.size(), defender->getObjectID());

		defenderList.add(defender);
	}

	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	setCombatState();

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	info("adding defender");

	defenderList.add(defender);

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6((CreatureObject*) _this);
	dcreo6->startDefenderUpdate(1);
	dcreo6->addDefender(defenderList.size() - 1, defender->getObjectID());
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::removeDefenders() {
	info("removing all defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6((CreatureObject*) _this);
	dcreo6->startDefenderUpdate(1);

	dcreo6->removeDefenders();
	dcreo6->close();

	broadcastMessage(dcreo6);

	defenderList.removeAll();

	info("removed all defenders");
}

void CreatureObjectImplementation::removeDefender(SceneObject* defender) {
	if (zone == NULL)
		return;

	//info("trying to remove defender");
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			defenderList.remove(i);

			info("removing defender");

			CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6((CreatureObject*) _this);
			dcreo6->startDefenderUpdate(1);

			if (defenderList.size() == 0)
				dcreo6->removeDefenders();
			else
				dcreo6->removeDefender(i);

			dcreo6->close();

			broadcastMessage(dcreo6);

			//info("defender found and removed");
			break;
		}
	}

	if (defenderList.size() == 0)
		clearCombatState(false);

	//info("finished removing defender");
}

bool CreatureObjectImplementation::hasDefender(SceneObject* defender) {
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender)
			return true;
	}
	return false;
}

void CreatureObjectImplementation::clearCombatState(bool removedefenders) {
	//info("trying to clear CombatState");
	if (stateBitmask & CreatureState::COMBAT) {
		if (stateBitmask & CreatureState::PEACE)
			stateBitmask &= ~CreatureState::PEACE;

		stateBitmask &= ~CreatureState::COMBAT;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updateCreatureBitmask(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3);
	}

	if (removedefenders)
		removeDefenders();

	//info("finished clearCombatState");
}

void CreatureObjectImplementation::setDizziedState() {
	//TODO: remove this once npcs gets state defences
	if (dizzyRecoveryTime.miliDifference() > -(1000 + System::random(3000)))
		return;

	if (setState(CreatureState::DIZZY)) {
		playEffect("clienteffect/combat_special_defender_dizzy.cef");
		showFlyText("combat_effects", "go_dizzy", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_dizzy_single");

		dizzyRecoveryTime.update();
		dizzyRecoveryTime.addMiliTime(5000 + System::random(20000));
	}
}

void CreatureObjectImplementation::setStunnedState() {
	//TODO: remove this once npcs gets state defences
	if (stunRecoveryTime.miliDifference() > -(1000 + System::random(5000)))
		return;

	if (setState(CreatureState::STUNNED)) {
		playEffect("clienteffect/combat_special_defender_stun.cef");
		showFlyText("combat_effects", "go_stunned", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_stunned_single");

		stunRecoveryTime.update();
		stunRecoveryTime.addMiliTime(5000 + System::random(20000));
	}
}

void CreatureObjectImplementation::setBlindedState() {
	//TODO: remove this once npcs gets state defences
	if (stunRecoveryTime.miliDifference() > -(1000 + System::random(1000)))
		return;

	if (setState(CreatureState::BLINDED)) {
		playEffect("clienteffect/combat_special_defender_blind.cef");
		showFlyText("combat_effects", "go_blind", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_blind_single");

		blindRecoveryTime.update();
		blindRecoveryTime.addMiliTime(5000 + System::random(20000));
	}
}

void CreatureObjectImplementation::setIntimidatedState() {
	if (setState(CreatureState::INTIMIDATED)) {
		playEffect("clienteffect/combat_special_defender_intimidate.cef");
		showFlyText("combat_effects", "go_intimidated", 0, 0xFF, 0);

		int time = 15000 + System::random(5000);

		intimidateRecoveryTime.update();
		intimidateRecoveryTime.addMiliTime(time);
	}
}

void CreatureObjectImplementation::setSnaredState() {
	if (setState(CreatureState::SNARED)) {
		//playEffect("clienteffect/combat_special_defender_intimidate.cef");
		showFlyText("combat_effects", "go_snare", 0, 0xFF, 0);

		int time = 20000 + System::random(10000);

		snareRecoveryTime.update();
		snareRecoveryTime.addMiliTime(time);
	}
}

void CreatureObjectImplementation::setRootedState() {
	if (setState(CreatureState::ROOTED)) {
		//playEffect("clienteffect/combat_special_defender_intimidate.cef");
		showFlyText("combat_effects", "go_rooted", 0, 0xFF, 0);

		int time = 20000 + System::random(10000);

		rootRecoveryTime.update();
		rootRecoveryTime.addMiliTime(time);
	}
}

bool CreatureObjectImplementation::setNextAttackDelay(int del) {
	if (nextAttackDelayRecovery.isPast()) {
		nextAttackDelay.update();
		nextAttackDelay.addMiliTime(del);

		nextAttackDelayRecovery.update();
		nextAttackDelayRecovery.addMiliTime(30000+del);

		if (isPlayer()) {
			StringBuffer msg;
			msg << "You have been delayed for " << (del/1000) << " seconds.";
			sendSystemMessage(msg.toString());
		}

		return true;
	}
	return false;
}

void CreatureObjectImplementation::setMeditateState() {
	if (isInCombat())
		return;

	updateMood("meditating");
	setPosture(CreaturePosture::SITTING);
	setState(CreatureState::ALERT);
}

void CreatureObjectImplementation::setPoisonedState(int str, int type, int duration) {
	if (setState(CreatureState::POISONED)) {
		playEffect("clienteffect/dot_apply_poison.cef");
		sendSystemMessage("dot_message", "start_poisoned");

		poisonDotType = type;
		poisonDotStrength = str;

		poisonRecoveryTime.update();
		poisonRecoveryTime.addMiliTime(duration * 1000);
	}
}

void CreatureObjectImplementation::setOnFireState(int str, int type, int duration) {
	if (setState(CreatureState::ONFIRE)) {
		playEffect("clienteffect/dot_apply_fire.cef");
		sendSystemMessage("dot_message", "start_fire");

		fireDotType = type;
		fireDotStrength = str;

		fireRecoveryTime.update();
		fireRecoveryTime.addMiliTime(duration * 1000);
	}
}

void CreatureObjectImplementation::setBleedingState(int str, int type, int duration) {
	if (setState(CreatureState::BLEEDING)) {
		playEffect("clienteffect/dot_apply_bleeding.cef");
		sendSystemMessage("dot_message", "start_bleeding");

		bleedingDotType = type;
		bleedingDotStrength = str;

		bleedingRecoveryTime.update();
		bleedingRecoveryTime.addMiliTime(duration * 1000);

		nextBleedingTick.update();
	}
}

void CreatureObjectImplementation::setDiseasedState(int str, int type, int duration) {
	if (setState(CreatureState::DISEASED)) {
		playEffect("clienteffect/dot_apply_disease.cef");
		sendSystemMessage("dot_message", "start_diseased");

		diseaseDotType = type;
		diseaseDotStrength = str;

		diseasedRecoveryTime.update();
		diseasedRecoveryTime.addMiliTime(duration * 1000);
	}
}

void CreatureObjectImplementation::doPoisonTick() {
	if (nextPoisonTick.isPast()) {
		if (poisonDotType == 1)
			changeHealthBar(-poisonDotStrength);
		else if (poisonDotType == 4)
			changeActionBar(-poisonDotStrength);
		else
			changeMindBar(-poisonDotStrength);

		playEffect("clienteffect/dot_poisoned.cef");

		nextPoisonTick.update();
		nextPoisonTick.addMiliTime(9000);
	}
}

void CreatureObjectImplementation::doBleedingTick() {
	if (nextBleedingTick.isPast()) {
		if (bleedingDotType == 1)
			changeHealthBar(-bleedingDotStrength);
		else if (bleedingDotType == 4)
			changeActionBar(-bleedingDotStrength);
		else
			changeMindBar(-bleedingDotStrength);

		playEffect("clienteffect/dot_bleeding.cef");

		nextBleedingTick.update();
		nextBleedingTick.addMiliTime(9000);
	}
}

void CreatureObjectImplementation::doDiseaseTick() {
	if (nextDiseaseTick.isPast()) {

		if (diseaseDotType == 1)
			changeHealthWoundsBar(diseaseDotStrength + (shockWounds * diseaseDotStrength / 500));
		else if (diseaseDotType == 4)
			changeActionWoundsBar(diseaseDotStrength + (shockWounds * diseaseDotStrength / 500));
		else
			changeMindWoundsBar(diseaseDotStrength + (shockWounds * diseaseDotStrength / 500));

		changeShockWounds(1 + (shockWounds * diseaseDotStrength / 5000));

		playEffect("clienteffect/dot_diseased.cef");

		nextDiseaseTick.update();
		nextDiseaseTick.addMiliTime(9000);
	}
}

void CreatureObjectImplementation::doFireTick() {
	if (isOnFire() && hasState(CreatureState::SWIMMING)) {
		clearState(CreatureState::ONFIRE);
		return;
	}

	if (nextFireTick.isPast()) {
		if (fireDotType == 1){
			changeHealthWoundsBar((fireDotStrength / 5) + (shockWounds * fireDotStrength / 500));
			changeHealthBar(-fireDotStrength);
		} else if (fireDotType == 4) {
			changeActionWoundsBar((fireDotStrength / 5) + (shockWounds * fireDotStrength / 500));
			changeActionBar(-fireDotStrength);
		} else {
			changeMindWoundsBar((fireDotStrength / 5) + (shockWounds * fireDotStrength / 500));
			changeMindBar(-fireDotStrength);
		}

		changeShockWounds(1 + (shockWounds * fireDotStrength / 5000));

		playEffect("clienteffect/dot_fire.cef");

		nextFireTick.update();
		nextFireTick.addMiliTime(9000);
	}
}

bool CreatureObjectImplementation::setState(uint64 state) {
	if (!(stateBitmask & state)) {
		stateBitmask |= state;
		return true;
	} else
		return false;
}

bool CreatureObjectImplementation::clearState(uint64 state) {
	if (stateBitmask & state) {
		switch (state) {
		case CreatureState::STUNNED:
			sendSystemMessage("cbt_spam", "no_stunned_single");
			showFlyText("combat_effects", "no_stunned", 0xFF, 0, 0);
			break;
		case CreatureState::BLINDED:
			sendSystemMessage("cbt_spam", "no_blind_single");
			showFlyText("combat_effects", "no_blind", 0xFF, 0, 0);
			break;
		case CreatureState::DIZZY:
			sendSystemMessage("cbt_spam", "no_dizzy_single");
			showFlyText("combat_effects", "no_dizzy", 0xFF, 0, 0);
			break;
		case CreatureState::POISONED:
			sendSystemMessage("dot_message", "stop_poisoned");
			break;
		case CreatureState::DISEASED:
			sendSystemMessage("dot_message", "stop_diseased");
			break;
		case CreatureState::ONFIRE:
			sendSystemMessage("dot_message", "stop_fire");
			break;
		case CreatureState::BLEEDING:
			sendSystemMessage("dot_message", "stop_bleeding");
			break;
		case CreatureState::INTIMIDATED:
			showFlyText("combat_effects", "no_intimidated", 0xFF, 0, 0);
			break;
		case CreatureState::SNARED:
			showFlyText("combat_effects", "no_snare", 0xFF, 0, 0);
			break;
		case CreatureState::ROOTED:
			showFlyText("combat_effects", "no_rooted", 0xFF, 0, 0);
			break;
		default:
			break;
		}

		stateBitmask &= ~state;
		return true;
	} else
		return false;
}

void CreatureObjectImplementation::updateStates() {
	if (stateBitmask != oldStateBitmask) {
		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3);

		oldStateBitmask = stateBitmask;
	}
}

void CreatureObjectImplementation::updateMood(const String& md) {
	setMood(md);

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMoodStr();
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::clearStates() {
	stateBitmask = 0;
	nextAttackDelay.update();

	removeDefenders();

	updateStates();
}

bool CreatureObjectImplementation::takeHealthDamage(int32 damage) {
	int32 newHealth = health - damage;

	if (newHealth <= 0) {
		setHealthBar(0);
		doIncapacitate();
		return false;
	}

	setHealthBar(MIN(newHealth, getHealthMax() - getHealthWounds()));

	return true;
}

bool CreatureObjectImplementation::takeActionDamage(int32 damage) {
	int32 newAction = action - damage;

	if (newAction <= 0)	{
		setActionBar(0);
		doIncapacitate();
		return false;
	}

	setActionBar(MIN(newAction, getActionMax() - getActionWounds()));

	return true;
}

bool CreatureObjectImplementation::takeMindDamage(int32 damage) {
	int32 newMind = mind - damage;

	if (newMind <= 0) {
		setMindBar(0);
		doIncapacitate();
		return false;
	}

	setMindBar(MIN(newMind, getMindMax() - getMindWounds()));

	return true;
}

bool CreatureObjectImplementation::changeHAMBars(int32 hp, int32 ap, int32 mp, bool forcedChange) {
	int32 newHealth = health + hp;
	int32 newAction = action + ap;
	int32 newMind = mind + mp;

	if (isIncapacitated()) {
		if ((health == 0) && (newHealth > 0) && (action > 0) && (mind > 0))
			setPosture(CreaturePosture::UPRIGHT);

		if ((action == 0) && (newAction > 0) && (health > 0) && (mind > 0))
			setPosture(CreaturePosture::UPRIGHT);

		if ((mind == 0) && (newMind > 0) && (action > 0) && (health > 0))
			setPosture(CreaturePosture::UPRIGHT);
	}

	if (newHealth <= 0 || newAction <= 0 || newMind <= 0) {
		if (forcedChange) {
			setHAMBars(MAX(newHealth, 0), MAX(newAction, 0), MAX(newMind, 0));

			doIncapacitate();
		}

		return false;
	}

	setHAMBars(MIN(newHealth, healthMax - healthWounds), MIN(newAction, actionMax - actionWounds), MIN(newMind, mindMax - mindWounds));

	return true;
}

void CreatureObjectImplementation::changeMaxHAMBars(int32 hp, int32 ap, int32 mp) {
	int32 newMaxHealth = healthMax + hp;
	int32 newMaxAction = actionMax + ap;
	int32 newMaxMind = mindMax + mp;

	setMaxHAMBars(newMaxHealth, newMaxAction, newMaxMind);
}


bool CreatureObjectImplementation::changeHAMWounds(int32 hpwnds, int32 apwnds, int32 mpwnds, bool forcedChange) {
	int32 newHealthWounds = getHealthWounds() + hpwnds;
	int32 newActionWounds = getActionWounds() + apwnds;
	int32 newMindWounds = getMindWounds() + mpwnds;

	setHAMWoundsBars(MIN(newHealthWounds, getBaseHealth() - 1), MIN(newActionWounds, getBaseAction() - 1), MIN(newMindWounds, getBaseMind() - 1));

	return true;

}

bool CreatureObjectImplementation::changeHealthWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getHealthWounds())
		wounds = -1 * getHealthWounds();

	int32 newHealthWounds = getHealthWounds() + wounds;

	if (newHealthWounds >= getHealthMax()) {
		if (forcedChange) {
		} else {
			newHealthWounds = getHealthMax() - 1;
		}
	}

	setHealthWoundsBar(MIN(newHealthWounds, getBaseHealth() - 1));

	return true;
}

bool CreatureObjectImplementation::changeStrengthWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getStrengthWounds())
		wounds = -1 * getStrengthWounds();

	int32 newStrengthWounds = getStrengthWounds() + wounds;

	if (newStrengthWounds >= getStrengthMax()) {
		if (forcedChange) {
		} else {
			newStrengthWounds = getStrengthMax() - 1;
		}
	}

	setStrengthWoundsBar(MIN(newStrengthWounds, getBaseStrength() - 1));

	return true;
}

bool CreatureObjectImplementation::changeConstitutionWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getConstitutionWounds())
		wounds = -1 * getConstitutionWounds();

	int32 newConstitutionWounds = getConstitutionWounds() + wounds;

	if (newConstitutionWounds >= getConstitutionMax()) {
		if (forcedChange) {

		} else {
			newConstitutionWounds = getConstitutionMax() - 1;
		}
	}

	setConstitutionWoundsBar(MIN(newConstitutionWounds, getBaseConstitution() - 1));

	return true;
}

bool CreatureObjectImplementation::changeActionWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getActionWounds())
		wounds = -1 * getActionWounds();

	int32 newActionWounds = getActionWounds() + wounds;

	if (newActionWounds >= getActionMax()) {
		if (forcedChange) {
		} else {
			newActionWounds = getActionMax() - 1;
		}
	}

	setActionWoundsBar(MIN(newActionWounds, getBaseAction() - 1));

	return true;
}


bool CreatureObjectImplementation::changeQuicknessWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getQuicknessWounds())
		wounds = -1 * getQuicknessWounds();

	int32 newQuicknessWounds = getQuicknessWounds() + wounds;

	if (newQuicknessWounds >= getQuicknessMax()) {
		if (forcedChange) {
		} else {
			newQuicknessWounds = getQuicknessMax() - 1;
		}
	}

	setQuicknessWoundsBar(MIN(newQuicknessWounds, getBaseQuickness() - 1));

	return true;
}

bool CreatureObjectImplementation::changeStaminaWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getStaminaWounds())
		wounds = -1 * getStaminaWounds();

	int32 newStaminaWounds = getStaminaWounds() + wounds;

	if (newStaminaWounds >= getStaminaMax()) {
		if (forcedChange) {
		} else {
			newStaminaWounds = getStaminaMax() - 1;
		}
	}

	setStaminaWoundsBar(MIN(newStaminaWounds, getBaseStamina() - 1));

	return true;
}

bool CreatureObjectImplementation::changeMindWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getMindWounds())
		wounds = -1 * getMindWounds();

	int32 newMindWounds = getMindWounds() + wounds;

	if (newMindWounds >= getMindMax()) {
		if (forcedChange) {
		} else {
			newMindWounds = getMindMax() - 1;
		}
	}

	setMindWoundsBar(MIN(newMindWounds, getBaseMind() - 1));

	return true;
}


bool CreatureObjectImplementation::changeFocusWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getFocusWounds())
		wounds = -1 * getFocusWounds();

	int32 newFocusWounds = getFocusWounds() + wounds;

	if (newFocusWounds >= getFocusMax()) {
		if (forcedChange) {
		} else {
			newFocusWounds = getFocusMax() - 1;
		}
	}

	setFocusWoundsBar(MIN(newFocusWounds, getBaseFocus() - 1));

	return true;
}

bool CreatureObjectImplementation::changeWillpowerWoundsBar(int32 wounds, bool forcedChange) {
	if (wounds < 0 && -wounds > getWillpowerWounds())
		wounds = -1 * getWillpowerWounds();

	int32 newWillpowerWounds = getWillpowerWounds() + wounds;

	if (newWillpowerWounds >= getWillpowerMax()) {
		if (forcedChange) {
		} else {
			newWillpowerWounds = getWillpowerMax() - 1;
		}
	}

	setWillpowerWoundsBar(MIN(newWillpowerWounds, getBaseWillpower() - 1));

	return true;
}

bool CreatureObjectImplementation::changeHealthBar(int32 hp, bool forcedChange) {
	int32 newHealth = getHealth() + hp;

	if (newHealth <= 0) {
		if (forcedChange) {
			setHealthBar(0);
			doIncapacitate();
		}

		return false;
	}

	setHealthBar(MIN(newHealth, getHealthMax() - getHealthWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxHealthBar(int32 hp, bool updateClient) {
	if (hp == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxHealthBar(hp);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeHealthMax(hp);

	// bring down current stat to match max
	if (getHealth() > (getHealthMax() - getHealthWounds())) {
		if (updateClient)
			setHealthBar(getHealthMax() - getHealthWounds());
		else
			setHealth(getHealthMax() - getHealthWounds());
	}
}

bool CreatureObjectImplementation::changeStrengthBar(int32 st, bool forcedChange) {
	int32 newStrength = strength + st;

	if (newStrength <= 0) {
		if (forcedChange)
			setStrengthBar(1);

		return false;
	}

	setStrengthBar(MIN(newStrength, getStrengthMax() - getStrengthWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxStrengthBar(int32 st, bool updateClient) {
	if (st == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxStrengthBar(st);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeStrengthMax(st);

	// bring down current stat to match max
	if (updateClient)
		setStrengthBar(getStrengthMax() - getStrengthWounds());
	else
		setStrength(getStrengthMax() - getStrengthWounds());
}

bool CreatureObjectImplementation::changeConstitutionBar(int32 cs, bool forcedChange) {
	if (cs == 0)
		return true;

	int32 newConstitution = constitution + cs;

	if (newConstitution <= 0) {
		if (forcedChange) {
			setConstitutionBar(0);
		}

		return false;
	}

	setConstitutionBar(MIN(newConstitution, getConstitutionMax() - getConstitutionWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxConstitutionBar(int32 cs, bool updateClient) {
	if (cs == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxConstitutionBar(cs);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeConstitutionMax(cs);

	// bring down current stat to match max
	if (updateClient)
		setConstitutionBar(getConstitutionMax() - getConstitutionWounds());
	else
		setConstitution(getConstitutionMax() - getConstitutionWounds());
}

bool CreatureObjectImplementation::changeActionBar(int32 ap, bool forcedChange) {
	if (ap == 0)
		return true;

	int32 newAction = action + ap;

	if (newAction <= 0) {
		if (forcedChange) {
			setActionBar(0);
			doIncapacitate();
		}

		return false;
	}

	setActionBar(MIN(newAction, getActionMax() - getActionWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxActionBar(int32 ap, bool updateClient) {
	if (ap == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxActionBar(ap);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeActionMax(ap);

	// bring down current stat to match max
	if (getAction() > (getActionMax() - getActionWounds())) {
		if (updateClient)
			setActionBar(getActionMax() - getActionWounds());
		else
			setAction(getActionMax() - getActionWounds());
	}
}

bool CreatureObjectImplementation::changeQuicknessBar(int32 qc, bool forcedChange) {
	if (qc == 0)
		return true;

	int32 newQuickness = quickness + qc;

	if (newQuickness <= 0) {
		if (forcedChange) {
			setQuicknessBar(0);
		}

		return false;
	}

	setQuicknessBar(MIN(newQuickness, getQuicknessMax() - getQuicknessWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxQuicknessBar(int32 qc, bool updateClient) {
	if (qc == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxQuicknessBar(qc);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeQuicknessMax(qc);

	// bring down current stat to match max
	if (updateClient)
		setQuicknessBar(getQuicknessMax() - getQuicknessWounds());
	else
		setQuickness(getQuicknessMax() - getQuicknessWounds());
}

bool CreatureObjectImplementation::changeStaminaBar(int32 st, bool forcedChange) {
	if (st == 0)
		return true;

	int32 newStamina = stamina + st;

	if (newStamina <= 0) {
		if (forcedChange) {
			setStaminaBar(0);
		}

		return false;
	}

	setStaminaBar(MIN(newStamina, getStaminaMax() - getStaminaWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxStaminaBar(int32 st, bool updateClient) {
	if (st == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxStaminaBar(st);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeStaminaMax(st);

	// bring down current stat to match max
	if (updateClient)
		setStaminaBar(getStaminaMax() - getStaminaWounds());
	else
		setStamina(getStaminaMax() - getStaminaWounds());
}

bool CreatureObjectImplementation::changeMindBar(int32 mp, bool forcedChange) {
	if (mp == 0)
		return true;

	int32 newMind = mind + mp;

	if (newMind <= 0) {
		if (forcedChange) {
			setMindBar(0);
			doIncapacitate();
		}

		return false;
	}

	setMindBar(MIN(newMind, getMindMax() - getMindWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxMindBar(int32 mp, bool updateClient) {
	if (mp == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxMindBar(mp);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeMindMax(mp);

	// bring down current stat to match max
	if (getMind() > (getMindMax() - getMindWounds())) {
		if (updateClient)
			setMindBar(getMindMax() - getMindWounds());
		else
			setMind(getMindMax() - getMindWounds());
	}
}

bool CreatureObjectImplementation::changeFocusBar(int32 fc, bool forcedChange) {
	if (fc == 0)
		return true;

	int32 newFocus = focus + fc;

	if (newFocus <= 0) {
		if (forcedChange) {
			setFocusBar(0);
		}

		return false;
	}

	setFocusBar(MIN(newFocus, getFocusMax() - getFocusWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxFocusBar(int32 fc, bool updateClient) {
	if (fc == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxFocusBar(fc);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeFocusMax(fc);

	// bring down current stat to match max
	if (updateClient)
		setFocusBar(getFocusMax() - getFocusWounds());
	else
		setFocus(getFocusMax() - getFocusWounds());
}

bool CreatureObjectImplementation::changeWillpowerBar(int32 wl, bool forcedChange) {
	if (wl == 0)
		return true;

	int32 newWillpower = willpower + wl;

	if (newWillpower <= 0) {
		if (forcedChange) {
			setWillpowerBar(0);
		}

		return false;
	}

	setWillpowerBar(MIN(newWillpower, getWillpowerMax() - getWillpowerWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxWillpowerBar(int32 wl, bool updateClient) {
	if (wl == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxWillpowerBar(wl);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeWillpowerMax(wl);

	// willpower should always be whatever max - wounds is
	if (updateClient)
		setWillpowerBar(getWillpowerMax() - getWillpowerWounds());
	else
		setWillpower(getWillpowerMax() - getWillpowerWounds());
}

void CreatureObjectImplementation::changeShockWounds(int bf) {
	shockWounds += bf;

	if ((int)shockWounds < 0)
		shockWounds = 0;
	else if (shockWounds > 1000)
		shockWounds = 1000;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateShockWounds();
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::changeConditionDamage(int amount) {
	conditionDamage += amount;

	if (conditionDamage > maxCondition)
		conditionDamage = maxCondition;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3((CreatureObject*) _this);

	dcreo3->updateConditionDamage();
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::setMaxCondition(int condition) {
	maxCondition = condition;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3((CreatureObject*) _this);
	if (conditionDamage > maxCondition){
		conditionDamage = maxCondition;
		dcreo3->updateConditionDamage();
	}
	dcreo3->updateMaxCondition();
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::resetHAMBars(bool doUpdateClient) {
	setHealthMax(getBaseHealth());
	setStrengthMax(getBaseStrength());
	setConstitutionMax(getBaseConstitution());

	setActionMax(getBaseAction());
	setQuicknessMax(getBaseQuickness());
	setStaminaMax(getBaseStamina());

	setMindMax(getBaseMind());
	setFocusMax(getBaseFocus());
	setWillpowerMax(getBaseWillpower());

	if (getHealthWounds() > getHealthMax()) {
		setHealthWounds(getHealthMax() - 1);
	}

	if (getActionWounds() > getActionMax())
		setActionWounds(getActionMax() - 1);

	if (getMindWounds() > getMindMax())
		setMindWounds(getMindMax() - 1);

	setHealth(getHealthMax() - getHealthWounds());
	setStrength(getStrengthMax() - getStrengthWounds());
	setConstitution(getConstitutionMax() - getConstitutionWounds());

	setAction(getActionMax() - getActionWounds());
	setQuickness(getQuicknessMax() - getQuicknessWounds());
	setStamina(getStaminaMax() - getStaminaWounds());

	setMind(getMindMax() - getMindWounds());
	setFocus(getFocusMax() - getFocusWounds());
	setWillpower(getWillpowerMax() - getWillpowerWounds());

	if (doUpdateClient)
		updateHAMBars();
}


void CreatureObjectImplementation::setBaseHealthBar(uint32 hp, bool updateClient) {
	if (hp == getBaseHealth())
		return;

	uint32 originalBaseHealth = getBaseHealth();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseHealthBar(hp);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseHealth(hp);

	// Change the Max Health to reflect new Base Health
	setHealthBar(getHealth() + (hp - originalBaseHealth));
	setMaxHealthBar(getHealthMax() + (hp - originalBaseHealth), updateClient);

}

void CreatureObjectImplementation::setBaseStrengthBar(uint32 st, bool updateClient) {
	if (st == getBaseStrength())
		return;

	uint32 originalBaseStrength = getBaseStrength();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseStrengthBar(st);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseStrength(st);

	// Change the Max Strength to reflect new Base Strength
	setStrengthBar(getStrength() + (st - originalBaseStrength));
	setMaxStrengthBar(getStrengthMax() + (st - originalBaseStrength), updateClient);
}
void CreatureObjectImplementation::setBaseConstitutionBar(uint32 cst, bool updateClient) {
	if (cst == getBaseConstitution())
		return;

	uint32 originalBaseConstitution = getBaseConstitution();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseConstitutionBar(cst);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseConstitution(cst);

	// Change the Max Constitution to reflect new Base Constitution
	setConstitutionBar(getConstitution() + (cst - originalBaseConstitution));
	setMaxConstitutionBar(getConstitutionMax() + (cst - originalBaseConstitution), updateClient);
}

void CreatureObjectImplementation::setBaseActionBar(uint32 ap, bool updateClient) {
	if (ap == getBaseAction())
		return;

	uint32 originalBaseAction = getBaseAction();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseActionBar(ap);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseAction(ap);

	// Change the Max Action to reflect new Base Action
	setActionBar(getAction() + (ap - originalBaseAction));
	setMaxActionBar(getActionMax() + (ap - originalBaseAction), updateClient);
}

void CreatureObjectImplementation::setBaseQuicknessBar(uint32 qck, bool updateClient) {
	if (qck == getBaseQuickness())
		return;

	uint32 originalBaseQuickness = getBaseQuickness();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseQuicknessBar(qck);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseQuickness(qck);

	// Change the Max Quickness to reflect new Base Quickness
	setQuicknessBar(getQuickness() + (qck - originalBaseQuickness));
	setMaxQuicknessBar(getQuicknessMax() + (qck - originalBaseQuickness), updateClient);
}

void CreatureObjectImplementation::setBaseStaminaBar(uint32 sta, bool updateClient) {
	if (sta == getBaseStamina())
		return;

	uint32 originalBaseStamina = getBaseStamina();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseStaminaBar(sta);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseStamina(sta);

	// Change the Max Stamina to reflect new Base Stamina
	setStaminaBar(getStamina() + (sta - originalBaseStamina));
	setMaxStaminaBar(getStaminaMax() + (sta - originalBaseStamina), updateClient);
}

void CreatureObjectImplementation::setBaseMindBar(uint32 mp, bool updateClient) {
	if (mp == getBaseMind())
		return;

	uint32 originalBaseMind = getBaseMind();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseMindBar(mp);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseMind(mp);

	// Change the Max Mind to reflect new Base Mind
	setMindBar(getMind() + (mp - originalBaseMind));
	setMaxMindBar(getMindMax() + (mp - originalBaseMind), updateClient);
}

void CreatureObjectImplementation::setBaseFocusBar(uint32 fc, bool updateClient) {
	if (fc == getBaseFocus())
		return;

	uint32 originalBaseFocus = getBaseFocus();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseFocusBar(fc);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseFocus(fc);

	// Change the Max Focus to reflect new Base Focus
	setFocusBar(getFocus() + (fc - originalBaseFocus));
	setMaxFocusBar(getFocusMax() + (fc - originalBaseFocus), updateClient);
}

void CreatureObjectImplementation::setBaseWillpowerBar(uint32 will, bool updateClient) {
	if (will == getBaseWillpower())
		return;

	uint32 originalBaseWillpower = getBaseWillpower();

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseWillpowerBar(will);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseWillpower(will);

	// Change the Max Willpower to reflect new Base Willpower
	setWillpowerBar(getWillpower() + (will - originalBaseWillpower));
	setMaxWillpowerBar(getWillpowerMax() + (will - originalBaseWillpower), updateClient);
}

void CreatureObjectImplementation::setHAMBars(uint32 hp, uint32 ap, uint32 mp) {
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);

	dcreo6->updatePrimaryBars(hp, ap, mp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setHAMWoundsBars(uint32 hpwnds, uint32 acwnds, uint32 mpwnds) {
	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);

	dcreo3->updateHAMWoundsBars(hpwnds, acwnds, mpwnds);
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::setHealthBar(uint32 hp) {
	if (hp == getHealth())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateHealthBar(hp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxHealthBar(uint32 hp, bool updateClient) {
	if (hp == getHealthMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxHealthBar(hp);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setHealthMax(hp);

	// bring down current stat to match max
	if (getHealth() > (getHealthMax() - getHealthWounds())) {
		if (updateClient)
			setHealthBar(getHealthMax() - getHealthWounds());
		else
			setHealth(getHealthMax() - getHealthWounds());
	}
}

void CreatureObjectImplementation::setHealthWoundsBar(uint32 wounds) {
	if (wounds == getHealthWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateHealthWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setHealthBar(MIN(getHealth(), getHealthMax() - getHealthWounds()));
	if (getHealth() < getHealthMax())
		activateRecovery();
}

void CreatureObjectImplementation::setStrengthBar(uint32 st) {
	if (st == getStrength())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateStrengthBar(st);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxStrengthBar(uint32 st, bool updateClient) {
	if (st == getStrengthMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxStrengthBar(st);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setStrengthMax(st);

	// bring down current stat to match max
	if (updateClient)
		setStrengthBar(getStrengthMax() - getStrengthWounds());
	else
		setStrength(getStrengthMax());
}

void CreatureObjectImplementation::setStrengthWoundsBar(uint32 wounds) {
	if (wounds == getStrengthWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateStrengthWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setQuicknessBar(getStrengthMax() - getStrengthWounds());
}

void CreatureObjectImplementation::setConstitutionBar(uint32 cst) {
	if (cst == getConstitution())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateConstitutionBar(cst);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxConstitutionBar(uint32 cst, bool updateClient) {
	if (cst == getConstitutionMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxConstitutionBar(cst);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setConstitutionMax(cst);

	// bring down current stat to match max
	if (updateClient)
		setConstitutionBar(getConstitutionMax() - getConstitutionWounds());
	else
		setConstitution(getConstitutionMax() - getConstitutionWounds());
}

void CreatureObjectImplementation::setConstitutionWoundsBar(uint32 wounds) {
	if (wounds == getConstitutionWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateConstitutionWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setConstitutionBar(getConstitutionMax() - getConstitutionWounds());
}

void CreatureObjectImplementation::setActionBar(uint32 ap) {
	if (ap == getAction())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateActionBar(ap);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxActionBar(uint32 ap, bool updateClient) {
	if (ap == getActionMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxActionBar(ap);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setActionMax(ap);

	// bring down current stat to match max
	if (getAction() > (getActionMax() - getActionWounds())) {
		if (updateClient)
			setActionBar(getActionMax() - getActionWounds());
		else
			setAction(getActionMax() - getActionWounds());
	}
}

void CreatureObjectImplementation::setActionWoundsBar(uint32 wounds) {
	if (wounds == getActionWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateActionWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setActionBar(MIN(getAction(), getActionMax() - getActionWounds()));
	if (getAction() < getActionMax())
		activateRecovery();
}

void CreatureObjectImplementation::setQuicknessBar(uint32 qck) {
	if (qck == getQuickness())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateQuicknessBar(qck);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxQuicknessBar(uint32 qck, bool updateClient) {
	if (qck == getQuicknessMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxQuicknessBar(qck);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setQuicknessMax(qck);

	// bring down current stat to match max
	if (updateClient)
		setQuicknessBar(getQuicknessMax() - getQuicknessWounds());
	else
		setQuickness(getQuicknessMax() - getQuicknessWounds());
}

void CreatureObjectImplementation::setQuicknessWoundsBar(uint32 wounds) {
	if (wounds == getQuicknessWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateQuicknessWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setQuicknessBar(getQuicknessMax() - getQuicknessWounds());
}

void CreatureObjectImplementation::setStaminaBar(uint32 sta) {
	if (sta == getStamina())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateStaminaBar(sta);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxStaminaBar(uint32 sta, bool updateClient) {
	if (sta == getStaminaMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxStaminaBar(sta);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setStaminaMax(sta);

	// bring down current stat to match max
	if (updateClient)
		setStaminaBar(getStaminaMax() - getStaminaWounds());
	else
		setStamina(getStaminaMax() - getStaminaWounds());
}

void CreatureObjectImplementation::setStaminaWoundsBar(uint32 wounds) {
	if (wounds == getStaminaWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateStaminaWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setStaminaBar(getStaminaMax() - getStaminaWounds());
}

void CreatureObjectImplementation::setMindBar(uint32 mp) {
	if (mp == getMind())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMindBar(mp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxMindBar(uint32 mp, bool updateClient) {
	if (mp == getMindMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxMindBar(mp);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setMindMax(mp);

	// bring down current stat to match max
	if (getMind() > (getMindMax() - getMindWounds()))
	{
		if (updateClient)
			setMindBar(getMindMax() - getMindWounds());
		else
			setMind(getMindMax() - getMindWounds());
	}
}

void CreatureObjectImplementation::setMindWoundsBar(uint32 wounds) {
	if (wounds == getMindWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateMindWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setMindBar(MIN(getMind(), getMindMax() - getMindWounds()));
	if (getMind() < getMindMax())
		activateRecovery();
}

void CreatureObjectImplementation::setFocusBar(uint32 fc) {
	if (fc == getFocus())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateFocusBar(fc);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxFocusBar(uint32 fc, bool updateClient) {
	if (fc == getFocusMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxFocusBar(fc);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setFocusMax(fc);

	// bring down current stat to match max
	if (updateClient)
		setFocusBar(getFocusMax() - getFocusWounds());
	else
		setFocus(getFocusMax() - getFocusWounds());
}

void CreatureObjectImplementation::setFocusWoundsBar(uint32 wounds) {
	if (wounds == getFocusWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateFocusWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setFocusBar(getFocusMax() - getFocusWounds());
}

void CreatureObjectImplementation::setWillpowerBar(uint32 will) {
	if (will == getWillpower())
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateWillpowerBar(will);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxWillpowerBar(uint32 will, bool updateClient) {
	if (will == getWillpowerMax())
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxWillpowerBar(will);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setWillpowerMax(will);

	// bring down current stat to match max
	if (updateClient)
		setWillpowerBar(getWillpowerMax() - getWillpowerWounds());
	else
		setWillpower(getWillpowerMax() - getWillpowerWounds());
}

void CreatureObjectImplementation::setWillpowerWoundsBar(uint32 wounds) {
	if (wounds == getWillpowerWounds())
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateWillpowerWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	setWillpowerBar(getWillpowerMax() - getWillpowerWounds());
}

void CreatureObjectImplementation::setMaxHAMBars(uint32 hp, uint32 ap, uint32 mp) {
	/*healthMax = hp;
	actionMax = ap;
	mindMax = mp;*/

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaximumPrimaryBars(hp, ap, mp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::calculateHAMregen() {
	if ((int) getConstitution() < 0 || (int) getStamina() < 0 || (int) getWillpower() < 0)
		return;

	if (!(objectType == PLAYER) && isInCombat()) {  // Creatures don't regen HAM in combat
		return;
	}

	float newHealth = (float)getConstitution() * 13 / 1200 * 3;
	float newAction = (float)getStamina() * 13 / 1200 * 3;
	float newMind = (float)getWillpower() * 13 / 1200 * 3;

	if (doListening || doWatching) {
		if (shockWounds != 0 && System::random(1) == 1)
			changeShockWounds(-System::random(3)-1);
	}

	if (isMeditating()) {
		int meditateMod = getSkillMod("meditate");
		float meditateBonus = 1 + ((float)meditateMod / 100);
		newHealth *= meditateBonus;
		newAction *= meditateBonus;
		newMind *= meditateBonus;
		doMeditateHeals();
	}

	if (isPlayer()) {
		Player* player = (Player*)_this;
		if (player->getPowerboosted() && pbMind != 0) {
			doPowerboostTick(player);
		}
	}

	if (postureState == CreaturePosture::SITTING) {
		bool change = changeHAMBars((int)newHealth, (int)newAction, (int)newMind);
	} else if (postureState == CreaturePosture::CROUCHED) {
		newHealth = newHealth * 5 / 7;
		newAction = newAction  * 5 / 7;
		newMind = newMind * 5 / 7;

		bool change = changeHAMBars((int)newHealth, (int)newAction, (int)newMind);
	} else {
		newHealth = newHealth * 4 / 7;
		newAction = newAction  * 4 / 7;
		newMind = newMind * 4 / 7;

		bool change = changeHAMBars((int)newHealth, (int)newAction, (int)newMind);
	}
}

void CreatureObjectImplementation::doMeditateHeals() {
	int meditateMod = getSkillMod("meditate");

    //Heal dots first.
	if (isBleeding() || isPoisoned() || isDiseased()) {

		switch (0) {
		case 0:
			if (isBleeding() && meditateMod >= 15) {
				bleedingDotStrength -= 20 + (meditateMod / 3);
				if (bleedingDotStrength < 1) {
					bleedingDotStrength = 0;
					clearState(CreatureState::BLEEDING);
				} else {
					if (isPlayer())
						sendSystemMessage("dot_message", "decrease_bleeding");
				}
				return;
			}

		case 1:
			if (isPoisoned() && meditateMod >= 30) {
				poisonDotStrength -= 20 + (meditateMod / 3);
				if (poisonDotStrength < 1) {
					poisonDotStrength = 0;
					clearState(CreatureState::POISONED);
				} else {
					if (isPlayer())
						sendSystemMessage("dot_message", "decrease_poisoned");
				}
				return;
			}

		case 2:
			if (isDiseased() && meditateMod >= 45) {
				diseaseDotStrength -= 20 + (meditateMod / 3);
				if (diseaseDotStrength < 1) {
					diseaseDotStrength = 0;
					clearState(CreatureState::DISEASED);
				} else {
					if (isPlayer())
						sendSystemMessage("dot_message", "decrease_diseased");
				}
				return;
			}
		}
	}

    //If no more dots can be healed, heal wounds.
	if (meditateMod >= 75) {
		doMeditateWoundHeals();
	}
}

void CreatureObjectImplementation::doMeditateWoundHeals() {
	int heal;
	int wounds;
	int meditateMod = getSkillMod("meditate");
	String attribute;
	StfParameter* healParams = new StfParameter;
	Vector<uint8> woundedPools;

	//Determine which pools are wounded.
	for (uint8 i = 1; i < 10; i++) {
		bool hasWounds = hasWound(i);
		if (hasWounds == true) {
			woundedPools.add(i);
		}
	}

	if (woundedPools.size() == 0) {
		return;
	}

    //Set the heal amount.
	if (meditateMod > 0 && meditateMod < 100) {
		 heal = 20 + System::random(10);
	} else if (meditateMod >= 100) {
		heal = 30 + System::random(20);
	} else {
		return;
	}

	//Heal a random wounded pool.
    uint8 pool = woundedPools.get(System::random(woundedPools.size() - 1));

    switch (pool) {
    case 1:
    	wounds = getHealthWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
    	attribute = "Health";
    	changeHealthWoundsBar(-heal);
    	break;

    case 2:
        wounds = getStrengthWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Strength";
        changeStrengthWoundsBar(-heal);
        break;

    case 3:
        wounds = getConstitutionWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Constitution";
        changeConstitutionWoundsBar(-heal);
        break;

    case 4:
        wounds = getActionWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Action";
        changeActionWoundsBar(-heal);
        break;

    case 5:
        wounds = getQuicknessWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Quickness";
        changeQuicknessWoundsBar(-heal);
        break;

    case 6:
        wounds = getStaminaWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Stamina";
        changeStaminaWoundsBar(-heal);
        break;

    case 7:
        wounds = getMindWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Mind";
        changeMindWoundsBar(-heal);
        break;

    case 8:
        wounds = getFocusWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Focus";
        changeFocusWoundsBar(-heal);
        break;

    case 9:
        wounds = getWillpowerWounds();
        if (wounds < heal) {
    		heal = wounds;
        }
        attribute = "Willpower";
        changeWillpowerWoundsBar(-heal);
        break;
    }

    //Send heal message.
	if (isPlayer()) {
		Player* player = (Player*)_this;
		healParams->addTO(attribute);
        healParams->addDI(heal);
		player->sendSystemMessage("teraskasi","prose_curewound",healParams);
		delete healParams;
	}
}

void CreatureObjectImplementation::doPowerboostTick(Player* player) {
    //Update the tick counter.
	pbCounter++;

	//Change the Max Health & Action.
	if (pbHA != 0) {
		if (pbCounter >= 20) {
			changeMaxHealthBar(pbHA);
			changeMaxActionBar(pbHA);
			pbHA = 0;

		} else {
			changeMaxHealthBar(pbTick);
			changeMaxActionBar(pbTick);
			pbHA -= pbTick;
		}
	}

	//Change the Max Mind.
	if (pbMind > 0) { //Deal with positive values.
		if (pbCounter >= 40) {
			changeMaxMindBar(pbMind);
			pbMind = 0;
			pbCounter = 0;
		} else {
			changeMaxMindBar(pbTick);
			pbMind -= pbTick;
		}

	} else if (pbMind < 0) { //Deal with negative values.
		if (pbCounter >= 20) {
			changeMaxMindBar(pbMind);
			pbMind = 0;
			pbCounter = 0;
			player->sendSystemMessage("teraskasi", "powerboost_end");
			player->setPowerboosted(false);
		} else {
			changeMaxMindBar(pbTick);
			pbMind -= pbTick;
		}
	}
	//System::out << "pbHA = " << pbHA << " pbMind = " << pbMind << " pbBonus = " << pbBonus << " pbTick = " << pbTick << " pbCounter = " << pbCounter << endl;
}

void CreatureObjectImplementation::removePowerboost() {
	//Remove health & action bonuses.
	if (pbHA > 0) {
		changeMaxHealthBar(-(pbBonus - pbHA));
		changeMaxActionBar(-(pbBonus - pbHA));
		pbHA = 0;
	} else if (pbHA < 0) {
		changeMaxHealthBar(pbHA);
		changeMaxActionBar(pbHA);
		pbHA = 0;
	} else {
		changeMaxHealthBar(-pbBonus);
		changeMaxActionBar(-pbBonus);
	}

	//Remove mind bonus.
	if (pbMind > 0) {
		changeMaxMindBar(-(pbBonus - pbMind));
		pbMind = 0;
	} else if (pbMind < 0) {
		changeMaxMindBar(pbMind);
		pbMind = 0;
	} else {
		changeMaxMindBar(-pbBonus);
	}
	pbCounter = 0;
}

void CreatureObjectImplementation::activateBurstRun() {
	//TODO: Burst run had HAM costs - but i can't find any documentation HOW MUCH...

	if (isMounted() ||
			isDizzied() ||
			isKnockedDown() ||
			isMeditating() ||
			postureState != CreaturePosture::UPRIGHT) {

		sendSystemMessage("@combat_effects:burst_run_no");

		return;
	}

	if (!burstRunCooldown.isPast() && isPlayer()) {
		int left = -(burstRunCooldown.miliDifference() / 1000);
		int min = left / 60;
		int seconds = left % 60;
		StringBuffer msg;
		msg << "You must wait " << min << " minutes and " << seconds << " seconds to perform this action.";
		((PlayerImplementation*) this)->sendSystemMessage(msg.toString());
		return;
	}

	if (isPlayer() && speed > 5.376f) {
		UnicodeString msg = UnicodeString("You are already running.");
		((PlayerImplementation*) this)->sendSystemMessage(msg);

		return;
	}

	speed = 8.0f;
	acceleration = 0.922938f;

	if (isPlayer()) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

		dcreo4->updateSpeed();
		dcreo4->updateAcceleration();
		dcreo4->close();

		((PlayerImplementation*) this)->sendMessage(dcreo4);

		Event* e = new CreatureBurstRunOverEvent(this);
		server->addEvent(e);

		((PlayerImplementation*) this)->sendSystemMessage("cbt_spam", "burstrun_start_single");
	}
}

void CreatureObjectImplementation::deactivateBurstRun() {
	if (speed <= 5.376) {
		burstRunCooldown.update();
		burstRunCooldown.addMiliTime(900000);

		return;
	}

	speed = 5.376f;
	acceleration = 1.549f;

	burstRunCooldown.update();
	burstRunCooldown.addMiliTime(900000);

	if (isPlayer()) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
		dcreo4->updateSpeed();
		dcreo4->updateAcceleration();
		dcreo4->close();

		PlayerImplementation* player = (PlayerImplementation*) this;
		player->sendMessage(dcreo4);

		((PlayerImplementation*) this)->sendSystemMessage("cbt_spam", "burstrun_stop_single");
	}
}

void CreatureObjectImplementation::updateSpeed(float speed, float acceleration) {
	setIgnoreMovementTests(10);

	CreatureObjectImplementation::speed = speed;
	CreatureObjectImplementation::acceleration = acceleration;

	if (isPlayer()) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

		dcreo4->updateSpeed();
		dcreo4->updateAcceleration();
		dcreo4->updateTerrainNegotiation();
		dcreo4->close();

		((PlayerImplementation*) this)->sendMessage(dcreo4);
	}
}


void CreatureObjectImplementation::updateTarget(uint64 targ) {
	SceneObject* target = zone->lookupObject(targ);

	if (target != targetObject) {
		if (targetObject != NULL)
			info("released target");

		targetObject = target;

		if (targetObject == NULL)
			return;

		info("updating target");

		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateTarget();
		dcreo6->close();

		broadcastMessage(dcreo6);
	}
}

void CreatureObjectImplementation::updateTarget(SceneObject* targ) {
	if (targetObject != targ) {
		if (targetObject != NULL)
			info("releasing target");

		targetObject = targ;

		info("updating target");

		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateTarget();

		/*if (isInCombat())
			dcreo6->updateDefender();*/

		dcreo6->close();

		broadcastMessage(dcreo6);
	}
}

void CreatureObjectImplementation::clearTarget() {
	if (targetObject != NULL) {
		info("releasing target");

		targetObject = NULL;
	}
}

void CreatureObjectImplementation::equipItem(TangibleObject* item) {
	if (item->isEquipped())
		return;

	item->setEquipped(true);
	item->setContainer(_this, 0x04);
	item->setParent(_this);

	item->setUpdated(true);

	try {
		zone->lock();

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());
			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (player->isOnline())
					item->sendTo(player);
			}
		}

		zone->unlock();
	} catch (...) {
		error("Unreported Exception in CreatureObjectImplementation::equipItem");
		zone->unlock();
	}
}

void CreatureObjectImplementation::unequipItem(TangibleObject* item) {
	if (!item->isEquipped())
		return;

	if (item->isInstrument() && isPlayingMusic())
        stopPlayingMusic();

	item->setEquipped(false);
	item->setContainer(inventory, 0xFFFFFFFF);
	item->setParent(inventory);

	item->setUpdated(true);

	BaseMessage* linkmsg = item->link(inventory);
	broadcastMessage(linkmsg);
}

uint64 CreatureObjectImplementation::getTargetID() {
	if (targetObject != NULL)
		return targetObject->getObjectID();
	else
		return 0;
}

uint64 CreatureObjectImplementation::getWeaponID() {
	if (weaponObject != NULL)
		return weaponObject->getObjectID();
	else
		return 0;
}

Instrument* CreatureObjectImplementation::getInstrument() {
	if (inventory == NULL)
		return NULL;

	for (int i=0; i < inventory->objectsSize(); i++) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);

		if (item->isInstrument() && item->isEquipped())
				return (Instrument*) item;
	}

	return NULL;
}

Armor* CreatureObjectImplementation::getArmor(int type) {
	if (inventory == NULL)
		return NULL;

	for (int i=0; i < inventory->objectsSize(); i++) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);

		if (item->isArmor()) {
			if (((Armor*) item)->getType() == type && item->isEquipped())
				return (Armor*) item;
		}
	}

	return NULL;
}

void CreatureObjectImplementation::addInventoryItem(TangibleObject* item) {
	if (item->isEquipped() && item->isWeapon()) {
		item->setContainer(_this, 0x04);
		setWeapon((Weapon*) item);
	} else
		item->setContainer(inventory, 0xFFFFFFFF);

	inventory->addObject(item);
}

void CreatureObjectImplementation::addInventoryResource(ResourceContainer* rcno) {

	bool makeNewResource = true;

	ResourceContainer* inventoryResource;

	Player* player = (Player*)_this;
	if (player == NULL)
		return;

	for (int i = 0; i < inventory->objectsSize(); i++) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);
		if (item != NULL && item->isResource()) {
			inventoryResource = (ResourceContainer*) item;

			try {

				inventoryResource->wlock();

				if (inventoryResource->compare(rcno)
						&& inventoryResource->getContents()
								< inventoryResource->getMaxContents()) {

					if (inventoryResource->getContents()
							+ rcno->getContents()
							<= inventoryResource->getMaxContents()) {

						inventoryResource->transferContents(player, rcno);

						makeNewResource = false;

						inventoryResource->unlock();

						return;

						break;
					} else {

						int diff = (inventoryResource->getContents()
								+ rcno->getContents())
								- inventoryResource->getMaxContents();

						inventoryResource->setContents(
								inventoryResource->getMaxContents());

						rcno->setContents(diff);

						inventoryResource->sendDeltas(player);

						inventoryResource->setUpdated(true);
					}
				}
				inventoryResource->unlock();
			} catch (...) {

				inventoryResource->unlock();

			}
		}
	}

	if (makeNewResource) {
		// NOTE: Figure out how to get max inventory size...
		if (inventory->getUnequippedItemCount() + 1 > InventoryImplementation::MAXUNEQUIPPEDCOUNT) {
			ChatSystemMessage* sysMessage =
					new ChatSystemMessage("survey", "no_inv_spc");
			player->sendMessage(sysMessage);
			return;
		}

		rcno->setContainer(inventory, 0xFFFFFFFF);

		inventory->addObject(rcno);

		rcno->sendTo(player);

		rcno->setPersistent(false);

	}
}

SceneObject* CreatureObjectImplementation::getInventoryItem(uint64 oid) {
	return (TangibleObject*) inventory->getObject(oid);
}

void CreatureObjectImplementation::removeAllInventoryByMisoKey(String& mkey) {
	inventory->removeAllByMisoKey(_this, mkey);
}

TangibleObject* CreatureObjectImplementation::getItemByMisoKey(String& tma) {
	return inventory->getItemByMisoKey(tma);
}

void CreatureObjectImplementation::removeInventoryItem(SceneObject* item) {
	inventory->removeObject(item->getObjectID());
}

void CreatureObjectImplementation::removeInventoryItem(uint64 oid) {
	inventory->removeObject(oid);
}

void CreatureObjectImplementation::addLootItem(TangibleObject* item) {

	item->setContainer(lootContainer, 0xFFFFFFFF);

	lootContainer->addObject(item);
}

TangibleObject* CreatureObjectImplementation::getLootItem(uint64 oid) {
	if (lootContainer != NULL)
		return (TangibleObject*) lootContainer->getObject(oid);
	else
		return NULL;
}

void CreatureObjectImplementation::removeLootItem(SceneObject* item) {
	lootContainer->removeObject(item->getObjectID());
}

void CreatureObjectImplementation::removeLootItem(uint64 oid) {
	lootContainer->removeObject(oid);
}


void CreatureObjectImplementation::addSkills(Vector<Skill*>& skills, bool updateClient) {
	if (!isPlayer())
		return;

	PlayerObjectDeltaMessage9* dplay9;
	PlayerObject* player = ((PlayerImplementation*) this)->getPlayerObject();

	if (updateClient) {
		dplay9 = new PlayerObjectDeltaMessage9(player);
		dplay9->startSkillListUpdate(skills.size());
	}

	for (int i = 0; i < skills.size(); i++) {
		Skill* skill = skills.get(i);
		if (!creatureSkills.contains(skill->getNameCRC()))
			creatureSkills.put(skill->getNameCRC(), skill);

		if (updateClient)
			dplay9->addSkill(skill->getSkillName());
	}

	if (updateClient) {
		dplay9->close();
		((PlayerImplementation*) this)->sendMessage(dplay9);
	}
}

void CreatureObjectImplementation::removeSkills(Vector<Skill*>& skills, bool updateClient) {
	for (int i = 0; i < skills.size(); i++) {
		Skill* skill = skills.get(i);
		creatureSkills.drop(skill->getNameCRC());
	}

	if (updateClient) {
		PlayerObject* player = ((PlayerImplementation*)this)->getPlayerObject();

		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player);
		dplay9->updateSkilsAndCertifications();
		dplay9->close();

		((PlayerImplementation*) this)->sendMessage(dplay9);
	}
}

void CreatureObjectImplementation::addSkillMod(const String& name, int mod, bool updateClient) {
	if (creatureSkillMods.containsKey(name)) {
		mod += creatureSkillMods.get(name);

		if (mod <= 0) {
			removeSkillMod(name, updateClient);
			return;
		}

		creatureSkillMods.remove(name);
	}

	creatureSkillMods.put(name, mod);

	if (updateClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

		dcreo4->startSkillModsUpdate(1);
		dcreo4->addSkillMod(name, mod);

		dcreo4->close();
		((PlayerImplementation*) this)->sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::removeSkillMod(const String& name, bool updateClient) {
	if (!creatureSkillMods.containsKey(name))
		return;

	creatureSkillMods.remove(name);

	if (updateClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

		dcreo4->startSkillModsUpdate(1);
		dcreo4->removeSkillMod(name, 0);

		dcreo4->close();
		((PlayerImplementation*) this)->sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::addSkillModBonus(const String& name, int mod, bool updateClient) {
	if (creatureSkillModBonus.containsKey(name)) {
		mod += creatureSkillModBonus.get(name);

		//if (mod <= 0) {
		//	removeSkillModBonus(name, updateClient);
		//	return;
		//}

		creatureSkillModBonus.remove(name);
	}

	creatureSkillModBonus.put(name, mod);

	if (updateClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

		dcreo4->startSkillModsUpdate(1);
		dcreo4->addSkillMod(name, mod + creatureSkillMods.get(name));

		dcreo4->close();
		((PlayerImplementation*) this)->sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::removeSkillModBonus(const String& name, bool updateClient) {
	if (!creatureSkillModBonus.containsKey(name))
		return;

	creatureSkillModBonus.remove(name);

	if (updateClient) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

		dcreo4->startSkillModsUpdate(1);
		dcreo4->removeSkillMod(name, 0);

		dcreo4->close();
		((PlayerImplementation*) this)->sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::startDancing(const String& modifier, bool changeDance) {

	if (isDancing() && !changeDance) {
		sendSystemMessage("performance", "already_performing_self");
		return;
	} else if (!isDancing() && changeDance) {
		sendSystemMessage("performance", "dance_must_be_performing_self");
		return;
	}

	if (isPlayingMusic())
		stopPlayingMusic();

	String anim = modifier.toLowerCase(); //leave original modifier alone

	// TODO: This needs to be cleaned up and refactored
	Vector<String> availableDances;

	if (isPlayer()) {
		PlayerImplementation* player = (PlayerImplementation*) this;

		String skillBox = "social_entertainer_novice";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("basic");
			availableDances.add("rhythmic");
		} else
		{
			sendSystemMessage("You do not have sufficient abilities to start dancing.");
			return;
		}


		skillBox = "social_entertainer_dance_01";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableDances.add("basic2");

		skillBox = "social_entertainer_dance_02";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableDances.add("rhythmic2");

		skillBox = "social_entertainer_dance_03";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableDances.add("footloose");

		skillBox = "social_entertainer_dance_04";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableDances.add("formal");

		skillBox = "social_entertainer_master";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("footloose2");
			availableDances.add("formal2");
		}

		skillBox = "social_dancer_novice";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("poplock");
			availableDances.add("popular");
		}


		skillBox = "social_dancer_knowledge_01";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("popular2");
			availableDances.add("tumble");
		}

		skillBox = "social_dancer_knowledge_02";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("poplock2");
			availableDances.add("tumble2");
		}


		skillBox = "social_dancer_knowledge_03";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("breakdance");
			availableDances.add("lyrical");
		}

		skillBox = "social_dancer_knowledge_04";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("breakdance2");
			availableDances.add("exotic");
			availableDances.add("exotic2");
		}

		skillBox = "social_dancer_master";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableDances.add("exotic3");
			availableDances.add("exotic4");
			availableDances.add("lyrical2");
			// Comment out the quest dances for now
			//availableDances.add("theatrical"); // this is given by a quest
			//availableDances.add("theatrical2"); // this is given by a quest
		}

		if (anim == "") {
			uint32 boxID = SuiWindowType::START_DANCING; // default startdance

			if (changeDance)
				boxID = SuiWindowType::CHANGE_DANCING; // differentiate changedance

			SuiListBox* sui = new SuiListBox((Player*) _this, boxID);
			sui->setPromptTitle("Available dances");
			sui->setPromptText("Pick a dance");

			// TODO: tie this somehow back to the database - the commands
			// aren't quite the right place since the actionCRC for startdance
			// is the same for all of them
			for (int i = 0; i < availableDances.size(); ++i) {
				String dance = availableDances.get(i);
				sui->addMenuItem(dance);
			}

			player->addSuiBox(sui);

			player->sendMessage(sui->generateMessage());

			return;
		} else {
			StringBuffer dance;
			dance << "startdance+";

			if (isdigit(anim[0]))
				dance << availableDances.get(atoi(anim.toCharArray()));
			else
				dance << anim;


			if (player->getSkill(dance.toString()) == NULL) {
				sendSystemMessage("performance", "dance_lack_skill_self");
				return;
			}
		}
	}

	int animid = Integer::valueOf(anim);

	if (anim == "basic" || (Character::isDigit(anim.charAt(0))
			&& "basic" == availableDances.get(animid))) { // anim == "0"
		sendEntertainingUpdate(0x3C4CCCCD, "dance_1", 0x07339FF8, 0xDD);
	} else if (anim == "rhythmic" || (Character::isDigit(anim.charAt(0))
			&& "rhythmic" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_3", 0x07339FF8, 0xDD);
	} else if (anim == "basic2" || (Character::isDigit(anim.charAt(0))
			&& "basic2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_2", 0x07339FF8, 0xDD);
	} else if (anim == "rhythmic2" || (Character::isDigit(anim.charAt(0))
			&& "rhythmic2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_4", 0x07339FF8, 0xDD);
	} else if (anim == "footloose" || (Character::isDigit(anim.charAt(0))
			&& "footloose" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_15", 0x07339FF8, 0xDD);
	} else if (anim == "formal" || (Character::isDigit(anim.charAt(0))
			&& "forma" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_17", 0x07339FF8, 0xDD);
	} else if (anim == "footloose2" || (Character::isDigit(anim.charAt(0))
			&& "footloose2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_16", 0x07339FF8, 0xDD);
	} else if (anim == "formal2" || (Character::isDigit(anim.charAt(0))
			&& "formal2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_18", 0x07339FF8, 0xDD);
	} else if (anim == "popular" || (Character::isDigit(anim.charAt(0))
			&& "popular" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_9", 0x07339FF8, 0xDD);
	} else if (anim == "poplock" || (Character::isDigit(anim.charAt(0))
			&& "poplock" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_13", 0x07339FF8, 0xDD);
	} else if (anim == "popular2" || (Character::isDigit(anim.charAt(0))
			&& "popular2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_10", 0x07339FF8, 0xDD);
	} else if (anim == "poplock2" || (Character::isDigit(anim.charAt(0))
			&& "poplock2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_14", 0x07339FF8, 0xDD);
	} else if (anim == "lyrical" || (Character::isDigit(anim.charAt(0))
			&& "lyrical" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_11", 0x07339FF8, 0xDD);
	} else if (anim == "exotic" || (Character::isDigit(anim.charAt(0))
			&& "exotic" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_5", 0x07339FF8, 0xDD);
	} else if (anim == "exotic2" || (Character::isDigit(anim.charAt(0))
			&& "exoitic2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_6", 0x07339FF8, 0xDD);
	} else if (anim == "lyrical2" || (Character::isDigit(anim.charAt(0))
			&& "lyrical2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_12", 0x07339FF8, 0xDD);
	} else if (anim == "exotic3" || (Character::isDigit(anim.charAt(0))
			&& "exotic3" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_7", 0x07339FF8, 0xDD);
	} else if (anim == "exotic4" || (Character::isDigit(anim.charAt(0))
			&& "exotic4" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_8", 0x07339FF8, 0xDD);
	} else if (anim == "theatrical" || (Character::isDigit(anim.charAt(0))
			&& "theatrical" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_21", 0x07339FF8, 0xDD);
	} else if (anim == "theatrical2" || (Character::isDigit(anim.charAt(0))
			&& "theatrical2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_22", 0x07339FF8, 0xDD);
		/*	} else if (anim == "unknown1" || "unknown1" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_19", 0x07339FF8, 0xDD);
		 } else if (anim == "unknown2" || "unknown2" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_20", 0x07339FF8, 0xDD);
		 } else if (anim == "unknown3" || "unknown3" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_23", 0x07339FF8, 0xDD);
		 } else if (anim == "unknown4" || "unknown4" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_24", 0x07339FF8, 0xDD);
		 } else if (anim == "unknown5" || "unknown5" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_25", 0x07339FF8, 0xDD);
		 } else if (anim == "unknown6" || "unknown6" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_26", 0x07339FF8, 0xDD);
		 } else if (anim == "unknown7" || "unknown7" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_27", 0x07339FF8, 0xDD);
		 } else if (anim == "unknown8" || "unknown8" == availableDances.get(animid)) {
		 sendEntertainingUpdate(0x3C4CCCCD, "dance_28", 0x07339FF8, 0xDD);*/
	} else if (anim == "breakdance" || (Character::isDigit(anim.charAt(0))
			&& "breakdance" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_29", 0x07339FF8, 0xDD);
	} else if (anim == "breakdance2" || (Character::isDigit(anim.charAt(0))
			&& "breakdance2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_30", 0x07339FF8, 0xDD);
	} else if (anim == "tumble" || (Character::isDigit(anim.charAt(0))
			&& "tumble" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_31", 0x07339FF8, 0xDD);
	} else if (anim == "tumble2" || (Character::isDigit(anim.charAt(0))
			&& "tumble2" == availableDances.get(animid))) {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_32", 0x07339FF8, 0xDD);
	} else {
		sendSystemMessage("performance", "dance_lack_skill_self");
		return;
	}

	info("started dancing");

	setPosture(CreaturePosture::SKILLANIMATING);
	setPerformanceName(isdigit(anim[0]) ? availableDances.get(atoi(anim.toCharArray())) : anim);
	setDancing(true);

	if (!changeDance)
		sendSystemMessage("performance", "dance_start_self");

	// Tick every 10 seconds HAM costs
	if (isPlayer()) {
		PlayerImplementation* player = (PlayerImplementation*) this;
		player->setEntertainerEvent();
	}
}

void CreatureObjectImplementation::startPlayingMusic(const String& modifier, bool changeMusic) {
	if (isPlayingMusic() && !changeMusic) {
		sendSystemMessage("performance", "already_performing_self");
		return;
	} else if (!isPlayingMusic() && changeMusic) {
		sendSystemMessage("performance", "music_must_be_performing_self");
		return;
	}

	if (isDancing())
		stopDancing();

	Instrument* instrument = getInstrument();

	if (instrument == NULL) {
		sendSystemMessage("performance", "music_no_instrument");
		return;
	}

	String music = modifier.toLowerCase(); //leave original modifier alone

	// TODO: Need to refactor this code
	Vector<String> availableSongs;

	if (isPlayer()) {
		PlayerImplementation* player = (PlayerImplementation*) this;

		String skillBox = "social_entertainer_novice";

		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("starwars1");
		else {
			sendSystemMessage("You do not have sufficient abilities to play music.");
			return;
		}

		skillBox = "social_entertainer_music_01";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("rock");

		skillBox = "social_entertainer_music_02";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("starwars2");

		skillBox = "social_entertainer_music_03";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("folk");

		skillBox = "social_entertainer_music_04";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("starwars3");

		skillBox = "social_entertainer_master";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("ceremonial");

		skillBox = "social_musician_novice";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("starwars4");

		skillBox = "social_musician_knowledge_01";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("ballad");

		skillBox = "social_musician_knowledge_02";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("funk");

		skillBox = "social_musician_knowledge_03";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("waltz");

		skillBox = "social_musician_knowledge_04";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox))
			availableSongs.add("jazz");

		skillBox = "social_musician_master";
		if (player->getSkillBoxesSize() && player->hasSkillBox(skillBox)) {
			availableSongs.add("virtuoso");
			//availableSongs.add("western"); //add back in later - this isn't in the skills tree
		}

		if (music == "") {
			uint32 boxID = SuiWindowType::START_MUSIC; // default startmusic

			if (changeMusic)
				boxID = SuiWindowType::CHANGE_MUSIC; // differentiate changemusic

			SuiListBox* sui = new SuiListBox((Player*) _this, boxID);
			sui->setPromptText("Available songs");
			sui->setPromptTitle("Pick a song");

			for (int i = 0; i < availableSongs.size(); ++i) {
				String song = availableSongs.get(i);
				sui->addMenuItem(song);
			}

			player->addSuiBox(sui);

			player->sendMessage(sui->generateMessage());
			return;
		} else {
			StringBuffer song;
			song << "startmusic+";

			if (isdigit(music[0]))
				song << availableSongs.get(atoi(music.toCharArray()));
			else
				song << music;

			if (player->getSkill(song.toString()) == NULL) {
				sendSystemMessage("performance", "music_lack_skill_song_self");
				return;
			}
		}
	}

	int instrid;
	if (music == "starwars1" || (isdigit(music[0]) && "starwars1" == availableSongs.get(atoi(music.toCharArray())))) { // music == "0"
		instrid = 1;
	} else if (music == "rock" || (isdigit(music[0]) && "rock" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 11;
	} else if (music == "starwars2" || (isdigit(music[0]) && "starwars2" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 21;
	} else if (music == "folk" || (isdigit(music[0]) && "folk" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 31;
	} else if (music == "starwars3" || (isdigit(music[0]) && "starwars3" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 41;
	} else if (music == "ceremonial" || (isdigit(music[0]) && "ceremonial" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 51;
	} else if (music == "ballad" || (isdigit(music[0]) && "ballad" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 61;
	} else if (music == "waltz" || (isdigit(music[0]) && "waltz" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 71;
	} else if (music == "jazz" || (isdigit(music[0]) && "jazz" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 81;
	} else if (music == "virtuoso" || (isdigit(music[0]) && "virtuoso" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 91;
	} else if (music == "western" || (isdigit(music[0]) && "western" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 101;
	} else if (music == "starwars4" || (isdigit(music[0]) && "starwars4" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 111;
	} else if (music == "funk" || (isdigit(music[0]) && "funk" == availableSongs.get(atoi(music.toCharArray())))) {
		instrid = 121;
	} else {
		sendSystemMessage("performance", "music_invalid_song");
		return;
	}

	String instrumentAnimation = "";

	switch(instrument->getInstrumentType()) {
		case InstrumentImplementation::SLITHERHORN: //SLITHERHORN: yeah!
			instrid += 0;
			instrumentAnimation = "music_3";
			break;
		case InstrumentImplementation::FIZZ: // yeah
			instrid += 1;
			instrumentAnimation = "music_3";
			break;
		case InstrumentImplementation::FANFAR: //FANFAR yeah
			instrid += 2;
			instrumentAnimation = "music_3";
			break;
		case InstrumentImplementation::KLOOHORN: // yeah
			instrid += 3;
			instrumentAnimation = "music_3";
			break;
		case InstrumentImplementation::MANDOVIOL: //MANDOVIOL
			instrid += 4;
			instrumentAnimation = "music_5";
			break;
		case InstrumentImplementation::TRAZ: //TRAZ yeah
			instrid += 5;
			instrumentAnimation = "music_3";
			break;
		case InstrumentImplementation::BANDFILL: // yeah
			instrid += 6;
			instrumentAnimation = "music_1";
			break;
		case InstrumentImplementation::FLUTEDROOPY: //
			instrid += 7;
			instrumentAnimation = "music_3";
			break;
		case InstrumentImplementation::OMNIBOX: //OMNIBOX:
			instrid += 8;
			instrumentAnimation = "music_4";
			break;
		case InstrumentImplementation::NALARGON: //NALARGON:
			instrid += 9;
			instrumentAnimation = "music_3";
			break;
		default:
			sendSystemMessage("Bad instrument type.");
			return;
	}

	sendSystemMessage("performance", "music_start_self");

	setPosture(CreaturePosture::SKILLANIMATING);
	setPerformanceName(isdigit(music[0]) ? availableSongs.get(atoi(music.toCharArray())) : music);
	setPlayingMusic(true);


	// instrid instrument->getInstrumentType()
	sendEntertainingUpdate(0x3C4CCCCD, instrumentAnimation, 0x07352BAC, instrid);

	// Tick every 10 seconds HAM costs
	if (isPlayer()) {
		PlayerImplementation* player = (PlayerImplementation*) this;
		player->setEntertainerEvent();
	}
}
void CreatureObjectImplementation::stopDancing() {
	if (!isDancing())
        return;
	sendSystemMessage("performance", "dance_stop_self");

	info("stopped dancing");

	setDancing(false);
	sendEntertainingUpdate(0x3F4D70A4, getPerformanceAnimation(), 0, 0);
	setPerformanceName("");

	while (!watchers.isEmpty()) {
		ManagedReference<CreatureObject> creo = watchers.get(0);

		try {
			creo->wlock(_this);

			info("stopping dance for [" + creo->getCharacterName().toString() + "]");
			// dance_stop_other	%TU stops dancing.

			creo->stopWatch(objectID, true, true, false);

			if (!creo->isListening())
				sendEntertainmentUpdate(0, "", true);

			creo->unlock();
		} catch (...) {
			error("Exception in CreatureObject::stopDancing()");
			creo->unlock();
		}
	}

	setPosture(0);
}

void CreatureObjectImplementation::stopPlayingMusic() {
    if (!isPlayingMusic())
        return;
	sendSystemMessage("performance", "music_stop_self");

	info("stopped playing music");

	setPlayingMusic(false);
	sendEntertainingUpdate(0x3F4D70A4, getPerformanceAnimation(), 0, 0);
	setPerformanceName("");
	setListenID(0);

	while (!listeners.isEmpty()) {
		ManagedReference<CreatureObject> creo = listeners.get(0);

		try {
			creo->wlock(_this);

			info("stopping music for [" + creo->getCharacterName().toString() + "]");

			creo->stopListen(objectID, true, true, false);

			if (!creo->isWatching())
				sendEntertainmentUpdate(0, "", true);

			creo->unlock();
		} catch (...) {
			error("Exception in CreatureObject::stopPlayingMusic()");
			creo->unlock();
		}
	}

	setPosture(0);
}

void CreatureObjectImplementation::startWatch(uint64 entid) {
	SceneObject* object = zone->lookupObject(entid);

	if (object == NULL)
		return;

	if (object->isNonPlayerCreature()) {
		sendSystemMessage("performance", "dance_watch_npc");
		return;
	}

	if (!object->isPlayer() && !object->isNonPlayerCreature()) {
		sendSystemMessage("You cannot start watching an object.");
		return;
	}

	CreatureObject* creature = (CreatureObject*) object;

	if (creature == _this)
		return;

	creature->wlock(_this);

	if (isDancing() || isPlayingMusic()) {
		sendSystemMessage("You cannot /watch while skill animating.");

		creature->unlock();
		return;
	} else if (!creature->isDancing()) {
		sendSystemMessage(creature->getCharacterName().toString() + " is not currently dancing.");

		creature->unlock();
		return;
	} else if (entid == watchID) {
		sendSystemMessage("You are already watching " + creature->getCharacterName().toString() + ".");

		creature->unlock();
		return;
	}

	if (isWatching()) {
		stopWatch(watchID, false);

		sendEntertainmentUpdate(entid, "entertained");

		creature->addWatcher(_this);

		if (isPlayer())
			sendSystemMessage("You begin watching " + creature->getCharacterName().toString() + ".");
	} else {
		sendEntertainmentUpdate(entid, "entertained");

		creature->addWatcher(_this);

		if (isPlayer())
			sendSystemMessage("You begin watching " + creature->getCharacterName().toString() + ".");

		doWatching = true;
	}
	setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f);
	setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);

	info("started watching [" + creature->getCharacterName().toString() + "]");

	watchID =  entid;

	creature->unlock();
}

void CreatureObjectImplementation::startListen(uint64 entid) {
	SceneObject* object = zone->lookupObject(entid);

	if (object == NULL)
		return;

	if (!object->isPlayer() && !object->isNonPlayerCreature()) {
		sendSystemMessage("You cannot start listening an object.");
		return;
	}

	CreatureObject* creature = (CreatureObject*) object;

	if (creature == _this)
		return;

	creature->wlock(_this);

	if (isDancing() || isPlayingMusic()) {
		sendSystemMessage("You cannot /listen while skill animating.");

		creature->unlock();
		return;
	} else 	if (!creature->isPlayingMusic()) {
		sendSystemMessage(creature->getCharacterName().toString() + " is not currently playing music.");

		creature->unlock();
		return;
	} else if (entid == listenID) {
		sendSystemMessage("You are already listening to " + creature->getCharacterName().toString() + ".");

		creature->unlock();
		return;
	}

	if (isListening()) {
		stopListen(listenID, false);

		sendEntertainmentUpdate(entid, "entertained");

		creature->addListener(_this);

		if (isPlayer())
			sendSystemMessage("You begin listening to " + creature->getCharacterName().toString() + ".");
	} else {
		sendEntertainmentUpdate(entid, "entertained");

		creature->addListener(_this);

		if (isPlayer())
			sendSystemMessage("You begin listening to " + creature->getCharacterName().toString() + ".");

		doListening = true;
	}
	setEntertainerBuffDuration(PerformanceType::MUSIC, 0.0f);
	setEntertainerBuffStrength(PerformanceType::MUSIC, 0.0f);

	info("started listening [" + creature->getCharacterName().toString() + "]");

	listenID = entid;

	creature->unlock();
}

void CreatureObjectImplementation::stopWatch(uint64 entid, bool doSendPackets, bool forced, bool doLock) {
	SceneObject* object = zone->lookupObject(entid);

	if (object == NULL)
		return;

	if (!object->isPlayer() && !object->isNonPlayerCreature()) {
		sendSystemMessage("You cannot stop watching an object.");
		return;
	}

	CreatureObject* creature = (CreatureObject*) object;

	if (creature == _this)
		return;

	String entName;
	if (creature != NULL) {
		if (doLock && (creature != _this))
			creature->wlock(_this);

		entName = creature->getCharacterName().toString();

		creature->removeWatcher(_this);

		if (doLock && (creature != _this))
			creature->unlock();
	}

	if (entid != watchID) {
		if (isPlayer() && creature != NULL)
			sendSystemMessage("You are not currently watching " + entName + ".");

		return;
	}

	if (doSendPackets)
		sendEntertainmentUpdate(0, moodStr);

	if (isPlayer() && creature != NULL) {
		StringBuffer msg;

		if (forced)
			msg << entName << " stops dancing.";
		else
			msg << "You stop watching " << entName << ".";

		sendSystemMessage(msg.toString());
		sendSystemMessage("healing", "performance_enhance_dance_mind_d");
	}

	activateEntertainerBuff(PerformanceType::DANCE);
	setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f); // reset
	setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);
	info("stopped watching [" + entName + "]");

	doWatching = false;
	watchID = 0;
}

void CreatureObjectImplementation::stopListen(uint64 entid, bool doSendPackets, bool forced, bool doLock) {
	SceneObject* object = zone->lookupObject(entid);

	if (object == NULL)
		return;

	if (!object->isPlayer() && !object->isNonPlayerCreature()) {
		sendSystemMessage("You cannot stop listening an object.");
		return;
	}

	CreatureObject* creature = (CreatureObject*) object;

	if (creature == _this)
		return;

	String entName;
	if (creature != NULL) {
		if (doLock && (creature != _this))
			creature->wlock(_this);

		entName = creature->getCharacterName().toString();

		creature->removeListener(_this);

		if (doLock && (creature != _this))
			creature->unlock();
	}

	if (entid != listenID) {
		if (isPlayer() && creature != NULL)
			sendSystemMessage("You are not currently listening to " + entName + ".");

		return;
	}

	if (doSendPackets)
		sendEntertainmentUpdate(0, moodStr);

	if (isPlayer() && creature != NULL) {
		StringBuffer msg;

		if (forced)
			msg << entName << " stops playing music.";
		else
			msg << "You stop listening to " << entName << ".";

		sendSystemMessage(msg.toString());
		sendSystemMessage("healing", "performance_enhance_music_focus_d");
		sendSystemMessage("healing", "performance_enhance_music_willpower_d");
	}

	//TODO: Activate Buff
	activateEntertainerBuff(PerformanceType::MUSIC);
	setEntertainerBuffDuration(PerformanceType::MUSIC, 0.0f); // reset
	setEntertainerBuffStrength(PerformanceType::MUSIC, 0.0f);
	info("stopped listening [" + entName + "]");

	doListening = false;
	listenID = 0;
}

void CreatureObjectImplementation::activateEntertainerBuff(int performanceType) {

	// Returns the Number of Seconds for the Buff Duration
	float buffDuration = getEntertainerBuffDuration(performanceType);
	// Returns a % of base stat
	float buffStrength = getEntertainerBuffStrength(performanceType);


	//System::out << "activateEntertainerBuff(" << performanceType << ") called for " << getCharacterName().toString() << " with duration: " << buffDuration << " strength: ";
	//System::out.precision(4);
	//System::out << buffStrength << endl;

	Buff *buff = NULL;
	switch(performanceType){
		case PerformanceType::MUSIC:
			buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_FOCUS, BuffType::PERFORMANCE, buffDuration * 60);
			buff->setFocusBuff((int)round(buffStrength * getBaseFocus()));
			applyBuff(buff);

			buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_MUSIC_WILLPOWER, BuffType::PERFORMANCE, buffDuration * 60);
			buff->setWillpowerBuff((int)round(buffStrength * getBaseWillpower()));
			applyBuff(buff);
			break;
		case PerformanceType::DANCE:
			buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_DANCE_MIND, BuffType::PERFORMANCE, buffDuration * 60);
			buff->setMindBuff((int)round(buffStrength * getBaseMind()));
			applyBuff(buff);
	}

}


void CreatureObjectImplementation::doFlourish(const String& modifier) {
	if (isPlayer()) {
		PlayerImplementation* player = (PlayerImplementation*) this;

		String skillBox = "social_entertainer_novice";

		if (!player->getSkillBoxesSize() || !player->hasSkillBox(skillBox)) {
			// TODO: sendSystemMessage("cmd_err", "ability_prose", creature);
			sendSystemMessage("You do not have sufficient abilities to Flourish");
			return;
		}
	}

	int fid = atoi(modifier.toCharArray());

	if (!isDancing() && !isPlayingMusic()) {
		sendSystemMessage("performance", "flourish_not_performing");
		return;
	}

	SkillManager* skillManager = server->getSkillManager();
	Performance* performance = NULL;

	if (isDancing())
		performance = skillManager->getDance(getPerformanceName());
	else if (isPlayingMusic() && getInstrument())
		performance = skillManager->getSong(getPerformanceName(), getInstrument()->getInstrumentType());
	else
		return;

	if (!performance) { // shouldn't happen
		StringBuffer msg;
		msg << "Performance was null.  Please report to McMahon! Name: " << getPerformanceName() << " and Type: " << dec << getInstrument()->getInstrumentType();

		sendSystemMessage(msg.toString());
		return;
	}

	float baseActionDrain =  -1 * performance->getActionPointsPerLoop();

	//float baseActionDrain = -40 + (getQuickness() / 37.5);
	float flourishActionDrain = baseActionDrain / 2.0;

	int actionDrain = (int)round((flourishActionDrain * 10+ 0.5) / 10.0); // Round to nearest dec for actual int cost

	if (changeActionBar(actionDrain, false) ) {
		activateRecovery();

		if (isDancing()) {
	    	StringBuffer msg;
			msg << "skill_action_" << fid;
	    	doAnimation(msg.toString());
	    } else if (isPlayingMusic()) {
	    	Flourish* flourish = new Flourish(_this, fid);
			broadcastMessage(flourish);
	    }

		// Add buff
		if (canGiveEntertainBuff()){
			//sendSystemMessage("Flourish Buff");
			addEntertainerFlourishBuff();
		}

		// Grant Experience
		if (isPlayer()) {
			Player* player = (Player*)_this;

			player->addEntertainerFlourishXp(performance->getBaseXp() + performance->getFlourishXpMod());
		}

		sendSystemMessage("performance", "flourish_perform");
	} else {
		sendSystemMessage("performance", "flourish_too_tired");
	}
}

// TODO: can this be simplified by doing the building check in the ticker?
void CreatureObjectImplementation::addEntertainerFlourishBuff() {
	// Watchers that are in our group for passive buff
	ManagedSortedVector<CreatureObject>* patrons = NULL;

	SkillManager* skillManager = server->getSkillManager();
	Performance* performance = NULL;

	if (getPerformanceName() == "")
		return;

	if (isDancing()) {
		//woundAbility = getSkillMod("healing_dance_wound");
		patrons = &watchers;
		performance = skillManager->getDance(getPerformanceName());
	} else if (isPlayingMusic() && getInstrument() != NULL) {
		//woundAbility = getSkillMod("healing_music_wound");
		patrons = &listeners;
		performance = skillManager->getSong(getPerformanceName(), getInstrument()->getInstrumentType());
	} else return;

	if (performance == NULL) { // shouldn't happen
		StringBuffer msg;
		msg << "Performance was null.  Please report to McMahon! Name: " << getPerformanceName() << " and Type: " << dec << getInstrument()->getInstrumentType();

		sendSystemMessage(msg.toString());
		return;
	}

	if (patrons != NULL && patrons->size() > 0) {
		for (int i = 0; i < patrons->size(); ++i) {
			CreatureObject* obj = patrons->get(i);
			try {
				if (obj != _this)
					obj->wlock(_this);

				// Passive Buff only to group members
				if (!isInAGroup() || (isInAGroup() && getGroupID() != obj->getGroupID())) {
					if (obj != _this)
						obj->unlock();

					continue;
				}

				bool patronInRange = false;

				if (obj->getBuilding() == getBuilding())
					patronInRange = true;

				if (patronInRange)
					obj->addEntertainerBuffDuration(performance->getType(), 1.0f);

				if (obj != _this)
					obj->unlock();
			} catch (...) {
				if (obj != _this)
					obj->unlock();

				error("Unreported exception caught in CreatureObjectImplementation::doHealMindWounds()");
			}
		}
	} /*else
		System::out << "no patrons";*/

}

// Handle the Entertainer 'tick's
void CreatureObjectImplementation::doEntertainerPatronEffects(bool healShock, bool healWounds, bool addBuff) {
	info("CreatureObjectImplementation::doEntertainerPatronEffects() begin");
	ManagedSortedVector<CreatureObject>* patrons = NULL;
	int healingXp = 0;

	//System::out << "CreatureObjectImplementation::doEntertainerPatronEffects()" << endl;
	SkillManager* skillManager = server->getSkillManager();
	Performance* performance = NULL;
	float enhancementSkill = 0.0f;

	if (getPerformanceName() == "")
		return;

	if (isDancing()) {
		//woundAbility = getSkillMod("healing_dance_wound");
		patrons = &watchers;
		performance = skillManager->getDance(getPerformanceName());
		enhancementSkill = (float)getSkillMod("healing_dance_mind");
	} else if (isPlayingMusic() && getInstrument() != NULL) {
		//woundAbility = getSkillMod("healing_music_wound");
		patrons = &listeners;
		performance = skillManager->getSong(getPerformanceName(), getInstrument()->getInstrumentType());
		enhancementSkill = (float)getSkillMod("healing_music_mind");
	} else
		return;

	if (performance == NULL) { // shouldn't happen
		StringBuffer msg;
		msg << "Performance was null.  Please report to McMahon! Name: " << getPerformanceName() << " and Type: " << dec << getInstrument()->getInstrumentType();

		sendSystemMessage(msg.toString());
		return;
	}

	int woundHeal = -1 * performance->getHealMindWound();
	int shockHeal = -1 * performance->getHealShockWound();

	// Entertainer can heal their own BF/Wounds
	if (healWounds)
	{
		changeMindWoundsBar(woundHeal, false);
		changeFocusWoundsBar(woundHeal, false);
		changeWillpowerWoundsBar(woundHeal, false);

		healingXp += -1 * woundHeal;
	}

	if (healShock) {
		changeShockWounds(shockHeal);
		healingXp += -1 * shockHeal;
	}


	if (patrons != NULL && patrons->size() > 0) {
		for (int i = 0; i < patrons->size(); ++i) {
			//System::out << "looping patron: " << i << endl;
			CreatureObject* obj = patrons->get(i);

			try {
				if (obj != _this)
					obj->wlock(_this);

				//performance->get
				//if (!isInRange(obj->getPositionX(), obj->getPositionY(), skill->getRange())) {
					//obj->stopListen()
				//}
				// verify patron is in the same building as performer

				bool patronInRange = false;

				if (obj->getBuilding() == getBuilding())
					patronInRange = true;

				if (patronInRange) {
					if (healWounds)
					{
						obj->changeMindWoundsBar(woundHeal, false);
						obj->changeFocusWoundsBar(woundHeal, false);
						obj->changeWillpowerWoundsBar(woundHeal, false);

						healingXp += -1 * woundHeal;
					}

					if (healShock) {
						obj->changeShockWounds(shockHeal);

						healingXp += -1 * woundHeal;
					}

					// Handle Passive Buff
					if (addBuff && isInAGroup() && (getGroupID() == obj->getGroupID())) {
						// Add 1 minute per tick
						obj->addEntertainerBuffDuration(performance->getType(), 1.0f);
						// TODO: In theory the buff isn't always the max, in practice after enough flourishes it maxes out way before duration
						obj->setEntertainerBuffStrength(performance->getType(), enhancementSkill / 100.0f);
					}
				} else {
					if (isDancing()) {
						obj->stopWatch(objectID, true, true, false);

						if (!obj->isListening())
							sendEntertainmentUpdate(0, "", true);

					} else if (isPlayingMusic()) {
						obj->stopListen(objectID, true, true, false);

						if (!obj->isWatching())
							sendEntertainmentUpdate(0, "", true);
					}
				}

				if (obj != _this)
					obj->unlock();
			} catch (...) {
				if (obj != _this)
					obj->unlock();

				error("Unreported exception caught in CreatureObjectImplementation::doHealMindWounds()");
			}
		}
	} /*else
		System::out << "no patrons";*/

	// Add Experience
	if (healingXp > 0 && isPlayer()) {
		Player* player = (Player*)_this;

		player->addEntertainerHealingXp(healingXp);
	}

	info("CreatureObjectImplementation::doEntertainerPatronEffects() end");
}



void CreatureObjectImplementation::doPerformanceAction() {
	/*if (!isPlayer())
		return;*/

	SkillManager* skillManager = server->getSkillManager();
	Performance* performance = NULL;

	if (isDancing())
		performance = skillManager->getDance(getPerformanceName());
	else if (isPlayingMusic() && getInstrument())
		performance = skillManager->getSong(getPerformanceName(), getInstrument()->getInstrumentType());
	else
		return;

	if (!performance) { // shouldn't happen
		StringBuffer msg;
		msg << "Performance was null.  Please report to McMahon! Name: " << getPerformanceName() << " and Type: " << dec << getInstrument()->getInstrumentType();

		sendSystemMessage(msg.toString());
		return;
	}

	int actionDrain = -1 * performance->getActionPointsPerLoop();

	if (changeActionBar(actionDrain, false)) {
		activateRecovery();
	} else {
		if (isDancing()) {
			stopDancing();
			sendSystemMessage("performance", "dance_too_tired");
		}

		if (isPlayingMusic()) {
			stopPlayingMusic();
			sendSystemMessage("performance", "music_too_tired");
		}
	}
}

void CreatureObjectImplementation::sendEntertainingUpdate(uint32 entval, const String& performance, uint32 perfcntr, int instrid) {
	if (isPlayer()) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

		if (isPlayingMusic() && instrid != 0)
			dcreo4->updateListenToID(objectID);

		dcreo4->updateEntertainerValue(entval);
		dcreo4->close();
		((PlayerImplementation*) this)->sendMessage(dcreo4);

	}

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updatePerformanceAnimation(performance);
	dcreo6->updatePerformanceCounter(perfcntr);
	dcreo6->updateInstrumentID(instrid);
	dcreo6->close();
	broadcastMessage(dcreo6);

	setPerformanceAnimation(performance);
	setPerformanceCounter(0);
	setInstrumentID(instrid);
}

void CreatureObjectImplementation::sendEntertainmentUpdate(uint64 entid, const String& mood, bool updateEntValue) {
	if (isPlayer()) {
		CreatureObjectDeltaMessage4* codm4 = new CreatureObjectDeltaMessage4(this);
		codm4->updateListenToID(entid);

		if (updateEntValue)
			codm4->updateEntertainerValue(0x3F4D70A4);

		codm4->close();
		((PlayerImplementation*) this)->sendMessage(codm4);
	}

	CreatureObjectDeltaMessage6* codm6 = new CreatureObjectDeltaMessage6(_this);
	String str = Races::getMoodStr(mood);
	codm6->updateMoodAnimation(str);
	codm6->close();
	broadcastMessage(codm6);
}

bool CreatureObjectImplementation::isInBuilding() {
	if (getParent() != NULL && getParent()->isCell())
		return true;

	return false;
}

int CreatureObjectImplementation::getBuildingType() {
	if (parent != NULL && parent->isCell()) {
		CellObject* cell = (CellObject*) parent;
		BuildingObject* building = (BuildingObject*)parent->getParent();

		return building->getBuildingType();
	}

	return 0;
}

bool CreatureObjectImplementation::canGiveEntertainBuff() {
	if (isInBuilding()) {
		int buildingType = getBuildingType();

		if (buildingType == BuildingObjectImplementation::CANTINA ||
			buildingType == BuildingObjectImplementation::GUILD_THEATER ||
			buildingType == BuildingObjectImplementation::TAVERN) {
			return true;
		}
	}
	return false;
}

SceneObject *CreatureObjectImplementation::getBuilding() {
	if (parent != NULL && parent->isCell()) {
		CellObject* cell = (CellObject*) parent;
		BuildingObject* building = (BuildingObject*)parent->getParent();

		return building;
	}

	return NULL;
}

void CreatureObjectImplementation::sendGuildTo() {
	CreatureObjectDeltaMessage6* codm6 = new CreatureObjectDeltaMessage6(_this);
	codm6->updateGuild(guild->getGuildID());
	codm6->close();

	broadcastMessage(codm6);
}

void CreatureObjectImplementation::updateGroupId(uint64 id) {
	groupId = id;

	CreatureObjectDeltaMessage6* delta = new CreatureObjectDeltaMessage6(_this);
	delta->updateGroupID();
	delta->close();

	broadcastMessage(delta);
}

void CreatureObjectImplementation::updateGroupInviterId(uint64 id) {
	setGroupInviterID(id);

	CreatureObjectDeltaMessage6* delta = new CreatureObjectDeltaMessage6(_this);
	delta->updateInviterId();
	delta->close();

	broadcastMessage(delta);
}

uint32 CreatureObjectImplementation::getMitigation(const String& mit) {
	Skill* mitig = creatureSkills.get(mit.hashCode());

	if (mitig == NULL || !mitig->isPassiveSkill())
		return 0;
	else {
		PassiveSkill* mitigation = (PassiveSkill*)mitig;
		return mitigation->getDamageReduction();
	}
}

void CreatureObjectImplementation::broadcastMessages(Vector<BaseMessage*>& msgs, int range, bool doLock) {
	if (zone == NULL) {
		for (int j = 0; j < msgs.size(); ++j) {
			Message* msg = msgs.get(j);
			delete msg;
		}

		msgs.removeAll();

		return;
	}

	try {
		//System::out << "CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";

		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range) || player->getParent() != NULL) {
					for (int j = 0; j < msgs.size(); ++j) {
						BaseMessage* msg = msgs.get(j);
						player->sendMessage(msg->clone());
					}
				}
			}
		}

		for (int j = 0; j < msgs.size(); ++j) {
			Message* msg = msgs.get(j);
			delete msg;
		}

		msgs.removeAll();

		zone->unlock(doLock);

		//System::out << "finished CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";
	} catch (...) {
		error("exception CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)");

		zone->unlock(doLock);
	}
}

void CreatureObjectImplementation::sendSystemMessage(const String& message) {
	if (isPlayer())
		((PlayerImplementation*) this)->sendSystemMessage(message);
}

void CreatureObjectImplementation::sendSystemMessage(const String& file, const String& str, uint64 targetid) {
	if (isPlayer())
		((PlayerImplementation*) this)->sendSystemMessage(file, str, targetid);
}

float CreatureObjectImplementation::getDistanceTo(CreatureObject* targetCreature) {
	// TEMP till
	float x = targetCreature->getPositionX();
	float y = targetCreature->getPositionY();

	float deltaX = x - positionX;
	float deltaY = y - positionY;

	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

void CreatureObjectImplementation::mountCreature(MountCreature* mnt, bool lockMount) {
	if (mnt != mount || isMounted() || mnt == NULL)
		return;

	if (mount->isDisabled() || !isInRange(mount, 5) || isKnockedDown())
		return;

	if (!mountCooldown.isPast())
		return;

	mountCooldown.update();
	mountCooldown.addMiliTime(3000);

	setPosture(CreaturePosture::UPRIGHT);

	parent = mount;
	linkType = 4;
	broadcastMessage(link(mount));

	try {
		if (lockMount)
			mnt->wlock(_this);

		if (mount == NULL) {
			if (lockMount)
				mnt->unlock();
			return;
		}

		mount->setState(CreatureState::MOUNTEDCREATURE);
		mount->updateStates();

		updateSpeed(mount->getSpeed(), mount->getAcceleration());
		setState(CreatureState::RIDINGMOUNT);
		updateStates();

		if (lockMount)
			mnt->unlock();
	} catch (...) {
		if (lockMount)
			mnt->unlock();
	}
}

void CreatureObjectImplementation::dismount(bool lockMount, bool ignoreCooldown) {
	if (parent == NULL || mount == NULL || !isMounted())
		return;

	if (!ignoreCooldown && !mountCooldown.isPast())
		return;

	mountCooldown.update();
	mountCooldown.addMiliTime(1000);

	linkType = 4;
	UpdateContainmentMessage* msg = new UpdateContainmentMessage(objectID, 0, 0xFFFFFFFF);
	broadcastMessage(msg);

	MountCreature* mnt = mount;

	try {
		if (lockMount)
			mnt->wlock(_this);

		if (mount != NULL) {
			mount->clearState(CreatureState::MOUNTEDCREATURE);
			mount->updateStates();
		}

		updateSpeed(5.376f, 1.549f);
		clearState(CreatureState::RIDINGMOUNT);
		updateStates();

		if (lockMount)
			mnt->unlock();
	} catch (...) {
		if (lockMount)
			mnt->unlock();
	}

	parent = NULL;
}

void CreatureObjectImplementation::addCashCredits(uint32 credits) {
	cashCredits = cashCredits + credits;

	if (!isPlayer())
		return;

	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateCashCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::addBankCredits(uint32 credits) {
	bankCredits = bankCredits + credits;

	if (!isPlayer())
		return;

	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateBankCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::updateCashCredits(uint32 credits) {
	cashCredits = credits;

	if (!isPlayer())
		return;

	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateCashCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::updateBankCredits(uint32 credits) {
	bankCredits = credits;

	if (!isPlayer())
		return;

	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateBankCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::subtractCashCredits(uint32 credits) {
	cashCredits = cashCredits - credits;

	if (!isPlayer())
		return;

	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateCashCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::subtractBankCredits(uint32 credits) {
	bankCredits = bankCredits - credits;

	if (!isPlayer())
		return;

	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateBankCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

bool CreatureObjectImplementation::verifyCashCredits(uint32 creditsToRemove) {
	if (cashCredits >= creditsToRemove) {
	 	return true;
	} else {
	 	return false;
	}
}

bool CreatureObjectImplementation::verifyBankCredits(uint32 creditsToRemove) {
	if (bankCredits >= creditsToRemove) {
	 	return true;
	} else {
	 	return false;
	}
}

void CreatureObjectImplementation::updateHAMBars() {
	CreatureObjectMessage6* msg = new CreatureObjectMessage6(_this);
	broadcastMessage(msg);
}

void CreatureObjectImplementation::updateBaseStats() {
	if (!isPlayer())
		return;

	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateBaseStats();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::addBuff(int buffCRC, float duration) {
	if (isPlayer())
		((PlayerImplementation*) this)->addBuff(buffCRC, duration);
}

// removeFromList - if iterating through all of the buffs, it could mess up
// the iteration if the .get(i) is off...
void CreatureObjectImplementation::removeBuff(const uint32 buffCRC, bool removeFromList) {
	info("CreatureObjectImplementation::removeBuff started");
	// TODO: call debuff?
	if (!hasBuff(buffCRC))
		return;

	Buff* buff = creatureBuffs.get(buffCRC);

	// Bad value return
	if (buff == NULL) {
		// if we should delete from the list then lets kill it
		if (removeFromList)
			creatureBuffs.drop(buffCRC);
		return;
	}

	buff->deActivateBuff(_this);

	// cleanup buff

	// remove from list
	if (removeFromList) {
		if (!creatureBuffs.drop(buffCRC))
			return;

		try {
			//delete buff;
			//buff = NULL;
		} catch (...) {
			StringBuffer msg;
			msg << "CreatureObjectImplementation::removeBuff exception around deleting buff (" << hex << buffCRC << dec << ")";
			info(msg.toString());
		}
	}

	info("CreatureObjectImplementation::removeBuff completed");
}


void CreatureObjectImplementation::applyBuff(BuffObject *bo) {
	if (bo == NULL)
		return;

	Buff *buff = bo->getBuff();
	applyBuff(buff);

	bo->finalize();
}

void CreatureObjectImplementation::applyBuff(Buff *buff) {
	if (buff == NULL || buff->getBuffCRC() <= 0 || buff->getBuffDuration() <= 0)
	{
		//System::out << "returning null for applyBuff" << endl;
		return;
	}

	//System::out << "applyBuff()" << endl;
	// Other code should handle returning an error message
	// if a previous buff already exists - safety net - make sure we don't double up
	if (hasBuff(buff->getBuffCRC()))
		removeBuff(buff->getBuffCRC());

	creatureBuffs.put(buff->getBuffCRC(), buff);

	buff->activateBuff(_this, server);

	CreatureObjectMessage3* msg1 = new CreatureObjectMessage3(_this);
	CreatureObjectMessage6* msg2 = new CreatureObjectMessage6(_this);

	Vector<BaseMessage*> msgs;
	msgs.add(msg1);
	msgs.add(msg2);
	broadcastMessages(msgs);

	activateRecovery();
}

// TODO: CreatureObjectImplementation::saveBuffs(bool doUpdateCreature)
// save the current duration onto the creature object so they can be
// loaded back when they login

void CreatureObjectImplementation::removeBuffs(bool doUpdateClient) {

	for (int i=0; i < creatureBuffs.size(); i++) {
		Buff* buff = creatureBuffs.get(i);
		if (buff != NULL) {
			removeBuff(buff->getBuffCRC(), false);
		}
	}

	creatureBuffs.removeAll();

	if (doUpdateClient) {
		resetHAMBars(true);
	}

	/*
	CreatureObjectMessage6* msg = new CreatureObjectDeltaMessage6(_this);
	broadcastMessage(msg);
	*/
}

bool CreatureObjectImplementation::isLootOwner(CreatureObject* creature) {
	int maxDmg = 0;
	int i = 0;

	for (; i < damageMap.size(); i++) {
		int damage = damageMap.get(i);

		if (damage > maxDmg)
			maxDmg = damage;
	}

	if (maxDmg > 0 && damageMap.get(creature) == maxDmg)
		return true;

	GroupObject* group = ((Player*)creature)->getGroupObject();

	if (group != NULL)
		for (i = 0; i < group->getGroupSize(); i++)
			if (damageMap.get(group->getGroupMember(i)) == maxDmg)
				return true;

	return false;
}

CreatureObject* CreatureObjectImplementation::getLootOwner() {
	int maxDmg = 0;
	int i = 0;
	int index = -1;

	for (; i < damageMap.size(); i++) {
		int damage = damageMap.get(i);

		if (damage > maxDmg) {

			maxDmg = damage;
			index = i;

		}
	}

	if (index == -1)
		return NULL;
	else
		return damageMap.elementAt(index)->getKey();
}

void CreatureObjectImplementation::removeFromDamageMap(CreatureObject* target) {
	if (damageMap.drop(target)) {
		target->release();
	}
}

void CreatureObjectImplementation::addDamage(CreatureObject* creature, uint32 damage) {
	if (damageMap.contains(creature))
		damageMap.get(creature) += damage;
	else {
		creature->acquire();
		damageMap.put(creature, damage);
	}

}

float CreatureObjectImplementation::calculateBFRatio() {
	if (shockWounds <= 250)
		return 0;
	else
		return (float)((shockWounds-250)/1000);
}

void CreatureObjectImplementation::updateCharacterAppearance() {
	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateCharacterAppearance();
	dcreo3->updateHeight();
	dcreo3->close();
	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::explode(int level, bool destroy) {

	String explodeStr;
	if (level < 2)
		explodeStr = "clienteffect/lair_damage_medium.cef";
	else
		explodeStr = "clienteffect/combat_explosion_lair_large.cef";

	String extraStr = "";

	PlayClientEffectObjectMessage* explode = new PlayClientEffectObjectMessage(_this, explodeStr, extraStr);
	broadcastMessage(explode);

	PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc(explodeStr, zoneID, positionX, positionZ, positionY);
	broadcastMessage(explodeLoc);

	if (destroy) {
		SceneObjectDestroyMessage* destroyMsg = new SceneObjectDestroyMessage(_this);
		broadcastMessage(destroyMsg);
	}

}


//Medic & Doctor
int CreatureObjectImplementation::healDamage(CreatureObject* target, int damage, uint8 attribute, bool doBattleFatigue) {
	if (!CreatureAttribute::isHAM(attribute))
		return 0;

	if (!target->hasDamage())
		return 0;

	int healableDamage = 0;

	switch (attribute) {
	case CreatureAttribute::HEALTH:
		healableDamage = (damage > target->getHealthDamage()) ? target->getHealthDamage() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (!target->changeHealthBar(healableDamage))
			healableDamage = 0;

		break;
	case CreatureAttribute::ACTION:
		healableDamage = (damage > target->getActionDamage()) ? target->getActionDamage() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (!target->changeActionBar(healableDamage))
			return healableDamage = 0;

		break;
	case CreatureAttribute::MIND:
		healableDamage = (damage > target->getMindDamage()) ? target->getMindDamage() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (!target->changeMindBar(healableDamage))
			return healableDamage = 0;

		break;
	}

	revive(target);

	return healableDamage;
}

int CreatureObjectImplementation::healWound(CreatureObject* target, int damage, uint8 attribute, bool doBattleFatigue) {
	if (!target->hasWounds())
		return 0;

	int healableDamage = 0;

	switch (attribute) {
	case CreatureAttribute::HEALTH:
		healableDamage = (damage > target->getHealthWounds()) ? target->getHealthWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeHealthWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::ACTION:
		healableDamage = (damage > target->getActionWounds()) ? target->getActionWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeActionWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::MIND:
		healableDamage = (damage > target->getMindWounds()) ? target->getMindWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeMindWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::STRENGTH:
		healableDamage = (damage > target->getStrengthWounds()) ? target->getStrengthWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeStrengthWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::CONSTITUTION:
		healableDamage = (damage > target->getConstitutionWounds()) ? target->getConstitutionWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeConstitutionWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::QUICKNESS:
		healableDamage = (damage > target->getQuicknessWounds()) ? target->getQuicknessWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeQuicknessWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::STAMINA:
		healableDamage = (damage > target->getStaminaWounds()) ? target->getStaminaWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeStaminaWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::FOCUS:
		healableDamage = (damage > target->getFocusWounds()) ? target->getFocusWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeFocusWoundsBar(-healableDamage))
			return healableDamage;

		break;
	case CreatureAttribute::WILLPOWER:
		healableDamage = (damage > target->getWillpowerWounds()) ? target->getWillpowerWounds() : damage;

		if (doBattleFatigue)
			healableDamage -= (int)round((float)healableDamage * target->calculateBFRatio());

		if (target->changeWillpowerWoundsBar(-healableDamage))
			return healableDamage;

		break;
	}

	return 0;
}

int CreatureObjectImplementation::healEnhance(CreatureObject* target, int amount, float duration, uint8 attribute, bool doBattleFatigue) {
	Buff* buff = new Buff(BuffCRC::TEST_FIRST);

	if (doBattleFatigue)
		amount -= (int) round((float)amount * target->calculateBFRatio());

	switch (attribute) {
	case CreatureAttribute::HEALTH:
		buff->setBuffCRC(BuffCRC::MEDICAL_ENHANCE_HEALTH);
		buff->setHealthBuff(amount);
		break;
	case CreatureAttribute::ACTION:
		buff->setBuffCRC(BuffCRC::MEDICAL_ENHANCE_ACTION);
		buff->setActionBuff(amount);
		break;
	case CreatureAttribute::STRENGTH:
		buff->setBuffCRC(BuffCRC::MEDICAL_ENHANCE_STRENGTH);
		buff->setStrengthBuff(amount);
		break;
	case CreatureAttribute::CONSTITUTION:
		buff->setBuffCRC(BuffCRC::MEDICAL_ENHANCE_CONSTITUTION);
		buff->setConstitutionBuff(amount);
		break;
	case CreatureAttribute::QUICKNESS:
		buff->setBuffCRC(BuffCRC::MEDICAL_ENHANCE_QUICKNESS);
		buff->setQuicknessBuff(amount);
		break;
	case CreatureAttribute::STAMINA:
		buff->setBuffCRC(BuffCRC::MEDICAL_ENHANCE_STAMINA);
		buff->setStaminaBuff(amount);
		break;
	default:
		return 0;
	}

	buff->setBuffDuration(duration);

	BuffObject* bo = new BuffObject(buff);

	target->applyBuff(bo);

	return amount;
}

bool CreatureObjectImplementation::curePoison(CreatureObject* target, float effectiveness) {
	//TODO: Add in effectiveness once DoT's are restructured
	if (!target->isPoisoned())
		return false;

	if (target->clearState(CreatureState::POISONED)) {
		target->updateStates();
		return true;
	}

	return false;
}

bool CreatureObjectImplementation::cureDisease(CreatureObject* target, float effectiveness) {
	//TODO: Add in effectiveness once DoT's are restructured
	if (!target->isDiseased())
		return false;

	if (target->clearState(CreatureState::DISEASED)) {
		target->updateStates();
		return true;
	}

	return false;
}

bool CreatureObjectImplementation::extinguishFire(CreatureObject* target, float effectiveness) {
	//TODO: Add in effectiveness once DoT's are restructured
	if (!target->isOnFire())
		return false;

	if (target->clearState(CreatureState::ONFIRE)) {
		target->updateStates();
		return true;
	}

	return false;
}

bool CreatureObjectImplementation::healState(CreatureObject* target, uint64 state) {
	if (!target->hasState(state))
		return false;

	if (target->clearState(state)) {
		target->updateStates();
		return true;
	}

	return false;
}

bool CreatureObjectImplementation::revive(CreatureObject* target, bool forcedChange) {
	//This method is used to bring a player out of Incapacitation
	if (!target->isIncapacitated() && !target->isDead())
		return false;

	if (!target->isRevivable() && !forcedChange)
		return false;

	if (target->isPlayer())
		((Player*)target)->changePosture(CreaturePosture::UPRIGHT);
	else
		target->setPosture(CreaturePosture::UPRIGHT, (forcedChange ? true : false));

	return true;
}

bool CreatureObjectImplementation::resurrect(CreatureObject* target, bool forcedChange) {
	if (!target->isDead())
		return false;

	if (!target->isResurrectable() && !forcedChange)
		return false;

	if (target->isPlayer()) {
		((Player*)target)->resurrect();
	} else {
		if (!revive(target, true))
			return false;
	}

	return true;
}

void CreatureObjectImplementation::deactivateWoundTreatment() {
	float modSkill = (float)getSkillMod("healing_wound_speed");
	int delay = (int)round((modSkill * -(2.0f / 25.0f)) + 20.0f);

	//Force the delay to be at least 4 seconds.
	delay = (delay < 4) ? 4 : delay;

	doWoundTreatment = false;
	if (woundTreatmentEvent == NULL) {
		woundTreatmentEvent = new WoundTreatmentOverEvent(this, delay);
		server->addEvent(woundTreatmentEvent);
	}
}

void CreatureObjectImplementation::activateWoundTreatment() {
	doWoundTreatment = true;
	woundTreatmentEvent = NULL;
	sendSystemMessage("healing_response", "healing_response_59"); //You are now ready to heal more wounds or apply more enhancements.
}

void CreatureObjectImplementation::deactivateInjuryTreatment() {
	float modSkill = (float)getSkillMod("healing_injury_speed");
	int delay = (int)round((modSkill * -(1.0f / 8.0f)) + 21.0f);

	//Force the delay to be at least 4 seconds.
	delay = (delay < 4) ? 4 : delay;

	doInjuryTreatment = false;
	if (injuryTreatmentEvent == NULL) {
		injuryTreatmentEvent = new InjuryTreatmentOverEvent(this, delay);
		server->addEvent(injuryTreatmentEvent);
	}
}

void CreatureObjectImplementation::activateInjuryTreatment() {
	doInjuryTreatment = true;
	injuryTreatmentEvent = NULL;
	sendSystemMessage("healing_response", "healing_response_58"); //You are now ready to heal more damage.
}

void CreatureObjectImplementation::deactivateStateTreatment() {
	float modSkill = (float)getSkillMod("healing_injury_speed");
	int delay = (int)round((modSkill * -(1.0f / 8.0f)) + 21.0f);

	//Force the delay to be at least 4 seconds.
	delay = (delay < 4) ? 4 : delay;

	doStateTreatment = false;
	if (stateTreatmentEvent == NULL) {
		stateTreatmentEvent = new StateTreatmentOverEvent(this, delay);
		server->addEvent(stateTreatmentEvent);
	}
}

void CreatureObjectImplementation::activateStateTreatment() {
	doStateTreatment = true;
	stateTreatmentEvent = NULL;
	sendSystemMessage("healing_response", "healing_response_59 ");
}

void CreatureObjectImplementation::deactivateConditionTreatment() {
	float modSkill = (float)getSkillMod("healing_wound_speed");
	int delay = (int)round((modSkill * -(2.0f / 25.0f)) + 20.0f);

	//Force the delay to be at least 4 seconds.
	delay = (delay < 4) ? 4 : delay;

	doConditionTreatment = false;
	if (conditionTreatmentEvent == NULL) {
		conditionTreatmentEvent = new ConditionTreatmentOverEvent(this, delay);
		server->addEvent(conditionTreatmentEvent);
	}
}

void CreatureObjectImplementation::activateConditionTreatment() {
	doConditionTreatment = true;
	conditionTreatmentEvent = NULL;
	sendSystemMessage("healing_response", "healing_response_59 ");
}

int CreatureObjectImplementation::getMedicalFacilityRating() {
	if (!isInBuilding()) //TODO: Add in search for nearby surgical droid
		return 0;

	int buildingType = getBuildingType();

	if (buildingType == BuildingObjectImplementation::MEDICAL_CENTER || buildingType == BuildingObjectImplementation::CLONING_FACILITY)
		return 100;

	return 65;
}

//This is a temp function.  I'm going to add a faction table in creature manager soon
bool CreatureObjectImplementation::hatesFaction(uint faction) {
	if (isImperial() && faction == String("rebel").hashCode())
		return true;
	else if (isRebel() && faction == String("imperial").hashCode())
		return true;
	else
		return false;
}

bool CreatureObjectImplementation::isAttackable() {
	if (isNonPlayerCreature() && ((Creature *) _this)->isMount())
		return !((MountCreature *) _this)->isDisabled();
	else
		return !isIncapacitated() && !isDead();
}

bool CreatureObjectImplementation::isAttackableBy(CreatureObject* creature) {
	if (creature->hatesFaction(this->getFaction())) {
		if (creature->isPlayer() && ((Player *) creature)->isOnLeave())
			return false;
		else
			return true;
	}

	return (pvpStatusBitmask & CreatureFlag::ATTACKABLE);
}

void CreatureObjectImplementation::activateCamo(unsigned int camoCRC ,unsigned int time,unsigned int ms) {
		MaskScentEvent* event = new MaskScentEvent(_this,camoCRC,time);

		maskScentEvent = event;

		server->addEvent(maskScentEvent);
		setMaskScent(ms);
		//addQueuedState(maskScentEvent->getNameCRC());
		addBuff(maskScentEvent->getNameCRC(),time);
		setState(CreatureState::MASKSCENT);
		updateStates();

		if (camoType == CamoSkill::MASKSCENT)
			sendSystemMessage("skl_use", "sys_scentmask_start");
		else
			sendSystemMessage("skl_use", "sys_conceal_start");
}

void CreatureObjectImplementation::deactivateCamo(bool forced) {
	if (maskScentEvent != NULL) {

		if (forced)
			sendSystemMessage("skl_use", "sys_scentmask_break");
		else if (getCamoType() == CamoSkill::MASKSCENT)
			sendSystemMessage("skl_use", "sys_scentmask_stop ");
		else
			sendSystemMessage("skl_use", "sys_conceal_stop ");



		//removeQueuedState(maskScentEvent->getNameCRC());
		removeBuff(maskScentEvent->getNameCRC());
		server->removeEvent(maskScentEvent);
		camoType = 11;
		clearState(CreatureState::MASKSCENT);
		updateStates();
		maskScentEvent = NULL;

		activateCamoLock();
	}
}

void CreatureObjectImplementation::activateCamoLock() {
	camoLock.update();
	camoLock.addMiliTime(60000);
}

bool CreatureObjectImplementation::isCamoCooldownActive() {
	return camoLock.isPast();
}

int CreatureObjectImplementation::getCamoCooldownLeft() {
	return -1 * camoLock.miliDifference();
}

void CreatureObjectImplementation::onDeath() {
}
void CreatureObjectImplementation::onClone() {
}
void CreatureObjectImplementation::onBlinded() {
}
void CreatureObjectImplementation::onDizzied() {
}
void CreatureObjectImplementation::onStunned() {
}
void CreatureObjectImplementation::onIntimidated() {
}
