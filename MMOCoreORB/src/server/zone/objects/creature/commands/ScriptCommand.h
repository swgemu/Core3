/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SCRIPTCOMMAND_H_
#define SCRIPTCOMMAND_H_

class ScriptCommand : public QueueCommand {
public:

	ScriptCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer args(arguments.toString());

		if(!args.hasMoreTokens())
			return GENERALERROR;

		String cmdName = "";

		args.getStringToken(cmdName);

		if (cmdName == "readshareddata") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script readshareddata <key>");
				return INVALIDPARAMETERS;
			}

			String key = "";
			args.getStringToken(key);

			uint64 data = DirectorManager::instance()->readSharedMemory(key);

			creature->sendSystemMessage("Value for shared data using key " + key + " is: " + String::valueOf(data));
		} else if (cmdName == "readstringshareddata") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script readstringshareddata <key>");
				return INVALIDPARAMETERS;
			}

			String key = "";
			args.getStringToken(key);

			String data = DirectorManager::instance()->readStringSharedMemory(key);

			creature->sendSystemMessage("Value for shared string data using key " + key + " is: " + data);
		} else if (cmdName == "getqueststatus") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script getqueststatus <key>");
				return INVALIDPARAMETERS;
			}

			String key = "";
			args.getStringToken(key);

			String data = DirectorManager::instance()->getQuestStatus(key);

			creature->sendSystemMessage("Value for queststatus using key " + key + " is: " + data);
		}

		return SUCCESS;
	}

};

#endif //SCRIPTCOMMAND_H_
