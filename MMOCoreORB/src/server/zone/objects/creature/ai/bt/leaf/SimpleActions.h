#ifndef SIMPLEACTIONS_H_
#define SIMPLEACTIONS_H_

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/objects/creature/ai/bt/BlackboardData.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
namespace ai {
namespace bt {
namespace leaf {

class Dummy : public Behavior {
public:
	Dummy(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	Dummy(const Dummy& d)
			: Behavior(d) {
	}

	Behavior::Status execute(AiAgent*, unsigned int) const {
		return SUCCESS; // this is meant to be decorated with AlwaysXX, so this return won't matter.
	}
};

class GeneratePatrol : public Behavior {
public:
	GeneratePatrol(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), numPoints(0), distFromHome(0.0) {
		parseArgs(args);
	}

	GeneratePatrol(const GeneratePatrol& a)
			: Behavior(a), numPoints(a.numPoints), distFromHome(a.distFromHome) {
	}

	GeneratePatrol& operator=(const GeneratePatrol& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		numPoints = a.numPoints;
		distFromHome = a.distFromHome;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		numPoints = getArg<int>()(args, "numPoints");
		distFromHome = getArg<float>()(args, "distFromHome");
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		return agent->generatePatrol(numPoints, distFromHome) ? SUCCESS : FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << numPoints << ":" << distFromHome;

		return msg.toString();
	}

private:
	int numPoints;
	float distFromHome;
};

class ExitCombat : public Behavior {
public:
	ExitCombat(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), clearDefenders(false) {
		parseArgs(args);
	}

	ExitCombat(const ExitCombat& a)
			: Behavior(a), clearDefenders(a.clearDefenders) {
	}

	ExitCombat& operator=(const ExitCombat& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		clearDefenders = a.clearDefenders;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		clearDefenders = getArg<bool>()(args, "clearDefenders");
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		agent->clearQueueActions();
		agent->clearCombatState(clearDefenders);

		return !agent->isInCombat() ? SUCCESS : FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << clearDefenders;

		return msg.toString();
	}

private:
	bool clearDefenders;
};

class EquipStagedWeapon : public Behavior {
public:
	EquipStagedWeapon(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	EquipStagedWeapon(const EquipStagedWeapon& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (!agent->peekBlackboard("stagedWeapon"))
			return FAILURE;

		uint32 weapon = agent->readBlackboard("stagedWeapon").get<uint32>();

		if (weapon == DataVal::PRIMARYWEAPON)
			agent->equipPrimaryWeapon();
		else if (weapon == DataVal::SECONDARYWEAPON)
			agent->equipSecondaryWeapon();

		return SUCCESS;
	}
};

class WriteBlackboard : public Behavior {
public:
	WriteBlackboard(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
		parseArgs(args);
	}

	WriteBlackboard(const WriteBlackboard& a)
			: Behavior(a), key(a.key), val(a.val) {
	}

	WriteBlackboard& operator=(const WriteBlackboard& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		key = a.key;
		val = a.val;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		key = getArg<String>()(args, "key");
		val = getArg<uint32>()(args, "val");
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		agent->writeBlackboard(key, val);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << key << ":" << val;

		return msg.toString();
	}

private:
	String key;
	uint32 val;
};

class EraseBlackboard : public Behavior {
public:
	EraseBlackboard(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), param("") {
		parseArgs(args);
	}

	EraseBlackboard(const EraseBlackboard& a)
			: Behavior(a), param(a.param) {
	}

	EraseBlackboard& operator=(const EraseBlackboard& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		param = a.param;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		param = getArg<String>()(args, "param");
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		agent->eraseBlackboard(param);
		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << param;

		return msg.toString();

	}

private:
	String param;
};

class SelectAttack : public Behavior {
public:
	SelectAttack(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), attackNum(-1) {
		parseArgs(args);
	}

	SelectAttack(const SelectAttack& a)
			: Behavior(a), attackNum(a.attackNum) {
	}

	SelectAttack& operator=(const SelectAttack& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		attackNum = a.attackNum;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		attackNum = getArg<int>()(args, "attackNum", -1);
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		//agent->info("SelectAttack::execute", true);

		WeaponObject* weapon = agent->getWeapon();

		if (weapon != nullptr && weapon->getAttackType() ==  SharedWeaponObjectTemplate::FORCEATTACK) {
			return agent->selectSpecialAttack(-1) ? SUCCESS : FAILURE;
		}

		if (agent->peekBlackboard("attackType")) {
			//agent->info("SelectAttack::execute has attackType", true);

			if (agent->readBlackboard("attackType").get<uint32>() == static_cast<uint32>(DataVal::DEFAULT)) {
				//agent->info("SelectAttack::execute has attackType DEFAULT", true);

				return agent->selectDefaultAttack() ? SUCCESS : FAILURE;
			}

			if (agent->readBlackboard("attackType").get<uint32>() == static_cast<uint32>(DataVal::RANDOM)) {
				//agent->info("SelectAttack::execute has attackType RANDOM", true);

				return agent->selectSpecialAttack(-1) ? SUCCESS : FAILURE;
			}
		}

		//agent->info("SelectAttack::execute has attackType attackNum", true);

		return agent->selectSpecialAttack(attackNum) ? SUCCESS : FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << attackNum;

		return msg.toString();
	}

private:
	int attackNum;
};

class EnqueueAttack : public Behavior {
public:
	EnqueueAttack(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	EnqueueAttack(const EnqueueAttack& a)
			: Behavior(a) {
	}

	EnqueueAttack& operator=(const EnqueueAttack& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);

		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		int res = agent->enqueueAttack(-1);
		Behavior::Status returnRes = FAILURE;

		if (!res)
			returnRes = SUCCESS;

		return returnRes;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}

};

class FindNextPosition : public Behavior {
public:
	FindNextPosition(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	FindNextPosition(const FindNextPosition& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		DataVal mode = DataVal::WALK;
		if (agent->peekBlackboard("moveMode"))
			mode = static_cast<DataVal>(agent->readBlackboard("moveMode").get<uint32>());

		return agent->findNextPosition(agent->getMaxDistance(), mode == DataVal::WALK) ? RUNNING : SUCCESS;
	}
};

class Leash : public Behavior {
public:
	Leash(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args) {
	}

	Leash(const Leash& a)
			: Behavior(a) {
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		agent->leash();
		return SUCCESS;
	}
};

class Wait : public Behavior {
public:
	Wait(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), duration(-1) {
		parseArgs(args);
	}

	Wait(const Wait& a)
			: Behavior(a), duration(a.duration) {
	}

	Wait& operator=(const Wait& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		duration = a.duration;
		return *this;
	}

	void parseArgs(const LuaObject& args) {
		duration = (int) (getArg<float>()(args, "duration") * 1000);
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		// we don't need to check a value. Just checking to see if this value
		// exists on the blackboard is fine since it can never be false
		if (agent->peekBlackboard("isWaiting")) {
			if (agent->isWaiting() || duration < 0) // < 0 means indefinite wait
				return RUNNING;
			else {
				agent->eraseBlackboard("isWaiting");
				return SUCCESS;
			}
		}

		agent->setWait(duration);
		agent->writeBlackboard("isWaiting", true);

		return RUNNING;
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << duration;

		return msg.toString();
	}

private:
	int duration;
};

class SetAlert : public Behavior {
public:
	SetAlert(const String& className, const uint32 id, const LuaObject& args)
			: Behavior(className, id, args), duration(0.f), show(true) {
		parseArgs(args);
	}

	SetAlert(const SetAlert& b) : Behavior(b), duration(b.duration), show(b.show) {
	}

	SetAlert& operator=(const SetAlert& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);
		duration = b.duration;
		show = b.show;
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		Time* alert = agent->getAlertedTime();

		if (alert == nullptr || !alert->isPast())
			return FAILURE;

		alert->updateToCurrentTime();
		alert->addMiliTime(duration);

		Time* delay = agent->getAggroDelay();
		if (delay != nullptr && delay->isPast()) {
			delay->updateToCurrentTime();
			uint32 newDelay = 5000;
			delay->addMiliTime(newDelay);
		}

		if (agent->getPosture() != CreaturePosture::UPRIGHT)
			agent->setPosture(CreaturePosture::UPRIGHT, true);

		if (show) {
			agent->showFlyText("npc_reaction/flytext", "alert", 255, 0, 0);

			if (agent->isNpc() && agent->getFaction() > 0)
				agent->doAnimation("search");

			agent->sendReactionChat(nullptr, ReactionManager::ALERT);
		}

		return SUCCESS;
	}

	void parseArgs(const LuaObject& args) {
		duration = (int) (getArg<float>()(args, "duration") * 1000);
		show = getArg<bool>()(args, "show");
	}

	String print() const {
		StringBuffer msg;
		msg << className << "-" << duration << ":" << show;

		return msg.toString();
	}

private:
	int duration;
	bool show;
};

class SetAttackPosture : public Behavior {
public:
	SetAttackPosture(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	SetAttackPosture(const SetAttackPosture& b) : Behavior(b) {
	}

	SetAttackPosture& operator=(const SetAttackPosture& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		Time* postureSet = agent->getPostureSet();

		if (postureSet == nullptr || !postureSet->isPast())
			return FAILURE;

		if (System::random(100) > 98 && !agent->isDizzied()) {
			WeaponObject* weapon = agent->getWeapon();

			if (weapon == nullptr || !weapon->isRangedWeapon())
				return FAILURE;

			ManagedReference<SceneObject*> target = nullptr;

			if (agent->peekBlackboard("targetProspect"))
				target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >().get();

			if (target == nullptr)
				return FAILURE;

			postureSet->updateToCurrentTime();
			postureSet->addMiliTime(20 * 1000);

			Locker clocker(target,agent);

			float sqrDist = agent->getPosition().squaredDistanceTo(target->getPosition());

			if (sqrDist > 25 * 25) {
				agent->enqueueCommand(STRING_HASHCODE("prone"), 0, 0, "");
			} else {
				agent->enqueueCommand(STRING_HASHCODE("kneel"), 0, 0, "");
			}
			return SUCCESS;
		}

		return FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}
};

class ContrabandScan : public Behavior {
public:
	ContrabandScan(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	ContrabandScan(const ContrabandScan& b) : Behavior(b) {
	}

	ContrabandScan& operator=(const ContrabandScan& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);

		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> target = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >().get();

		if (target == nullptr)
			return FAILURE;

		if (!agent->checkCooldownRecovery("crackdown_scan"))
			return FAILURE;

		Zone* zone = agent->getZone();

		if (zone == nullptr)
			return FAILURE;

		GCWManager* gcwMan = zone->getGCWManager();

		if (gcwMan == nullptr)
			return FAILURE;

		Locker clocker(target, agent);

		return gcwMan->runCrackdownScan(agent, target->asCreatureObject()) ? SUCCESS : FAILURE;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}

};

class HealTarget : public Behavior {
public:
	HealTarget(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	HealTarget(const HealTarget& b) : Behavior(b) {
	}

	HealTarget& operator=(const HealTarget& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);

		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<CreatureObject*> healTarget = nullptr;

		if (agent->peekBlackboard("healTarget"))
			healTarget = agent->readBlackboard("healTarget").get<ManagedReference<CreatureObject*> >().get();

		if (healTarget == nullptr || healTarget->isDead()) {
			agent->eraseBlackboard("healTarget");
			agent->setMovementState(AiAgent::FOLLOWING);
			return FAILURE;
		}

		bool healExecuted = false;
		float range = 7.5f;
		uint32 healerType = agent->getHealerType().toLowerCase().hashCode();

		if (healerType == STRING_HASHCODE("force")) {
			range = 32.f;
		}

		if (healTarget->getHAM(CreatureAttribute::HEALTH) < healTarget->getMaxHAM(CreatureAttribute::HEALTH) || healTarget->getHAM(CreatureAttribute::ACTION) < healTarget->getMaxHAM(CreatureAttribute::ACTION)) {
			agent->clearQueueActions();

			if (healTarget == agent) {
				agent->healTarget(healTarget);
				healExecuted = true;
			} else {
				if (agent->isInRange(healTarget, range)) {
					Locker clocker(healTarget, agent);

					agent->healTarget(healTarget);

					healExecuted = true;
				}
			}
		}

		if (healExecuted == true) {
			Time* healDelay = agent->getHealDelay();

			if (healDelay != nullptr) {
				healDelay->updateToCurrentTime();
				healDelay->addMiliTime(20 * 1000);
			}

			agent->eraseBlackboard("healTarget");
		}

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}
};

class SendChatGreeting : public Behavior {
public:
	SendChatGreeting(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	SendChatGreeting(const SendChatGreeting& b) : Behavior(b) {
	}

	SendChatGreeting& operator=(const SendChatGreeting& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);

		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> target = nullptr;

		if (agent->peekBlackboard("targetProspect"))
			target = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >().get();

		if (target == nullptr || !target->isPlayerCreature()) {
			return FAILURE;
		}

		CreatureObject* creoTarget = target->asCreatureObject();

		if (creoTarget == nullptr || (creoTarget->getCurrentSpeed() < creoTarget->getWalkSpeed() * 0.5))
			return FAILURE;

		Locker clocker(target, agent);

		if (!agent->hasReactionChatMessages() || agent->getParentUnsafe() != target->getParentUnsafe())
			return FAILURE;

		float sqrDist = agent->getWorldPosition().squaredDistanceTo(target->getWorldPosition());

		if (sqrDist > 35 * 35 || sqrDist < 25 * 25) // Between 35m and 25m
			return FAILURE;

		agent->faceObject(target, true);

		if (target->isFacingObject(agent))
			agent->sendReactionChat(target, ReactionManager::HI);
		else
			agent->sendReactionChat(target, ReactionManager::BYE);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}
};

class CallForHelp : public Behavior {
public:
	CallForHelp(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	CallForHelp(const CallForHelp& b) : Behavior(b) {
	}

	CallForHelp& operator=(const CallForHelp& b) {
		if (this == &b)
			return *this;
		Behavior::operator=(b);

		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		ManagedReference<SceneObject*> ally = nullptr;

		if (agent->peekBlackboard("allyProspect"))
			ally = agent->readBlackboard("allyProspect").get<ManagedReference<SceneObject*> >().get();

		if (ally == nullptr) {
			agent->eraseBlackboard("allyProspect");
			return FAILURE;
		}

		CreatureObject* allyCreo = ally->asCreatureObject();

		if (allyCreo == nullptr || allyCreo->isDead() || !allyCreo->isAiAgent()) {
			agent->eraseBlackboard("allyProspect");
			return FAILURE;
		}

		Locker clock(allyCreo, agent);

		Vector3 agentPosition = agent->getPosition();
		Vector3 allyPosition = allyCreo->getPosition();

		float sqrDistance = agentPosition.squaredDistanceTo(allyPosition);

		if (sqrDistance > 50 * 50) {
			agent->eraseBlackboard("allyProspect");
			return FAILURE;
		}

#ifdef DEBUG_CALLFORHELP
		ZoneServer* zoneServer = agent->getZoneServer();

		ChatManager* chatManager = nullptr;

		if (zoneServer != nullptr)
			chatManager = zoneServer->getChatManager();
#endif

		agent->clearPatrolPoints();
		agent->faceObject(ally, true);

		agent->setMovementState(AiAgent::NOTIFY_ALLY);
		agent->setNextPosition(allyPosition.getX(), allyPosition.getZ(), allyPosition.getY(), allyCreo->getParent().get().castTo<CellObject*>());

#ifdef DEBUG_CALLFORHELP
		if (chatManager != nullptr)
			chatManager->broadcastChatMessage(agent, "Heading to notify my ally", 0, 0, agent->getMoodID());
#endif

		AiAgent* allyAgent = allyCreo->asAiAgent();

		if (allyAgent == nullptr) {
			agent->eraseBlackboard("allyProspect");
			return FAILURE;
		}

		Time* allyTime = allyAgent->getLastCallForHelp();

		if (allyTime != nullptr) {
			allyTime->updateToCurrentTime();
			allyTime->addMiliTime(90 * 1000);
		}

		if (sqrDistance < 10 * 10) {
			Time* callForHelp = agent->getLastCallForHelp();

			if (callForHelp == nullptr)
				return FAILURE;

			callForHelp->updateToCurrentTime();
			callForHelp->addMiliTime(90 * 1000);

			ManagedReference<SceneObject*> enemyTarget = nullptr;

			if (agent->peekBlackboard("targetProspect"))
				enemyTarget = agent->readBlackboard("targetProspect").get<ManagedReference<SceneObject*> >().get();

			if (enemyTarget != nullptr) {

#ifdef DEBUG_CALLFORHELP
				if (chatManager != nullptr)
					chatManager->broadcastChatMessage(agent, "Notifying my ally", 0, 0, agent->getMoodID());
#endif

				Core::getTaskManager()->executeTask([allyAgent, enemyTarget] () {
					Locker lock(allyAgent);
					Locker enlocker(enemyTarget, allyAgent);

					allyAgent->addDefender(enemyTarget);

				}, "CallForHelpLambda");
			}

			agent->eraseBlackboard("allyProspect");
			agent->setMovementState(AiAgent::FOLLOWING);
		}

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}
};

class Rest : public Behavior {
public:
	Rest(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	Rest(const Rest& a) : Behavior(a) {
	}

	Rest& operator=(const Rest& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr)
			return FAILURE;

		Time* restDelay = agent->getRestDelay();

		if (restDelay == nullptr) {
			return FAILURE;
		}

		// Wait 5 minutes until we check if we should rest again
		int delay = 300 * 1000;

		restDelay->updateToCurrentTime();
		restDelay->addMiliTime(delay);

		agent->setMovementState(AiAgent::RESTING);

		// Chance to stop resting from 45s up to 2 minutes stored in ms
		int restingTime = delay - ((45 + System::random(45)) * 1000);
		agent->writeBlackboard("restingTime", restingTime);

		int speciesID = agent->getSpecies();
		bool canSitDown = false;

		Zone* zone = agent->getZone();

		// We are returning Success here since we have the state and delays set
		if (zone == nullptr)
			return SUCCESS;

		ManagedReference<CreatureManager*> creoManager = zone->getCreatureManager();

		if (creoManager != nullptr) {
			AiSpeciesData* speciesData = creoManager->getAiSpeciesData(speciesID);

			if (speciesData != nullptr) {
				canSitDown = speciesData->canSitDown();
			}
		}

		if (agent->isNpc() || (canSitDown && System::random(2) > 0)) {
			agent->setPosture(CreaturePosture::SITTING, true);
		} else {
			agent->setPosture(CreaturePosture::LYINGDOWN, true);
		}

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}
};

class StopResting : public Behavior {
public:
	StopResting(const String& className, const uint32 id, const LuaObject& args) : Behavior(className, id, args) {
	}

	StopResting(const StopResting& a) : Behavior(a) {
	}

	StopResting& operator=(const StopResting& a) {
		if (this == &a)
			return *this;
		Behavior::operator=(a);
		return *this;
	}

	Behavior::Status execute(AiAgent* agent, unsigned int startIdx = 0) const {
		if (agent == nullptr)
			return FAILURE;

		agent->setPosture(CreaturePosture::UPRIGHT, true);
		agent->setMovementState(AiAgent::PATROLLING);

		return SUCCESS;
	}

	String print() const {
		StringBuffer msg;
		msg << className;

		return msg.toString();
	}
};


}
}
}
}
}
}
}

#endif // SIMPLEACTIONS_H_
