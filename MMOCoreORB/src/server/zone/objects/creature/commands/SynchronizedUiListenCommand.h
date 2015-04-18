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
		int value = 0;

		StringTokenizer tokenizer(arguments.toString());

		if (tokenizer.hasMoreTokens())
			value = tokenizer.getIntToken();

		if (object != NULL && creature->isPlayerCreature()) {
			try {
				Locker clocker(object, creature);

				object->synchronizedUIListen(creature, value);
			} catch (Exception& e) {
			}
		}

		return SUCCESS;
	}

};

#endif //SYNCHRONIZEDUILISTENCOMMAND_H_
