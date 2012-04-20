/*
 * EntertainingSessionImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: victor
 */

#include "EntertainingSession.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/Performance.h"
#include "server/zone/managers/skill/PerformanceManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/player/events/EntertainingSessionTask.h"
#include "server/zone/objects/player/EntertainingObserver.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/packets/object/Flourish.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/mission/EntertainerMissionObjective.h"
#include "server/zone/objects/creature/buffs/PerformanceBuff.h"
#include "server/zone/objects/creature/buffs/PerformanceBuffType.h"

void EntertainingSessionImplementation::doEntertainerPatronEffects() {
	ManagedReference<CreatureObject*> creo = entertainer.get();

	if (creo == NULL)
		return;

	Locker locker(entertainer);
	//info("EntertainingSessionImplementation::doEntertainerPatronEffects() begin");

	//**DECLARATIONS**
	VectorMap<ManagedReference<CreatureObject*>, EntertainingData>* patrons = NULL;

	SkillManager* skillManager = creo->getZoneServer()->getSkillManager();

	PerformanceManager* performanceManager = skillManager->getPerformanceManager();
	Performance* performance = NULL;

	float enhancementSkill = 0.0f;
	float woundHealingSkill = 0.0f;
	float playerShockHealingSkill = 0.0f;
	float buildingShockHealingSkill = entertainer->getSkillMod("private_med_battle_fatigue");
	int campModtemp = 100;

	/*if (entertainer->isInCamp()) {
			campModtemp = getCampModifier();
		}*/

	if (performanceName == "")
		return;

	ManagedReference<Instrument*> instrument = getInstrument(entertainer);

	//**LOAD PATRONS, GET THE PERFORMANCE AND ENT'S HEALING SKILL.**
	if (dancing) {
		patrons = &watchers;
		performance = performanceManager->getDance(performanceName);
		enhancementSkill = (float) entertainer->getSkillMod("healing_dance_mind");
		woundHealingSkill = (float) entertainer->getSkillMod("healing_dance_wound");
		playerShockHealingSkill = (float) entertainer->getSkillMod("healing_dance_shock");
	} else if (playingMusic && instrument != NULL) {
		patrons = &listeners;
		performance = performanceManager->getSong(performanceName, instrument->getInstrumentType());
		enhancementSkill = (float) entertainer->getSkillMod("healing_music_mind");
		woundHealingSkill = (float) entertainer->getSkillMod("healing_music_wound");
		playerShockHealingSkill = (float) entertainer->getSkillMod("healing_music_shock");

	} else {
		cancelSession();
		return;
	}

	if (performance == NULL) {
		return;
	}

	//**DETERMINE WOUND HEAL AMOUNTS.**
	int woundHeal = ceil(performance->getHealMindWound() * (woundHealingSkill / 100.0f));
	int shockHeal = ceil(performance->getHealShockWound() * ((playerShockHealingSkill + buildingShockHealingSkill) / 100.0f));

	//**ENTERTAINER HEALS THEIR OWN MIND.**
	healWounds(entertainer, woundHeal*(flourishCount+1), shockHeal*(flourishCount+1));

	//**APPLY EFFECTS TO PATRONS.**
	if (patrons != NULL && patrons->size() > 0) {

		for (int i = 0; i < patrons->size(); ++i) {
			ManagedReference<CreatureObject*> patron = patrons->elementAt(i).getKey();

			try {
				//**VERIFY THE PATRON IS NOT ON THE DENY SERVICE LIST

				if (entertainer->isInRange(patron, 10.0f)) {
					healWounds(patron, woundHeal*(flourishCount+1), shockHeal*(flourishCount+1));
					increaseEntertainerBuff(patron);

				} else { //patron is not in range, force to stop listening
					ManagedReference<PlayerManager*> playerManager = patron->getZoneServer()->getPlayerManager();

					if (dancing) {
						if (playerManager != NULL)
							playerManager->stopWatch(patron, entertainer->getObjectID(), true, false, false, true);

						if (!patron->isListening())
							sendEntertainmentUpdate(patron, 0, "", true);

					} else if (playingMusic) {
						if (playerManager != NULL)
							playerManager->stopListen(patron, entertainer->getObjectID(), true, false, false, true);

						if (!patron->isWatching())
							sendEntertainmentUpdate(patron, 0, "", true);
					}
				}

			} catch (Exception& e) {
				error("Unreported exception caught in EntertainingSessionImplementation::doEntertainerPatronEffects()");
			}
		}
	} //else
	//System::out << "There are no patrons.\n";


	info("EntertainingSessionImplementation::doEntertainerPatronEffects() end");
}

bool EntertainingSessionImplementation::isInEntertainingBuilding(CreatureObject* creature) {
	ManagedReference<SceneObject*> root = creature->getRootParent();

	if (root != NULL) {
		uint32 gameObjectType = root->getGameObjectType();

		switch (gameObjectType) {
		case SceneObjectType::RECREATIONBUILDING:
		case SceneObjectType::HOTELBUILDING:
		case SceneObjectType::THEATERBUILDING:
			return true;
		}
	}

	return false;
}

void EntertainingSessionImplementation::healWounds(CreatureObject* creature, float woundHeal, float shockHeal) {
	float amountHealed = 0;

	Locker clocker(creature, entertainer);

	if(!canGiveEntertainBuff())
		return;

	if(isInDenyServiceList(creature))
		return;

	if(shockHeal > 0 && creature->getShockWounds() > 0 && canHealBattleFatigue()) {
		creature->addShockWounds(-shockHeal);
		amountHealed += shockHeal;
	}
	if(woundHeal > 0 && (creature->getWounds(CreatureAttribute::MIND) > 0
			|| creature->getWounds(CreatureAttribute::FOCUS) > 0
			|| creature->getWounds(CreatureAttribute::WILLPOWER) > 0)) {
		creature->addWounds(CreatureAttribute::MIND, -woundHeal);
		creature->addWounds(CreatureAttribute::FOCUS, -woundHeal);
		creature->addWounds(CreatureAttribute::WILLPOWER, -woundHeal);

		amountHealed += woundHeal;
	}

	if(entertainer->getGroup() != NULL)
		addHealingXpGroup(amountHealed);
	else
		addHealingXp(amountHealed);

}

void EntertainingSessionImplementation::addHealingXpGroup(int xp) {
	ManagedReference<GroupObject*> group = entertainer->getGroup();
	int groupSize = group->getGroupSize();
	ManagedReference<PlayerManager*> playerManager = entertainer->getZoneServer()->getPlayerManager();
	for(int i=0;i<groupSize;i++) {
		ManagedReference<CreatureObject*> groupMember = group->getGroupMember(i)->isPlayerCreature() ? cast<CreatureObject*>(group->getGroupMember(i)) : NULL;
		if(groupMember != NULL && groupMember->isEntertaining() && groupMember->isInRange(entertainer, 40.0f)
				&& groupMember->hasSkill("social_entertainer_novice")) {
			String healxptype("entertainer_healing");

			if (playerManager != NULL)
				playerManager->awardExperience(groupMember, healxptype, xp, true);

		}

	}
}

void EntertainingSessionImplementation::activateAction() {
	ManagedReference<SceneObject*> strongRef = entertainer.get();

	if (entertainer == NULL)
		return;

	Locker locker(entertainer);

	doEntertainerPatronEffects();
	doPerformanceAction();

	if (!isDancing() && !isPlayingMusic()) {
		return; // don't tick action if they aren't doing anything
	}

	ManagedReference<PlayerManager*> playerManager = entertainer->getZoneServer()->getPlayerManager();

	CreatureObject* player = entertainer->isPlayerCreature() ? cast<CreatureObject*>(entertainer.get()) : NULL;

	if (player != NULL) {
		if (flourishXp > 0) {
			String xptype;

			if (isDancing())
				xptype = "dance";
			else if (isPlayingMusic())
				xptype = "music";

			if (playerManager != NULL)
				playerManager->awardExperience(player, xptype, flourishXp, true);

			flourishXp--;
		}

		if (healingXp > 0) {
			String healxptype("entertainer_healing");

			if (playerManager != NULL)
				playerManager->awardExperience(player, healxptype, healingXp, true);

			healingXp = 0;
		}
	}

	flourishXp = 0;
	healingXp = 0;
	flourishCount = 0;

	startTickTask();

	player->info("EntertainerEvent completed.");
}

void EntertainingSessionImplementation::startTickTask() {
	if (tickTask == NULL) {
		tickTask = new EntertainingSessionTask(_this);
	}

	if (!tickTask->isScheduled()) {
		tickTask->schedule(10000);
	}
}

void EntertainingSessionImplementation::doPerformanceAction() {
	ManagedReference<CreatureObject*> ref = entertainer.get();

	if (ref == NULL)
		return;

	Locker locker(entertainer);

	Performance* performance = NULL;

	PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();
	ManagedReference<Instrument*> instrument = getInstrument(entertainer);

	if (isDancing())
		performance = performanceManager->getDance(performanceName);
	else if (isPlayingMusic() && instrument)
		performance = performanceManager->getSong(performanceName, instrument->getInstrumentType());
	else {
		cancelSession();
		return;
	}

	if (performance == NULL) { // shouldn't happen
		StringBuffer msg;
		msg << "Performance was null.  Please report to www.swgemu.com/bugs ! Name: " << performanceName << " and Type: " << dec << instrument->getInstrumentType();

		entertainer->sendSystemMessage(msg.toString());
		return;
	}

	int actionDrain = performance->getActionPointsPerLoop();

	if (entertainer->getHAM(CreatureAttribute::ACTION) <= actionDrain) {
		if (isDancing()) {
			stopDancing();
			entertainer->sendSystemMessage("@performance:dance_too_tired");
		}

		if (isPlayingMusic()) {
			stopPlayingMusic();
			entertainer->sendSystemMessage("@performance:music_too_tired");
		}
	} else {
		entertainer->inflictDamage(entertainer, CreatureAttribute::ACTION, actionDrain, false, true);
	}
}

Instrument* EntertainingSessionImplementation::getInstrument(CreatureObject* creature) {
	//all equipable instruments are in hold_r

	if (targetInstrument) {
		SceneObject* target = creature->getZoneServer()->getObject(creature->getTargetID());

		if (target == NULL)
			return NULL;

		Instrument* instrument = dynamic_cast<Instrument*>(target);

		if (externalInstrument != NULL && externalInstrument != instrument)
			return NULL;
		else
			return instrument;
	} else {
		SceneObject* object = creature->getSlottedObject("hold_r");

		return dynamic_cast<Instrument*>(object);
	}
}

void EntertainingSessionImplementation::stopPlayingMusic() {
	Locker locker(entertainer);

	if (!playingMusic)
		return;

	playingMusic = false;
	entertainer->sendSystemMessage("@performance:music_stop_self");

	sendEntertainingUpdate(entertainer, 0.8025000095f, entertainer->getPerformanceAnimation(), 0, 0);

	performanceName = "";
	entertainer->setListenToID(0);

	if (entertainer->getPosture() == CreaturePosture::SKILLANIMATING)
		entertainer->setPosture(CreaturePosture::UPRIGHT);

	if (externalInstrument != NULL && externalInstrument->isBeingUsed())
		externalInstrument->setBeingUsed(false);

	externalInstrument = NULL;

	ManagedReference<PlayerManager*> playerManager = entertainer->getZoneServer()->getPlayerManager();

	while (listeners.size() > 0) {
		ManagedReference<CreatureObject*> listener = listeners.elementAt(0).getKey();

		Locker clocker(listener, entertainer);

		playerManager->stopListen(listener, entertainer->getObjectID(), true, true, false);

		if (!listener->isWatching())
			sendEntertainmentUpdate(listener, 0, "", true);

		listeners.drop(listener);
	}

	if (tickTask != NULL && tickTask->isScheduled())
		tickTask->cancel();

	targetInstrument = false;
	updateEntertainerMissionStatus(false, MissionObject::MUSICIAN);

	entertainer->dropObserver(ObserverEventType::POSTURECHANGED, observer);

	if (!dancing && !playingMusic) {
		entertainer->dropActiveSession(SessionFacadeType::ENTERTAINING);
	}
}

void EntertainingSessionImplementation::startDancing(const String& dance, const String& animation) {
	Locker locker(entertainer);

	sendEntertainingUpdate(entertainer, /*0x3C4CCCCD*/0.0125, animation, 0x07339FF8, 0xDD);
	performanceName = dance;
	dancing = true;

	entertainer->sendSystemMessage("@performance:dance_start_self");

	updateEntertainerMissionStatus(true, MissionObject::DANCER);

	startEntertaining();
}

void EntertainingSessionImplementation::startPlayingMusic(const String& song, const String& instrumentAnimation, int instrid) {
	Locker locker(entertainer);

	sendEntertainingUpdate(entertainer, 0.0125, instrumentAnimation, 0x07352BAC, instrid);
	performanceName = song;
	playingMusic = true;

	entertainer->sendSystemMessage("@performance:music_start_self");

	entertainer->setListenToID(entertainer->getObjectID(), true);

	externalInstrument = getInstrument(entertainer);

	if (externalInstrument != NULL)
		externalInstrument->setBeingUsed(true);

	updateEntertainerMissionStatus(true, MissionObject::MUSICIAN);

	startEntertaining();
}

void EntertainingSessionImplementation::startEntertaining() {
	Locker locker(entertainer);

	entertainer->setPosture(CreaturePosture::SKILLANIMATING);

	startTickTask();

	if (observer == NULL) {
		observer = new EntertainingObserver();
		observer->deploy();
	}

	entertainer->registerObserver(ObserverEventType::POSTURECHANGED, observer);
}

void EntertainingSessionImplementation::stopDancing() {
	ManagedReference<CreatureObject*> ent = entertainer.get();

	if (ent == NULL)
		return;

	Locker locker(entertainer);

	if (!dancing)
		return;

	dancing = false;

	entertainer->sendSystemMessage("@performance:dance_stop_self");

	performanceName = "";

	sendEntertainingUpdate(entertainer, 0.8025000095f, entertainer->getPerformanceAnimation(), 0, 0);

	if (entertainer->getPosture() == CreaturePosture::SKILLANIMATING)
		entertainer->setPosture(CreaturePosture::UPRIGHT);


	ManagedReference<PlayerManager*> playerManager = entertainer->getZoneServer()->getPlayerManager();

	while (watchers.size() > 0) {
		ManagedReference<CreatureObject*> watcher = watchers.elementAt(0).getKey();

		Locker clocker(watcher, entertainer);

		playerManager->stopWatch(watcher, entertainer->getObjectID(), true, true, false);

		if (!watcher->isWatching())
			sendEntertainmentUpdate(watcher, 0, "", true);

		watchers.drop(watcher);
	}

	if (tickTask != NULL && tickTask->isScheduled())
		tickTask->cancel();

	updateEntertainerMissionStatus(false, MissionObject::DANCER);

	entertainer->dropObserver(ObserverEventType::POSTURECHANGED, observer);

	if (!dancing && !playingMusic) {
		entertainer->dropActiveSession(SessionFacadeType::ENTERTAINING);
	}
}

bool EntertainingSessionImplementation::canHealBattleFatigue() {
	if(entertainer->getSkillMod("private_med_battle_fatigue") > 0)
		return true;
	else
		return false;
}

bool EntertainingSessionImplementation::canGiveEntertainBuff() {
	if(entertainer->getSkillMod("private_buff_mind") > 0)
		return true;
	else
		return false;
}

// TODO: can this be simplified by doing the building check in the ticker?
void EntertainingSessionImplementation::addEntertainerFlourishBuff() {
	// Watchers that are in our group for passive buff
	VectorMap<ManagedReference<CreatureObject*>, EntertainingData>* patrons = NULL;
	if (dancing) {
			patrons = &watchers;
	}
	else if (playingMusic) {
			patrons = &listeners;
	}
	if (patrons != NULL) {
		for (int i = 0; i < patrons->size(); ++i) {
			ManagedReference<CreatureObject*> patron = patrons->elementAt(i).getKey();
			try {
				increaseEntertainerBuff(patron);
			} catch (Exception& e) {
				error("Unreported exception caught in EntertainingSessionImplementation::addEntertainerFlourishBuff()");
			}
		}
	} /*else
		System::out << "no patrons";*/

}

void EntertainingSessionImplementation::doFlourish(int flourishNumber) {
	int fid = flourishNumber;

	if (!dancing && !playingMusic) {
		entertainer->sendSystemMessage("@performance:flourish_not_performing");
		return;
	}

	PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();
	Performance* performance = NULL;
	ManagedReference<Instrument*> instrument = getInstrument(entertainer);

	if (dancing)
		performance = performanceManager->getDance(performanceName);
	else if (playingMusic && instrument)
		performance = performanceManager->getSong(performanceName, instrument->getInstrumentType());
	else {
		cancelSession();
		return;
	}

	if (!performance) { // shouldn't happen
		StringBuffer msg;
		msg << "Performance was null.  Please report to www.swgemu.com/bugs ! Name: " << performanceName << " and Type: " << dec << instrument->getInstrumentType();

		entertainer->sendSystemMessage(msg.toString());
		return;
	}

	float baseActionDrain =  performance->getActionPointsPerLoop();

	//float baseActionDrain = -40 + (getQuickness() / 37.5);
	float flourishActionDrain = baseActionDrain / 2.0;

	int actionDrain = (int)round((flourishActionDrain * 10 + 0.5) / 10.0); // Round to nearest dec for actual int cost

	if (entertainer->getHAM(CreatureAttribute::ACTION) <= actionDrain) {
		entertainer->sendSystemMessage("@performance:flourish_too_tired");
	} else {
		entertainer->inflictDamage(entertainer, CreatureAttribute::ACTION, actionDrain, false, true);

		if (dancing) {
			StringBuffer msg;
			msg << "skill_action_" << fid;
			entertainer->doAnimation(msg.toString());
		} else if (playingMusic) {
			Flourish* flourish = new Flourish(entertainer, fid);
			entertainer->broadcastMessage(flourish, true);
		}

		//check to see how many flourishes have occurred this tick
		if(flourishCount < 5) {
			// Add buff
			addEntertainerFlourishBuff();

			// Grant Experience
			if(flourishCount < 2)
				flourishXp += performance->getBaseXp() + performance->getFlourishXpMod();

			flourishCount++;
		}

		entertainer->sendSystemMessage("@performance:flourish_perform");
	}
}

void EntertainingSessionImplementation::addEntertainerBuffDuration(CreatureObject* creature, int performanceType, float duration) {
	int buffDuration = getEntertainerBuffDuration(creature, performanceType);

	buffDuration += duration;

	if (buffDuration > (120.0f + (10.0f / 60.0f)) ) // 2 hrs 10 seconds
		buffDuration = (120.0f + (10.0f / 60.0f)); // 2hrs 10 seconds

	setEntertainerBuffDuration(creature, performanceType, buffDuration);
}

void EntertainingSessionImplementation::addEntertainerBuffStrength(CreatureObject* creature, int performanceType, float strength) {

	int buffStrength = getEntertainerBuffStrength(creature, performanceType);


	float newBuffStrength = buffStrength + strength;

	float maxBuffStrength = 0.0f;	//cap based on enhancement skill
	if(dancing) {
		maxBuffStrength = (float) entertainer->getSkillMod("healing_dance_mind");
	}
	else if (playingMusic) {
		maxBuffStrength = (float) entertainer->getSkillMod("healing_music_mind");
	}

	if(maxBuffStrength > 125.0f)
		maxBuffStrength = 125.0f;	//cap at 125% power

	//add xp based on % added to buff strength
	if (newBuffStrength  < maxBuffStrength) {
		healingXp += strength;
	}
	else {
		healingXp += maxBuffStrength - buffStrength;
		newBuffStrength = maxBuffStrength;
	}

	//newBuffStrength = newBuffStrength;

	setEntertainerBuffStrength(creature, performanceType, newBuffStrength);
}

void EntertainingSessionImplementation::addWatcher(CreatureObject* creature) {
	if (watchers.contains(creature))
		watchers.drop(creature);

	EntertainingData data;

	watchers.put(creature, data);
}

void EntertainingSessionImplementation::addListener(CreatureObject* creature) {
	if (listeners.contains(creature))
		listeners.drop(creature);

	EntertainingData data;

	listeners.put(creature, data);
}

void EntertainingSessionImplementation::setEntertainerBuffDuration(CreatureObject* creature, int performanceType, float duration) {
	EntertainingData* data = NULL;

	switch(performanceType) {
	case PerformanceType::DANCE:
		if (!watchers.contains(creature))
			return;

		data = &watchers.get(creature);

		break;
	case PerformanceType::MUSIC:
		if (!listeners.contains(creature))
			return;

		data = &listeners.get(creature);

		break;
	}

	data->setDuration(duration);
}

int EntertainingSessionImplementation::getEntertainerBuffDuration(CreatureObject* creature, int performanceType) {
	EntertainingData* data = NULL;

	switch(performanceType) {
	case PerformanceType::DANCE:
		if (!watchers.contains(creature))
			return 0;

		data = &watchers.get(creature);

		break;
	case PerformanceType::MUSIC:
		if (!listeners.contains(creature))
			return 0;

		data = &listeners.get(creature);

		break;
	}

	return data->getDuration();
}

int EntertainingSessionImplementation::getEntertainerBuffStrength(CreatureObject* creature, int performanceType) {
	EntertainingData* data = NULL;

	switch(performanceType) {
	case PerformanceType::DANCE:
		if (!watchers.contains(creature))
			return 0;

		data = &watchers.get(creature);

		break;
	case PerformanceType::MUSIC:
		if (!listeners.contains(creature))
			return 0;

		data = &listeners.get(creature);

		break;
	}
	return data->getStrength();
}

int EntertainingSessionImplementation::getEntertainerBuffStartTime(CreatureObject* creature, int performanceType) {
	EntertainingData* data = NULL;
	switch(performanceType) {
	case PerformanceType::DANCE:
		if (!watchers.contains(creature))
			return 0;

		data = &watchers.get(creature);

		break;
	case PerformanceType::MUSIC:
		if (!listeners.contains(creature))
			return 0;

		data = &listeners.get(creature);

		break;
	}
	return data->getTimeStarted();
}

void EntertainingSessionImplementation::setEntertainerBuffStrength(CreatureObject* creature, int performanceType, float strength) {
	EntertainingData* data = NULL;

	switch(performanceType) {
	case PerformanceType::DANCE:
		if (!watchers.contains(creature))
			return;

		data = &watchers.get(creature);

		break;
	case PerformanceType::MUSIC:
		if (!listeners.contains(creature))
			return;

		data = &listeners.get(creature);

		break;
	}
	data->setStrength(strength);
}

void EntertainingSessionImplementation::sendEntertainmentUpdate(CreatureObject* creature, uint64 entid, const String& mood, bool updateEntValue) {
	creature->setListenToID(entid, true);

	if (updateEntValue)
		creature->setTerrainNegotiation(0.8025000095f, true);

	String str = Races::getMoodStr(mood);
	creature->setMoodString(str, true);
}


void EntertainingSessionImplementation::sendEntertainingUpdate(CreatureObject* creature, float entval, const String& performance, uint32 perfcntr, int instrid) {
	creature->setTerrainNegotiation(entval, true);

	creature->setPerformanceAnimation(performance, false);
	creature->setPerformanceCounter(0, false);
	creature->setInstrumentID(instrid, false);

	CreatureObjectDeltaMessage6* dcreo6 = new CreatureObjectDeltaMessage6(creature);
	dcreo6->updatePerformanceAnimation(performance);
	dcreo6->updatePerformanceCounter(0);
	dcreo6->updateInstrumentID(instrid);
	dcreo6->close();

	creature->broadcastMessage(dcreo6, true);
}

void EntertainingSessionImplementation::activateEntertainerBuff(CreatureObject* creature, int performanceType) {
	try {
		//Check if on Deny Service list
		if(isInDenyServiceList(creature)) {
			return;
		}

		ManagedReference<PlayerObject*> entPlayer = entertainer->getPlayerObject();
		//Check if the patron is a valid buff target
		//Whether it be passive(in the same group) or active (/setPerform target)
		if ((!entertainer->isGrouped() || entertainer->getGroupID() != creature->getGroupID())
				&& entPlayer->getPerformanceBuffTarget() != creature->getObjectID()) {
			return;
		}

		if(!canGiveEntertainBuff())
			return;

		// Returns the Number of Minutes for the Buff Duration
		float buffDuration = getEntertainerBuffDuration(creature, performanceType);

		if (buffDuration * 60 < 10.0f) { //10 sec minimum buff duration
			return;
		}

		//1 minute minimum listen/watch time
		int timeElapsed = time(0) - getEntertainerBuffStartTime(creature, performanceType);
		if(timeElapsed < 60) {
			creature->sendSystemMessage("@performance:buff_time_failed");
			return;
		}

		// Returns a % of base stat
		int campModTemp = 100;

		/*if (creature->isInCamp())
			campModTemp = getCampModifier();*/

		float buffStrength = getEntertainerBuffStrength(creature, performanceType) / 100.0f;

		if(buffStrength == 0)
			return;

		ManagedReference<PerformanceBuff*> oldBuff = NULL;
		switch (performanceType){
			case PerformanceType::MUSIC:
			{
				uint32 focusBuffCRC = String("performance_enhance_music_focus").hashCode();
				uint32 willBuffCRC = String("performance_enhance_music_willpower").hashCode();
				oldBuff = cast<PerformanceBuff*>(creature->getBuff(focusBuffCRC));
				if (oldBuff != NULL && oldBuff->getBuffStrength() > buffStrength)
					return;
				ManagedReference<PerformanceBuff*> focusBuff = new PerformanceBuff(creature, focusBuffCRC, buffStrength, buffDuration * 60, PerformanceBuffType::MUSIC_FOCUS);
				ManagedReference<PerformanceBuff*> willBuff = new PerformanceBuff(creature, willBuffCRC, buffStrength, buffDuration * 60, PerformanceBuffType::MUSIC_WILLPOWER);

				creature->addBuff(focusBuff);
				creature->addBuff(willBuff);
				break;
			}
			case PerformanceType::DANCE:
			{
				uint32 mindBuffCRC = String("performance_enhance_dance_mind").hashCode();
				oldBuff = cast<PerformanceBuff*>(creature->getBuff(mindBuffCRC));
				if (oldBuff != NULL && oldBuff->getBuffStrength() > buffStrength)
					return;
				ManagedReference<PerformanceBuff*> mindBuff = new PerformanceBuff(creature, mindBuffCRC, buffStrength, buffDuration * 60, PerformanceBuffType::DANCE_MIND);
				creature->addBuff(mindBuff);
				break;
			}
		}


	} catch(Exception& e) {

	}

}

void EntertainingSessionImplementation::updateEntertainerMissionStatus(bool entertaining, const int missionType) {
	if (entertainer == NULL) {
		return;
	}

	SceneObject* datapad = entertainer->getSlottedObject("datapad");

	if (datapad == NULL) {
		return;
	}

	//Notify all missions of correct type.
	int datapadSize = datapad->getContainerObjectsSize();
	for (int i = 0; i < datapadSize; ++i) {
		if (datapad->getContainerObject(i)->isMissionObject()) {
			MissionObject* datapadMission = cast<MissionObject*>(datapad->getContainerObject(i));

			if (datapadMission != NULL) {
				EntertainerMissionObjective* objective = cast<EntertainerMissionObjective*>(datapadMission->getMissionObjective());

				if (objective != NULL && datapadMission->getTypeCRC() == MissionObject::DANCER && missionType == MissionObject::DANCER) {
					objective->setIsEntertaining(entertaining);
				} else if (objective != NULL && datapadMission->getTypeCRC() == MissionObject::MUSICIAN && missionType == MissionObject::MUSICIAN) {
					objective->setIsEntertaining(entertaining);
				}
			}
		}
	}
}

void EntertainingSessionImplementation::increaseEntertainerBuff(CreatureObject* patron){
	PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();
	Performance* performance = NULL;

	ManagedReference<Instrument*> instrument = getInstrument(entertainer);

	if (performanceName == "")
		return;

	if (dancing) {
		performance = performanceManager->getDance(performanceName);
	} else if (playingMusic && instrument != NULL) {
		performance = performanceManager->getSong(performanceName, instrument->getInstrumentType());
	} else {
		cancelSession();
		return;
	}

	if(!canGiveEntertainBuff())
		return;

	if (performance == NULL) { // shouldn't happen
		return;
	}

	ManagedReference<PlayerObject*> entPlayer = entertainer->getPlayerObject();
	//Check if the patron is a valid buff target
	//Whether it be passive(in the same group) or active (/setPerform target)
	if ((!entertainer->isGrouped() || entertainer->getGroupID() != patron->getGroupID())
			&& entPlayer->getPerformanceBuffTarget() != patron->getObjectID()) {
		return;
	}

	if(isInDenyServiceList(patron))
		return;

	addEntertainerBuffDuration(patron, performance->getType(), 2.0f);
	addEntertainerBuffStrength(patron, performance->getType(), performance->getHealShockWound());

}
