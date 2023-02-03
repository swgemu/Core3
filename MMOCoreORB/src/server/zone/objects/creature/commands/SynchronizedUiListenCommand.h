/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SYNCHRONIZEDUILISTENCOMMAND_H_
#define SYNCHRONIZEDUILISTENCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"

class SynchronizedUiListenCommand : public QueueCommand {
public:

	SynchronizedUiListenCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = (creature->getZoneServer()->getObject(target)).castTo<SceneObject*>();

		if (object == nullptr)
			return GENERALERROR;

		try {
			Locker clocker(object, creature);

			object->synchronizedUIListen(creature);
		} catch (Exception& e) {
		}

		return SUCCESS;
	}

};

#endif //SYNCHRONIZEDUILISTENCOMMAND_H_
