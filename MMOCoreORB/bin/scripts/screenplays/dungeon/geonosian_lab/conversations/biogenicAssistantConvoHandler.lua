local ObjectManager = require("managers.object.object_manager")

BiogenicAssistantConvoHandler = Object:new {}

function BiogenicAssistantConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if screenID == "init_talk" then
		writeData(CreatureObject(pConversingPlayer):getObjectID() .. ":geo_assistant_talked", 1)
	elseif screenID == "really_fantastic" then
		GeonosianLabScreenPlay:giveGeoItem(pConversingPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")
	end
	return pConversationScreen
end

function BiogenicAssistantConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local hasTalked = readData(CreatureObject(pPlayer):getObjectID() .. ":geo_assistant_talked")

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "geonosian_lab_datapad_delivered")) then
		return convoTemplate:getScreen("thanks_for_delivering")
	elseif (GeonosianLabScreenPlay:hasGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
		return convoTemplate:getScreen("please_deliver_codes")
	elseif (hasTalked ~= nil and hasTalked == 1) then
		return convoTemplate:getScreen("back_ask_favor")
	end
	return convoTemplate:getScreen("init_talk")
end

function BiogenicAssistantConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
