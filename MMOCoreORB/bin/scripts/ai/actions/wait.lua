Wait = Ai:new {}

function Wait:start(pAgent)
	self:setWait(pAgent)
	
	createObserver(STARTCOMBAT, "Wait", "interrupt", pAgent)
	return 0
end

function Wait:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		local waitTime = agent:getWait()
		if (waitTime ~= 0) then
			agent:setWait(0)
			return BEHAVIOR_RUNNING
		end
	end
	return BEHAVIOR_SUCCESS
end

function Wait:terminate(pAgent)
	dropObserver(STARTCOMBAT, pAgent)
	return 0
end

-- By default, wait indefinitely
function Wait:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(-1)
	end
end