local ObjectManager = require("managers.object.object_manager")

lifeDayOraalarriConvoHandler = Object:new {}

function lifeDayOraalarriConvoHandler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, ghost)
		local playerID = player:getObjectID()
		if readScreenPlayData(pPlayer, "lifeDay", "complete") == "1" then
			return convoTemplate:getScreen("return_complete")
		elseif readData(playerID .. ":lifeDayState") == 1 or readData(playerID .. ":lifeDayState") == 2 then
			return convoTemplate:getScreen("greetings")
		elseif readData(playerID .. ":lifeDayState") == 3 then
			if ghost:getCharacterAgeInDays() >= 30  then
				return convoTemplate:getScreen("have_spoken")
			else
				return convoTemplate:getScreen("no_gift")
			end
		else
			return convoTemplate:getScreen("im_sorry")
		end
	end)
end

function lifeDayOraalarriConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)

	if screenID == "speak_to_others" then
		writeData(SceneObject(conversingPlayer):getObjectID() .. ":lifeDayState", 2)
	elseif screenID == "have_gifts" then
		if CreatureObject(conversingPlayer):getSpecies() == 4 then
			clonedConversation:addOption("@conversation/lifeday04b:s_afabf3ac", "gift_wookiee") -- What sort of gifts?
		else
			clonedConversation:addOption("@conversation/lifeday04b:s_afabf3ac", "gift_non_wookiee") -- What sort of gifts?
		end
	elseif screenID == "gift_non_wookiee" or screenID == "enjoy_other_gift" then
		lifeDayScreenplay:giveRandomGift(conversingPlayer)
	elseif screenID == "enjoy_robe" then
		lifeDayScreenplay:giveRobe(conversingPlayer)
	elseif screenID == "no_gift" then
		lifeDayScreenplay:noGift(conversingPlayer)
	end
	return conversationScreen
end

function lifeDayOraalarriConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
