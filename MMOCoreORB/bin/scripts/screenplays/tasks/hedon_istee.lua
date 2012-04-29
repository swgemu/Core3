hedon_istee_screenplay = ScreenPlay:new {
	numberOfActs = 1,

	states = {
		quest1 = {started = 1, defeated = 2, completed = 8},
		quest2 = {started = 16, defeated = 32, completed = 64},
		quest3 = {started = 128, delivered = 256, completed = 512}
	},

	loc = {
		hedon	= {x = 1390, z = 0, y = 3195},
		drog	= {x = 1553, z = 15, y = 3488},
		rath	= {x = 1800, z = 7, y = 3128},
		monk	= {x = 1560, z = 7, y = 2970},
		map		= {x = 6700, z = 20, y = 4240}
	},
	
	bomarr_scroll = "object/tangible/mission/quest_item/hedon_istee_q3_needed.iff",
	
	--Time for the treasure to stay spawned before it is removed from the game in miliseconds.
	treasure_life = 600000 --10 minutes
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
	self:spawnActiveAreas()
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

function hedon_istee_screenplay:spawnActiveAreas()
	local pActiveArea = spawnSceneObject("tatooine", "object/active_area.iff", self.loc.map.x, self.loc.map.z, self.loc.map.y, 0, 0, 0, 0, 0)
	local area = LuaSceneObject(pActiveArea)
	
	writeData("hedon_istee:treasureAreaID", area:getObjectID())
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
		local pInventory = creatureObject:getSlottedObject("inventory")
		
		if (pInventory ~= nil) then
			local pMap = giveItem(pInventory, "object/tangible/loot/quest/treasure_map_hedon.iff", -1)
			
			if (pMap ~= nil) then
				local map = LuaSceneObject(pMap)
				map:sendTo(creatureObject:_getObject())
			end
		end
		
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


function hedon_istee_screenplay:handleTreasureMapCallback(pCreature, pSui, cancelPressed)
	if (not cancelPressed) then
		if (pCreature ~= nil) then
			local creature = LuaCreatureObject(pCreature)
			local pPlayerObject = creature:getPlayerObject()
			
			if (pPlayerObject ~= nil) then
				local playerObject = LuaPlayerObject(pPlayerObject)
				playerObject:addWaypoint("tatooine", "Ancient Treasure Location", "", hedon_istee_screenplay.loc.map.x, hedon_istee_screenplay.loc.map.y, WAYPOINTBLUE, true, true)
			end
		end
	end
end

function hedon_istee_screenplay:spawnTreasure(pTreasureMap, pPlayer)
	local creature = LuaCreatureObject(pPlayer)
	creature:sendSystemMessage("@treasure_map/treasure_map:sys_found") --You successfully extract the treasure!
	
	local pChest = spawnSceneObject("tatooine", "object/tangible/container/drum/treasure_drum.iff", self.loc.map.x, self.loc.map.z, self.loc.map.y, 0, 0, 0, 0, 0)
	local pKrayt = spawnMobile("tatooine", "canyon_krayt_dragon", 0, self.loc.map.x, self.loc.map.z, self.loc.map.y, 0, 0)
	
	createLoot(pChest, "hedon_istee_treasure", 10)
	createEvent(self.treasure_life, "hedon_istee_screenplay", "removeTreasureChest", pChest)
	
	if (pTreasureMap ~= nil) then
		local map = LuaSceneObject(pTreasureMap)
		map:destroyObjectFromWorld()
		map:destroyObjectFromDatabase()
	end
	
	--Spawn event to remove chest after x time.
end

function hedon_istee_screenplay:removeTreasureChest(pChest)
	if (pChest ~= nil) then
		local chest = LuaSceneObject(pChest)
		chest:destroyObjectFromWorld()
		chest:destroyObjectFromDatabase(true)
	end
end

hedon_istee_holo_map_menucomponent = { }


function hedon_istee_holo_map_menucomponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	
	local player = LuaSceneObject(pPlayer)
	
	if (player:hasActiveArea(readData("hedon_istee:treasureAreaID"))) then
		menuResponse:addRadialMenuItem(121, 3, "@treasure_map/treasure_map:extract_treasure") --Extract Treasure
	else
		menuResponse:addRadialMenuItem(120, 3, "@treasure_map/treasure_map:use") --Read
	end
end

function hedon_istee_holo_map_menucomponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end
	
	if (selectedID == 120) then
		local suiManager = LuaSuiManager()
		suiManager:sendMessageBox(pSceneObject, pPlayer, "@treasure_map/treasure_map:title_hedon1", "@treasure_map/treasure_map:text_hedon1", "@treasure_map/treasure_map:store_waypoint", "hedon_istee_screenplay", "handleTreasureMapCallback")
	elseif (selectedID == 121) then
		hedon_istee_screenplay:spawnTreasure(pSceneObject, pPlayer)
	end
			
	return 0
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
	elseif (screenID == "npc_reset_1") or (screenID == "npc_reset_2") or (screenID == "npc_reset_3") then
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
	
	local pInventory = player:getSlottedObject("inventory")

	playerObject:addWaypoint("tatooine", "Deliver the Scroll", "", hedon_istee_screenplay.loc.monk.x, hedon_istee_screenplay.loc.monk.y, WAYPOINTBLUE, true, true)
	local pScroll = giveItem(pInventory, hedon_istee_screenplay.bomarr_scroll, -1)
	
	if (pScroll ~= nil) then
		local scroll = LuaSceneObject(pScroll)
		scroll:sendTo(player:_getObject())
	end
	
	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest3.started)
end

function hedon_istee_handler:resetQuest(player)
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest1.started, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest1.defeated, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest1.completed, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest2.started, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest2.defeated, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest2.completed, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest3.started, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest3.defeated, "hedon_istee")
	player:removeScreenPlayState(hedon_istee_screenplay.states.quest3.completed, "hedon_istee")
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
		return convoTemplate:getScreen("next")
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


---
--Serene Floater Conversation Handler
---
serene_floater_handler = Object:new {
}

function serene_floater_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return conversationScreen
end

function serene_floater_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local pInventory = conversingPlayer:getSlottedObject("inventory")
	local inventory = LuaSceneObject(pInventory)
	
	if (pInventory ~= nil) then
		local pScroll = getContainerObjectByTemplate(pInventory, hedon_istee_screenplay.bomarr_scroll, true)
		
		if (pScroll ~= nil) then
			local scroll = LuaSceneObject(pScroll)
			scroll:destroyObjectFromWorld()
			scroll:destroyObjectFromDatabase()
			
			conversingPlayer:setScreenPlayState(hedon_istee_screenplay.states.quest3.delivered, "hedon_istee")
			
			local pPlayerObject = conversingPlayer:getPlayerObject()
			
			if (pPlayerObject ~= nil) then
				local playerObject = LuaPlayerObject(pPlayerObject)
				playerObject:addWaypoint("tatooine", "Return to Hedon Istee", "", hedon_istee_screenplay.loc.hedon.x, hedon_istee_screenplay.loc.hedon.y, WAYPOINTBLUE, true, true)
			end
			
			--They had the scroll
			return convoTemplate:getScreen("npc_smuggle_3")
		end
	end
	
	--Don't know the person, they don't have the scroll.
	return convoTemplate:getScreen("dontknowyou_3")
end

function serene_floater_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
