dolac_legasi_screenplay = ScreenPlay:new {
	numberOfActs = 1
}

registerScreenPlay("dolac_legasi_screenplay", true)

function dolac_legasi_screenplay:start()
	local loc = self:getEscapedPrisonerLocation()
	local pActiveArea = spawnSceneObject("dathomir", "object/active_area.iff", loc.x, loc.z, loc.y, 0, 0, 0, 0, 0)
	
	if (pActiveArea == nil) then
		return 0
	end
	
	local activeArea = LuaActiveArea(pActiveArea)
	activeArea:setRadius(50)
	
	createObserver(ENTEREDAREA, "dolac_legasi_screenplay", "spawnEscapedPrisoner", pActiveArea)
end

function dolac_legasi_screenplay:getEscapedPrisonerLocation()
	return {x = -5866, z = 129, y = 809}
end

function dolac_legasi_screenplay:spawnEscapedPrisoner(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (not movingObject:isCreatureObject()) then
		return 0
	end
	
	local player = LuaCreatureObject(pMovingObject)
	
	if (player:hasScreenPlayState(1, "dolac_legasi") == 1) then
		local isSpawned = readData(player:getObjectID() .. ":dolac_legasi:escapedprisoner_spawned")
		
		if (isSpawned ~= 1) then
			writeData(player:getObjectID() .. ":dolac_legasi:escapedprisoner_spawned", 1)
			
			local pPrisoner = spawnMobile("dathomir", "dolac_escaped_prisoner", -5866, 129, 809, 0)
			local prisoner = LuaSceneObject(pPrisoner)
			
			local pTamer = spawnMobile("dathomir", "nightsister_rancor_tamer", -5872, 129, 812, 0)
			local tamer = LuaSceneObject(pTamer)
			
			writeData(player:getObjectID() .. ":dolac_legasi:prisonerID", prisoner:getObjectID())
			writeData(player:getObjectID() .. ":dolac_legasi:tamerID", tamer:getObjectID())
			writeData(tamer:getObjectID() .. ":dolac_legasi:questOwnerID", player:getObjectID())
			
			createObserver(OBJECTDESTRUCTION, "dolac_legasi_screenplay", "defendEscapedPrisoner", pTamer)
			createObserver(OBJECTINRANGEMOVED, "dolac_legasi_screenplay", "barkEscapedPrisoner", pPrisoner)
			createObserver(STOPCONVERSATION, "dolac_legasi_screenplay", "escortEscapedPrisoner", pPrisoner)
		end
	end
	
	return 0
end

function dolac_legasi_screenplay:defendEscapedPrisoner(pVictim, pAttacker)
	local tamer = LuaCreatureObject(pVictim)
	local ownerObjectID = readData(tamer:getObjectID() .. ":doloc_legasi:questOwnerID")
	writeData(ownerObjectID .. ":dolac_legasi:escapedprisoner_killed_tamer", 1)
	
	return 1
end

function dolac_legasi_screenplay:barkEscapedPrisoner(pPrisoner, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (not movingObject:isCreatureObject()) then
		return 0
	end
	
	local prisoner = LuaCreatureObject(pPrisoner)
	
	local distance = prisoner:getDistanceTo(pMovingObject)
	
	if (distance > 16) then
		return 0
	end
	
	local creatureObject = LuaCreatureObject(pMovingObject)
	
	--if they are on this part of the quest, and not progressed, or before it.
	if (creatureObject:hasScreenPlayState(1, "dolac_legasi") == 1 and not creatureObject:hasScreenPlayState(2, "dolac_legasi")) then
		local isSpawned = readData(creatureObject:getObjectID() .. ":dolac_legasi:escapedprisoner_spawned")
		
		if (isSpawned == 1) then
			local hasSpoken = readData(creatureObject:getObjectID() .. ":dolac_legasi:escapedprisoner_spoken_initial")
			
			if (hasSpoken ~= 1) then
				spatialChat(pPrisoner, "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_takeme_1") --Can you see them? The wraiths? There is no escaping them! They will always be there!
				writeData(creatureObject:getObjectID() .. ":dolac_legasi:escapedprisoner_spoken_initial", 1)
				
				return 1
			end
		end
	end
	
	return 0
end

function dolac_legasi_screenplay:escortEscapedPrisoner(pPrisoner, pPlayer)
	local prisonerObject = LuaCreatureObject(pPrisoner)
	
	local prisoner = LuaAiAgent(pPrisoner)
	local player = LuaCreatureObject(pPlayer)

	local distance = prisonerObject:getDistanceTo(pPlayer)
	
	if (distance == 0) then
		return 0
	end
	
	if (distance > 32) then
		return 0
	end

	prisoner:setFollowObject(pPlayer)
	
	player:setScreenPlayState(2, "dolac_legasi")
	
	return 1
end

function dolac_legasi_screenplay:despawnEscortCreatures(player)
	local prisonerID = readData(player:getObjectID() .. ":dolac_legasi:prisonerID")
	local tamerID = readData(player:getObjectID() .. ":dolac_legasi:tamerID")
	
	local pPrisoner = getCreatureObject(prisonerID)
	local pTamer = getCreatureObject(tamerID)
	
	if (pPrisoner ~= nil) then
		local prisoner = LuaSceneObject(pPrisoner)
		prisoner:destroyObjectFromWorld()
	end
	
	if (pTamer ~= nil) then
		local tamer = LuaSceneObject(pTamer)
		tamer:destroyObjectFromWorld()
	end
	
	--Cleanup stage 1 data
	deleteData(player:getObjectID() .. ":dolac_legasi:prisonerID")
	deleteData(player:getObjectID() .. ":dolac_legasi:tamerID")
	deleteData(player:getObjectID() .. ":dolac_legasi:escapedprisoner_spawned")
	deleteData(player:getObjectID() .. ":dolac_legasi:escapedprisoner_spoken_initial")
end

function dolac_legasi_screenplay:rewardQuest1(player, playerObject)
	player:addCashCredits(350, true)
	playerObject:increaseFactionStanding("imperial", 10)
	
	player:setScreenPlayState(4, "dolac_legasi")
end

dolac_legasi_handler = Object:new {
}

function dolac_legasi_handler:getNextConversationScreen(conversationTemplate, conversingPlayer, selectedOption, conversingNPC)
	local creature = LuaCreatureObject(conversingPlayer)
	local convosession = creature:getConversationSession()
	
	lastConversationScreen = nil
	
	if (convosession ~= nil) then
		local session = LuaConversationSession(convosession)
		lastConversationScreen = session:getLastConversationScreen()
	end
		
	local conversation = LuaConversationTemplate(conversationTemplate)
		
	local nextConversationScreen
	
	--printf("last conv screen " .. lastConversationScreen .. "\n")
	
	if (lastConversationScreen ~= nil) then	
		--Get the linked screen for the selected option.
		local luaLastConversationScreen = LuaConversationScreen(lastConversationScreen)
		local optionLink = luaLastConversationScreen:getOptionLink(selectedOption)
		
		--printf("optionLink " .. optionLink .. "\n")
		
		nextConversationScreen = conversation:getScreen(optionLink)
		
		if (nextConversationScreen == nil) then
			printf("nextConversationScreen nill for option link = " .. optionLink .. "\n")
		end
	else
		nextConversationScreen = self:getInitialScreen(conversingPlayer, conversingNPC, conversationTemplate)
	end
	
	return nextConversationScreen
end

function dolac_legasi_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	
	local screenID = screen:getScreenID()
	
	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()
	
	if (screenID == "npc_2_1") then
		self:beginEscortQuest(player)
	elseif (screenID == "npc_reset") then
		self:resetQuest(player)
	end
	
	return conversationScreen
end

function dolac_legasi_handler:beginEscortQuest(player)
	local playerObjectPointer = player:getPlayerObject()
	local playerObject = LuaPlayerObject(playerObjectPointer)
	
	player:setScreenPlayState(1, "dolac_legasi")
	
	local loc = dolac_legasi_screenplay:getEscapedPrisonerLocation()
	--addWaypoint(planet, name, desc, x, y, color, active, notifyClient)
	playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_name_1", "@@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_description_1", loc.x, loc.y, WAYPOINTBLUE, true, true)
end

function dolac_legasi_handler:resetQuest(player)
	player:removeScreenPlayState(1, "dolac_legasi")
end

function dolac_legasi_handler:getInitialScreen(pPlayer, npc, conversationTemplate)
	local convoTemplate = LuaConversationTemplate(conversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local faction = conversingPlayer:getFaction()
	local pPlayerObject = conversingPlayer:getPlayerObject()
	
	if (pPlayerObject == nil) then
		return nil
	end
	
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	if (conversingPlayer:hasScreenPlayState(4, "dolac_legasi") == 1) then
		--Time for quest #2
		return nil
	end
	
	if (conversingPlayer:hasScreenPlayState(2, "dolac_legasi") == 1) then
		dolac_legasi_screenplay:despawnEscortCreatures(conversingPlayer)
		dolac_legasi_screenplay:rewardQuest1(conversingPlayer, playerObject)
		
		return convoTemplate:getScreen("npc_reward_1")
	end
	
	if (conversingPlayer:hasScreenPlayState(1, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("npc_work_1")
	end
	
	--Check if they are Imperial
	if (faction ~= 3679112276) then
		local val = math.random(2)
		
		if (val == 1) then
			return convoTemplate:getScreen("dontknowyou_1")
		else
			return convoTemplate:getScreen("dontknowyou_3")
		end
	end
	
	return convoTemplate:getScreen("npc_1_1")
end
