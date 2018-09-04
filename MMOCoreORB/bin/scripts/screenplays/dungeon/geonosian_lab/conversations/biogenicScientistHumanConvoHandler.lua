local ObjectManager = require("managers.object.object_manager")

BiogenicScientistHumanConvoHandler = conv_handler:new {}

function BiogenicScientistHumanConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if screenID == "since_youre_here" or screenID == "i_hope_so" then
		CreatureObject(pPlayer):setScreenPlayState(1, "geonosian_lab_tenloss");
		GeonosianLab:giveGeoItem(pPlayer, "object/tangible/loot/loot_schematic/geonosian_tenloss_dxr6_schematic.iff")
	end

	return pConvScreen
end

function BiogenicScientistHumanConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(1, "geonosian_lab_tenloss")) then
		return convoTemplate:getScreen("go_on_ahead")
	elseif (readData(CreatureObject(pPlayer):getObjectID() .. ":geoTalkedToHumanScientist") == 1) then
		return convoTemplate:getScreen("glad_youre_back")
	end

	return convoTemplate:getScreen("thanks_so_much")
end
