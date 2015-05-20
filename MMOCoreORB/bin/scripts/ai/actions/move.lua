require("ai.ai")
require("ai.interrupts")

MoveBase = createClass(Ai)

function MoveBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local creature = CreatureObject(pAgent)
		if (creature:getPosture() == UPRIGHT and agent:setDestination() > 0) then
			if agent:shouldRetreat(256) then
				agent:leash()
				return false
			end
			return true
		end
	end
	return false
end

function MoveBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		
		if (agent:getCurrentSpeed() > 0) then 
			agent:completeMove()
		end
		
		if (self:findNextPosition(pAgent)) then
			return BEHAVIOR_RUNNING
		else
			return BEHAVIOR_SUCCESS
		end
	end
	return BEHAVIOR_FAILURE
end

-- default action is to run
function MoveBase:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), false)) then
			return true
		end
	end
	return false
end

Move = createClass(MoveBase, Interrupt)
MovePetBase = createClass(MoveBase, Interrupt)

function MovePetBase:doAction(pAgent)
  if (pAgent ~= nil) then
    local agent = AiAgent1(pAgent)
    
    if (agent:getCurrentSpeed() > 0) then 
      agent:completeMove()
    end
    local Ptarget = agent:getFollowObject()
    
    if (Ptarget ~= nil and not agent:checkRange(Ptarget,156)) then
      local scno = SceneObject1(Ptarget)
      if (scno ~= nil) then
        SceneObject2(pAgent):teleport(scno:getPositionX(), scno:getPositionZ(), scno:getPositionY(), scno:getParentID())
        return BEHAVIOR_SUCCESS    
      end    
    end
    
    if (self:findNextPosition(pAgent)) then
      return BEHAVIOR_RUNNING
    else
      return BEHAVIOR_SUCCESS
    end
  end
  return BEHAVIOR_FAILURE
end



MoveDefault = createClass(MoveBase, DefaultInterrupt)
MovePack = createClass(MoveBase, PackInterrupt)
MoveCreaturePet = createClass(MovePetBase, CreaturePetInterrupt)
MoveDroidPet = createClass(MovePetBase, DroidPetInterrupt)
MoveFactionPet = createClass(MovePetBase, FactionPetInterrupt)

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
