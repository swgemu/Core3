/*
 * ScannerZoneComponent.cpp
 *
 *  Created on: Dec 17, 2012
 *      Author: root
 */

#include "ScannerZoneComponent.h"
#include "ScannerDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/faction/Factions.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/installation/components/TurretObserver.h"


void ScannerZoneComponent::notifyInsertToZone(SceneObject* sceneObject, Zone* zone) const {
	if (zone == nullptr)
		return;

	ManagedReference<InstallationObject*> installation = cast<InstallationObject*>(sceneObject);

	if (installation == nullptr)
		return;

	ManagedReference<TurretObserver*> observer = new TurretObserver();

	if (observer != nullptr)
		installation->registerObserver(ObserverEventType::OBJECTDESTRUCTION, observer);
}

void ScannerZoneComponent::notifyPositionUpdate(SceneObject* sceneObject, QuadTreeEntry* entry) const {
	if (sceneObject == nullptr || entry == nullptr)
		return;

	ManagedReference<SceneObject*> target = cast<SceneObject*>(entry);

	if (!sceneObject->isTangibleObject() || target == nullptr){
		return;
	}

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

	if (tano == nullptr)
		return;

	DataObjectComponentReference* ref = sceneObject->getDataObjectComponent();

	if (ref == nullptr) {
		return;
	}

	ScannerDataComponent* scannerData = cast<ScannerDataComponent*>(ref->get());

	if (scannerData == nullptr || !scannerData->canScan())
		return;

	if (sceneObject->isScanner() && target->isPlayerCreature() && sceneObject->isInRange(target, 32)){
		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(entry);

		if (player == nullptr)
			return;

		ManagedReference<PlayerObject*> playerObject = player->getPlayerObject();

		if (playerObject == nullptr)
			return;

		uint32 playerFaction = player->getFaction();

		if (tano->getFaction() != playerFaction && playerFaction != 0 && CollisionManager::checkLineOfSight(tano, player)){
			scannerData->updateCooldown();

			PlayClientEffectLoc* explodeLoc = new PlayClientEffectLoc("clienteffect/survey_effect.cef", tano->getZone()->getZoneName(), tano->getPositionX(), tano->getPositionZ(), tano->getPositionY());
			tano->broadcastMessage(explodeLoc, false);

			if (ConfigManager::instance()->useCovertOvertSystem() && player->getFactionStatus() == FactionStatus::COVERT && System::random(100) < 40) {
				if (sceneObject->isInstallationObject()) {
					InstallationObject* scanner = cast<InstallationObject*>(sceneObject);

					if (scanner != nullptr) {
						StringIdChatParameter stringId("base_player", "prose_covert_uncloak");

						stringId.setTT(scanner->getOwnerObjectID());

						String factionString = "";

						if (playerFaction == Factions::FACTIONIMPERIAL) {
							factionString = "Imperial";
						} else {
							factionString = "Rebel";
						}

						stringId.setTO(factionString);
						player->sendSystemMessage(stringId);
					}
				}

				Locker lock(player);

				player->setFactionStatus(FactionStatus::OVERT);
			}
		}
	}

	return;
}
