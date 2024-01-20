/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INSERTITEMINTOSHIPCOMPONENTSLOTCOMMAND_H_
#define INSERTITEMINTOSHIPCOMPONENTSLOTCOMMAND_H_

#include "server/zone/objects/ship/components/ShipComponent.h"

class InsertItemIntoShipComponentSlotCommand : public QueueCommand {
public:

	InsertItemIntoShipComponentSlotCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		UnicodeTokenizer tokens(arguments);

		auto shipID = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;
		auto weaponID = tokens.hasMoreTokens() ? tokens.getIntToken() : 0;
		auto itemID = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;

		if (shipID == 0 || itemID == 0 || weaponID > Components::FIGHTERSLOTMAX) {
			return GENERALERROR;
		}

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> sceneShip = zoneServer->getObject(shipID);

		if (sceneShip == nullptr || !sceneShip->isShipObject()) {
			return GENERALERROR;
		}

		auto ship = sceneShip->asShipObject();

		if (ship == nullptr) {
			return GENERALERROR;
		}

		auto weapon = ship->getComponentObject(weaponID);

		if (weapon == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> sceneAmmo = zoneServer->getObject(itemID);

		if (sceneAmmo == nullptr || !sceneAmmo->isASubChildOf(creature) || !sceneAmmo->isComponent() || !(sceneAmmo->getGameObjectType() & SceneObjectType::SHIPATTACHMENT)) {
			return GENERALERROR;
		}

		auto ammo = dynamic_cast<Component*>(sceneAmmo.get());

		if (ammo == nullptr || ammo->getAttributeValue("fltmaxammo") == 0) {
			return GENERALERROR;
		}

		auto ammoClassMap = ship->getAmmoClassMap();
		auto ammoMaxMap = ship->getMaxAmmoMap();
		auto ammoMinMap = ship->getCurrentAmmoMap();

		if (ammoClassMap == nullptr || ammoMaxMap == nullptr || ammoMinMap == nullptr) {
			return GENERALERROR;
		}

		bool isCounterLauncher = weapon->getClientGameObjectType() == SceneObjectType::SHIPCOUNTERMEASURELAUNCHER;
		bool isMissileLauncher = weapon->getClientGameObjectType() == SceneObjectType::SHIPWEAPONLAUNCHER;

		if (!isCounterLauncher && !isMissileLauncher) {
			creature->sendSystemMessage("@space/space_interaction:no_ammo_allowed");
			return GENERALERROR;
		}

		bool isCounterAmmo = sceneAmmo->getClientGameObjectType() == SceneObjectType::SHIPCOUNTERMEASURE;
		bool isMissileAmmo = sceneAmmo->getClientGameObjectType() == SceneObjectType::SHIPMISSILE;

		if (!isMissileAmmo && !isCounterAmmo) {
			creature->sendSystemMessage("@space/space_interaction:not_ammo");
			return GENERALERROR;
		}

		if ((isCounterLauncher && !isCounterAmmo) || (isMissileLauncher && !isMissileAmmo)) {
			creature->sendSystemMessage("@space/space_interaction:incorrect_ammo");
			return GENERALERROR;
		}

		int ammoMax = ammoMaxMap->get(weaponID);
		int ammoMin = ammoMinMap->get(weaponID);

		if (ammoMax > 0 && ammoMin == ammoMax) {
			String type = isMissileLauncher ? "missile" : "countermeasure";
			creature->sendSystemMessage("@space/space_interaction:" + type + "_full_no_reload");
			return GENERALERROR;
		}

		int ammoCrc = sceneAmmo->getServerObjectCRC();
		int ammoType = -1;

		if (sceneAmmo->getGameObjectType() == SceneObjectType::SHIPCOUNTERMEASURE) {
			ammoType = ShipCountermeasureData::getCountermeasureAmmoType(ammoCrc);
		} else if (sceneAmmo->getGameObjectType() == SceneObjectType::SHIPMISSILE) {
			ammoType = ShipMissileData::getMissileAmmoType(ammoCrc);
		}

		if (ammoType == -1 || ammoType != ammoClassMap->get(weaponID)) {
			creature->sendSystemMessage("@space/space_interaction:incorrect_ammo");
			return GENERALERROR;
		}

		StringIdChatParameter stringId;
		String type = isMissileLauncher ? "missile" : "countermeasure";

		stringId.setStringId("space/space_interaction", "reloaded_x_" + type + "_ammo");
		stringId.setDI(ammo->getAttributeValue("fltmaxammo"));
		stringId.setTO(sceneAmmo->getObjectID());

		creature->sendSystemMessage(stringId);

		auto ammoParent = sceneAmmo->getParent().get();

		if (ammoParent != nullptr && ammoParent->isFactoryCrate()) {
			auto factoryCrate = dynamic_cast<FactoryCrate*>(ammoParent.get());

			if (factoryCrate == nullptr || !factoryCrate->isValidFactoryCrate() || factoryCrate->getUseCount() < 1) {
				return GENERALERROR;
			}

			auto crateParent = factoryCrate->getParent().get();

			if (crateParent == nullptr || crateParent->getCountableObjectsRecursive() > crateParent->getContainerVolumeLimit() + 1) {
				return GENERALERROR;
			}

			Locker xLock(factoryCrate, creature);

			ManagedReference<TangibleObject*> crateAmmo = factoryCrate->extractObject();

			if (crateAmmo == nullptr || !crateAmmo->isComponent()) {
				return GENERALERROR;
			}

			if (crateAmmo->getUseCount() == 1) {
				Locker cLock(crateAmmo, creature);

				crateAmmo->setUseCount(0, true);
			}

			sceneAmmo = crateAmmo;
		}

		Locker locker(ship, creature);

		ship->installAmmo(creature, sceneAmmo, weaponID, true);

		return SUCCESS;
	}
};

#endif //INSERTITEMINTOSHIPCOMPONENTSLOTCOMMAND_H_
