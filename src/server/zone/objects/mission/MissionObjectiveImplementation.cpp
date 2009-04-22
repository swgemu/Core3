#include "MissionObjective.h"
#include "MissionObjectiveImplementation.h"

MissionObjectiveImplementation::MissionObjectiveImplementation(String serialized) : MissionObjectiveServant() {
	init();

	deserializeObjective(serialized, true);
}

MissionObjectiveImplementation::~MissionObjectiveImplementation() {
}

void MissionObjectiveImplementation::init() {
	//Objective Completion Conditions (for serialization)
	targetCrc = 0;
	var = 0;
	limit = 0;
	strVar = "null";
	isFailureObjective = false;

	//Objective Status Vars:
	m_hasFailed = false;
	m_hasCompleted = false;
	objectiveType = 0;
	serialized = "";
}

/**
 * checkObjectiveStatus updates the m_hasFailed and isComplete booleans.
 * Checks completion and failure conditions after deserialization
 * Programmer should call isComplete() or hasFailed() after this is run.
 */
void MissionObjectiveImplementation::checkObjectiveStatus() {
	bool conditionMet = false;
	m_hasFailed = false;
	m_hasCompleted = false;

	if(var >= limit)
		conditionMet = true;

	if(conditionMet) {
		if(isFailureObjective)
			m_hasFailed = true;
		else
			m_hasCompleted = true;
	}
}

/**
 * Formats objective into the correct serialization string for storage
 */
String& MissionObjectiveImplementation::serializeObjective() {
	serialized = String::valueOf(objectiveType) + ":" + String::valueOf(targetCrc) + ":" + String::valueOf(var) + ":" + String::valueOf(limit) + ":";
	serialized += strVar + ":";
	if(isFailureObjective)
		serialized += String::valueOf(1);
	else
		serialized += String::valueOf(0);
	return serialized;
}

/**
 * Takes a serialized objective string breaks it into the correct completion conditions. Returns true if string is formatted correctly.
 * \param setThis Sets the variables pulled from the serialized string as the completion conditions for this objective object
 */
bool MissionObjectiveImplementation::deserializeObjective(String localTemp, bool setThis) {
	bool success = true;
	int idx = 0;
	// Parse objective limiteters. ex. 1:23232:0:32:null:1 (objective type:crc:var:limit:strVar:failure flag)

	StringTokenizer localTok(localTemp);
	localTok.setDelimeter(":");

	int tType = 0, tFail = 0;
	uint32 tCrc = 0;
	int tVar = 0, tlimit = 0;
	String tStr;

	// This is just to check if the limiteters were formatted correctly
	while(localTok.hasMoreTokens()) {
		if(idx == 0)
			tType = localTok.getIntToken();
		else if(idx == 1)
			tCrc = localTok.getIntToken();
		else if(idx == 2)
			tVar = localTok.getLongToken();
		else if(idx == 3)
			tlimit = localTok.getLongToken();
		else if(idx == 4)
			localTok.getStringToken(tStr);
		else
			tFail = localTok.getIntToken();

		idx++;
	}

	if(idx != 6) {
		System::out << "MissionObjectiveImpl: objective limiter count mismatch[" << idx << "]" << endl;
		success = false;
	}

	if(setThis && success) {
		objectiveType = tType;
		targetCrc = tCrc;
		var = tVar;
		limit = tlimit;
		strVar = tStr;
		if(tFail == 1)
			isFailureObjective = true;
		else
			isFailureObjective = false;

		checkObjectiveStatus();
	}

	return success;
}
