-- The definitons for move-related base classes (anything that would derive from MoveBase alone)
require("ai.ai")

MoveBase = createClass(Ai)

function MoveBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			if agent:shouldRetreat(256) then
				agent:leash()
				return false
			end
			return true
		end
	end
	return false
end

function MoveBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)

		if (agent:getCurrentSpeed() > 0) then
			agent:completeMove()
		end

		if (self:findNextPosition(pAgent)) then
			return BEHAVIOR_RUNNING
		else
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

-- default action is to run
function MoveBase:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), false)) then
			return true
		end
	end
	return false
end

MovePetBase = createClass(MoveBase)

function MovePetBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent1(pAgent)

		if (agent:getCurrentSpeed() > 0) then
			agent:completeMove()
		end
		local Ptarget = agent:getFollowObject()

		if (Ptarget ~= nil and not agent:checkRange(Ptarget,156)) then
			local scno = SceneObject1(Ptarget)
			if (scno ~= nil) then
				SceneObject2(pAgent):teleport(scno:getPositionX(), scno:getPositionZ(), scno:getPositionY(), scno:getParentID())
			end
		end

		if (self:findNextPosition(pAgent)) then
			return BEHAVIOR_RUNNING
		else
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

function MovePetBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:getFollowState() ~= OBLIVIOUS) then
			agent:setDestination()
			return true
		end
	end
	return false
end

MoveEscortBase = createClass(MovePetBase)

function MoveEscortBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent1(pAgent)

		if (agent:getCurrentSpeed() > 0) then
			agent:completeMove()
		end
		local Ptarget = agent:getFollowObject()

		if (Ptarget ~= nil and not agent:checkRange(Ptarget,156)) then
			return BEHAVIOR_SUCCESS
		end

		if (self:findNextPosition(pAgent)) then
			return BEHAVIOR_RUNNING
		else
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

CombatMoveBase = createClass(MoveBase)

function CombatMoveBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)

		if (agent:getCurrentSpeed() > 0) then
			agent:completeMove()
		end

		self:findNextPosition(pAgent)

		agent = AiAgent(pAgent) --reset our pointer to agent
		if agent:getTargetOfTargetID() == agent:getObjectID() then agent:broadcastInterrupt(STARTCOMBAT) end
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end

WalkBase = createClass(MoveBase)

-- overrides so that we walk instead of run
function WalkBase:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), true)) then
			return true
		end
	end
	return false
end

MoveVillageRaiderBase = createClass(MoveBase)

function MoveVillageRaiderBase:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), agent:isInRangeOfHome(20))) then
			return true
		end
	end
	return false
end
