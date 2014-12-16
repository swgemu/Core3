require("ai.actions.move")
require("ai.interrupts")

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

CombatMove = createClass(CombatMoveBase, Interrupt)
CombatMoveCreaturePet = createClass(CombatMoveBase, CreaturePetInterrupt)
CombatMoveDroidPet = createClass(CombatMoveBase, DroidPetInterrupt)
CombatMoveFactionPet = createClass(CombatMoveBase, FactionPetInterrupt)

function CombatMoveCreaturePet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			return true
		end
	end
	return false
end

function CombatMoveCreaturePet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end

function CombatMoveDroidPet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			return true
		end
	end
	return false
end

function CombatMoveDroidPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end

function CombatMoveFactionPet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			return true
		end
	end
	return false
end

function CombatMoveFactionPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end