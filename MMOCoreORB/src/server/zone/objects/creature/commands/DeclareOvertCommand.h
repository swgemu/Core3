/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DECLAREOVERTCOMMAND_H_
#define DECLAREOVERTCOMMAND_H_

class DeclareOvertCommand : public QueueCommand {
public:

	DeclareOvertCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!ConfigManager::instance()->useCovertOvertSystem())
			return GENERALERROR;

		uint32 creatureFaction = creature->getFaction();

		if (creatureFaction == Factions::FACTIONNEUTRAL || creature->getFactionStatus() != FactionStatus::COVERT)
			return GENERALERROR;

		Zone* zone = creature->getZone();

		if (zone == nullptr)
			return GENERALERROR;

		// 	This command allows a covert faction member to declare overt faction status. Usage of this command is restricted to a 50m radius around friendly player-placed faction headquarters.
		CloseObjectsVector* vec = (CloseObjectsVector*) creature->getCloseObjects();
		SortedVector<QuadTreeEntry*> closeObjects;

		if (vec != nullptr) {
			closeObjects.removeAll(vec->size(), 20);

			vec->safeCopyReceiversTo(closeObjects, CloseObjectsVector::STRUCTURETYPE);
		} else {
	#ifdef COV_DEBUG
			sourceCreature->info("Null closeobjects vector in DeclareOvertCommand", true);
	#endif
			zone->getInRangeObjects(creature->getWorldPositionX(), creature->getWorldPositionY(), 50, &closeObjects, true);
		}

		int result = false;

		for (int i = 0; i < closeObjects.size(); i++) {
			SceneObject* object = static_cast<SceneObject*>(closeObjects.get(i));

			if (object == nullptr || !object->isGCWBase())
				continue;

			TangibleObject* baseTano = object->asTangibleObject();

			if (baseTano != nullptr && creatureFaction == baseTano->getFaction() && baseTano->isInRange(creature, 50.f)) {
				result = true;
				break;
			}
		}

		if (result) {
			Locker lock(creature);
			creature->setFactionStatus(FactionStatus::OVERT);
		} else {
			creature->sendSystemMessage("You must be within 50m of a friendly player-placed faction headquarters to declare your faction allegiance.");
		}

		return result ? SUCCESS : GENERALERROR;
	}
};

#endif //DECLAREOVERTCOMMAND_H_
