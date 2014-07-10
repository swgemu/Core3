Succeed = Ai:new {}

function Succeed:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Succeed check...")
	end
	return true
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
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("Succeed do...")
	end
	return BEHAVIOR_SUCCESS
end