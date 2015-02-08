local ObjectManager = require("managers.object.object_manager")

deathWatchTechnicianConvoHandler = {  }

function deathWatchTechnicianConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pConversationSession = player:getConversationSession()
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
	end)
end

function deathWatchTechnicianConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)

		if (player:hasScreenPlayState(2, "death_watch_bunker_technician_sidequest") == 1) then
			if (readData("dwb:ventsEnabled") == 1) then
				return convoTemplate:getScreen("quest_completed_gas_cleared")
			else
				return convoTemplate:getScreen("intro_prev_completed_new_escort")
			end
		elseif (player:hasScreenPlayState(1, "death_watch_bunker_technician_sidequest") == 1) then
			-- dwb:droidEscortStatus": 1 - escort in progress, 2 - escort failed
			if (readData("dwb:droidEscortStatus") == 1) then
				if (readData("dwb:droidEscortStarter") == player:getObjectID()) then
					return convoTemplate:getScreen("should_be_escorting")
				else
					return convoTemplate:getScreen("escort_in_progress")
				end
			elseif (readData("dwb:droidEscortStatus") == 2) then
				return convoTemplate:getScreen("escort_failed")
			end
		else
			if (readData("dwb:ventsEnabled") == 1) then
				return convoTemplate:getScreen("cant_talk_busy")
			else
				return convoTemplate:getScreen("intro")
			end
		end
	end)
end

function deathWatchTechnicianConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "release_the_droid" or screenID == "knew_could_count") then
			player:setScreenPlayState(1, "death_watch_bunker_technician_sidequest")
			writeData("dwb:droidEscortStatus", 1)
			writeData("dwb:droidEscortStarter", player:getObjectID())
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

		return conversationScreen
	end)
end