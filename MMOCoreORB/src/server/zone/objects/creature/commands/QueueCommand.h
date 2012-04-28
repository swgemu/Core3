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
#include "server/zone/objects/creature/CreatureLocomotion.h"


#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/creature/variables/Skill.h"
//#include "../../../managers/combat/CombatManager.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace commands {


class QueueCommand : public Logger, public Object {
protected:
	ZoneProcessServer* server;

	String name;
	uint32 nameCRC;

	uint64 stateMask;
	Vector<int> invalidLocomotion;
	//int target;
	int targetType;
	int maxRangeToTarget;

	bool disabled;
	bool addToQueue;
	bool admin;

	uint32 cooldown; // in msec

	float defaultTime;

	String characterAbility;

	int defaultPriority;

	VectorMap<String, int> skillMods;

public:
	QueueCommand(const String& skillname, ZoneProcessServer* serv);

	const static int IMMEDIATE = 0;
	const static int FRONT = 1;
	const static int NORMAL = 2;

	const static int SUCCESS = 0;
	const static int GENERALERROR = 1;
	const static int INVALIDLOCOMOTION = 2;
	const static int INVALIDSTATE = 3;
	const static int INVALIDTARGET = 4;
	const static int INVALIDWEAPON = 5;
	const static int TOOFAR = 6;
	const static int INSUFFICIENTHAM = 7;
	const static int INVALIDPARAMETERS = 8;
	const static int NOPRONE = 9;
	const static int NOKNEELING = 10;
	const static int INSUFFICIENTPERMISSION = 11;
	const static int NOJEDIARMOR = 12;


	virtual ~QueueCommand() {
	}

	/*
	 * Checks each invalid locomotion with the player's current locomotion
	 */
	bool checkInvalidLocomotions(CreatureObject* creature);

	void onStateFail(CreatureObject* creature, uint32 actioncntr);
	void onLocomotionFail(CreatureObject* creature, uint32 actioncntr);

	/*
	 * Unsuccessful command completion alerts the player of the invalid state, must clear the queue action from client queue
	 */
	virtual void onFail(uint32 actioncntr, CreatureObject* creature, uint32 errorNumber);

	/*
	 * Successful command completion, must clear the queue action from client queue
	 */
	virtual void onComplete(uint32 actioncntr, CreatureObject* creature, float commandDuration);

	/*
	 * Sets the invalid locomotions for this command.
	 * Parses the string from LUA's. Format: "4,12,13,"
	 */
	void setInvalidLocomotions(const String& lStr);

	/*
	 * adds an invalid locomotion
	 */
	void addInvalidLocomotion(int l) {
		invalidLocomotion.add(l);
	}

	/*
	 * Override me
	 */
	virtual int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		return SUCCESS;
	}

	/*
	 * Checks all states at once with a bitwise operation
	 */
	bool checkStateMask(CreatureObject* creature) {
		return (creature->getStateBitmask() & stateMask) == 0;
	}

	/**
	 * Returns duration of the command
	 */

	virtual float getCommandDuration(CreatureObject* object) {
		// TODO: modify this value by skill, probably need to specify which skill affects what in luas
		return defaultTime;
	}

	//setters

	/*
	 * Sets the invalid states for this command
	 */
	inline void setStateMask(uint64 mask) {
		stateMask = mask;
	}



	/*inline void setTarget(int num) {
		target = num;
	}*/

	inline void setDefaultTime(float time) {
		defaultTime = time;
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

	inline void setCharacterAbility(const String& ability) {
		characterAbility = ability;

		if(ability == "admin")
			admin = true;
	}

	inline void setDefaultPriority(const String& priority) {
		if (priority == "immediate")
			defaultPriority = IMMEDIATE;
		else if (priority == "normal")
			defaultPriority = NORMAL;
		else if (priority == "front")
			defaultPriority = FRONT;
		else
			System::out << "Setting unknown priority " << priority << endl;
	}

	inline void setDefaultPriority(const int priority) {
		if (priority < 0 || priority > 2)
			System::out << "Setting unknown priority " << priority << endl;
		else
			defaultPriority = priority;
	}

	//getters
	inline uint64 getStateMask() {
		return stateMask;
	}

	inline bool requiresAdmin() {
		return admin == true;
	}

	/*inline int getTarget() {
		return target;
	}*/

	inline int getTargetType() {
		return targetType;
	}

	inline uint32 getNameCRC() {
		return nameCRC;
	}

	inline float getMaxRange() {
		return maxRangeToTarget;
	}

	inline String& getQueueCommandName() {
		return name;
	}

	inline String& getCharacterAbility() {
		return characterAbility;
	}

	inline float getDefaultTime() {
		return defaultTime;
	}

	inline int getDefaultPriority() {
		return defaultPriority;
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

	virtual bool isCombatCommand() {
		return false;
	}

	inline int getSkillModSize() {
		return skillMods.size();
	}

	inline int getSkillMod(int index, String& skillMod) {
		skillMod = skillMods.elementAt(index).getKey();
		return skillMods.get(skillMod);
	}

	void addSkillMod(const String& skillMod, const int value) {
		skillMods.put(skillMod, value);
	}
	
	bool isWearingArmor(CreatureObject* creo) {
		for (int i = 0; i < creo->getSlottedObjectsSize(); ++i) {
			SceneObject* item = creo->getSlottedObject(i);
			if (item != NULL && item->isArmorObject())
				return true;
		}

		return false;
	}

	virtual void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {
	}
};


}
}
}
}
}

using namespace server::zone::objects::creature::commands;

#endif //SLASHCOMMAND_H_


