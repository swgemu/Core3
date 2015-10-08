require("ai.actions.waitbase")

function Wait10CreaturePet:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if agent:getFollowState() == PATROLLING then
			agent:setWait(5)
		end
	end
end

function Wait10DroidPet:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if agent:getFollowState() == PATROLLING then
			agent:setWait(5)
		end
	end
end

function Wait10FactionPet:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if agent:getFollowState() == PATROLLING then
			agent:setWait(5)
		end
	end
end
