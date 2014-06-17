Wait10 = {}

function Wait10:checkConditions(pAgent)
	return true
end

function Wait10:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(10)
	end
	return 0
end

function Wait10:terminate(pAgent)
	return 0
end

function Wait10:doAction(pAgent)
	return BEHAVIOR_SUCCESS
end

addAiBehavior("Wait10")