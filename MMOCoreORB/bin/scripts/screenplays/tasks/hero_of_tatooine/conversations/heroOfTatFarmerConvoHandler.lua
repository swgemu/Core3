local ObjectManager = require("managers.object.object_manager")

heroOfTatFarmerConvoHandler = conv_handler:new {}

-- 1 - Started farmer quest, 2 - Completed farmer quest

function heroOfTatFarmerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine_altruism")) then
		return convoTemplate:getScreen("intro_completed")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine_altruism")) then
		return convoTemplate:getScreen("intro_has_quest")
	elseif (readData(CreatureObject(pNpc):getObjectID() .. ":gaveQuest") == 1) then
		return convoTemplate:getScreen("intro_someone_else_started")
	else
		return convoTemplate:getScreen("intro")
	end
end

function heroOfTatFarmerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "in_your_debt") then
		CreatureObject(pPlayer):sendSystemMessage("@quest/hero_of_tatooine/system_messages:altruism_quest_fail")
		writeData(CreatureObject(pNpc):getObjectID() .. ":gaveQuest", 1)
		CreatureObject(pPlayer):subtractCashCredits(10000)
		HeroOfTatooineScreenPlay:doGiverDespawn(pNpc)
	elseif (screenID == "sincerest_gratitude") then
		HeroOfTatooineScreenPlay:giveAltruismWaypoint(pPlayer)
		writeData(CreatureObject(pNpc):getObjectID() .. ":gaveQuest", 1)
		CreatureObject(pPlayer):setScreenPlayState(1, "hero_of_tatooine_altruism")
		HeroOfTatooineScreenPlay:doGiverDespawn(pNpc)
	elseif (screenID == "here_is_loc_again") then
		HeroOfTatooineScreenPlay:giveAltruismWaypoint(pPlayer)
	elseif (screenID == "a_lot_of_money") then
		if(CreatureObject(pPlayer):getCashCredits() >= 10000) then
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_5cdaed70", "in_your_debt")
		else
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_2e1d6626", "ill_go_myself")
		end
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_d5adc7c6", "very_dangerous")
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_2fdb8fbd", "ill_go_myself")
	elseif (screenID == "thanks_for_offering") then
		CreatureObject(pPlayer):removeScreenPlayState(1, "hero_of_tatooine_altruism")
	elseif (screenID == "intro") then
		if (CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine")) then
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_9e0bb613", "family_is_gone")
			clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_ca776e30", "moisture_farmer")
		end
		clonedConversation:addOption("@conversation/quest_hero_of_tatooine_farmer:s_b658a801", "ill_go_myself")
	end

	return pConvScreen
end
