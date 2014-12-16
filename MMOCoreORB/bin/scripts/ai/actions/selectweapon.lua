require("ai.ai")
require("ai.interrupts")

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
		
		if (getRandomNumber(10) == 0) then
			agent:selectDefaultWeapon()
		else
			agent:selectWeapon()
		end
		
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end

SelectWeapon = createClass(SelectWeaponBase, Interrupt)
SelectWeaponCreaturePet = createClass(SelectWeaponBase, CreaturePetInterrupt)
SelectWeaponDroidPet = createClass(SelectWeaponBase, DroidPetInterrupt)
SelectWeaponFactionPet = createClass(SelectWeaponBase, FactionPetInterrupt)

function SelectWeaponCreaturePet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end

function SelectWeaponDroidPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end
function SelectWeaponFactionPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end