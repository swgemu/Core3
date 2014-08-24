local ObjectManager = require("managers.object.object_manager")

BiogenicSecurityTechConvoHandler = Object:new {
	}

function BiogenicSecurityTechConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	if screenID == "init_firsttalk" then
		writeData(CreatureObject(pConversingPlayer):getObjectID() .. ":geo_security_tech_talked", 1)
	end
	return pConversationScreen
end

function BiogenicSecurityTechConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local hasTalked = readData(CreatureObject(pPlayer):getObjectID() .. ":geo_security_tech_talked")
	if (hasTalked ~= nil and hasTalked == 1) then
		return convoTemplate:getScreen("im_very_busy")
	else
		return convoTemplate:getScreen("init_firsttalk")
	end
end

function BiogenicSecurityTechConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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