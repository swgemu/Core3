require("ai.ai")
require("ai.interrupts")

GetTargetBase = createClass(Ai)

function GetTargetBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local creature = CreatureObject(pAgent)

		if (creature:isDead()) then
			local agent = AiAgent(pAgent)
			agent:clearCombatState(true)
			agent:setOblivious()
			return false
		end

		return true
	end
	return false
end

function GetTargetBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		local ranLevel = getRandomNumber(creature:getLevel())

		local pTarget = agent:getTargetFromMap()
		--print(pTarget)
		if pTarget ~= nil and pTarget ~= agent:getFollowObject() then
		--print("1")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
		--print("2")
			if agent:followHasState(PEACE) and ranLevel == 1 and not agent:isAggressiveTo(pTarget) then
				agent:clearCombatState(true)
				agent:setOblivious()
				return BEHAVIOR_FAILURE
			end
			agent:setDefender(pTarget)
			return BEHAVIOR_SUCCESS
		end

		pTarget = agent:getTargetFromDefenders()
		--print(pTarget)
		if pTarget ~= nil and pTarget ~= agent:getFollowObject() then
		--print("3")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
		--print("4")
			if agent:followHasState(PEACE) and ranLevel == 1 and not agent:isAggressiveTo(pTarget) then
				agent:clearCombatState(true)
				agent:setOblivious()
				return BEHAVIOR_FAILURE
			end
			agent:setDefender(pTarget)
			return BEHAVIOR_SUCCESS
		end
		
		if (agent:isInCombat()) then
		--print("5")
			agent:clearCombatState(true)
			agent:setOblivious()
		end
		--print("6")
	end
	return BEHAVIOR_FAILURE
end

GetTarget = createClass(GetTargetBase, Interrupt)
GetTargetCreaturePet = createClass(GetTargetBase, CreaturePetInterrupt)
GetTargetDroidPet = createClass(GetTargetBase, DroidPetInterrupt)
GetTargetFactionPet = createClass(GetTargetBase, FactionPetInterrupt)

function GetTargetCreaturePet:doAction(pAgent)
	if (pAgent ~= nil) then
		--print("1")
		local agent = AiAgent(pAgent)
		
		local command = agent:getLastCommand()
		if (command ~= PET_ATTACK and command ~= PET_GUARD and command ~= PET_SPECIAL_ATTACK1 and command ~= PET_SPECIAL_ATTACK2 and command ~= PET_PATROL) then
			return BEHAVIOR_FAILURE	
		end

		if (command ~= PET_GUARD and command ~= PET_PATROL ) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
				if agent:validateTarget(pTarget) then
					agent:setFollowObject(pTarget)
					agent:setDefender(pTarget)
					return BEHAVIOR_SUCCESS
				end
			elseif pTarget ~= nil and agent:validateFollow() then
				return BEHAVIOR_SUCCESS
			else
				agent:setLastCommandTarget(nil)
			end
		end

		local creature = CreatureObject(pAgent)

		local pTarget = agent:getTargetFromMap()
		--print(pTarget)
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			--print("2")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			--print("5")
			return BEHAVIOR_SUCCESS
		end


		pTarget = agent:getTargetFromDefenders()
		--print(pTarget)
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			--print("6")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			--print("9")
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

function GetTargetCreaturePet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE and agent:getFollowState() ~= PATROLLING then agent:restoreFollowObject() end
	end
	return 0
end


function GetTargetDroidPet:doAction(pAgent)
	if (pAgent ~= nil) then
		--print("1")
		local agent = AiAgent(pAgent)
		
		local command = agent:getLastCommand()
		if (command ~= PET_ATTACK and command ~= PET_GUARD and command ~= PET_PATROL ) then
			return BEHAVIOR_FAILURE	
		end

		if (command == PET_ATTACK ) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
				if agent:validateTarget(pTarget) then
					agent:setFollowObject(pTarget)
					agent:setDefender(pTarget)
					return BEHAVIOR_SUCCESS
				end
			elseif pTarget ~= nil and agent:validateFollow() then
				return BEHAVIOR_SUCCESS
			else
				agent:setLastCommandTarget(nil)
			end
		end

		local creature = CreatureObject(pAgent)

		local pTarget = agent:getTargetFromMap()
		--print(pTarget)
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			--print("2")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			--print("5")
			return BEHAVIOR_SUCCESS
		end


		pTarget = agent:getTargetFromDefenders()
		--print(pTarget)
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			--print("6")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			--print("9")
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

function GetTargetDroidPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE and agent:getFollowState() ~= PATROLLING then agent:restoreFollowObject() end
	end
	return 0
end


function GetTargetFactionPet:doAction(pAgent)
	if (pAgent ~= nil) then
		--print("1")
		local agent = AiAgent(pAgent)
		
		local command = agent:getLastCommand()
		if (command ~= PET_ATTACK and command ~= PET_GUARD and command ~= PET_PATROL) then
			return BEHAVIOR_FAILURE	
		end

		if (command == PET_ATTACK) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
				if agent:validateTarget(pTarget) then
					agent:setFollowObject(pTarget)
					agent:setDefender(pTarget)
					return BEHAVIOR_SUCCESS
				end
			elseif pTarget ~= nil and agent:validateFollow() then
				return BEHAVIOR_SUCCESS
			else
				agent:setLastCommandTarget(nil)
			end
		end

		local creature = CreatureObject(pAgent)

		local pTarget = agent:getTargetFromMap()
		--print(pTarget)
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			--print("2")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			--print("5")
			return BEHAVIOR_SUCCESS
		end


		pTarget = agent:getTargetFromDefenders()
		--print(pTarget)
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			--print("6")
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			--print("9")
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

function GetTargetFactionPet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE and agent:getFollowState() ~= PATROLLING then agent:restoreFollowObject() end
	end
	return 0
end
