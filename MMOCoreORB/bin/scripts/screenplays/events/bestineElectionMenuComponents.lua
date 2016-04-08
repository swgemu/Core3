local ObjectManager = require("managers.object.object_manager")

BestineElectionSeanTerminalMenuComponent = { }

function BestineElectionSeanTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	if victorVisalisConvoHandler:hasNQuestVar(pPlayer) then
		local menuResponse = LuaObjectMenuResponse(pMenuResponse)
		menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
	end
end

function BestineElectionSeanTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
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
	return 1
end

BestineElectionVictorTerminalMenuComponent_Registry = { }

function BestineElectionVictorTerminalMenuComponent_Registry:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) then
		return
	end
	if (not BestineElectionScreenPlay:VictorCampaign(pPlayer)) and (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
end

function BestineElectionVictorTerminalMenuComponent_Registry:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end
	if (not BestineElectionScreenPlay:VictorCampaign(pPlayer)) then
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
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end

	 if (not victorVisalisConvoHandler:victorNegQuest(pPlayer)) then
    return
  end

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
end

function BestineElectionSeanDeskMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
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
	return 1
end

BestineElectionSeanDesk2MenuComponent = { }

function BestineElectionSeanDesk2MenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	if (not victorVisalisConvoHandler:victorNegQuest(pPlayer)) then
	 return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
end

function BestineElectionSeanDesk2MenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end
	CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
	return 1
end


BestineElectionSearchMenuComponent_Journal = { }

function BestineElectionSearchMenuComponent_Journal:canAddObject(pContainer, pObj, slot)
	return
end

function BestineElectionSearchMenuComponent_Journal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	 if (not seanTrenwellConvoHandler:seanNegQuest(pPlayer)) then
   return
  end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
end

function BestineElectionSearchMenuComponent_Journal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	if seanTrenwellConvoHandler:hasNQuestVar(pPlayer) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory == nil) then
			return
		end
		if getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff" , true) then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
			return
		end

		local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", -1)
		if (pDisk == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item:victor_questn_journal.iff")
			return
		end
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receivemsg")
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
	return
end


BestineElectionFakeSearchMenuComponent = { }

function BestineElectionFakeSearchMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
end

function BestineElectionFakeSearchMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
	return
end

TourContainerComponent = {}

function TourContainerComponent:transferObject(pContainer, pObj, slot)
	if (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/sean_questp_mdisk.iff") or 	(SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/sean_questp_ctestimony.iff") or
	(SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/sean_questp_htestimony.iff") or (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/victor_questp_jregistry.iff") or
	(SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/victor_questp_testimony.iff") or (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/victor_questp_receipt.iff")
	then spatialChat(pContainer, "@bestine:give_governor_item")
	end
	return 0
end

BestineElectionHistoryQuestMenuComponent = { }

function BestineElectionHistoryQuestMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
  if (pSceneObject == nil) then
    return
  end
  local playerID = CreatureObject(pPlayer):getObjectID()
   if readData(playerID .. ":bestine_election:find") == 1 then
      local menuResponse = LuaObjectMenuResponse(pMenuResponse)
      menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
   end
end



function BestineElectionHistoryQuestMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
  if (pSceneObject == nil) or (pPlayer == nil) or (selectedID ~= 20) then
    return
  end

  if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
    CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:inv_full")
    return
  end

  local playerID = CreatureObject(pPlayer):getObjectID()
  if (readData(playerID .. ":bestine_election:searched") == 1) then
    CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:history_disk_found_already")
    return
  else
    local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

    if (pInventory == nil) then
      return
    end

    local pDisk = giveItem(pInventory,"object/tangible/loot/quest/sean_history_disk.iff", -1)
    if (pDisk == nil) then
      CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item:sean_history_disk.iff")
      return
    end
    CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:history_disk_found")
    writeData(playerID .. ":bestine_election:searched",1)
    return
  end
  CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
  return
end



