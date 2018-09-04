GeoLabTrapTerminalMenuComponent = { }

function GeoLabTrapTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function GeoLabTrapTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return
	end

	if (SceneObject(pPlayer):getParentID() ~= SceneObject(pSceneObject):getParentID() or not CreatureObject(pPlayer):isInRangeWithObject(pSceneObject, 4)) then
		return
	end

	local trapIndex = readData(SceneObject(pSceneObject):getObjectID() .. ":trapIndex")
	local trapEnabled = readData("geoLab:trapEnabled:" .. trapIndex)

	if (trapEnabled == 0) then
		if (trapIndex >= 3) then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:power_already_off") -- The power is already off.
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:gas_already_off") -- The gas leak has already been repaired...
		end

		return
	end

	local trapID = readData("geoLab:trapIndex" .. trapIndex)
	local pTrap = getSceneObject(trapID)

	if (pTrap == nil) then
		printLuaError("GeoLab null trap object when attempting to use trap terminal for trap index " .. trapIndex)
		return
	end

	local trapEffectID = readData("geoLab:trapEffect:" .. trapIndex)
	local pTrapEffect = getSceneObject(trapEffectID)

	if (pTrapEffect ~= nil) then
		SceneObject(pTrapEffect):destroyObjectFromWorld()
	end

	deleteData("geoLab:trapEnabled:" .. trapIndex)
	local trapTimer = 10000

	if (trapIndex == 3) then
		trapTimer = 27000
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:power_off") -- You have shut off the power.
	elseif (trapIndex == 4) then
		trapTimer = 20000
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:power_off") -- You have shut off the power.
		SceneObject(pTrap):clearContainerDefaultDenyPermission(OPEN + MOVEOUT)
		SceneObject(pTrap):setContainerDefaultAllowPermission(OPEN + MOVEOUT)
	else
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:gas_off") -- You have shut off the gas leak.
		SceneObject(pTrap):playEffect("clienteffect/item_gas_leak_trap_off.cef", "")
	end

	createEvent(trapTimer, "GeonosianLab", "turnOnTrap", pTrap, "")
end

GeoLabTrashContainerMenuComponent = { }

function GeoLabTrashContainerMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function GeoLabTrashContainerMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 16) then
		return
	end

	if (SceneObject(pPlayer):getParentID() ~= SceneObject(pSceneObject):getParentID() or not CreatureObject(pPlayer):isInRangeWithObject(pSceneObject, 6)) then
		return
	end

	local trapIndex = readData(SceneObject(pSceneObject):getObjectID() .. ":trapIndex")
	local trapEnabled = readData("geoLab:trapEnabled:" .. trapIndex)

	if (trapEnabled == 1) then
		CreatureObject(pPlayer):inflictDamage(pPlayer, 0, getRandomNumber(300, 700), 1)
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/geonosian_madbio:electric_trash") -- You were electrified by the trash heap!
		playClientEffectLoc(CreatureObject(pPlayer):getObjectID(), "clienteffect/trap_electric_01.cef", "yavin4", SceneObject(pSceneObject):getPositionX(), SceneObject(pSceneObject):getPositionZ(), SceneObject(pSceneObject):getPositionY(), SceneObject(pSceneObject):getParentID())
	else
		if (readData("geoLab:trashContainerLoot") == 1) then
			createLoot(pSceneObject, "geonosian_loot_container", 1, false)
			createLoot(pSceneObject, "geonosian_loot_container", 1, false)
			deleteData("geoLab:trashContainerLoot")
			createEvent(10 * 60 * 1000, "GeonosianLab", "resetTrashLoot", pSceneObject, "")
		end
	end
end

GeoLabKeypadMenuComponent = { }

function GeoLabKeypadMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
end

function GeoLabKeypadMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return
	end

	if (SceneObject(pPlayer):getParentID() ~= SceneObject(pSceneObject):getParentID() or not CreatureObject(pPlayer):isInRangeWithObject(pSceneObject, 6)) then
		return
	end

	local sui = SuiKeypad.new("GeonosianLab", "keypadSuiCallback")

	if (not CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_01")) then
		sui.hideSliceButton()
	end

	sui.setTargetNetworkId(SceneObject(pSceneObject):getObjectID())
	sui.setForceCloseDistance(10)
	sui.sendTo(pPlayer)
end
