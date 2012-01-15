/*
 * AiAgentImplementation.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include "AiAgent.h"

#include "events/AiThinkEvent.h"
#include "events/AiMoveEvent.h"
#include "events/AiWaitEvent.h"
#include "events/AiAwarenessEvent.h"
#include "events/RespawnCreatureTask.h"
#include "events/DespawnCreatureOnPlayerDissappear.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/conversation/ConversationManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/mobile/CreatureTemplate.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/object/StringList.h"
#include "server/zone/packets/object/NpcConversationMessage.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/object/StopNpcConversation.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "PatrolPoint.h"
#include "AiObserver.h"
#include "CreatureSetDefenderTask.h"
#include "server/zone/templates/appearance/PortalLayout.h"
#include "server/zone/templates/appearance/FloorMesh.h"
#include "server/zone/objects/tangible/DamageMap.h"
#include "server/zone/packets/ui/CreateClientPathMessage.h"

//#define SHOW_WALK_PATH

void AiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);
}

void AiAgentImplementation::loadTemplateData(CreatureTemplate* templateData) {
	npcTemplate = templateData;

	setPvpStatusBitmask(npcTemplate->getPvpBitmask());

	optionsBitmask = npcTemplate->getOptionsBitmask();
	//npcTemplate->getCreatureBitmask(); -- TODO: need to add a bitmask for AI (pack, herd, etc)
	level = npcTemplate->getLevel();

	if (weapons.size() == 0) {
		Vector<String> wepgroups = npcTemplate->getWeapons();
		for (int i = 0; i < wepgroups.size(); ++i) {
			Vector<String> weptemps = CreatureTemplateManager::instance()->getWeapons(wepgroups.get(i));

			for (int i = 0; i < weptemps.size(); ++i) {
				uint32 crc = weptemps.get(i).hashCode();

				ManagedReference<WeaponObject*> weao = dynamic_cast<WeaponObject*>(server->getZoneServer()->createObject(crc, 0));
				weao->setMinDamage((weao->getMinDamage() / 2) + npcTemplate->getDamageMin());
				weao->setMaxDamage((weao->getMaxDamage() / 2) + npcTemplate->getDamageMax());
				weapons.add(weao);

				if (i == 0)
					transferObject(weao, 4, false);
			}
		}

		// add the default weapon for creatures
		if (isCreature()) {
			weapons.add(getWeapon());
		}
	}

	// set the damage of the default weapon
	getWeapon()->setMinDamage(npcTemplate->getDamageMin());
	getWeapon()->setMaxDamage(npcTemplate->getDamageMax());

	int ham;
	baseHAM.removeAll();
	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) {
			ham = System::random(npcTemplate->getBaseHAMmax() - npcTemplate->getBaseHAM()) + npcTemplate->getBaseHAM();
			baseHAM.add(ham);
		} else
			baseHAM.add(ham/100);
	}

	hamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		hamList.add(baseHAM.get(i));
	}

	maxHamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		maxHamList.add(baseHAM.get(i));
	}

	objectName = npcTemplate->getObjectName();

	String currentLogName = getLoggingName();

	if (!currentLogName.contains(npcTemplate->getTemplateName())) {
		StringBuffer logName;
		logName << getLoggingName() << "[" << npcTemplate->getTemplateName() << "]";

		setLoggingName(logName.toString());
	}
}

void AiAgentImplementation::initializeTransientMembers() {
	CreatureObjectImplementation::initializeTransientMembers();

	npcTemplate = NULL;
}

void AiAgentImplementation::doRecovery() {
	if (isDead() || getZone() == NULL)
		return;

	activateHAMRegeneration();
	activateStateRecovery();
	activatePostureRecovery();

	if (damageOverTimeList.hasDot() && damageOverTimeList.isNextTickPast()) {
		damageOverTimeList.activateDots(_this);
	}

	CreatureObject* target = damageMap->getHighestThreatCreature();

	if (target != NULL && !defenderList.contains(target) && !target->isDead())
		addDefender(target);

	if (target == NULL && defenderList.size() > 0) {
		for (int i = 0; i < defenderList.size(); ++i) {
			SceneObject* tarObj = defenderList.get(i);

			if (tarObj->isCreatureObject()) {
				CreatureObject* targetCreature = cast<CreatureObject*>(tarObj);

				if (!targetCreature->isDead()) {
					target = targetCreature;

					break;
				}
			}
		}
	}

	if (!isInCombat() || defenderList.size() <= 0 || target == NULL) {
		tryRetreat();
		activateRecovery();
		return;
	}

	if (target != NULL && (!target->isInRange(_this, 128) || !target->isAttackableBy(_this))) {
		//Locker clocker(target, _this);
		CombatManager::instance()->forcePeace(_this); //calling this on target will cause a deadlock, needs to be called in a new task
		activateRecovery();
		return;
	}

	if (commandQueue->size() > 5) {
		activateRecovery();
		return;
	}

	if (target != followObject)
		setDefender(target);

	selectWeapon();

	if (System::random(2) == 0 && npcTemplate != NULL && commandQueue->size() < 3) {
		// do special attack
		CreatureAttackMap* attackMap = npcTemplate->getAttacks();
		int attackNum = attackMap->getRandomAttackNumber();

		if (attackNum < 0 || attackNum >= attackMap->size()) {
			enqueueCommand(String("defaultattack").hashCode(), 0, target->getObjectID(), "");
		} else {
			String args = attackMap->getArguments(attackNum);

			if (!validateStateAttack(target, args)) {
				// do default attack
				enqueueCommand(String("defaultattack").hashCode(), 0, target->getObjectID(), "");
			} else {
				// queue special attack
				unsigned int actionCRC = attackMap->getCommand(attackNum).hashCode();
				enqueueCommand(actionCRC, 0, target->getObjectID(), args);

				if (System::random(4) == 0) {
					// queue second special attack (rudimentary combo)
					int secondAttackNum = attackMap->getRandomAttackNumber();
					args = attackMap->getArguments(secondAttackNum);

					if (validateStateAttack(target, args) && secondAttackNum != attackNum) {
						actionCRC = attackMap->getCommand(attackNum).hashCode();
						enqueueCommand(actionCRC, 0, target->getObjectID(), args);
					}
				}
			}
		}
	} else
		enqueueCommand(String("defaultattack").hashCode(), 0, target->getObjectID(), "");

	activateRecovery();
}

int AiAgentImplementation::notifyAttack(Observable* observable) {
	// TODO: add reaction attacks
	return 0;
}

int AiAgentImplementation::notifyCallForHelp(Observable* observable, ManagedObject* arg1) {
	// TODO: add aggroing
	return 0;
}

int AiAgentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (isDead()) {
		switch (selectedID) {
		case 35:
			player->executeObjectControllerAction(String("loot").hashCode(), getObjectID(), "");

			return 0;
		case 36:
			getZoneServer()->getPlayerManager()->lootAll(player, _this);

			return 0;
		}
	}

	return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void AiAgentImplementation::selectWeapon() {
	float dist = 5.f;

	if (followObject != NULL)
		dist = getDistanceTo(followObject.get());

	float diff = 1024.f;
	WeaponObject* finalWeap = getWeapon();

	for (int i = 0; i < weapons.size(); ++i) {
		WeaponObject* weap = weapons.get(i);
		float range = abs(weap->getIdealRange() - dist);
		if (range < diff) {
			diff = range;
			finalWeap = weap;
		}
	}

	ManagedReference<WeaponObject*> currentWeapon = getWeapon();
	ManagedReference<WeaponObject*> defaultWeapon = dynamic_cast<WeaponObject*>(getSlottedObject("default_weapon"));

	if (currentWeapon != finalWeap) {
		if (currentWeapon != NULL && currentWeapon != defaultWeapon) {
			currentWeapon->destroyObjectFromWorld(false);

			info("removed weapon " + currentWeapon->getObjectName()->getDisplayedName(), true);
		}

		if (finalWeap != defaultWeapon) {

			info("selected weapon " + finalWeap->getObjectName()->getDisplayedName(), true);

			transferObject(finalWeap, 4, false);
			broadcastObject(finalWeap, false);
		}
	}

	//setWeapon(finalWeap, true);
}

bool AiAgentImplementation::validateStateAttack(CreatureObject* target, String& args) {
	StringTokenizer tokenizer(args);
	tokenizer.setDelimeter(";");

	while (tokenizer.hasMoreTokens()) {
		String singleArg;
		tokenizer.getStringToken(singleArg);

		if (singleArg.indexOf("Chance") != -1) {
			String stateName = singleArg.subString(0, args.indexOf("Chance"));
			uint64 state = CreatureState::instance()->getState(stateName);
			if (target->hasState(state) || (stateName == "postureDown" && target->isProne()) || (stateName == "knockdown" && target->isKnockedDown()) || (stateName == "postureUp" && target->isStanding())) {
				return false;

			}
		}
	}

	return true;
}

void AiAgentImplementation::setDespawnOnNoPlayerInRange(bool val) {
	if (despawnOnNoPlayerInRange == val)
		return;

	despawnOnNoPlayerInRange = val;

	if (val && numberOfPlayersInRange <= 0) {
		if (despawnEvent == NULL) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(_this);
		}

		if (!despawnEvent->isScheduled())
			despawnEvent->schedule(30000);
	}
}

bool AiAgentImplementation::tryRetreat() {
	try {
		if (homeLocation.getPositionX() == 0 && homeLocation.getPositionY() == 0 && homeLocation.getPositionZ() == 0)
			return false;

		if (lastSuccessfulCombatAction.miliDifference() <= 30000) {
			return false;
		} else if (homeLocation.isInRange(_this, 100))
			return false;

		Locker locker(&targetMutex);

		setOblivious();

		showFlyText("npc_reaction/flytext", "afraid", 0xFF, 0, 0);

		homeLocation.setReached(false);

		damageMap->removeAll();

		patrolPoints.removeAll();
		patrolPoints.add(homeLocation);

		CombatManager::instance()->forcePeace(_this);

		activateMovementEvent();
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	return true;
}

void AiAgentImplementation::setDefender(SceneObject* defender) {
	CreatureObjectImplementation::setDefender(defender);

	Reference<CreatureSetDefenderTask*> task;
	ManagedReference<AiObserver*> observer = NULL;

	if (aiObserverMap.size() == 0) {
		observer = new AiObserver(_this);
		ObjectManager::instance()->persistObject(observer, 1, "aiobservers");
		aiObserverMap.put(observer);
	} else {
		observer = aiObserverMap.get(0);

		task = new CreatureSetDefenderTask(_this, defender, observer, true);

		/*for (int i = 0; i < defenderList.size(); ++i)
			defenderList.get(i)->dropObserver(ObserverEventType::SPECIALATTACK, observer);*/
	}

	/*if (observer != NULL)
			defender->registerObserver(ObserverEventType::SPECIALATTACK, observer);*/


	if (task == NULL)
		task = new CreatureSetDefenderTask(_this, defender, observer, false);

	Core::getTaskManager()->executeTask(task);

	setFollowObject(defender);

	activateRecovery();
}

void AiAgentImplementation::addDefender(SceneObject* defender) {
	if (defenderList.size() == 0)
		showFlyText("npc_reaction/flytext", "threaten", 0xFF, 0, 0);

	CreatureObjectImplementation::addDefender(defender);

	activateRecovery();
}

void AiAgentImplementation::removeDefender(SceneObject* defender) {
	CreatureObjectImplementation::removeDefender(defender);

	if (defender != NULL) {
		if (defender->isCreatureObject())
			damageMap->dropDamage(cast<CreatureObject*>(defender));

		if (aiObserverMap.size() > 0)
			defender->dropObserver(ObserverEventType::SPECIALATTACK, aiObserverMap.get(0));
	}

	if (followObject == defender) {
		CreatureObject* target = damageMap->getHighestThreatCreature();

		if (target == NULL && defenderList.size() > 0) {
			SceneObject* tarObj = defenderList.get(0);
			if (tarObj->isCreatureObject())
				target = cast<CreatureObject*>(tarObj);
		}

		if (target == NULL) {
			setOblivious();
		} else  {
			setDefender(target);
		}
	}

	activateRecovery();
}

/**
 * Cleares the combat state
 * @pre { this object is locked }
 * @post { this object is locked, this object is not in a combat state }
 * @param clearDefenders if true the defender vector willl be emptied
 */
void AiAgentImplementation::clearCombatState(bool clearDefenders) {
	CreatureObjectImplementation::clearCombatState(clearDefenders);

	damageMap->removeAll();

	setOblivious();
}

void AiAgentImplementation::notifyInsert(QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>( entry);

	if (scno == _this)
		return;

	if (scno->isPlayerCreature())
		++numberOfPlayersInRange;
}

void AiAgentImplementation::clearDespawnEvent() {
	despawnEvent = NULL;
}

void AiAgentImplementation::respawn(Zone* zone, int level) {
	if (getZone() != NULL)
		return;

	setLevel(level);

	initializePosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());

	SceneObject* cell = homeLocation.getCell();

	Locker zoneLocker(zone);

	if (cell != NULL)
		cell->transferObject(_this, -1);
	else
		zone->transferObject(_this, -1, true);
}

void AiAgentImplementation::notifyDespawn(Zone* zone) {
	if (moveEvent != NULL) {
		moveEvent->clearCreatureObject();
		moveEvent = NULL;
	}

	if (npcTemplate == NULL)
		return;

	loadTemplateData(templateObject);
	loadTemplateData(npcTemplate);
	stateBitmask = 0;
	posture = CreaturePosture::UPRIGHT;
	shockWounds = 0;
	damageMap->removeAll();

	setTargetObject(NULL);
	setFollowObject(NULL);

	//_this->printReferenceHolders();

	//printf("%d ref count\n", _this->getReferenceCount());

	if (respawnTimer == 0) {
		//zone->getCreatureManager()->addToReservePool(_this);
		return;
	}

	Reference<Task*> task = new RespawnCreatureTask(_this, zone, level);
	task->schedule(respawnTimer * 1000);
}

void AiAgentImplementation::scheduleDespawn(int timeToDespawn) {
	if (getPendingTask("despawn") != NULL)
		return;

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(_this);
	addPendingTask("despawn", despawn, timeToDespawn * 1000);
}

void AiAgentImplementation::notifyDissapear(QuadTreeEntry* entry) {
	SceneObject* scno = cast<SceneObject*>( entry);

	if (scno == _this)
		return;

	if (entry == followObject.get())
		setFollowObject(NULL);

	if (scno->isPlayerCreature()) {
		if ((--numberOfPlayersInRange <= 0)  && (despawnEvent == NULL)) {
			/*despawnEvent = new DespawnCreatureOnPlayerDissappear(_this);
			despawnEvent->schedule(30000);*/
		}
	}
}

void AiAgentImplementation::activateAwarenessEvent(CreatureObject *target) {
	if (awarenessEvent == NULL) {
		awarenessEvent = new AiAwarenessEvent(_this, target);

		awarenessEvent->schedule(1000);
	}

	if (!awarenessEvent->isScheduled()) {
		awarenessEvent->setTarget(target);
		awarenessEvent->schedule(1000);
	}
}

void AiAgentImplementation::activateRecovery() {
	if (thinkEvent == NULL) {
		thinkEvent = new AiThinkEvent(_this);

		thinkEvent->schedule(2000);
	}

	if (!thinkEvent->isScheduled())
		thinkEvent->schedule(2000);
}

void AiAgentImplementation::activatePostureRecovery() {
	if (isProne() || isKnockedDown() || isKneeling())
		executeObjectControllerAction(0xA8A25C79); // stand
}

void AiAgentImplementation::updateCurrentPosition(PatrolPoint* pos) {
	PatrolPoint* nextPosition = pos;

	setPosition(nextPosition->getPositionX(), nextPosition->getPositionZ(),
			nextPosition->getPositionY());

	SceneObject* cell = nextPosition->getCell();

	/*StringBuffer reachedPosition;
	reachedPosition << "(" << positionX << ", " << positionY << ")";
	info("reached " + reachedPosition.toString(), true);*/

	if (cell != NULL && cell->getParent() != NULL)
		updateZoneWithParent(cell, false, false);
	else
		updateZone(false, false);
}


void AiAgentImplementation::checkNewAngle() {
	if (followObject == NULL)
		return;

	faceObject(followObject);

	if (!nextStepPosition.isReached()) {
		broadcastNextPositionUpdate(&nextStepPosition);
	} else {
		++movementCounter;

		if (parent != NULL && getParent()->isCellObject())
			updateZoneWithParent(getParent(), true, true);
		else
			updateZone(true, true);
	}
}

bool AiAgentImplementation::findNextPosition(float maxDistance, WorldCoordinates* nextPosition) {
	Locker locker(&targetMutex);

	Vector3 thisWorldPos = getWorldPosition();

	ManagedReference<SceneObject*> strongFollow = followObject.get();

	float newSpeed = runSpeed;
	if (followObject == NULL && !isFleeing() && !isRetreating()) // TODO: think about implementing a more generic "walk, don't run" criterion
		newSpeed = walkSpeed;

	float updateTicks = float(UPDATEMOVEMENTINTERVAL) / 1000.f;
	currentSpeed = newSpeed;

	newSpeed *= updateTicks;

	float newSpeedSquared = newSpeed * newSpeed;
	float newPositionX = 0, newPositionZ = 0, newPositionY = 0;
	PathFinderManager* pathFinder = PathFinderManager::instance();
	float maxDist = MIN(maxDistance * maxDistance, newSpeedSquared);

	bool found = false;
	float dist = 0;
	float dx = 0, dy = 0;
	ManagedReference<SceneObject*> cellObject;

#ifdef SHOW_WALK_PATH
	CreateClientPathMessage* pathMessage = new CreateClientPathMessage();
	if (getParent() == NULL) {
		pathMessage->addCoordinate(getPositionX(), getZone()->getHeight(getPositionX(), getPositionY()), getPositionY());
	} else {
		pathMessage->addCoordinate(getPositionX(), getPositionZ(), getPositionY());
	}
#endif

	while (!found && patrolPoints.size() != 0) {
		PatrolPoint* targetPosition = &patrolPoints.get(0);

		Vector<WorldCoordinates>* path = pathFinder->findPath(_this.get(), targetPosition->getCoordinates());

		if (path == NULL) {
			patrolPoints.remove(0);

			continue;
		}

		WorldCoordinates* oldCoord = NULL;
		float pathDistance = 0;

		bool remove = true;

		for (int i = 1; i < path->size() && !found; ++i) { // i = 0 is our position
			WorldCoordinates* coord = &path->get(i);

			Vector3 nextWorldPos = coord->getWorldPosition();

#ifdef SHOW_WALK_PATH
			if (coord->getCell() == NULL)
				pathMessage->addCoordinate(nextWorldPos.getX(), getZone()->getHeight(nextWorldPos.getX(), nextWorldPos.getY()), nextWorldPos.getY());
			else
				pathMessage->addCoordinate(nextWorldPos.getX(), nextWorldPos.getZ(), nextWorldPos.getY());
#endif

			if (oldCoord == NULL) {
				pathDistance += nextWorldPos.squaredDistanceTo(thisWorldPos);
				oldCoord = &path->get(0);
			} else {
				pathDistance += oldCoord->getWorldPosition().squaredDistanceTo(nextWorldPos);
			}

			if (i == path->size() - 1 || pathDistance >= maxDist || coord->getCell() != parent) { //last waypoint
				cellObject = coord->getCell();

				//TODO: calculate height
				Vector3 noHeightWorldPos(thisWorldPos.getX(), thisWorldPos.getY(), 0);
				Vector3 noHeightNextWorldPos(nextWorldPos.getX(), nextWorldPos.getY(), 0);
				dist = noHeightNextWorldPos.squaredDistanceTo(noHeightWorldPos);

				*nextPosition = *coord;
				found = true;

				if ((dist <= maxDistance * maxDistance && cellObject == parent)) {
					if (i == path->size() - 1) {
						patrolPoints.remove(0);
						remove = false;
					}

					found = false;
				} else {
					//lets convert source and target coordinates to model or world space
					Vector3 oldCoordinates = oldCoord->getPoint();

					if (coord->getCell() != NULL) { //target coord in cell
						if (oldCoord->getCell() == NULL)  // convert old coord to model space
							oldCoordinates = PathFinderManager::transformToModelSpace(oldCoord->getPoint(), coord->getCell()->getParent());

					} else { // target coord in world
						oldCoordinates = oldCoord->getWorldPosition();
					}

					if (pathDistance > maxDist) {
						Vector3 oldWorldCoord = oldCoord->getWorldPosition();

						dist = oldWorldCoord.squaredDistanceTo(nextWorldPos);

						float distanceToTravel = dist - (pathDistance - maxDist);

						if (distanceToTravel <= 0) {
							newPositionX = nextPosition->getX();
							newPositionY = nextPosition->getY();
						} else {
							float rest = Math::sqrt(distanceToTravel);

							dist = Math::sqrt(dist);

							if (dist != 0 && !isnan(dist)) {
								dx = nextPosition->getX() - oldCoordinates.getX();
								dy = nextPosition->getY() - oldCoordinates.getY();

								newPositionX = oldCoordinates.getX() + (rest * (dx / dist));// (newSpeed * (dx / dist));
								newPositionY = oldCoordinates.getY() + (rest * (dy / dist)); //(newSpeed * (dy / dist));
							} else {
								newPositionX = nextPosition->getX();
								newPositionY = nextPosition->getY();
							}
						}

						if (nextPosition->getCell() == NULL) {
							newPositionZ = getZone()->getHeight(newPositionX, newPositionY);
							//newPositionZ = nextPosition.getZ();
						} else {
							newPositionZ = nextPosition->getZ();
						}
					} else {
						//info("setting nextPosition point", true);
						newPositionX = nextPosition->getX();
						newPositionY = nextPosition->getY();
						newPositionZ = nextPosition->getZ();
					}
				}
			}

			oldCoord = coord;
		}

		if (!found && remove) {
			patrolPoints.remove(0);
		}

		delete path;
	}

#ifdef SHOW_WALK_PATH
	broadcastMessage(pathMessage, false);
#endif

	nextPosition->setX(newPositionX);
	nextPosition->setY(newPositionY);
	nextPosition->setZ(newPositionZ);
	nextPosition->setCell(cellObject);

	return found;
}

void AiAgentImplementation::doMovement() {
	//info("doMovement", true);
	if (isDead() || (getZone() == NULL)) {
		setFollowObject(NULL);
		return;
	}

	ManagedReference<SceneObject*> storage = followObject.get();

	if (currentSpeed != 0) {
		updateCurrentPosition(&nextStepPosition);
		nextStepPosition.setReached(true);
	}

	float maxDistance = 5;

	ManagedReference<SceneObject*> follow = followObject.get();

	if (follow != NULL) {
		// drop everything and go after the target, this will also chase the target without having to reach them to change direction
		//patrolPoints.removeAll();

		//Locker locker(&targetMutex);

		switch (followState) {
		case AiAgent::OBLIVIOUS:
			break;
		case AiAgent::WATCHING:
			setNextPosition(getPositionX(), getPositionZ(), getPositionY(), getParent());
			setDirection(atan2(follow->getPositionX() - getPositionX(), follow->getPositionX() - getPositionX()));
			checkNewAngle();
			if (patrolPoints.size() > 0)
				updateCurrentPosition(&patrolPoints.get(0));
			break;
		case AiAgent::STALKING:
			setNextPosition(follow->getPositionX(), follow->getPositionZ(), follow->getPositionY(), follow->getParent());
			maxDistance = 25;
			break;
		case AiAgent::FOLLOWING: {

			//we might get out of the floor
			/*float newX = followObject->getPositionX() + (-3 + System::random(6));
			float newY = followObject->getPositionY() + (-3 + System::random(6));*/

			setNextPosition(follow->getPositionX(), follow->getPositionZ(), follow->getPositionY(), follow->getParent());
			// stop in weapons range
			if (weapon != NULL )
				maxDistance = weapon->getIdealRange();

			if (follow != NULL && !CollisionManager::checkLineOfSight(_this, follow)) {
				maxDistance = 0.5;
			}

			break;
		}
		default:
			setOblivious();
			break;
		}
	}

	if (isRetreating() || isFleeing())
		maxDistance = 0.5;

	WorldCoordinates nextPosition;

	bool found = findNextPosition(maxDistance, &nextPosition);

	if (!found) {
		currentSpeed = 0;
		//info("not found in doMovement", true);

		if (isRetreating())
			homeLocation.setReached(true);

		if (isFleeing())
			fleeing = false;

		if (followObject != NULL)
			activateMovementEvent();
		else
			notifyObservers(ObserverEventType::DESTINATIONREACHED);

		return;
	} else {
	/*	if (getLoggingName().contains("bandit")) {
			StringBuffer msg;
			msg << "finding next position with maxDistance " << maxDistance << " next pos:x" << nextPosition.getX() << " y:" << nextPosition.getY();
			//info( + String::valueOf(maxDistance), true);
			info(msg.toString(), true);
		}*/
	}

	if (!isStanding()) {
		activateMovementEvent();
		return;
	}

	nextStepPosition.setPosition(nextPosition.getX(), nextPosition.getZ(), nextPosition.getY());
	nextStepPosition.setCell(nextPosition.getCell());

	float directionangle = atan2(nextPosition.getX() - getPositionX(), nextPosition.getY() - getPositionY());

	if (directionangle < 0)
		directionangle = 2 * M_PI + directionangle;

	direction.setHeadingDirection(directionangle);

	nextStepPosition.setReached(false);

	broadcastNextPositionUpdate(&nextStepPosition);

	activateMovementEvent();
}

void AiAgentImplementation::activateMovementEvent() {
	if (getZone() == NULL)
		return;

	if (moveEvent == NULL) {
		moveEvent = new AiMoveEvent(_this);

		moveEvent->schedule(UPDATEMOVEMENTINTERVAL);
	}

	if (!moveEvent->isScheduled())
		moveEvent->schedule(UPDATEMOVEMENTINTERVAL);
}

void AiAgentImplementation::activateWaitEvent() {
	if (getZone() == NULL)
			return;

	if (waitEvent == NULL) {
		waitEvent = new AiWaitEvent(_this);

		waitEvent->schedule(UPDATEMOVEMENTINTERVAL * 10);
	}

	if (!waitEvent->isScheduled())
		waitEvent->schedule(UPDATEMOVEMENTINTERVAL * 10);
}

void AiAgentImplementation::setNextPosition(float x, float z, float y, SceneObject* cell) {
	Locker locker(&targetMutex);

	PatrolPoint point(x, z, y, cell);

	if (patrolPoints.size() == 0)
		patrolPoints.add(point);
	else
		patrolPoints.setElementAt(0, point);
}

void AiAgentImplementation::broadcastNextPositionUpdate(PatrolPoint* point) {
	BasePacket* msg = NULL;
	++movementCounter;

	if (point == NULL) {
		if (parent != NULL)
			msg = new UpdateTransformWithParentMessage(_this);
		else
			msg = new UpdateTransformMessage(_this);
	} else {
		if (point->getCell() != NULL)
			msg = new LightUpdateTransformWithParentMessage(_this, point->getPositionX(), point->getPositionZ(), point->getPositionY(), point->getCell()->getObjectID());
		else
			msg = new LightUpdateTransformMessage(_this, point->getPositionX(), point->getPositionZ(), point->getPositionY());
	}

	broadcastMessage(msg, false);
}

int AiAgentImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	if (getZone() != NULL) {
		CreatureManager* creatureManager = getZone()->getCreatureManager();

		creatureManager->notifyDestruction(attacker, _this, condition);
	}

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition);
}

int AiAgentImplementation::notifyConverseObservers(CreatureObject* converser) {
	notifyObservers(ObserverEventType::CONVERSE, converser);

	return 1;
}

int AiAgentImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	activateRecovery();

	if (attacker->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( attacker);

		if (damage > 0) {
			damageMap->addDamage(player, damage);

			if (System::random(5) == 1) {
				setDefender(player);
			}
		}
	}

	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}


void AiAgentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {

	if (isDead()) {
		return;
	}

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


void AiAgentImplementation::sendConversationStartTo(SceneObject* player) {
	if (!player->isPlayerCreature())
		return;

	//Face player.
	faceObject(player);

	PatrolPoint current(coordinates.getPosition(), getParent());

	broadcastNextPositionUpdate(&current);

	CreatureObject* playerCreature = cast<CreatureObject*>( player);
	StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
	player->sendMessage(conv);

	SortedVector<ManagedReference<Observer*> >* observers = getObservers(ObserverEventType::STARTCONVERSATION);

	if (observers != NULL) {
		for (int i = 0;  i < observers->size(); ++i) {
			if (dynamic_cast<ConversationObserver*>(observers->get(i).get()) != NULL)
				return;
		}
	}

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

bool AiAgentImplementation::isAggressiveTo(CreatureObject* target) {
	if (!isAttackableBy(target))
		return false;

	/// Check masked scent
	if (target->getStateBitmask() & CreatureState::MASKSCENT) {
		int camoSkill = target->getSkillMod("mask_scent");
		int myLevel = getLevel();

		if(myLevel > camoSkill) {

		}

	}

	if (getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE)
		return true;

	return false;
}

void AiAgentImplementation::sendDefaultConversationTo(SceneObject* player) {
	/*if (!player->isPlayerCreature())
		return;

	faceObject(player);

	PatrolPoint current(coordinates.getPosition(), getParent());

	broadcastNextPositionUpdate(&current);

	CreatureObject* playerCreature = cast<CreatureObject*>( player);

	ManagedReference<PlayerObject*> ghost = playerCreature->getPlayerObject();

	if (npcTemplate != NULL) {
		uint32 convoTemplate = npcTemplate->getConversationTemplate();

		Reference<ConversationTemplate*> convo = CreatureTemplateManager::instance()->getConversationTemplate(convoTemplate);

		if (convo != NULL) {
			Reference<ConversationScreen*> initialScreen = convo->getInitialScreen();

			if (initialScreen == NULL)
				return;

			//ghost->setLastNpcConvMessStr(root->getID());

			StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
			player->sendMessage(conv);

			initialScreen->sendTo(playerCreature);

			return;
		}
	}

	//player->setLastNpcConvStr(("npc_" + getFu().toString()));
	ghost->setLastNpcConvMessStr("0,init");

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
	player->sendMessage(conv);

	String responseFile, responseAttitude;

	if (responseFile == "") {
		if (isImperial()) {
			responseFile = "npc_reaction/stormtrooper";
		} else if (isRebel()) {
			responseFile = "npc_reaction/military";
		} else {
			short file = System::random(2);
			if (file == 0)
				responseFile = "npc_reaction/fancy";
			else if (file == 1)
				responseFile = "npc_reaction/slang";
			else
				responseFile = "npc_reaction/townperson";
		}
	}

	if (responseAttitude == "") {
		short type = System::random(2);
		if (type == 0)
			responseAttitude = "mean";
		else if (type == 1)
			responseAttitude = "mid";
		else
			responseAttitude = "nice";
	}

	StringBuffer convoChoice;
	convoChoice << "hi_" <<  responseAttitude << "_" << (System::random(15) + 1);

	//TODO: Revisit NPC Conversation
	//NpcConversationMessage* initial = new NpcConversationMessage(
	//		playerCreature, responseFile, convoChoice.toString());
	//player->sendMessage(initial);

	// Parse and send the options:
	//StringList* slist = new StringList(playerCreature);

	//String test = "I'm looking for work";
	//slist->insertOption(test);

	//player->sendMessage(slist);

	//playerCreature->setLastNpcConvMessStr("chitchat");*/
}

void AiAgentImplementation::selectConversationOption(int option, SceneObject* obj) {
	/*if (!obj->isCreatureObject())
		return;

	CreatureObject* player = cast<CreatureObject*>( obj);

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	String chk = ghost->getLastNpcConvMessStr();

	if (npcTemplate != NULL) {
			uint32 convoTemplate = npcTemplate->getConversationTemplate(); //TODO: Consider storing reference to the convo on the template?

			Reference<ConversationTemplate*> convo = CreatureTemplateManager::instance()->getConversationTemplate(convoTemplate);

			if (convo != NULL) {
				Reference<ConversationScreen*> lastScreen = convo->getScreen(chk);

				if (lastScreen == NULL)
					lastScreen = convo->getInitialScreen();

				Reference<ConversationOption*> convoOption = lastScreen->getOption(option);

				if (convoOption == NULL || !convoOption->isLinked())
					return; //Stop Conversation if no option exists or this option isn't linked to another option.

				Reference<ConversationScreen*> nextScreen = convo->getScreen(convoOption->getLinkedScreenID());

				if (nextScreen == NULL)
					return; //Couldn't find the linked screen in this conversation template.

				nextScreen->sendTo(player);

				return;
			}
	}

	if (chk != "chitchat") {
		return;
	}

	UnicodeString saying = "";
	switch(System::random(5)) {
	case 0:
		saying = "Why the heck would you want to work when welfare is free.";
		break;
	case 1:
		saying = "Pfft, work in this economy?  I'm waiting for the government to bail me out.";
		break;
	case 2:
		saying = "Check the missions terminals, they are overflowing with work.";
		break;
	case 3:
		saying = "Huh, work?  Whats that?";
		break;
	case 4:
		saying = "Did you check the mission terminals?";
		break;
	case 5:
		saying = "Me too.";
		break;
	}

	NpcConversationMessage* response = new NpcConversationMessage(player, saying);
	player->sendMessage(response);

	// Parse and send the options:
	StringList* slist = new StringList(player);
	player->sendMessage(slist);*/
}
