require("ai.ai")

GetTargetBase = createClass(Ai)

function GetTargetBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local creature = CreatureObject(pAgent)

		if (creature:isDead()) then
			local agent = AiAgent(pAgent)
			agent:clearCombatState(true)
			agent:setOblivious()
			agent:info("check conditions target for skipped dead target")
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
