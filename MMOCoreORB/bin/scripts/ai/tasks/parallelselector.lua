ParallelSelector = Ai:new {}

function ParallelSelector:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSelector checking...")
	end
	return 1
end

function ParallelSelector:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSelector start...")
	end
	return 0
end

function ParallelSelector:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSelector end...")
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

function ParallelSelector:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("ParallelSelector do...")
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end