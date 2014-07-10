GetTarget = Ai:new {}

function GetTarget:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local creature = LuaCreatureObject(pAgent)
		
		if (creature:isDead()) then
			local agent = LuaAiAgent(pAgent)
			agent:removeDefenders()
			agent:setFollowObject(nil)
			return false
		end
		
		return true
	end
	return false
end

function GetTarget:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		local creature = LuaCreatureObject(pAgent)
		
		agent:getTargetFromMap()
		if (agent:validateTarget() and not (agent:followHasState(PEACE) and math.random(creature:getLevel()) == 1)) then
			return BEHAVIOR_SUCCESS
		else
			agent:removeDefender()
		end
		
		agent:getTargetFromDefenders()
		if (agent:validateTarget() and not (agent:followHasState(PEACE) and math.random(creature:getLevel()) == 1)) then
			return BEHAVIOR_SUCCESS
		else
			agent:removeDefender()
		end
	end
	return BEHAVIOR_FAILURE
end