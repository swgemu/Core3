local ObjectManager = require("managers.object.object_manager")

heroOfTatIntellectLiarConvoHandler = conv_handler:new {}

function heroOfTatIntellectLiarConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (CreatureObject(pPlayer):hasScreenPlayState(1, "hero_of_tatooine_intellect") and not CreatureObject(pPlayer):hasScreenPlayState(2, "hero_of_tatooine_intellect")) then
		return convoTemplate:getScreen("init")
	else
		return convoTemplate:getScreen("init_noquest")
	end
end

function heroOfTatIntellectLiarConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "init" or screenID == "init_noquest") then
		clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:greeting_" .. getRandomNumber(11))
	elseif (screenID == "equipment") then
		clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:equipment_" .. getRandomNumber(11))
	elseif (screenID == "smugglers") then
		local liarId = readData(SceneObject(pNpc):getObjectID() .. ":liarId")

		if (liarId == 0) then
			CreatureObject(pPlayer):sendSystemMessage("Unable to find Mark of Intellect smuggler data. Please file a bug report.")
			return pConvScreen
		end

		liarId = liarId - 1

		clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:others_" .. liarId .. "_" .. getRandomNumber(2))
		if (liarId == 1) then
			clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(5))
		elseif (liarId == 2) then
			clonedConversation:setDialogTextTT(HeroOfTatooineScreenPlay:getIntellectLiarName(1))
			clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(3))
		elseif (liarId == 3) then
			clonedConversation:setDialogTextTT(HeroOfTatooineScreenPlay:getIntellectLiarName(1))
			clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(2))
		elseif (liarId == 4) then
			clonedConversation:setDialogTextTT(HeroOfTatooineScreenPlay:getIntellectLiarName(3))
			clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(1))
			clonedConversation:setDialogTextTU(HeroOfTatooineScreenPlay:getIntellectLiarName(2))
		elseif (liarId == 5) then
			clonedConversation:setDialogTextTO(HeroOfTatooineScreenPlay:getIntellectLiarName(4))
		end

	elseif (screenID == "bye") then
		clonedConversation:setDialogTextStringId("@quest/hero_of_tatooine/intellect_liar:bye_" .. getRandomNumber(11))
	end

	return pConvScreen
end
