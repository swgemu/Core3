local ObjectManager = require("managers.object.object_manager")

BiogenicSecurityTechConvoHandler = conv_handler:new {}

function BiogenicSecurityTechConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if screenID == "init_firsttalk" then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":geo_security_tech_talked", 1)
	end
	return pConvScreen
end

function BiogenicSecurityTechConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local hasTalked = readData(CreatureObject(pPlayer):getObjectID() .. ":geo_security_tech_talked")
	if (hasTalked ~= nil and hasTalked == 1) then
		return convoTemplate:getScreen("im_very_busy")
	else
		return convoTemplate:getScreen("init_firsttalk")
	end
end
