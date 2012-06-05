/*
 * AiStateComponent.cpp
 *
 *  Created on: May 24, 2012
 *      Author: da
 */

/*
 * AiStateComponent.h
 *
 *  Created on: May 6, 2012
 *      Author: da
 */

#include "engine/engine.h"
#include "server/zone/objects/scene/components/SceneObjectComponent.h"

#include "server/zone/objects/creature/ai/AiActor.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/scene/WorldCoordinates.h"
#include "server/zone/objects/creature/PatrolPointsVector.h"
#include "server/zone/objects/creature/PatrolPoint.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "engine/core/ManagedReference.h"
#include "system/lang/ref/Reference.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"

void AiStateComponent::notifyDespawn(AiActor* actor, Zone* zone) {
	for (int i = 0; i < actor->getMovementMarkersSize(); ++i)
		actor->getMovementMarker(i)->destroyObjectFromWorld(false);

	if (actor->getCreatureTemplate() == NULL)
		return;

	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return;

	int oldLevel = host->getLevel();

	actor->loadTemplateData(host->getObjectTemplate());
	actor->loadTemplateData(actor->getCreatureTemplate());

	if (oldLevel != host->getLevel())
		actor->setLevel(host->getLevel());

	host->clearState(0xFFFFFFFF, false);
	host->setPosture(CreaturePosture::UPRIGHT, false);
	host->setShockWounds(0, false);
	host->getThreatMap()->removeAll();

	//Delete all loot out of inventory
	ManagedReference<SceneObject*> inventory = host->getSlottedObject("inventory");

	if (inventory != NULL) {
		while (inventory->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = inventory->getContainerObject(0);
			inventory->removeFromContainerObjects(0);
			obj->destroyObjectFromWorld(false);
			obj->destroyObjectFromDatabase(true);
		}
	}

	actor->setTargetObject(NULL);
	actor->setFollowObject(NULL);

	if (actor->getRespawnTimer() == 0) {
		//zone->getCreatureManager()->addToReservePool(_this);
		return;
	}

	/*
	 * TODO: redo RespawnCreatureTask to take AiActor
		Reference<Task*> task = new RespawnCreatureTask(_this, zone, level);
		task->schedule(respawnTimer * 1000);
	 */
}

/*
 * host = creature doing moving
 * maxDistance = maxDistance to stay from target
 * speed = speed to travel
 * patrolPoints = queued points in path
 * nextPosition = calculated next position
 */
bool AiStateComponent::findNextPosition(Observable* obs, float maxDistance, float speed, PatrolPointsVector* patrolPoints, WorldCoordinates* nextPosition) {
	ManagedReference<AiActor*> actor = cast<AiActor*>(obs);
	if (actor == NULL)
		return true;

	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return true;

	float newSpeed = speed;

	Vector3 thisWorldPos = host->getWorldPosition();

	if(host->hasState(CreatureState::IMMOBILIZED))
		newSpeed = newSpeed / 2.f;

	if(host->hasState(CreatureState::FROZEN))
		newSpeed = 0.01f;

	float updateTicks = float(AiActor::UPDATEMOVEMENTINTERVAL) / 1000.f;
	host->setCurrentSpeed(newSpeed);

	newSpeed *= updateTicks;

	float newPositionX = 0, newPositionZ = 0, newPositionY = 0;
	float maxDist = newSpeed;

	bool found = false;
	float dist = 0,dx = 0, dy = 0;
	ManagedReference<SceneObject*> cellObject;

#ifdef SHOW_WALK_PATH
	CreateClientPathMessage* pathMessage = new CreateClientPathMessage();
	if (host->getParent() == NULL) {
		pathMessage->addCoordinate(host->getPositionX(), host->getZone()->getHeight(host->getPositionX(), host->getPositionY()), host->getPositionY());
	} else {
		pathMessage->addCoordinate(host->getPositionX(), host->getPositionZ(), host->getPositionY());
	}
#endif

	while (!found && patrolPoints->size() != 0) {
		PatrolPoint targetPosition = patrolPoints->get(0);

		WorldCoordinates hostCoords(host);
		Vector<WorldCoordinates>* path = PathFinderManager::instance()->findPath(hostCoords, targetPosition.getCoordinates());

		if (path == NULL) {
			patrolPoints->remove(0);
			continue;
		}

		float targetDistance = targetPosition.getWorldPosition().distanceTo(host->getWorldPosition());

		if (targetDistance > maxDistance)
			maxDist = MIN(newSpeed, targetDistance - maxDistance);
		else {
			delete path;
			return false;
		}

		WorldCoordinates* oldCoord = NULL;
		float pathDistance = 0;
		bool remove = true;

		for (int i = 1; i < path->size() && !found; ++i) { // i = 0 is our position
			WorldCoordinates* coord = &path->get(i);

			Vector3 nextWorldPos = coord->getWorldPosition();

#ifdef SHOW_WALK_PATH
			if (coord->getCell() == NULL)
				pathMessage->addCoordinate(nextWorldPos.getX(), host->getZone()->getHeight(nextWorldPos.getX(), nextWorldPos.getY()), nextWorldPos.getY());
			else
				pathMessage->addCoordinate(nextWorldPos.getX(), nextWorldPos.getZ(), nextWorldPos.getY());
#endif

			if (oldCoord == NULL) {
				oldCoord = &path->get(0);
			}

			pathDistance += oldCoord->getWorldPosition().distanceTo(nextWorldPos);

			if (i == path->size() - 1 || pathDistance >= maxDist || coord->getCell() != host->getParent()) { //last waypoint
				cellObject = coord->getCell();

				//TODO: calculate height
				Vector3 noHeightWorldPos(thisWorldPos.getX(), thisWorldPos.getY(), 0);
				Vector3 noHeightNextWorldPos(nextWorldPos.getX(), nextWorldPos.getY(), 0);
				dist = noHeightNextWorldPos.distanceTo(noHeightWorldPos);

				*nextPosition = *coord;
				found = true;

				if ((dist <= maxDistance && cellObject == host->getParent())) {
					if (i == path->size() - 1) {
						patrolPoints->remove(0);
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

						dist = oldWorldCoord.distanceTo(nextWorldPos);

						float distanceToTravel = dist - (pathDistance - maxDist);

						if (distanceToTravel <= 0) {
							newPositionX = nextPosition->getX();
							newPositionY = nextPosition->getY();
						} else {
							//float rest = Math::sqrt(distanceToTravel);

							float rest = distanceToTravel;

							//dist = Math::sqrt(dist);

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
							Zone* zone = host->getZone();

							if (zone != NULL)
								newPositionZ = zone->getHeight(newPositionX, newPositionY);
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
#ifdef SHOW_NEXT_POSITION
					if (actor->isShowNextPosition()) {
						for (int i = 0; i < actor->getMovementMarkersSize(); ++i)
							actor->getMovementMarker(i)->destroyObjectFromWorld(false);

						actor->dropAllMovemementMarkers();

						SceneObject* movementMarker = host->getZoneServer()->createObject(String("object/path_waypoint/path_waypoint.iff").hashCode(), 0);

						movementMarker->initializePosition(newPositionX, newPositionZ, newPositionY);
						StringBuffer msg;
						msg << "Next Position: path distance: " << pathDistance << " maxDist:" << maxDist;
						movementMarker->setCustomObjectName(msg.toString(), false);

						if (cellObject != NULL) {
							cellObject->transferObject(movementMarker, -1, true);
						} else {
							getZone()->transferObject(movementMarker, -1, false);
						}

						actor->addMovementMarker(movementMarker);

						for (int i = 0; i < path->size(); ++i) {
							WorldCoordinates* coord = &path->get(i);
							SceneObject* coordCell = coord->getCell();

							movementMarker = host->getZoneServer()->createObject(String("object/path_waypoint/path_waypoint.iff").hashCode(), 0);
							movementMarker->initializePosition(coord->getPoint().getX(), coord->getPoint().getZ(), coord->getPoint().getY());

							if (coordCell != NULL) {
								coordCell->transferObject(movementMarker, -1, true);
							} else {
								getZone()->transferObject(movementMarker, -1, false);
							}

							actor->addMovementMarker(movementMarker);
						}
					}
#endif
				}
			}

			oldCoord = coord;
		}

		if (!found && remove) {
			patrolPoints->remove(0);
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

void AiStateComponent::setNextPosition(AiActor* actor, float x, float z, float y, SceneObject* cell) {
	PatrolPoint point(x, z, y, cell);
	actor->setNextPosition(point);
}

void AiStateComponent::updateCurrentPosition(CreatureObject* host, PatrolPoint* pos) {
	host->setPosition(pos->getPositionX(), pos->getPositionZ(), pos->getPositionY());

	if (host->getZone() == NULL)
		return;

	SceneObject* cell = pos->getCell();
	if (cell != NULL && cell->getParent() != NULL)
		host->updateZoneWithParent(cell, false, false);
	else
		host->updateZone(false, false);
}

void AiStateComponent::broadcastNextPositionUpdate(CreatureObject* host, PatrolPoint* point) {
	BasePacket* msg = NULL;
	host->incrementMovementCounter();

	if (point == NULL) {
		if (host->getParent() != NULL)
			msg = new UpdateTransformWithParentMessage(host);
		else
			msg = new UpdateTransformMessage(host);
	} else {
		if (point->getCell() != NULL)
			msg = new LightUpdateTransformWithParentMessage(host, point->getPositionX(), point->getPositionZ(), point->getPositionY(), point->getCell()->getObjectID());
		else
			msg = new LightUpdateTransformMessage(host, point->getPositionX(), point->getPositionZ(), point->getPositionY());
	}

	host->broadcastMessage(msg, false);
}

void AiStateComponent::checkNewAngle(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return;

	if (actor->getFollowObject() == NULL)
		return;

	host->faceObject(actor->getFollowObject());

	PatrolPoint* nextStepPosition = actor->getNextStepPosition();

	if (!nextStepPosition->isReached()) {
		broadcastNextPositionUpdate(host, nextStepPosition);
	} else {
		host->incrementMovementCounter();

		if (host->getParent() != NULL && host->getParent()->isCellObject())
			host->updateZoneWithParent(host->getParent(), true, true);
		else
			host->updateZone(true, true);
	}
}

void AiStateComponent::sendConversationStartTo(CreatureObject* host, SceneObject* player) {
	//Face player.
	host->faceObject(player);

	PatrolPoint current(host->getPosition(), host->getParent());

	broadcastNextPositionUpdate(host, &current);

	CreatureObject* playerCreature = cast<CreatureObject*>(player);
	StartNpcConversation* conv = new StartNpcConversation(playerCreature, host->getObjectID(), "");
	player->sendMessage(conv);
}

void AiStateComponent::selectWeapon(AiActor* actor) {
	// TODO: this algorithm can be done better
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return;

	float dist = 5.f;

	if (actor->getFollowObject() != NULL)
		dist = host->getDistanceTo(actor->getFollowObject());

	float diff = 1024.f;
	ManagedReference<WeaponObject*> currentWeapon = host->getWeapon();
	ManagedReference<WeaponObject*> finalWeap = currentWeapon;
	Vector<ManagedReference<WeaponObject*> > weapons = actor->getWeapons();

	for (int i = 0; i < weapons.size(); ++i) {
		WeaponObject* weap = weapons.get(i);

		float range = abs(weap->getIdealRange() - dist);

		if (range < diff) {
			diff = range;
			finalWeap = weap;
		}
	}

	ManagedReference<WeaponObject*> defaultWeapon = dynamic_cast<WeaponObject*>(host->getSlottedObject("default_weapon"));

	// why is this here? defaultWeapon is in weapons
	if ((dist < 6) && (finalWeap->isRangedWeapon() || (finalWeap->isMeleeWeapon() && System::random(10) == 0))) {
		float range = fabs(defaultWeapon->getIdealRange() - dist);

		if (range < diff) {
			finalWeap = defaultWeapon;
		}
	}

	if (currentWeapon != finalWeap) {
		if (currentWeapon != NULL && currentWeapon != defaultWeapon) {
			currentWeapon->destroyObjectFromWorld(false);

			//info("removed weapon " + currentWeapon->getDisplayedName(), true);
		}

		if (finalWeap != defaultWeapon) {

			//info("selected weapon " + finalWeap->getDisplayedName(), true);

			host->transferObject(finalWeap, 4, false);
			host->broadcastObject(finalWeap, false);
		}
	}
}

bool AiStateComponent::validateStateAttack(CreatureObject* target, String& args) {
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

bool AiStateComponent::isScared(CreatureObject* host, SceneObject* followObject) {
	if (!followObject->isCreatureObject())
		return false;

	ManagedReference<CreatureObject*> followCreature = cast<CreatureObject*>(followObject);
	// disallow checking non-players for now
	if (!followCreature->isPlayerCreature())
		return false;

	// TODO: check ferocity vs some formula involving player combat diff + player speed towards mob
	return false;
}

uint16 AiStateComponent::onEnter(AiActor* actor) {
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	if (host->isDead())
		return AiActor::DEAD;

	if (host->isInCombat())
		return AiActor::ATTACKED;

	actor->activateMovementEvent();
	actor->activateRecovery();

	return AiActor::UNFINISHED;
}

uint16 AiStateComponent::tryRetreat(AiActor* actor) {
	return AiActor::NONE;
}

uint16 AiStateComponent::doRecovery(AiActor* actor) {
	return AiActor::NONE;
}

uint16 AiStateComponent::doAttack(AiActor* actor) {
	return AiActor::NONE;
}

uint16 AiStateComponent::doMovement(AiActor* actor) {
	//info("doMovement", true);
	ManagedReference<CreatureObject*> host = actor->getHost();
	if (host == NULL)
		return AiActor::NONE;

	float currentSpeed = host->getCurrentSpeed();
	PatrolPoint* nextStepPosition = actor->getNextStepPosition();
	if (currentSpeed != 0) {
		updateCurrentPosition(host, nextStepPosition);
		nextStepPosition->setReached(true);
	}

	if (host->isDead() || (host->getZone() == NULL))
		return AiActor::DEAD;

	actor->activateMovementEvent();

	WorldCoordinates nextPosition;
	bool found = findNextPosition(actor, getMaxDistance(host), getSpeed(host), actor->getPatrolPoints(), &nextPosition);

	// couldn't find a path to any patrol point
	if (!found)
		return AiActor::FINISHED;

	nextStepPosition->setPosition(nextPosition.getX(), nextPosition.getZ(), nextPosition.getY());
	nextStepPosition->setCell(nextPosition.getCell());

	float directionangle = atan2(nextPosition.getX() - host->getPositionX(), nextPosition.getY() - host->getPositionY());

	if (directionangle < 0)
		directionangle = 2 * M_PI + directionangle;

	Quaternion* direction = host->getDirection();

	direction->setHeadingDirection(directionangle);

	nextStepPosition->setReached(false);

	broadcastNextPositionUpdate(host, nextStepPosition);

	actor->activateMovementEvent();

	return AiActor::UNFINISHED;
}
