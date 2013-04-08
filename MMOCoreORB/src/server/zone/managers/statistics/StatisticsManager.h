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

#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/mission/MissionObject.h"

class StatisticsManager : public Singleton<StatisticsManager>, public Logger, public Object {
	AtomicLong numberOfCompletedMissionsBounty;
	AtomicLong numberOfCompletedMissionsCrafting;
	AtomicLong numberOfCompletedMissionsDancer;
	AtomicLong numberOfCompletedMissionsDeliver;
	AtomicLong numberOfCompletedMissionsDestroy;
	AtomicLong numberOfCompletedMissionsHunting;
	AtomicLong numberOfCompletedMissionsMusician;
	AtomicLong numberOfCompletedMissionsRecon;
	AtomicLong numberOfCompletedMissionsSurvey;
	AtomicLong creditsGeneratedFromMissionsBounty;
	AtomicLong creditsGeneratedFromMissionsCrafting;
	AtomicLong creditsGeneratedFromMissionsDancer;
	AtomicLong creditsGeneratedFromMissionsDeliver;
	AtomicLong creditsGeneratedFromMissionsDestroy;
	AtomicLong creditsGeneratedFromMissionsHunting;
	AtomicLong creditsGeneratedFromMissionsMusician;
	AtomicLong creditsGeneratedFromMissionsRecon;
	AtomicLong creditsGeneratedFromMissionsSurvey;
	AtomicLong charactersDeletedByUser;

	//stats for character deletion in packet handler
	AtomicLong charactersMovedToDeletedTable;  // chracters moved to teh characters_deleted table
	AtomicLong characterMoveErrors;  // errors moving character from char to delted_char table
	AtomicLong deleteTasksRun;
	AtomicLong characterUpdateCount;
	AtomicLong characterInsertErrors;
	AtomicLong characterMoveExceptions;

	// from delete character task
	AtomicLong charactersDestroyedFromWorld;   // characters destroybojectfromworld
	AtomicLong charactersDestroyedFromDatabase; // characters destroyobjectfromdatabase
	AtomicLong deleteCharacterTaskErrors;
	AtomicLong deleteCharacterTaskExceptions;

public:
	const static int CHARACTERDELETEDBYUSER = 0;
	const static int CHARACTERMOVED = 1;
	const static int CHARACTERDESTROYEDFROMWORLD = 2;
	const static int CHARACTERDESTROYEDFROMDATABASE = 3;
	const static int TASKERRORS = 4;
	const static int TASKEXCEPTIONS = 5;
	const static int TASKRUN = 6;

	const static int CHARACTERMOVEEXCEPTION = 7;
	const static int CHARACTERMOVEERROR = 8;
	const static int CHARACTUREUPDATES = 9;
	const static int CHARACTERINSERTERROR = 10;


	StatisticsManager() : Logger("Statistics Manager") {
		reset();
		resetCharacterStatistics();
	}

	void completeMission(unsigned int missionType, int reward) {
		switch (missionType) {
		case MissionObject::BOUNTY:
			numberOfCompletedMissionsBounty.increment();
			creditsGeneratedFromMissionsBounty.add(reward);
			break;
		case MissionObject::CRAFTING:
			numberOfCompletedMissionsCrafting.increment();
			creditsGeneratedFromMissionsCrafting.add(reward);
			break;
		case MissionObject::DANCER:
			numberOfCompletedMissionsDancer.increment();
			creditsGeneratedFromMissionsDancer.add(reward);
			break;
		case MissionObject::DELIVER:
			numberOfCompletedMissionsDeliver.increment();
			creditsGeneratedFromMissionsDeliver.add(reward);
			break;
		case MissionObject::DESTROY:
			numberOfCompletedMissionsDestroy.increment();
			creditsGeneratedFromMissionsDestroy.add(reward);
			break;
		case MissionObject::HUNTING:
			numberOfCompletedMissionsHunting.increment();
			creditsGeneratedFromMissionsHunting.add(reward);
			break;
		case MissionObject::MUSICIAN:
			numberOfCompletedMissionsMusician.increment();
			creditsGeneratedFromMissionsMusician.add(reward);
			break;
		case MissionObject::RECON:
			numberOfCompletedMissionsRecon.increment();
			creditsGeneratedFromMissionsRecon.add(reward);
			break;
		case MissionObject::SURVEY:
			numberOfCompletedMissionsSurvey.increment();
			creditsGeneratedFromMissionsSurvey.add(reward);
			break;
		}
	}


	void IncrementCharacterStat(int statType) {
		switch ( statType) {
		case CHARACTERDELETEDBYUSER:
			charactersDeletedByUser.increment();
			break;
		case CHARACTERMOVED:
			charactersMovedToDeletedTable.increment();
			break;
		case CHARACTERDESTROYEDFROMWORLD:
			charactersDestroyedFromWorld.increment();
			break;
		case CHARACTERDESTROYEDFROMDATABASE:
			charactersDestroyedFromDatabase.increment();
			break;
		case TASKERRORS:
			deleteCharacterTaskErrors.increment();
			break;
		case TASKEXCEPTIONS:
			deleteCharacterTaskExceptions.increment();
			break;
		case TASKRUN:
			deleteTasksRun.increment();
			break;
		case CHARACTERMOVEERROR:
			characterMoveErrors.increment();
			break;
		case CHARACTUREUPDATES:
			characterUpdateCount.increment();
			break;
		case CHARACTERINSERTERROR:
			characterInsertErrors.increment();
			break;
		case CHARACTERMOVEEXCEPTION:
			characterMoveExceptions.increment();
			break;
		}


	}


	String getStatistics() {
		StringBuffer stats;
		stats << "Server Statistics" << endl;
		stats << "=================" << endl << endl;

		getMissionStatistics(stats);

		return stats.toString();
	}

	String getCharacterStats(){
		StringBuffer stats;
		getCharacterStatistics(stats);

		return stats.toString();
	}

	void reset() {
		resetMissionStatistics();
		resetCharacterStatistics();
	}

private:
	void getMissionStatistics(StringBuffer& stats) {
		stats << "Number of completed missions" << endl;
		stats << "----------------------------" << endl;
		stats << "Bounty hunter: " << numberOfCompletedMissionsBounty << endl;
		stats << "Crafting: " << numberOfCompletedMissionsCrafting << endl;
		stats << "Dancing: " << numberOfCompletedMissionsDancer << endl;
		stats << "Deliver: " << numberOfCompletedMissionsDeliver << endl;
		stats << "Destroy: " << numberOfCompletedMissionsDestroy << endl;
		stats << "Hunting: " << numberOfCompletedMissionsHunting << endl;
		stats << "Musician: " << numberOfCompletedMissionsMusician << endl;
		stats << "Reconnaissance: " << numberOfCompletedMissionsRecon << endl;
		stats << "Survey: " << numberOfCompletedMissionsSurvey << endl;
		stats << "Total: " << getTotalNumberOfCompletedMissions() << endl << endl;
		stats << "Credit rewards" << endl;
		stats << "--------------" << endl;
		stats << "Bounty hunter: " << creditsGeneratedFromMissionsBounty << endl;
		stats << "Crafting: " << creditsGeneratedFromMissionsCrafting << endl;
		stats << "Dancing: " << creditsGeneratedFromMissionsDancer << endl;
		stats << "Deliver: " << creditsGeneratedFromMissionsDeliver << endl;
		stats << "Destroy: " << creditsGeneratedFromMissionsDestroy << endl;
		stats << "Hunting: " << creditsGeneratedFromMissionsHunting << endl;
		stats << "Musician: " << creditsGeneratedFromMissionsMusician << endl;
		stats << "Reconnaissance: " << creditsGeneratedFromMissionsRecon << endl;
		stats << "Survey: " << creditsGeneratedFromMissionsSurvey << endl;
		stats << "Total: " << getTotalCreditsFromCompletedMissions() << endl << endl;
	}

	long getTotalNumberOfCompletedMissions() {
		return numberOfCompletedMissionsBounty + numberOfCompletedMissionsCrafting + numberOfCompletedMissionsDancer +
				numberOfCompletedMissionsDeliver + numberOfCompletedMissionsDestroy + numberOfCompletedMissionsHunting +
				numberOfCompletedMissionsMusician + numberOfCompletedMissionsRecon + numberOfCompletedMissionsSurvey;
	}

	long getTotalCreditsFromCompletedMissions() {
		return creditsGeneratedFromMissionsBounty + creditsGeneratedFromMissionsCrafting + creditsGeneratedFromMissionsDancer +
				creditsGeneratedFromMissionsDeliver + creditsGeneratedFromMissionsDestroy + creditsGeneratedFromMissionsHunting +
				creditsGeneratedFromMissionsMusician + creditsGeneratedFromMissionsRecon + creditsGeneratedFromMissionsSurvey;
	}

	void resetMissionStatistics() {
		numberOfCompletedMissionsBounty = 0;
		numberOfCompletedMissionsCrafting = 0;
		numberOfCompletedMissionsDancer = 0;
		numberOfCompletedMissionsDeliver = 0;
		numberOfCompletedMissionsDestroy = 0;
		numberOfCompletedMissionsHunting = 0;
		numberOfCompletedMissionsMusician = 0;
		numberOfCompletedMissionsRecon = 0;
		numberOfCompletedMissionsSurvey = 0;
		creditsGeneratedFromMissionsBounty = 0;
		creditsGeneratedFromMissionsCrafting = 0;
		creditsGeneratedFromMissionsDancer = 0;
		creditsGeneratedFromMissionsDeliver = 0;
		creditsGeneratedFromMissionsDestroy = 0;
		creditsGeneratedFromMissionsHunting = 0;
		creditsGeneratedFromMissionsMusician = 0;
		creditsGeneratedFromMissionsRecon = 0;
		creditsGeneratedFromMissionsSurvey = 0;
	}

	void resetCharacterStatistics(){
		charactersDeletedByUser = 0;
		characterMoveErrors = 0;
		characterInsertErrors = 0;
		charactersMovedToDeletedTable = 0;
		characterMoveExceptions = 0;

		deleteTasksRun = 0;
		charactersDestroyedFromWorld = 0;
		charactersDestroyedFromDatabase = 0;
		deleteCharacterTaskErrors = 0;
		deleteCharacterTaskExceptions = 0;
		characterUpdateCount = 0;

	}

	void getCharacterStatistics(StringBuffer& stats){
		stats << endl << "======= CHARACTER STATS ==========" << endl << endl;
		stats << "CHARS DELETED BY USERS: " << String::valueOf(charactersDeletedByUser) << endl;
		stats << "CHARS MOVED TO DELETED TABLE: " << String::valueOf(charactersMovedToDeletedTable) << endl;
		stats << "CHAR INSERT ERRORS: " << String::valueOf(characterInsertErrors) << endl;
		stats << "CHAR MOVE VERICIATION FAILURES: " << String::valueOf(characterMoveErrors) << endl;
		stats << "CHAR MOVE EXCEPTIONS: " << String::valueOf(characterMoveExceptions) << endl;

		stats << endl << endl;
		stats << "DELETE TASK RUN: " << String::valueOf(deleteTasksRun) << endl;
		stats << "CHARS DELETED FROM WORLD: " << String::valueOf(charactersDestroyedFromWorld) << endl;
		stats << "CHARS DELETED FROM DB: " << String::valueOf(charactersDestroyedFromDatabase) << endl;
		stats << "DELETE TASK ERRORS: " << String::valueOf(deleteCharacterTaskErrors) << endl;
		stats << "DELTE TASK EXCEPTIONS: " << String::valueOf(deleteCharacterTaskExceptions) << endl;
		stats << "CHAR UPDATE RUN: " << String::valueOf(characterUpdateCount) << endl;

	}
};

#endif /* STATISTICSMANAGER_H_ */
