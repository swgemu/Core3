NonDeterministicSequence = {}

function NonDeterministicSequence:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSequence checking...")
	end
	return 1
end

function NonDeterministicSequence:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSequence start...")
	end
	return 0
end

function NonDeterministicSequence:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSequence end...")
	end
	return 0
end

function NonDeterministicSequence:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("NonDeterministicSequence do...")
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end

addAiBehavior("NonDeterministicSequence", NONDETERMINISTICSEQUENCEBEHAVIOR)