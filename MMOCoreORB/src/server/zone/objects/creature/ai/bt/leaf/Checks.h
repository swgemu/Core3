#ifndef CHECKS_H_
#define CHECKS_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace leaf {

// helper enum to ensure we have exactly one template realization per check typedef
enum CheckType {
	CHECK_POSTURE,
	CHECK_DESTINATION,
	CHECK_MOVEMENTSTATE,
	CHECK_HASFOLLOW,
	CHECK_FOLLOWHASSTATE,
	CHECK_AGGRODELAYPAST,
	CHECK_PROSPECTINRANGE,
	CHECK_FOLLOWAGGRESSION,
	CHECK_PROSPECTAGGRESSION,
	CHECK_FOLLOWPOSTURE,
	CHECK_FOLLOWINWEAPONRANGE,
	CHECK_FOLLOWCLOSESTIDEALRANGE,
	CHECK_RANDOMLEVEL,
	CHECK_ATTACKINRANGE,
	CHECK_ATTACKISVALID,
	CHECK_TARGETISVALID,
	CHECK_RETREAT,
	CHECK_SPEED,
	CHECK_PROSPECTSPEED,
	CHECK_PROSPECTLOS,
	CHECK_OUTDOORS,
	CHECK_PROSPECTLEVEL,
	CHECK_PROSPECTBACKAGGRESSION,
	CHECK_PROSPECTFACING,
	CHECK_PETCOMMAND,
	CHECK_PROSPECTISCOMMAND,
	CHECK_ISINCOMBAT,
	CHECK_HASPATROL,
	CHECK_PROSPECTISTYPE,
	CHECK_ISTYPE,
	CHECK_PROSPECTJEDITRIAL,
	CHECK_PROSPECTISINCAPACITATED,
	CHECK_ISKILLER,
	CHECK_ISSTALKER,
	CHECK_FLEE,
	CHECK_OWNERINRANGE,
	CHECK_TARGETINOWNERRANGE,
	CHECK_USERANGED,
	CHECK_WEAPONISRANGED,
	CHECK_ISDROID,
	CHECK_CRACKDOWNSCANNER,
	CHECK_CRACKDOWNFOLLOWTARGET,
	CHECK_ISSTATIONARY,
	CHECK_ISHEALER,
	CHECK_HEALCHANCE,
	CHECK_ISHOME,
	CHECK_HOMEISCELL,
	CHECK_CHATDELAY,
	CHECK_CALLFORHELP,
	CHECK_ISHARVESTER,
	CHECK_HASHARVESTTARGETS,
	CHECK_ISCAMOUFLAGED,
	CHECK_SHOULDREST,
	CHECK_STOPRESTING,
	CHECK_QUEUESIZE,
	CHECK_ISESCORT,
	CHECK_HASRANGEDWEAPON,
	CHECK_HASMELEEWEAPON,
	CHECK_ISSWIMMING
};

// template class to reduce repeated code. Do this instead of inheritance so we
// don't have to retype the ctors (which would be exactly the same)
template<typename val_type, CheckType C>
class _Check : public Behavior {
public:
	_Check(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), checkVar((val_type) (0)) {
		parseArgs(args);
	}

	_Check(const _Check& c)
			: Behavior(c), checkVar(c.checkVar) {
	}

	_Check& operator=(const _Check& c) {
		if (this == &c)
			return *this;
		Behavior::operator=(c);
		checkVar = c.checkVar;
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		assert(agent != nullptr);

		return check(agent) ? SUCCESS : FAILURE;
	}

	bool check(AiAgent*) const;

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

typedef _Check<uint32, CHECK_POSTURE> CheckPosture;
template<> bool CheckPosture::check(AiAgent* agent) const;

typedef _Check<int32, CHECK_DESTINATION> CheckDestination;
template<> bool CheckDestination::check(AiAgent* agent) const;

typedef _Check<int32, CHECK_MOVEMENTSTATE> CheckMovementState;
template<> bool CheckMovementState::check(AiAgent* agent) const;

typedef _Check<int32, CHECK_HASFOLLOW> CheckHasFollow;
template<> bool CheckHasFollow::check(AiAgent* agent) const;

typedef _Check<uint64, CHECK_FOLLOWHASSTATE> CheckFollowHasState;
template<> bool CheckFollowHasState::check(AiAgent* agent) const;

typedef _Check<uint64, CHECK_AGGRODELAYPAST> CheckAggroDelayPast;
template<> bool CheckAggroDelayPast::check(AiAgent* agent) const;

typedef _Check<float, CHECK_PROSPECTINRANGE> CheckProspectInRange;
template<> bool CheckProspectInRange::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_FOLLOWAGGRESSION> CheckFollowAggression;
template<> bool CheckFollowAggression::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_PROSPECTAGGRESSION> CheckProspectAggression;
template<> bool CheckProspectAggression::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISCAMOUFLAGED> CheckIsCamouflaged;
template<> bool CheckIsCamouflaged::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_FOLLOWPOSTURE> CheckFollowPosture;
template<> bool CheckFollowPosture::check(AiAgent* agent) const;

typedef _Check<DataVal, CHECK_FOLLOWINWEAPONRANGE> CheckFollowInWeaponRange;
template<> bool CheckFollowInWeaponRange::check(AiAgent* agent) const;

typedef _Check<DataVal, CHECK_FOLLOWCLOSESTIDEALRANGE> CheckFollowClosestIdealRange;
template<> bool CheckFollowClosestIdealRange::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_RANDOMLEVEL> CheckRandomLevel;
template<> bool CheckRandomLevel::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ATTACKINRANGE> CheckAttackInRange;
template<> bool CheckAttackInRange::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ATTACKISVALID> CheckAttackIsValid;
template<> bool CheckAttackIsValid::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_TARGETISVALID> CheckTargetIsValid;
template<> bool CheckTargetIsValid::check(AiAgent* agent) const;

typedef _Check<int32, CHECK_RETREAT> CheckRetreat;
template<> bool CheckRetreat::check(AiAgent* agent) const;

typedef _Check<float, CHECK_FLEE> CheckFlee;
template<> bool CheckFlee::check(AiAgent* agent) const;

typedef _Check<float, CHECK_SPEED> CheckSpeed;
template<> bool CheckSpeed::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_PROSPECTSPEED> CheckProspectSpeed;
template<> bool CheckProspectSpeed::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_PROSPECTLOS> CheckProspectLOS;
template<> bool CheckProspectLOS::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_OUTDOORS> CheckOutdoors;
template<> bool CheckOutdoors::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_PROSPECTLEVEL> CheckProspectLevel;
template<> bool CheckProspectLevel::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_PROSPECTBACKAGGRESSION> CheckProspectBackAggression;
template<> bool CheckProspectBackAggression::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_PROSPECTFACING> CheckProspectFacing;
template<> bool CheckProspectFacing::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_PETCOMMAND> CheckPetCommand;
template<> bool CheckPetCommand::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_PROSPECTISCOMMAND> CheckProspectIsCommand;
template<> bool CheckProspectIsCommand::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISINCOMBAT> CheckIsInCombat;
template<> bool CheckIsInCombat::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_HASPATROL> CheckHasPatrol;
template<> bool CheckHasPatrol::check(AiAgent* agent) const;

typedef _Check<DataVal, CHECK_PROSPECTISTYPE> CheckProspectIsType;
template<> bool CheckProspectIsType::check(AiAgent* agent) const;

typedef _Check<DataVal, CHECK_ISTYPE> CheckIsType;
template<> bool CheckIsType::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_PROSPECTJEDITRIAL> CheckProspectJediTrial;
template<> bool CheckProspectJediTrial::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_PROSPECTISINCAPACITATED> CheckProspectIsIncapacitated;
template<> bool CheckProspectIsIncapacitated::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISKILLER> CheckIsKiller;
template<> bool CheckIsKiller::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISSTALKER> CheckIsStalker;
template<> bool CheckIsStalker::check(AiAgent* agent) const;

typedef _Check<float, CHECK_OWNERINRANGE> CheckOwnerInRange;
template<> bool CheckOwnerInRange::check(AiAgent* agent) const;

typedef _Check<float, CHECK_TARGETINOWNERRANGE> CheckTargetInOwnerRange;
template<> bool CheckTargetInOwnerRange::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_USERANGED> CheckUseRanged;
template<> bool CheckUseRanged::check(AiAgent* agent) const;

typedef _Check<uint32, CHECK_WEAPONISRANGED> CheckWeaponIsRanged;
template<> bool CheckWeaponIsRanged::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISDROID> CheckIsDroid;
template<> bool CheckIsDroid::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_CRACKDOWNSCANNER> CheckCrackdownScanner;
template<> bool CheckCrackdownScanner::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_CRACKDOWNFOLLOWTARGET> CheckCrackdownFollowTarget;
template<> bool CheckCrackdownFollowTarget::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISSTATIONARY> CheckIsStationary;
template<> bool CheckIsStationary::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISHEALER> CheckIsHealer;
template<> bool CheckIsHealer::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_HEALCHANCE> CheckHealChance;
template<> bool CheckHealChance::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISHOME> CheckIsHome;
template<> bool CheckIsHome::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_HOMEISCELL> CheckHomeIsCell;
template<> bool CheckHomeIsCell::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_CHATDELAY> CheckChatDelay;
template<> bool CheckChatDelay::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_CALLFORHELP> CheckCallForHelp;
template<> bool CheckCallForHelp::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISHARVESTER> CheckIsHarvester;
template<> bool CheckIsHarvester::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_HASHARVESTTARGETS> CheckHasHarvestTargets;
template<> bool CheckHasHarvestTargets::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_SHOULDREST> CheckShouldRest;
template<> bool CheckShouldRest::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_STOPRESTING> CheckStopResting;
template<> bool CheckStopResting::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_QUEUESIZE> CheckQueueSize;
template<> bool CheckQueueSize::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISESCORT> CheckIsEscort;
template<> bool CheckIsEscort::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_HASRANGEDWEAPON> CheckHasRangedWeapon;
template<> bool CheckHasRangedWeapon::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_HASMELEEWEAPON> CheckHasMeleeWeapon;
template<> bool CheckHasMeleeWeapon::check(AiAgent* agent) const;

typedef _Check<bool, CHECK_ISSWIMMING> CheckIsSwimming;
template<> bool CheckIsSwimming::check(AiAgent* agent) const;

}
}
}
}
}
}
}

#endif // CHECKS_H_
