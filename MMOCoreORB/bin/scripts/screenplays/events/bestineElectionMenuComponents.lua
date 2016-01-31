local ObjectManager = require("managers.object.object_manager")

BestineElectionSeanTerminalMenuComponent = { }

function BestineElectionSeanTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) then
		return
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorNegativeQuests"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
	print(pSceneObject, pMenuResponse, pPlayer)
end

function BestineElectionSeanTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	print(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorNegativeQuests"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return
	end

	if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff" , true) ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		return
	end

	local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", -1)
	if (pDisk == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item:sean_questn_tdisk.iff")
		return 0
	end
	CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receive1")
	return
end

BestineElectionVictorTerminalMenuComponent = { }

function BestineElectionVictorTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) then
		return
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorCampaign"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
	print(pSceneObject, pMenuResponse, pPlayer)
end

function BestineElectionVictorTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	print(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorCampaign"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if pInventory == nil then
		return
	end
	if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff" , true) ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		return
	end
	
	local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff" , -1)
	if (pDisk == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item:victor_questp_jregistry.iff")
		return 0
	end
	CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
	return
end



BestineElectionSeanDeskMenuComponent = { }

function BestineElectionSeanDeskMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) then
		return
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorNegativeQuests"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	print(pSceneObject, pMenuResponse, pPlayer)
end

function BestineElectionSeanDeskMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	print(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()

	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:VictorNegativeQuests"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory == nil) then
		return
	end

	local pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_alog.iff", -1)
	if (pDisk == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item:sean_questn_alog.iff")
		return 0
	end
	CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receive1")
	return
end

BestineElectionSeanDesk2MenuComponent = { }

function BestineElectionSeanDesk2MenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) then
		return
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:SeanCampaign"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	print(pSceneObject, pMenuResponse, pPlayer)
end

function BestineElectionSeanDesk2MenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	print(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:SeanCampaign"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
	return
end

BestineElectionFakeSearchMenuComponent = { }

function BestineElectionFakeSearchMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) then
		return
	end
	if (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:SeanCampaign"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	print(pSceneObject, pMenuResponse, pPlayer)
end

function BestineElectionFakeSearchMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	print(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local playerCampaign = tonumber(getQuestStatus(playerID..":bestine_election:SeanCampaign"))
	if (playerCampaign == nil) or (playerCampaign < electionNum) then
		return
	end
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
	return
end



