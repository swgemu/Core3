NonDeterministicSelector = {}

function NonDeterministicSelector:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSelector checking...")
	end
	return 1
end

function NonDeterministicSelector:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSelector start...")
	end
	return 0
end

function NonDeterministicSelector:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSelector end...")
	end
	return 0
end

function NonDeterministicSelector:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSelector do...")
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end

addAiBehavior("NonDeterministicSelector", NONDETERMINISTICSELECTORBEHAVIOR)