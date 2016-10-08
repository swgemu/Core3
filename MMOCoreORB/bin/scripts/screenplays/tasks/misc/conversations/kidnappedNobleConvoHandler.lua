local ObjectManager = require("managers.object.object_manager")

kidnappedNobleConvoHandler = conv_handler:new {}

function kidnappedNobleConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "init") then
		CreatureObject(pNpc):doAnimation("angry")
	elseif (screenID == "of_course") then
		CreatureObject(pNpc):doAnimation("nod_head_multiple")
	elseif (screenID == "my_hero") then
		CreatureObject(pNpc):doAnimation("celebrate")
		local objectName = AiAgent(pNpc):getCreatureTemplateName()

		if (readScreenPlayData(pPlayer, "kidnappedNoble:" .. objectName, "completed") == "") then
			CreatureObject(pPlayer):awardExperience("combat_general", 250, true)
			writeScreenPlayData(pPlayer, "kidnappedNoble:" .. objectName, "completed", 1)
		end

		createEvent(2000, "kidnappedNobleConvoHandler", "doRunAway", pNpc, "")
	end

	return pConvScreen
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
