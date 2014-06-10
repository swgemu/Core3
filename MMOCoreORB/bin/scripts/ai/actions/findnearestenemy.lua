FindNearestEnemy = {}

function FindNearestEnemy:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("check...")
	end
	return 1
end

function FindNearestEnemy:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("start...")
	end
	return 0
end

function FindNearestEnemy:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("end...")
	end
	return 0
end

function FindNearestEnemy:doAction(pAgent)
	spatialChat(pAgent, "Hello there!")
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:info("do...")
	end
	return BEHAVIOR_SUCCESS
end

addAiBehavior("FindNearestEnemy", BEHAVIOR)