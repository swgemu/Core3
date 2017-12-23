local ObjectManager = require("managers.object.object_manager")

BestineElectionTerminalMenuComponent = {}

function BestineElectionTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElectionScreenPlay:getCurrentPhase() ~= 1) then
		return
	end

	if (not BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer)) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download") -- Download
end

function BestineElectionTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName, "_")
	local searched = 0

	if tblQuest[1] ~= "victor" then
		return 0
	end

	if tblQuest[2] == "questn" then
		searched = tonumber(readScreenPlayData(pPlayer, "BestineElection", "questn_term_searched"))
	elseif tblQuest[2] == "questp" then
		searched = tonumber(readScreenPlayData(pPlayer, "BestineElection", "questp_term_searched"))
	end

	if searched == 1 then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched") -- Access Denied: You have already downloaded data from this terminal.
		return 0
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil or SceneObject(pInventory):isContainerFullRecursive() then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full") -- Download Terminated: Inventory Full
		return 0
	end

	if (tblQuest[2] == "questn" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "victor")) then
		local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", -1) -- Business Terminal in Sean's office
		if (pDisk ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete") -- Download Complete
			writeScreenPlayData(pPlayer, "BestineElection", "questn_term_searched", 1)
		end
	elseif tblQuest[2] == "questp" and BestineElectionScreenPlay:joinedCampaign(pPlayer, "victor") then
		local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff", -1) -- Business Terminal in Victor's office
		if (pDisk ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete") -- Download Complete
			writeScreenPlayData(pPlayer,"BestineElection", "questp_term_searched", 1)
		end
	end

	return 0
end

BestineElectionDeskMenuComponent = {}

function BestineElectionDeskMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElectionScreenPlay:getCurrentPhase() ~= 1) then
		return 0
	end

	if (not BestineElectionScreenPlay:canSearch(pSceneObject, pPlayer)) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item") -- Search
end

function BestineElectionDeskMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	local strTerminalName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")
	local tblQuest = BestineElectionScreenPlay:parseString(strTerminalName, "_")
	local searched = 0

	if tblQuest[2] ~= "questn" then
		return 0
	end

	searched = tonumber(readScreenPlayData(pPlayer, "BestineElection", "questn_desk_searched"))

	if searched == 1 then
		CreatureObject(pPlayer):sendSystemMessage("@bestine:already_searched") -- You've already searched here.
		return 0
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil or SceneObject(pInventory):isContainerFullRecursive() then
		CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full") -- You find something but have no room in your inventory for it. Try again when you are carrying fewer things.
		return 0
	end

	if (tblQuest[1] == "sean" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "sean")) then
		local pItem = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", -1) -- Desk in Victor's office
		if (pItem ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receivemsg") -- You find a handheld viewscreen in the jumble of papers. It looks like it would contain valuable information.
			writeScreenPlayData(pPlayer, "BestineElection", "questn_desk_searched", 1)
		end
	elseif (tblQuest[1] == "victor" and BestineElectionScreenPlay:isOnNegativeQuest(pPlayer, "victor")) then
		local pItem = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_alog.iff", -1) -- Desk in Sean's office
		if (pItem ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receive1") -- The desk is neat. It's easy to find the accountant's log book. You take the item.
			writeScreenPlayData(pPlayer, "BestineElection", "questn_desk_searched", 1)
		end
	end

	return 0
end
