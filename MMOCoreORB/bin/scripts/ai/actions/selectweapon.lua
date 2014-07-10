SelectWeapon = Ai:new {}

function SelectWeapon:checkConditions(pAgent)
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

function SelectWeapon:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		
		if (math.random(10) == 0) then
			agent:selectDefaultWeapon()
		else
			agent:selectWeapon()
		end
		
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end