Move = {}

function Move:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		local creature = LuaCreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			return true
		end
	end
	return false
end

function Move:start(pAgent)
	return 0
end

function Move:terminate(pAgent)
	return 0
end

function Move:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		
		if (agent:getCurrentSpeed() > 0) then 
			agent:completeMove()
		end
		
		if (agent:findNextPosition(agent:getMaxDistance())) then
			return BEHAVIOR_RUNNING
		else
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

addAiBehavior("Move")