FindNextPosition = {}

function FindNextPosition:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local creature = LuaCreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT) then
			return true
		end
		-- should also send a stand instruction here (postureRecovery)
	end
	return false
end

function FindNextPosition:start(pAgent)
	return 0
end

function FindNextPosition:terminate(pAgent)
	return 0
end

function FindNextPosition:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance())) then
			return BEHAVIOR_SUCCESS
		else
			return BEHAVIOR_FAILURE
		end
	end
	return BEHAVIOR_FAILURE
end

addAiBehavior("FindNextPosition")