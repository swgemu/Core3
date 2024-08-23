/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
#define ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_

#include "server/zone/objects/ship/ShipDroidData.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/ai/DroidObject.h"

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

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		UnicodeTokenizer tokens(arguments);
		uint64 shipID = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;
		uint64 itemID = tokens.hasMoreTokens() ? tokens.getLongToken() : 0;

		if (shipID == 0) {
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> shipObject = zoneServer->getObject(shipID);

		if (shipObject == nullptr || !shipObject->isShipObject()) {
			return GENERALERROR;
		}

		auto ship = shipObject->asShipObject();

		if (ship == nullptr || ship->getOwner().get() != creature) {
			return GENERALERROR;
		}

		if (itemID == 0) {
			Locker sLock(ship, creature);
			ship->setShipDroidID(0, true);
			return SUCCESS;
		}

		if (!ship->isComponentInstalled(Components::DROID_INTERFACE)) {
			creature->sendSystemMessage("@space/space_interaction:no_droid_command_module");
			return GENERALERROR;
		}

		if (!ship->isComponentFunctional(Components::DROID_INTERFACE)) {
			creature->sendSystemMessage("@space/space_interaction:droid_interface_disabled_no_equip");
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> control = zoneServer->getObject(itemID);

		if (control == nullptr || !control->isPetControlDevice()) {
			return GENERALERROR;
		}

		auto droidControl = dynamic_cast<PetControlDevice*>(control.get());

		if (droidControl == nullptr || !droidControl->isASubChildOf(creature)) {
			return GENERALERROR;
		}

		ManagedReference<TangibleObject*> droid = droidControl->getControlledObject();

		if (droid == nullptr || !droid->isDroidObject()) {
			return GENERALERROR;
		}

		uint32 droidType = ShipDroidData::getDroidType(droid->getServerObjectCRC());
		uint32 shipType = ShipDroidData::getShipDroidType(ship->getShipChassisName().hashCode());

		if (droidType != shipType) {
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

		Locker sLock(ship, creature);

		ship->setShipDroidID(droid->getObjectID(), true);

		creature->sendSystemMessage("@space/space_interaction:ship_droid_set");
		return SUCCESS;
	}
};

#endif //ASSOCIATEDROIDCONTROLDEVICEWITHSHIPCOMMAND_H_
