local ObjectManager = require("managers.object.object_manager")

BestineEvidenceMenuComponent = {}

function BestineEvidenceMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pPlayer == nil or pSceneObject == nil or BestineElection:getCurrentPhase() ~= BestineElection.ELECTION_PHASE) then
		return
	end

	local objectName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")

	if (not self:canSearchObject(pPlayer, objectName)) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	if (objectName == "victor_questp_jregistry" or objectName == "sean_questn_tdisk") then
		menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download") -- Download
	elseif (objectName == "victor_questn_journal" or objectName == "sean_questn_alog") then
		menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	end
end

function BestineEvidenceMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return 0
	end

	local objectName = readStringData(SceneObject(pSceneObject):getObjectID() .. ":name")

	if (not self:canSearchObject(pPlayer, objectName)) then
		return 0
	end

	if (BestineElection:hasSearchedObject(pPlayer, objectName)) then
		if (objectName == "victor_questp_jregistry" or objectName == "sean_questn_tdisk") then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		elseif (objectName == "victor_questn_journal" or objectName == "sean_questn_alog") then
			CreatureObject(pPlayer):sendSystemMessage("@bestine:already_searched")
		end

		return 0
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil or SceneObject(pInventory):isContainerFullRecursive()) then
		if (objectName == "victor_questp_jregistry" or objectName == "sean_questn_tdisk") then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
		elseif (objectName == "victor_questn_journal" or objectName == "sean_questn_alog") then
			CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
		end

		return 0
	end

	local pDisk = giveItem(pInventory, "object/tangible/loot/quest/" .. objectName .. ".iff", -1)

	if (pDisk == nil) then
		if (objectName == "victor_questp_jregistry" or objectName == "sean_questn_tdisk") then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
		elseif (objectName == "victor_questn_journal" or objectName == "sean_questn_alog") then
			CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
		end

		return 0
	end

	if (objectName == "victor_questp_jregistry" or objectName == "sean_questn_tdisk") then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
	elseif (objectName == "victor_questn_journal" or objectName == "sean_questn_alog") then
		CreatureObject(pPlayer):sendSystemMessage("@bestine:default_receive_msg")
	end

	BestineElection:setSearchedObject(pPlayer, objectName)

	return 0
end

function BestineEvidenceMenuComponent:canSearchObject(pPlayer, objectName)
	if (objectName == "victor_questp_jregistry") then
		return BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:hasJoinedCampaign(pPlayer, BestineElection.VICTOR)
	elseif (objectName == "victor_questn_journal") then
		return BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:getQuestStep(pPlayer, BestineElection.SEAN, BestineElection.SEAN_RIVAL_QUEST) == BestineElection.SEAN_RIVAL_QUEST_ACCEPTED
	elseif (objectName == "sean_questn_tdisk") then
		return BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_QUEST) == BestineElection.VICTOR_RIVAL_QUEST_ACCEPTED
	elseif (objectName == "sean_questn_alog") then
		return BestineElection:getPlayerVote(pPlayer) == BestineElection.NONE and BestineElection:getQuestStep(pPlayer, BestineElection.VICTOR, BestineElection.VICTOR_RIVAL_QUEST) == BestineElection.VICTOR_RIVAL_QUEST_ACCEPTED
	end

	return false
end
