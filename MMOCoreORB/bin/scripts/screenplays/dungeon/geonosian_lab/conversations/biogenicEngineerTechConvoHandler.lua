local ObjectManager = require("managers.object.object_manager")

BiogenicEngineerTechConvoHandler = Object:new {}

function BiogenicEngineerTechConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, conversationScreen)
	return ObjectManager.withCreatureObject(pConversingPlayer, function(player)
		local screen = LuaConversationScreen(conversationScreen)

		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)

		local screenID = screen:getScreenID()

		if screenID == "init_talk" then
			if (GeonosianLabScreenPlay:hasGeoItem(pConversingPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
				clonedConversation:addOption("@conversation/biogenic_engineertech:s_a7b6a9c7", "oh_yes_codes")
			end
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_56fde3ca", "could_use_help")
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_428087e9", "knocked_out_power")
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_99c2fa91", "wandered_bad_spot")
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_9d6ccb86", "thanks_for_stopping")
		elseif screenID == "come_back_with_codes" or screenID == "come_back_when_find" then
			writeData(player:getObjectID() .. ":geo_engineertech_talked", 1)
		elseif screenID == "return_init" then
			if (GeonosianLabScreenPlay:hasGeoItem(pConversingPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
				clonedConversation:addOption("@conversation/biogenic_engineertech:s_da5959ed", "yes_here_are_codes")
			end
			clonedConversation:addOption("@conversation/biogenic_engineertech:s_27707b65", "come_back_when_find")
		elseif (screenID == "yes_here_are_codes" or screenID == "oh_yes_codes") and GeonosianLabScreenPlay:hasGeoItem(pConversingPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff") then
			GeonosianLabScreenPlay:removeGeoItem(pConversingPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")
			GeonosianLabScreenPlay:giveGeoItem(pConversingPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_key.iff")
			player:setScreenPlayState(1, "geonosian_lab_datapad_delivered");
		end
		return conversationScreen
	end)
end

function BiogenicEngineerTechConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local hasTalked = readData(player:getObjectID() .. ":geo_engineertech_talked")
		if (player:hasScreenPlayState(1, "geonosian_lab_datapad_delivered")) then
			return convoTemplate:getScreen("things_under_control")
		elseif (hasTalked ~= nil and hasTalked == 1) then
			return convoTemplate:getScreen("return_init")
		end
		return convoTemplate:getScreen("init_talk")
	end)
end

function BiogenicEngineerTechConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

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