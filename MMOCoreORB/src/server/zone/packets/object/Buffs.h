/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BUFFS_H_
#define BUFFS_H_

#include "ObjectControllerMessage.h"

class AddBuffMessage : public ObjectControllerMessage {
public:
	/**
	 * Adds the buff to the player's buff window.
	 * @param player {PlayerCreature} The player to add this buff to.
	 * @param buffcrc {uint32} The crc of the buff to add.
	 * @param duration {float} The duration of the buff in seconds.
	 * @return {AddBuffMessage} The add buff message..
	 */
	AddBuffMessage(SceneObject* player, uint32 buffcrc, float duration)
			: ObjectControllerMessage(player->getObjectID(), 0x1B, 0x229, false) {

		insertInt(buffcrc);
		insertFloat(duration);
	}
};

class RemoveBuffMessage : public ObjectControllerMessage {
public:
	/**
	 * Removes a buff from a player's buff window.
	 * @param player {PlayerCreature} The player whom's buff should be removed.
	 * @param buffcrc {uint32} The crc of the buff to remove.
	 * @return {RemoveBuffMessage} The remove buff message.
	 */
	RemoveBuffMessage(CreatureObject* player, uint32 buffcrc)
			: ObjectControllerMessage(player->getObjectID(), 0x1B, 0x22A, false) {

		insertInt(buffcrc);
	}
};

#endif /*BUFFS_H_*/
