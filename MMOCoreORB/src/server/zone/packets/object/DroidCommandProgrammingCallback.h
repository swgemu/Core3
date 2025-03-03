/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#ifndef DROIDCOMMANDPROGRAMMINGCALLBACK_H_
#define DROIDCOMMANDPROGRAMMINGCALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"

#define DEBUG_DROID_COMMAND

class DroidCommandProgrammingCallback : public MessageCallback {
protected:
	ObjectControllerMessageCallback* objectControllerMain;

	Vector<String> commandsToAdd;
	Vector<uint64> modulesToAdd;
	Vector<uint64> modulesToRemove;
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

			commandsToAdd.add(command);
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

			modulesToAdd.add(commandID);
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

			modulesToRemove.add(commandID);
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

		auto ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr) {
			return;
		}

		auto skillManager = zoneServer->getSkillManager();

		if (skillManager == nullptr) {
			return;
		}

		Locker lock(player);

		auto deviceSceneO = zoneServer->getObject(controlDeviceID);

		if (deviceSceneO == nullptr || !deviceSceneO->isPetControlDevice()) {
			return;
		}

		auto petControlDevice = deviceSceneO.castTo<PetControlDevice*>();

		if (petControlDevice == nullptr) {
			return;
		}

		auto datapad = petControlDevice->getDatapad();

		if (datapad == nullptr) {
			return;
		}

		auto droid = cast<DroidObject*>(petControlDevice->getControlledObject());

		if (droid == nullptr) {
			return;
		}

		Locker clock(datapad, player);

#ifdef DEBUG_DROID_COMMAND
		player->info(true) << "DroidCommandProgrammingCallback::run ---- called";
#endif // DEBUG_DROID_COMMAND

		// Remove Memory modules
		for (int i = 0; i < modulesToRemove.size(); i++) {

		}

		int capacity = droid->getDataStorageCapacity();

		// Add Commands
		for (int i = 0; i < commandsToAdd.size(); i++) {
			const String command = commandsToAdd.get(i);

#ifdef DEBUG_DROID_COMMAND
			player->info(true) << "Attempting to Add Command #" << i << " Name: " << command;
#endif // DEBUG_DROID_COMMAND

			if (command.isEmpty() || !ghost->hasAbility(command)) {
				continue;
			}

			auto ability = skillManager->getAbility(command);

			if (ability == nullptr) {
				continue;
			}

			if (hasCommand(datapad, ability->getAbilityName())) {
				player->sendSystemMessage("@space/droid_commands:droid_command_programmed_already"); // "This program is already programmed, and cannot be loaded a second time."
				continue;
			}

			int dataSize = skillManager->getDroidProgramSize(command.hashCode());

			if (!hasSpaceForCommand(datapad, capacity, dataSize)) {
				player->sendSystemMessage("@space/droid_commands:droid_command_full"); // "Your droid's datapad is full."

				break;
			}

			addCommand(zoneServer, datapad, ability, dataSize);
		}

		// Add memory modules
		for (int i = 0; i < modulesToAdd.size(); i++) {

		}

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

	void removeModules() {

	}

	void addCommand(ZoneServer* zoneServer, SceneObject* datapad, Ability* ability, float dataSize) {
		if (zoneServer == nullptr || datapad == nullptr || ability == nullptr) {
			return;
		}

		String commandTemplate = "object/intangible/data_item/droid_command.iff";

		auto commandModule = zoneServer->createObject(commandTemplate.hashCode(), 1).castTo<IntangibleObject*>();

		if (commandModule == nullptr) {
			return;
		}

		Locker modLock(commandModule, datapad);

		// Set the module name
		String commandName = ability->getAbilityName();
		String moduleName = "@space/droid_commands:" + commandName + "_chipname";

		commandModule->setCustomObjectName(StringIdManager::instance()->getStringId(moduleName.hashCode()), false);

		// Set the Size of the module
		commandModule->setDataSize(dataSize, false);
		commandModule->updateStatus(1, false);
		commandModule->setItemIdentifier(commandName, false);

		if (!datapad->transferObject(commandModule, -1)) {
			datapad->error() << "Failed to transfer Space Command Intangible into Droid Datapad ID: " << datapad->getObjectID();
			return;
		}

		ContainerPermissions* permissions = commandModule->getContainerPermissionsForUpdate();
		permissions->setDefaultAllowPermission(ContainerPermissions::MOVECONTAINER);

		//permissions->setAllowPermission("owner", ContainerPermissions::MOVECONTAINER);

		datapad->broadcastObject(commandModule, true);

	}

	void addModules() {

	}

	bool hasCommand(SceneObject* datapad, String commandName) {
		if (datapad == nullptr) {
			return false;
		}

		int containerSize = datapad->getContainerObjectsSize();

		for (int i = 0; i < containerSize; i++) {
			auto commandModule = datapad->getContainerObject(i).castTo<IntangibleObject*>();

			if (commandModule == nullptr || commandModule->getItemIdentifier() != commandName) {
				continue;
			}

			return true;
		}

		return false;
	}

	bool hasSpaceForCommand(SceneObject* datapad, int capacity, int commandSize) {
		if (datapad == nullptr) {
			return false;
		}

		int containerSize = datapad->getContainerObjectsSize();
		int currentDataSize = commandSize;

		for (int i = 0; i < containerSize; i++) {
			auto commandModule = datapad->getContainerObject(i).castTo<IntangibleObject*>();

			if (commandModule == nullptr) {
				continue;
			}

			currentDataSize += commandModule->getDataSize();
		}

		return currentDataSize < capacity;
	}
};

#endif // DROIDCOMMANDPROGRAMMINGCALLBACK_H_
