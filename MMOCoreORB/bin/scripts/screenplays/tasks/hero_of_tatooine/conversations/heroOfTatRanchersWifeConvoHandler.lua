local ObjectManager = require("managers.object.object_manager")

heroOfTatRanchersWifeConvoHandler = conv_handler:new {}

function heroOfTatRanchersWifeConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerID = SceneObject(pPlayer):getObjectID()

	local inProgressID = readData("hero_of_tat:ranch_player_id")
	if (inProgressID ~= 0 and inProgressID ~= playerID) then
		return convoTemplate:getScreen("intro_otherinprogress")
	elseif (not CreatureObject(pPlayer):hasScreenPlayState(1,"hero_of_tatooine_honor") or CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine_honor")) then
		return convoTemplate:getScreen("intro_noquest")
	elseif (not CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine_honor") and CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine_honor") and readData(playerID .. ":hero_of_tat_honor:accepted") == 1) then
		if (readData(playerID .. ":hero_of_tat_honor:distracting_wife") == 1) then
			return convoTemplate:getScreen("intro_distract")
		else
			return convoTemplate:getScreen("intro_hasquest")
		end
	elseif (readData(playerID .. ":hero_of_tat_honor:spoke_to_wife") == 1) then
		return convoTemplate:getScreen("intro_leftprior")
	else
		return convoTemplate:getScreen("intro")
	end
end

function heroOfTatRanchersWifeConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "leave_now") then
		writeData(CreatureObject(pPlayer):getObjectID() .. ":hero_of_tat_honor:spoke_to_wife", 1)
	elseif (screenID == "thanks_intercom") then
		local inProgressID = readData("hero_of_tat:ranch_player_id")
		if (inProgressID ~= 0 and inProgressID ~= SceneObject(pPlayer):getObjectID()) then
			clonedConversation:setDialogTextStringId("@conversation/quest_hero_of_tatooine_wife:s_c74cdffb")
		else
			HeroOfTatooineScreenPlay:doHonorStart(pPlayer)
		end
	elseif (screenID == "so_nice_ahh") then
		HeroOfTatooineScreenPlay:doHonorFail(pPlayer)
	elseif (screenID == "cant_believe_this") then
		HeroOfTatooineScreenPlay:doHonorSuccess(pPlayer)
		HeroOfTatooineScreenPlay:doSuccessHonorPhase(pPlayer)
	end

	return pConvScreen
end
