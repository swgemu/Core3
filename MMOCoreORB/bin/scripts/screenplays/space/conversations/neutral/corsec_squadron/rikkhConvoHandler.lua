local QuestManager = require("managers.quest.quest_manager")

rikkhConvoHandler = conv_handler:new {}

function rikkhConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("no_jtl") -- Sorry, but you don't look like a pilot to me.
	end


	print("rikkhConvoHandler:getInitialScreen  -- called")


	-- Check if player has any pilot skills
	if (not SpaceHelpers:isPilot(pPlayer)) then
		return convoTemplate:getScreen("not_pilot") -- Everything is fine here. Nothing wrong at all.
	end




	-- Check if player is correct faction

	-- Check if player is ready for rikkh missions







	return convoTemplate:getScreen("no_jtl")
end

function rikkhConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	-- Set player as conversation target
	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	print("runScreenHandlers -- Screen ID: " .. screenID)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end








	return pClonedScreen
end
