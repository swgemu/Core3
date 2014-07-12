Sequence = Ai:new {}

function Sequence:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Sequence checking...")
	end
	return true
end

function Sequence:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Sequence start...")
	end
	return 0
end

function Sequence:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Sequence end...")
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

function Sequence:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Sequence do...")
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end