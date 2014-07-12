require("ai.ai")
require("ai.interrupts")

--GeneratePatrol = Ai:new {}
GeneratePatrolBase = createClass(Ai)

function GeneratePatrolBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		if (agent:generatePatrol(5, 10)) then
			return BEHAVIOR_SUCCESS
		else
			return BEHAVIOR_FAILURE
		end
	end
	return BEHAVIOR_FAILURE
end

--[[function GeneratePatrol:interrupt(pAgent, pObject, msg)
	if msg == STARTCOMBAT and pAgent == pObject then
		Ai:startCombatInterrupt(pAgent, pObject)
	end
	
	return 0
end]]

GeneratePatrol = createClass(GeneratePatrolBase, Interrupt)
GeneratePatrolDefault = createClass(GeneratePatrolBase, DefaultInterrupt)
GeneratePatrolPack = createClass(GeneratePatrolBase, PackInterrupt)