/*
 * ShuttleDepartureTask.h
 *
 *  Created on: Aug 19, 2011
 *      Author: crush
 */

#ifndef SHUTTLEDEPARTURETASK_H_
#define SHUTTLEDEPARTURETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "engine/engine.h"

//#define SHUTTLE_TIMER_DEBUG

class ShuttleDepartureTask : public Task, public Logger {
	ManagedWeakReference<CreatureObject*> shuttleObject;

protected:
	int landedTime; //In seconds
	int landingTime; //How long the landing animation takes to complete in seconds.
	int departedTime; //In seconds
	int shuttleType; // Type of Shuttle

public:
	ShuttleDepartureTask(CreatureObject* shuttle) : Task() {
		shuttleObject = shuttle;
		departedTime = 300;
		landingTime = 11;
		landedTime = 120;
		shuttleType = 0;

		Logger::setLoggingName("ShuttleDepartureTask");
	}

	void run() {
		ManagedReference<CreatureObject*> strongReference = shuttleObject.get();

		if (strongReference == nullptr) {
			error() << " run() - shuttle strongReference has a nullptr.";
			return;
		}

		ZoneServer* zoneServer = strongReference->getZoneServer();

		if (zoneServer != nullptr && zoneServer->isServerShuttingDown()) {
			cancel();
			return;
		}

		Locker _lock(strongReference);

		if (strongReference->isStanding()) {
			strongReference->setPosture(CreaturePosture::PRONE);
			reschedule(getDepartedTime() * 1000);
		} else {
			strongReference->setPosture(CreaturePosture::UPRIGHT);
			reschedule(getLandedTime() * 1000);
		}
	}

	int getSecondsRemaining() {
		int seconds = (int) (getNextExecutionTime().miliDifference() / 1000.f * -1) + 1;

		return seconds;
	}

	bool isLanded() {
		ManagedReference<CreatureObject*> strongReference = shuttleObject.get();

		if (strongReference == nullptr) {
			error() << " isLanded - shuttle strongReference has a nullptr.";
			return false;
		}

		if (!strongReference->isStanding())
			return false;

		int landedCalc = landedTime - getSecondsRemaining();

#ifdef SHUTTLE_TIMER_DEBUG
		info(true) << " isLanded - landing time = " << landingTime << " landed calc = " << landedCalc;
#endif

		//Make sure the shuttle isn't still landing
		if (landedCalc <= landingTime)
			return false;

		return true;
	}

	bool isLanding() {
		ManagedReference<CreatureObject*> strongReference = shuttleObject.get();

		if (strongReference == nullptr) {
			error() << "ShuttleDepartureTask::isLanding - shuttle strongReference has a nullptr.";
			return false;
		}

		int landedCalc = landedTime - getSecondsRemaining();

#ifdef SHUTTLE_TIMER_DEBUG
		info(true) << " isLanded - landing time = " << landingTime << " landed calc = " << landedCalc;
#endif

		if (strongReference->isStanding() && landedTime <= landingTime)
			return true;

		return false;
	}

	int getLandingTime() {
		return landingTime;
	}

	int getLandedTime() {
		// Landed Time is 120s for all shuttle
		// Shuttleports = 11s	Startports = 14s
		int timeLanded = landedTime + landingTime;

#ifdef SHUTTLE_TIMER_DEBUG
		info(true) << " Shuttle Type = " << getShuttleType() <<  " Setting time landed to " << timeLanded << " seconds.";
#endif

		return timeLanded;
	}

	int getDepartedTime() {
		// Startport departedTime is 60s and shuttleport departedTime is 300s

#ifdef SHUTTLE_TIMER_DEBUG
		info(true) << " Shuttle Type = " << getShuttleType() << " Setting departed time to " << departedTime << " seconds.";
#endif

		return departedTime;
	}

	int getShuttleType() {
		return shuttleType;
	}

	void setLandingTime(int landing) {
		landingTime = landing;
	}

	void setLandedTime(int landed) {
		landedTime = landed;
	}

	void setDepartedTime(int departed) {
		departedTime = departed;
	}

	void setShuttleType (int type) {
		shuttleType = type;
	}
};

#endif /* SHUTTLEDEPARTURETASK_H_ */
