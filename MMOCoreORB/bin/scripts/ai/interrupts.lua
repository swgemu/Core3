-- When an interrupt gets called (startXXXInterrupt), pAgent and pObject both come in locked. This means that any object that
-- gets declared in the course of the method CANNOT be locked in any subsequent cpp call. For example, startAwarenessInterrupt
-- declares a pFollow object, and many calls are made using it. All of those calls MUST be threadsafe WITHOUT locking pFollow.

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
	if (pAgent == nil or pObject == nil) then return false end

	if TangibleObject(pAgent):getPvpStatusBitmask() == NONE or CreatureObject(pAgent):isDead() or CreatureObject(pAgent):isIncapacitated() then return false end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("4") end
	if AiAgent(pAgent):getNumberOfPlayersInRange() <= 0  or AiAgent(pAgent):isRetreating() or AiAgent(pAgent):isFleeing() or AiAgent(pAgent):isInCombat() then return false	end

	self:checkForReactionChat(pAgent, pObject)

	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("5") end
	if AiAgent(pAgent):getFollowObject() ~= nil and AiAgent(pAgent):getFollowObject() ~= pObject then return false end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("6") end
	
	-- TODO (dannuic): factor in level difference here
	local radius = 32
	if CreatureObject(pAgent):getInCellNumber() ~= -1 then radius = 12 end
	radius = radius + AiAgent(pAgent):getFerocity()
	if not SceneObject(pAgent):isInRangeWithObject(pObject, radius) then return false end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("7") end

	if not SceneObject(pObject):isCreatureObject() then return false end -- don't aggro TANOs (lairs, turrets, etc)
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("8") end
	if TangibleObject(pAgent):getPvpStatusBitmask() == NONE or CreatureObject(pObject):isDead() or CreatureObject(pObject):isIncapacitated() then return false end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("9") end
	
	-- if not in combat, ignore creatures in different cells
	local agentParentID = SceneObject(pAgent):getParentID()
	local targetParentID = SceneObject(pObject):getParentID()
	if agentParentID ~= targetParentID then	return false end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("10") end
	
	if AiAgent(pAgent):isCamouflaged(pObject) or not AiAgent(pAgent):isAttackableBy(pObject) or not CreatureObject(pObject):isAttackableBy(pAgent) then return false end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("11") end
	
	--TODO (dannuic): this seems wrong
	if SceneObject(pObject):isAiAgent() then
		--AiAgent(pObject):info("attacking me!")
		
		local agentFerocity = AiAgent(pAgent):getFerocity();
		
		--local agentTarget = LuaAiAgent(pObject)
		local agentTargetFerocity = AiAgent(pObject):getFerocity()
		
		
		--local creature = LuaCreatureObject(pAgent)
		local creatureFaction = CreatureObject(pAgent):getFaction()
		
		--local creatureTarget = LuaCreatureObject(pObject)
		local creatureTargetFaction = CreatureObject(pObject):getFaction()
		
		
		if not AiAgent(pObject):isAttackableBy(pAgent) then return false end
		--AiAgent(pAgent):info("12")
		if ((agentTargetFerocity <= 0 or agentFerocity <= 0) 
		    and CreatureObject(pObject):getLevel() >= CreatureObject(pAgent):getLevel()) 
		    or (creatureFaction ~= 0 and creatureTargetFaction == 0) 
		    or (creatureFaction == 0 and creatureTargetFaction ~= 0) 
		    then return false 
		end
		--AiAgent(pAgent):info("13")
	end
	
	-- All the checks are out of the way, now we know we want to notice them
	return true
end

function DefaultInterrupt:checkForReactionChat(pAgent, pObject)
	if not SceneObject(pObject):isPlayerCreature() then return end

	if not AiAgent(pAgent):hasReactionChatMessages() then return end

	if SceneObject(pObject):getParentID() ~= SceneObject(pAgent):getParentID() then return end

	local dist = SceneObject(pObject):getDistanceTo(pAgent)

	if dist > 48 or dist < 35 then return end

	if not CreatureObject(pAgent):checkCooldownRecovery("reaction_chat") then return end

	if not AiAgent(pAgent):checkLineOfSight(pObject) then return end

	local factionString = AiAgent(pAgent):getFactionString()
	local aiFaction = CreatureObject(pAgent):getFaction()
	local targetFaction = CreatureObject(pObject):getFaction()
	local state = 0

	if aiFaction ~= 0 then
		if targetFaction == aiFaction then
			state = REACTION_NICE
		elseif targetFaction == 0 then
			state = REACTION_MID
		else
			state = REACTION_MEAN
		end

	elseif factionString ~= "" then
		local pGhost = CreatureObject(pObject):getPlayerObject()

		if pGhost ~= nil then
			local standing = PlayerObject(pGhost):getFactionStanding(factionString)
			if standing >= 3000 then
				state = REACTION_NICE
			elseif standing <= -3000 then
				state = REACTION_MEAN
			else
				state = REACTION_MID
			end
		end
	else
		state = REACTION_MID
	end

	if SceneObject(pObject):isFacingObject(pAgent) then
		AiAgent(pAgent):sendReactionChat(REACTION_HI, state)
	else
		AiAgent(pAgent):sendReactionChat(REACTION_BYE, state)
	end
end

-- put this in a different function so that the generic checks are re-usable
function DefaultInterrupt:startAwarenessInterrupt(pAgent, pObject)
	if (pAgent == pObject) then return end
	if (pAgent == nil or pObject == nil) then return end

	if not SceneObject(pObject):isCreatureObject() then return false end -- don't aggro TANOs (lairs, turrets, etc)
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1a") end
	
	if CreatureObject(pAgent):isDead() or CreatureObject(pAgent):isIncapacitated() then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1b") end
	if CreatureObject(pObject):isDead() or CreatureObject(pObject):isIncapacitated() then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1c") end

	if AiAgent(pAgent):isInCombat() then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1d") end

	if not AiAgent(pAgent):checkLineOfSight(pObject) then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1e") end
	
	if AiAgent(pAgent):isCamouflaged(pObject) then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1f") end
	
	-- TODO (dannuic): tweak these formulae based on feedback
	local effectiveLevel = CreatureObject(pAgent):getLevel()
	if SceneObject(pObject):isPlayerCreature() then
		effectiveLevel = effectiveLevel * (1 + AiAgent(pAgent):getFerocity() / 4)
		local faction = AiAgent(pAgent):getFactionString()
		if faction == "rebel" or faction == "imperial" then
			effectiveLevel = effectiveLevel * 2.5
		elseif faction ~= "" and faction ~= nil and SceneObject(pObject):isPlayerCreature() then
			local pGhost = CreatureObject(pObject):getPlayerObject()
			if pGhost ~= nil then
				local standing = PlayerObject(pGhost):getFactionStanding(faction)
				effectiveLevel = effectiveLevel * (1 + (standing / -5000))
			end
		end
	end

	local radius = 32 - CreatureObject(pObject):getLevel() + effectiveLevel
	if not SceneObject(pObject):isPlayerCreature() then radius = radius * AiAgent(pAgent):getFerocity() end
	if radius < 10 then radius = 10 end
	if radius > 64 then radius = 64 end
	local inRange = SceneObject(pObject):isInRangeWithObject(pAgent, radius)
	
	local pFollow = AiAgent(pAgent):getFollowObject();
	
	if AiAgent(pAgent):isStalker() and AiAgent(pAgent):isAggressiveTo(pObject) then
		--AiAgent(pAgent):info("1")
		if pFollow == nil and not inRange then
			--AiAgent(pAgent):info("1a")
			AiAgent(pAgent):setStalkObject(pObject)
			-- TODO (dannuic): is there a skill check associated with this message?
			CreatureObject(pObject):sendSystemMessageWithTO("@skl_use:notify_stalked", SceneObject(pAgent):getDisplayedName())
			AiAgent(pAgent):activateAwareness(pObject)
		elseif AiAgent(pAgent):getAvgSpeed() <= (CreatureObject(pObject):getWalkSpeed() * CreatureObject(pObject):getWalkSpeed()) or inRange then
			--AiAgent(pAgent):info("1b")
			AiAgent(pAgent):addDefender(pObject) -- TODO (dannuic): do stalkers also agro when the target starts to move towards them?
		else
			--AiAgent(pAgent):info("1c")
			AiAgent(pAgent):setOblivious()
		end
	elseif AiAgent(pAgent):isAggressiveTo(pObject) and inRange then
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("3") end
		--if SceneObject(pObject):isAiAgent() then AiAgent(pObject):info("attacking me!") end) end
		AiAgent(pAgent):addDefender(pObject)
	elseif pFollow == nil and inRange and (AiAgent(pAgent):getAvgSpeed() > (CreatureObject(pObject):getWalkSpeed() * CreatureObject(pObject):getWalkSpeed())) then
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("2") end
		AiAgent(pAgent):setWatchObject(pObject)
		AiAgent(pAgent):setAlertDuration(10000); -- TODO (dannuic): make this wait time more dynamic
		SceneObject(pAgent):showFlyText("npc_reaction/flytext", "alert", 255, 0, 0)
		AiAgent(pAgent):activateAwareness(pObject)
	elseif pObject == pFollow and AiAgent(pAgent):alertedTimeIsPast() and AiAgent(pAgent):getAvgSpeed() <= (CreatureObject(pObject):getWalkSpeed() * CreatureObject(pObject):getWalkSpeed()) then
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("4") end
		AiAgent(pAgent):setOblivious() -- if we're "standing still" (and they aren't aggressive) forget about us
	elseif pObject == pFollow and not inRange then
		AiAgent(pAgent):activateAwareness(pObject)
	elseif pObject == pFollow and inRange and SceneObject(pObject):getParent() == nil then -- TODO: Do we want weaker mobs to run away when indoors? Revisit when indoor pathing is better
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("5") end
		-- TODO (dannuic): Not sure about this stuff, needs testing
		if SceneObject(pFollow):isCreatureObject() then
			local creoLevel = CreatureObject(pFollow):getLevel()
			local isBackwardsAggressive = SceneObject(pFollow):isAiAgent() and AiAgent(pFollow):isAggressiveTo(pAgent)
 
			if effectiveLevel < creoLevel and (isBackwardsAggressive or SceneObject(pFollow):isPlayerCreature()) then
				AiAgent(pAgent):runAway(pFollow, 64 - radius)
			else
				AiAgent(pAgent):activateAwareness(pFollow)
			end
		else AiAgent(pAgent):setOblivious() end
	else
		AiAgent(pAgent):setOblivious()
	end

	AiAgent(pAgent):stopWaiting();
	AiAgent(pAgent):executeBehavior();
end


PackInterrupt = createClass(DefaultInterrupt)
function PackInterrupt:startCombatInterrupt(pAgent, pObject)
	if (pAgent ~= pObject) then
		if (pAgent ~= nil and pObject ~= nil) then
			if SceneObject(pObject):isAiAgent() then
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
	if pAgent == nil or pObject == nil then return end
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
