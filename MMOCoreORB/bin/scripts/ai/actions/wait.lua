Wait = Ai:new {}

function Wait:start(pAgent)
	self:setWait(pAgent)
	
	createObserver(STARTCOMBAT, "Wait", "interrupt", pAgent)
	return 0
end

function Wait:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		if (agent:isWaiting()) then
			return BEHAVIOR_RUNNING
		end
	end
	return BEHAVIOR_SUCCESS
end

function Wait:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(0)
	end
	
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