local ObjectManager = require("managers.object.object_manager")

deathWatchTechnicianConvoHandler = conv_handler:new {}

function deathWatchTechnicianConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_bunker_technician_sidequest")) then
		if (readData("dwb:ventsEnabled") == 1) then
			return convoTemplate:getScreen("quest_completed_gas_cleared")
		else
			return convoTemplate:getScreen("intro_prev_completed_new_escort")
		end
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker_technician_sidequest")) then
		-- dwb:droidEscortStatus": 1 - escort in progress, 2 - escort failed
		if (readData("dwb:droidEscortStatus") == 1) then
			if (readData("dwb:droidEscortStarter") == CreatureObject(pPlayer):getObjectID()) then
				return convoTemplate:getScreen("should_be_escorting")
			else
				return convoTemplate:getScreen("escort_in_progress")
			end
		elseif (readData("dwb:droidEscortStatus") == 2) then
			return convoTemplate:getScreen("escort_failed")
		else
			return convoTemplate:getScreen("intro")
		end
	else
		if (readData("dwb:ventsEnabled") == 1) then
			return convoTemplate:getScreen("cant_talk_busy")
		else
			return convoTemplate:getScreen("intro")
		end
	end
end

function deathWatchTechnicianConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "release_the_droid" or screenID == "knew_could_count") then
		CreatureObject(pPlayer):setScreenPlayState(1, "death_watch_bunker_technician_sidequest")
		writeData("dwb:droidEscortStatus", 1)
		writeData("dwb:droidEscortStarter", CreatureObject(pPlayer):getObjectID())
		DeathWatchBunkerScreenPlay:doVentDroidStep(nil)
	elseif (screenID == "escort_failed") then
		if (readData("dwb:ventDroidAvailable") == 1) then
			clonedConversation:addOption("@conversation/death_watch_technician:s_7d875e15", "release_the_droid")
		else
			clonedConversation:addOption("@conversation/death_watch_technician:s_7d875e15", "building_new_droid")
		end
		clonedConversation:addOption("@conversation/death_watch_technician:s_3bc0260c", "not_first_person")
	elseif (screenID == "intro_prev_completed_new_escort") then
		if (readData("dwb:ventDroidAvailable") == 1) then
			clonedConversation:addOption("@conversation/death_watch_technician:s_373533eb", "knew_could_count")
		else
			clonedConversation:addOption("@conversation/death_watch_technician:s_373533eb", "building_new_droid")
		end
		clonedConversation:addOption("@conversation/death_watch_technician:s_cbf95857", "thanks_anyways")
	end

	return pConvScreen
end
