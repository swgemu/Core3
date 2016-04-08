local ObjectManager = require("managers.object.object_manager")

BestineElectionTerminalMenuComponent = {}

function BestineElectionTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return 0
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

	local questn_searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questn_searched"))
	local questp_searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questp_searched"))
	
	if questn_searched == 1 or questp_searched == 1 then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		return 0
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName,"_")
	
	
	if tblQuest[1] == "victor" then
		if (tblQuest[2] == "questn" and victorVisalisConvoHandler:victorNegQuest(pPlayer)) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", -1)
				if (pDisk ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
					writeScreenPlayData(pPlayer,"BestineElection", "questn_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
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
					CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
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
					CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
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
		if (tblQuest[2] == "questn" and victorVisalisConvoHandler:victorNegQuest(pPlayer)) then
			local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then
				local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", -1)
				if (pDisk ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
					writeScreenPlayData(pPlayer,"BestineElection", "questn_searched",1)
				else
					CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
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
					CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
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
					CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
				end
			end
		end
	end
	return 0
end


TourContainerComponent = {}

function TourContainerComponent:transferObject(pContainer, pObj, slot)
	if (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/sean_questp_mdisk.iff") or (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/sean_questp_ctestimony.iff") or
		(SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/sean_questp_htestimony.iff") or (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/victor_questp_jregistry.iff") or
		(SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/victor_questp_testimony.iff") or (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/victor_questp_receipt.iff")
	then spatialChat(pContainer, "@bestine:give_governor_item")
	end
	return 0
end

BestineElectionHistoryQuestMenuComponent = { }

function BestineElectionHistoryQuestMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pMenuResponse == nil) then
		return
	end
	if tonumber(readScreenPlayData(pPlayer, "BestineElection", "hquest_find")) == 1 then
		local menuResponse = LuaObjectMenuResponse(pMenuResponse)
		menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
	end
end

function BestineElectionHistoryQuestMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil  or selectedID ~= 20) then
		return 0
	end
	
	if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
		return 0
	end
	
	if (tonumber(readScreenPlayData(pPlayer,"BestineElection", "historyq_searched")) == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:history_disk_found_already")
		return 0
	else
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pDisk = giveItem(pInventory,"object/tangible/loot/quest/sean_history_disk.iff", -1)
			if (pDisk == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item:sean_history_disk.iff")
				return 0
			end
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:history_disk_found")
			writeScreenPlayData(pPlayer, "BestineElection", "historyq_searched",1)
		end
	end
	return 0
end
