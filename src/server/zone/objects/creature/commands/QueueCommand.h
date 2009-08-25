/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef QUEUECOMMAND_H_
#define QUEUECOMMAND_H_


#include "engine/engine.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreaturePosture.h"


#include "server/zone/ZoneProcessServerImplementation.h"
//#include "../../../managers/combat/CombatManager.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace commands {


class QueueCommand {
protected:
	String slashCommandName;
	uint32 nameCRC;

	uint32 animCRC;
	uint64 stateMask;
	Vector<int> invalidPostures;
	int target;
	int targetType;
	int maxRangeToTarget;

	bool disabled;
	bool addToQueue;

	uint32 cooldown; // in msec

	ZoneProcessServerImplementation* server;

public:
	QueueCommand(const String& name, ZoneProcessServerImplementation* serv) {
		server = serv;

		nameCRC = name.hashCode();

		slashCommandName = name;

		animCRC = 0;

		maxRangeToTarget = 0;

		stateMask = 0;
		target = 0;
		targetType = 0;
		disabled = false;
		addToQueue = false;

		cooldown = 0;
	}

	virtual ~QueueCommand() {
	}

	//setters
	inline void setAnimation(const String& ename) {
		animCRC = ename.hashCode();
	}

	/*
	 * Sets the invalid states for this command
	 */
	inline void setStateMask(uint64 mask) {
		stateMask = mask;
	}

	/*
	 * Sets the invalid postures for this command.
	 * Parses the string from LUA's. Format: "4,12,13,"
	 */
	void setInvalidPostures(const String& postureStr) {
		StringTokenizer tokenizer(postureStr);
		tokenizer.setDelimeter(",");

		String token = "";
		while (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(token);

			if(!token.isEmpty())
				invalidPostures.add(Integer::valueOf(token));
		}
	}

	inline void setTarget(int num) {
		target = num;
	}

	inline void setTargetType(int num) {
		targetType = num;
	}

	inline void setDisabled(bool state) {
		disabled = state;
	}

	inline void setDisabled(int state) {
		if (state == 0)
			disabled = false;
		else
			disabled = true;
	}

	inline void setAddToCombatQueue(bool state) {
		addToQueue = state;
	}

	inline void setAddToCombatQueue(int state) {
		if (state == 0)
			addToQueue = false;
		else
			addToQueue = true;
	}

	inline void setMaxRange(float r) {
		maxRangeToTarget = (int)r;
	}

	//getters
	inline uint64 getStateMask() {
		return stateMask;
	}

	inline int getTarget() {
		return target;
	}

	inline int getTargetType() {
		return targetType;
	}

	inline uint32 getNameCRC() {
		return nameCRC;
	}

	inline uint32 getAnimCRC() {
		return animCRC;
	}

	inline uint32 getAnimCRC(CreatureObject* creature, const String& actionModifier) {
		return animCRC;
	}

	inline float getMaxRange() {
		return maxRangeToTarget;
	}

	//misc
	bool hasAnimation() {
		return animCRC != 0;
	}

	/*
	 * @return True if the command has been disabled by the admins
	 */
	bool isDisabled() {
		return disabled;
	}

	/*
	 * @return True if the command is supposed to be added to the combat queue.
	 */
	bool addToCombatQueue() {
		return addToQueue;
	}

	/*
	 * Override me
	 */
	virtual bool doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		return false;
	}

	/*
	 * Checks all states at once with a bitwise operation
	 */
	bool checkStateMask(CreatureObject* creature) {
		return (creature->getStateBitmask() & stateMask) == 0;
	}

	/*
	 * Checks each invalid posture with the player's current posture
	 */
	bool checkInvalidPostures(CreatureObject* creature) {
		for (int i = 0; i < invalidPostures.size(); ++i) {
			if (invalidPostures.get(i) == creature->getPosture())
				return false;
		}
		return true;
	}

	/*
	 * Unsuccessful command completion alerts the player of the invalid state
	 */
	virtual void onFail(uint32 actioncntr, CreatureObject* creature) {
		uint64 states = stateMask & creature->getStateBitmask();

		if (!checkStateMask(creature)) {

			uint64 state = 1;
			int num = 0;

			while (num < 34) {
				if (states & state) {

					creature->clearQueueAction(actioncntr, 0, 5, num);
					return;

				}

				state *= 2;
				++num;
			}
		}

		/*
		 * SOE is stupid so player postures do NOT match up with their respective client error message
		 * Because of this, we have to have this switch statement to match them up manually
		 * */
		if (!checkInvalidPostures(creature)) {
			/*switch(player->getPosture()) {
			case(CreaturePosture::UPRIGHT):
				player->clearQueueAction(actioncntr, 0, 1, 0);
				break;
			case(CreaturePosture::CROUCHED):
				player->clearQueueAction(actioncntr, 0, 1, 4);
				break;
			case(CreaturePosture::PRONE):
				player->clearQueueAction(actioncntr, 0, 1, 7);
				break;
			case(CreaturePosture::SNEAKING):
				player->clearQueueAction(actioncntr, 0, 1, 5);
				break;
			case(CreaturePosture::BLOCKING):
				player->clearQueueAction(actioncntr, 0, 1, 21);
				break;
			case(CreaturePosture::CLIMBING):
				player->clearQueueAction(actioncntr, 0, 1, 10);
				break;
			case(CreaturePosture::FLYING):
				player->clearQueueAction(actioncntr, 0, 1, 12);
				break;
			case(CreaturePosture::LYINGDOWN):
				player->clearQueueAction(actioncntr, 0, 1, 13);
				break;
			case(CreaturePosture::SITTING):
				player->clearQueueAction(actioncntr, 0, 1, 14);
				break;
			case(CreaturePosture::SKILLANIMATING):
				player->clearQueueAction(actioncntr, 0, 1, 15);
				break;
			case(CreaturePosture::DRIVINGVEHICLE):
				player->clearQueueAction(actioncntr, 0, 1, 16);
				break;
			case(CreaturePosture::RIDINGCREATURE):
				player->clearQueueAction(actioncntr, 0, 1, 17);
				break;
			case(CreaturePosture::KNOCKEDDOWN):
				player->clearQueueAction(actioncntr, 0, 1, 18);
				break;
			case(CreaturePosture::INCAPACITATED):
				player->clearQueueAction(actioncntr, 0, 1, 19);
				break;
			case(CreaturePosture::DEAD):
				player->clearQueueAction(actioncntr, 0, 1, 20);
				break;
			default:
				player->clearQueueAction(actioncntr);
				break;
			}*/
		}
	}

	/*
	 * Successful command completion
	 */
	virtual void onComplete(uint32 actioncntr, CreatureObject* player) {

	}

	inline String& getSlashCommandName() {
		return slashCommandName;
	}

};


}
}
}
}
}

using namespace server::zone::objects::creature::commands;

#endif //SLASHCOMMAND_H_

