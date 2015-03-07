require("ai.ai")
local ObjectManager = require("managers.object.object_manager")

Interrupt = { }
function Interrupt:interrupt(pAgent, pObject, msg)
	if     msg == STARTCOMBAT        then self:startCombatInterrupt(pAgent, pObject)    -- pObject = sender of interrupt message
	elseif msg == OBJECTINRANGEMOVED then self:startAwarenessInterrupt(pAgent, pObject) -- pObject = object that moved
	elseif msg == DAMAGERECEIVED	 then self:startDamageInterrupt(pAgent, pObject)    -- pObject = source of damage
	end
end

function Interrupt:startDamageInterrupt(pAgent,pObject)
end

function Interrupt:startCombatInterrupt(pAgent, pObject)
end

function Interrupt:doAwarenessCheck(pAgent, pObject)
	--print("Shouldn't be here...")
	return false
end

function Interrupt:startAwarenessInterrupt(pAgent, pObject)
	--print("Shouldn't be here either...")
end


DefaultInterrupt = createClass(Interrupt)
function DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
	if (pAgent ~= pObject) then return end
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
		agent:resetBehaviorList()
		agent:executeBehavior()
	end
end

function DefaultInterrupt:doAwarenessCheck(pAgent, pObject)
	if (pAgent == pObject) then return false end
	if (pAgent == nil or pObject == nil or not SceneObject(pAgent):isAiAgent()) then return false end
	
	local agent = AiAgent(pAgent)
	local scno = SceneObject(pObject)
	if TangibleObject(pAgent):getPvpStatusBitmask() == NONE or CreatureObject(pAgent):isDead() or CreatureObject(pAgent):isIncapacitated() then return false end
	--if not scno:isAiAgent() then agent:info("4") end
	if agent:getNumberOfPlayersInRange() <= 0  or agent:isRetreating() or agent:isFleeing() or agent:isInCombat() then return false	end
	--if not scno:isAiAgent() then agent:info("5") end
	if agent:getFollowObject() ~= nil and agent:getFollowObject() ~= pObject then return false end
	--if not scno:isAiAgent() then agent:info("6") end
	
	-- TODO (dannuic): factor in level difference here
	local radius = 32
	if CreatureObject(pAgent):getInCellNumber() ~= -1 then radius = 12 end
	radius = radius + agent:getFerocity()
	if not SceneObject(pAgent):isInRangeWithObject(pObject, radius) then return false end
	--if not scno:isAiAgent() then agent:info("7") end
	
	--local scno = LuaSceneObject(pObject)
	if not scno:isCreatureObject() then	return false end -- don't aggro TANOs (lairs, turrets, etc)
	--if not scno:isAiAgent() then agent:info("8") end
	local target = CreatureObject(pObject)
	if TangibleObject(pAgent):getPvpStatusBitmask() == NONE or target:isDead() or target:isIncapacitated() then return false end
	--if not scno:isAiAgent() then agent:info("9") end
	
	-- if not in combat, ignore creatures in different cells
	local agentParentID = SceneObject(pAgent):getParentID()
	local targetParentID = SceneObject(pObject):getParentID()
	if agentParentID ~= targetParentID then	return false end
	--if not scno:isAiAgent() then agent:info("10") end
	
	if agent:isCamouflaged(pObject) or not agent:isAttackableBy(pObject) or not target:isAttackableBy(pAgent) then return false end
	--if not scno:isAiAgent() then agent:info("11") end
	
	--TODO (dannuic): this seems wrong
	if scno:isAiAgent() then
		--AiAgent(pObject):info("attacking me!")
		
		local agentFerocity = agent:getFerocity();
		
		--local agentTarget = LuaAiAgent(pObject)
		local agentTargetFerocity = AiAgent(pObject):getFerocity()
		
		
		--local creature = LuaCreatureObject(pAgent)
		local creatureFaction = CreatureObject(pAgent):getFaction()
		
		--local creatureTarget = LuaCreatureObject(pObject)
		local creatureTargetFaction = CreatureObject(pObject):getFaction()
		
		
		if not AiAgent(pObject):isAttackableBy(pAgent) then return false end
		--agent:info("12")
		if ((agentTargetFerocity <= 0 or agentFerocity <= 0) 
		    and CreatureObject(pObject):getLevel() >= CreatureObject(pAgent):getLevel()) 
		    or (creatureFaction ~= 0 and creatureTargetFaction == 0) 
		    or (creatureFaction == 0 and creatureTargetFaction ~= 0) 
		    then return false 
		end
		--agent:info("13")
	end
	
	-- All the checks are out of the way, now we know we want to notice them
	return true
end

-- put this in a different function so that the generic checks are re-usable
function DefaultInterrupt:startAwarenessInterrupt(pAgent, pObject)
	if (pAgent == pObject) then return end
	if (pAgent == nil or pObject == nil or not SceneObject(pAgent):isAiAgent()) then return end
	
	local agent = AiAgent(pAgent)
	local scno = SceneObject(pObject)
	if not scno:isCreatureObject() then return false end -- don't aggro TANOs (lairs, turrets, etc)
	--if not scno:isAiAgent() then agent:info("1a") end
	local target = CreatureObject(pObject)
	
	if CreatureObject(pAgent):isDead() or CreatureObject(pAgent):isIncapacitated() then return end
	--if not scno:isAiAgent() then agent:info("1b") end
	if target:isDead() or target:isIncapacitated()) then return end
	--if not scno:isAiAgent() then agent:info("1c") end

	if agent:isInCombat() then return end
	--if not scno:isAiAgent() then agent:info("1d") end

	if not agent:checkLineOfSight(pObject) then return end
	--if not scno:isAiAgent() then agent:info("1e") end
	
	if agent:isCamouflaged(pObject) then return end
	--if not scno:isAiAgent() then agent:info("1f") end
	
	-- TODO (dannuic): tweak these formulae based on feedback
	local effectiveLevel = CreatureObject(pAgent):getLevel()
	if scno:isPlayerCreature() then
		effectiveLevel = effectiveLevel * (1 + agent:getFerocity() / 4)
		local faction = agent:getFactionString()
		if faction == "rebel" or faction == "imperial" then
			effectiveLevel = effectiveLevel * 2.5
		elseif faction ~= "" and faction ~= nil and scno:isPlayerCreature() then
			local standing = PlayerObject(pObject):getFactionStanding(faction)
			effectiveLevel = effectiveLevel * (1 + (standing / -5000))
		end
	end

	local radius = 32 - target:getLevel() + effectiveLevel
	if not scno:isPlayerCreature() then radius = radius * agent:getFerocity() end
	if radius < 10 then radius = 10 end
	if radius > 64 then radius = 64 end
	local inRange = scno:isInRangeWithObject(pAgent, radius)
	
	local pFollow = agent:getFollowObject();
	
	if agent:isStalker() and agent:isAggressiveTo(pObject) then
		--agent:info("1")
		if pFollow == nil and not inRange then
			--agent:info("1a")
			agent:setStalkObject(pObject)
			-- TODO (dannuic): is there a skill check associated with this message?
			target:sendSystemMessageWithTO("@skl_use:notify_stalked", SceneObject(pAgent):getDisplayedName())
			agent:activateAwareness(pObject)
		elseif agent:getAvgSpeed() <= (target:getWalkSpeed() * target:getWalkSpeed()) or inRange then
			--agent:info("1b")
			agent:addDefender(pObject) -- TODO (dannuic): do stalkers also agro when the target starts to move towards them?
		else
			--agent:info("1c")
			agent:setOblivious()
		end
	elseif agent:isAggressiveTo(pObject) and inRange then
		--if not scno:isAiAgent() then agent:info("3") end
		--if scno:isAiAgent() then AiAgent(pObject):info("attacking me!") end) end
		agent:addDefender(pObject)
	elseif pFollow == nil and inRange and (agent:getAvgSpeed() > (target:getWalkSpeed() * target:getWalkSpeed())) then
		--if not scno:isAiAgent() then agent:info("2") end
		agent:setWatchObject(pObject)
		agent:setAlertDuration(10000); -- TODO (dannuic): make this wait time more dynamic
		SceneObject(pAgent):showFlyText("npc_reaction/flytext", "alert", 255, 0, 0)
		agent:activateAwareness(pObject)
	elseif pObject == pFollow and agent:alertedTimeIsPast() and agent:getAvgSpeed() <= (target:getWalkSpeed() * target:getWalkSpeed()) then
		--if not scno:isAiAgent() then agent:info("4") end
		agent:setOblivious() -- if we're "standing still" (and they aren't aggressive) forget about us
	elseif pObject == pFollow and not inRange then
		agent:activateAwareness(pObject)
	elseif pObject == pFollow and inRange and scno:getParent() == nil then -- TODO: Do we want weaker mobs to run away when indoors? Revisit when indoor pathing is better
		--if not scno:isAiAgent() then agent:info("5") end
		-- TODO (dannuic): Not sure about this stuff, needs testing
		if SceneObject(pFollow):isCreatureObject() then
			local creoLevel = CreatureObject(pFollow):getLevel()
			local isBackwardsAggressive = SceneObject(pFollow):isAiAgent() and AiAgent(pFollow):isAggressiveTo(pAgent)
 
			if effectiveLevel < creoLevel and (isBackwardsAggressive or SceneObject(pFollow):isPlayerCreature()) then
				agent:runAway(pFollow, 64 - radius)
			else
				agent:activateAwareness(pFollow) 
			end
		else agent:setOblivious() end
	else
		agent:setOblivious()
	end

	agent:stopWaiting();
	agent:executeBehavior();
end


PackInterrupt = createClass(DefaultInterrupt)
function PackInterrupt:startCombatInterrupt(pAgent, pObject)
	if (pAgent ~= pObject) then
		if (pAgent ~= nil and pObject ~= nil) then
			local agent = AiAgent(pAgent)
			local scno = SceneObject(pObject)
			if scno:isAiAgent() then
				--scno = AiAgent(pObject)
				if AiAgent(pObject):getSocialGroup() ~= AiAgent(pAgent):getSocialGroup() or not AiAgent(pAgent):checkLineOfSight(pObject) then
					return
				end
			end

			-- if the source is not an AiAgent (like a lair) then don't check social group
			-- TODO (dannuic): change the range to calculate based on level difference and ferocity
			agent = AiAgent(pAgent)
			
			if agent:checkRange(pObject, 15) then
				agent:assist(pObject)
			end
		end
	end

	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
end


CreaturePetInterrupt = createClass(DefaultInterrupt)
function CreaturePetInterrupt:startCombatInterrupt(pAgent, pObject)
	if pAgent == nil or pObject == nil then return end
	local agent = AiAgent(pAgent)
	if agent:getOwner() ~= pObject then return end -- this is where the friend checks will go	
	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)

  --recover our pointer to agent
	agent = AiAgent(pAgent)
	agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
	agent:resetBehaviorList()
	agent:executeBehavior()
end

DroidPetInterrupt = createClass(DefaultInterrupt)
function DroidPetInterrupt:startDamageInterrupt(pAgent,pObject)
	if pAgent == nil or pObject == nil or not SceneObject(pAgent):isAiAgent() then return end
	local agent = AiAgent(pAgent)
	--print("droid got damage\n")
	-- starting combat droids should flee if they arent combat capable and they get hit by damage
	if CreatureObject(pAgent):isCombatDroidPet() then
		-- if in combat run away if not a combat pet
		agent:runAway(pObject, 32)
		agent:stopWaiting()
		agent:executeBehavior()
		return
	end

  	--recover our pointer to agent
	agent = AiAgent(pAgent)
	agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
	agent:resetBehaviorList()
	agent:executeBehavior()
end

function DroidPetInterrupt:startCombatInterrupt(pAgent, pObject)
	if pAgent == nil or pObject == nil then return end
	local agent = AiAgent(pAgent)
	if agent:getOwner() ~= pObject then return end -- this is where the friend checks will go
	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)

  	--recover our pointer to agent
	agent = AiAgent(pAgent)
	agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
	agent:resetBehaviorList()
	agent:executeBehavior()
end


FactionPetInterrupt = createClass(DefaultInterrupt)
function FactionPetInterrupt:startCombatInterrupt(pAgent, pObject)
	if pAgent == nil or pObject == nil then return end
	local agent = AiAgent(pAgent)
	if agent:getOwner() ~= pObject then return end -- this is where the friend checks will go	

	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)

  --recover our pointer to agent
	agent = AiAgent(pAgent)
	agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
	agent:resetBehaviorList()
	agent:executeBehavior()
end
