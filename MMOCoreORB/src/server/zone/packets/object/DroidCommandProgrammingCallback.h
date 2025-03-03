/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef DROIDCOMMANDPROGRAMMINGCALLBACK_H_
#define DROIDCOMMANDPROGRAMMINGCALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

#define DEBUG_DROID_COMMAND

class DroidCommandProgrammingCallback : public MessageCallback {
protected:
	ObjectControllerMessageCallback* objectControllerMain;

	Vector<String> chipCommands;
	Vector<uint64> chipsToAdd;
	Vector<uint64> chipsToRemove;
	uint64 controlDeviceID;

public:
	DroidCommandProgrammingCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()), objectControllerMain(objectControllerCallback), controlDeviceID(0) {
	}

	void parse(Message* message) {
#ifdef DEBUG_DROID_COMMAND
		Logger::console.info(true) << "DroidCommandProgrammingCallback -- Raw Message: " << message->toStringData();
#endif // DEBUG_DROID_COMMAND

		// Skip int buffer
		message->shiftOffset(4);

		int commandSize = message->parseInt();

#ifdef DEBUG_DROID_COMMAND
		Logger::console.info(true) << "DroidCommandProgrammingCallback::parse ---- Command Size: " << commandSize;
#endif // DEBUG_DROID_COMMAND

		for (int i = 0; i < commandSize; ++i) {
			String command = "";
			message->parseAscii(command);

#ifdef DEBUG_DROID_COMMAND
			Logger::console.info(true) << "DroidCommandProgrammingCallback -- parse Command #" << i << " Name: " << command;
#endif // DEBUG_DROID_COMMAND

			chipCommands.add(command);
		}

		int addSize = message->parseInt();

#ifdef DEBUG_DROID_COMMAND
		Logger::console.info(true) << "DroidCommandProgrammingCallback::parse ---- Add size: " << addSize;
#endif // DEBUG_DROID_COMMAND

		for (int i = 0; i < addSize; ++i) {
			uint64 commandID = message->parseLong();

#ifdef DEBUG_DROID_COMMAND
			Logger::console.info(true) << "DroidCommandProgrammingCallback -- parse Add #" << i << " Command ID: " << commandID;
#endif // DEBUG_DROID_COMMAND

			chipsToAdd.add(commandID);
		}

		int dropSize = message->parseInt();

#ifdef DEBUG_DROID_COMMAND
		Logger::console.info(true) << "DroidCommandProgrammingCallback::parse ---- Drop size: " << dropSize;
#endif // DEBUG_DROID_COMMAND

		for (int i = 0; i < dropSize; ++i) {
			uint64 commandID = message->parseLong();

#ifdef DEBUG_DROID_COMMAND
			Logger::console.info(true) << "DroidCommandProgrammingCallback -- parse Drop #" << i << " Command ID: " << commandID;
#endif // DEBUG_DROID_COMMAND

			chipsToRemove.add(commandID);
		}

		controlDeviceID = message->parseLong();

#ifdef DEBUG_DROID_COMMAND
		Logger::console.info(true) << "DroidCommandProgrammingCallback -- controlDeviceID: " << controlDeviceID;
#endif // DEBUG_DROID_COMMAND
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr) {
			return;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		auto deviceSceneO = zoneServer->getObject(controlDeviceID);

		if (deviceSceneO == nullptr || !deviceSceneO->isPetControlDevice()) {
			return;
		}

		auto petControlDevice = deviceSceneO.castTo<PetControlDevice*>();

		if (petControlDevice == nullptr) {
			return;
		}

		Locker lock(player);

#ifdef DEBUG_DROID_COMMAND
		player->info(true) << "DroidCommandProgrammingCallback::run ---- called";
#endif // DEBUG_DROID_COMMAND

		// TODO: verify and add the droid commands to the droid here
	}
};

#endif // DROIDCOMMANDPROGRAMMINGCALLBACK_H_
