/*
 * AiActorImplementation.cpp
 *
 *  Created on: May 7, 2012
 *      Author: da
 */

#include "AiActor.h"
#include "components/AiStateComponent.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/events/CamoTask.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/templates/AiTemplate.h"
#include "server/zone/templates/mobile/MobileOutfit.h"
#include "server/zone/templates/mobile/MobileOutfitGroup.h"
#include "engine/util/Observable.h"
#include "engine/util/u3d/Coordinate.h"
#include "system/lang/ref/Reference.h"
#include "system/thread/Locker.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/creature/events/AiMoveEvent.h"
#include "server/zone/objects/creature/events/AiAwarenessEvent.h"
#include "server/zone/objects/creature/events/AiThinkEvent.h"
#include "server/zone/objects/creature/events/DespawnCreatureOnPlayerDissappear.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "system/thread/Mutex.h"
#include "engine/core/ManagedReference.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "AiObserver.h"

using server::zone::objects::creature::conversation::ConversationObserver;

void AiActorImplementation::setNpcTemplate(CreatureTemplate* templ) {
	npcTemplate = templ;
}

void AiActorImplementation::loadAiTemplate(const String& templateName) {
	CreatureTemplateManager* templateManager = CreatureTemplateManager::instance();

	aiTemplate = templateManager->getAiTemplate(templateName);

	if (aiTemplate == NULL) {
		// TODO: this will spam until I fill aiTemplate fields in the mobile scripts
		// error("no ai template in AiActor " + templateData->getTemplateName());
		aiTemplate = templateManager->getAiTemplate("static");
	}

	defaultStateName = aiTemplate->getDefaultName();
	currentStateName = "SpawnStateComponent"; // need to start with spawn state
	currentState = ComponentManager::instance()->getComponent<AiStateComponent*>(currentStateName);

	if (currentState == NULL) {
		error("spawn state undefined");
		return;
	}

	transitions = aiTemplate->getTransitions();

	currentMessage = currentState->onEnter(_this.get());
}

void AiActorImplementation::loadTemplateData(CreatureTemplate* templateData) {
	ZoneProcessServer* server = getZoneProcessServer();
	if (server == NULL)
		return;

	npcTemplate = templateData;

	if (host == NULL) {
		error("no host in AiActor " + templateData->getTemplateName());
		return;
	}

	// TODO: this is so previous systems work while phasing out AiAgent:
	if (host->isAiAgent()) {
		host.castTo<AiAgent*>()->loadTemplateData(npcTemplate);
	}

	host->setPvpStatusBitmask(npcTemplate->getPvpBitmask());

	host->setOptionsBitmask(npcTemplate->getOptionsBitmask());
	//npcTemplate->getCreatureBitmask(); -- TODO: need to add a bitmask for AI (pack, herd, etc)

	if (weapons.size() == 0) {
		Vector<String> wepgroups = npcTemplate->getWeapons();
		for (int i = 0; i < wepgroups.size(); ++i) {
			Vector<String> weptemps = CreatureTemplateManager::instance()->getWeapons(wepgroups.get(i));

			for (int i = 0; i < weptemps.size(); ++i) {
				uint32 crc = weptemps.get(i).hashCode();

				ManagedReference<WeaponObject*> weao = dynamic_cast<WeaponObject*>(server->getZoneServer()->createObject(crc, 0));

				if (weao != NULL) {
					weapons.add(weao);
					if (i == 0) host->transferObject(weao, 4, false);
				} else
					error("could not create weapon " + weptemps.get(i));
			}
		}
	}

	WeaponObject* defaultWeapon = cast<WeaponObject*>(host->getSlottedObject("default_weapon"));
	if (defaultWeapon != NULL && !weapons.contains(defaultWeapon))
		weapons.add(defaultWeapon);

	setLevel(npcTemplate->getLevel());

	StringId objName(npcTemplate->getObjectName());
	host->setObjectName(objName);
	host->setCustomObjectName(npcTemplate->getCustomName(), false);

	host->setHeight(npcTemplate->getScale(), false);

	String currentLogName = getLoggingName();
	if (!currentLogName.contains(npcTemplate->getTemplateName())) {
		StringBuffer logName;
		logName << getLoggingName() << "[" << npcTemplate->getTemplateName() << "]";

		setLoggingName(logName.toString());
	}

	String pvpFaction = npcTemplate->getPvpFaction();
	if (!pvpFaction.isEmpty() && (pvpFaction == "imperial" || pvpFaction == "rebel"))
		host->setFaction(pvpFaction.hashCode());

	if (!loadedOutfit) {
		loadedOutfit = true;
		String outfit = npcTemplate->getOutfit();

		if (!outfit.isEmpty()) {
			MobileOutfitGroup* group = CreatureTemplateManager::instance()->getMobileOutfitGroup(outfit);

			if (group != NULL) {
				Vector<MobileOutfit>* outfits = group->getOutfits();

				int num = System::random(outfits->size() - 1);

				if (num > -1) {
					MobileOutfit* clothes = &outfits->get(num);

					Vector<OutfitTangibleObject>* objects = clothes->getObjects();

					for (int i = 0; i < objects->size(); ++i) {
						OutfitTangibleObject* obj = &objects->get(i);

						String templ = obj->getObjectTemplate();

						ManagedReference<TangibleObject*> tano = dynamic_cast<TangibleObject*>(server->getZoneServer()->createObject(templ.hashCode(), 0));

						if (tano != NULL) {
							VectorMap<String, uint8>* cust = obj->getCustomizationVariables();

							for (int j = 0; j < cust->size(); ++j) {
								tano->setCustomizationVariable(cust->elementAt(j).getKey(), cust->elementAt(j).getValue());
							}

							host->transferObject(tano, 4, false);
						}

					}
				}
			} else {
				error("null outfit group " + outfit);
			}
		}
	}
}

void AiActorImplementation::setLevel(int lvl) {
	if (lvl == 0)
		return;

	host->setLevel(lvl);

	if (npcTemplate == NULL) {
		return;
	}

	int baseLevel = npcTemplate->getLevel();

	float minDmg = calculateAttackMinDamage(baseLevel);
	float maxDmg = calculateAttackMaxDamage(baseLevel);
	float speed = calculateAttackSpeed(baseLevel);

	WeaponObject* defaultWeapon = cast<WeaponObject*>(host->getSlottedObject("default_weapon"));

	float ratio = ((float)lvl) / (float)baseLevel;

	minDmg *= ratio;
	maxDmg *= ratio;

	if (ratio != 0)
		speed = MIN(4, speed / ratio);

	for (int i = 0; i < weapons.size(); ++i) {
		WeaponObject* weao = weapons.get(i);

		weao->setMinDamage(minDmg * 0.5);
		weao->setMaxDamage(maxDmg * 0.5);
		weao->setAttackSpeed(speed);
	}

	if (defaultWeapon != NULL) {
		defaultWeapon->setMinDamage(minDmg);
		defaultWeapon->setMaxDamage(maxDmg);
		defaultWeapon->setAttackSpeed(speed);
	}

	int baseHamMax = ((float)npcTemplate->getBaseHAMmax()) * ratio;
	int baseHam = ((float)npcTemplate->getBaseHAM()) * ratio;

	int ham;

	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) {
			ham = System::random(baseHamMax - baseHam) + baseHam;
			host->setBaseHAM(i, ham);
		} else
			host->setBaseHAM(i, ham / 100);

		host->setHAM(i, host->getBaseHAM(i));
		host->setMaxHAM(i, host->getBaseHAM(i));
	}
}

int AiActorImplementation::calculateAttackMinDamage(int level) {
	int minDmg = MAX(npcTemplate->getDamageMin(), 50 + (level * 5));

	return minDmg;
}

int AiActorImplementation::calculateAttackMaxDamage(int level) {
	int dmg = MAX(npcTemplate->getDamageMax(), calculateAttackMinDamage(level) * 2);

	return dmg;
}

float AiActorImplementation::calculateAttackSpeed(int level) {
	float speed = 3.5f - ((float)level / 100.f);

	return speed;
}

void AiActorImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	defaultStateName = "AiStateComponent";
	currentStateName = "AiStateComponent";
	currentState = ComponentManager::instance()->getComponent<AiStateComponent*>(currentStateName);
	currentMessage = AiActor::UNFINISHED;

	movementMarkers = new Vector<ManagedReference<SceneObject*> >();

 	ManagedReference<AiObserver*> aiObserver = new AiObserver();
 	aiObserver->deploy();

 	registerObserver(ObserverEventType::OBJECTDESTRUCTION, aiObserver);
 	registerObserver(ObserverEventType::DAMAGERECEIVED, aiObserver);
 	registerObserver(ObserverEventType::OBJECTINRANGEMOVED, aiObserver);

	transitions.removeAll();
}

void AiActorImplementation::next(uint16 msg) {
	if (msg == AiActor::NONE) {
		error("AiActor is incomplete (most likely no host).");
		Reference<DespawnCreatureTask*> task = new DespawnCreatureTask(_this.get());
		task->execute();
		return;
	}

	activateRecovery();

	String resultStateName = transitions.get(currentStateName + String::valueOf(msg));

	if (resultStateName == currentStateName || resultStateName == "") {
		currentMessage = currentState->doRecovery(_this.get());
		return;
	}

	currentState->onExit(_this.get());

	currentStateName = resultStateName;
	currentState = ComponentManager::instance()->getComponent<AiStateComponent*>(currentStateName);

	currentMessage = currentState->onEnter(_this.get());

	info("set mob to state " + currentStateName, true);
}

void AiActorImplementation::next() {
	next(currentMessage);
}

void AiActorImplementation::destroyActor() {
	ManagedReference<Task*> despawn = getPendingTask("despawn");
	if (despawn != NULL) {
		removePendingTask("despawn");
		despawn->cancel();
	}

	if (thinkEvent != NULL && thinkEvent->isScheduled())
		thinkEvent->cancel();

	if (moveEvent != NULL && moveEvent->isScheduled())
		moveEvent->cancel();

	if (awarenessEvent != NULL && awarenessEvent->isScheduled())
		awarenessEvent->cancel();

	if (despawnEvent != NULL && despawnEvent->isScheduled())
		despawnEvent->cancel();

	destroyObjectFromWorld(true);
	destroyObjectFromDatabase(true);
}

void AiActorImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	// first do host checks to make sure it is appropriate
	if (host == NULL || host->isDead() || getNumberOfPlayersInRange() <= 0 || host->isInCombat() || host->getPvpStatusBitmask() == CreatureFlag::NONE)
		return;

	// second do actor checks
	int radius = 32;
	if(host->getParent() != NULL && host->getParent().get()->isCellObject())
		radius = 12;

	int awarenessRadius = getFerocity() + radius;

	if (!entry->isInRange(host, awarenessRadius) || getNumberOfPlayersInRange() <= 0)
		return;

	// now do entry checks to make sure the entry shouldn't be ignored
	Reference<CreatureObject*> creoEntry = cast<CreatureObject*>(entry);

	if (creoEntry == host || creoEntry == NULL || creoEntry->getPvpStatusBitmask() == CreatureFlag::NONE || isCamouflaged(creoEntry))
		return;

	// If not in combat, ignore creatures in different cells
	if (host->getParent() != NULL && host->getParent().get() != creoEntry->getParent().get())
		return;

	if (getFollowObject() == NULL || getFollowObject() == creoEntry) {
		Coordinate hostCoord(host->getPositionX(), host->getPositionZ(), host->getPositionY());
		doAwarenessCheck(hostCoord, 0, creoEntry); // TODO: this will become an awareness event
	}

	currentState->notifyPositionUpdate(_this.get(), entry);
}

void AiActorImplementation::notifyInsert(QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>(entry);

	if (scno == host || scno == NULL)
		return;

	if (scno->isPlayerCreature())
		++numberOfPlayersInRange;
}

void AiActorImplementation::notifyDissapear(QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>(entry);

	if (scno == host || scno == NULL)
		return;

	if (scno == followObject.get())
		setFollowObject(NULL);

	if (scno->isPlayerCreature()) {
		if ((--numberOfPlayersInRange <= 0)  && (despawnEvent == NULL)) {
			/*despawnEvent = new DespawnCreatureOnPlayerDissappear(_this);
			despawnEvent->schedule(30000);*/
		}
	}
}

int AiActorImplementation::notifyConverseObservers(CreatureObject* converser) {
	notifyObservers(ObserverEventType::CONVERSE, converser);

	return 1;
}

void AiActorImplementation::doAwarenessCheck(Coordinate &start, uint64 time, CreatureObject* target) {
	currentState->doAwarenessCheck(_this.get(), start, time, target);
}

void AiActorImplementation::addTransition(const String& stateName, uint16 msg, const String& resultState) {
	transitions.put(stateName + String::valueOf(msg), resultState);
}

bool AiActorImplementation::isScentMasked(CreatureObject* target) {
	if (!host->isCreature())
		return false;

	Locker locker(&targetMutex);

	// Check masked scent
	if (!target->hasState(CreatureState::MASKSCENT)) {
		if(camouflagedObjects.contains(target)) camouflagedObjects.removeElement(target);
		return false;
	}

	// Don't do anything if object is ignored (Camo / Masked Scent)
	if (camouflagedObjects.contains(target))
		return true;

	int camoSkill = target->getSkillMod("mask_scent");
	int creatureLevel = host->getLevel();

	bool success = false;

	if (System::random(100) <= (-1 * (1 / ((camoSkill / 100.0f) * 20)) * creatureLevel) + 100) {
		camouflagedObjects.add(target);
		success = true;
	}

	Reference<Task*> ct = new CamoTask(target, host, true, success);
	ct->execute();

	return success;
}

bool AiActorImplementation::isConcealed(CreatureObject* target) {
	Locker locker(&targetMutex);

	if (!target->hasState(CreatureState::MASKSCENT)) {
		if(camouflagedObjects.contains(target)) camouflagedObjects.removeElement(target);
		return false;
	}

	// Don't do anything if object is ignored (Camo / Masked Scent)
	if (camouflagedObjects.contains(target))
		return true;

	// Check if camo breaks
	int camoSkill = target->getSkillMod("private_conceal");
	int creatureLevel = host->getLevel();

	if (!host->isCreature())
		creatureLevel *= 2;

	bool success = false;

	if (System::random(100) < (-1 * (1 / ((camoSkill / 100.0f) * 20)) * creatureLevel) + 100) {
		camouflagedObjects.add(target);
		success = true;
	}

	Reference<Task*> ct = new CamoTask(target, host, false, success);
	ct->execute();

	return success;
}

void AiActorImplementation::activateRecovery() {
	if (thinkEvent == NULL) {
		thinkEvent = new AiThinkEvent(_this.get());

		thinkEvent->schedule(2000);
	}

	if (!thinkEvent->isScheduled())
		thinkEvent->schedule(2000);
}

void AiActorImplementation::activateMovementEvent() {
	if (getZone() == NULL)
		return;

	if (moveEvent == NULL) {
		moveEvent = new AiMoveEvent(_this.get());

		moveEvent->schedule(UPDATEMOVEMENTINTERVAL);
	}

	if (!moveEvent->isScheduled())
		moveEvent->schedule(UPDATEMOVEMENTINTERVAL);
}

void AiActorImplementation::activateAwarenessEvent(CreatureObject *target) {
#ifdef DEBUG
	info("Starting activateAwarenessEvent check", true);
#endif

	if (awarenessEvent == NULL) {
		awarenessEvent = new AiAwarenessEvent(_this.get(), target);

		awarenessEvent->schedule(1000);

#ifdef DEBUG
		info("Scheduling new Awareness Event", true);
#endif
	}

	if (!awarenessEvent->isScheduled()) {
		awarenessEvent->setTarget(target);
		awarenessEvent->schedule(1000);

#ifdef DEBUG
		info("Rescheduling awareness event", true);
#endif
	}
}

void AiActorImplementation::activatePostureRecovery() {
	if (host->isProne() || host->isKnockedDown() || host->isKneeling())
		host->executeObjectControllerAction(0xA8A25C79); // stand
}

void AiActorImplementation::queueDizzyFallEvent() {
	if (System::random(10) == 1)
		host->queueDizzyFallEvent();
}

void AiActorImplementation::setDespawnOnNoPlayerInRange(bool val) {
	if (despawnOnNoPlayerInRange == val)
		return;

	despawnOnNoPlayerInRange = val;

	if (val && numberOfPlayersInRange <= 0) {
		if (despawnEvent == NULL) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(_this.get());
		}

		if (!despawnEvent->isScheduled())
			despawnEvent->schedule(30000);
	}
}

void AiActorImplementation::notifyDespawn(Zone* zone) {
	currentState->notifyDespawn(_this.get(), zone);
}

void AiActorImplementation::scheduleDespawn(int timeToDespawn) {
	if (getPendingTask("despawn") != NULL)
		return;

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(_this.get());
	addPendingTask("despawn", despawn, timeToDespawn * 1000);
}

void AiActorImplementation::respawn(Zone* zone, int level) {
	setZone(zone);
	next(AiActor::FINISHED);
}

void AiActorImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {

	if (host->isDead())
		return;

	if (getArmor() == 0)
		alm->insertAttribute("armorrating", "None");
	else if (getArmor() == 1)
		alm->insertAttribute("armorrating", "Light");
	else if (getArmor() == 2)
		alm->insertAttribute("armorrating", "Medium");
	else if (getArmor() == 3)
		alm->insertAttribute("armorrating", "Heavy");

	if (getKinetic() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", "100%");

	if (getEnergy() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", "100%");

	if (getElectricity() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", "100%");

	if (getStun() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", "100%");

	if (getBlast() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", "100%");

	if (getHeat() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", "100%");

	if (getCold() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", "100%");

	if (getAcid() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", "100%");

	if (getLightSaber() == 100)
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", "100%");

	if (getKinetic() > 0 && getKinetic() < 100) {
		StringBuffer txt;
		txt << round(getKinetic()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 0 && getEnergy() < 100) {
		StringBuffer txt;
		txt << round(getEnergy()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 0 && getElectricity() < 100) {
		StringBuffer txt;
		txt << round(getElectricity()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 0 && getStun() < 100) {
		StringBuffer txt;
		txt << round(getStun()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 0 && getBlast() < 100) {
		StringBuffer txt;
		txt << round(getBlast()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 0 && getHeat() < 100) {
		StringBuffer txt;
		txt << round(getHeat()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 0 && getCold() < 100) {
		StringBuffer txt;
		txt << round(getCold()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 0 && getAcid() < 100) {
		StringBuffer txt;
		txt << round(getAcid()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 0 && getLightSaber() < 100) {
		StringBuffer txt;
		txt << round(getLightSaber()) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (getEnergy() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (getElectricity() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (getStun() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (getBlast() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (getHeat() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (getCold() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (getAcid() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (getLightSaber() == 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");
}

void AiActorImplementation::sendConversationStartTo(SceneObject* player) {
	if (!player->isPlayerCreature())
		return;

	currentState->sendConversationStartTo(host, player);

	SortedVector<ManagedReference<Observer*> >* observers = observerEventMap.getObservers(ObserverEventType::STARTCONVERSATION);

	if (observers != NULL) {
		for (int i = 0;  i < observers->size(); ++i) {
			if (dynamic_cast<ConversationObserver*>(observers->get(i).get()) != NULL)
				return;
		}
	}

	if (npcTemplate == NULL)
		return;
	//Create conversation observer.
	ConversationObserver* conversationObserver = ConversationManager::instance()->getConversationObserver(npcTemplate->getConversationTemplate());

	if (conversationObserver != NULL) {
		//Register observers.
		registerObserver(ObserverEventType::CONVERSE, conversationObserver);
		registerObserver(ObserverEventType::STARTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::SELECTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::STOPCONVERSATION, conversationObserver);
	} else {
		error("Could not create conversation observer.");
	}
}

void AiActorImplementation::setDefender(SceneObject* defender) {
	host->setDefender(defender);
	setFollowObject(defender);
	currentMessage = AiActor::ATTACKED;
}

void AiActorImplementation::addDefender(SceneObject* defender) {
	host->addDefender(defender);
	currentMessage = AiActor::ATTACKED;
}

void AiActorImplementation::removeDefender(SceneObject* defender) {
	host->removeDefender(defender);

	if (defender != NULL && defender->isCreatureObject())
		host->getThreatMap()->dropDamage(cast<CreatureObject*>(defender));

	if (followObject == defender) {
		CreatureObject* target = host->getThreatMap()->getHighestThreatCreature();

		if (target == NULL && host->getDefenderList()->size() > 0) {
			SceneObject* tarObj = host->getDefenderList()->get(0);
			if (tarObj->isCreatureObject())
				target = cast<CreatureObject*>(tarObj);
		}

		if (target == NULL) {
			setFollowObject(NULL);
			next(AiActor::FORGOT);
		} else  {
			setDefender(target);
		}
	}
}

bool AiActorImplementation::isAggressiveTo(CreatureObject* target) {
	if (!isAttackableBy(target))
		return false;

	uint32 targetFaction = target->getFaction();

	if (host->getFaction() != 0 && targetFaction != 0) {
		PlayerObject* ghost = target->getPlayerObject();

		if (ghost == NULL && (targetFaction != host->getFaction()))
			return true;
		else if (ghost != NULL && (targetFaction != host->getFaction()) && ghost->getFactionStatus() != FactionStatus::ONLEAVE)
			return true;
	}

	if (host->getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE)
		return true;

	return false;
}

void AiActorImplementation::setNextPosition(PatrolPoint& point) {
	Locker _locker(&targetMutex);
	if (patrolPoints.size() == 0)
		patrolPoints.add(point);
	else
		patrolPoints.setElementAt(0, point);
}

void AiActorImplementation::addPatrolPoint(PatrolPoint& point) {
	Locker _locker(&targetMutex);
	patrolPoints.add(point);
}

Vector<ManagedReference<WeaponObject*> > AiActorImplementation::getWeapons() {
	return weapons;
}

Time AiActorImplementation::getLastDamageReceived() {
	return lastDamageReceived;
}

