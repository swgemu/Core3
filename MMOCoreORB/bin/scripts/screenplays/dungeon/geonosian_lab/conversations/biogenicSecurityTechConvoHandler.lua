local ObjectManager = require("managers.object.object_manager")

BiogenicSecurityTechConvoHandler = conv_handler:new {}

function BiogenicSecurityTechConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if screenID == "sith_spit" or screenID == "seismic_event" or screenID == "forget_you_saw" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoSecurityTechState", 1)
	elseif screenID == "first_need_code" or screenID == "could_use_help" or screenid == "your_funeral" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geoSecurityTechState", 2)
	end
	return pConvScreen
end

function BiogenicSecurityTechConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local techState = readData(CreatureObject(pPlayer):getObjectID() .. ":geoSecurityTechState")
	if (techState == nil or techState == 0) then
		return convoTemplate:getScreen("init_firsttalk")
	elseif (techState == 1) then
		return convoTemplate:getScreen("im_very_busy")
	elseif (techState == 2) then
		return convoTemplate:getScreen("init_anything_else")
	end

	return convoTemplate:getScreen("init_firsttalk")
end
