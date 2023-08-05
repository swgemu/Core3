BartenderConversationHandler = conv_handler:new {}

function BartenderConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()

	print("Screen ID = " .. screenID .. " selected option: " .. selectedOption)

	if (screenID == "opt_rumor") then
		local hasRumors = readData(npcID .. ":BartenderPlayerRumors:")

		-- Chance to have no rumor
		if (getRandomNumber(100) < 50) then
			return convoTemplate:getScreen("query_buy")
		elseif (hasRumors == 1) then
			local playerName = readStringData(npcID .. ":BartenderRumorPlayer:")
			local rumorString = readStringData(npcID .. ":BartenderRumorMessage:")

			clonedConversation:setDialogTextStringId("@bartender:prose_rumor" .. getRandomNumber(1,4))
			clonedConversation:setDialogTextTT(playerName)
			clonedConversation:setDialogTextTO(rumorString)

			deleteData(npcID .. ":BartenderPlayerRumors:")
			deleteStringData(npcID .. ":BartenderRumorPlayer:")
			deleteStringData(npcID .. ":BartenderRumorMessage:")
		else
			clonedConversation:setDialogTextStringId("@bartender:monthly_fiction_" .. getRandomNumber(1, 9))
		end
	elseif (screenID == "opt_buy" or screenID == "opt_yes") then
		-- buy drink SUI here
		--[[
		stringFiles[9].addEntry("sui_prompt", "Please select the beverage you would like from the list.");
		stringFiles[9].addEntry("sui_title", "Bar Menu");

		stringFiles[9].addEntry("prose_buy_fail", "You were unable to purchase %TO. Perhaps you do not have enough credits?");
		stringFiles[9].addEntry("prose_buy_pass", "You successfully purchase a %TT for %DI credits.");
		stringFiles[9].addEntry("inv_full", "The bartender was unable to hand you your %TO. It is likely your inventory is full.");
		]]
	end

	return pConvScreen
end

function BartenderConversationHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local npcID = SceneObject(pNpc):getObjectID()

	local rumorBartender = readData(npcID .. ":BartenderRumorFlag:")

	if (rumorBartender == 1) then
		return convoTemplate:getScreen("bartender_rumor_start")
	end

	return convoTemplate:getScreen("bartender_start")
end
