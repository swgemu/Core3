local ObjectManager = require("managers.object.object_manager")

deathWatchDoorControlTerminal = {  }

function deathWatchDoorControlTerminal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(20, 3, "@dungeon/death_watch:mnu_open_door")
end

function deathWatchDoorControlTerminal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (selectedID == 20) then
		DeathWatchBunkerScreenPlay:checkDoor(pSceneObject, pPlayer)
	end
	return 0
end

deathWatchFilterDispenser = { }

function deathWatchFilterDispenser:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(117, 3, "@dungeon/death_watch:mnu_issue_filter")
end

function deathWatchFilterDispenser:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil) then
		return 0
	end

	if (selectedID == 117) then
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

		if (pInventory == nil) then
			return 0
		end

		local oldFilter = getContainerObjectByTemplate(pInventory, DeathWatchBunkerScreenPlay.bunkerItems.filter, true)
		if oldFilter ~= nil then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:already_has_filter")
		else
			local givenItem = giveItem(pInventory, DeathWatchBunkerScreenPlay.bunkerItems.filter, -1)
			if (givenItem == nil) then
				CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
			else
				CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:issue_filter")
			end
		end
	end
	return 0
end

deathWatchWorkbench = { }

function deathWatchWorkbench:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(117, 3, "@dungeon/death_watch:mnu_workbench")
end

function deathWatchWorkbench:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil) then
		return 0
	end

	if (selectedID ~= 117) then
		return 0
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 0
	end

	local pRebreather = getContainerObjectByTemplate(pInventory, DeathWatchBunkerScreenPlay.bunkerItems.mandoRebreather, true)
	local pEnhancedFilter = getContainerObjectByTemplate(pInventory, DeathWatchBunkerScreenPlay.bunkerItems.enhancedFilter, true)


	if (pRebreather == nil or pEnhancedFilter == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:missing_component")
		return 0
	else
		SceneObject(pEnhancedFilter):destroyObjectFromWorld()
		SceneObject(pEnhancedFilter):destroyObjectFromDatabase()
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:agumented_rebreather")

		SceneObject(pRebreather):setCustomObjectName("Advanced Rebreather")
	end
	return 0
end

deathWatchFilter = { }

function deathWatchFilter:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(117, 3, "@dungeon/death_watch:mnu_filter")
end

function deathWatchFilter:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil) then
		return 0
	end

	if (selectedID ~= 117) then
		return 0
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 0
	end

	local pAlumGel = getContainerObjectByTemplate(pInventory, DeathWatchBunkerScreenPlay.bunkerItems.alumGel, true)

	if (pAlumGel == nil or pSceneObject == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:missing_component2")
		return 0
	elseif (not CreatureObject(pPlayer):hasSkill("crafting_artisan_engineering_02")) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:not_skilled")
		return 0
	else
		SceneObject(pAlumGel):destroyObjectFromWorld()
		SceneObject(pAlumGel):destroyObjectFromDatabase()
		SceneObject(pSceneObject):destroyObjectFromWorld()
		SceneObject(pSceneObject):destroyObjectFromDatabase()
		local givenItem = giveItem(pInventory, DeathWatchBunkerScreenPlay.bunkerItems.enhancedFilter, -1)
		if (givenItem == nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: Unable to generate item.")
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:agumented_filter")
		end
	end
	return 0
end

deathWatchWaterValve = { }

function deathWatchWaterValve:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local response = LuaObjectMenuResponse(pMenuResponse)
	response:addRadialMenuItem(20, 3, "@dungeon/death_watch:mnu_water_valve")
end

function deathWatchWaterValve:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end

	if (selectedID ~= 20) then
		return 0
	end

	return ObjectManager.withCreatureObject(pPlayer, function(creature)
		if not creature:hasScreenPlayState(32, "death_watch_foreman_stage") or creature:hasScreenPlayState(64, "death_watch_foreman_stage") then
			creature:sendSystemMessage("@dungeon/death_watch:access_denied")
			return 0
		end

		local terminalNumber = readData(SceneObject(pSceneObject):getObjectID() .. ":dwb:terminal")

		DeathWatchBunkerScreenPlay:doValveSwitch(pPlayer, terminalNumber)
		
		return 0
	end)
end

deathWatchMandalorianCraftingTerminal = { }

function deathWatchMandalorianCraftingTerminal:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function deathWatchMandalorianCraftingTerminal:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end

	if (selectedID ~= 20) then
		return 0
	end

	local pTerminal = getSceneObject(readData(SceneObject(pSceneObject):getObjectID() .. ":dwb:droid"))

	if pTerminal == nil then
		return 0
	end

	local isCrafting = readData(SceneObject(pTerminal):getObjectID() .. ":dwb:currentlycrafting")
	local userId = readData(SceneObject(pTerminal):getObjectID() .. ":dwb:user")

	if isCrafting < 1 then
		return 0
	end

	if CreatureObject(pPlayer):getObjectID() ~= userId then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:same_user_only")
		return 0
	end

	if isCrafting == 2 or isCrafting == 4 then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:crafting_not_yet")
		return 0
	end

	if isCrafting == 1 then
		local suiManager = LuaSuiManager()
		suiManager:sendConfirmSui(pTerminal, pPlayer, "DeathWatchBunkerScreenPlay", "craftingConfirmCallback", "@dungeon/death_watch:continue_manufacturing", "@dungeon/death_watch:continue_button")
	elseif isCrafting == 3 then
		local suiManager = LuaSuiManager()
		suiManager:sendConfirmSui(pTerminal, pPlayer, "DeathWatchBunkerScreenPlay", "craftingConfirmCallback", "@dungeon/death_watch:finish_manufacturing", "@dungeon/death_watch:finish_button")
	end

	return 0
end