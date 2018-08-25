#include "server/zone/managers/frs/FrsManagerData.h"

void FrsManagerDataImplementation::updateChallengeTime(uint64 playerID) {
	Time current;
	challengeTimes.put(playerID, current);
}

bool FrsManagerDataImplementation::hasChallengedRecently(uint64 playerID, uint64 challengeCooldown) {
	if (!challengeTimes.contains(playerID))
		return false;

	if (getChallengeDuration(playerID) > challengeCooldown) {
		challengeTimes.drop(playerID);
		return false;
	}

	return true;
}

uint64 FrsManagerDataImplementation::getChallengeTime(uint64 playerID) {
	return challengeTimes.get(playerID).getMiliTime();
}

uint64 FrsManagerDataImplementation::getChallengeDuration(uint64 playerID) {
	return (Time().getMiliTime() - getChallengeTime(playerID));
}

void FrsManagerDataImplementation::updateDemoteTime(uint64 playerID) {
	Time current;
	demoteTimes.put(playerID, current);
}

bool FrsManagerDataImplementation::hasDemotedRecently(uint64 playerID, uint64 demoteCooldown) {
	if (!demoteTimes.contains(playerID))
		return false;

	if (getDemoteDuration(playerID) > demoteCooldown) {
		demoteTimes.drop(playerID);
		return false;
	}

	return true;
}

uint64 FrsManagerDataImplementation::getDemoteTime(uint64 playerID) {
	return demoteTimes.get(playerID).getMiliTime();
}

uint64 FrsManagerDataImplementation::getDemoteDuration(uint64 playerID) {
	return (Time().getMiliTime() - getDemoteTime(playerID));
}

