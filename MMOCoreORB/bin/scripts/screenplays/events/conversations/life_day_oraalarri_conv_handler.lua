local ObjectManager = require("managers.object.object_manager")

lifeDayOraalarriConvoHandler = conv_handler:new {}

function lifeDayOraalarriConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local playerID = CreatureObject(pPlayer):getObjectID()
	if readScreenPlayData(pPlayer, readStringSharedMemory("lifeDayScreenplayName"), "complete") == "1" then
		return convoTemplate:getScreen("return_complete")
	elseif readData(playerID .. ":lifeDayState") == 1 or readData(playerID .. ":lifeDayState") == 2 then
		return convoTemplate:getScreen("greetings")
	elseif readData(playerID .. ":lifeDayState") == 3 then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if pGhost ~= nil and PlayerObject(pGhost):getCharacterAgeInDays() >= 30  then
			return convoTemplate:getScreen("have_spoken")
		else
			return convoTemplate:getScreen("no_gift")
		end
	else
		return convoTemplate:getScreen("im_sorry")
	end
end

function lifeDayOraalarriConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if screenID == "speak_to_others" then
		writeData(SceneObject(pPlayer):getObjectID() .. ":lifeDayState", 2)
	elseif screenID == "have_gifts" then
		if CreatureObject(pPlayer):getSpecies() == 4 then
			clonedConversation:addOption("@conversation/lifeday04b:s_afabf3ac", "gift_wookiee") -- What sort of gifts?
		else
			clonedConversation:addOption("@conversation/lifeday04b:s_afabf3ac", "gift_non_wookiee") -- What sort of gifts?
		end
	elseif screenID == "gift_non_wookiee" or screenID == "enjoy_other_gift" then
		lifeDayScreenplay:giveRandomGift(pPlayer)
	elseif screenID == "enjoy_robe" then
		lifeDayScreenplay:giveRobe(pPlayer)
	elseif screenID == "no_gift" then
		lifeDayScreenplay:noGift(pPlayer)
	end
	return pConvScreen
end
