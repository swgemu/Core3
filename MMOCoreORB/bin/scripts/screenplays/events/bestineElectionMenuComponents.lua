local ObjectManager = require("managers.object.object_manager")

BestineElectionSeanTerminalMenuComponent = { }

function BestineElectionSeanTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	if victorVisalisConvoHandler:victorNegQuest(pPlayer) then
		local menuResponse = LuaObjectMenuResponse(pMenuResponse)
		menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
	end
end

function BestineElectionSeanTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory == nil) then
		return
	end

  local pDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff" , -1)
  if (pDisk ~= nil) then
		CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		return
	end
  if BestineElectionScreenPlay:hasFullInventory(pPlayer)then
    CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
    return
  else
	pDisk = giveItem(pInventory, "object/tangible/loot/quest/sean_questn_tdisk.iff", -1)
	if (pDisk ~= nil) then
		   CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receive1")
	 end
	end
	 return
end

BestineElectionVictorTerminalMenuComponent_Registry = { }

function BestineElectionVictorTerminalMenuComponent_Registry:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
    return
  end

	if BestineElectionScreenPlay:VictorCampaign(pPlayer) then
	 local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	 menuResponse:addRadialMenuItem(20, 3,"@city/bestine/terminal_items:download")
	end
end

function BestineElectionVictorTerminalMenuComponent_Registry:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
	   local pDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff" , -1)
	   if pDisk ~= nil then
       CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:searched")
		   return
	   end
	 end

	local pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questp_jregistry.iff" , -1)
	if (pDisk ~= nil) then
	 CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:download_complete")
	else
	 CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
	end
	return
end



BestineElectionSeanDeskMenuComponent = { }

function BestineElectionSeanDeskMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end

	 if (victorVisalisConvoHandler:victorNegQuest(pPlayer)) then
    local menuResponse = LuaObjectMenuResponse(pMenuResponse)
    menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	 end
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
	if (pDisk ~= nil) then
	 CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receive1")
	else
	 CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
	end
	return
end

BestineElectionSeanDesk2MenuComponent = { }

function BestineElectionSeanDesk2MenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	if victorVisalisConvoHandler:victorNegQuest(pPlayer) then
	 local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	 menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
  end
end

function BestineElectionSeanDesk2MenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end
	CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
	return
end


BestineElectionSearchMenuComponent_Journal = { }

function BestineElectionSearchMenuComponent_Journal:canAddObject(pContainer, pObj, slot)
	return
end

function BestineElectionSearchMenuComponent_Journal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	if seanTrenwellConvoHandler:seanNegQuest(pPlayer) then
   local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	 menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	end
end

function BestineElectionSearchMenuComponent_Journal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pSceneObject == nil or pPlayer == nil or selectedID ~= 20) then
		return
	end

	if seanTrenwellConvoHandler:seanNegQuest(pPlayer) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
		  local pDisk = getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff" , -1)
		  if pDisk ~= nil then
			CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:fail")
			return
		  end
		end

		pDisk = giveItem(pInventory, "object/tangible/loot/quest/victor_questn_journal.iff", -1)
		if (pDisk ~= nil) then
		  CreatureObject(pPlayer):sendSystemMessage("@city/bestine/terminal_items:receivemsg")
	  else
	  CreatureObject(pPlayer):sendSystemMessage("@bestine:inventory_full")
	 end
		return
	end
end


BestineElectionFakeSearchMenuComponent = { }

function BestineElectionFakeSearchMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	if (pSceneObject == nil) or (BestineElectionScreenPlay:getCurrentPhase() == 2) then
		return
	end
	if seanTrenwellConvoHandler:seanNegQuest(pPlayer) then
	 local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	 menuResponse:addRadialMenuItem(20, 3,"@bestine:search_item")
	end
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
	return
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