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

		ManagedReference<SceneObject*> shipSceneO = zoneServer->getObject(shipID);

		if (shipSceneO == nullptr || !shipSceneO->isShipObject())
			return GENERALERROR;

		ManagedReference<ShipObject*> ship = shipSceneO.castTo<ShipObject*>();

		if (ship == nullptr)
			return GENERALERROR;

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

};

#endif //INSTALLSHIPCOMPONENTCOMMAND_H_
