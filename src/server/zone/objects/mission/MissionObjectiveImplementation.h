#ifndef MISSIONOBJECTIVEIMPLEMENTATION_H_
#define MISSIONOBJECTIVEIMPLEMENTATION_H_

#include "engine/engine.h"

class MissionObjectiveImplementation : public MissionObjectiveServant {
	//Objective Completion Conditions (for serialization)
	uint32 targetCrc;
	int var;
	int limit;
	String strVar;
	bool isFailureObjective;

	//Objective Status Vars:
	bool m_hasFailed;
	bool m_hasCompleted;
	int objectiveType;
	String serialized;

public:
	/**
	 * Client must meet kill criteria
	 * objectCrc - obj crc of creature to kill
	 * var - client kill count
	 * limit - kill limit
	 * strVar, optional, name of creature to kill
	 */
	const static int HAS_KILLS = 1;

	/**
	 * Client was killed in action
	 * objectCrc - optional, objCrc of creature that kills the client
	 * var - client death count
	 * limit - client death limit
	 * strVar - optional, name of killer
	 */
	const static int WAS_KIA = 2;

	/**
	 * Client delivered item(s) in criteria
	 * objectCrc - objcrc of required item
	 * var - number of certain item
	 * limit - number to complete condition
	 * strVar - optional, name of item
	 */
	const static int HAS_ITEMS = 4;

public:
	//MissionObjectiveImplementation::MissionObjectiveImplementation();
	MissionObjectiveImplementation::MissionObjectiveImplementation(String serialized);
	MissionObjectiveImplementation::~MissionObjectiveImplementation();

	void init();

	/**
	 * Objective Status Functions
	 */

	void setObjectiveType(int ot) {
		objectiveType = ot;
	}

	int getObjectiveType() {
		return objectiveType;
	}

	bool hasFailed() {
		return m_hasFailed;
	}

	bool hasCompleted() {
		return m_hasCompleted;
	}

	/**
	 * Objective Completion Condition Updates
	 */

	inline void setTargetCrc(int oc) {
		targetCrc = oc;
	}

	inline uint32 getTargetCrc() {
		return targetCrc;
	}

	inline void setIsFailure(bool isf) {
		isFailureObjective = isf;
	}

	inline void incrementVar(int increment) {
		var+=increment;
	}

	inline int getVar() {
		return var;
	}

	inline void setLimit(int lm) {
		limit = lm;
	}

	inline int getLimit() {
		return limit;
	}

	void setStrVar(const String& str) {
		strVar = str;
	}

	inline String& getStrVar() {
		return strVar;
	}

	void checkObjectiveStatus();

	/**
	 * Serialization Functions
	 * Mission Objective Objects should be creatable from a serialzed string. No var in the MissionObjective should exist that cannot be recreated
	 * from within LUA script (like a memory reference)
	 */

	String& serializeObjective();
	bool deserializeObjective(String localTemp, bool setThis);
};

#endif
