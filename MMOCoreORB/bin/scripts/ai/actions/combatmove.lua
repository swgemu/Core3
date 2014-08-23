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
CombatMovePet = createClass(CombatMoveBase, PetInterrupt)

function CombatMovePet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			return true
		end
	end
	return false
end

function CombatMovePet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end