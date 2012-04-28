hedon_istee_screenplay = ScreenPlay:new {
	numberOfActs = 1,

	states = {
		quest1 = {started = 1, defeated = 2, completed = 8},
		quest2 = {started = 16, defeated = 32, completed = 64},
		quest3 = {started = 128, delivered = 256, completed = 512}
	},

	loc = {
		hedon = {x = 1390, z = 0, y = 3195},
		drog  = {x = 1553, z = 15, y = 3488},
		rath  = {x = 1800, z = 7, y = 3128},
		monk  = {x = 1560, z = 7, y = 2970}
	}
}

registerScreenPlay("hedon_istee_screenplay", true)

---
--Initialize Screenplay
---
function hedon_istee_screenplay:start()
	if (not isZoneEnabled("tatooine")) then	
		return
	end
	
	self:spawnMobiles()
end

function hedon_istee_screenplay:spawnMobiles()
	local pHedonIstee = spawnMobile("tatooine", "hedon_istee", 1, self.loc.hedon.x, self.loc.hedon.z, self.loc.hedon.y, 0, 0)
	local pDrognuz = spawnMobile("tatooine", "drognuz", 10, self.loc.drog.x, self.loc.drog.z, self.loc.drog.y, 0, 0)
	local pRathKana = spawnMobile("tatooine", "rath_kana", 60, self.loc.rath.x, self.loc.rath.z, self.loc.rath.y, 0, 0)
	local pSereneFloater = spawnMobile("tatooine", "serene_floater", 60, self.loc.monk.x, self.loc.monk.z, self.loc.monk.y, 0, 0)
	
	local hedonIstee = LuaCreatureObject(pHedonIstee)
	local drognuz = LuaCreatureObject(pDrognuz)
	local rathKana = LuaCreatureObject(pRathKana)
	local sereneFloater = LuaCreatureObject(pSereneFloater)
	
	writeData("hedon_istee:hedonIsteeID", hedonIstee:getObjectID())
	writeData("hedon_istee:drognuzID", drognuz:getObjectID())
	writeData("hedon_istee:rathKanaID", rathKana:getObjectID())
	writeData("hedon_istee:sereneFloaterID", sereneFloater:getObjectID())
	
	createObserver(OBJECTDESTRUCTION, "hedon_istee_screenplay", "notifyDefeated", pDrognuz)
	createObserver(OBJECTINRANGEMOVED, "hedon_istee_screenplay", "notifyProximityBreeched", pDrognuz)
	createObserver(OBJECTDESTRUCTION, "hedon_istee_screenplay", "notifyDefeated", pRathKana)
	createObserver(OBJECTINRANGEMOVED, "hedon_istee_screenplay", "notifyProximityBreeched", pRathKana)
	createObserver(OBJECTINRANGEMOVED, "hedon_istee_screenplay", "notifyProximityBreeched", pSereneFloater)
end

function hedon_istee_screenplay:notifyDefeated(pVictim, pAttacker)
	local victim = LuaCreatureObject(pVictim)
	local attacker = LuaSceneObject(pAttacker)
	
	if (attacker:isCreatureObject()) then
		local creature = LuaCreatureObject(pAttacker)
		local pPlayerObject = creature:getPlayerObject()

		if (victim:getObjectID() == readData("hedon_istee:drognuzID")) then
			if (self:hasState(creature, self.states.quest1.started) and (not self:hasState(player, self.states.quest1.defeated))) then
				if (pPlayerObject ~= nil) then
					local playerObject = LuaPlayerObject(pPlayerObject)
					playerObject:addWaypoint("tatooine", "Return to Hedon Istee", "", hedon_istee_screenplay.loc.hedon.x, hedon_istee_screenplay.loc.hedon.y, WAYPOINTBLUE, true, true)
				end
				
				self:setState(creature, self.states.quest1.defeated)
			end
		elseif (victim:getObjectID() == readData("hedon_istee:rathKanaID")) then
			if (self:hasState(creature, self.states.quest2.started) and (not self:hasState(player, self.states.quest2.defeated))) then
				if (pPlayerObject ~= nil) then
					local playerObject = LuaPlayerObject(pPlayerObject)
					playerObject:addWaypoint("tatooine", "Return to Hedon Istee", "", hedon_istee_screenplay.loc.hedon.x, hedon_istee_screenplay.loc.hedon.y, WAYPOINTBLUE, true, true)
				end
				
				self:setState(creature, self.states.quest2.defeated)
			end
		end
	end

	return 0
end

function hedon_istee_screenplay:notifyProximityBreeched(pMobile, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	local mobile = LuaCreatureObject(pMobile)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local currentTimestamp = getTimestamp()
		
		if (mobile:getObjectID() == readData("hedon_istee:drognuzID")) then
			if (self:hasState(player, self.states.quest1.started) and (not self:hasState(player, self.states.quest1.defeated))) then
				local lastBark = readData("hedon_istee:drognuz_bark")
				
				--If he hasn't barked in 60 seconds, then let him bark...
				if (lastBark + 60 <= currentTimestamp) then
					spatialChat(pMobile, "@static_npc/tatooine/hedon_istee:npc_breech_1") --Grunt!
					writeData("hedon_istee:drognuz_bark", getTimestamp())
				end
			end
		elseif (mobile:getObjectID() == readData("hedon_istee:rathKanaID")) then
			if (self:hasState(player, self.states.quest2.started) and (not self:hasState(player, self.states.quest2.defeated))) then
				local lastBark = readData("hedon_istee:rath_bark")
				
				if (lastBark + 60 <= currentTimestamp) then
					spatialChat(pMobile, "@static_npc/tatooine/hedon_istee:npc_breech_2") --All the B'omarr want is that sacred scroll. You're in my way and must be removed.
					writeData("hedon_istee:rath_bark", getTimestamp())
				end
			end
		elseif (mobile:getObjectID() == readData("hedon_istee:sereneFloaterID")) then
			if (self:hasState(player, self.states.quest3.started) and (not self:hasState(player, self.states.quest3.defeated))) then
				local lastBark = readData("hedon_istee:monk_bark")
				
				if (lastBark + 60 <= currentTimestamp) then
					spatialChat(pMobile, "@static_npc/tatooine/hedon_istee:npc_breech_3") --May you come to know the serenity of emptiness, sensualist.
					writeData("hedon_istee:monk_bark", getTimestamp())
				end
			end
		end
	end
	
	return 0
end

function hedon_istee_screenplay:giveReward(creatureObject, level)
	if (creatureObject == nil) then
		return false
	end
	
	if (level == 3) then
		--Add the ancient holo map.
		self:setState(creatureObject, self.states.quest3.completed)
	elseif (level == 2) then
		creatureObject:addCashCredits(6000, true)
		--TODO: Should there be a system message?
		self:setState(creatureObject, self.states.quest2.completed)
	else
		creatureObject:addCashCredits(3000, true)
		--TODO: Should there be a system message?
		self:setState(creatureObject, self.states.quest1.completed)
	end
end


--------------------------------------
--   Common functions                -
--------------------------------------
function hedon_istee_screenplay:hasState(creatureObject, state)
	if (creatureObject == nil) then
		return false
	end

	local val = creatureObject:hasScreenPlayState(state, "hedon_istee")

	if (val == 1) then
		return true
	end

	return false
end

function hedon_istee_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "hedon_istee")
end



---
--Hedon Istee Conversation Handler
---
hedon_istee_handler = Object:new {
}

function hedon_istee_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()

	if (screenID == "npc_2_1") then
		self:beginQuest1(player)
	elseif (screenID == "npc_2_2") then
		self:beginQuest2(player)
	elseif (screenID == "npc_2_3") then
		self:beginQuest3(player)
	elseif (screenID == "npc_reset") then
		self:resetQuest(player)
	end

	return conversationScreen
end

function hedon_istee_handler:beginQuest1(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	--Waypoint to Drognuz
	playerObject:addWaypoint("tatooine", "Eliminate the Bodyguard", "", hedon_istee_screenplay.loc.drog.x, hedon_istee_screenplay.loc.drog.y, WAYPOINTBLUE, true, true)

	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest1.started)
end

function hedon_istee_handler:beginQuest2(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	playerObject:addWaypoint("tatooine", "Eliminate the Bounty Hunter", "", hedon_istee_screenplay.loc.rath.x, hedon_istee_screenplay.loc.rath.y, WAYPOINTBLUE, true, true)
	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest2.started)
end

function hedon_istee_handler:beginQuest3(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	playerObject:addWaypoint("tatooine", "Deliver the Scroll", "", hedon_istee_screenplay.loc.monk.x, hedon_istee_screenplay.loc.monk.y, WAYPOINTBLUE, true, true)
	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest3.started)
end

function hedon_istee_handler:resetQuest(player)
end

function hedon_istee_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local faction = conversingPlayer:getFaction()
	local pPlayerObject = conversingPlayer:getPlayerObject()
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	local inventory = LuaSceneObject(pInventory)

	if (pPlayerObject == nil) then
		return nil
	end

	local playerObject = LuaPlayerObject(pPlayerObject)

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("nextQuest")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.delivered, "hedon_istee") == 1) then
		hedon_istee_screenplay:giveReward(conversingPlayer, 3)
		return convoTemplate:getScreen("npc_reward_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_1_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.defeated, "hedon_istee") == 1) then
		hedon_istee_screenplay:giveReward(conversingPlayer, 2)
		return convoTemplate:getScreen("npc_reward_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_1_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.defeated, "hedon_istee") == 1) then
		hedon_istee_screenplay:giveReward(conversingPlayer, 1)
		return convoTemplate:getScreen("npc_reward_1")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_1")
	end

	--We need to check skill points here maybe?
	--if (faction ~= 3679112276) then
	--return convoTemplate:getScreen("notyet")
	--end

	return convoTemplate:getScreen("npc_1_1") --First quest
end

function hedon_istee_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local player = LuaCreatureObject(pPlayer)
	local pConversationSession = player:getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then	
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
