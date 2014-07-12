Selector = Ai:new {}

function Selector:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Selector checking...")
	end
	return true
end

function Selector:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Selector start...")
	end
	return 0
end

function Selector:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Selector end...")
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

function Selector:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		--agent:info("Selector do...")
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end