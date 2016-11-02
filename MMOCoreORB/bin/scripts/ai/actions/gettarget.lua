require("ai.actions.gettargetbase")

function GetTargetCreaturePet:doAction(pAgent)
	if (pAgent ~= nil) then
		--print("1")
		local agent = AiAgent(pAgent)

		local command = agent:getLastCommand()
		if (command ~= PET_ATTACK and command ~= PET_GUARD and command ~= PET_SPECIAL_ATTACK1 and command ~= PET_SPECIAL_ATTACK2 and command ~= PET_PATROL) then
			return BEHAVIOR_FAILURE
		end

		if (command == PET_GUARD) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget == agent:getFollowObject()) then
				local pNewTarget = agent:getTargetFromTargetsDefenders()
				if agent:validateTarget(pNewTarget) then
					agent:setFollowObject(pNewTarget)
					agent:setDefender(pNewTarget)
					return BEHAVIOR_SUCCESS
				end
			elseif agent:validateFollow() then
				return BEHAVIOR_SUCCESS
			end
		elseif (command ~= PET_PATROL ) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
				if agent:validateTarget(pTarget) then
					agent:setFollowObject(pTarget)
					agent:setDefender(pTarget)
					return BEHAVIOR_SUCCESS
				else
					agent:setLastCommandTarget(nil)
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

		if (command == PET_GUARD) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget == agent:getFollowObject()) then
				local pNewTarget = agent:getTargetFromTargetsDefenders()
				if agent:validateTarget(pNewTarget) then
					agent:setFollowObject(pNewTarget)
					agent:setDefender(pNewTarget)
					return BEHAVIOR_SUCCESS
				end
			elseif agent:validateFollow() then
				return BEHAVIOR_SUCCESS
			end
		elseif (command == PET_ATTACK ) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
				if agent:validateTarget(pTarget) then
					agent:setFollowObject(pTarget)
					agent:setDefender(pTarget)
					return BEHAVIOR_SUCCESS
				else
					agent:setLastCommandTarget(nil)
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

		if (command == PET_GUARD) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget == agent:getFollowObject()) then
				local pNewTarget = agent:getTargetFromTargetsDefenders()
				if agent:validateTarget(pNewTarget) then
					agent:setFollowObject(pNewTarget)
					agent:setDefender(pNewTarget)
					return BEHAVIOR_SUCCESS
				end
			elseif agent:validateFollow() then
				return BEHAVIOR_SUCCESS
			end
		elseif (command == PET_ATTACK) then
			local pTarget = agent:getLastCommandTarget()
			if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
				if agent:validateTarget(pTarget) then
					agent:setFollowObject(pTarget)
					agent:setDefender(pTarget)
					return BEHAVIOR_SUCCESS
				else
					agent:setLastCommandTarget(nil)
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

function GetTargetVillageRaider:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)

		local pTarget = agent:getTargetFromMap()

		if pTarget ~= nil and pTarget ~= agent:getFollowObject() then
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			agent:setDefender(pTarget)
			return BEHAVIOR_SUCCESS
		end

		pTarget = agent:getTargetFromDefenders()

		if pTarget ~= nil and pTarget ~= agent:getFollowObject() then
			if agent:validateTarget(pTarget) then
				agent:setFollowObject(pTarget)
				agent:setDefender(pTarget)
				return BEHAVIOR_SUCCESS
			end
		elseif pTarget ~= nil and agent:validateFollow() then
			agent:setDefender(pTarget)
			return BEHAVIOR_SUCCESS
		end

		if (agent:isInCombat()) then
			agent:clearCombatState(true)
			agent:setOblivious()
		end
	end

	return BEHAVIOR_FAILURE
end
