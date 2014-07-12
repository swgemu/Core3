ParallelSequence = Ai:new {}

function ParallelSequence:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSequence checking...")
	end
	return 1
end

function ParallelSequence:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSequence start...")
	end
	return 0
end

function ParallelSequence:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSequence end...")
		local res = agent:getBehaviorStatus()
		if (res == BEHAVIOR_SUCCESS) then
			agent:spatialChat("I have finished successfully.")
			agent:info("Success!")
		elseif (res == BEHAVIOR_FAILURE) then 
			agent:spatialChat("I have finished in failure.")
			agent:info("Failure!")
		end
	end
	return 0
end

function ParallelSequence:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSequence do...")
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end