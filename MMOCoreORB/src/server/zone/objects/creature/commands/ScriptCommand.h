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
		} else if (cmdName == "luaevents") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script luaevents <oid>");
				return INVALIDPARAMETERS;
			}

			uint64 objID = args.getLongToken();

			ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objID);

			if (obj == NULL) {
				creature->sendSystemMessage("Invalid object.");
				return INVALIDPARAMETERS;
			}

			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

			if (ghost == NULL)
				return GENERALERROR;

			Vector<Reference<ScreenPlayTask*> > eventList = DirectorManager::instance()->getObjectEvents(obj);

			ManagedReference<SuiListBox*> box = new SuiListBox(creature, 0);
			box->setPromptTitle("LUA Events");
			Time currentTime;
			box->setPromptText("Below are the LUA Events currently scheduled for the object.\n\nCurrent server time: " + currentTime.getFormattedTime());
			box->setUsingObject(creature);
			box->setForceCloseDisabled();

			for (int i = 0; i < eventList.size(); i++) {
				Reference<ScreenPlayTask*> task = eventList.get(i);

				if (task == NULL)
					continue;

				String buffer = task->getScreenPlay() + ":" + task->getTaskKey();
				String args = task->getArgs();

				if (args != "")
					buffer += " (Args: " + args + ")";

				Time nextExecutionTime;
				Core::getTaskManager()->getNextExecutionTime(task, nextExecutionTime);
				uint64 miliDiff = nextExecutionTime.miliDifference();

				buffer += ", Execution (server time): " + nextExecutionTime.getFormattedTime() + " (" + getTimeString(-miliDiff) + " from now)";

				box->addMenuItem(buffer);
			}

			ghost->addSuiBox(box);
			creature->sendMessage(box->generateMessage());
		}

		return SUCCESS;
	}


	String getTimeString(uint64 timestamp) const {
		int seconds = timestamp / 1000;

		int hours = seconds / 3600;
		seconds -= hours * 3600;

		int minutes = seconds / 60;
		seconds -= minutes * 60;

		StringBuffer buffer;

		if (hours > 0)
			buffer << hours << "h ";

		if (minutes > 0)
			buffer << minutes << "m ";

		if (seconds > 0)
			buffer << seconds << "s";

		return buffer.toString();
	}

};

#endif //SCRIPTCOMMAND_H_
