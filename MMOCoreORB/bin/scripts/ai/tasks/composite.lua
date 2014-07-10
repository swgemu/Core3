Composite = {}

function Composite:checkConditions(pAgent)
	return 1
end

function Composite:start(pAgent)
	return 0
end

function Composite:terminate(pAgent)
	return 0
end

function Composite:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end