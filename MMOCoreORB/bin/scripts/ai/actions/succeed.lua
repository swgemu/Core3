Succeed = {}

function Succeed:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Succeed check...")
	end
	return 1
end

function Succeed:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Succeed start...")
	end
	return 0
end

function Succeed:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Succeed end...")
	end
	return 0
end

function Succeed:doAction(pAgent)
	spatialChat(pAgent, "Hello there!")
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Succeed do...")
	end
	return BEHAVIOR_SUCCESS
end

addAiBehavior("Succeed", BEHAVIOR)