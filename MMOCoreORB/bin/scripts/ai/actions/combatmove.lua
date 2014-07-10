CombatMove = Move:new {}

function CombatMove:doAction(pAgent)
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