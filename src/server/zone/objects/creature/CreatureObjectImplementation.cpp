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

#include "../../ZoneClient.h"

#include "../../packets.h"

#include "../player/Player.h"
#include "../player/PlayerImplementation.h"

#include "CreatureObject.h"
#include "CreatureObjectImplementation.h"

#include "../tangible/Inventory.h"
#include "../tangible/InventoryImplementation.h"

#include "../tangible/weapons/Weapon.h"
#include "../tangible/appearance/HairObject.h"
#include "../tangible/appearance/HairObjectImplementation.h"

#include "../group/GroupObject.h"

#include "events/CreatureBurstRunOverEvent.h"
#include "events/CreatureForceRunOverEvent.h"
#include "events/DizzyFallDownEvent.h"

#include "../../objects/player/Races.h"
#include "mount/MountCreature.h"

#include "../building/BuildingObject.h"

#include "skills/PassiveSkill.h"

CreatureObjectImplementation::CreatureObjectImplementation(uint64 oid) : CreatureObjectServant(oid + 0x15) {
	objectType = NONPLAYERCREATURE;

	positionCounter = 0;

	inventory = NULL;
	
	weaponSpeedModifier = 1;
	
	creatureSkillsCount = 0;
	creatureSkills.setInsertPlan(SortedVector<Skill*>::NO_DUPLICATE);
	creatureSkills.setNullValue(NULL);
	
	stfName = "species";

	// CREO1 operands
	cashCredits = 25000;
	bankCredits = 25000;

	// CREO3 operands
	postureState = UPRIGHT_POSTURE;
	stateBitmask = oldStateBitmask = 0;
	creatureBitmask = 0x1080;
	
	conditionDamage = 0;
	maxCondition = 0;
	mount = NULL;
	creatureLinkID = 0;
	
	height = 1.0f;
	
	// CREO4 operands
	speed = 5.376f;
	acceleration = 1.549f;
	skillModsCounter = 0;
	
	// CREO6 operands
	defenderUpdateCounter = 0;
	defenderID = 0;
	
	moodid = 0;
	mood = Races::getMood(moodid);
	
	weaponObject = NULL;
	targetObject = NULL;
	hairObj = NULL;
	
	hamUpdateCounter = 0;
	hamMaxUpdateCounter = 0;
	
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
	
	armor=0;

	// ent
	performanceCounter = 0;
	
	instrumentID = 0;
	
	doDancing = false;
	doPlayingMusic = false;
	doListening = false;
	doWatching = false;
	
	watchID = 0;
	listenID = 0;
	
	listeners.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);
	watchers.setInsertPlan(SortedVector<CreatureObject*>::NO_DUPLICATE);
	
	// wounds
	
	woundsUpdateCounter = 0;
	
	healthWounds = 0;
	actionWounds = 0;
	mindWounds = 0;
	
	// misc
	pvpStatusBitmask = 0x10;
	faction = 0;
	
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
	meditating = false;
	
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
	
	building = NULL;
	
	dizzyFallDownEvent = new DizzyFallDownEvent(this);
	
	lastMovementUpdateStamp = 0;
	ignoreMovementTests = 5;
	
	level = 0;
}

CreatureObjectImplementation::~CreatureObjectImplementation() {
	/*delete inventory;
	
	if (hairObj != NULL)
		delete hairObj;*/
}

void CreatureObjectImplementation::sendToOwner(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;

	Message* ubf = new unkByteFlag();
	client->sendMessage(ubf);
	
	Message* css = new CmdStartScene(_this);
	client->sendMessage(css);
	
	Message* pmm = new ParametersMessage();
	client->sendMessage(pmm);
	
	if (parent != NULL)
		parent->sendTo((Player*)_this, false);
	
	sendTo(player, doClose);
}

void CreatureObjectImplementation::sendTo(Player* player, bool doClose) {
	ZoneClient* client = player->getClient();
	if (client == NULL)
		return;
		
	if (player == (Player*) _this && group != NULL)
		group->sendTo(player);
	
	create(client);
	
	if (parent != NULL)
		client->sendMessage(link(parent));
	
	if (player == (Player*) _this) {
		Message* creo1 = new CreatureObjectMessage1(this);
		client->sendMessage(creo1);
	}
	
	Message* creo3 = new CreatureObjectMessage3(_this);
	client->sendMessage(creo3);
		
	if (player == (Player*) _this) {
		Message* creo4 = new CreatureObjectMessage4(this);
		client->sendMessage(creo4);
	}

	Message* creo6 = new CreatureObjectMessage6(_this);
	client->sendMessage(creo6);
	
	sendFactionStatusTo(player);
	
	if (doClose)
		close(client);
}

void CreatureObjectImplementation::sendDestroyTo(Player* player) {
	ZoneClient* client = player->getClient();
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

void CreatureObjectImplementation::sendFactionStatusTo(Player* player, bool doTwoWay) {
	if (pvpStatusBitmask & OVERT_FLAG) {
		uint32 pvpBitmask = pvpStatusBitmask;
		uint32 playerPvp = player->getPvpStatusBitmask();
			
		if (player->isOvert() && (player->getFaction() != faction)) {
			if (doTwoWay && isPlayer()) {	
				Message* pvpstat = new UpdatePVPStatusMessage(player, playerPvp + ATTACKABLE_FLAG + AGGRESSIVE_FLAG);	
				((PlayerImplementation*) this)->sendMessage(pvpstat);
			}
				
			Message* pvpstat2 = new UpdatePVPStatusMessage(_this, pvpBitmask + ATTACKABLE_FLAG + AGGRESSIVE_FLAG);	
			player->sendMessage(pvpstat2);
		} else { 				
			Message* pvpstat3 = new UpdatePVPStatusMessage(_this, pvpBitmask);	
			player->sendMessage(pvpstat3);
			
			if (doTwoWay && isPlayer()) {	
				Message* pvpstat = new UpdatePVPStatusMessage(player, playerPvp);	
				((PlayerImplementation*) this)->sendMessage(pvpstat);
			}
		}
	} else {
		uint32 playerPvp = player->getPvpStatusBitmask();

		if (doTwoWay && isPlayer()) {	
			Message* pvpstat = new UpdatePVPStatusMessage(player, playerPvp);	
			((PlayerImplementation*) this)->sendMessage(pvpstat);
		}
		
		Message* pvpstat2 = new UpdatePVPStatusMessage(_this, pvpStatusBitmask);	
		player->sendMessage(pvpstat2);
	}
}

void CreatureObjectImplementation::doCombatAnimation(CreatureObject* defender, uint32 animcrc, uint8 hit) {
	CombatAction* action = new CombatAction(_this, defender, animcrc, hit);
	
	broadcastMessage(action);
}

void CreatureObjectImplementation::doAnimation(const string& anim) {
	Animation* msg = new Animation(_this, anim);
	
	broadcastMessage(msg);
}

void CreatureObjectImplementation::playEffect(const string& file, const string& aux) {
	PlayClientEffectObjectMessage* effect = new PlayClientEffectObjectMessage(_this, file, aux); 

	int rangeLimit = 128;
	
	if (inRangeObjectCount() > 40)
		rangeLimit = 70;

	broadcastMessage(effect, rangeLimit);
}

void CreatureObjectImplementation::showFlyText(const string& file, const string& aux, uint8 red, uint8 green, uint8 blue) {
	ShowFlyText* fly = new ShowFlyText(_this, file, aux, red, green, blue);

	int rangeLimit = 128;
	
	if (inRangeObjectCount() > 40)
		rangeLimit = 70;
	
	broadcastMessage(fly, rangeLimit);
}

void CreatureObjectImplementation::sendCombatSpam(CreatureObject* defender, TangibleObject* item, uint32 damage, const string& skill) {
	try {
		//info("sending combat spam");

		zone->lock();
	
		bool needLimiting = inRangeObjectCount() > 40;
	
		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());
			
			if (object->isPlayer() && isInRange(object, 70)) {
				Player* player = (Player*) object;
		
				CombatSpam* msg = new CombatSpam(_this, defender, item, damage, "cbt_spam", skill, player);
				player->sendMessage(msg);
			}
		}

		zone->unlock();

		//info("combat spam sent");
	} catch (...) {
		error("exception CreatureObject::sendCombatSpam(CreatureObject* defender, TangibleObject* item, uint32 damage, const string& skill)");

		zone->unlock();
	}
}

void CreatureObjectImplementation::setPosture(uint8 state, bool overrideDizzy, bool objectInteraction, float objX, float objY, float objZ) {
	if (!overrideDizzy && isDizzied() && (postureState != UPRIGHT_POSTURE))
		state = KNOCKEDDOWN_POSTURE;
	
	if (state != postureState) {
		postureState = state;
		
		//Now we need to check for entertainer stuff.
		if (doDancing)
			stopDancing();
		else if (doPlayingMusic)
			stopPlayingMusic();
			
		Vector<Message*> msgs;
		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->updatePosture();
		
		if (objectInteraction == false) {
			PostureMessage* octrl = new PostureMessage(_this);
			msgs.add(octrl);
			
			//Now we need to check if they are sitting on a chair
			if (isSittingOnObject()) {
				setSittingOnObject(false);
				clearState(SITTINGONCHAIR_STATE);
				
				dcreo3->updateState();
			 }
		} else {
			SitOnObject* soo = new SitOnObject(_this, objX, objY, objZ);
			msgs.add(soo);
			
			setState(SITTINGONCHAIR_STATE);
			setSittingOnObject(true);
			
			dcreo3->updateState();
		}

		dcreo3->close();
		msgs.add(dcreo3);
		
		broadcastMessages(msgs);
		
		if (postureState == PRONE_POSTURE)
			setSpeed(2.688, 0.7745);
		else if (postureState == UPRIGHT_POSTURE)
			setSpeed(5.376, 1.549f);
	}
}

void CreatureObjectImplementation::setCombatState() {
	lastCombatAction.update();
	
	if (!(stateBitmask & COMBAT_STATE)) {
		stateBitmask |= COMBAT_STATE;
		
		if (stateBitmask & PEACE_STATE)
			stateBitmask &= ~PEACE_STATE;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->update06Operand(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3);

		/*if (defenderList.size() == 0 && targetObject != NULL && 
				(targetObject->isPlayer() || targetObject->isNonPlayerCreature()))
			setDefender((CreatureObject*) targetObject);*/
		
		if (postureState == SITTING_POSTURE)
			setPosture(UPRIGHT_POSTURE);
	}
}

void CreatureObjectImplementation::setDefender(CreatureObject* defender) {
	if (defender == _this)
		return;
		
	setCombatState();
	
	CreatureObject* temp = NULL;
	
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

void CreatureObjectImplementation::addDefender(CreatureObject* defender) {
	if (defender == _this)
		return;
		
	setCombatState();
	
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}
	
	defenderList.add(defender);
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6((CreatureObject*) _this);
	dcreo6->startDefenderUpdate(1);
	dcreo6->addDefender(defenderList.size() - 1, defender->getObjectID());
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::removeDefenders() {
	//info("starting to remove defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6((CreatureObject*) _this);
	dcreo6->startDefenderUpdate(defenderList.size());
	
	for (int i = 0; i < defenderList.size(); ++i)
		dcreo6->removeDefender(i);
	
	dcreo6->close();
	broadcastMessage(dcreo6);
	
	defenderList.removeAll();
	
	//info("removed all defenders");
}

void CreatureObjectImplementation::removeDefender(CreatureObject* defender) {
	if (zone == NULL)
		return;
	
	//info("trying to remove defender");
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			defenderList.remove(i);
			
			CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6((CreatureObject*) _this);
			dcreo6->startDefenderUpdate(1);
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

bool CreatureObjectImplementation::hasDefender(CreatureObject* defender) {
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender)
			return true;
	}
	return false;
}

void CreatureObjectImplementation::clearCombatState(bool removedefenders) {
	//info("trying to clear CombatState");
	if (stateBitmask & COMBAT_STATE) {
		if (stateBitmask & PEACE_STATE)
			stateBitmask &= ~PEACE_STATE;
		
		stateBitmask &= ~COMBAT_STATE;

		CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
		dcreo3->update06Operand(0x80);
		dcreo3->updateState();
		dcreo3->close();

		broadcastMessage(dcreo3);
	}
	
	if (removedefenders)
		removeDefenders();
	
	//info("finished clearCombatState");
}

void CreatureObjectImplementation::setDizziedState() {
	if (setState(DIZZY_STATE)) {
		playEffect("clienteffect/combat_special_defender_dizzy.cef");
		showFlyText("combat_effects", "go_dizzy", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_dizzy_single");

		dizzyRecoveryTime.update();
		dizzyRecoveryTime.addMiliTime(5000 + System::random(20000));
	}
}

void CreatureObjectImplementation::setStunnedState() {
	if (setState(STUNNED_STATE)) {
		playEffect("clienteffect/combat_special_defender_stun.cef");
		showFlyText("combat_effects", "go_stunned", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_stunned_single");
	
		stunRecoveryTime.update();
		stunRecoveryTime.addMiliTime(5000 + System::random(20000));
	}
}

void CreatureObjectImplementation::setBlindedState() {
	if (setState(BLINDED_STATE)) {
		playEffect("clienteffect/combat_special_defender_blind.cef");
		showFlyText("combat_effects", "go_blind", 0, 0xFF, 0);
		sendSystemMessage("cbt_spam", "go_blind_single");

		blindRecoveryTime.update();
		blindRecoveryTime.addMiliTime(5000 + System::random(20000));
	}
}

void CreatureObjectImplementation::setIntimidatedState() {
	if (setState(INTIMIDATED_STATE)) {
		playEffect("clienteffect/combat_special_defender_intimidate.cef");
		showFlyText("combat_effects", "go_intimidated", 0, 0xFF, 0);
		
		intimidateRecoveryTime.update();
		intimidateRecoveryTime.addMiliTime(15000 + System::random(5000));
	}
}

bool CreatureObjectImplementation::setNextAttackDelay(int del) {
	if (nextAttackDelayRecovery.isPast()) {
		nextAttackDelay.update();
		nextAttackDelay.addMiliTime(del);
		
		nextAttackDelayRecovery.update();
		nextAttackDelayRecovery.addMiliTime(30000+del);
		
		if (isPlayer()) {
			stringstream msg;
			msg << "You have been delayed for " << (del/1000) << " seconds.";
			sendSystemMessage(msg.str());
		}
		
		return true;
	}
	return false;
}

void CreatureObjectImplementation::setMeditateState() {
	if (isInCombat())
		return;
	
	updateMood("meditating");
	setPosture(SITTING_POSTURE);
	
	meditating = true;
}

void CreatureObjectImplementation::setPoisonedState(int str, int type) {
	if(setState(POISONED_STATE)) {
		playEffect("clienteffect/dot_apply_poison.cef");
		sendSystemMessage("dot_message", "start_poisoned");
		
		poisonDotType = type;
		poisonDotStrength = str;

		poisonRecoveryTime.update();
		poisonRecoveryTime.addMiliTime(60000);
	}
}

void CreatureObjectImplementation::setOnFireState(int str, int type) {
	if(setState(ONFIRE_STATE)) {
		playEffect("clienteffect/dot_apply_fire.cef");
		sendSystemMessage("dot_message", "start_fire");
		
		fireDotType = type;
		fireDotStrength = str;

		fireRecoveryTime.update();
		fireRecoveryTime.addMiliTime(60000);
	}
}

void CreatureObjectImplementation::setBleedingState(int str, int type) {
	if(setState(BLEEDING_STATE)) {
		playEffect("clienteffect/dot_apply_bleeding.cef");
		sendSystemMessage("dot_message", "start_bleeding");
		
		bleedingDotType = type;
		bleedingDotStrength = str;

		bleedingRecoveryTime.update();
		bleedingRecoveryTime.addMiliTime(60000);
		
		nextBleedingTick.update();
	}
}

void CreatureObjectImplementation::setDiseasedState(int str, int type) {
	if(setState(DISEASED_STATE)) {
		playEffect("clienteffect/dot_apply_disease.cef");
		sendSystemMessage("dot_message", "start_diseased");
		
		diseaseDotType = type;
		diseaseDotStrength = str;

		diseasedRecoveryTime.update();
		diseasedRecoveryTime.addMiliTime(60000);
	}
}

void CreatureObjectImplementation::doPoisonTick() {
	if(nextPoisonTick.isPast()) {
		if (poisonDotType == 1)
			changeHealthBar(-poisonDotStrength);
		else if (poisonDotType == 2)
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
		else if (bleedingDotType == 2)
			changeActionBar(-bleedingDotStrength);
		else
			changeMindBar(-bleedingDotStrength);
	
		playEffect("clienteffect/dot_bleeding.cef");
		
		nextBleedingTick.update();
		nextBleedingTick.addMiliTime(9000);
	}
}

void CreatureObjectImplementation::doDiseaseTick() {
	/*
	if (nextDiseaseTick.isPast()) {
	
		if (diseaseDotType == 1)
			changeHealthWoundBar(diseaseDotStrength);
		else if (diseaseDotType == 2)
			changeActionWoundBar(diseaseDotStrength);
		else
			changeMindWoundBar(diseaseDotStrength);
			
		playEffect("clienteffect/dot_diseased.cef");
		
		nextDiseaseTick.update();
		nextDiseaseTick.addMiliTime(9000);
	*/
}

void CreatureObjectImplementation::doFireTick() {
	if (nextFireTick.isPast()) {
		if (fireDotType == 1)
			changeHealthBar(-fireDotStrength);
		else if (bleedingDotType == 2)
			changeActionBar(-fireDotStrength);
		else
			changeMindBar(-fireDotStrength);
		
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
		case STUNNED_STATE:
			sendSystemMessage("cbt_spam", "no_stunned_single");
			showFlyText("combat_effects", "no_stunned", 0xFF, 0, 0);
			break;
		case BLINDED_STATE:
			sendSystemMessage("cbt_spam", "no_blind_single");
			showFlyText("combat_effects", "no_blind", 0xFF, 0, 0);
			break;
		case DIZZY_STATE:
			sendSystemMessage("cbt_spam", "no_dizzy_single");
			showFlyText("combat_effects", "no_dizzy", 0xFF, 0, 0);
			break;
		case POISONED_STATE:
			sendSystemMessage("dot_message", "stop_poisoned");
			break;
		case DISEASED_STATE:
			sendSystemMessage("dot_message", "stop_diseased");
			break;
		case ONFIRE_STATE:
			sendSystemMessage("dot_message", "stop_fire");
			break;
		case BLEEDING_STATE:
			sendSystemMessage("dot_message", "stop_bleeding");
			break;
		case INTIMIDATED_STATE:
			showFlyText("combat_effects", "no_intimidated", 0xFF, 0, 0);
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

void CreatureObjectImplementation::updateMood(const string& md) {
	setMood(md);
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMoodStr();
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::clearStates() {
	stateBitmask = 0;
	nextAttackDelay.update();
	
	updateStates();
}

bool CreatureObjectImplementation::changeHAMBars(int32 hp, int32 ap, int32 mp, bool forcedChange) {
	int32 newHealth = health + hp;
	int32 newAction = action + ap;
	int32 newMind = mind + mp;
	
	if (isIncapacitated()) {
		if ((health == 0) && (newHealth > 0) && (action > 0) && (mind > 0)) 
			setPosture(UPRIGHT_POSTURE);
		
		if ((action == 0) && (newAction > 0) && (health > 0) && (mind > 0))
			setPosture(UPRIGHT_POSTURE);
		
		if ((mind == 0) && (newMind > 0) && (action > 0) && (health > 0))
			setPosture(UPRIGHT_POSTURE);
	}
	
	if (newHealth <= 0 || newAction <=0 || newMind <= 0) {
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
	int32 newHealthWounds = healthWounds + hpwnds;
	int32 newActionWounds = actionWounds + apwnds;
	int32 newMindWounds = mindWounds + mpwnds;
	
	if (newHealthWounds >= healthMax || newActionWounds >=actionMax || newMindWounds >= mindMax) {
		if (forcedChange) {
			setHAMWoundsBars(MIN(newHealthWounds, healthMax), MIN(newActionWounds, actionMax), MIN(newMindWounds, mindMax));
			//doIncapacitate();
		}
		return false; 
	}

	setHAMWoundsBars(MIN(newHealthWounds, healthMax), MIN(newActionWounds, actionMax), MIN(newMindWounds, mindMax));
	
	return true;

}

bool CreatureObjectImplementation::changeHealthBar(int32 hp, bool forcedChange) {
	int32 newHealth = health + hp;
	
	if (newHealth <= 0) {
		if (forcedChange) { 
			setHealthBar(0);
			doIncapacitate();
		}

		return false; 
	}

	setHealthBar(MIN(newHealth, healthMax - healthWounds));
	
	return true;
}

void CreatureObjectImplementation::changeMaxHealthBar(int32 hp) {
	int32 newMaxHealth = healthMax + hp;

	setMaxHealthBar(newMaxHealth);
}

bool CreatureObjectImplementation::changeHealthWoundsBar(int32 wounds, bool forcedChange) {
	int32 newHealthWounds = healthWounds + wounds;
	
	if (newHealthWounds >= healthMax) {
		if (forcedChange) {
		}
		return false;
	}
	
	setHealthWoundsBar(MIN(newHealthWounds, healthMax));
	
	return true;
}

bool CreatureObjectImplementation::changeStrengthBar(int32 st, bool forcedChange) {
	int32 newStrength = strength + st;
	
	if (newStrength <= 0) {
		if (forcedChange) { 
			setStrengthBar(0);
		}

		return false; 
	}

	setStrengthBar(MIN(newStrength, strengthMax));
	
	return true;
}

void CreatureObjectImplementation::changeMaxStrengthBar(int32 hp) {
	int32 newMaxStrength = strengthMax + hp;

	setMaxStrengthBar(newMaxStrength);
}

bool CreatureObjectImplementation::changeConstitutionBar(int32 cs, bool forcedChange) {
	int32 newConstitution = constitution + cs;
	
	if (newConstitution <= 0) {
		if (forcedChange) { 
			setConstitutionBar(0);
		}

		return false; 
	}

	setConstitutionBar(MIN(newConstitution, constitutionMax));
	
	return true;
}

void CreatureObjectImplementation::changeMaxConstitutionBar(int32 hp) {
	int32 newMaxConstitution = constitutionMax + hp;

	setMaxConstitutionBar(newMaxConstitution);
}

bool CreatureObjectImplementation::changeActionBar(int32 ap, bool forcedChange) {
	int32 newAction = action + ap;
	
	if (newAction <= 0) {
		if (forcedChange) { 
			setActionBar(0);
			doIncapacitate();
		}

		return false; 
	}

	setActionBar(MIN(newAction, actionMax - actionWounds));
	
	return true;
}

void CreatureObjectImplementation::changeMaxActionBar(int32 hp) {
	int32 newMaxAction = actionMax + hp;

	setMaxActionBar(newMaxAction);
}

bool CreatureObjectImplementation::changeActionWoundsBar(int32 wounds, bool forcedChange) {
	int32 newActionWounds = actionWounds + wounds;
	
	if (newActionWounds >= actionMax) {
		if (forcedChange) {
		}
		return false;
	}
	
	setActionWoundsBar(MIN(newActionWounds, actionMax));
	
	return true;
}

bool CreatureObjectImplementation::changeQuicknessBar(int32 qc, bool forcedChange) {
	int32 newQuickness = quickness + qc;
	
	if (newQuickness <= 0) {
		if (forcedChange) { 
			setQuicknessBar(0);
		}

		return false; 
	}

	setQuicknessBar(MIN(newQuickness, quicknessMax));
	
	return true;
}

void CreatureObjectImplementation::changeMaxQuicknessBar(int32 hp) {
	int32 newMaxQuickness = quicknessMax + hp;

	setMaxQuicknessBar(newMaxQuickness);
}

bool CreatureObjectImplementation::changeStaminaBar(int32 st, bool forcedChange) {
	int32 newStamina = stamina + st;
	
	if (newStamina <= 0) {
		if (forcedChange) { 
			setStaminaBar(0);
		}

		return false; 
	}

	setStaminaBar(MIN(newStamina, staminaMax));
	
	return true;
}

void CreatureObjectImplementation::changeMaxStaminaBar(int32 hp) {
	int32 newMaxStamina = staminaMax + hp;

	setMaxStaminaBar(newMaxStamina);
}

bool CreatureObjectImplementation::changeMindBar(int32 mp, bool forcedChange) {
	int32 newMind = mind + mp;
	
	if (newMind <= 0) {
		if (forcedChange) { 
			setMindBar(0);
			doIncapacitate();
		}
		
		return false; 
	}

	setMindBar(MIN(newMind, mindMax - mindWounds));
	
	return true;
}

void CreatureObjectImplementation::changeMaxMindBar(int32 hp) {
	int32 newMaxMind = mindMax + hp;

	setMaxMindBar(newMaxMind);
}

bool CreatureObjectImplementation::changeMindWoundsBar(int32 wounds, bool forcedChange) {
	int32 newMindWounds = mindWounds + wounds;
	
	if (newMindWounds >= mindMax) {
		if (forcedChange) {
		}
		return false;
	}
	
	setMindWoundsBar(MIN(newMindWounds, mindMax));
	
	return true;
}

bool CreatureObjectImplementation::changeFocusBar(int32 fc, bool forcedChange) {
	int32 newFocus = focus + fc;
	
	if (newFocus <= 0) {
		if (forcedChange) { 
			setFocusBar(0);
		}

		return false; 
	}

	setFocusBar(MIN(newFocus, focusMax));
	
	return true;
}

void CreatureObjectImplementation::changeMaxFocusBar(int32 hp) {
	int32 newFocusMax = focusMax + hp;

	setMaxFocusBar(newFocusMax);
}


bool CreatureObjectImplementation::changeWillpowerBar(int32 wl, bool forcedChange) {
	int32 newWillpower = willpower + wl;
	
	if (newWillpower <= 0) {
		if (forcedChange) { 
			setWillpowerBar(0);
		}

		return false; 
	}

	setWillpowerBar(MIN(newWillpower, willpowerMax));
	
	return true;
}

void CreatureObjectImplementation::changeMaxWillpowerBar(int32 hp) {
	int32 newMaxWillpower = willpowerMax + hp;

	setMaxWillpowerBar(newMaxWillpower);
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
	if (hp == health) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateHealthBar(hp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxHealthBar(uint32 hp) {
	if (hp == healthMax) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxHealthBar(hp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setHealthWoundsBar(uint32 wounds) {
	if (wounds == healthWounds)
		return;
		
	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateHealthWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::setStrengthBar(uint32 st) {
	if (st == strength) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateStrengthBar(st);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxStrengthBar(uint32 st) {
	if (st == strengthMax) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxStrengthBar(st);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setConstitutionBar(uint32 cst) {
	if (cst == constitution) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateConstitutionBar(cst);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxConstitutionBar(uint32 cst) {
	if (cst == constitutionMax) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxConstitutionBar(cst);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setActionBar(uint32 ap) {
	if (ap == action) 
		return;
		
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateActionBar(ap);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxActionBar(uint32 ap) {
	if (ap == actionMax) 
		return;
		
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxActionBar(ap);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setActionWoundsBar(uint32 wounds) {
	if (wounds == actionWounds) 
		return;
	
	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateActionWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::setQuicknessBar(uint32 qck) {
	if (qck == quickness) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateQuicknessBar(qck);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxQuicknessBar(uint32 qck) {
	if (qck == quicknessMax) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxQuicknessBar(qck);
	dcreo6->close();

	broadcastMessage(dcreo6);
}


void CreatureObjectImplementation::setStaminaBar(uint32 sta) {
	if (sta == stamina) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateStaminaBar(sta);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxStaminaBar(uint32 sta) {
	if (sta == staminaMax) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxStaminaBar(sta);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMindBar(uint32 mp) {
	if (mp == mind) 
		return;
		
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMindBar(mp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxMindBar(uint32 mp) {
	if (mp == mindMax) 
		return;
		
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxMindBar(mp);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMindWoundsBar(uint32 wounds) {
	if (wounds == mindWounds) 
		return;
		
	CreatureObjectDeltaMessage3* dcreo3 = new CreatureObjectDeltaMessage3(_this);
	dcreo3->updateMindWoundsBar(wounds);
	dcreo3->close();

	broadcastMessage(dcreo3);
}

void CreatureObjectImplementation::setFocusBar(uint32 fc) {
	if (fc == focus) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateFocusBar(fc);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxFocusBar(uint32 fc) {
	if (fc == focusMax)
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxFocusBar(fc);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setWillpowerBar(uint32 will) {
	if (will == willpower) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateWillpowerBar(will);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxWillpowerBar(uint32 will) {
	if (will == willpowerMax) 
		return;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaxWillpowerBar(will);
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::setMaxHAMBars(uint32 hp, uint32 ap, uint32 mp) {
	healthMax = hp;
	actionMax = ap;
	mindMax = mp;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateMaximumPrimaryBars();
	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::calculateHAMregen() {
	float newHealth = (float)constitution * 13 / 1200 * 3;
	float newAction = (float)stamina * 13 / 1200 * 3;
	float newMind = (float)willpower * 13 / 1200 * 3;
	
	if (meditating) { 
		newHealth *= 2; 
		newAction *= 2; 
		newMind *= 2;
		
		if (healthWounds != 0 && System::random(3) == 3)
			changeHealthWoundsBar(-100);
		
		if (actionWounds != 0 && System::random(3) == 3)
			changeActionWoundsBar(-100);
		
		if (mindWounds != 0 && System::random(3) == 3)
			changeMindWoundsBar(-100);
		
		if (isPoisoned() && System::random(3) == 3)
			poisonRecoveryTime.update();
		
		if (isBleeding() && System::random(3) == 3)
			bleedingRecoveryTime.update();
		
		if (isDiseased() && System::random(3) == 3)
			diseasedRecoveryTime.update();			
	}
 	                 
	if (postureState == SITTING_POSTURE) {
		bool change = changeHAMBars((int)newHealth, (int)newAction, (int)newMind);
	} else if (postureState == CROUCHED_POSTURE) {
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

void CreatureObjectImplementation::activateBurstRun() {
	if (isMounted())
		return;
	
	if (!burstRunCooldown.isPast() && isPlayer()) {
		int left = -(burstRunCooldown.miliDifference() / 1000); 
		int min = left / 60;
		int seconds = left % 60;
		stringstream msg;
		msg << "You must wait " << min << " minutes and " << seconds << " seconds to perform this action.";
		((PlayerImplementation*) this)->sendSystemMessage(msg.str());
		return;
	}
	
	if (isPlayer() && speed > 5.376f) {
		unicode msg = unicode("You are already running.");
		((PlayerImplementation*) this)->sendSystemMessage(msg);

		return;
	}
	
	if (isDizzied() || postureState == PRONE_POSTURE)
		return;
	
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

void CreatureObjectImplementation::setSpeed(float Speed, float Acceleration) {
	setIgnoreMovementTests(10);
		
	speed = Speed; 
	acceleration = Acceleration;

	if (isPlayer()) {
		CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
	
		dcreo4->updateSpeed();
		dcreo4->updateAcceleration();
		dcreo4->close();

		((PlayerImplementation*) this)->sendMessage(dcreo4);
	}
}

void CreatureObjectImplementation::activateForceRun1(float sp, float acc) {
	if (speed > 5.376f) {
		unicode msg = unicode("You are already running.");
		((PlayerImplementation*) this)->sendSystemMessage(msg);

		return;
	}
	
	if (isDizzied()) {
		return;
	}
	
	speed = sp;//8.0f; 
	acceleration = acc;

	CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);
	
	dcreo4->updateSpeed();
	dcreo4->updateAcceleration();
	dcreo4->close();

	((PlayerImplementation*) this)->sendMessage(dcreo4);
	
	playEffect("clienteffect/pl_force_run_self.cef");
	((PlayerImplementation*) this)->addBuff(0x9A04E4F8, 120.0f);
	
	Event* e = new CreatureForceRunOverEvent(this);
	server->addEvent(e);
}

void CreatureObjectImplementation::updateTarget(uint64 targ) {
	SceneObject* target = zone->lookupObject(targ); 

	if (target != targetObject) {
		targetObject = target;
		
		if (targetObject == NULL)
			return;
	
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updateTarget();
		dcreo6->close();

		broadcastMessage(dcreo6);
	}
}

void CreatureObjectImplementation::updateTarget(SceneObject* targ) {
	targetObject = targ;
	
	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
	dcreo6->updateTarget();
	
	/*if (isInCombat())
		dcreo6->updateDefender();*/

	dcreo6->close();

	broadcastMessage(dcreo6);
}

void CreatureObjectImplementation::equipItem(TangibleObject* item) {
	if (item->isEquipped())
		return;
		
	item->setEquipped(true);
	item->setContainer(_this, 0x04);

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
		
	item->setEquipped(false);
	item->setContainer(inventory, 0xFFFFFFFF);

	item->setUpdated(true);

	Message* linkmsg = item->link(inventory);
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

void CreatureObjectImplementation::addInventoryItem(TangibleObject* item) {
	if (item->isEquipped()) {
		item->setContainer(_this, 0x04);
		
		if (item->getObjectSubType() == TangibleObjectImplementation::WEAPON)
			setWeapon((Weapon*) item);
	} else
		item->setContainer(inventory, 0xFFFFFFFF);

	inventory->addObject(item);
}

TangibleObject* CreatureObjectImplementation::getInventoryItem(uint64 oid) {
	return (TangibleObject*) inventory->getObject(oid);
}

void CreatureObjectImplementation::removeInventoryItem(uint64 oid) {
	inventory->removeObject(oid);
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

void CreatureObjectImplementation::addSkillMod(const string& name, int mod, bool updateClient) {
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

void CreatureObjectImplementation::removeSkillMod(const string& name, bool updateClient) {
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

void CreatureObjectImplementation::startDancing(const string& anim) {
	if (isPlayingMusic())
		stopPlayingMusic();	
		
	if (isDancing()) {
		sendSystemMessage("You are already dancing.");
		return;
	}

	if (anim == "basic") {
		sendEntertainingUpdate(0x3C4CCCCD, "dance_1", 0x07339FF8, 0xDD);
	} else if (anim == "rhythmic") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_3", 0x07339FF8, 0xDD);
	} else if (anim == "basic2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_2", 0x07339FF8, 0xDD);
	} else if (anim == "rhythmic2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_4", 0x07339FF8, 0xDD);
	} else if (anim == "footloose") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_15", 0x07339FF8, 0xDD);
	} else if (anim == "formal") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_17", 0x07339FF8, 0xDD);
	} else if (anim == "footloose2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_16", 0x07339FF8, 0xDD);
	} else if (anim == "formal2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_18", 0x07339FF8, 0xDD);
	} else if (anim == "popular") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_9", 0x07339FF8, 0xDD);
	} else if (anim == "poplock") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_13", 0x07339FF8, 0xDD);
	} else if (anim == "popular2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_10", 0x07339FF8, 0xDD);
	} else if (anim == "poplock2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_14", 0x07339FF8, 0xDD);
	} else if (anim == "lyrical") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_11", 0x07339FF8, 0xDD);
	} else if (anim == "exotic") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_5", 0x07339FF8, 0xDD);
	} else if (anim == "exotic2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_6", 0x07339FF8, 0xDD);
	} else if (anim == "lyrical2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_12", 0x07339FF8, 0xDD);
	} else if (anim == "exotic3") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_7", 0x07339FF8, 0xDD);
	} else if (anim == "exotic4") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_8", 0x07339FF8, 0xDD);
	} else if (anim == "theatrical") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_21", 0x07339FF8, 0xDD);
	} else if (anim == "theatrical2") { 
		sendEntertainingUpdate(0x3C4CCCCD, "dance_22", 0x07339FF8, 0xDD);
	} else {
		sendSystemMessage("Invalid dance name.");
		return;
	}
			
	info("started dancing");
	
	setPosture(9);
	setDancing(true);
	
	sendSystemMessage("You start dancing.");
}

void CreatureObjectImplementation::startPlayingMusic(const string& music) {
	if (isDancing())
		stopDancing();	
	
	if (isPlayingMusic()) {
		sendSystemMessage("You are already playing music.");
		return;
	}
	
	int instrid;
	if (music == "starwars1") {
		instrid = 1;
	} else if (music == "rock") {
		instrid = 11;
	} else if (music == "starwars2") {
		instrid = 21;
	} else if (music == "folk") {
		instrid = 31;
	} else if (music == "starwars3") {
		instrid = 41;
	} else if (music == "ceremonial") {
		instrid = 51;
	} else if (music == "ballad") {
		instrid = 61;
	} else if (music == "waltz") {
		instrid = 71;
	} else if (music == "jazz") {
		instrid = 81;
	} else if (music == "virtuoso") {
		instrid = 91;
	} else if (music == "western") {
		instrid = 101;
	} else {
		sendSystemMessage("Invalid music name.");
		return;
	}

	info("started playing music");
		
	setPosture(9);
	setPlayingMusic(true);
	
	sendEntertainingUpdate(0x3C4CCCCD, "music_3", 0x07352BAC, instrid);
	
	sendSystemMessage("You start to play music.");
}

void CreatureObjectImplementation::stopDancing() {
	if (isPlayer())
		sendSystemMessage("You stop dancing.");
	
	info("stopped dancing");

	setDancing(false);
	sendEntertainingUpdate(0x3F4D70A4, "", 0, 0);

	while (!watchers.isEmpty()) {
		CreatureObject* creo = watchers.get(0);	

		try {
			creo->wlock(_this);

			info("stopping dance for [" + creo->getCharacterName().c_str() + "]");
		
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
	if (isPlayer())
		sendSystemMessage("You stop playing music.");

	info("stopped playing music");

	setPlayingMusic(false);
	setListenID(0);
	
	sendEntertainingUpdate(0x3F4D70A4, "", 0, 0);
	
	while (!listeners.isEmpty()) {
		CreatureObject* creo = listeners.get(0);
		
		try {
			creo->wlock(_this);

			info("stopping music for [" + creo->getCharacterName().c_str() + "]");
			
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
	CreatureObject* creature = (CreatureObject*) zone->lookupObject(entid);
	if (creature == NULL || creature == _this)
		return;
	
	creature->wlock(_this);
	
	if (isDancing() || isPlayingMusic()) {
		sendSystemMessage("You cannot /watch while skill animating.");
		
		creature->unlock();
		return;
	} else if (!creature->isDancing()) {
		sendSystemMessage(creature->getCharacterName().c_str() + " is not currently dancing.");
		
		creature->unlock();
		return;
	} else if (entid == watchID) {
		sendSystemMessage("You are already watching " + creature->getCharacterName().c_str() + ".");
		
		creature->unlock();
		return;
	}

	if (isWatching()) {
		stopWatch(watchID, false);
		
		sendEntertainmentUpdate(entid, "entertained");
	
		creature->addWatcher(_this);

		if (isPlayer())
			sendSystemMessage("You begin watching " + creature->getCharacterName().c_str() + ".");
	} else {
		sendEntertainmentUpdate(entid, "entertained");

		creature->addWatcher(_this);

		if (isPlayer())
			sendSystemMessage("You begin watching " + creature->getCharacterName().c_str() + ".");

		doWatching = true;
	}

	info("started watching [" + creature->getCharacterName().c_str() + "]");
		
	watchID =  entid;

	creature->unlock();
}

void CreatureObjectImplementation::startListen(uint64 entid) {
	CreatureObject* creature = (CreatureObject*) zone->lookupObject(entid);
	if (creature == NULL || creature == _this)
		return;
		
	creature->wlock(_this);
	
	if (isDancing() || isPlayingMusic()) {
		sendSystemMessage("You cannot /listen while skill animating.");
		
		creature->unlock();
		return;
	} else 	if (!creature->isPlayingMusic()) {
		sendSystemMessage(creature->getCharacterName().c_str() + " is not currently playing music.");

		creature->unlock();
		return;
	} else if (entid == listenID) {
		sendSystemMessage("You are already listening to " + creature->getCharacterName().c_str() + ".");

		creature->unlock();
		return;
	} 
		
	if (isListening()) {
		stopListen(listenID, false);
		
		sendEntertainmentUpdate(entid, "entertained");
		
		creature->addListener(_this);
		
		if (isPlayer())
			sendSystemMessage("You begin listening to " + creature->getCharacterName().c_str() + ".");
	} else {
		sendEntertainmentUpdate(entid, "entertained");
		
		creature->addListener(_this);
		
		if (isPlayer())			
			sendSystemMessage("You begin listening to " + creature->getCharacterName().c_str() + ".");

		doListening = true;
	}

	info("started listening [" + creature->getCharacterName().c_str() + "]");

	listenID = entid;
	
	creature->unlock();
}

void CreatureObjectImplementation::stopWatch(uint64 entid, bool doSendPackets, bool forced, bool doLock) {
	CreatureObject* creature = (CreatureObject*) zone->lookupObject(entid);
	
	string entName;
	if (creature != NULL) {
		if (doLock && (creature != _this))
			creature->wlock(_this);
		
		entName = creature->getCharacterName().c_str();
		
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
		sendEntertainmentUpdate(0, "");

	if (isPlayer() && creature != NULL) {
		stringstream msg;

		if (forced)
			msg << entName << " stops dancing.";
		else
			msg << "You stop watching " << entName << ".";
		
		sendSystemMessage(msg.str());
	}

	info("stopped watching [" + entName + "]");
	
	doWatching = false;
	watchID = 0;
}

void CreatureObjectImplementation::stopListen(uint64 entid, bool doSendPackets, bool forced, bool doLock) {
	CreatureObject* creature = (CreatureObject*) zone->lookupObject(entid);

	string entName;
	if (creature != NULL) {
		if (doLock && (creature != _this))
			creature->wlock(_this);
		
		entName = creature->getCharacterName().c_str();
		
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
		sendEntertainmentUpdate(0, "");
		
	if (isPlayer() && creature != NULL) {
		stringstream msg;

		if (forced)
			msg << entName << " stops playing music.";
		else
			msg << "You stop listening to " << entName << ".";

		sendSystemMessage(msg.str());
	}

	info("stopped listening [" + entName + "]");
	
	doListening = false;
	listenID = 0;
}

void CreatureObjectImplementation::sendEntertainingUpdate(uint32 entval, const string& performance, uint32 perfcntr, int instrid) {
		if (isPlayer()) {
			CreatureObjectDeltaMessage4* dcreo4 = new CreatureObjectDeltaMessage4(this);

			if (isPlayingMusic() && instrid != 0)
				dcreo4->updateListenToID(objectID);

			dcreo4->updateEntertainerValue(entval);
			dcreo4->close();
			((PlayerImplementation*) this)->sendMessage(dcreo4);
			
		}
			
		CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(_this);
		dcreo6->updatePerformanceName(performance);
		dcreo6->updatePerformanceCounter(perfcntr);
		dcreo6->updateInstrumentID(instrid);
		dcreo6->close();
		broadcastMessage(dcreo6);

		setPerformanceName(performance);
		setPerformanceCounter(0);
		setInstrumentID(instrid);
}

void CreatureObjectImplementation::sendEntertainmentUpdate(uint64 entid, const string& mood, bool updateEntValue) {
	if (isPlayer()) {
		CreatureObjectDeltaMessage4* codm4 = new CreatureObjectDeltaMessage4(this);
		codm4->updateListenToID(entid);
		
		if (updateEntValue)
			codm4->updateEntertainerValue(0x3F4D70A4);
		
		codm4->close();
		((PlayerImplementation*) this)->sendMessage(codm4);
	}
	
	CreatureObjectDeltaMessage6* codm6 = new CreatureObjectDeltaMessage6(_this);
	codm6->updateMoodAnimation(mood);
	codm6->close();
	broadcastMessage(codm6);
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

uint32 CreatureObjectImplementation::getMitigation(const string& mit) {
	Skill* mitig = creatureSkills.get(String::hashCode(mit));
	
	if (mitig == NULL || !mitig->isPassiveSkill())
		return 0;
	else {
		PassiveSkill* mitigation = (PassiveSkill*)mitig;
		return mitigation->getDamageReduction();
	}
}

void CreatureObjectImplementation::broadcastMessage(Message* msg, int range, bool doLock) {
	if (zone == NULL)
		return;
	
	try {
		//cout << "CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
		zone->lock(doLock);

		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());
			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range))
					player->sendMessage(msg->clone());
			}
		}

		delete msg;

		zone->unlock(doLock);

		//cout << "finished CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)\n";
	} catch (...) {
		error("exception CreatureObject::broadcastMessage(Message* msg, int range, bool doLock)");

		zone->unlock(doLock);
	}
}

void CreatureObjectImplementation::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock) {
	if (zone == NULL)
		return;
		
	try {
		//cout << "CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";
		
		zone->lock(doLock);
	
		for (int i = 0; i < inRangeObjectCount(); ++i) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) getInRangeObject(i))->_getStub());
			
			if (object->isPlayer()) {
				Player* player = (Player*) object;

				if (range == 128 || isInRange(player, range)) {
					for (int j = 0; j < msgs.size(); ++j) {
						Message* msg = msgs.get(j);				
						player->sendMessage(msg->clone());
					}
				}
			}
		}

		for (int j = 0; j < msgs.size(); ++j) {
			Message* msg = msgs.get(j);				
			delete msg;
		}

		zone->unlock(doLock);

		//cout << "finished CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)\n";
	} catch (...) {
		error("exception CreatureObject::broadcastMessages(Vector<Message*>& msgs, int range, bool doLock)");

		zone->unlock(doLock);
	}
}

void CreatureObjectImplementation::sendSystemMessage(const string& message) {
	if (isPlayer())
		((PlayerImplementation*) this)->sendSystemMessage(message);
}

void CreatureObjectImplementation::sendSystemMessage(const string& file, const string& str, uint64 targetid) {
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
	
	if (mount->isDisabled() || !isInRange(mount, 5))
		return;
	
	if (!mountCooldown.isPast())
		return;
	
	mountCooldown.update();
	mountCooldown.addMiliTime(3000);
	
	parent = mount;
	linkType = 4;
	Message* msg = link(mount);
	broadcastMessage(msg);
	
	setIgnoreMovementTests(10);
	
	setSpeed(mount->getSpeed(), mount->getAcceleration());
	setState(RIDINGMOUNT_STATE);
	updateStates();
	
	setPosture(UPRIGHT_POSTURE);
	
	if (lockMount)
		mount->wlock(_this);
	
	mount->setState(MOUNTEDCREATURE_STATE);
	mount->updateStates();
	
	if (lockMount)
		mount->unlock();
}

void CreatureObjectImplementation::dismount(bool lockMount, bool ignoreCooldown) {
	if (parent == NULL || mount == NULL || !isMounted())
		return;
	
	if (!ignoreCooldown && !mountCooldown.isPast())
		return;

	mountCooldown.update();
	mountCooldown.addMiliTime(1000);
	
	if (lockMount)
		mount->wlock(_this);
	
	mount->clearState(MOUNTEDCREATURE_STATE);
	mount->updateStates();
	
	if (lockMount)
		mount->unlock();

	setSpeed(5.376f, 1.549f);
	clearState(RIDINGMOUNT_STATE);
	updateStates();
	
	linkType = 0xFFFFFFFF;
	UpdateContainmentMessage* msg = new UpdateContainmentMessage(objectID, 0, 0xFFFFFFFF);
	broadcastMessage(msg);
	
	parent = NULL;
}

void CreatureObjectImplementation::addCashCredits(int credits) {
	cashCredits = cashCredits + credits;
	
	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateCashCredits();
	delta->close();
	
	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::addBankCredits(int credits) {
	bankCredits = bankCredits + credits;
	
	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateBankCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::subtractCashCredits(int credits) {
	cashCredits = cashCredits - credits;
	
	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateCashCredits();
	delta->close();
	
	((PlayerImplementation*) this)->sendMessage(delta);
}

void CreatureObjectImplementation::subtractBankCredits(int credits) {
	bankCredits = bankCredits - credits;
	
	CreatureObjectDeltaMessage1* delta = new CreatureObjectDeltaMessage1(this);
	delta->updateBankCredits();
	delta->close();

	((PlayerImplementation*) this)->sendMessage(delta);
}

bool CreatureObjectImplementation::verifyCashCredits(int creditsToRemove) {
	 if (cashCredits >= creditsToRemove) {
	 	return true;
	 } else {
	 	return false;
	}
}

bool CreatureObjectImplementation::verifyBankCredits(int creditsToRemove) {
	 if (bankCredits >= creditsToRemove) {
	 	return true;
	 } else {
	 	return false;
	}
}
