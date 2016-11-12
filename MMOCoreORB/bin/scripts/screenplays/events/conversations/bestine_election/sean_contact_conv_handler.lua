local ObjectManager = require("managers.object.object_manager")

seanContactConvoHandler = conv_handler:new {
}

function seanContactConvoHandler:hasHistoryDisk(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff", true) ~= nil) then
				return true
			end
		end
	end

	return false
end

function seanContactConvoHandler:destroyHDisk(pPlayer)
	if (pPlayer ~= nil) then
		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if pInventory ~= nil then
				local hDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_history_disk.iff" , true)
				if (hDisk ~= nil) then
					SceneObject(hDisk):destroyObjectFromWorld()
					SceneObject(hDisk):destroyObjectFromDatabase()

					local playerID = CreatureObject(pPlayer):getObjectID()
					local wayID = readData(playerID .. ":bestine_election:contactWaypointID")
					PlayerObject(pPlayerObj):removeWaypoint(wayID, true)
					deleteData(playerID .. ":bestine_election:contactWaypointID")
					CreatureObject(pPlayer):removeScreenPlayState(16, "bestine_history_quest")
					CreatureObject(pPlayer):setScreenPlayState(32, "bestine_history_quest")
				end
			end
		end
	end
end

function seanContactConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if (screenID == "seanContact_itemDestroyed") then
		self:destroyHDisk(pPlayer)
	end

	return pConvScreen
end

function seanContactConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (not BestineElectionScreenPlay:isElectionEnabled()) then
		return convoTemplate:getScreen("sean_notinOffice")
	end

	if getQuestStatus("bestine_election:electionWinner") == "sean" then
		if self:hasHistoryDisk(pPlayer) then
			return convoTemplate:getScreen("sean_inOffice_hasItem")
		else
			return convoTemplate:getScreen("sean_inOffice_noItem")
		end
	end

	return convoTemplate:getScreen("sean_notinOffice")
end
