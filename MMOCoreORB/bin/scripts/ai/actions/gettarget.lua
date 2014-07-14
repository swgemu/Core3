require("ai.ai")
require("ai.interrupts")

GetTargetBase = createClass(Ai)

function GetTargetBase:checkConditions(pAgent)
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

function GetTargetBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		local creature = LuaCreatureObject(pAgent)

		local pTarget = agent:getTargetFromMap()
		if (pTarget ~= agent:getFollowObject()) then
			agent:setFollowObject(pTarget)
			if (pTarget ~= nil) then agent:setDefender(pTarget) end
			if (agent:validateTarget() and not (agent:followHasState(PEACE) and math.random(creature:getLevel()) == 1)) then
				return BEHAVIOR_SUCCESS
			else
				agent:removeDefender()
			end
		end

		pTarget = agent:getTargetFromDefenders()
		if (pTarget ~= agent:getFollowObject()) then
			agent:setFollowObject(pTarget)
			if (pTarget ~= nil) then agent:setDefender(pTarget) end
			if (agent:validateTarget() and not (agent:followHasState(PEACE) and math.random(creature:getLevel()) == 1)) then
				return BEHAVIOR_SUCCESS
			else
				agent:removeDefender()
			end
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
		end
	end
	return BEHAVIOR_FAILURE
end