local ObjectManager = require("managers.object.object_manager")

DeathWatchBunker = ScreenPlay:new {
	dungeonEnabled = true
}

registerScreenPlay("DeathWatchBunker", true)

function DeathWatchBunker:start()
	if (not isZoneEnabled("endor")) then
		return
	end

	local pBunker = getSceneObject(5996314)

	if pBunker == nil then
		return
	end

	self:setupLockedDoors()

	createObserver(ENTEREDBUILDING, "DeathWatchBunker", "onEnteredBunker", pBunker)
	createObserver(EXITEDBUILDING, "DeathWatchBunker", "onExitedBunker", pBunker)
end

function DeathWatchBunker:handleStandardDoor(pPlayer, terminalType)
end

function DeathWatchBunker:givePermission(pPlayer, permissionGroup)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost ~= nil) then
		PlayerObject(pGhost):addPermissionGroup(permissionGroup, true)
	end
end

function DeathWatchBunker:removePermission(pPlayer, permissionGroup)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):hasPermissionGroup(permissionGroup)) then
		PlayerObject(pGhost):removePermissionGroup(permissionGroup, true)
	end
end

function DeathWatchBunker:hasPermission(pPlayer, permissionGroup)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):hasPermissionGroup(permissionGroup)
end

function DeathWatchBunker:setupLockedDoors()
	local doorTerminals = deathWatchDoorTerminals

	for i = 1, #doorTerminals, 1 do
		local doorData = doorTerminals[i]

		local pCell = getSceneObject(doorData[10])

		if (pCell ~= nil) then
			local pTerminal = spawnSceneObject("endor", "object/tangible/dungeon/door_control_terminal.iff", doorData[1], doorData[2], doorData[3], doorData[4], doorData[5], doorData[6], doorData[7], doorData[8])

			if (pTerminal ~= nil) then
				local terminalID = SceneObject(pTerminal):getObjectID()
				writeStringData(terminalID .. ":terminalType", doorData[9])

				SceneObject(pCell):setContainerInheritPermissionsFromParent(false)
				SceneObject(pCell):clearContainerDefaultDenyPermission(WALKIN)
				SceneObject(pCell):clearContainerDefaultAllowPermission(WALKIN)

				local permGroup = dwb .. doorData[9]

				SceneObject(pCell):setContainerAllowPermission(permGroup, WALKIN)
				SceneObject(pCell):setContainerDenyPermission(permGroup, MOVEIN)
			end
		end
	end
end
