/*
			Copyright <SWGEmu>
	See file COPYING for copying conditions.

	SquadronObserver.h

	Author: Hakry
	Created On: 2025-10-09
*/

#ifndef SQUADRONOBSERVER_H_
#define SQUADRONOBSERVER_H_

#include "engine/util/Observer.h"
#include "server/zone/managers/ship/ShipManager.h"


namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {

class SquadronObserver : public Observer, public Logger {
private:
	Mutex mutex;

	uint32 formationType;
	SortedVector<WeakReference<ShipAiAgent*>> squadronVector;

public:
	SquadronObserver();
	SquadronObserver(ShipAiAgent* shipAgent);
	~SquadronObserver();

	int notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2);

	// Mutators
	void addSquadronShip(ShipAiAgent* shipAgent);

	void dropSquadronShip(ShipAiAgent* shipAgent);

	void setRandomFormation();

	void setFormationType(uint32 formation);

	// Accessors
	ShipAiAgent* getSquadronLeader();

	uint64 getSquadronLeaderID();

	int getSquadronSize() {
		return squadronVector.size();
	}

	uint32 getFormationType() {
		return formationType;
	}
};

} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai;

#endif /* SQUADRONOBSERVER_H_ */
