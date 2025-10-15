/*
			Copyright <SWGEmu>
	See file COPYING for copying conditions.

	SquadronObserver.h

	Author: Hakry
	Created On: 2025-10-09
*/

#ifndef SQUADRONOBSERVER_H_
#define SQUADRONOBSERVER_H_

#include "server/zone/objects/ship/squadron/ShipSquadronData.h"
#include "engine/util/Observer.h"
#include "server/zone/managers/ship/ShipManager.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {

class SquadronObserver : public Observer, public Logger {
private:
	Vector<Reference<ShipAiAgent*>> squadronAgents;
	ShipSquadronData squadronData;
	mutable ReadWriteLock mutex;

public:
	SquadronObserver();

	SquadronObserver(ShipAiAgent* shipAgent);

	~SquadronObserver();

	int notifyObserverEvent(unsigned int eventType, Observable* observable, ManagedObject* arg1, long long arg2);

	// Mutators
	void addSquadronShip(ShipAiAgent* shipAgent);

	void dropSquadronShip(ShipAiAgent* shipAgent);

	void setFormationType(int type, float radius = -1.f);

	void setRandomFormation();

	void updateSquadron();

	// Accessors
	int getSquadronIndex(ShipAiAgent* shipAgent) const;

	int getSquadronSize() const;

	int getFormationType() const;

	float getFormationSpeed() const;

	ShipAiAgent* getSquadronLeader() const;

	ShipAiAgent* getSquadronMember(int index) const;

	uint64 getSquadronLeaderID() const;

	uint64 getSquadronMemberID(int index) const;

	bool isSquadronLeader(ShipAiAgent* shipAgent) const;

	bool isSquadronMember(ShipAiAgent* shipAgent) const;

	Vector3 getPosition(ShipAiAgent* shipAgent) const;

	float getSpeed(ShipAiAgent* shipAgent) const;
};

} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

using namespace server::zone::objects::ship::ai;

#endif /* SQUADRONOBSERVER_H_ */
