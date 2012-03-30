ris_armor_quest_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
		quest1 = {started = 1, paid = 2},
		quest2 = {complete = 4},
		quest3 = {started = 8},
		quest4 = {complete = 16},
		quest5 = {started = 32},
		quest6 = {complete = 64}
	}
	
	
}

registerScreenPlay("ris_armor_quest_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function ris_armor_quest_screenplay:start()
	self:spawnMobiles()
end

function ris_armor_quest_screenplay:spawnMobiles()
	local pMolNimai = spawnMobile("dantooine", "mol_nimai", 1, -6805, 126, 6022, 179, 0)
	local molNimai = LuaSceneObject(pMolNimai)
	molNimai:setCustomObjectName("Mol Ni'mai")
end

--------------------------------------
--   Common functions                -
--------------------------------------
function ris_armor_quest_screenplay:hasState(player, state)
	if (player == nil) then
		return false
	end
	
	local val = player:hasScreenPlayState(state, "ris_armor_quest")
	
	if (val == 1) then
		return true
	end
	
	return false
end

function ris_armor_quest_screenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":ris_armor_quest:spawned:" .. key)
	
	if (val == 1) then
		return true
	end
	
	return false
end

function ris_armor_quest_screenplay:setSpawned(objectID, key)
	writeData(objectID .. ":ris_armor_quest:spawned:" .. key, 1)
end

function ris_armor_quest_screenplay:deleteSpawnedSetting(objectID, key)
	deleteData(objectID .. ":ris_armor_quest:spawned:" .. key)
end

function ris_armor_quest_screenplay:writeObjectData(objectID, key, value)
	if (objectID == nil) then
		return 0
	end
	
	writeData(objectID .. ":ris_armor_quest:" .. key, value)
end

function ris_armor_quest_screenplay:readObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	return readData(objectID .. ":ris_armor_quest:" .. key)
end

function ris_armor_quest_screenplay:deleteObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	deleteData(objectID .. ":ris_armor_quest:" .. key)
end

function ris_armor_quest_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "ris_armor_quest")
end

function ris_armor_quest_screenplay:removeState(creatureObject, state)
	creatureObject:removeScreenPlayState(state, "ris_armor_quest")
end


--------------------------------------
-- ris_armor_quest Conversation Handler -
--------------------------------------
ris_armor_quest_handler = Object:new {
}

function ris_armor_quest_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	
	local screenID = screen:getScreenID()
	
	local playerCreo = LuaCreatureObject(conversingPlayer)
		
	if (screenID == "quest_1_start_yes") then
		self:payNPC(playerCreo)
	
	elseif (screenID == "quest_1_description") then
		self:startQuest1(playerCreo)
	
	elseif (screenID == "quest_2_query") then
		conversationScreen = screen:cloneScreen()
		screen = LuaConversationScreen(conversationScreen)
		screen:setDialogTextTO("R.I.S. armor segment")
		
	elseif (screenID == "quest_3_start") then
		self:startQuest3(playerCreo)
	
	elseif (screenID == "quest_4_query") then
		conversationScreen = screen:cloneScreen()
		screen = LuaConversationScreen(conversationScreen)
		screen:setDialogTextTO("R.I.S. armor layer")
		
	elseif (screenID == "quest_5_start") then
		self:startQuest5(playerCreo)
	
	elseif (screenID == "quest_6_query") then
		conversationScreen = screen:cloneScreen()
		screen = LuaConversationScreen(conversationScreen)
		screen:setDialogTextTO("R.I.S. armor boots")
		
	elseif (screenID == "quest_6_complete") then
		self:completeQuest6(playerCreo, conversingPlayer)
		
	end
	
	return conversationScreen
end

function ris_armor_quest_handler:payNPC(playerCreo)
	
	playerCreo:subtractCashCredits(50000)	
	ris_armor_quest_screenplay:setState(playerCreo, ris_armor_quest_screenplay.states.quest1.paid)

end

function ris_armor_quest_handler:startQuest1(playerCreo)
	local pPlayerObject = playerCreo:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	playerObject:addRewardedSchematic("object/draft_schematic/armor/armor_segment_ris.iff", -1, true)
	ris_armor_quest_screenplay:setState(playerCreo, ris_armor_quest_screenplay.states.quest1.started)

end

function ris_armor_quest_handler:startQuest3(playerCreo)
	local pPlayerObject = playerCreo:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	playerObject:addRewardedSchematic("object/draft_schematic/armor/component/armor_layer_ris.iff", -1, true)
	ris_armor_quest_screenplay:setState(playerCreo, ris_armor_quest_screenplay.states.quest3.started)

end

function ris_armor_quest_handler:startQuest5(playerCreo)
	local pPlayerObject = playerCreo:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_boots.iff", -1, true)
	ris_armor_quest_screenplay:setState(playerCreo, ris_armor_quest_screenplay.states.quest5.started)

end

function ris_armor_quest_handler:completeQuest6(playerCreo)
	local pPlayerObject = playerCreo:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_bicep_l.iff", -1, true)
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_bicep_r.iff", -1, true)
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_bracer_l.iff", -1, true)
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_bracer_r.iff", -1, true)
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_chest_plate.iff", -1, true)
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_gloves.iff", -1, true)
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_helmet.iff", -1, true)
	playerObject:addRewardedSchematic("object/draft_schematic/clothing/clothing_armor_ris_leggings.iff", -1, true)
	ris_armor_quest_screenplay:setState(playerCreo, ris_armor_quest_screenplay.states.quest6.complete)

end

	
function ris_armor_quest_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local pPlayerObject = conversingPlayer:getPlayerObject()
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	local inventory = LuaSceneObject(pInventory)
	
	if (pPlayerObject == nil) then
		return nil
	end
	
	local playerObject = LuaPlayerObject(pPlayerObject)
	
	if (conversingPlayer:hasScreenPlayState(ris_armor_quest_screenplay.states.quest6.complete, "ris_armor_quest") == 1) then
		return convoTemplate:getScreen("armorsmith_quest")
		--spatialChat(npc,"@quest_armorsmith:armorsmith_quest")
		--return nil
	end
	
	if (conversingPlayer:hasScreenPlayState(ris_armor_quest_screenplay.states.quest5.started, "ris_armor_quest") == 1) then
		return convoTemplate:getScreen("quest_6_query")
	end
	
	if (conversingPlayer:hasScreenPlayState(ris_armor_quest_screenplay.states.quest4.complete, "ris_armor_quest") == 1) then
		return convoTemplate:getScreen("quest_5_start")
	end
	
	if (conversingPlayer:hasScreenPlayState(ris_armor_quest_screenplay.states.quest3.started, "ris_armor_quest") == 1) then
		return convoTemplate:getScreen("quest_4_query")
	end
	
	if (conversingPlayer:hasScreenPlayState(ris_armor_quest_screenplay.states.quest2.complete, "ris_armor_quest") == 1) then
		return convoTemplate:getScreen("quest_3_start")
	end
	
	if (conversingPlayer:hasScreenPlayState(ris_armor_quest_screenplay.states.quest1.started, "ris_armor_quest") == 1) then
		return convoTemplate:getScreen("quest_2_query")
	end
	
	if (conversingPlayer:hasScreenPlayState(ris_armor_quest_screenplay.states.quest1.paid, "ris_armor_quest") == 1) then
		return convoTemplate:getScreen("quest_1_start_yes")
	end
	
	if (conversingPlayer:hasSkill("crafting_armorsmith_master")) then
		return convoTemplate:getScreen("quest_1_start")
	end
	
	return convoTemplate:getScreen("greeting")
	--spatialChat(npc, "@quest_armorsmith:greeting")
	--return nil
		
end

function ris_armor_quest_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
		
		if (optionLink == "quest_1_start_yes") then
			local credits = player:getCashCredits()
			
			if (credits < 50000) then
				return conversationTemplate:getScreen("illegal_response")
			end
		end
		
		if (optionLink == "quest_2_complete") then
			
			local playerSceo = LuaSceneObject(pPlayer)
			inventory = playerSceo:getSlottedObject("inventory")
			armorSegmentPointer = getContainerObjectByTemplate(inventory, "object/tangible/component/armor/armor_segment_ris.iff", true)
			
			if (armorSegmentPointer == nil) then
				return conversationTemplate:getScreen("illegal_response")	
			else
				armorSegmentObject = LuaSceneObject(armorSegmentPointer)				
				armorSegmentObject:destroyObjectFromWorld()
				armorSegmentObject:destroyObjectFromDatabase()
				ris_armor_quest_screenplay:setState(player, ris_armor_quest_screenplay.states.quest2.complete)
			end
			
		end
		
		if (optionLink == "quest_4_complete") then
			
			local playerSceo = LuaSceneObject(pPlayer)
			inventory = playerSceo:getSlottedObject("inventory")
			armorLayerPointer = getContainerObjectByTemplate(inventory, "object/tangible/component/armor/armor_layer_ris.iff", true)
			
			if (armorLayerPointer == nil) then
				return conversationTemplate:getScreen("illegal_response")	
			else
				armorLayerObject = LuaSceneObject(armorLayerPointer)				
				armorLayerObject:destroyObjectFromWorld()
				armorLayerObject:destroyObjectFromDatabase()
				ris_armor_quest_screenplay:setState(player, ris_armor_quest_screenplay.states.quest4.complete)
			end
			
		end
		
		if (optionLink == "quest_6_complete") then
			
			local playerSceo = LuaSceneObject(pPlayer)
			inventory = playerSceo:getSlottedObject("inventory")
			armorBootsPointer = getContainerObjectByTemplate(inventory, "object/tangible/wearables/armor/ris/armor_ris_boots.iff", true)
			
			if (armorBootsPointer == nil) then
				return conversationTemplate:getScreen("illegal_response")	
			else
				armorBootsObject = LuaSceneObject(armorBootsPointer)				
				armorBootsObject:destroyObjectFromWorld()
				armorBootsObject:destroyObjectFromDatabase()
				ris_armor_quest_screenplay:setState(player, ris_armor_quest_screenplay.states.quest6.complete)
			end
			
		end
			
		return conversationTemplate:getScreen(optionLink)
		
	end
	
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

