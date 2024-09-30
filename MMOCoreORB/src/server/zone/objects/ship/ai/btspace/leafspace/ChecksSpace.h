#ifndef CHECKSSPACE_H_
#define CHECKSSPACE_H_

#include "server/zone/objects/ship/ai/btspace/BehaviorSpace.h"

namespace server {
namespace zone {
namespace objects {
namespace ship {
namespace ai {
namespace btspace {
namespace leafspace {

// helper enum to ensure we have exactly one template realization per check typedef
enum CheckTypeSpace {
	CHECK_DESTINATION,
	CHECK_HASPATROL,
	CHECK_MOVEMENTSTATE,
	CHECK_PROSPECTINRANGE,
	CHECK_AGGRODELAYPAST,
	CHECK_HASFOLLOW,
	CHECK_RETREAT,
	CHECK_PROSPECTAGGRESSION,
	CHECK_REFIRERATE,
	CHECK_EVADEDELAYPAST,
	CHECK_CHECKTARGETISVALID,
	CHECK_ENGINESDISABLED,
	CHECK_EVADECHANCE,
	CHECK_PROSPECTLOS,
	CHECK_WEAPONS,
};

// template class to reduce repeated code. Do this instead of inheritance so we
// don't have to retype the ctors (which would be exactly the same)
template <typename val_type, CheckTypeSpace C>
class _CheckSpace : public BehaviorSpace {
public:
	_CheckSpace(const String& className, const uint32 id, const LuaObject& args) : BehaviorSpace(className, id, args), checkVar((val_type)(0)) {
		parseArgs(args);
	}

	_CheckSpace(const _CheckSpace& c) : BehaviorSpace(c), checkVar(c.checkVar) {
	}

	_CheckSpace& operator=(const _CheckSpace& c) {
		if (this == &c)
			return *this;

		BehaviorSpace::operator=(c);

		checkVar = c.checkVar;
		return *this;
	}

	BehaviorSpace::Status execute(ShipAiAgent* agent, unsigned int startIdx = 0) const {
		assert(agent != nullptr);

		return check(agent) ? SUCCESS : FAILURE;
	}

	bool check(ShipAiAgent*) const;

	void parseArgs(const LuaObject& args) {
		checkVar = getArg<val_type>()(args, "condition");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << checkVar;

		return msg.toString();
	}

	protected:
		val_type checkVar;
};

typedef _CheckSpace<int32, CHECK_DESTINATION> CheckDestination;
template<> bool CheckDestination::check(ShipAiAgent* agent) const;

typedef _CheckSpace<bool, CHECK_HASPATROL> CheckHasPatrol;
template<> bool CheckHasPatrol::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_MOVEMENTSTATE> CheckMovementState;
template<> bool CheckMovementState::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_PROSPECTINRANGE> CheckProspectInRange;
template<> bool CheckProspectInRange::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_AGGRODELAYPAST> CheckAggroDelayPast;
template<> bool CheckAggroDelayPast::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_HASFOLLOW> CheckHasFollow;
template<> bool CheckHasFollow::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_RETREAT> CheckRetreat;
template<> bool CheckRetreat::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_PROSPECTAGGRESSION> CheckProspectAggression;
template<> bool CheckProspectAggression::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_REFIRERATE> CheckRefireRate;
template<> bool CheckRefireRate::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_EVADEDELAYPAST> CheckStopEvading;
template<> bool CheckStopEvading::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_CHECKTARGETISVALID> CheckTargetIsValid;
template<> bool CheckTargetIsValid::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_ENGINESDISABLED> CheckEnginesDisabled;
template<> bool CheckEnginesDisabled::check(ShipAiAgent* agent) const;

typedef _CheckSpace<int32, CHECK_EVADECHANCE> CheckEvadeChance;
template<> bool CheckEvadeChance::check(ShipAiAgent* agent) const;

typedef _CheckSpace<uint32, CHECK_PROSPECTLOS> CheckProspectLOS;
template<> bool CheckProspectLOS::check(ShipAiAgent* agent) const;

typedef _CheckSpace<uint32, CHECK_WEAPONS> CheckWeapons;
template<> bool CheckWeapons::check(ShipAiAgent* agent) const;

} // namespace leafspace
} // namespace btspace
} // namespace ai
} // namespace ship
} // namespace objects
} // namespace zone
} // namespace server

#endif // CHECKSSPACE_H_
