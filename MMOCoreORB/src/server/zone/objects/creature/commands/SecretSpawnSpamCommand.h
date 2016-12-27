/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SECRETSPAWNSPAMCOMMAND_H_
#define SECRETSPAWNSPAMCOMMAND_H_

class SecretSpawnSpamCommand : public QueueCommand {
public:

	SecretSpawnSpamCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif //SECRETSPAWNSPAMCOMMAND_H_
