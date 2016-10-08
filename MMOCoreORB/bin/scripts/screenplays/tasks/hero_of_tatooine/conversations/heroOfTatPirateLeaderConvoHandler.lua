local ObjectManager = require("managers.object.object_manager")

heroOfTatPirateLeaderConvoHandler = conv_handler:new {}

function heroOfTatPirateLeaderConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (screenID == "made_me_happy" or screenID == "be_quick") then
		HeroOfTatooineScreenPlay:giveHonorWaypoint(pPlayer)
		CreatureObject(pPlayer):setScreenPlayState(1, "hero_of_tatooine_honor")
		HeroOfTatooineScreenPlay:doGiverDespawn(pNpc)
	elseif (screenID == "lets_get_em" or screenID == "is_that_so" or screenID == "teach_a_lesson") then
		HeroOfTatooineScreenPlay:spawnAggroLeader(pNpc, pPlayer, screenID)
	end

	return pConvScreen
end
