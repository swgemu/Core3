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
		} else if (cmdName == "clearallquests") {
			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
			if (ghost != nullptr) {
				// Clear quest data map
				int questCount = ghost->getPlayerQuestsData()->size();
				Vector<uint32> questCrcs;
				for (int i = 0; i < questCount; i++) {
					questCrcs.add(ghost->getPlayerQuestsData()->getKeyAt(i));
				}
				for (int i = 0; i < questCrcs.size(); i++) {
					ghost->clearPlayerQuestData(questCrcs.get(i), false);
				}

				// Clear bit arrays
				int bitCount = ghost->getActiveQuests()->bitCount();
				for (int i = 0; i < bitCount; i++) {
					ghost->clearActiveQuestsBit(i, false);
					ghost->clearCompletedQuestsBit(i, false);
				}
				creature->sendSystemMessage("Cleared " + String::valueOf(questCrcs.size()) + " quests and " + String::valueOf(bitCount) + " bits. Relog to refresh client.");
			}
		} else if (cmdName == "setpilottier") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script setpilottier <tier>");
				return INVALIDPARAMETERS;
			}

			int tier = args.getIntToken();

			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
			if (ghost != nullptr) {
				ghost->setPilotTier(tier);
				creature->sendSystemMessage("Set pilot tier to: " + String::valueOf(tier));
			}
		} else if (cmdName == "setsquadron") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script setsquadron <squadronType>");
				return INVALIDPARAMETERS;
			}

			int squadron = args.getIntToken();

			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
			if (ghost != nullptr) {
				ghost->setPilotSquadron(squadron);
				creature->sendSystemMessage("Set squadron type to: " + String::valueOf(squadron));
			}
		} else if (cmdName == "setqueststatus") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script setqueststatus <key> <value>");
				return INVALIDPARAMETERS;
			}

			String key = "";
			args.getStringToken(key);

			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script setqueststatus <key> <value>");
				return INVALIDPARAMETERS;
			}

			String value = "";
			args.getStringToken(value);

			DirectorManager::instance()->setQuestStatus(key, value);

			creature->sendSystemMessage("Set quest status: " + key + " = " + value);
		} else if (cmdName == "removequeststatus") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script removequeststatus <key>");
				return INVALIDPARAMETERS;
			}

			String key = "";
			args.getStringToken(key);

			DirectorManager::instance()->removeQuestStatus(key);

			creature->sendSystemMessage("Removed quest status: " + key);
		} else if (cmdName == "luaevents") {
			if (!args.hasMoreTokens()) {
				creature->sendSystemMessage("SYNTAX: /script luaevents <oid>");
				return INVALIDPARAMETERS;
			}

			uint64 objID = args.getLongToken();

			ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objID);

			if (obj == nullptr) {
				creature->sendSystemMessage("Invalid object.");
				return INVALIDPARAMETERS;
			}

			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

			if (ghost == nullptr)
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

				if (task == nullptr)
					continue;

				String buffer = task->getScreenPlay() + ":" + task->getTaskKey();
				String args = task->getArgs();

				if (args != "")
					buffer += " (Args: " + args + ")";

				AtomicTime nextExecutionTime;
				Core::getTaskManager()->getNextExecutionTime(task, nextExecutionTime);
				int64 miliDiff = nextExecutionTime.miliDifference();

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
