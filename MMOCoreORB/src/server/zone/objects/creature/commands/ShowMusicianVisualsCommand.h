/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SHOWMUSICIANVISUALSCOMMAND_H_
#define SHOWMUSICIANVISUALSCOMMAND_H_

class ShowMusicianVisualsCommand : public QueueCommand {
public:

	ShowMusicianVisualsCommand(const String& name, ZoneProcessServer* server)
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

#endif //SHOWMUSICIANVISUALSCOMMAND_H_
