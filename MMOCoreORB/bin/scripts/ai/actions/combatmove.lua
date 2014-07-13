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
		agent:broadcastInterrupt(STARTCOMBAT)
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end

CombatMove = createClass(CombatMoveBase, Interrupt)