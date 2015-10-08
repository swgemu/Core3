require("ai.actions.movebase")

function MoveCreaturePet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:getFollowState() ~= OBLIVIOUS) then
			agent:setDestination()
			return true
		end
	end
	return false
end

function MoveDroidPet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:getFollowState() ~= OBLIVIOUS) then
			agent:setDestination()
			return true
		end
	end
	return false
end

function MoveFactionPet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:getFollowState() ~= OBLIVIOUS) then
			agent:setDestination()
			return true
		end
	end
	return false
end
