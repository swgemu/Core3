Sequence = {}

function Sequence:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Sequence checking...")
	end
	return 1
end

function Sequence:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Sequence start...")
	end
	return 0
end

function Sequence:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Sequence end...")
	end
	return 0
end

function Sequence:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Sequence do...")
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end

addAiBehavior("Sequence", SEQUENCEBEHAVIOR)