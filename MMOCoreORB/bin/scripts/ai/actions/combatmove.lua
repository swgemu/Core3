require("ai.actions.move")
require("ai.interrupts")

CombatMoveBase = createClass(Move)

function CombatMoveBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		
		if (agent:getCurrentSpeed() > 0) then 
			agent:completeMove()
		end
		
		self:findNextPosition(pAgent)
		if agent:getTargetOfTargetID() == agent:getObjectID() then agent:broadcastInterrupt(STARTCOMBAT) end
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end

CombatMove = createClass(CombatMoveBase, Interrupt)
CombatMovePet = createClass(CombatMoveBase, PetInterrupt)

function CombatMovePet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		local creature = LuaCreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			return true
		end
	end
	return false
end