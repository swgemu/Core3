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

		// TODO: verify and add the droid commands to the droid datapad here


		/* String -- @space/droid_commands
			"droid_command_datapad_room", "You can fit %DI more programs into the datapad.");
			"droid_command_datapad_roomleft", "You can fit %DI more units of programs.");
			"droid_command_datapad_room_nfull", "This datapad is now full, and can not accept any more droid programs.");
			"droid_command_datapad_room_single", "You can fit one more program into this datapad.");
			"droid_command_delete", "To remove droid commands from a droid or flight computer, you must destroy them.");
			"droid_command_full", "Your droid's datapad is full.");
			"droid_command_not_enough_room", "There isn't enough memory in your datapad to store this program.");
			"droid_command_programmed", "Command has been transferred to your droid.");
			"droid_command_programmed_already", "This program is already programmed, and cannot be loaded a second time.");
			"droid_command_programmed_flightcomputer", "Command has been transferred to your flight computer.");
		*/
	}
};

#endif // DROIDCOMMANDPROGRAMMINGCALLBACK_H_
