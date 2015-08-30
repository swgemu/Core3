local ObjectManager = require("managers.object.object_manager")

imperialInformantConvoHandler = Object:new {}

function imperialInformantConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	local npcID = SceneObject(npc):getObjectID()
	local playersNpcID = readData(SceneObject(pPlayer):getObjectID() .. ":coaNpcID")

	if npcID == playersNpcID then
		return convoTemplate:getScreen("m1_informant")
	else
		return convoTemplate:getScreen("m1_informant_invalid")
	end
end

function imperialInformantConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	if screenID == "m1_informant_report" then
		Coa2Screenplay:progressMissionOne(conversingPlayer, "imperial")
	end

	return conversationScreen
end

function imperialInformantConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
