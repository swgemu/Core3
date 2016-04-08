local ObjectManager = require("managers.object.object_manager")

BestineElectionTerminalMenuComponent = {}

function BestineElectionTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	if (not BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer)) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
end

function BestineElectionTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName,"_")
	local searched = 0


	if tblQuest[2] == "questn" then
		searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questn_term_searched"))
	elseif tblQuest[2] == "questp" then
		searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questp_term_searched"))
	end

	if searched == 1 then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		return 0
	end

	if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
		return 0
	end

	if (tblQuest[2] == "questn" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor")) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", -1) --Business Terminal in sean's office
			if (pDisk ~= nil) then
				CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
				writeScreenPlayData(pPlayer,"BestineElection", "questn_term_searched",1)
			end
		end
	elseif tblQuest[2] == "questp" and BestineElectionScreenPlay:joinedCampaign(pPlayer, "Victor") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff" , -1) --	Business Terminal in Victor's office
			if (pDisk ~= nil) then
				CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
				writeScreenPlayData(pPlayer,"BestineElection", "questp_term_searched",1)
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
	if (not BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer)) then
		return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
end

function BestineElectionDeskMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName,"_")
	local searched = 0

	if tblQuest[2] == "questn" then
		searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questn_desk_searched"))
	elseif tblQuest[2] == "questp" then
		searched = tonumber(readScreenPlayData(pPlayer,"BestineElection","questp_desk_searched"))
	end
	if searched == 1 then
		CreatureObject(pPlayer):sendSystemMessage("@bestine:already_searched")
		return 0
	end

	if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
		CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
		return 0
	end


	if (tblQuest[2] == "questn" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Sean")) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pItem = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", -1) --	Desk in Victor's office
			if (pItem ~= nil) then
				CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receivemsg")
				writeScreenPlayData(pPlayer,"BestineElection", "questp_desk_searched",1)
			end
		end
	end

	if (tblQuest[2] == "questn" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "Victor")) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local pItem = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_alog.iff", -1) --Desk in sean's office
			if (pItem ~= nil) then
				CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receive1")
				writeScreenPlayData(pPlayer,"BestineElection", "questp_desk_searched",1)
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
