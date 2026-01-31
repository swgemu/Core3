vrakConvoHandler = conv_handler:new {}

function vrakConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return nil
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- Get the viopaSmuggler flag value
	local viopaSmuggler = getQuestStatus(playerID .. "HavocSquadron:viopaSmuggler")

	if (viopaSmuggler == nil) then
		viopaSmuggler = 0
	else
		viopaSmuggler = tonumber(viopaSmuggler) or 0
	end

	-- First meeting: Player has been sent by Viopa to meet Vrak (viopaSmuggler == 1)
	if (viopaSmuggler == 1) then
		return convoTemplate:getScreen("are_you_the_pilot")

	-- Confrontation: Player returns to confront Vrak about betrayal (viopaSmuggler == 3)
	elseif (viopaSmuggler == 3) then
		return convoTemplate:getScreen("what_are_you_doing_here")
	end

	-- Default: Not the right player or wrong state
	return convoTemplate:getScreen("not_right_player")
end

function vrakConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	local playerID = CreatureObject(pPlayer):getObjectID()

	-- First meeting complete: Player finished talking to Vrak
	-- Set viopaSmuggler = 2 so Viopa knows they met
	if (screenID == "thank_you_vrak" or screenID == "calm_down_goodbye") then
		setQuestStatus(playerID .. "HavocSquadron:viopaSmuggler", 2)

	-- Confrontation complete: Player got the info about Kud'ar Mub'at
	-- Set viopaSmuggler = 4 so Viopa knows they confronted Vrak
	elseif (screenID == "betrayal_explanation") then
		setQuestStatus(playerID .. "HavocSquadron:viopaSmuggler", 4)
	end

	return pClonedScreen
end
