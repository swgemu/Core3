local ObjectManager = require("managers.object.object_manager")

BestineElectionTerminalMenuComponent = {}

function BestineElectionTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end

	if BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer) then
		local menuResponse = LuaObjectMenuResponse(pMenuResponse)
		menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
	end
end

function BestineElectionTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName,"_")
	local searched = 0

	if tblQuest[2] == "questn" then
		searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questn_searched"))
	elseif tblQuest[2] == "questp" then
		searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questp_searched"))
	end

	if searched == 1 then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		return 0
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName,"_")


	if tblQuest[1] == "victor" then
		if (tblQuest[2] == "questn" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor")) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", -1)
				if (pDisk ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
					writeScreenPlayData(pPlayer,"BestineElection", "questn_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
				end
			end
		elseif tblQuest[2] == "questp" then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff" , -1)
				if (pDisk ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
					writeScreenPlayData(pPlayer,"BestineElection", "questp_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
				end
			end
		end
	elseif tblQuest[1] == "sean" then
		if (tblQuest[2] == "questn" and seanTrenwellConvoHandler:seanNegQuest(pPlayer)) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", -1)
				if (pDisk ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receivemsg")
					writeScreenPlayData(pPlayer,"BestineElection", "questn_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
				end
			end
		end
	end
	return 0
end

BestineElectionDeskMenuComponent = {}

function BestineElectionDeskMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return 0
	end

	if BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer) then
		local menuResponse = LuaObjectMenuResponse(pMenuResponse)
		menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	end
end

function BestineElectionDeskMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)

	local questn_searched = tonumber(readScreenPlayData(pPlayer,"BestineElection", "questn_searched"))
	local questp_searched = tonumber(readScreenPlayData(pPlayer,"BestineElection", "questp_searched"))

	if (questn_searched == 1 or questp_searched == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		return 0
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName,"_")
	if tblQuest[1] == "victor" then
		if (tblQuest[2] == "questn" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor")) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", -1)
				if (pDisk ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
					writeScreenPlayData(pPlayer,"BestineElection", "questn_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
				end
			end
		elseif tblQuest[2] == "questp" then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff" , -1)
				if (pDisk ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
					writeScreenPlayData(pPlayer,"BestineElection", "questp_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
				end
			end
		end
	elseif tblQuest[1] == "sean" then
		if (tblQuest[2] == "questn" and seanTrenwellConvoHandler:seanNegQuest(pPlayer)) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pItem = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_alog.iff", -1)
				if (pItem ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receive1")
					writeScreenPlayData(pPlayer,"BestineElection", "questn_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
				end
			end
		end
	end
	return 0
end


BestineElectionHistoryQuestMenuComponent = { }

function BestineElectionHistoryQuestMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pMenuResponse == nil) then
		return
	end
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if player:hasScreenPlayState(8, "bestine_history_quest") then
			local menuResponse = LuaObjectMenuResponse(pMenuResponse)
			menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
		end
	end)
end

function BestineElectionHistoryQuestMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil  or selectedID ~= 20) then
		return 0
	end
	return ObjectManager.withCreatureObject(pPlayer, function(player)

			if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				player:sendSystemMessage("@city/bestine/terminal_items:inv_full")
				return 0
			end

			if player:hasScreenPlayState(16, "bestine_history_quest") then
				player:sendSystemMessage("@city/bestine/terminal_items:history_disk_found_already")
				return 0
			else
				local pInventory = player:getSlottedObject("inventory")
				if (pInventory ~= nil) then
					local pDisk = giveItem(pInventory,"object/tangible/loot/quest/sean_history_disk.iff", -1)
					if (pDisk == nil) then
						player:sendSystemMessage("Error: Unable to generate item:sean_history_disk.iff")
						return 0
					end
					player:sendSystemMessage("@city/bestine/terminal_items:history_disk_found")
					player:setScreenPlayState(16, "bestine_history_quest")
				end
			end
			return 0
	end)
end
