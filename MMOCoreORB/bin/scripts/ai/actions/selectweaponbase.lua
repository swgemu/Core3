require("ai.ai")

SelectWeaponBase = createClass(Ai)

function SelectWeaponBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local creature = CreatureObject(pAgent)
		
		if (creature:isDead()) then
			local agent = AiAgent(pAgent)
			agent:removeDefenders()
			agent:setFollowObject(nil)
			return false
		end
		
		return true
	end
	return false
end

function SelectWeaponBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)

		agent:selectWeapon()
		
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end
