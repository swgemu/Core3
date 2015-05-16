local ObjectManager = require("managers.object.object_manager")

MirlaConversationHandler = Object:new {}

function MirlaConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)

	local screenID = screen:getScreenID()

	if (screenID == "mirla_password") then
		local screen = LuaConversationScreen(pConversationScreen)
		local code = readStringData("warren:mirla:password")
		screen:setDialogTextTO(code)
	elseif (screenID == "mirla_2") then
		ObjectManager.withCreatureAndPlayerObject(pConversingPlayer, function(player, playerObject)
			playerObject:awardBadge(38) --Warren Compassion
			player:setScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren");
		end)
	end

	return pConversationScreen
end

function MirlaConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(WarrenScreenPlay.states.mirla.done, "warren")) then
		return convoTemplate:getScreen("mirla_done")
	elseif (CraetureObject(pPlayer):hasScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren")) then
		return convoTemplate:getScreen("mirla_get_teraud")
	end

	return convoTemplate:getScreen("mirla_start")
end

function MirlaConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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