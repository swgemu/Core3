Failure = Ai:new {}

function Failure:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Failure check...")
	end
	return true
end

function Failure:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Failure start...")
	end
	return 0
end

function Failure:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Failure end...")
	end
	return 0
end

function Failure:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Failure do...")
	end
	return BEHAVIOR_FAILURE
end