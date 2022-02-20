/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STATISTICSMANAGER_H_
#define STATISTICSMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/mission/MissionTypes.h"
#include "engine/util/Singleton.h"
#include "system/thread/atomic/AtomicLong.h"
#include "engine/log/Logger.h"
#include "server/zone/managers/creature/AiMap.h"

class StatisticsManager : public Singleton<StatisticsManager>, public Logger, public Object {
	const static int CONSOLE_REPORT_INTERVAL = 1000;

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

	pid_t corePid;
	Time coreStartTime;
	Time coreInitializedTime;

	Mutex mutex;
	Time lastReset;

	uint16 accountsCount;
	uint16 accountsMax;
	Time accountsMaxWhen;

	uint16 onlineCount;
	uint16 onlineMax;
	Time onlineMaxWhen;

	uint16 distinctIPsCount;
	uint16 distinctIPsMax;
	Time distinctIPsMaxWhen;

public:
	StatisticsManager() : Logger("StatisticsManager") {
		reset();
	}

	void markCoreStart(pid_t pid) {
		Locker guard(&mutex);
		corePid = pid;
		coreStartTime.updateToCurrentTime();
	}

	void markCoreInitialized() {
		Locker guard(&mutex);
		coreInitializedTime.updateToCurrentTime();
	}

	void setAccountsCount(uint16 count) {
		Locker guard(&mutex);

		accountsCount = count;

		if (accountsCount > accountsMax) {
			accountsMax = accountsCount;
			accountsMaxWhen.updateToCurrentTime();
		}
	}

	void setOnlineCount(uint16 count) {
		Locker guard(&mutex);

		onlineCount = count;

		if (onlineCount > onlineMax) {
			onlineMax = onlineCount;
			onlineMaxWhen.updateToCurrentTime();
		}
	}

	void setDistinctIPsCount(uint16 count) {
		Locker guard(&mutex);

		distinctIPsCount = count;

		if (distinctIPsCount > distinctIPsMax) {
			distinctIPsMax = distinctIPsCount;
			distinctIPsMaxWhen.updateToCurrentTime();
		}
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
		return String(getAsJSON().dump(2));
	}

	const JSONSerializationType getAsJSON() {
		Locker guard(&mutex);

		JSONSerializationType json = JSONSerializationType::object();

		JSONSerializationType state;

		state["elapsedMs"] = lastReset.miliDifference();
		state["lastResetTime"] = lastReset.getFormattedTimeFull();
		state["lastResetTimeMs"] = lastReset;

		json["state"] = state;

		auto aimap = AiMap::instance();

		if (aimap != nullptr) {
			json["ai"] = aimap->getStatsAsJSON();
		}

		JSONSerializationType core;

		core["pid"] = corePid;
		core["coreStartTime"] = coreStartTime.getFormattedTimeFull();
		core["coreStartTimeMs"] = coreStartTime;
		core["coreInitializedTime"] = coreInitializedTime.getFormattedTimeFull();
		core["coreInitializedTimeMs"] = coreInitializedTime;
		core["coreLoadMs"] = coreStartTime.miliDifference(coreInitializedTime);

		json["core"] = core;

		JSONSerializationType players;

		players["accountsCount"] = accountsCount;
		players["accountsMax"] = accountsMax;
		players["accountsMaxWhen"] = accountsMaxWhen.getFormattedTimeFull();
		players["accountsMaxWhenMs"] = accountsMaxWhen;
		players["distinctIPsCount"] = distinctIPsCount;
		players["distinctIPsMax"] = distinctIPsMax;
		players["distinctIPsMaxWhen"] = distinctIPsMaxWhen.getFormattedTimeFull();
		players["distinctIPsMaxWhenMs"] = distinctIPsMaxWhen;
		players["onlineCount"] = onlineCount;
		players["onlineMax"] = onlineMax;
		players["onlineMaxWhen"] = onlineMaxWhen.getFormattedTimeFull();
		players["onlineMaxWhenMs"] = onlineMaxWhen;

		json["players"] = players;

		JSONSerializationType missions;

		missions["creditsGeneratedFromMissionsBounty"] = creditsGeneratedFromMissionsBounty.get();
		missions["creditsGeneratedFromMissionsCrafting"] = creditsGeneratedFromMissionsCrafting.get();
		missions["creditsGeneratedFromMissionsDancer"] = creditsGeneratedFromMissionsDancer.get();
		missions["creditsGeneratedFromMissionsDeliver"] = creditsGeneratedFromMissionsDeliver.get();
		missions["creditsGeneratedFromMissionsDestroy"] = creditsGeneratedFromMissionsDestroy.get();
		missions["creditsGeneratedFromMissionsHunting"] = creditsGeneratedFromMissionsHunting.get();
		missions["creditsGeneratedFromMissionsMusician"] = creditsGeneratedFromMissionsMusician.get();
		missions["creditsGeneratedFromMissionsRecon"] = creditsGeneratedFromMissionsRecon.get();
		missions["creditsGeneratedFromMissionsSurvey"] = creditsGeneratedFromMissionsSurvey.get();
		missions["numberOfCompletedMissionsBounty"] = numberOfCompletedMissionsBounty.get();
		missions["numberOfCompletedMissionsCrafting"] = numberOfCompletedMissionsCrafting.get();
		missions["numberOfCompletedMissionsDancer"] = numberOfCompletedMissionsDancer.get();
		missions["numberOfCompletedMissionsDeliver"] = numberOfCompletedMissionsDeliver.get();
		missions["numberOfCompletedMissionsDestroy"] = numberOfCompletedMissionsDestroy.get();
		missions["numberOfCompletedMissionsHunting"] = numberOfCompletedMissionsHunting.get();
		missions["numberOfCompletedMissionsMusician"] = numberOfCompletedMissionsMusician.get();
		missions["numberOfCompletedMissionsRecon"] = numberOfCompletedMissionsRecon.get();
		missions["numberOfCompletedMissionsSurvey"] = numberOfCompletedMissionsSurvey.get();

		json["missionStats"] = missions;

		return json;
	}

	void reset() {
		Locker guard(&mutex);

		resetMissionStatistics();

		accountsCount = 0;
		accountsMax = 0;
		accountsMaxWhen.updateToCurrentTime();

		distinctIPsCount = 0;
		distinctIPsMax = 0;
		distinctIPsMaxWhen.updateToCurrentTime();

		onlineCount = 0;
		onlineMax = 0;
		onlineMaxWhen.updateToCurrentTime();

		lastReset.updateToCurrentTime();
	}

private:
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
