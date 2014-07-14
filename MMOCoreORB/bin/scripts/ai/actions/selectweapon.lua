require("ai.ai")
require("ai.interrupts")

SelectWeaponBase = createClass(Ai)

function SelectWeaponBase:checkConditions(pAgent)
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

function SelectWeaponBase:doAction(pAgent)
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

SelectWeapon = createClass(SelectWeaponBase, Interrupt)
SelectWeaponPet = createClass(SelectWeaponBase, PetInterrupt)