local ObjectManager = require("managers.object.object_manager")

BiogenicScientistHumanConvoHandler = Object:new {}

function BiogenicScientistHumanConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if screenID == "since_youre_here" or screenID == "i_hope_so" then
		CreatureObject(pConversingPlayer):setScreenPlayState(1, "geonosian_lab_tenloss");
		GeonosianLabScreenPlay:giveGeoItem(pConversingPlayer, "object/tangible/loot/loot_schematic/geonosian_tenloss_dxr6_schematic.iff")
	end

	return pConversationScreen
end

function BiogenicScientistHumanConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "geonosian_lab_tenloss")) then
		return convoTemplate:getScreen("go_on_ahead")
	elseif (readData(CreatureObject(pPlayer):getObjectID() .. ":geoTalkedToHumanScientist") == 1) then
		return convoTemplate:getScreen("glad_youre_back")
	end

	return convoTemplate:getScreen("thanks_so_much")
end

function BiogenicScientistHumanConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
