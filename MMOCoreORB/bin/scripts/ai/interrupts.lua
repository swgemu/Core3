-- When an interrupt gets called (startXXXInterrupt), pAgent and pObject both come in locked. This means that any object that
-- gets declared in the course of the method CANNOT be locked in any subsequent cpp call. For example, startAwarenessInterrupt
-- declares a pFollow object, and many calls are made using it. All of those calls MUST be threadsafe WITHOUT locking pFollow.

require("ai.ai")
local ObjectManager = require("managers.object.object_manager")

Interrupt = { }
function Interrupt:interrupt(pAgent, pObject, msg)
	if     msg == STARTCOMBAT        then self:startCombatInterrupt(pAgent, pObject)    -- pObject = sender of interrupt message
	elseif msg == OBJECTINRANGEMOVED then self:startAwarenessInterrupt(pAgent, pObject) -- pObject = object that moved TODO: should rename this
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
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Entering doAwarenessCheck()") end
	if (pAgent == pObject) then return false end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed unique objects") end
	if (pAgent == nil or pObject == nil) then return false end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed non-nil objects") end

	local tanoAgent = TangibleObject1(pAgent)
	local creoAgent = CreatureObject1(pAgent)
	local aiAgent = AiAgent1(pAgent)

	if tanoAgent:getPvpStatusBitmask() == NONE or creoAgent:isDead() or creoAgent:isIncapacitated() then
	 if creoAgent:isDead() then 
	   --AiAgent(pAgent):info("Creo is dead ")
	   return false 
	 end
	 if creoAgent:isIncapacitated() then 
	   --AiAgent(pAgent):info("Creo is incapped ")
	   return false 	 
	 end
	 if tanoAgent:getPvpStatusBitmask() == NONE and creoAgent:isDroidPet() == false then 
	   --AiAgent(pAgent):info("Not bitmask ")
	   return false 
	 end
	end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed self bitmask checks") end
	if aiAgent:getNumberOfPlayersInRange() <= 0  or aiAgent:isRetreating() or aiAgent:isFleeing() or aiAgent:isInCombat() then return false	end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed playersInRange, retreat, flee, and inCombat checks") end

	local sceneObject = SceneObject1(pObject)

	if not sceneObject:isCreatureObject() then return false end -- don't aggro TANOs (lairs, turrets, etc)
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed target CREO check") end

	local creoObject = CreatureObject2(pObject)

	if creoObject:isInvisible() then return false end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed target invisible check") end

	self:checkForReactionChat(pAgent, pObject)

	--restore pointers
	tanoAgent = TangibleObject1(pAgent)
	creoAgent = CreatureObject1(pAgent)
	aiAgent = AiAgent1(pAgent)
	sceneObject = SceneObject1(pObject)
	creoObject = CreatureObject2(pObject)

	if aiAgent:getFollowObject() ~= nil and aiAgent:getFollowObject() ~= pObject then return false end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed followObject checks") end

	local radius = aiAgent:getAggroRadius()
	if radius == 0 then radius = DEFAULTAGGRORADIUS end
	if sceneObject:isPlayerCreature() then radius = radius * 2 end

	-- TODO possibly tweak, but we need a cap on mob awareness distance
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Radius "..radius) end
	if not sceneObject:isInRangeWithObject(pAgent, radius * 1.2) then return false end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed radius check") end

	local tanoObject = TangibleObject2(pObject)

	if tanoObject:getPvpStatusBitmask() == NONE or creoObject:isDead() or creoObject:isIncapacitated() then 
	   -- need a case here for harvet droids
	   return false 
	end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed target bitmask checks") end

	-- if not in combat, ignore creatures in different cells
	local agentParentID = creoAgent:getBuildingParentID()
	local targetParentID = creoObject:getBuildingParentID()
	if agentParentID ~= targetParentID then	return false end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed parent checks") end

	if aiAgent:isCamouflaged(pObject) or not aiAgent:isAttackableBy(pObject) or not creoObject:isAttackableBy(pAgent) then return false end
	--if SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("Passed attackable checks") end

	--TODO (dannuic): this still seems wrong, but it's only for AI aggroing AI anyway
	if sceneObject:isAiAgent() then
		--AiAgent(pObject):info("attacking me!")

		local agentObject = AiAgent2(pObject)

		--local creature = LuaCreatureObject(pAgent)
		local creatureFaction = creoAgent:getFaction()

		--local creatureTarget = LuaCreatureObject(pObject)
		local creatureTargetFaction = creoObject:getFaction()

		if not agentObject:isAttackableBy(pAgent) then return false end
		--AiAgent(pAgent):info("Passed AiAgent target attackable checks")
		if (creatureFaction ~= 0 and creatureTargetFaction == 0) or (creatureFaction == 0 and creatureTargetFaction ~= 0) 
			then return false 
		end
		--AiAgent(pAgent):info("Passed all AiAgent attackable checks")
	end

	-- All the checks are out of the way, now we know we want to notice them
	return true
end

function DefaultInterrupt:checkForReactionChat(pAgent, pObject)
	local sceneObject = SceneObject1(pObject)

	if not sceneObject:isPlayerCreature() then return end

	local creoObject = CreatureObject1(pObject)

	if not (creoObject:getCurrentSpeed() > 0.5*creoObject:getWalkSpeed()) then return end

	local aiAgent = AiAgent1(pAgent)

	if not aiAgent:hasReactionChatMessages() then return end

	local sceneAgent = SceneObject2(pAgent)

	if sceneObject:getParentID() ~= sceneAgent:getParentID() then return end

	local dist = sceneObject:getDistanceTo(pAgent)

	if dist > 35 or dist < 30 then return end

	local creoAgent = CreatureObject2(pAgent)

	if not creoAgent:checkCooldownRecovery("reaction_chat") then return end

	if not aiAgent:checkLineOfSight(pObject) then return end

	local factionString = aiAgent:getFactionString()
	local aiFaction = creoAgent:getFaction()
	local targetFaction = creoObject:getFaction()
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
		local pGhost = creoObject:getPlayerObject()

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

	sceneAgent:faceObject(pObject, true)

	if sceneObject:isFacingObject(pAgent) then
		aiAgent:sendReactionChat(REACTION_HI, state)
	else
		aiAgent:sendReactionChat(REACTION_BYE, state)
	end
end

-- put this in a different function so that the generic checks are re-usable
function DefaultInterrupt:startAwarenessInterrupt(pAgent, pObject)
	if (pAgent == pObject) then return end
	if (pAgent == nil or pObject == nil) then return end
	
	local sceneObject = SceneObject1(pObject)

	if not sceneObject:isCreatureObject() then return false end -- don't aggro TANOs (lairs, turrets, etc)
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("a") end
	
	local creoAgent = CreatureObject1(pAgent)

	if creoAgent:isDead() or creoAgent:isIncapacitated() then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("b") end
	
	local creoObject = CreatureObject2(pObject)
	
	if creoObject:isDead() or creoObject:isIncapacitated() then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("c") end
	
	local aiAgent = AiAgent1(pAgent)

	if aiAgent:isInCombat() then return end
	--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("d") end

	-- TODO (dannuic): tweak these formulae based on feedback
	-- TODO (dannuic): should we be using group levels here (if available)?
	local levelDiff = creoObject:getLevel() - creoAgent:getLevel()
	local mod = math.max(0.04, math.min((1 - (levelDiff/20)), 1.2))

	local radius = aiAgent:getAggroRadius()
	if radius == 0 then radius = DEFAULTAGGRORADIUS end
	radius = radius*mod

	local inRange = sceneObject:isInRangeWithObject(pAgent, radius)

	local pFollow = aiAgent:getFollowObject();

	if aiAgent:isStalker() and sceneObject:isPlayerCreature() and aiAgent:isAggressiveTo(pObject) and sceneObject:isInRangeWithObject(pAgent, radius*2) then
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1") end
		if pFollow == nil and not inRange then
			--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1a") end
			if aiAgent:checkLineOfSight(pObject) then
				aiAgent:setStalkObject(pObject)
				aiAgent:setAlertDuration(10000)
				if creoObject:hasSkill("outdoors_ranger_novice") then
					creoObject:sendSystemMessageWithTO("@skl_use:notify_stalked", SceneObject(pAgent):getDisplayedName())
				end
			end
		elseif inRange or creoObject:getCurrentSpeed() <= creoObject:getWalkSpeed() then
			--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1b") end
			if aiAgent:checkLineOfSight(pObject) then aiAgent:addDefender(pObject) end -- TODO (dannuic): do stalkers also agro when the target starts to move towards them?
		else
			--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("1c") end
			aiAgent:setOblivious()
		end
	elseif aiAgent:isAggressiveTo(pObject) and inRange then
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("2") end
		--if SceneObject(pObject):isAiAgent() then AiAgent(pObject):info("attacking me!") end) end
		if aiAgent:checkLineOfSight(pObject) then aiAgent:addDefender(pObject) end

	elseif pFollow == nil and inRange and aiAgent:isCreature() and (creoObject:getCurrentSpeed() >= creoObject:getWalkSpeed()) then
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("3") end
		if aiAgent:checkLineOfSight(pObject) then
			aiAgent:setWatchObject(pObject)
			aiAgent:setAlertDuration(10000); -- TODO (dannuic): make this wait time more dynamic
			SceneObject(pAgent):showFlyText("npc_reaction/flytext", "alert", 255, 0, 0)
		end
	elseif pObject == pFollow and aiAgent:alertedTimeIsPast() and aiAgent:getFollowState() == WATCHING then
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("4") end
		aiAgent:setOblivious() -- if we're "standing still" (and they aren't aggressive) forget about us
	elseif pObject == pFollow and inRange and sceneObject:getParent() == nil then -- TODO: Do we want weaker mobs to run away when indoors? Revisit when indoor pathing is better
		--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("5") end
		-- TODO (dannuic): Not sure about this stuff, needs testing
		local sceneFollow = SceneObject2(pFollow)
		
		if sceneFollow:isCreatureObject() then
			local creoLevel = CreatureObject(pFollow):getLevel()
			local isBackwardsAggressive = sceneFollow:isAiAgent() and AiAgent(pFollow):isAggressiveTo(pAgent)
 
 			-- TODO (dannuic): Add in run away logic for nearby combat
			if aiAgent:isCreature() and creoAgent:getLevel()*mod < creoLevel and (isBackwardsAggressive or sceneFollow:isPlayerCreature()) and creoObject:getCurrentSpeed() > 2*creoObject:getWalkSpeed() and sceneObject:isFacingObject(pAgent) then
				--if not SceneObject(pObject):isAiAgent() then AiAgent(pAgent):info("run!") end
				if aiAgent:checkLineOfSight(pObject) then
					aiAgent:runAway(pFollow, 64 - radius)
					aiAgent:setAlertDuration(10000)
				end
			end
		else aiAgent:setOblivious() end
	else
		aiAgent:setOblivious()
	end

	aiAgent:stopWaiting();
	aiAgent:executeBehavior();
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
	-- droids should flee if they arent combat capable and they get hit by damage
	if not CreatureObject(pAgent):isCombatDroidPet() then
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
