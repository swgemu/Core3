require("ai.ai")
require("ai.interrupts")

GetTargetBase = createClass(Ai)

function GetTargetBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local creature = LuaCreatureObject(pAgent)

		if (creature:isDead()) then
			local agent = LuaAiAgent(pAgent)
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
		local agent = LuaAiAgent(pAgent)
		local creature = LuaCreatureObject(pAgent)
		local ranLevel = math.random(creature:getLevel())

		local pTarget = agent:getTargetFromMap()
		if (pTarget ~= agent:getFollowObject()) then
			agent:setFollowObject(pTarget)
			if (pTarget ~= nil) then agent:setDefender(pTarget) end
			if (agent:validateTarget()) then
				return BEHAVIOR_SUCCESS
			else
				agent:removeDefender()
			end
		elseif pTarget ~= nil and agent:validateTarget() then
			if agent:followHasState(PEACE) and ranLevel == 1 then
				agent:clearCombatState(true)
				agent:setOblivious()
				return BEHAVIOR_FAILURE
			end
			agent:setDefender(pTarget)
			return BEHAVIOR_SUCCESS
		end

		pTarget = agent:getTargetFromDefenders()
		if (pTarget ~= agent:getFollowObject()) then
			agent:setFollowObject(pTarget)
			if (pTarget ~= nil) then agent:setDefender(pTarget) end
			if (agent:validateTarget()) then
				return BEHAVIOR_SUCCESS
			else
				agent:removeDefender()
			end
		elseif pTarget ~= nil and agent:validateTarget() then
			if agent:followHasState(PEACE) and ranLevel == 1 then
				agent:clearCombatState(true)
				agent:setOblivious()
				return BEHAVIOR_FAILURE
			end
			agent:setDefender(pTarget)
			return BEHAVIOR_SUCCESS
		end
		
		if (agent:isInCombat()) then
		print("5")
			agent:clearCombatState(true)
			agent:setOblivious()
		end
	end
	return BEHAVIOR_FAILURE
end

GetTarget = createClass(GetTargetBase, Interrupt)
GetTargetPet = createClass(GetTargetBase, PetInterrupt)

function GetTargetPet:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		local creature = LuaCreatureObject(pAgent)

		local pTarget = agent:getTargetFromMap()
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			agent:setFollowObject(pTarget)
			agent:setDefender(pTarget)
			if (agent:validateTarget()) then
				return BEHAVIOR_SUCCESS
			else
				agent:removeDefender()
			end
		elseif pTarget ~= nil and agent:validateTarget() then
			return BEHAVIOR_SUCCESS
		end


		pTarget = agent:getTargetFromDefenders()
		if (pTarget ~= nil and pTarget ~= agent:getFollowObject()) then
			agent:setFollowObject(pTarget)
			agent:setDefender(pTarget)
			if (agent:validateTarget()) then
				return BEHAVIOR_SUCCESS
			else
				agent:removeDefender()
			end
		elseif pTarget ~= nil and agent:validateTarget() then
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end