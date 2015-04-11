require("ai.actions.move")
require("ai.interrupts")

WalkBase = createClass(MoveBase)

-- overrides so that we walk instead of run
function WalkBase:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), true)) then
			return true
		end
	end
	return false
end

Walk = createClass(WalkBase, Interrupt)
WalkDefault = createClass(WalkBase, DefaultInterrupt)
WalkPack = createClass(WalkBase, PackInterrupt)
WalkCreaturePet = createClass(WalkBase, CreaturePetInterrupt)
WalkDroidPet = createClass(WalkBase, DroidPetInterrupt)
WalkFactionPet = createClass(WalkBase, FactionPetInterrupt)

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
