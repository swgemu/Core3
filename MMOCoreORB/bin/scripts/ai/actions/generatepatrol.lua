require("ai.ai")
require("ai.interrupts")

GeneratePatrolBase = createClass(Ai)

function GeneratePatrolBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if agent:generatePatrol(5, 10) then
			return BEHAVIOR_SUCCESS
		else
			return BEHAVIOR_FAILURE
		end
	end
	return BEHAVIOR_FAILURE
end

GeneratePatrol = createClass(GeneratePatrolBase, Interrupt)
GeneratePatrolDefault = createClass(GeneratePatrolBase, DefaultInterrupt)
GeneratePatrolPack = createClass(GeneratePatrolBase, PackInterrupt)