/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSTALLSHIPCOMPONENTCOMMAND_H_
#define INSTALLSHIPCOMPONENTCOMMAND_H_

#include "server/zone/objects/ship/ShipObject.h"

class InstallShipComponentCommand : public QueueCommand {
public:

	InstallShipComponentCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		auto ghost = creature->getPlayerObject().get();

		if (ghost == nullptr || ghost->isTeleporting()) {
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		uint64 shipID = tokenizer.getLongToken();
		int slot = tokenizer.getIntToken();

		if (slot == 112) {
			/* TODO: When adding ship components double clicking the main menu for slot, this number is sent along with the slot name as
					the next token value. Should this look for a component for the slot automatically? - H
			*/
			return GENERALERROR;
		}

		String componentString;
		tokenizer.getStringToken(componentString);

		if (shipID == 0 || componentString == "") {
			return GENERALERROR;
		}

		if (componentString == "installed") {
			return GENERALERROR;
		}

		uint64 componentID = Long::valueOf(componentString);

		if (componentID == 0) {
			return GENERALERROR;
		}

		ZoneServer* zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> component = zoneServer->getObject(componentID);

		if (component == nullptr || !component->isASubChildOf(creature) || !component->isComponent() || !(component->getGameObjectType() & SceneObjectType::SHIPATTACHMENT)) {
			return GENERALERROR;
		}

		auto shipComponent = dynamic_cast<ShipComponent*>(component.get());

		if (shipComponent == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> shipSceneO = zoneServer->getObject(shipID);

		if (shipSceneO == nullptr || !shipSceneO->isShipObject()) {
			return GENERALERROR;
		}

		auto ship = shipSceneO->asShipObject();

		if (ship == nullptr || ship->getOwner().get() != creature) {
			return GENERALERROR;
		}

		bool hasGodMode = ghost->hasGodMode();

		if (!hasGodMode) {
			if (!isPlayerCertifiedForObject(creature, ship)) {
				creature->sendSystemMessage("@ui_shipcomponents:err_cannot_open_ship_not_certified");
				return GENERALERROR;
			}

			if (!isPlayerCertifiedForObject(creature, shipComponent)) {
				creature->sendSystemMessage("@ui_shipcomponents:err_component_not_certified");
				return GENERALERROR;
			}

			if (!isSlotCompatibleWithComponent(ship, shipComponent, slot)) {
				creature->sendSystemMessage("That component is incompatible with that slot.");
				return GENERALERROR;
			}

			int chassisMass = ship->getChassisMass();
			int chassisMassMax = ship->getChassisMaxMass();
			int chassisMassAvailable = chassisMassMax - chassisMass;

			if (shipComponent->getMass() > chassisMassAvailable) {
				creature->sendSystemMessage("@ui_shipcomponents:err_too_heavy");
				return GENERALERROR;
			}
		} else {
			creature->sendSystemMessage("Bypassing InstallShipComponentCommand checks due to GOD mode.");
		}

		auto componentParent = component->getParent().get();

		if (componentParent != nullptr && componentParent->isFactoryCrate()) {
			auto factoryCrate = dynamic_cast<FactoryCrate*>(componentParent.get());

			if (factoryCrate == nullptr || !factoryCrate->isValidFactoryCrate() || factoryCrate->getUseCount() < 1) {
				return GENERALERROR;
			}

			auto crateParent = factoryCrate->getParent().get();

			if (crateParent == nullptr || crateParent->getCountableObjectsRecursive() > crateParent->getContainerVolumeLimit() + 1) {
				return GENERALERROR;
			}

			Locker xLock(factoryCrate, creature);

			ManagedReference<TangibleObject*> crateComponent = factoryCrate->extractObject();

			if (crateComponent == nullptr || !crateComponent->isComponent()) {
				return GENERALERROR;
			}

			if (crateComponent->getUseCount() == 1) {
				Locker cLock(crateComponent, creature);

				crateComponent->setUseCount(0, true);
			}

			component = crateComponent;
		}

		Locker locker(ship, creature);
		ship->install(creature, component, slot, true);

		return SUCCESS;
	}

	bool isSlotCompatibleWithComponent(ShipObject* ship, ShipComponent* component, uint32 slot) const {
		auto shipManager = ShipManager::instance();

		if (shipManager == nullptr) {
			return false;
		}

		const auto chassisData = shipManager->getChassisData(ship->getShipChassisName());

		if (chassisData == nullptr) {
			return false;
		}

		const auto slotData = chassisData->getComponentSlotData(slot);

		if (slotData == nullptr) {
			return false;
		}

		const auto componentData = shipManager->getShipComponent(component->getComponentDataName());

		if (componentData == nullptr) {
			return false;
		}

		const auto& slotCompatibility = slotData->getCompatability();
		const auto& compCompatibility = componentData->getCompatibility();

		return slotCompatibility == compCompatibility;
	}

	bool isPlayerCertifiedForObject(CreatureObject* player, TangibleObject* object) const {
		auto objectTemplate = dynamic_cast<SharedTangibleObjectTemplate*>(object->getObjectTemplate());

		if (objectTemplate == nullptr) {
			return false;
		}

		auto ghost = player->getPlayerObject().get();

		if (ghost == nullptr) {
			return false;
		}

		const auto& certs = objectTemplate->getCertificationsRequired();

		for (int i = 0; i < certs.size(); ++i) {
			auto cert = certs.get(i);

			if (!ghost->hasAbility(cert) && !player->hasSkill(cert)) {
				return false;
			}
		}

		return true;
	}

};

#endif //INSTALLSHIPCOMPONENTCOMMAND_H_
