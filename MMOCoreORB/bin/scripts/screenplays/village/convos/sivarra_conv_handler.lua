--[[
** THIS IS THE CONVO HANDLER FOR SIVARRA VILLAGE NPC.

VillageSivarraScreenPlay - the name of the screenplaystate key.

Values:
0 - Has not accepted the quest
1 - Accepted the quest, has not treated any patients.

]]

local ObjectManager = require("managers.object.object_manager")

villageSivarraConvoHandler = Object:new {}

function villageSivarraConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function villageSivarraConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local phase = 1 -- add in the function to get it later...
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local state =	CreatureObject(pConversingPlayer):getScreenPlayState("VillageSivarraScreenPlay")

	if (phase == 1) then
		if (state == 0) then
			return convoTemplate:getScreen("intro")
		elseif (state == 1) then
			return convoTemplate:getScreen("intro")
		end
	end
end

function villageSivarraConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "intro") then
	end

	return pConversationScreen
end
