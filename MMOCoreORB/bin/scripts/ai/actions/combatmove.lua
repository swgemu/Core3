require("ai.actions.move")
require("ai.interrupts")

--CombatMove = Move:new {}
CombatMoveBase = createClass(Move)

function CombatMoveBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		
		if (agent:getCurrentSpeed() > 0) then 
			agent:completeMove()
		end
		
		self:findNextPosition(pAgent)
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end

CombatMove = createClass(CombatMoveBase, Interrupt)