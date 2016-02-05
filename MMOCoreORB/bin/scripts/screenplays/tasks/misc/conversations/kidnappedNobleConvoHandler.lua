local ObjectManager = require("managers.object.object_manager")

kidnappedNobleConvoHandler = {  }

function kidnappedNobleConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	return convoTemplate:getScreen("init")
end

function kidnappedNobleConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local conversationScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(conversationScreen)
	if (screenID == "init") then
		CreatureObject(conversingNPC):doAnimation("angry")
	elseif (screenID == "of_course") then
		CreatureObject(conversingNPC):doAnimation("nod_head_multiple")
	elseif (screenID == "my_hero") then
		CreatureObject(conversingNPC):doAnimation("celebrate")
		local objectName = AiAgent(conversingNPC):getCreatureTemplateName()

		if (readScreenPlayData(conversingPlayer, "kidnappedNoble:" .. objectName, "completed") == "") then
			CreatureObject(conversingPlayer):awardExperience("combat_general", 250, true)
			writeScreenPlayData(conversingPlayer, "kidnappedNoble:" .. objectName, "completed", 1)
		end

		createEvent(2000, "kidnappedNobleConvoHandler", "doRunAway", conversingNPC, "")
	end

	return conversationScreen
end

function kidnappedNobleConvoHandler:doRunAway(pCreature)
	if (pCreature == nil or not CreatureObject(pCreature):isAiAgent()) then
		return
	end

	local xPos = SceneObject(pCreature):getWorldPositionX() + 60
	local yPos = SceneObject(pCreature):getWorldPositionY() + 60
	local zPos = getTerrainHeight(pCreature, xPos, yPos)

	AiAgent(pCreature):setAiTemplate("manualescort") -- Don't move unless patrol point is added to list
	AiAgent(pCreature):setFollowState(4) -- Patrolling
	AiAgent(pCreature):stopWaiting()
	AiAgent(pCreature):setWait(0)
	AiAgent(pCreature):setNextPosition(xPos, zPos, yPos, 0)
	AiAgent(pCreature):executeBehavior()

	createEvent(30000, "kidnappedNobleConvoHandler", "destroyNoble", pCreature, "")
end

function kidnappedNobleConvoHandler:destroyNoble(pCreature)
	if (pCreature == nil or not CreatureObject(pCreature):isAiAgent()) then
		return
	end

	AiAgent(pCreature):doDespawn()
end

function kidnappedNobleConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()
	local pLastConversationScreen = nil
	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)
		return conversationTemplate:getScreen(optionLink)
	end
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
