require("ai.actions.movebase")

function WalkCreaturePet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:getFollowState() == PATROLLING) then
			agent:setDestination()
			return true
		end
	end
	return false
end

function WalkDroidPet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:getFollowState() == PATROLLING) then
			agent:setDestination()
			return true
		end
	end
	return false
end

function WalkFactionPet:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:getFollowState() == PATROLLING) then
			agent:setDestination()
			return true
		end
	end
	return false
end
