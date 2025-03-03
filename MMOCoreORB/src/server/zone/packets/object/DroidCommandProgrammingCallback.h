/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef DROIDCOMMANDPROGRAMMINGCALLBACK_H_
#define DROIDCOMMANDPROGRAMMINGCALLBACK_H_

#include "ObjectControllerMessageCallback.h"

class DroidCommandProgrammingCallback : public MessageCallback {
protected:
	ObjectControllerMessageCallback* objectControllerMain;

	Vector<String> chipCommands;
	Vector<uint64> chipsToAdd;
	Vector<uint64> chipsToRemove;
	uint64 droidControlID;

public:
	DroidCommandProgrammingCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()), objectControllerMain(objectControllerCallback), droidControlID(0) {
		Logger::console.info(true) << "DroidCommandProgrammingCallback --- ctor called";

	}

	void parse(Message* message) {
		Logger::console.info(true) << "Raw Message: " << message->toStringData();

		// Ignore int?
		//message->parseInt();

		//message->shiftOffset(12);

		uint64 playerID = message->parseLong();

		Logger::console.info(true) << "Player ID: " << playerID;


		int commandSize = message->parseInt();

		Logger::console.info(true) << "DroidCommandProgrammingCallback::parse ---- Command Size: " << commandSize;

		for (int i = 0; i < commandSize; ++i) {
			String command = "";
			message->parseAscii(command);

			Logger::console.info(true) << "DroidCommandProgrammingCallback -- parse Command #" << i << " Name: " << command;

			chipCommands.add(command);
		}

		int addSize = message->parseInt();

		Logger::console.info(true) << "DroidCommandProgrammingCallback::parse ---- Add size: " << addSize;

		for (int i = 0; i < addSize; ++i) {
			uint64 commandID = message->parseLong();

			Logger::console.info(true) << "DroidCommandProgrammingCallback -- parse Add #" << i << " Command ID: " << commandID;

			chipsToAdd.add(commandID);
		}

		int dropSize = message->parseInt();

		Logger::console.info(true) << "DroidCommandProgrammingCallback::parse ---- Drop size: " << dropSize;

		for (int i = 0; i < dropSize; ++i) {
			uint64 commandID = message->parseLong();

			Logger::console.info(true) << "DroidCommandProgrammingCallback -- parse Drop #" << i << " Command ID: " << commandID;

			chipsToRemove.add(commandID);
		}

		droidControlID = message->parseLong();

		Logger::console.info(true) << "DroidCommandProgrammingCallback -- droidControlID: " << droidControlID;
	}

	void run() {
		Logger::console.info(true) << "test 1";

		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr) {
			return;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		Locker lock(player);

		player->info(true) << "DroidCommandProgrammingCallback::run ---- called";

		// TODO: verify and add the droid commands to the droid here
	}
};

#endif // DROIDCOMMANDPROGRAMMINGCALLBACK_H_
