/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

	int commandGroup;

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
	const static int INVALIDSYNTAX = 13;
	const static int TOOCLOSE = 14;


	virtual ~QueueCommand() {
	}

	/*
	 * Checks each invalid locomotion with the player's current locomotion
	 */
	bool checkInvalidLocomotions(CreatureObject* creature) const;

	void onStateFail(CreatureObject* creature, uint32 actioncntr) const;
	void onLocomotionFail(CreatureObject* creature, uint32 actioncntr) const;

	/**
	 * Gets a string describing this commands syntax usage.
	 */
	virtual String getSyntax() const {
		return String("");
	}

	/*
	 * Unsuccessful command completion alerts the player of the invalid state, must clear the queue action from client queue
	 */
	virtual void onFail(uint32 actioncntr, CreatureObject* creature, uint32 errorNumber) const;

	/*
	 * Successful command completion, must clear the queue action from client queue
	 */
	virtual void onComplete(uint32 actioncntr, CreatureObject* creature, float commandDuration) const;

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
	virtual int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const = 0;

	/*
	 * Checks all states at once with a bitwise operation
	 */
	bool checkStateMask(CreatureObject* creature) const {
		return (creature->getStateBitmask() & stateMask) == 0;
	}

	/**
	 * Returns duration of the command
	 */

	virtual float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
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

	inline void setCommandGroup(int val) {
		commandGroup = val;
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
	inline uint64 getStateMask() const {
		return stateMask;
	}

	inline bool requiresAdmin() const {
		return admin;
	}

	/*inline int getTarget() {
		return target;
	}*/

	inline int getTargetType() const {
		return targetType;
	}

	inline uint32 getNameCRC() const {
		return nameCRC;
	}

	inline float getMaxRange() const {
		return maxRangeToTarget;
	}

	inline const String& getQueueCommandName() const {
		return name;
	}

	inline const String& getCharacterAbility() const {
		return characterAbility;
	}

	inline float getDefaultTime() const {
		return defaultTime;
	}

	inline int getDefaultPriority() const {
		return defaultPriority;
	}

	/*
	 * @return True if the command has been disabled by the admins
	 */
	bool isDisabled() const {
		return disabled;
	}

	/*
	 * @return True if the command is supposed to be added to the combat queue.
	 */
	bool addToCombatQueue() const {
		return addToQueue;
	}

	virtual bool isCombatCommand() {
		return false;
	}

	virtual bool isForceHealCommand() {
		return false;
	}

	virtual bool isJediQueueCommand() {
		return false;
	}

	inline int getSkillModSize() const {
		return skillMods.size();
	}

	inline int getSkillMod(int index, String& skillMod) {
		skillMod = skillMods.elementAt(index).getKey();
		return skillMods.get(skillMod);
	}

	inline int getCommandGroup() const {
		return commandGroup;
	}

	void addSkillMod(const String& skillMod, const int value) {
		skillMods.put(skillMod, value);
	}
	
	bool isWearingArmor(CreatureObject* creo) const {
		for (int i = 0; i < creo->getSlottedObjectsSize(); ++i) {
			SceneObject* item = creo->getSlottedObject(i);
			if (item != NULL && item->isArmorObject())
				return true;
		}

		return false;
	}

	virtual void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {
	}

	int doCommonMedicalCommandChecks(CreatureObject* creature) const;

	void checkForTef(CreatureObject* creature, CreatureObject* target) const;
};


}
}
}
}
}

using namespace server::zone::objects::creature::commands;

#endif //SLASHCOMMAND_H_


