/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRUCTURESTATUSCOMMAND_H_
#define STRUCTURESTATUSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/structure/StructureManager.h"

class StructurestatusCommand : public QueueCommand {
public:

	StructurestatusCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		uint64 targetid = creature->getTargetID();
		ManagedReference<SceneObject*> obj = playerManager->getInRangeStructureWithAdminRights(creature, targetid);

		if (obj == nullptr || !obj->isStructureObject() || obj->getZone() == nullptr) {
			creature->sendSystemMessage("@player_structure:no_building"); //you must be in a building, be near an installation, or have one targeted to do that.
			return INVALIDTARGET;
		}

		StructureObject* structure = cast<StructureObject*>( obj.get());

		StructureManager::instance()->reportStructureStatus(creature, structure, nullptr);

		// Check for admin doing export: /structurestatus export [reason for export]
		auto ghost = creature->getPlayerObject();

		if (structure != nullptr && ghost != nullptr && ghost->isStaff()) {
			StringTokenizer args(arguments.toString());

			if (args.hasMoreTokens()) {
				String arg1;
				args.getStringToken(arg1);

				if (arg1.toLowerCase() == "export") {
					String reason = "";

					if (args.hasMoreTokens())
						args.finalToken(reason);

					StringBuffer msg;

					msg << "/structurestatus export by " << creature->getFirstName();

					if (!reason.isEmpty())
						msg << "; reason: " << reason;

					String path = structure->exportJSON(msg.toString());

					structure->info(msg.toString() + "; exported to " + path, true);

					msg << endl << "Exported to " << path;

					creature->sendSystemMessage(msg.toString());
				} else {
					creature->sendSystemMessage("Usage: /structurestatus export [reason for export]");
				}
			}
		}

		return SUCCESS;
	}

};

#endif //STRUCTURESTATUSCOMMAND_H_
