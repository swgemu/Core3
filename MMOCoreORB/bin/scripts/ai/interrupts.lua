require("ai.ai")
local ObjectManager = require("managers.object.object_manager")

Interrupt = { }
function Interrupt:interrupt(pAgent, pObject, msg)
	if     msg == STARTCOMBAT        then self:startCombatInterrupt(pAgent, pObject)    -- pObject = sender of interrupt message
	elseif msg == OBJECTINRANGEMOVED then self:startAwarenessInterrupt(pAgent, pObject) -- pObject = object that moved
	end
end

function Interrupt:startCombatInterrupt(pAgent, pObject)
end

function Interrupt:doAwarenessCheck(pAgent, pObject)
end

function Interrupt:startAwarenessInterrupt(pAgent, pObject)
end


DefaultInterrupt = createClass(Interrupt)
function DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
	if (pAgent ~= pObject) then return end
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
		agent:resetBehaviorList()
		agent:executeBehavior()
	end
end

function DefaultInterrupt:doAwarenessCheck(pAgent, pObject)
	if (pAgent == pObject) then return false end
	if (pAgent == nil or pObject == nil) then return false end
	
	local agent = LuaAiAgent(pAgent)
	if ObjectManager.withTangibleObject(pAgent, function(tano) return tano:getPvpStatusBitmask() == NONE end) or ObjectManager.withCreatureObject(pAgent, function(creo) return creo:isDead() or creo:isIncapacitated() end) then return false end
	if agent:getNumberOfPlayersInRange() <= 0  or agent:isRetreating() or agent:isFleeing() or agent:isInCombat() then return false end
	if agent:getFollowObject() ~= nil and agent:getFollowObject() ~= pObject then return false end
	
	-- TODO (dannuic): factor in level difference here
	local radius = 32
	if ObjectManager.withCreatureObject(pAgent, function(creo) return creo:getInCellNumber() end) == -1 then radius = 12 end
	radius = radius + agent:getFerocity()
	if not ObjectManager.withSceneObject(pAgent, function(scno) return scno:isInRangeWithObject(pObject, radius) end) then return false end
	
	local scno = LuaSceneObject(pObject)
	if not scno:isCreatureObject() then return false end -- don't aggro TANOs (lairs, turrets, etc)
	local target = LuaCreatureObject(pObject)
	if ObjectManager.withTangibleObject(pObject, function(tano) return tano:getPvpStatusBitmask() == NONE end) or target:isDead() or target:isIncapacitated() then return false end
	
	-- if not in combat, ignore creatures in different cells
	local agentParentID = ObjectManager.withSceneObject(pAgent, function(scno) return scno:getParentID() end)
	local targetParentID = ObjectManager.withSceneObject(pObject, function(scno) return scno:getParentID() end)
	if not agent:isInCombat() and agentParentID ~= targetParentID then return false end
	
	if agent:isCamouflaged(pObject) or not agent:isAttackableBy(pObject) or not target:isAttackableBy(pAgent) then return false end
	
	--TODO (dannuic): this seems wrong
	if scno:isAiAgent() then
		local agentTarget = LuaAiAgent(pObject)
		local creature = LuaCreatureObject(pAgent)
		local creatureTarget = LuaCreatureObject(pObject)
		if not agentTarget:isAttackableBy(pAgent) then return false end
		if ((agentTarget:getFerocity() <= 0 or agent:getFerocity() <= 0) and creatureTarget:getLevel() >= creature:getLevel()) or (creature:getFaction() ~= 0 and creatureTarget:getFaction() == 0) or (creature:getFaction() == 0 and creatureTarget:getFaction() ~= 0) then return false end
	end
	
	-- All the checks are out of the way, now we know we want to aggro
	return true
end

-- put this in a different function so that the generic checks are re-usable
function DefaultInterrupt:startAwarenessInterrupt(pAgent, pObject)
	if (pAgent == pObject) then return end
	if (pAgent == nil or pObject == nil) then return end
	
	local agent = LuaAiAgent(pAgent)
	local scno = LuaSceneObject(pObject)
	if not scno:isCreatureObject() then return false end -- don't aggro TANOs (lairs, turrets, etc)
	local target = LuaCreatureObject(pObject)
	
	if ObjectManager.withCreatureObject(pAgent, function(creo) return creo:isDead() or creo:isIncapacitated() end) then return end
	if ObjectManager.withCreatureObject(pObject, function(creo) return creo:isDead() or creo:isIncapacitated() end) then return end
	if not agent:checkLineOfSight(pObject) then return end
	
	if agent:isCamouflaged(pObject) then return end
	
	-- TODO (dannuic): tweak these formulae based on feedback
	local effectiveLevel = agent:getFerocity() * ObjectManager.withCreatureObject(pAgent, function(creo) return creo:getLevel() end) / 4
	local levelDiff = effectiveLevel - target:getLevel()
	local radius = 32 - levelDiff
	if radius < 0 then radius = 0 end
	if radius > 64 then radius = 64 end
	local inRange = (scno:isInRangeWithObject(pAgent, radius) ~= 0)

	if agent:isInCombat() then return end -- TODO: the "peace out" checks should go here
	
	local pFollow = agent:getFollowObject();
	
	if agent:isStalker() and agent:isAggressiveTo(pObject) then
		--agent:info("1")
		if pFollow == nil and not inRange then
			--agent:info("1a")
			agent:setStalkObject(pObject);
		elseif agent:getAvgSpeed() <= (target:getWalkSpeed() * target:getWalkSpeed()) and not inRange then
			--agent:info("1b")
			agent:addDefender(pObject)
		elseif inRange then
			--agent:info("1c")
			agent:addDefender(pObject) -- TODO (dannuic): do stalkers also agro when the target starts to move towards them?
		else
			--agent:info("1d")
			agent:setOblivious()
		end
	elseif agent:isAggressiveTo(pObject) and inRange then
		--agent:info("2")
		--if scno:isAiAgent() then ObjectManager.withCreatureAiAgent(pObject, function(ai) ai:info("attacking me!") end) end
		agent:addDefender(pObject)
	elseif agent:getAvgSpeed() <= (target:getWalkSpeed() * target:getWalkSpeed()) and scno:isPlayerCreature() and inRange then
		--agent:info("3")
		agent:setOblivious() -- if we're "standing still" (and they aren't aggressive) forget about us
	elseif pFollow == nil and scno:isPlayerCreature() and inRange then
		--agent:info("4")
		agent:setWatchObject(pObject)
		ObjectManager.withSceneObject(pAgent, function(scno) scno:showFlyText("npc_reaction/flytext", "alert", 255, 0, 0) end)
	elseif pObject == pFollow and inRange then
		--agent:info("5")
		ObjectManager.withCreatureObject(pFollow, function(creo)
			if effectiveLevel < creo:getLevel() then
				agent:runAway(pFollow)
			else
				agent:addDefender(pFollow)
			end
		end)
	end

	agent:activateRecovery();
	agent:stopWaiting();
	agent:executeBehavior();
end


PackInterrupt = createClass(DefaultInterrupt)
function PackInterrupt:startCombatInterrupt(pAgent, pObject)
	if (pAgent ~= pObject) then
		if (pAgent ~= nil and pObject ~= nil) then
			local agent = LuaAiAgent(pAgent)
			local scno = LuaSceneObject(pObject)
			if scno:isAiAgent() then
				local source = LuaAiAgent(pObject)
				if source:getSocialGroup() ~= agent:getSocialGroup() or not agent:checkLineOfSight(pObject) then
					return
				end
			end

			-- if the source is not an AiAgent (like a lair) then don't check social group
			-- TODO (dannuic): change the range to calculate based on level difference and ferocity
			if agent:checkRange(pObject, 15) then
				agent:assist(pObject)
			end
		end
	end

	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
end


PetInterrupt = createClass(DefaultInterrupt)
function PetInterrupt:startCombatInterrupt(pAgent, pObject)
	if pAgent == nil or pObject == nil then return end
	local agent = LuaAiAgent(pAgent)
	if agent:getOwner() ~= pObject then return end -- this is where the friend checks will go
	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
	agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
	agent:resetBehaviorList()
	agent:executeBehavior()
end
