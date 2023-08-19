BartenderConversationHandler = conv_handler:new {}

function BartenderConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()

	if (AiAgent(pNpc):getPatrolPointsSize() == 0) then
		createEvent(20 * 1000, "BartendersScreenPlay", "assignPatrolPoint", pNpc, "")
	end

	if (screenID == "opt_rumor") then
		local hasPlayerRumor = readData(npcID .. ":BartenderPlayerRumors:")

		if (hasPlayerRumor == 1) then
			local playerName = readStringData(npcID .. ":BartenderRumorPlayer:")
			local rumorString = readStringData(npcID .. ":BartenderRumorMessage:")

			local rumorMessage = LuaStringIdChatParameter("@bartender:prose_rumor" .. getRandomNumber(1,4))
			rumorMessage:setTT(playerName)
			rumorMessage:setTO(rumorString)

			-- Send the rumor in spatial
			spatialChat(pNpc, rumorMessage:_getObject())

			deleteData(npcID .. ":BartenderPlayerRumors:")
			deleteStringData(npcID .. ":BartenderRumorPlayer:")
			deleteStringData(npcID .. ":BartenderRumorMessage:")
		else
			local rumorMessage = LuaStringIdChatParameter("@bartender:no_rumor")
			-- Send the rumor in spatial
			spatialChat(pNpc, rumorMessage:_getObject())
		end

		return convoTemplate:getScreen("query_buy")
	elseif (screenID == "talk_to_me") then
		clonedConversation:setDialogTextStringId("@bartender:monthly_fiction_" .. getRandomNumber(1, 9))
	elseif (screenID == "opt_buy" or screenID == "opt_yes") then
		-- Purchase Drink SUI
		local zoneName = CreatureObject(pPlayer):getZoneName()
		local drinksTable = BartendersScreenPlay.drinkOptions[zoneName]

		local pSui = SuiListBox.new("BartendersScreenPlay", "purchaseDrinkCallback")
		pSui.setTitle("@bartender:sui_title")
		pSui.setPrompt("@bartender:sui_prompt")

		for i = 1, #drinksTable, 1 do
			local drinkName = drinksTable[i][1]
			local drinkCost = drinksTable[i][2]
			local messageString = "@food_name:" .. drinkName

			pSui.add("[" .. drinkCost .. "] " .. getStringId(messageString), "")
		end

		pSui.sendTo(pPlayer)
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
