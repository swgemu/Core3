Walk = Move:new {}

function Walk:start(pAgent)
	createObserver(DAMAGERECEIVED, "Walk", "interrupt", pAgent)
	createObserver(STARTCOMBAT, "Walk", "interrupt", pAgent)
	createObserver(DEFENDERADDED, "Walk", "interrupt", pAgent)
	createObserver(DEFENDERDROPPED, "Walk", "interrupt", pAgent)
	return 0
end

function Walk:terminate(pAgent)
	dropObserver(DAMAGERECEIVED, pAgent)
	dropObserver(STARTCOMBAT, pAgent)
	dropObserver(DEFENDERADDED, pAgent)
	dropObserver(DEFENDERDROPPED, pAgent)
	return 0
end

-- overrides so that we walk instead of run
function Walk:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), true)) then
			return true
		end
	end
	return false
end