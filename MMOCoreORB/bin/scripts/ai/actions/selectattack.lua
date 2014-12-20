require("ai.ai")
require("ai.interrupts")
local ObjectManager = require("managers.object.object_manager")

SelectAttackBase = createClass(Ai)

function SelectAttackBase:checkConditions(pAgent)
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

function SelectAttackBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local creature = CreatureObject(pAgent)
		
		if (creature:getQueueSize() > 3) then
			return BEHAVIOR_SUCCESS
		end
		
    local agent = AiAgent(pAgent)
		
		agent:selectSpecialAttack(-1)
		if (not agent:validateStateAttack() or getRandomNumber(5) == 1) then
			agent:selectDefaultAttack()
		end
		
		agent:enqueueAttack()
		
		return BEHAVIOR_SUCCESS
	end
	return BEHAVIOR_FAILURE
end

SelectAttack = createClass(SelectAttackBase, Interrupt)
SelectAttackCreaturePet = createClass(SelectAttackBase, CreaturePetInterrupt)
SelectAttackDroidPet = createClass(SelectAttackBase, DroidPetInterrupt)
SelectAttackFactionPet = createClass(SelectAttackBase, FactionPetInterrupt)

function SelectAttackCreaturePet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end


function SelectAttackDroidPet:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if ObjectManager.withCreatureObject(pAgent, function(creo) return not creo:isCombatDroidPet() end) then
			-- get the attack against us
			local pTarget = agent:getTargetFromDefenders()
			if not ObjectManager.withSceneObject(pAgent, function(scno) return scno:isInRangeWithObject(pTarget, 10) end) then 
				agent:setOblivious()
				agent:restoreFollowObject()
				agent:clearCombatState(true)			
				return BEHAVIOUR_SUSPEND
			end
			agent:runAway(pTarget, 32)
			return BEHAVIOR_SUCCESS
		else
			return SelectAttackBase:doAction(pAgent)			
		end		
	end
end

function SelectAttackDroidPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end

function SelectAttackFactionPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
end
