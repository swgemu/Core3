herald_tatooine2_conv_handler = MultiDestHeraldConvoHandler:new {
	themePark = heraldScreenPlay
}

function herald_tatooine2_conv_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedScreen = LuaConversationScreen(pConvScreen)

	if screenID == "loc1" then
		self:handleScreenLoc(pPlayer, pNpc, 1)
	elseif screenID == "loc2" then
		self:handleScreenLoc(pPlayer, pNpc, 2)
	elseif screenID == "loc3" then
		self:handleScreenLoc(pPlayer, pNpc, 3)
	elseif screenID == "loc4" then
		self:handleScreenLoc(pPlayer, pNpc, 4)
	elseif screenID == "sixty_credits_please" then
		if CreatureObject(pPlayer):getCashCredits() < 60 then
			clonedScreen:addOption("@conversation/heraldtatooine2:s_c3dbbcab", "no_money") -- Fine, here.
		else
			clonedScreen:addOption("@conversation/heraldtatooine2:s_c3dbbcab", "loc1") -- Fine, here.
		end
		clonedScreen:addOption("@conversation/heraldtatooine2:s_30c59b36", "sad_story") -- I don't have the money.
	elseif screenID == "fifty_credits_please" then
		if CreatureObject(pPlayer):getCashCredits() < 50 then
			clonedScreen:addOption("@conversation/heraldtatooine2:s_81a382e3", "jip_me") -- Here you are.
		else
			clonedScreen:addOption("@conversation/heraldtatooine2:s_81a382e3", "loc2") -- Here you are.
		end
		clonedScreen:addOption("@conversation/heraldtatooine2:s_4440ce87", "go_away") -- I changed my mind.
	elseif screenID == "be_thirty_credits" then
		if CreatureObject(pPlayer):getCashCredits() < 30 then
			clonedScreen:addOption("@conversation/heraldtatooine2:s_d9903b42", "dont_have_money") -- Yes, I do. Here you are.
		else
			clonedScreen:addOption("@conversation/heraldtatooine2:s_d9903b42", "loc3") -- Yes, I do. Here you are.
		end
		clonedScreen:addOption("@conversation/heraldtatooine2:s_fb859e03", "bury_you") -- Actually, I don't. Bye!
	elseif screenID == "thatll_be_thirty" then
		if CreatureObject(pPlayer):getCashCredits() < 30 then
			clonedScreen:addOption("@conversation/heraldtatooine2:s_177f6371", "cheapskate") -- I guess. Here.
		else
			clonedScreen:addOption("@conversation/heraldtatooine2:s_177f6371", "loc4") -- I guess. Here.
		end
		clonedScreen:addOption("@conversation/heraldtatooine2:s_63855d3f", "not_surprised") -- Oh, look at that. I don't have the money.
	end

	return pConvScreen
end
