/*
 * WildContrabandScanSessionImplementation.cpp
 *
 *  Created on: Aug 30, 2020
 *      Author: loshult
 */

#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/gcw/sessions/WildContrabandScanSession.h"
#include "server/zone/managers/gcw/tasks/WildContrabandScanTask.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"

int WildContrabandScanSessionImplementation::initializeSession() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

	if (wildContrabandScanTask == nullptr) {
		wildContrabandScanTask = new WildContrabandScanTask(player);
	}
	if (!wildContrabandScanTask->isScheduled()) {
		wildContrabandScanTask->schedule(TASKDELAY);
	}

	player->updateCooldownTimer("crackdown_scan", CONTRABANDSCANCOOLDOWN);

	if (player->getActiveSession(SessionFacadeType::WILDCONTRABANDSCAN) != nullptr) {
		player->dropActiveSession(SessionFacadeType::WILDCONTRABANDSCAN);
	}
	player->addActiveSession(SessionFacadeType::WILDCONTRABANDSCAN, _this.getReferenceUnsafeStaticCast());

	landingCoordinates = getLandingCoordinates(player);

	return true;
}

int WildContrabandScanSessionImplementation::cancelSession() {
	ManagedReference<CreatureObject*> player = weakPlayer.get();

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

	Locker locker(player);

	ManagedReference<Zone*> zone = player->getZone();

	if (zone == nullptr) {
		cancelSession();
	}

	timeLeft--;

	switch (scanState) {
	case LANDING:
		landProbeDroid(player);
		scanState = CLOSINGIN;
		break;
	case CLOSINGIN:
		if (timeLeft <= 0) {
			droid = cast<AiAgent*>(player->getZone()->getCreatureManager()->spawnCreature(STRING_HASHCODE("probot"), 0, landingCoordinates.getX(),
																						  landingCoordinates.getZ(), landingCoordinates.getY(), 0));
			droid->activateLoad("stationary");
			droid->setFollowObject(player);
			scanState = INITIATESCAN;
		}
		break;
	case INITIATESCAN:
		sendSystemMessage(player, "dismount_imperial");

		if (player->isRidingMount()) {
			player->dismount();
			sendSystemMessage(player, "dismount");
		}
		sendSystemMessage(player, "probe_scan");

		timeLeft = SCANTIME;
		scanState = SCANDELAY;
		break;
	case SCANDELAY:
		if (timeLeft <= 0) {
			sendSystemMessage(player, "probe_scan_negative");
			scanState = WAITFORSHUTTLE;
		}
		break;
	case WAITFORSHUTTLE:
		scanState = TAKEOFF;
		break;
	case TAKEOFF:
		scanState = CLEANUP;
		timeLeft = 10;
		if (droid != nullptr) {
			Locker clocker(droid, player);
			droid->setPosture(CreaturePosture::SITTING, true); // Takeoff
		}
		break;
	case CLEANUP:
		if (timeLeft <= 0) {
			if (droid != nullptr) {
				Locker clocker(droid, player);
				droid->destroyObjectFromWorld(true);
			}
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
	return player != nullptr && player->isPlayerCreature() && !player->isDead() && !player->isFeigningDeath() && !player->isIncapacitated() && !player->isInCombat();
}

void WildContrabandScanSessionImplementation::landProbeDroid(CreatureObject* player) {
	PlayClientEffectLoc* effect = new PlayClientEffectLoc("clienteffect/probot_delivery.cef", player->getZone()->getZoneName(), landingCoordinates.getX(),
														  landingCoordinates.getZ(), landingCoordinates.getY(), 0, 0);
	player->sendMessage(effect);
	timeLeft = 3;
}

Vector3 WildContrabandScanSessionImplementation::getLandingCoordinates(CreatureObject* player) {
	if (player->getZone() == nullptr || player->getZone()->getPlanetManager() == nullptr) {
		return player->getPosition();
	}

	PlanetManager* planetManager = player->getZone()->getPlanetManager();

	return planetManager->getInSightSpawnPoint(player, 30, 120, 15);
}

void WildContrabandScanSessionImplementation::sendSystemMessage(CreatureObject* player, const String& messageName) {
	StringIdChatParameter systemMessage;
	systemMessage.setStringId("@imperial_presence/contraband_search:" + messageName);
	player->sendSystemMessage(systemMessage);
}