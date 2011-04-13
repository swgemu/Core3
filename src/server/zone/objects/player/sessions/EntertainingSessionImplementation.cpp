/*
 * EntertainingSessionImplementation.cpp
 *
 *  Created on: 20/08/2010
 *      Author: victor
 */

#include "EntertainingSession.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/professions/Performance.h"
#include "server/zone/managers/professions/PerformanceManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/player/events/EntertainingSessionTask.h"
#include "server/zone/objects/player/EntertainingObserver.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/packets/object/Flourish.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage6.h"

void EntertainingSessionImplementation::doEntertainerPatronEffects() {
	ManagedReference<CreatureObject*> creo = entertainer.get();

	if (creo == NULL)
		return;

	Locker locker(entertainer);
	//info("EntertainingSessionImplementation::doEntertainerPatronEffects() begin");

	//**DECLARATIONS**
	VectorMap<ManagedReference<CreatureObject*>, EntertainingData>* patrons = NULL;

	PerformanceManager* performanceManager = ProfessionManager::instance()->getPerformanceManager();
	Performance* performance = NULL;
	float enhancementSkill = 0.0f;
	//int HealingXp = 0;
	int campModtemp = 100;
	bool canHeal = false;

	/*if (entertainer->isInCamp()) {
			campModtemp = getCampModifier();
		}*/

	if (performanceName == "")
		return;

	ManagedReference<Instrument*> instrument = getInstrument(entertainer);

	//**LOAD PATRONS, GET THE PERFORMANCE AND ENT'S HEALING SKILL.**
	if (dancing) {
		//woundAbility = getSkillMod("healing_dance_wound");
		patrons = &watchers;
		performance = performanceManager->getDance(performanceName);
		enhancementSkill = (float) entertainer->getSkillMod("healing_dance_mind");

	} else if (playingMusic && instrument != NULL) {
		//woundAbility = getSkillMod("healing_music_wound");
		patrons = &listeners;
		performance = performanceManager->getSong(performanceName, instrument->getInstrumentType());
		enhancementSkill = (float) entertainer->getSkillMod("healing_music_mind");

	} else {
		cancelSession();
		return;
	}

	if (performance == NULL) {
		return;
	}

	//**DETERMINE IF THE ENT CAN HEAL.**
	canHeal = isInEntertainingBuilding(entertainer);

	//**DETERMINE WOUND HEAL AMOUNTS.**
	int woundHeal = performance->getHealMindWound() * campModtemp / 100;
	int shockHeal = performance->getHealShockWound() * campModtemp / 100;

	//**ENTERTAINER HEALS THEIR OWN MIND.**
	if (canHeal && (entertainer->getWounds(CreatureAttribute::MIND) > 0
			|| entertainer->getWounds(CreatureAttribute::FOCUS) > 0
			|| entertainer->getWounds(CreatureAttribute::WILLPOWER) > 0
			|| entertainer->getShockWounds() > 0)) {

		healWounds(entertainer, woundHeal, shockHeal);
	}

	//**APPLY EFFECTS TO PATRONS.**
	if (patrons != NULL && patrons->size() > 0) {

		for (int i = 0; i < patrons->size(); ++i) {
			ManagedReference<CreatureObject*> patron = patrons->elementAt(i).getKey();

			try {
				//**VERIFY THE PATRON IS IN RANGE OF THE ENT.
				bool patronInRange = false;

				if (entertainer->isInRange(patron, 40.0f) && patron->getRootParent() == entertainer->getRootParent()) {
					patronInRange = true;
				}

				if (patronInRange) {
					if (canHeal && (patron->getWounds(CreatureAttribute::MIND) > 0
							|| patron->getWounds(CreatureAttribute::FOCUS) > 0
							|| patron->getWounds(CreatureAttribute::WILLPOWER) > 0
							|| patron->getShockWounds() > 0)) {

						Locker clocker(patron, entertainer);

						healWounds(patron, woundHeal, shockHeal);
					}

					// Handle Passive Buff
					if (canHeal && entertainer->getGroup() != NULL && (entertainer->getGroupID() == patron->getGroupID())) {
						// Add 1 minute per tick
						float dur = 1.0f;

						// If T'ssolok is active, then increase the amount added per tick.
						if (entertainer->hasBuff(BuffCRC::FOOD_ACCELERATE_ENTERTAINER_BUFF)) {
							ManagedReference<Buff*> buff = entertainer->getBuff(BuffCRC::FOOD_ACCELERATE_ENTERTAINER_BUFF);

							if (buff != NULL)
								dur += (buff->getSkillModifierValue("accelerate_entertainer_buff") / 100.0f);
						}

						addEntertainerBuffDuration(patron, performance->getType(), dur);
						setEntertainerBuffStrength(patron, performance->getType(), enhancementSkill / 100.0f);
					}

				} else { //patron is not in range
					ManagedReference<PlayerManager*> playerManager = patron->getZoneServer()->getPlayerManager();

					if (dancing) {
						if (playerManager != NULL)
							playerManager->stopWatch(patron, entertainer->getObjectID(), true, false, false, true);

						if (!patron->isListening())
							sendEntertainmentUpdate(entertainer, 0, "", true);

					} else if (playingMusic) {
						if (playerManager != NULL)
							playerManager->stopListen(patron, entertainer->getObjectID(), true, false, false, true);

						if (!patron->isWatching())
							sendEntertainmentUpdate(entertainer, 0, "", true);
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
		case SceneObject::RECREATIONBUILDING:
		case SceneObject::HOTELBUILDING:
		case SceneObject::THEATERBUILDING:
			return true;
		}
	}

	return false;
}

void EntertainingSessionImplementation::healWounds(CreatureObject* creature, float woundHeal, float shockHeal) {
	creature->addWounds(CreatureAttribute::MIND, -woundHeal);
	creature->addWounds(CreatureAttribute::FOCUS, -woundHeal);
	creature->addWounds(CreatureAttribute::WILLPOWER, -woundHeal);

	creature->addShockWounds(-shockHeal);

	healingXp += shockHeal;
	healingXp += woundHeal;
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

	PlayerCreature* player = entertainer->isPlayerCreature() ? (PlayerCreature*)entertainer.get() : NULL;

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

	//player->setEntertainerEvent(); // Renew tick

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

	PerformanceManager* performanceManager = ProfessionManager::instance()->getPerformanceManager();
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
			entertainer->sendSystemMessage("performance", "dance_too_tired");
		}

		if (isPlayingMusic()) {
			stopPlayingMusic();
			entertainer->sendSystemMessage("performance", "music_too_tired");
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
	entertainer->sendSystemMessage("performance", "music_stop_self");

	sendEntertainingUpdate(entertainer, 0.8025000095f, entertainer->getPerformanceAnimation(), 0, 0);

	performanceName = "";
	entertainer->setListenToID(0);
	//entertainer->setPosture(CreaturePosture::UPRIGHT);

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

	entertainer->sendSystemMessage("performance", "dance_start_self");

	startEntertaining();
}

void EntertainingSessionImplementation::startPlayingMusic(const String& song, const String& instrumentAnimation, int instrid) {
	Locker locker(entertainer);

	sendEntertainingUpdate(entertainer, 0.0125, instrumentAnimation, 0x07352BAC, instrid);
	performanceName = song;
	playingMusic = true;

	entertainer->sendSystemMessage("performance", "music_start_self");

	entertainer->setListenToID(entertainer->getObjectID(), true);

	externalInstrument = getInstrument(entertainer);

	if (externalInstrument != NULL)
		externalInstrument->setBeingUsed(true);

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

	entertainer->sendSystemMessage("performance", "dance_stop_self");

	performanceName = "";

	sendEntertainingUpdate(entertainer, 0.8025000095f, entertainer->getPerformanceAnimation(), 0, 0);

	if (entertainer->getPosture() == CreaturePosture::SKILLANIMATING)
		entertainer->setPosture(CreaturePosture::UPRIGHT);

	//entertainer->setListenToID(0);

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

	entertainer->dropObserver(ObserverEventType::POSTURECHANGED, observer);

	if (!dancing && !playingMusic) {
		entertainer->dropActiveSession(SessionFacadeType::ENTERTAINING);
	}

}

bool EntertainingSessionImplementation::canGiveEntertainBuff() {
	return isInEntertainingBuilding(entertainer);
}

// TODO: can this be simplified by doing the building check in the ticker?
void EntertainingSessionImplementation::addEntertainerFlourishBuff() {
	// Watchers that are in our group for passive buff
	VectorMap<ManagedReference<CreatureObject*>, EntertainingData>* patrons = NULL;

	PerformanceManager* performanceManager = ProfessionManager::instance()->getPerformanceManager();
	Performance* performance = NULL;

	ManagedReference<Instrument*> instrument = getInstrument(entertainer);

	if (performanceName == "")
		return;

	if (dancing) {
		//woundAbility = getSkillMod("healing_dance_wound");
		patrons = &watchers;
		performance = performanceManager->getDance(performanceName);
	} else if (playingMusic && instrument != NULL) {
		//woundAbility = getSkillMod("healing_music_wound");
		patrons = &listeners;
		performance = performanceManager->getSong(performanceName, instrument->getInstrumentType());
	} else {
		cancelSession();
		return;
	}

	if (performance == NULL) { // shouldn't happen
		StringBuffer msg;
		msg << "Performance was null.  Please report to www.swgemu.com/bugs ! Name: " << performanceName << " and Type: " << dec << instrument->getInstrumentType();

		entertainer->sendSystemMessage(msg.toString());
		return;
	}

	if (patrons != NULL) {
		for (int i = 0; i < patrons->size(); ++i) {
			ManagedReference<CreatureObject*> obj = patrons->elementAt(i).getKey();
			try {
				//Locker clocker(entertainer, obj);

				// Passive Buff only to group members
				if (entertainer->getGroupID() == 0
						|| (entertainer->getGroupID() != obj->getGroupID())) {
					continue;
				}

				bool patronInRange = false;

				if (obj->getRootParent() == entertainer->getRootParent())
					patronInRange = true;

				if (patronInRange)
					addEntertainerBuffDuration(obj, performance->getType(), 1.0f);

			} catch (Exception& e) {
				error("Unreported exception caught in EntertainingSessionImplementation::doHealMindWounds()");
			}
		}
	} /*else
		System::out << "no patrons";*/

}

void EntertainingSessionImplementation::doFlourish(int flourishNumber) {
	int fid = flourishNumber;

	if (!dancing && !playingMusic) {
		entertainer->sendSystemMessage("performance", "flourish_not_performing");
		return;
	}

	PerformanceManager* performanceManager = ProfessionManager::instance()->getPerformanceManager();
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
		entertainer->sendSystemMessage("performance", "flourish_too_tired");
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

		// Add buff
		if (canGiveEntertainBuff()){
			//sendSystemMessage("Flourish Buff");
			addEntertainerFlourishBuff();
		}

		// Grant Experience

		addFlourishXp(performance->getBaseXp() + performance->getFlourishXpMod());

		entertainer->sendSystemMessage("performance", "flourish_perform");
	}
}

void EntertainingSessionImplementation::addEntertainerBuffDuration(CreatureObject* creature, int performanceType, float duration) {
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

	int buffDuration = data->getDuration();

	buffDuration += duration;

	if (buffDuration > (120.0f + (10.0f / 60.0f)) ) // 2 hrs 10 seconds
		buffDuration = (120.0f + (10.0f / 60.0f)); // 2hrs 10 seconds

	data->setDuration(buffDuration);
}

void EntertainingSessionImplementation::addEntertainerBuffStrength(CreatureObject* creature, int performanceType, float strength) {
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

	int buffStrength = data->getStrength();

	buffStrength += strength;

	if (buffStrength > 125.0f)
		buffStrength = 125.0f; // 125% cap

	data->setStrength(buffStrength);
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

	// Returns the Number of Minutes for the Buff Duration
	float buffDuration = getEntertainerBuffDuration(creature, performanceType);

	if (buffDuration * 60 < 10.0f) { //10 sec minimum buff duration
		return;
	}

	// Returns a % of base stat
	int campModTemp = 100;

	/*if (creature->isInCamp())
		campModTemp = getCampModifier();*/

	float buffStrength = getEntertainerBuffStrength(creature, performanceType) * campModTemp / 100;
	//System::out << "activateEntertainerBuff(" << performanceType << ") called for " << getCharacterName().toString() << " with duration: " << buffDuration << " strength: ";
	//System::out.precision(4);
	//System::out << buffStrength << endl;

	//TODO: Redo with a PerformanceBuff class.
	ManagedReference<Buff*> buff = NULL;
	switch (performanceType){
	case PerformanceType::MUSIC:
	{
		uint32 buff1 = String("performance_enhance_music_focus").hashCode();

		ManagedReference<Buff*> oldBuff = creature->getBuff(buff1);

		if (oldBuff != NULL && oldBuff->getBuffDuration() > buffDuration * 60)
			return;

		buff = new Buff(creature, buff1, buffDuration * 60, BuffType::PERFORMANCE);
		buff->setAttributeModifier(7, (int) round(buffStrength * creature->getBaseHAM(CreatureAttribute::FOCUS)));
		creature->addBuff(buff);

		buff = new Buff(creature, String("performance_enhance_music_willpower").hashCode(), buffDuration * 60, BuffType::PERFORMANCE);
		buff->setAttributeModifier(8, (int) round(buffStrength * creature->getBaseHAM(CreatureAttribute::WILLPOWER)));
		creature->addBuff(buff);

		creature->sendSystemMessage("healing", "performance_enhance_music_focus_d");
		creature->sendSystemMessage("healing", "performance_enhance_music_willpower_d");
		break;
	}
	case PerformanceType::DANCE:
	{
		uint32 buff1 = String("performance_enhance_dance_mind").hashCode();

		ManagedReference<Buff*> oldBuff = creature->getBuff(buff1);

		if (oldBuff != NULL && oldBuff->getBuffDuration() > buffDuration * 60)
			return;

		buff = new Buff(creature, String("performance_enhance_dance_mind").hashCode(), buffDuration * 60, BuffType::PERFORMANCE);
		buff->setAttributeModifier(6, (int) round(buffStrength * creature->getBaseHAM(CreatureAttribute::MIND)));
		creature->addBuff(buff);

		creature->sendSystemMessage("healing", "performance_enhance_dance_mind_d");
	}
	}

}
