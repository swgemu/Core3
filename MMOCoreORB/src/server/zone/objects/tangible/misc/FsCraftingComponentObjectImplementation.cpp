#include "server/zone/objects/tangible/misc/FsCraftingComponentObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

void FsCraftingComponentObjectImplementation::destroyObjectFromWorld(bool sendSelfDestroy) {
	ManagedReference<CreatureObject*> strongOwner = getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if (strongOwner != NULL) {
		PlayerObject* ghost = strongOwner->getPlayerObject();

		if (ghost != NULL) {
			uint32 objCRC = getServerObjectCRC();
			int index = 0;

			if (objCRC == 0x3741D56F) // object/tangible/item/quest/force_sensitive/fs_craft_puzzle_config_processor.iff
				index = 1;
			else if (objCRC == 0x5909F8) // object/tangible/item/quest/force_sensitive/fs_craft_puzzle_gyro_receiver.iff
				index = 2;
			else if (objCRC == 0x3FA7B01) // object/tangible/item/quest/force_sensitive/fs_craft_puzzle_signal_amp.iff
				index = 3;
			else if (objCRC == 0x70035120) // object/tangible/item/quest/force_sensitive/fs_craft_puzzle_solid_state_array.iff
				index = 4;

			String analyzed = ghost->getScreenPlayData("SuiFsCrafting1Analyzer", "componentAnalyzed" + String::valueOf(index));

			if (analyzed == "" || analyzed == "0")
				ghost->setScreenPlayData("FsCrafting1", "accessTerminalStatus" + String::valueOf(index), "-1");
		}
	}

	TangibleObjectImplementation::destroyObjectFromWorld(sendSelfDestroy);
}
