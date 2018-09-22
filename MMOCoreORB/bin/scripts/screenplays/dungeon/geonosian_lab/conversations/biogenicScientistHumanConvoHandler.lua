local ObjectManager = require("managers.object.object_manager")

BiogenicScientistHumanConvoHandler = conv_handler:new {}

function BiogenicScientistHumanConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if screenID == "here_it_is" or screenID == "no_i_want_you_to" or screenID == "no_i_insist" or screenID == "no_youre_right" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoHumanScientistState", 2)
		GeonosianLab:giveGeoItem(pPlayer, "object/tangible/loot/loot_schematic/geonosian_tenloss_dxr6_schematic.iff")
	elseif screenID == "killed_quite_a_few" or screenID == "well_yes" or screenID == "thank_you_wait" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoHumanScientistState", 1)
	elseif screenID == "since_youre_here" or screenID == "i_hope_so" or screenID == "no_problem_at_all" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoHumanScientistState", 3)
	end

	return pConvScreen
end

function BiogenicScientistHumanConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local scientistState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoHumanScientistState")

	if (scientistState == nil or scientistState == 0) then
		return convoTemplate:getScreen("thanks_so_much")
	elseif (scientistState == 3) then
		return convoTemplate:getScreen("go_on_ahead")
	elseif (scientistState == 2) then
		return convoTemplate:getScreen("since_youre_here")
	elseif (scientistState == 1) then
		return convoTemplate:getScreen("glad_youre_back")
	end

	return convoTemplate:getScreen("thanks_so_much")
end
