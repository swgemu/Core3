require("ai.ai")
require("ai.interrupts")

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

Move = createClass(MoveBase, Interrupt)
MoveDefault = createClass(MoveBase, DefaultInterrupt)
MovePack = createClass(MoveBase, PackInterrupt)
MoveCreaturePet = createClass(MoveBase, CreaturePetInterrupt)
MoveDroidPet = createClass(MoveBase, DroidPetInterrupt)
MoveFactionPet = createClass(MoveBase, FactionPetInterrupt)

function MoveCreaturePet:checkConditions(pAgent)
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

function MoveCreaturePet:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)

		if (agent:getCurrentSpeed() > 0) then 
			agent:completeMove()
		end

		self:findNextPosition(pAgent)
		return BEHAVIOR_RUNNING
	end
	return BEHAVIOR_FAILURE
end

function MoveDroidPet:checkConditions(pAgent)
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

function MoveDroidPet:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)

		if (agent:getCurrentSpeed() > 0) then 
			agent:completeMove()
		end

		self:findNextPosition(pAgent)
		return BEHAVIOR_RUNNING
	end
	return BEHAVIOR_FAILURE
end


function MoveFactionPet:checkConditions(pAgent)
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

function MoveFactionPet:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)

		if (agent:getCurrentSpeed() > 0) then 
			agent:completeMove()
		end

		self:findNextPosition(pAgent)
		return BEHAVIOR_RUNNING
	end
	return BEHAVIOR_FAILURE
end
