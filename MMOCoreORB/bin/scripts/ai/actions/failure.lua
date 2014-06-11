Failure = {}

function Failure:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Failure check...")
	end
	return 1
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
	spatialChat(pAgent, "Hello there!")
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Failure do...")
	end
	return BEHAVIOR_FAILURE
end

addAiBehavior("Failure")