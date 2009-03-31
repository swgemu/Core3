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


#include "events/BurstRunOverEvent.h"
#include "events/BurstRunNotifyAvailableEvent.h"
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
	bankContainer = NULL;

	weaponSpeedModifier = 1;
	centeredBonus = 0;

	creatureSkillsCount = 0;
	creatureSkills.setInsertPlan(SortedVector<Skill*>::NO_DUPLICATE);
	creatureSkills.setNullValue(NULL);

	damageMap.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);
	damageMap.setNullValue(0);
	cooldownMap.setInsertPlan(SortedVector<String>::NO_DUPLICATE);
	cooldownMap.setNullValue(0);

	stfFile = "species";

	boneType = "";
	hideType = "";
	meatType = "";

	complexity = 10.f;

	volume = 0x0085E5CA;

	actionCounter = 0;

	// CREO1 operands
	cashCredits = 25000;
	bankCredits = 25000;

	// CREO3 operands
	postureState = CreaturePosture::UPRIGHT;
	stateBitmask = oldStateBitmask = 0;
	optionsBitmask = 0x80;

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
	moodid = 0;
	mood = Races::getMood(moodid);
	moodStr = Races::getMoodStr(mood);

	weaponObject = NULL;
	targetObject = NULL;
	hairObj = NULL;

	hamUpdateCounter = 0;
	hamMaxUpdateCounter = 0;
	hamBaseUpdateCounter = 0;
	encumbUpdateCounter = 0;
	woundsUpdateCounter = 0;

	setBaseHealth(1000);
	setBaseStrength(500);
	setBaseConstitution(500);
	setBaseAction(1000);
	setBaseQuickness(500);
	setBaseStamina(500);
	setBaseMind(1000);
	setBaseFocus(500);
	setBaseWillpower(500);

	setHealth(3000);
	setStrength(3000);
	setConstitution(3000);
	setAction(3000);
	setQuickness(3000);
	setStamina(3000);
	setMind(3000);
	setFocus(3000);
	setWillpower(3000);

	setHealthMax(3000);
	setStrengthMax(3000);
	setConstitutionMax(3000);
	setActionMax(3000);
	setQuicknessMax(3000);
	setStaminaMax(3000);
	setMindMax(3000);
	setFocusMax(3000);
	setWillpowerMax(3000);

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
	burstRunning = false;

	watchID = 0;
	listenID = 0;

	danceBuffDuration = 0.0f;
	musicBuffDuration = 0.0f;

	danceBuffStrength = 0.0f;
	musicBuffStrength = 0.0f;

	listeners.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);
	watchers.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);

	// wounds
	setHealthWounds(0);
	setStrengthWounds(0);
	setConstitutionWounds(0);
	setActionWounds(0);
	setQuicknessWounds(0);
	setStaminaWounds(0);
	setMindWounds(0);
	setFocusWounds(0);
	setWillpowerWounds(0);

	// AKA Battle Fatigue
	shockWounds = 0;

	// misc
	pvpStatusBitmask = 0x10;
	faction = 0;
	factionRank = 0;

	// combat
/*	fireDotType = 0;
	fireDotStrength = 0;

	poisonDotType = 0;
	poisonDotStrength = 0;

	diseaseDotType = 0;
	diseaseDotStrength = 0;

	bleedingDotType = 0;
	bleedingDotStrength = 0;*/

	accuracy = 0;
	accuracyBonus = 0;

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

	burstRunOverEvent = new BurstRunOverEvent(this);
	burstRunNotifyAvailableEvent = new BurstRunNotifyAvailableEvent(this);
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
	camoXPTraget = NULL;
	campMod = 0;
	petNumber = 0;

	ferocity = 0;
	baby = false;

	//Regeneration modifiers
	combatRegenModifier = 1.0f;
	peacedRegenModifier = 1.0f;

	dotMap = new DamageOverTimeMap();

	timeOfDeath = 0;
}

CreatureObjectImplementation::~CreatureObjectImplementation() {
	if (dizzyFallDownEvent != NULL) {
		if (dizzyFallDownEvent->isQueued())
			server->removeEvent(dizzyFallDownEvent);

		delete dizzyFallDownEvent;
		dizzyFallDownEvent = NULL;
	}

	if (burstRunOverEvent != NULL) {
		if (burstRunOverEvent->isQueued())
			server->removeEvent(burstRunOverEvent);

		delete burstRunOverEvent;
		burstRunOverEvent = NULL;
	}

	if (burstRunNotifyAvailableEvent != NULL) {
		if (burstRunNotifyAvailableEvent->isQueued())
			server->removeEvent(burstRunNotifyAvailableEvent);

		delete burstRunNotifyAvailableEvent;
		burstRunNotifyAvailableEvent = NULL;
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

	if (bankContainer != NULL) {
		bankContainer->finalize();
		bankContainer = NULL;
	}

	if (inventory != NULL) {
		info("undeploying creature object inventory");

		inventory->finalize();
		inventory = NULL;
	}

	if (dotMap != NULL) {
		// TODO: clear & delete dotMap
		dotMap = NULL;
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

	if (parent != NULL)	{
		if (parent != NULL && parent->isCell()) {
			BuildingObject* building = (BuildingObject*) parent->getParent();

			//info("sending building to client through CreatureObjectImplementation::sendToOwner");
			building->sendTo((Player*)_this, false);
		} else
			parent->sendTo((Player*)_this, false);
	}

	sendTo(player, doClose);
}

void CreatureObjectImplementation::sendTo(Player* player, bool doClose) {
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
		SceneObjectImplementation::close(client);
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

	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
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

void CreatureObjectImplementation::doEmote(uint32 targetid, uint32 emoteid, bool showtext) {
	//Emote* emsg = new Emote(_this, targetid, emoteid, showtext);
	//broadcastMessage(emsg);

	try {
		zone->lock();

		for (int i = 0; i < _this->inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) _this->getInRangeObject(i))->_this);

			if (object->isPlayer()) {
				Player* creature = (Player*) object;

				Emote* emsg = new Emote(creature, _this, targetid, emoteid, showtext);
				creature->sendMessage(emsg);
			}
		}

		zone->unlock();
	} catch (...) {
		zone->unlock();
		System::out << "exception ChatManagerImplementation::handleEmote(Player* player, Message* pack)\n";
	}
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

void CreatureObjectImplementation::sendCombatSpamTrap(CreatureObject* defender, TangibleObject* item, uint32 damage, const String& skill, bool areaSpam) {
	try {
		//info("sending combat spam");

		zone->lock();

		bool needLimiting = inRangeObjectCount() > 40;

		if (areaSpam)
		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());

			if (object->isPlayer() && isInRange(object, 70)) {
				Player* player = (Player*) object;

				CombatSpam* msg = new CombatSpam(_this, defender, item, damage, "trap//trap", skill, player);
				player->sendMessage(msg);
			}
		}
		else if (isPlayer()) {
			CombatSpam* msg = new CombatSpam(_this, defender, item, damage, "trap//trap", skill, _this);
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

		if (postureState == CreaturePosture::UPRIGHT) {
			if (isBurstRunning()) {
				updateSpeed(8.0f, 0.922938f);
			} else
				updateSpeed(5.376f, 1.549f);
		}

		if (postureState == CreaturePosture::PRONE) {
			float proneModifier = calculateProneSpeedModifier();

			if (isBurstRunning()) {
				updateSpeed(1.2f * proneModifier, 0.7745f / proneModifier);
			} else {
				updateSpeed(0.7f * proneModifier, 0.7745f / proneModifier);
			}
		}
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


int CreatureObjectImplementation::addDotState(CreatureObject* attacker,uint64 dotID, uint64 dotType, uint32 str, uint8 type, uint32 duration, float potency,uint32 defense) {
	//System::out << "add dot\n";
	return dotMap->addDot(attacker,_this, dotID ,duration,dotType, type , str,potency,defense);
}

bool CreatureObjectImplementation::healDot(uint64 dotType,int reduction) {
	return dotMap->healState(_this,dotType,reduction);
}

bool CreatureObjectImplementation::setState(uint64 state) {
	if (!(stateBitmask & state)) {
		stateBitmask |= state;
		return true;
	} else
		return false;
}

void CreatureObjectImplementation::updateDotStates(uint64 oldStates, uint64 newStates) {
	stateBitmask &= ~oldStates;
	stateBitmask |= newStates;
	updateStates();
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
		case CreatureState::RALLIED:
			showFlyText("combat_effects", "no_rally", 0xFF, 0, 0);
			break;
		default:
			break;
		}

		stateBitmask &= ~state;
		return true;
	} else
		return false;
}

void CreatureObjectImplementation::removeState(uint64 state) {
	stateBitmask &= ~state;
	updateStates();
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
	dotMap->clear();
	updateStates();
}

bool CreatureObjectImplementation::changeHAMBars(int32 health, int32 action, int32 mind, bool forcedChange) {
	int32 newHealth = getHealth() + health;
	int32 newAction = getAction() + action;
	int32 newMind = getMind() + mind;

	if (isIncapacitated()) {
		if ((getHealth() == 0) && (newHealth > 0) && (getAction() > 0) && (getMind() > 0))
			setPosture(CreaturePosture::UPRIGHT);

		if ((getAction() == 0) && (newAction > 0) && (getHealth() > 0) && (getMind() > 0))
			setPosture(CreaturePosture::UPRIGHT);

		if ((getMind() == 0) && (newMind > 0) && (getAction() > 0) && (getHealth() > 0))
			setPosture(CreaturePosture::UPRIGHT);
	}

	if (newHealth <= 0 || newAction <= 0 || newMind <= 0) {
		if (forcedChange) {
			setHAMBars(MAX(newHealth, 0), MAX(newAction, 0), MAX(newMind, 0));

			incapacitateSelf();

			return false;

		} else {
			if (newHealth <= 0)
				newHealth = 1;
			if (newAction <= 0)
				newAction = 1;
			if (newMind <= 0)
				newMind = 1;
		}
	}

	setHAMBars(MIN(newHealth, getHealthMax() - getHealthWounds()), MIN(newAction, getActionMax() - getActionWounds()), MIN(newMind, getMindMax() - getMindWounds()));
	//setHAMBars(MIN(MAX(newHealth,1), getHealthMax() - getHealthWounds()), MIN(MAX(newAction,1), getActionMax() - getActionWounds()), MIN(MAX(newMind,1), getMindMax() - getMindWounds()));

	return true;
}

void CreatureObjectImplementation::changeMaxHAMBars(int32 health, int32 action, int32 mind) {
	int32 newMaxHealth = getHealthMax() + health;
	int32 newMaxAction = getActionMax() + action;
	int32 newMaxMind = getMindMax() + mind;

	setMaxHAMBars(newMaxHealth, newMaxAction, newMaxMind);
}


bool CreatureObjectImplementation::changeHAMWounds(int32 health, int32 action, int32 mind, bool forcedChange) {
	int32 newHealthWounds = getHealthWounds() + health;
	int32 newActionWounds = getActionWounds() + action;
	int32 newMindWounds = getMindWounds() + mind;

	setHAMWoundsBars(MIN(newHealthWounds, getBaseHealth() - 1), MIN(newActionWounds, getBaseAction() - 1), MIN(newMindWounds, getBaseMind() - 1));

	return true;

}

bool CreatureObjectImplementation::changeWoundsBar(uint8 attribute, int32 value, bool forcedChange) {
	if (value < 0 && -value > getWounds(attribute))
		value = -1 * getWounds(attribute);

	int32 newWounds = getWounds(attribute) + value;

	//if (newWounds >= getAttributeMax(attribute)) {
	if (newWounds >= getAttributeMax(attribute)) {
		if (!forcedChange) {
			newWounds = getAttributeMax(attribute) - 1;
		}
	}

	setWoundsBar(attribute, MIN(newWounds, getAttributeMax(attribute) - 1));

	if (attribute != CreatureAttribute::HEALTH && attribute != CreatureAttribute::ACTION && attribute != CreatureAttribute::MIND)
		changeAttributeBar(attribute,-1 * value);

	return true;
}

bool CreatureObjectImplementation::changeHealthWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::HEALTH, value, forcedChange);
}

bool CreatureObjectImplementation::changeStrengthWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::STRENGTH, value, forcedChange);
}

bool CreatureObjectImplementation::changeConstitutionWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::CONSTITUTION, value, forcedChange);
}

bool CreatureObjectImplementation::changeActionWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::ACTION, value, forcedChange);
}

bool CreatureObjectImplementation::changeQuicknessWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::QUICKNESS, value, forcedChange);
}

bool CreatureObjectImplementation::changeStaminaWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::STAMINA, value, forcedChange);
}

bool CreatureObjectImplementation::changeMindWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::MIND, value, forcedChange);
}

bool CreatureObjectImplementation::changeFocusWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::FOCUS, value, forcedChange);
}

bool CreatureObjectImplementation::changeWillpowerWoundsBar(int32 value, bool forcedChange) {
	return changeWoundsBar(CreatureAttribute::WILLPOWER, value, forcedChange);
}

bool CreatureObjectImplementation::changeAttributeBar(uint8 attribute, int32 value, bool forcedChange) {
	int32 newValue = getAttribute(attribute) + value;

	if (newValue <= 0) {
		if (forcedChange) {
			setAttributeBar(attribute, 0);

			if (CreatureAttribute::isHAM(attribute))
				incapacitateSelf();
		}

		return false;
	}

	setAttributeBar(attribute, MIN(newValue, getAttributeMax(attribute) - getWounds(attribute)));
	return true;
}

bool CreatureObjectImplementation::changeHealthBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::HEALTH, value, forcedChange);
}

bool CreatureObjectImplementation::changeStrengthBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::STRENGTH, value, forcedChange);
}

bool CreatureObjectImplementation::changeConstitutionBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::CONSTITUTION, value, forcedChange);
}

bool CreatureObjectImplementation::changeActionBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::ACTION, value, forcedChange);
}

bool CreatureObjectImplementation::changeQuicknessBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::QUICKNESS, value, forcedChange);
}

bool CreatureObjectImplementation::changeStaminaBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::STAMINA, value, forcedChange);
}

bool CreatureObjectImplementation::changeMindBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::MIND, value, forcedChange);
}

bool CreatureObjectImplementation::changeFocusBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::FOCUS, value, forcedChange);
}

bool CreatureObjectImplementation::changeWillpowerBar(int32 value, bool forcedChange) {
	return changeAttributeBar(CreatureAttribute::WILLPOWER, value, forcedChange);
}


void CreatureObjectImplementation::changeMaxAttributeBar(uint8 attribute, int32 value, bool updateClient) {
	if (value == 0)
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->changeMaxAttributeBar(attribute, value);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		changeAttributeMax(attribute, value);

	// bring down current stat to match max
	if (getAttribute(attribute) > (getAttributeMax(attribute) - getWounds(attribute))) {
		if (updateClient)
			setAttributeBar(attribute, getAttributeMax(attribute) - getWounds(attribute));
		else
			setAttribute(attribute, getAttributeMax(attribute) - getWounds(attribute));
	}
}

void CreatureObjectImplementation::changeMaxHealthBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::HEALTH, value, updateClient);
}

void CreatureObjectImplementation::changeMaxStrengthBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::STRENGTH, value, updateClient);
}

void CreatureObjectImplementation::changeMaxConstitutionBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::CONSTITUTION, value, updateClient);
}

void CreatureObjectImplementation::changeMaxActionBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::ACTION, value, updateClient);
}

void CreatureObjectImplementation::changeMaxQuicknessBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::QUICKNESS, value, updateClient);
}

void CreatureObjectImplementation::changeMaxStaminaBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::STAMINA, value, updateClient);
}

void CreatureObjectImplementation::changeMaxMindBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::MIND, value, updateClient);
}

void CreatureObjectImplementation::changeMaxFocusBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::FOCUS, value, updateClient);
}

void CreatureObjectImplementation::changeMaxWillpowerBar(int32 value, bool updateClient) {
	changeMaxAttributeBar(CreatureAttribute::WILLPOWER, value, updateClient);
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

	//reset maximums for all 9 stats to btheir base values
	setHealthMax(getBaseHealth());
	setStrengthMax(getBaseStrength());
	setConstitutionMax(getBaseConstitution());

	setActionMax(getBaseAction());
	setQuicknessMax(getBaseQuickness());
	setStaminaMax(getBaseStamina());

	setMindMax(getBaseMind());
	setFocusMax(getBaseFocus());
	setWillpowerMax(getBaseWillpower());

	//if wounds for any of the 9 stats have managed to grow larger than
	//the base value then reset them to base - 1
	if (getHealthWounds() > getHealthMax())
		setHealthWounds(getHealthMax() - 1);
	if (getStrengthWounds() > getStrengthMax())
		setStrengthWounds(getStrengthMax() - 1);
	if (getConstitutionWounds() > getConstitutionMax())
		setConstitutionWounds(getConstitutionMax() - 1);

	if (getActionWounds() > getActionMax())
		setActionWounds(getActionMax() - 1);
	if (getQuicknessWounds() > getQuicknessMax())
		setQuicknessWounds(getQuicknessMax() - 1);
	if (getStaminaWounds() > getStaminaMax())
		setStaminaWounds(getStaminaMax() - 1);

	if (getMindWounds() > getMindMax())
		setMindWounds(getMindMax() - 1);
	if (getFocusWounds() > getFocusMax())
		setFocusWounds(getFocusMax() - 1);
	if (getWillpowerWounds() > getWillpowerMax())
		setWillpowerWounds(getWillpowerMax() - 1);

	//if the wound value for any of the 9 stats has managed
	//to become negative, reset it to zero
	if (getHealthWounds() < 0) setHealthWounds(0);
	if (getStrengthWounds() < 0) setStrengthWounds(0);
	if (getConstitutionWounds() < 0) setConstitutionWounds(0);

	if (getActionWounds() < 0) setActionWounds(0);
	if (getQuicknessWounds() < 0) setQuicknessWounds(0);
	if (getStaminaWounds() < 0) setStaminaWounds(0);

	if (getMindWounds() < 0) setMindWounds(0);
	if (getFocusWounds() < 0) setFocusWounds(0);
	if (getWillpowerWounds() < 0) setWillpowerWounds(0);

	//set the current values for each of the 9 stats to max - wounds
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

void CreatureObjectImplementation::setBaseAttributeBar(uint8 attribute, int32 value, bool updateClient) {
	if (value == getBaseAttribute(attribute))
		return;

	int32 originalAmount = getBaseAttribute(attribute);

	if (updateClient) {
		CreatureObjectDeltaMessage1* dcreo1 = new CreatureObjectDeltaMessage1(this);
		dcreo1->updateBaseAttributeBar(attribute, value);
		dcreo1->close();

		((PlayerImplementation*) this)->sendMessage(dcreo1);
	} else
		setBaseAttribute(attribute, value);

	// Change the Max Health to reflect new Base Health
	setAttributeBar(attribute, getAttribute(attribute) + (value - originalAmount));
	setMaxAttributeBar(attribute, getAttributeMax(attribute) + (value - originalAmount), updateClient);
}

void CreatureObjectImplementation::setBaseHealthBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::HEALTH, value, updateClient);
}

void CreatureObjectImplementation::setBaseStrengthBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::STRENGTH, value, updateClient);
}

void CreatureObjectImplementation::setBaseConstitutionBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::CONSTITUTION, value, updateClient);
}

void CreatureObjectImplementation::setBaseActionBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::ACTION, value, updateClient);
}

void CreatureObjectImplementation::setBaseQuicknessBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::QUICKNESS, value, updateClient);
}

void CreatureObjectImplementation::setBaseStaminaBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::STAMINA, value, updateClient);
}

void CreatureObjectImplementation::setBaseMindBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::MIND, value, updateClient);
}

void CreatureObjectImplementation::setBaseFocusBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::FOCUS, value, updateClient);
}

void CreatureObjectImplementation::setBaseWillpowerBar(int32 value, bool updateClient) {
	setBaseAttributeBar(CreatureAttribute::WILLPOWER, value, updateClient);
}

void CreatureObjectImplementation::setHAMBars(int32 health, int32 action, int32 mind) {
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);

	dcreo6->updatePrimaryBars(health, action, mind);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setHAMWoundsBars(int32 health, int32 action, int32 mind) {
	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);

	dcreo3->updateHAMWoundsBars(health, action, mind);
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::setAttributeBar(uint8 attribute, int32 value) {
	if (value == getAttribute(attribute))
		return;

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateAttributeBar(attribute, value);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setHealthBar(int32 value) {
	setAttributeBar(CreatureAttribute::HEALTH, value);
}

void CreatureObjectImplementation::setStrengthBar(int32 value) {
	setAttributeBar(CreatureAttribute::STRENGTH, value);
}

void CreatureObjectImplementation::setConstitutionBar(int32 value) {
	setAttributeBar(CreatureAttribute::CONSTITUTION, value);
}

void CreatureObjectImplementation::setActionBar(int32 value) {
	setAttributeBar(CreatureAttribute::ACTION, value);
}

void CreatureObjectImplementation::setQuicknessBar(int32 value) {
	setAttributeBar(CreatureAttribute::QUICKNESS, value);
}

void CreatureObjectImplementation::setStaminaBar(int32 value) {
	setAttributeBar(CreatureAttribute::STAMINA, value);
}

void CreatureObjectImplementation::setMindBar(int32 value) {
	setAttributeBar(CreatureAttribute::MIND, value);
}

void CreatureObjectImplementation::setFocusBar(int32 value) {
	setAttributeBar(CreatureAttribute::FOCUS, value);
}

void CreatureObjectImplementation::setWillpowerBar(int32 value) {
	setAttributeBar(CreatureAttribute::WILLPOWER, value);
}

void CreatureObjectImplementation::setMaxAttributeBar(uint8 attribute, int32 value, bool updateClient) {
	if (value == getAttributeMax(attribute))
		return;

	if (updateClient) {
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateMaxAttributeBar(attribute, value);
		dcreo6->close();

		broadcastMessage(dcreo6);
	} else
		setAttributeMax(attribute, value);

	// bring down current stat to match max
	if (getAttribute(attribute) > (getAttributeMax(attribute) - getWounds(attribute))) {
		if (updateClient)
			setAttributeBar(attribute, getAttributeMax(attribute) - getWounds(attribute));
		else
			setAttribute(attribute, getAttributeMax(attribute) - getWounds(attribute));
	}
}

void CreatureObjectImplementation::setMaxHealthBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::HEALTH, value, updateClient);
}

void CreatureObjectImplementation::setMaxStrengthBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::STRENGTH, value, updateClient);
}

void CreatureObjectImplementation::setMaxConstitutionBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::CONSTITUTION, value, updateClient);
}

void CreatureObjectImplementation::setMaxActionBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::ACTION, value, updateClient);
}

void CreatureObjectImplementation::setMaxQuicknessBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::QUICKNESS, value, updateClient);
}

void CreatureObjectImplementation::setMaxStaminaBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::STAMINA, value, updateClient);
}

void CreatureObjectImplementation::setMaxMindBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::MIND, value, updateClient);
}

void CreatureObjectImplementation::setMaxFocusBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::FOCUS, value, updateClient);
}

void CreatureObjectImplementation::setMaxWillpowerBar(int32 value, bool updateClient) {
	setMaxAttributeBar(CreatureAttribute::WILLPOWER, value, updateClient);
}

void CreatureObjectImplementation::setWoundsBar(uint8 attribute, int32 value) {
	if (value == getWounds(attribute))
		return;

	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateWoundsBar(attribute, value);
	dcreo3->close();

	broadcastMessage(dcreo3);

	// Update to match max/wounds
	/*setAttributeBar(attribute, MIN(getAttribute(attribute), getAttributeMax(attribute) - getWounds(attribute)));
	if (getAttribute(attribute) < getAttributeMax(attribute))
		activateRecovery();*/

	setAttributeBar(attribute, MIN(getAttribute(attribute), getAttributeMax(attribute) - getWounds(attribute)));
	if (getAttribute(attribute) < getAttributeMax(attribute))
			activateRecovery();
}

void CreatureObjectImplementation::setHealthWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::HEALTH, value);
}

void CreatureObjectImplementation::setStrengthWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::STRENGTH, value);
}

void CreatureObjectImplementation::setConstitutionWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::CONSTITUTION, value);
}

void CreatureObjectImplementation::setActionWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::ACTION, value);
}

void CreatureObjectImplementation::setQuicknessWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::QUICKNESS, value);
}

void CreatureObjectImplementation::setStaminaWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::STAMINA, value);
}

void CreatureObjectImplementation::setMindWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::MIND, value);
}

void CreatureObjectImplementation::setFocusWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::FOCUS, value);
}

void CreatureObjectImplementation::setWillpowerWoundsBar(int32 value) {
	setWoundsBar(CreatureAttribute::WILLPOWER, value);
}

void CreatureObjectImplementation::setMaxHAMBars(int32 health, int32 action, int32 mind) {
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaximumPrimaryBars(health, action, mind);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::doMeditateHeals() {
	int meditateMod = getSkillMod("meditate");

    //Heal dots first.
//	if (isBleeding() || isPoisoned() || isDiseased()) {
		uint32 meditatePower = 20 + (meditateMod / 3);
		//switch (0) {
		//case 0:
			if (isBleeding() && meditateMod >= 15) {
				if (!healDot(CreatureState::BLEEDING,meditatePower)) {
					if (isPlayer())
						sendSystemMessage("dot_message", "decrease_bleeding");
				}
				return;
			}

		//case 1:
			if (isPoisoned() && meditateMod >= 30) {
				if (!healDot(CreatureState::POISONED,meditatePower)) {
					if (isPlayer())
						sendSystemMessage("dot_message", "decrease_poisoned");
				}
				return;
			}

		//case 2:
			if (isDiseased() && meditateMod >= 45) {
				if (!healDot(CreatureState::DISEASED,meditatePower)) {
					if (isPlayer())
						sendSystemMessage("dot_message", "decrease_diseased");
				}
				return;
			}
		//}
	//}

    //If no more dots can be healed, heal wounds.
	if (meditateMod >= 75) {
		doMeditateWoundHeals();
	}
}

void CreatureObjectImplementation::doMeditateWoundHeals() {
	if (!hasWounds())
		return;

	int heal;
	int wounds;
	int skillMeditate = getSkillMod("meditate");

	if (skillMeditate <= 0)
		return;

	if (skillMeditate >= 100)
		heal = 30 + System::random(20);
	else
		heal = 20 + System::random(10);


	uint8 attribute = getRandomWoundedAttribute();
    wounds = getWounds(attribute);
    wounds = (wounds > heal) ? heal : wounds;
    changeWoundsBar(attribute, -heal);

    //Send heal message.
	if (isPlayer()) {
		Player* player = (Player*)_this;
		StfParameter* healParams = new StfParameter;
		healParams->addTO(CreatureAttribute::getName(attribute, true));
        healParams->addDI(heal);
		player->sendSystemMessage("teraskasi", "prose_curewound", healParams);
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

void CreatureObjectImplementation::activateBurstRun(bool bypassChecks) {
	int duration = 30; //seconds of burst run duration.
	int coolDown = 300; //seconds after burst run ends.

	//Check if mounted.
	if (isMounted()) {
		sendSystemMessage("cbt_spam", "no_burst"); //"You cannot burst-run while mounted on a creature or vehicle."
		return;
	}

	//Check if on the Corvette dungeon.
	if (getZoneID() == 39) {
		if (isPlayer()) {
			sendSystemMessage("cbt_spam", "burst_run_space_dungeon"); //"The artificial gravity makes burst running impossible here."
		}
		return;
	}

	//Check if already burst running.
	if (isBurstRunning()) {
		if (bypassChecks) {
			//Renew the end event.
			if (burstRunOverEvent->isQueued()) {
				server->removeEvent(burstRunOverEvent);
				server->addEvent(burstRunOverEvent, duration * 1000);
			}
			if (isPlayer()) {
				sendSystemMessage("cbt_spam", "burstrun_start_single"); //"You run as hard as you can!"
			}
			return;

		} else {
			if (isPlayer()) {
				sendSystemMessage("You are already running.");
			}
			return;
		}
	}

	//Check for other forms of running (force run)
	if (speed > 8.0f) {
		if (isPlayer()) {
			sendSystemMessage("You are already running.");
		}
		return;
	}

	//Check states, HAM, etc.
	if (!bypassChecks) {
		bool success = burstRunChecks();
		if (!success) {
			return;
		}
	}

	//Apply burst run.
	if (isProne()) {
		float proneModifier = calculateProneSpeedModifier();
		updateSpeed(1.2f * proneModifier, 0.7745f / proneModifier);
	} else {
		updateSpeed(8.0f, 0.922938f);
	}

	burstRunning = true;

	//Queue the end event.
	server->addEvent(burstRunOverEvent, duration * 1000);

	if (isPlayer()) {
		sendSystemMessage("cbt_spam", "burstrun_start_single"); //"You run as hard as you can!"

		if (!bypassChecks) {
			//Queue the notify burst run available event.
			int delay = (duration + coolDown) * 1000;
			if (isPlayer()) {
				server->addEvent(burstRunNotifyAvailableEvent, delay);
			}

			//Update the cool down timer.
			String skillName = "burstrun";
			addCooldown(skillName, delay);
		}
	}
}

void CreatureObjectImplementation::deactivateBurstRun(bool bypassChecks) {
	if (isPlayer()) {
		sendSystemMessage("cbt_spam", "burstrun_stop_single"); //"You slow down."
	}

	burstRunning = false;

	if (isMounted()) {
		return;
	}

	if (isProne()) {
		float proneModifier = calculateProneSpeedModifier();
		updateSpeed(0.7f * proneModifier, 0.7745f / proneModifier);

	} else {
		updateSpeed(5.376, 1.549f);
	}
}

bool CreatureObjectImplementation::burstRunChecks() {
	float hamCost = 100.0f;

	//Check invalid states.
	if (isDizzied() || isKnockedDown() || isMeditating() || postureState != CreaturePosture::UPRIGHT) {
		if (isPlayer()) {
			sendSystemMessage("combat_effects", "burst_run_no");
		}
		return false;
	}

	//Check cooldown timer.
	if (!hasCooldownExpired("burstrun")) {
		String skillName = "burstrun";
		int timeRemaining = getCooldownTimeRemaining(skillName);
		int min = timeRemaining / 60;
		int seconds = timeRemaining % 60;
		StringBuffer msg;
		msg << "You must wait " << min << " minutes and " << seconds << " seconds to perform this action.";
		sendSystemMessage(msg.toString());
		return false;
	}

	//Calculate HAM cost based on efficiency skill mod.
	float burstRunMod = (float)getSkillMod("burst_run");
	if (burstRunMod > 100.0f) {
		burstRunMod = 100.0f;
	}

	float efficiency = 1.0f - (burstRunMod / 100.0f);
	hamCost *= efficiency;
	int newHamCost = (int)hamCost;

	//Check for and deduct HAM cost.
	if (getHealth() <= newHamCost || getAction() <= newHamCost || getMind() <= newHamCost) {
		sendSystemMessage("combat_effects", "burst_run_wait"); //"You are too tired to Burst Run."
		return false;

	} else {
		changeHAMBars(-newHamCost, -newHamCost, -newHamCost, false);
	}

	return true;
}

float CreatureObjectImplementation::calculateProneSpeedModifier() {
	float proneModifier;
	int terrainMod = getSkillMod("slope_move");

	if (terrainMod > 100) {
		terrainMod = 100;
	}

	if (terrainMod > 50) {
		proneModifier = 1.0f + (((float)terrainMod - 50.0f) / 25.0f);
	} else {
		proneModifier = 1.0f;
	}

	return proneModifier;
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

	for (int i=0; i < inventory->getContainerObjectsSize(); i++) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);

		if (item->isInstrument() && item->isEquipped())
				return (Instrument*) item;
	}

	return NULL;
}

int CreatureObjectImplementation::getInstrumentType() {
	Instrument* instrument = getInstrument();
	if (instrument == NULL) {
		return -1;
	} else {
		return instrument->getInstrumentType();
	}
}

Armor* CreatureObjectImplementation::getArmor(int type) {
	if (inventory == NULL)
		return NULL;

	for (int i=0; i < inventory->getContainerObjectsSize(); i++) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);

		if (item->isArmor()) {
			if (((Armor*) item)->getArmorPiece() == type && item->isEquipped())
				return (Armor*) item;
		}
	}

	return NULL;
}

void CreatureObjectImplementation::addInventoryItem(TangibleObject* item) {
	if (item->isEquipped() && item->isWeapon()) {
		item->setParent(_this, 0x04);
		setWeapon((Weapon*) item);
	}
	inventory->addObject(item);
}

void CreatureObjectImplementation::addInventoryResource(ResourceContainer* rcno) {

	bool makeNewResource = true;

	ResourceContainer* inventoryResource;

	Player* player = (Player*)_this;
	if (player == NULL)
		return;

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
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
		if (inventory->getUnequippedItemCount() + 1 > inventory->getContainerVolumeLimit()) {
			ChatSystemMessage* sysMessage =
					new ChatSystemMessage("survey", "no_inv_spc");
			player->sendMessage(sysMessage);
			return;
		}

		//TODO: 19519 - remove this comment and next line if its running stable on TC
		//rcno->setParent(inventory, 0xFFFFFFFF);

		inventory->addObject(rcno);

		rcno->sendTo(player);

		rcno->setPersistent(false);

	}
}

SceneObject* CreatureObjectImplementation::getInventoryItem(uint64 oid) {
	SceneObject* returnSCO = NULL;

	//First level of inventory
	returnSCO = inventory->getObject(oid);
	if (returnSCO != NULL)
		return returnSCO;

	//Container in inventory
	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);

		if (item->isContainer()) {
			returnSCO = item->getObject(oid);

			if (returnSCO != NULL)
				return returnSCO;
		}
	}

	return NULL;
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
	lootContainer->addObject(item);
}

void CreatureObjectImplementation::addBankItem(TangibleObject* item) {
	bankContainer->addObject(item);
}

TangibleObject* CreatureObjectImplementation::getLootItem(uint64 oid) {
	if (lootContainer != NULL)
		return (TangibleObject*) lootContainer->getObject(oid);
	else
		return NULL;
}

TangibleObject* CreatureObjectImplementation::getBankItem(uint64 oid) {
	if (bankContainer != NULL)
		return (TangibleObject*) bankContainer->getObject(oid);
	else
		return NULL;
}

void CreatureObjectImplementation::removeBankItem(SceneObject* item) {
	bankContainer->removeObject(item->getObjectID());
}

void CreatureObjectImplementation::removeBankItem(uint64 oid) {
	bankContainer->removeObject(oid);
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
		if (!creatureSkills.contains(skill->getNameCRC())) {
			creatureSkills.put(skill->getNameCRC(), skill);
			skillsAndCertifications.add(skill->getSkillName());
		}

		if (updateClient) {
			dplay9->addSkill(skill->getSkillName(), skillsAndCertifications.size() - 1);
			/*dplay9->insertByte(1);
			dplay9->insertShort(skillsAndCertifications.size() - 1);
			dplay9->insertAscii(skill->getSkillName().toCharArray());*/
		}
	}

	if (updateClient) {
		dplay9->close();
		((PlayerImplementation*) this)->sendMessage(dplay9);
	}
}

void CreatureObjectImplementation::removeSkills(Vector<Skill*>& skills, bool updateClient) {
	Vector<int> indexes;

	for (int i = 0; i < skills.size(); ++i) {
		Skill* skill = skills.get(i);
		creatureSkills.drop(skill->getNameCRC());

		for (int j = 0; j < skillsAndCertifications.size(); ++j) {
			if (skill->getSkillName() == skillsAndCertifications.get(j)) {
				indexes.add(j);

				skillsAndCertifications.remove(j);
			}
		}
	}

	if (updateClient) {
		PlayerObject* player = ((PlayerImplementation*)this)->getPlayerObject();

		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player);
		dplay9->startSkillListUpdate(indexes.size());

		for (int i = 0; i < indexes.size(); ++i) {
			int idx = indexes.get(i);
			dplay9->removeSkill(idx);
		}

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
	setListenID(objectID);
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

			creo->stopWatch(true, true, false);

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

			creo->stopListen(true, true, false);

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
	StfParameter* params;

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

	CreatureObject* entertainer = (CreatureObject*) object;
	Player* player = (Player*)_this;

	if (entertainer == _this)
		return;

	//Check range.
	if (!isInRange(entertainer, 40.0f) || !(entertainer->getBuilding() == getBuilding())) {
		params = new StfParameter;
		params->addTO("radial_performance", "watch");
		player->sendSystemMessage("cmd_err", "target_range_prose", params); //"Your target is too far away to %TO."
		delete params;
		return;
	}

	entertainer->wlock(_this);

	if (isDancing() || isPlayingMusic()) {
		sendSystemMessage("You cannot /watch while skill animating.");
		entertainer->unlock();
		return;

	} else if (!entertainer->isDancing()) {
		params = new StfParameter;
		params->addTT(entid);
		player->sendSystemMessage("performance", "dance_watch_not_dancing", params); //"%TT is not dancing."
		delete params;

		entertainer->unlock();
		return;

	} else if (entid == watchID) {
		sendSystemMessage("You are already watching " + entertainer->getCharacterName().toString() + ".");

		entertainer->unlock();
		return;
	}

	if (isWatching()) {
		stopWatch(false);
		sendEntertainmentUpdate(entid, "entertained");
		entertainer->addWatcher(_this);

		if (isPlayer())
			sendSystemMessage("You begin watching " + entertainer->getCharacterName().toString() + ".");

	} else {
		sendEntertainmentUpdate(entid, "entertained");
		entertainer->addWatcher(_this);

		if (isPlayer())
			sendSystemMessage("You begin watching " + entertainer->getCharacterName().toString() + ".");

		doWatching = true;
	}
	setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f);
	setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);

	info("started watching [" + entertainer->getCharacterName().toString() + "]");

	watchID =  entid;

	entertainer->unlock();
}

void CreatureObjectImplementation::startListen(uint64 entid) {
	SceneObject* object = zone->lookupObject(entid);
	StfParameter* params;

	if (object == NULL)
		return;

	if (!object->isPlayer() && !object->isNonPlayerCreature()) {
		sendSystemMessage("You cannot start listening an object.");
		return;
	}

	CreatureObject* entertainer = (CreatureObject*) object;
	Player* player = (Player*)_this;

	if (entertainer == _this)
		return;

	//Check range.
	if (!isInRange(entertainer, 40.0f) || !(entertainer->getBuilding() == getBuilding())) {
		params = new StfParameter;
		params->addTO("radial_performance", "listen");
		player->sendSystemMessage("cmd_err", "target_range_prose", params); //"Your target is too far away to %TO."
		delete params;
		return;
	}

	entertainer->wlock(_this);

	if (isDancing() || isPlayingMusic()) {
		sendSystemMessage("You cannot /listen while skill animating.");
		entertainer->unlock();
		return;

	} else 	if (!entertainer->isPlayingMusic()) {
		params = new StfParameter;
		params->addTT(entid);
		player->sendSystemMessage("performance", "music_listen_not_playing", params); //"%TT is not playing a song."
		delete params;

		entertainer->unlock();
		return;

	} else if (entid == listenID) {
		sendSystemMessage("You are already listening to " + entertainer->getCharacterName().toString() + ".");

		entertainer->unlock();
		return;
	}

	if (isListening()) {
		stopListen(false);
		sendEntertainmentUpdate(entid, "entertained");
		entertainer->addListener(_this);

		if (isPlayer())
			sendSystemMessage("You begin listening to " + entertainer->getCharacterName().toString() + ".");

	} else {
		sendEntertainmentUpdate(entid, "entertained");
		entertainer->addListener(_this);

		if (isPlayer())
			sendSystemMessage("You begin listening to " + entertainer->getCharacterName().toString() + ".");

		doListening = true;
	}
	setEntertainerBuffDuration(PerformanceType::MUSIC, 0.0f);
	setEntertainerBuffStrength(PerformanceType::MUSIC, 0.0f);

	info("started listening [" + entertainer->getCharacterName().toString() + "]");

	setListenID(entid);

	entertainer->unlock();
}

void CreatureObjectImplementation::stopWatch(bool doSendPackets, bool forced, bool doLock, bool outOfRange) {
	SceneObject* object = zone->lookupObject(watchID);

	if (object == NULL)
		return;

	CreatureObject* entertainer = (CreatureObject*) object;

	if (entertainer == _this)
		return;

	String entName;
	if (entertainer != NULL) {
		if (doLock && (entertainer != _this))
			entertainer->wlock(_this);

		entName = entertainer->getCharacterName().toString();

		entertainer->removeWatcher(_this);

		if (doLock && (entertainer != _this))
			entertainer->unlock();
	}

	setMood(moodid);

	if (doSendPackets)
		sendEntertainmentUpdate(0, moodStr);

	//System Message.
	if (isPlayer() && entertainer != NULL) {
		Player* player = (Player*)_this;
		StfParameter* params = new StfParameter;

		if (forced) {
			params->addTU(watchID);
			player->sendSystemMessage("performance", "dance_stop_other", params); //"%TU stops dancing."
		} else if (outOfRange) {
			StringBuffer msg;
			msg << "You stop watching " << entertainer->getCharacterName().toString() << " because they are too far away.";
			sendSystemMessage(msg.toString());

			//TODO: Why does %OT say "him/her" instead of "he/she"?
			//params->addTT(watchID);
			//player->sendSystemMessage("performance", "dance_watch_out_of_range", params); //"You stop watching %TT because %OT is too far away."
		} else {
			player->sendSystemMessage("performance", "dance_watch_stop_self"); //"You stop watching."
		}

		delete params;
	}

	activateEntertainerBuff(PerformanceType::DANCE);
	setEntertainerBuffDuration(PerformanceType::DANCE, 0.0f); // reset
	setEntertainerBuffStrength(PerformanceType::DANCE, 0.0f);
	info("stopped watching [" + entName + "]");

	doWatching = false;
	watchID = 0;
}

void CreatureObjectImplementation::stopListen(bool doSendPackets, bool forced, bool doLock, bool outOfRange) {
	SceneObject* object = zone->lookupObject(listenID);

	if (object == NULL)
		return;

	CreatureObject* entertainer = (CreatureObject*) object;

	if (entertainer == _this)
		return;

	String entName;
	if (entertainer != NULL) {
		if (doLock && (entertainer != _this))
			entertainer->wlock(_this);

		entName = entertainer->getCharacterName().toString();

		entertainer->removeListener(_this);

		if (doLock && (entertainer != _this))
			entertainer->unlock();
	}

	setMood(moodid);

	if (doSendPackets)
		sendEntertainmentUpdate(0, moodStr);

	//System Message.
	if (isPlayer() && entertainer != NULL) {
		Player* player = (Player*)_this;
		StfParameter* params = new StfParameter;

		if (forced) {
			params->addTU(listenID);
			player->sendSystemMessage("performance", "music_stop_other", params); //"%TU stops playing."
		} else if (outOfRange) {
			StringBuffer msg;
			msg << "You stop listening to " << entertainer->getCharacterName().toString() << " because they are too far away.";
			sendSystemMessage(msg.toString());

			//TODO: Why does %OT say "him/her" instead of "he/she"?
			//params->addTT(listenID);
			//player->sendSystemMessage("performance", "music_listen_out_of_range", params); //"You stop listening to %TT because %OT is too far away."
		} else {
			player->sendSystemMessage("performance", "music_listen_stop_self"); //"You stop listening."
		}

		delete params;
	}

	//TODO: Activate Buff
	activateEntertainerBuff(PerformanceType::MUSIC);
	setEntertainerBuffDuration(PerformanceType::MUSIC, 0.0f); // reset
	setEntertainerBuffStrength(PerformanceType::MUSIC, 0.0f);
	info("stopped listening [" + entName + "]");

	doListening = false;
	setListenID(0);
}

void CreatureObjectImplementation::activateEntertainerBuff(int performanceType) {

	// Returns the Number of Minutes for the Buff Duration
	float buffDuration = getEntertainerBuffDuration(performanceType);

	if (buffDuration * 60 < 10.0f) { //10 sec minimum buff duration
		return;
	}

	// Returns a % of base stat
	int campMod = 100;

	if (isInCamp())
		campMod = getCampModifier();

	float buffStrength = getEntertainerBuffStrength(performanceType) * campMod / 100;
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

			sendSystemMessage("healing", "performance_enhance_music_focus_d");
			sendSystemMessage("healing", "performance_enhance_music_willpower_d");
			break;
		case PerformanceType::DANCE:
			buff = new Buff(BuffCRC::PERFORMANCE_ENHANCE_DANCE_MIND, BuffType::PERFORMANCE, buffDuration * 60);
			buff->setMindBuff((int)round(buffStrength * getBaseMind()));
			applyBuff(buff);

			sendSystemMessage("healing", "performance_enhance_dance_mind_d");
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
void CreatureObjectImplementation::doEntertainerPatronEffects() {
	info("CreatureObjectImplementation::doEntertainerPatronEffects() begin");

	//**DECLARATIONS**
	ManagedSortedVector<CreatureObject>* patrons = NULL;
	SkillManager* skillManager = server->getSkillManager();
	Performance* performance = NULL;
	float enhancementSkill = 0.0f;
	int healingXp = 0;
	int campMod = 100;
	bool canHeal = false;

	if (isInCamp()) {
		campMod = getCampModifier();
	}

	if (getPerformanceName() == "")
		return;

	//**LOAD PATRONS, GET THE PERFORMANCE AND ENT'S HEALING SKILL.**
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

	if (performance == NULL) {
		return;
	}

	//**DETERMINE IF THE ENT CAN HEAL.**
	if (isInBuilding() || isInCamp()) {
		int buildingType = getBuildingType();

		if (buildingType == BuildingObjectImplementation::CANTINA ||
			buildingType == BuildingObjectImplementation::GUILD_THEATER ||
			buildingType == BuildingObjectImplementation::TAVERN ||
			isInCamp()) {

			canHeal = true;
		}
	}

	//**DETERMINE WOUND HEAL AMOUNTS.**
	int woundHeal = performance->getHealMindWound() * campMod / 100;
	int shockHeal = performance->getHealShockWound() * campMod / 100;


	//**ENTERTAINER HEALS THEIR OWN MIND.**
	if (canHeal) {
		changeMindWoundsBar(-woundHeal, false);
		changeFocusWoundsBar(-woundHeal, false);
		changeWillpowerWoundsBar(-woundHeal, false);
		changeShockWounds(-shockHeal);

		healingXp += shockHeal;
		healingXp += woundHeal;
	}

	//**APPLY EFFECTS TO PATRONS.**
	if (patrons != NULL && patrons->size() > 0) {

		for (int i = 0; i < patrons->size(); ++i) {
			CreatureObject* patron = patrons->get(i);
			try {
				if (patron != _this)
					patron->wlock(_this);

				//**VERIFY THE PATRON IS IN RANGE OF THE ENT.
				bool patronInRange = false;
				if (isInRange(patron, 40.0f) && patron->getBuilding() == getBuilding()) {
					patronInRange = true;
				}

				if (patronInRange) {
					if (canHeal)
					{
						patron->changeMindWoundsBar(-woundHeal, false);
						patron->changeFocusWoundsBar(-woundHeal, false);
						patron->changeWillpowerWoundsBar(-woundHeal, false);
						patron->changeShockWounds(-shockHeal);

						healingXp += shockHeal;
						healingXp += woundHeal;
					}

					// Handle Passive Buff
					if (canHeal && isInAGroup() && (getGroupID() == patron->getGroupID())) {
						// Add 1 minute per tick
						patron->addEntertainerBuffDuration(performance->getType(), 1.0f);
						// TODO: In theory the buff isn't always the max, in practice after enough flourishes it maxes out way before duration
						patron->setEntertainerBuffStrength(performance->getType(), enhancementSkill / 100.0f);
					}

				} else { //patron is not in range
					if (isDancing()) {
						patron->stopWatch(true, false, false, true);

						if (!patron->isListening())
							sendEntertainmentUpdate(0, "", true);

					} else if (isPlayingMusic()) {
						patron->stopListen(true, false, false, true);

						if (!patron->isWatching())
							sendEntertainmentUpdate(0, "", true);
					}
				}

				if (patron != _this)
					patron->unlock();
			} catch (...) {
				if (patron != _this)
					patron->unlock();

				error("Unreported exception caught in CreatureObjectImplementation::doEntertainerPatronEffects()");
			}
		}
	} else
		//System::out << "There are no patrons.\n";

	//**ADD XP.**
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
	setMood(mood);
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
	if (isInCamp())
		return true;

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

void CreatureObjectImplementation::sendSystemMessage(const String& message) {
	if (isPlayer())
		((PlayerImplementation*) this)->sendSystemMessage(message);
}

void CreatureObjectImplementation::sendSystemMessage(const String& file, const String& str, uint64 targetid) {
	if (isPlayer())
		((PlayerImplementation*) this)->sendSystemMessage(file, str, targetid);
}

void CreatureObjectImplementation::sendSystemMessage(UnicodeString& message) {
	if (isPlayer())
		((PlayerImplementation*) this)->sendSystemMessage(message);
}

float CreatureObjectImplementation::getDistanceTo(SceneObject* targetCreature) {
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
SceneObject* test = mount->getParent();
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

		if (isBurstRunning()) {
			updateSpeed(8.0f, 0.922938f);
		} else {
			updateSpeed(5.376f, 1.549f);
		}

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
		return;

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

	//activateRecovery();
}

void CreatureObjectImplementation::removeBuffs(bool doUpdateClient) {

	//Changed loop style to while and set "removeFromList" to true
	//to ensure that all the buffs are properly removed from player.
	//Spice Downers were being applied in error on cloning! - Lak Moore
	while (creatureBuffs.size() > 0) {
		Buff* buff = creatureBuffs.get(0);
		if (buff != NULL) {
			removeBuff(buff->getBuffCRC(), true);
		}
	}

	//in theory this is now a redundant call - Lak Moore
	creatureBuffs.removeAll();

	if (doUpdateClient) {
		resetHAMBars(true);
	}

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
		return ((((float) shockWounds) - 250.0f) / 1000.0f);
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

bool CreatureObjectImplementation::healState(CreatureObject* target, uint64 state) {
	if (!target->hasState(state))
		return false;

	if (target->clearState(state)) {
		target->updateStates();
		return true;
	}

	return false;
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

void CreatureObjectImplementation::deactivateInjuryTreatment(bool isRangedStim) {
	float modSkill = 0.0f;

	if (isRangedStim)
		modSkill = (float)getSkillMod("healing_range_speed");
	else
		modSkill = (float)getSkillMod("healing_injury_speed");


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
	sendSystemMessage("healing_response", "healing_response_59");
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
	sendSystemMessage("healing_response", "healing_response_59");
}

int CreatureObjectImplementation::getMedicalFacilityRating() {
	if (!isInBuilding() && !isInCamp()) //TODO: Add in search for nearby surgical droid
		return 0;

	int buildingType = getBuildingType();

	if (buildingType == BuildingObjectImplementation::MEDICAL_CENTER || buildingType == BuildingObjectImplementation::CLONING_FACILITY)
		return 100;

	if (isInCamp())
		return getCampModifier();

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

/**
 * Activates the camo skill.
 * \param camoCRC The skills crc.
 * \param time The duration.
 * \param ms the mask scent type.
 */
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

/**
 *	Deactivates the camo.
 *	\param forced Was the deactivation forcced by an attack ?
 */
void CreatureObjectImplementation::deactivateCamo(bool forced) {
	if (maskScentEvent != NULL) {

		if (forced)
			sendSystemMessage("skl_use", "sys_scentmask_break");
		else if (getCamoType() == CamoSkill::MASKSCENT)
			sendSystemMessage("skl_use", "sys_scentmask_stop");
		else
			sendSystemMessage("skl_use", "sys_conceal_stop");



		//removeQueuedState(maskScentEvent->getNameCRC());
		removeBuff(maskScentEvent->getNameCRC());
		server->removeEvent(maskScentEvent);
		camoType = 11;
		clearState(CreatureState::MASKSCENT);
		updateStates();
		maskScentEvent = NULL;
		camoXPTraget = NULL;
		activateCamoLock();
	}
}

/**
 * Activates the camo deactivation timer.
 */
void CreatureObjectImplementation::activateCamoLock() {
	camoLock.update();
	camoLock.addMiliTime(60000);
}

/**
 * Checks if the the camo deactivation timer is on.
 * \return True if timer is active else false.
 */
bool CreatureObjectImplementation::isCamoCooldownActive() {
	return camoLock.isPast();
}

/**
 * Returns the deactivation time left.
 * \return The time left until camo can be used again.
 */
int CreatureObjectImplementation::getCamoCooldownLeft() {
	return -1 * camoLock.miliDifference();
}

/// Actions
bool CreatureObjectImplementation::inflictDamage(CreatureObject* victim, uint8 attribute, uint32 damage) {
	victim->addDamage(_this, damage);
	if (SceneObjectImplementation::inflictDamage(victim, attribute, damage)) {
		return true;
	}

	return false;
}


/**
 * Action performed incapacitated by own consequence.
 */
void CreatureObjectImplementation::incapacitateSelf() {
	setPosture(CreaturePosture::INCAPACITATED);
	System::out << "creo::incapself" << endl;
	onIncapacitated(NULL);
}

/**
 * Action performed to recover from incapacitation.
 */
void CreatureObjectImplementation::recoverFromIncapacitation() {
	setPosture(CreaturePosture::UPRIGHT);
	onIncapacitationRecovery();
}

/**
 * Action performed when a player dies, whether by deathblow or kill.
 */
void CreatureObjectImplementation::die() {

	clearStates();
	setPosture(CreaturePosture::DEAD);
	timeOfDeath = Time().getMiliTime();

	/// If creature is a player, don't execute the onDeath handler here. It will propagate down from PlayerImplementation.
	//TODO: Does this really need to be here?
	if (!isPlayer())
		onDeath();
}

/**
 * This action is performed when an item is equipped.
 * \param item The item that is being equipped.
 */
void CreatureObjectImplementation::equipItem(TangibleObject* item) {
	if (item->isEquipped())
		return;

	item->setEquipped(true);
	item->setParent(_this, 0x04);

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
		error("Unreported Exception in CreatureObjectImplementation::equipItem()");
		zone->unlock();
	}

	onEquip(item);
}

/**
 * This action is performed when an item is unequipped.
 * \param item The item that is being unequipped.
 */
void CreatureObjectImplementation::unequipItem(TangibleObject* item) {
	if (!item->isEquipped())
		return;

	if (item->isInstrument() && isPlayingMusic())
        stopPlayingMusic();

	item->setEquipped(false);
	item->setParent(inventory, 0xFFFFFFFF);

	item->setUpdated(true);

	BaseMessage* linkmsg = item->link(inventory);
	broadcastMessage(linkmsg);

	onUnequip(item);
}

bool CreatureObjectImplementation::isTanoObjEquipped(TangibleObject* tano) {
	if (inventory == NULL)
		return false;

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		TangibleObject* item = (TangibleObject*) inventory->getObject(i);

		if (tano == item)
			if(item->isEquipped())
				return true;
	}

	return false;
}


/**
 * This event handler is executed after a creature has been incapacitated via incapacitate incapacitateSelf.
 * \param attacker The attacker who caused the incapacitation, if NULL then caused by self.
 */
void CreatureObjectImplementation::onIncapacitated(SceneObject* attacker) {
	//Pets can be incapacitated.
}

/**
 * This event handler is executed when a creature recovers from incapacitation.
 */
void CreatureObjectImplementation::onIncapacitationRecovery() {
	setSpeed(5.376);

	//TODO: Move this to a method.
	if (getHealth() < 1)
		setHealthBar(1);
	if (getAction() < 1)
		setActionBar(1);
	if (getMind() < 1)
		setMindBar(1);
}

/**
 * onDeath are the actions that occur for every type of death.
 */
void CreatureObjectImplementation::onDeath() {
	//Remove buffs
	//Decay items
	//Only creature stuff happens here.
}

/**
 * This event handler takes place after a creature has been killed with the use of kill()
 * \param killer The invoker of the kill()
 */
void CreatureObjectImplementation::onKilled(SceneObject* killer) {
	//Lose any faction points
	//Lose experience (Jedi)
	die();
}

void CreatureObjectImplementation::onResuscitated(SceneObject* healer) {
	setPosture(CreaturePosture::UPRIGHT);
}

void CreatureObjectImplementation::onDamageHealed(SceneObject* healer, uint8 attribute, uint32 amount) {
	if (canRecoverFromIncapacitation()) {
		if (healer->isPlayer()) {
			((Player*)healer)->stopWatch(true, true, false);
			((Player*)healer)->stopListen(true, true, false);
		}

		recoverFromIncapacitation();
	}
}

void CreatureObjectImplementation::onWoundHealed(SceneObject* healer, uint8 attribute, uint32 amount) {

}

void CreatureObjectImplementation::onHealEnhanced(SceneObject* enhancer, uint8 attribute, uint32 amount, float duration) {

}

void CreatureObjectImplementation::onBlinded() {
}
void CreatureObjectImplementation::onDizzied() {
}
void CreatureObjectImplementation::onStunned() {
}
void CreatureObjectImplementation::onIntimidated() {
}

void CreatureObjectImplementation::onEquip(TangibleObject* item) {

}

void CreatureObjectImplementation::onUnequip(TangibleObject* item) {
}

void CreatureObjectImplementation::onChangeWeapon(Weapon* weapon) {

}

void CreatureObjectImplementation::onChangeArmor(Armor* armor) {

}

//void CreatureObjectImplementation::onChangeClothing(Wearable* clothing) {

//}

/**
 * Event handler that is called when damage has been received.
 * \param attacker The attacker that caused the damage.
 * \param attribute The attribute that was targetted by the damage.
 * \param amount How much damage was caused by the attack.
 */
void CreatureObjectImplementation::onReceiveDamage(SceneObject* attacker, uint8 attribute, uint32 amount) {

}

/**
 * Event handler that occurs when HAM regeneration takes place.
 */
void CreatureObjectImplementation::onRegenerateHAM() {
	float modifier = (isInCombat()) ? combatRegenModifier : peacedRegenModifier;

	if (isKneeling())
		modifier *= (5.0f / 7.0f);
	else if (!isSitting())
		modifier *= (4.0f / 7.0f);

	uint32 healthTick = (uint32) ceil((float) getConstitutionMax() * 13.0f / 1200.0f * 3.0f * modifier);
	uint32 actionTick = (uint32) ceil((float) getStaminaMax() * 13.0f / 1200.0f * 3.0f * modifier);
	uint32 mindTick = (uint32) ceil((float) getWillpowerMax() * 13.0f / 1200.0f * 3.0f * modifier);

	healthTick = (healthTick > 1) ? healthTick : 1;
	actionTick = (actionTick > 1) ? actionTick : 1;
	mindTick = (mindTick > 1) ? mindTick : 1;

	//TODO: Refactor this with event handlers
	if (isMeditating()) {
		int meditateMod = getSkillMod("meditate");
		float meditateBonus = 1 + ((float)meditateMod / 100);
		healthTick *= (int)meditateBonus;
		actionTick *= (int)meditateBonus;
		mindTick *= (int)meditateBonus;
		doMeditateHeals();
	}

	//TODO: Refactor this into an event handler
	if (isPlayer()) {
		Player* player = (Player*)_this;
		if (player->getPowerboosted() && pbMind != 0) {
			doPowerboostTick(player);
		}
	}
	changeHAMBars(healthTick, actionTick, mindTick);
}

void CreatureObjectImplementation::applyDots() {
	if (dotMap->hasDot() && dotMap->isPast()) {
		dotMap->activateDots(_this);
	}
	//else
	//	dotList->clear();
}
