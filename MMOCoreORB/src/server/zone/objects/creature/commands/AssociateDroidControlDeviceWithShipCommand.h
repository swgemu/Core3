/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
#define ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_

#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/ship/ShipDroidData.h"

class AssociateDroidControlDeviceWithShipCommand : public QueueCommand {
public:

	AssociateDroidControlDeviceWithShipCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		UnicodeTokenizer tokens(arguments);

		auto shipID = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;
		auto itemID = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;

		if (shipID == 0) {
			return GENERALERROR;
		}

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> shipObject = zoneServer->getObject(shipID);

		if (shipObject == nullptr || !shipObject->isShipObject()) {
			return GENERALERROR;
		}

		auto ship = shipObject->asShipObject();

		if (ship == nullptr) {
			return GENERALERROR;
		}

		Locker sLock(ship, creature);

		if (itemID == 0) {
			ship->setShipDroidID(0, true);
			return SUCCESS;
		}

		auto componentMap = ship->getShipComponentMap();

		if (!ship->isComponentInstalled(Components::DROID_INTERFACE)) {
			creature->sendSystemMessage("@space/space_interaction:no_droid_command_module");
			return GENERALERROR;
		}

		if (!ship->isComponentFunctional(Components::DROID_INTERFACE)) {
			creature->sendSystemMessage("@space/space_interaction:droid_interface_disabled_no_equip");
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> petControl = zoneServer->getObject(itemID);

		if (petControl == nullptr || !petControl->isPetControlDevice()) {
			return GENERALERROR;
		}

		auto droidControl = dynamic_cast<PetControlDevice*>(petControl.get());

		if (droidControl == nullptr) {
			return GENERALERROR;
		}

		ManagedReference<TangibleObject*> droid = droidControl->getControlledObject();

		if (droid == nullptr || !droid->isDroidObject()) {
			return GENERALERROR;
		}

		auto droidObject = dynamic_cast<DroidObject*>(droid.get());

		if (droidObject == nullptr) {
			return GENERALERROR;
		}

		uint32 droidType = ShipDroidData::getDroidType(droidObject->getServerObjectCRC());
		uint32 shipType = ShipDroidData::getShipDroidType(ship->getShipChassisName().hashCode());

		if (shipType != droidType) {
			if (droidType == ShipDroidData::NONE) {
				creature->sendSystemMessage("@space/space_interaction:not_an_astromech_for_space");
				return GENERALERROR;
			}

			if (droidType == ShipDroidData::ASTROMECH) {
				creature->sendSystemMessage("@space/space_interaction:need_flight_computer");
				return GENERALERROR;
			}

			if (droidType == ShipDroidData::FLIGHTCOMPUTER) {
				creature->sendSystemMessage("@space/space_interaction:need_astromech");
				return GENERALERROR;
			}
		}

		uint64 droidID = droid->getObjectID();

		ship->setShipDroidID(droidID, true);
		creature->sendSystemMessage("@space/space_interaction:ship_droid_set");
		return SUCCESS;
	}
};

#endif //ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
