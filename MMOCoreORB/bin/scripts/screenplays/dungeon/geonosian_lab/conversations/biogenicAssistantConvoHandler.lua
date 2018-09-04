local ObjectManager = require("managers.object.object_manager")

BiogenicAssistantConvoHandler = conv_handler:new {}

function BiogenicAssistantConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if screenID == "init_talk" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geo_assistant_talked", 1)
	elseif screenID == "really_fantastic" then
		GeonosianLab:giveGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")
	end
	return pConvScreen
end

function BiogenicAssistantConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local hasTalked = readData(CreatureObject(pPlayer):getObjectID() .. ":geo_assistant_talked")

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "geonosian_lab_datapad_delivered")) then
		return convoTemplate:getScreen("thanks_for_delivering")
	elseif (GeonosianLab:hasGeoItem(pPlayer, "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff")) then
		return convoTemplate:getScreen("please_deliver_codes")
	elseif (hasTalked ~= nil and hasTalked == 1) then
		return convoTemplate:getScreen("back_ask_favor")
	end
	return convoTemplate:getScreen("init_talk")
end
