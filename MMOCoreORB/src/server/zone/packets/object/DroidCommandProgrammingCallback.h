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

		Locker clock(datapad, player);

#ifdef DEBUG_DROID_COMMAND
		player->info(true) << "DroidCommandProgrammingCallback::run ---- called";
#endif // DEBUG_DROID_COMMAND

		// Remove Memory modules
		for (int i = modulesToRemove.size() - 1; i >= 0 ; --i) {
#ifdef DEBUG_DROID_COMMAND
			player->info(true) << "Attempting to Remove Command #" << i << " Name: " << modulesToRemove.get(i);
#endif // DEBUG_DROID_COMMAND

			auto module = zoneServer->getObject(modulesToRemove.get(i));

			if (module == nullptr) {
				continue;
			}

			Locker modLock(module, datapad);

			datapad->removeObject(module, nullptr, true);

			module->destroyObjectFromWorld(true);
			module->destroyObjectFromDatabase(true);
#ifdef DEBUG_DROID_COMMAND
			player->info(true) << "Module: " << module->getDisplayedName() << " removed";
#endif // DEBUG_DROID_COMMAND
		}

		int capacity = petControlDevice->getDataStorageCapacity();

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

		auto inventory = player->getInventory();

		if (inventory == nullptr) {
			return;
		}

		// Add memory modules
		for (int i = 0; i < modulesToAdd.size(); i++) {
			auto programmedModule = zoneServer->getObject(modulesToAdd.get(i));

			if (programmedModule == nullptr || programmedModule->getGameObjectType() != SceneObjectType::DROIDPROGRAMMINGCHIP) {
				continue;
			}

			// TODO: Add from programmed module
			addModuleFromInventory();
		}
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

		permissions->setInheritPermissionsFromParent(true);
		permissions->clearDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
		permissions->clearDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

		datapad->broadcastObject(commandModule, true);
	}

	void addModuleFromInventory() {

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

#ifdef DEBUG_DROID_COMMAND
		info(true) << "hasSpaceForCommand -- Capacity: " << capacity << " Current Data Size: " << currentDataSize << " Container Size: " << containerSize;
#endif // DEBUG_DROID_COMMAND

		return currentDataSize <= capacity;
	}
};

#endif // DROIDCOMMANDPROGRAMMINGCALLBACK_H_
