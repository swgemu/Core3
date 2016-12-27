/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include "server/zone/objects/mission/MissionTypes.h"

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

public:
	StatisticsManager() : Logger("Statistics Manager") {
		reset();
	}

	void completeMission(unsigned int missionType, int reward) {
		switch (missionType) {
		case MissionTypes::BOUNTY:
			numberOfCompletedMissionsBounty.increment();
			creditsGeneratedFromMissionsBounty.add(reward);
			break;
		case MissionTypes::CRAFTING:
			numberOfCompletedMissionsCrafting.increment();
			creditsGeneratedFromMissionsCrafting.add(reward);
			break;
		case MissionTypes::DANCER:
			numberOfCompletedMissionsDancer.increment();
			creditsGeneratedFromMissionsDancer.add(reward);
			break;
		case MissionTypes::DELIVER:
			numberOfCompletedMissionsDeliver.increment();
			creditsGeneratedFromMissionsDeliver.add(reward);
			break;
		case MissionTypes::DESTROY:
			numberOfCompletedMissionsDestroy.increment();
			creditsGeneratedFromMissionsDestroy.add(reward);
			break;
		case MissionTypes::HUNTING:
			numberOfCompletedMissionsHunting.increment();
			creditsGeneratedFromMissionsHunting.add(reward);
			break;
		case MissionTypes::MUSICIAN:
			numberOfCompletedMissionsMusician.increment();
			creditsGeneratedFromMissionsMusician.add(reward);
			break;
		case MissionTypes::RECON:
			numberOfCompletedMissionsRecon.increment();
			creditsGeneratedFromMissionsRecon.add(reward);
			break;
		case MissionTypes::SURVEY:
			numberOfCompletedMissionsSurvey.increment();
			creditsGeneratedFromMissionsSurvey.add(reward);
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

	void reset() {
		resetMissionStatistics();
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
};

#endif /* STATISTICSMANAGER_H_ */
