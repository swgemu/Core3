/*
 * WildContrabandScanSessionImplementation.cpp
 *
 *  Created on: Aug 30, 2020
 *      Author: loshult
 */

#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/gcw/observers/ProbotObserver.h"
#include "server/zone/managers/gcw/sessions/WildContrabandScanSession.h"
#include "server/zone/managers/gcw/tasks/LambdaShuttleWithReinforcementsTask.h"
#include "server/zone/managers/gcw/tasks/WildContrabandScanTask.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"

int WildContrabandScanSessionImplementation::initializeSession() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if (player == nullptr) {
		return false;
	}

	ManagedReference<Zone*> zone = player->getZone();

	if (zone == nullptr || zone->getGCWManager() == nullptr) {
		return false;
	}

	Locker lock(player);

	if (wildContrabandScanTask == nullptr) {
		wildContrabandScanTask = new WildContrabandScanTask(player);
	}

	if (!wildContrabandScanTask->isScheduled()) {
		wildContrabandScanTask->schedule(TASKDELAY);
	}

	GCWManager* gcwMan = zone->getGCWManager();

	if (gcwMan != nullptr)
		player->updateCooldownTimer("crackdown_scan", gcwMan->getCrackdownPlayerScanCooldown());

	if (player->getActiveSession(SessionFacadeType::WILDCONTRABANDSCAN) != nullptr) {
		player->dropActiveSession(SessionFacadeType::WILDCONTRABANDSCAN);
	}

	player->addActiveSession(SessionFacadeType::WILDCONTRABANDSCAN, _this.getReferenceUnsafeStaticCast());

	Vector3 playerPos = player->getPosition();

	landingCoordinates = getLandingCoordinates(zone, player, playerPos);

	return true;
}

int WildContrabandScanSessionImplementation::cancelSession() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	AiAgent* droid = getDroid();

	if (droid != nullptr) {
		Locker dlocker(droid);
		droid->destroyObjectFromWorld(true);
	}

	if (player != nullptr) {
		player->dropActiveSession(SessionFacadeType::WILDCONTRABANDSCAN);
	}

	if (wildContrabandScanTask != nullptr) {
		wildContrabandScanTask->cancel();
	}

	return clearSession();
}

int WildContrabandScanSessionImplementation::clearSession() {
	return 0;
}

void WildContrabandScanSessionImplementation::runWildContrabandScan() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if (!scanPrerequisitesMet(player)) {
		cancelSession();
	}

	Locker plocker(player);

	ManagedReference<Zone*> zone = player->getZone();

	if (zone == nullptr) {
		cancelSession();
		return;
	}

	AiAgent* droid = getDroid();

	if (droid != nullptr && droid->isInCombat()) {
		scanState = INCOMBAT;
	}

	timeLeft--;

	switch (scanState) {
	case LANDING:
		landProbeDroid(zone, player);
		scanState = HEADTOPLAYER;
		break;
	case HEADTOPLAYER:
		if (timeLeft <= 0) {
			weakDroid = cast<AiAgent*>(zone->getCreatureManager()->spawnCreature(STRING_HASHCODE("crackdown_probot"), 0, landingCoordinates.getX(), landingCoordinates.getZ(), landingCoordinates.getY(), 0));

			AiAgent* droid = getDroid();
			if (droid != nullptr) {
				Locker clocker(droid, player);

				ManagedReference<ProbotObserver*> probotObserver = new ProbotObserver();
				probotObserver->setProbot(droid);
				droid->registerObserver(ObserverEventType::DEFENDERADDED, probotObserver);
				droid->setAITemplate();

				droid->addCreatureFlag(CreatureFlag::FOLLOW);
				droid->setFollowObject(player);

				scanState = CLOSINGIN;
				timeLeft = 30;
			} else {
				error("Probot is missing.");
				scanState = FINISHED;
			}
		}
		break;
	case CLOSINGIN:
		if (timeLeft > 0) {
			AiAgent* droid = getDroid();
			if (droid != nullptr) {
				if (player->getWorldPosition().distanceTo(droid->getWorldPosition()) < 32) {
					scanState = INITIATESCAN;
				}
			} else {
				error("Probot is missing.");
				scanState = FINISHED;
			}
		} else {
			scanState = TAKEOFF; // Probot has not reached the player in 30 s, take off again.
		}
		break;
	case INITIATESCAN: {
		sendSystemMessage(player, "dismount_imperial");

		if (player->isRidingMount()) {
			player->dismount();
			sendSystemMessage(player, "dismount");
		}
		sendSystemMessage(player, "probe_scan");

		AiAgent* droid = getDroid();
		if (droid != nullptr) {
			Locker clocker(droid, player);
			droid->showFlyText("imperial_presence/contraband_search", "probe_scan_fly", 255, 0, 0);
			droid->setFollowObject(player);
			timeLeft = SCANTIME;
			scanState = SCANDELAY;
		} else {
			error("Probot is missing.");
			scanState = FINISHED;
		}
	} break;
	case SCANDELAY: {
		PlayerObject* ghost = player->getPlayerObject();
		if ((ghost != nullptr && ghost->hasCrackdownTefTowards(Factions::FACTIONIMPERIAL)) || (player->getFaction() == Factions::FACTIONREBEL && (player->getFactionStatus() == FactionStatus::OVERT || player->getFactionStatus() == FactionStatus::COVERT))) {
			AiAgent* droid = getDroid();
			if (droid != nullptr) {
				Locker droidlock(droid);
				droid->addDefender(player);
			}
		}

		if (timeLeft <= 0) {
			int numberOfContrabandItems = 0;
			GCWManager* gcwManager = zone->getGCWManager();
			if (gcwManager != nullptr) {
				numberOfContrabandItems = gcwManager->countContrabandItems(player);
			}
			if (numberOfContrabandItems > 0) {
				sendSystemMessage(player, "probe_scan_positive");
				scanState = TAKEOFF;
				timeLeft = 12;

				MissionManager* missionManager = player->getZoneServer()->getMissionManager();
				auto spawnPoint = missionManager->getFreeNpcSpawnPoint(player->getPlanetCRC(), player->getWorldPositionX(), player->getWorldPositionY(), NpcSpawnPoint::LAMBDASHUTTLESPAWN, 128.f);

				if (spawnPoint != nullptr) {
					Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(player, Factions::FACTIONIMPERIAL, 1, "@imperial_presence/contraband_search:containment_team_imperial", *spawnPoint->getPosition(), *spawnPoint->getDirection(), LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLESCAN);
					lambdaTask->schedule(1000);
				} else {
					float spawnDirection = player->getDirection()->getRadians() + Math::PI;
					if (spawnDirection >= 2 * Math::PI) {
						spawnDirection -= 2 * Math::PI;
					}

					Reference<Task*> lambdaTask = new LambdaShuttleWithReinforcementsTask(player, Factions::FACTIONIMPERIAL, 1, "@imperial_presence/contraband_search:containment_team_imperial", landingCoordinates, Quaternion(Vector3(0, 1, 0), spawnDirection), LambdaShuttleWithReinforcementsTask::LAMBDASHUTTLESCAN);
					lambdaTask->schedule(1000);
				}

				AiAgent* droid = getDroid();

				if (droid != nullptr && !droid->isDead()) {
					Locker dlocker(droid);
					PatrolPoint* homeLocation = droid->getHomeLocation();

					droid->removeCreatureFlag(CreatureFlag::FOLLOW);
					droid->clearPatrolPoints();

					droid->setMovementState(AiAgent::PATROLLING);
					droid->setNextPosition(homeLocation->getPositionX(), homeLocation->getPositionZ(), homeLocation->getPositionY());

					droid->showFlyText("imperial_presence/contraband_search", "probot_support_fly", 255, 0, 0);
				}
			} else {
				sendSystemMessage(player, "probe_scan_negative");
				scanState = TAKEOFF;
				timeLeft = 5;
			}
		}
		break;
	}
	case INCOMBAT: {
		AiAgent* droid = getDroid();
		if (droid != nullptr) {
			if (!droid->isInCombat() && !droid->isDead()) {
				scanState = TAKEOFF;
				timeLeft = 5;
			} else if (droid->isDead()) {
				scanState = TAKINGOFF;
				timeLeft = 60;
			}
		} else {
			scanState = FINISHED; // Probot is destroyed.
		}
	} break;
	case TAKEOFF:
		if (timeLeft <= 0) {
			scanState = TAKINGOFF;
			timeLeft = 7;
			AiAgent* droid = getDroid();

			if (droid != nullptr) {
				Locker dlocker(droid);
				droid->setPosture(CreaturePosture::SITTING, true); // Takeoff
			} else {
				scanState = FINISHED; // Probot is destroyed.
			}
		}
		break;
	case TAKINGOFF:
		if (timeLeft <= 0) {
			scanState = FINISHED;
		}
		break;
	default:
		error("Incorrect state");
		break;
	}

	if (scanState != FINISHED) {
		wildContrabandScanTask->reschedule(TASKDELAY);
	} else {
		cancelSession();
	}
}

bool WildContrabandScanSessionImplementation::scanPrerequisitesMet(CreatureObject* player) {
	return player != nullptr && player->isPlayerCreature();
}

void WildContrabandScanSessionImplementation::landProbeDroid(Zone* zone, CreatureObject* player) {
	PlayClientEffectLoc* effect = new PlayClientEffectLoc("clienteffect/probot_delivery.cef", zone->getZoneName(), landingCoordinates.getX(), landingCoordinates.getZ(), landingCoordinates.getY(), 0, 0);
	player->sendMessage(effect);
	timeLeft = 3;
}

Vector3 WildContrabandScanSessionImplementation::getLandingCoordinates(Zone* zone, CreatureObject* player, Vector3& playerPos) {
	if (zone == nullptr || player == nullptr) {
		return playerPos;
	}

	PlanetManager* planetManager = zone->getPlanetManager();

	if (planetManager == nullptr) {
		return playerPos;
	}

	Vector3 coords = planetManager->getInSightSpawnPoint(player, 30, 120, 25);
	float z = CollisionManager::getWorldFloorCollision(coords.getX(), coords.getY(), coords.getZ(), zone, true);

	coords.setZ(z);

	return coords;
}

void WildContrabandScanSessionImplementation::sendSystemMessage(CreatureObject* player, const String& messageName) {
	StringIdChatParameter systemMessage;
	systemMessage.setStringId("@imperial_presence/contraband_search:" + messageName);
	player->sendSystemMessage(systemMessage);
}

AiAgent* WildContrabandScanSessionImplementation::getDroid() {
	return weakDroid.get();
}
