local ObjectManager = require("managers.object.object_manager")
local QuestManager = require("managers.quest.quest_manager")

villageFsReflex1PrisonerConvoHandler = conv_handler:new {}

function villageFsReflex1PrisonerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local playerID = SceneObject(pPlayer):getObjectID()
	local npcID = SceneObject(pNpc):getObjectID()

	if (readData(npcID .. ":ownerID") ~= playerID) then
		return convoTemplate:getScreen("intro_wrongplayer")
	elseif (readData(npcID .. ":safe") == 1) then
		return convoTemplate:getScreen("intro_rescued")
	elseif (CreatureObject(pNpc):isInCombat()) then
		return convoTemplate:getScreen("intro_incombat")
	elseif (readData(playerID .. ":failedWhipPhase1") == 1) then
		return convoTemplate:getScreen("intro_failedquest")
	elseif (readData(playerID .. ":escortInProgress") == 1) then
		return convoTemplate:getScreen("intro_inprogress")
	end
	return convoTemplate:getScreen("intro")
end

function villageFsReflex1PrisonerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "intro") then
		QuestManager.completeQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_02)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_03)
		QuestManager.activateQuest(pPlayer, QuestManager.quests.FS_REFLEX_RESCUE_QUEST_04)
		FsReflex1Theater:removeTheaterWaypoint(pPlayer)
		FsReflex1Escort:start(pPlayer, pNpc)
	elseif (screenID == "intro_inprogress") then
		FsReflex1Escort:setEscortFollow(pPlayer, pNpc)
	end

	return pConvScreen
end
