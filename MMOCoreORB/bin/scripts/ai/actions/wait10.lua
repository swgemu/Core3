Wait10 = Ai:new {}

function Wait10:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(10)
	end
	
	createObserver(DAMAGERECEIVED, "Move", "interrupt", pAgent)
	createObserver(STARTCOMBAT, "Move", "interrupt", pAgent)
	createObserver(DEFENDERADDED, "Move", "interrupt", pAgent)
	createObserver(DEFENDERDROPPED, "Move", "interrupt", pAgent)
	return 0
end

function Wait10:terminate(pAgent)
	dropObserver(DAMAGERECEIVED, pAgent)
	dropObserver(STARTCOMBAT, pAgent)
	dropObserver(DEFENDERADDED, pAgent)
	dropObserver(DEFENDERDROPPED, pAgent)
	return 0
end

addAiBehavior("Wait10")