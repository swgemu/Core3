Wait10 = Ai:new {}

function Wait10:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(10)
	end
	
	createObserver(DAMAGERECEIVED, "Wait10", "interrupt", pAgent)
	createObserver(STARTCOMBAT, "Wait10", "interrupt", pAgent)
	createObserver(DEFENDERADDED, "Wait10", "interrupt", pAgent)
	createObserver(DEFENDERDROPPED, "Wait10", "interrupt", pAgent)
	return 0
end

function Wait10:doAction(pAgent)
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

function Wait10:terminate(pAgent)
	dropObserver(DAMAGERECEIVED, pAgent)
	dropObserver(STARTCOMBAT, pAgent)
	dropObserver(DEFENDERADDED, pAgent)
	dropObserver(DEFENDERDROPPED, pAgent)
	return 0
end