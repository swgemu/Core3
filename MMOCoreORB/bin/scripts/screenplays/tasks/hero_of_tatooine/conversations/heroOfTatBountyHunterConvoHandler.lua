local ObjectManager = require("managers.object.object_manager")

heroOfTatBountyHunterConvoHandler = conv_handler:new {}

-- 1 - Started farmer quest, 2 - Completed farmer quest

function heroOfTatBountyHunterConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local npcId = CreatureObject(pNpc):getObjectID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine_intellect")) then
		return convoTemplate:getScreen("intro_completed")
	elseif (readData(CreatureObject(pPlayer):getObjectID() .. ":hero_of_tat:failedIntellect") == npcId) then
		return convoTemplate:getScreen("already_failed")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine_intellect")) then
		return convoTemplate:getScreen("intro_hasquest")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine")) then
		return convoTemplate:getScreen("intro")
	else
		return convoTemplate:getScreen("intro_no_hermit")
	end
end

function heroOfTatBountyHunterConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "give_it_a_shot") then
		CreatureObject(pPlayer):setScreenPlayState(1, "hero_of_tatooine_intellect")
	elseif (screenID == "thats_great") then
		HeroOfTatooineScreenPlay:sendImplicateSui(pPlayer, pNpc)
	end

	return pConvScreen
end
