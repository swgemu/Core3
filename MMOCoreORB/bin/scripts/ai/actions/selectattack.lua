require("ai.actions.selectattackbase")

function SelectAttackCreaturePet:terminate(pAgent)
	if pAgent ~= nil then
		local agent = AiAgent(pAgent)
		if agent:getBehaviorStatus() == BEHAVIOR_FAILURE then agent:restoreFollowObject() end
	end
	return 0
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
