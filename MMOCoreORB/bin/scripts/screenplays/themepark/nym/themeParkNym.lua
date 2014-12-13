local ObjectManager = require("managers.object.object_manager")
THEME_PARK_NYM_BADGE = 108

npcMapNym =
	{
		{
			spawnData = { planetName = "lok", npcTemplate = "jinkins", x = 3.07003, z = 3.29302, y = -21.31, direction = 0, cellID = 6595511, position = STAND },
			worldPosition = { x = 478, y = 4768 },
			npcNumber = 1,
			stfFile = "@celebrity/jinkins",
		},
		{
			spawnData = { planetName = "lok", npcTemplate = "nym", x = 0, z = 3.27819, y = -22.9, direction = 0, cellID = 6595511, position = SIT },
			worldPosition = { x = 475, y = 4766 },
			npcNumber = 3,
			stfFile = "@celebrity/nym",
		},
		{
			spawnData = { planetName = "lok", npcTemplate = "kole", x = -3, z = 3.4, y = -21.31, direction = 0, cellID = 6595511, position = STAND },
			worldPosition = { x = 472, y = 4768 },
			npcNumber = 2,
			stfFile = "@celebrity/kole",
		},
		{
			spawnData = { planetName = "lok", npcTemplate = "choster", x = 11.63, z = -0.894992, y = -16.56, direction = 277.008, cellID = 8145381, position = STAND },
			worldPosition = { x = 519, y = 5058 },
			npcNumber = 1,
			stfFile = "@celebrity/lok_engineer"
		},
		{
			spawnData = { planetName = "lok", npcTemplate = "lok_hacker", x = -61.9, z = -65.8, y = -142.5, direction = -92, cellID = 5126333, position = STAND },
			worldPosition = { x = -2847, y = -712 },
			npcNumber = 1,
			stfFile = "@celebrity/lok_hacker"
		},
		{
			spawnData = { planetName = "lok", npcTemplate = "berema", x = 14.3, z = -0.9, y = 23.3, direction = 181, cellID = 8145380, position = SIT },
			worldPosition = { x = 496, y = 5092 },
			npcNumber = 1,
			stfFile = "@celebrity/lok_gambler"
		},
		{
			spawnData = { planetName = "lok", npcTemplate = "sergeant_moore", x = -36.1, z = 0.1, y = -14.2, direction = 90, cellID = 8145389, position = STAND },
			worldPosition = { x = 479, y = 5031 },
			npcNumber = 1,
			stfFile = "@celebrity/imperial_bribe"
		}
	}

sceneObjectMapNym = {
	{
		spawnData = { planetName = "lok", objectTemplate = "object/tangible/terminal/terminal_nym_cave.iff", x = -60.0, z = -65.8, y = -142.4, cellID = 5126333, dw = 0.6946583704589974, dx = 0, dy = -0.7193398003386511, dz = 0 },
		worldPosition = { x = -3027, y = -681 },
		customObjectName = "Terminal"
	}
}

waypointMapNym = {
	nym = { x = 475, y = 4766 },
	jinkins = { x = 478, y = 4768 },
	kole = { x = 472, y = 4768 },
	choster = { x = 519, y = 5058 },
	piratecave = { x = -3027, y = -681 },
	imperialbribe = { x = 479, y = 5031 },
	gasmine = { x = 6467, y = 3885 },
	gambler = { x = 496, y = 5092 },
	researchfacility = { x = 902, y = -4193 }
}

ThemeParkNym = ThemeParkLogic:new {
	numberOfActs = 1,
	npcMap = npcMapNym,
	waypointMap = waypointMapNym,
	sceneObjectMap = sceneObjectMapNym,
	className = "ThemeParkNym",
	screenPlayState = "nym_theme_park",
	missionDescriptionStf = "",
	missionCompletionMessageStf = "",
}

-- Customer observer function to handle instant unlocking of area near hacker
function ThemeParkNym:cellPlayerPermissionsObserver(pCreature, pCreature2)
	return ObjectManager.withSceneObject(pCreature, function(creatureSceneObject)
		if creatureSceneObject:isCreatureObject() then
			for i = 1, # self.permissionMap, 1 do
				self:setCellPermissions(self.permissionMap[i], pCreature)
			end
		end
		return 0
	end)
end

function ThemeParkNym:setState(creatureObject, state, questGiver)
	creatureObject:setScreenPlayState(state, questGiver)
end

function ThemeParkNym:removeState(creatureObject, state, questGiver)
	creatureObject:removeScreenPlayState(state, questGiver)
end

function ThemeParkNym:spawnLootObjects()
	local droidPointer = spawnSceneObject("lok", "object/tangible/container/loot/astromech_container.iff", -64.9, -66.0, -177.7, 5126336, 0, 0, -1, 0)
	ObjectManager.withSceneObject(droidPointer, function(droidContainer)
		droidContainer:setCustomObjectName("A Defunct Astromech")
		createObserver(OBJECTRADIALUSED, "ThemeParkNym", "notifyNymContainerUsed", droidPointer)
	end)
	local afuPointer = spawnSceneObject("lok", "object/tangible/container/loot/gas_filter_container.iff", -94.2, -69.6, -93.5, 5645592, 0.7071067811865476, 0, -0.7071067811865475, 0)
	ObjectManager.withSceneObject(afuPointer, function(afuContainer)
		afuContainer:setCustomObjectName("Air Filtration Unit")
		createObserver(OBJECTRADIALUSED, "ThemeParkNym", "notifyNymContainerUsed", afuPointer)
	end)
	local csuPointer = spawnSceneObject("lok", "object/tangible/container/loot/computer_container.iff", -57.6, -20.0, 46.8, 5126277, 0, 0, 0, 0)
	ObjectManager.withSceneObject(csuPointer, function(csuContainer)
		csuContainer:setCustomObjectName("A Computer Storage Unit")
		createObserver(OBJECTRADIALUSED, "ThemeParkNym", "notifyNymContainerUsed", csuPointer)
	end)
	local cratePointer = spawnSceneObject("lok", "object/tangible/container/loot/placable_loot_crate.iff", -7.9, -20.0, 78.4, 5126291, 0, 0, -1, 0)
	ObjectManager.withSceneObject(cratePointer, function(crateContainer)
		crateContainer:setCustomObjectName("Supply Crate")
		createObserver(OBJECTRADIALUSED, "ThemeParkNym", "notifyNymContainerUsed", cratePointer)
	end)
end

function ThemeParkNym:notifyNymContainerUsed(pDroid, pPlayer, radialSelected)
	if (radialSelected ~= 16) then
		return 0
	end
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		local questItem, questMsg, questNpc
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
		if (SceneObject(pDroid):getTemplateObjectPath() == "object/tangible/container/loot/astromech_container.iff") then
			if (player:hasScreenPlayState(1, "nym_theme_park_jinkinsNpc") ~= 1 or player:hasScreenPlayState(2, "nym_theme_park_jinkinsNpc") == 1) then
				return 1
			end
			questItem = "object/tangible/loot/quest/nym_droid_memory_chip.iff"
			questMsg = "@theme_park_nym/messages:acquired_memory"
			ThemeParkNym:removeNpcWaypoints(player, playerObject)
			local jinkinsWaypoint = playerObject:addWaypoint("lok", "Return the chip to Jinkins", "Return the chip to Jinkins", ThemeParkNym.waypointMap.jinkins.x, ThemeParkNym.waypointMap.jinkins.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":jinkinsWaypointID", jinkinsWaypoint)
		elseif (SceneObject(pDroid):getTemplateObjectPath() == "object/tangible/container/loot/gas_filter_container.iff") then
			if (player:hasScreenPlayState(1, "nym_theme_park_koleNpc") ~= 1 or player:hasScreenPlayState(2, "nym_theme_park_koleNpc") == 1) then
				return 1
			end
			questItem = "object/tangible/loot/quest/nym_filtered_gas.iff"
			questMsg = "@theme_park_nym/messages:acquired_gas"
			ThemeParkNym:removeNpcWaypoints(player, playerObject)
			local koleWaypoint = playerObject:addWaypoint("lok", "Return the filter to Kole", "Return the filter to Kole", ThemeParkNym.waypointMap.kole.x, ThemeParkNym.waypointMap.kole.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":koleWaypointID", koleWaypoint)
		elseif (SceneObject(pDroid):getTemplateObjectPath() == "object/tangible/container/loot/computer_container.iff") then
			if (player:hasScreenPlayState(1, "nym_theme_park_nymNpc") ~= 1 or player:hasScreenPlayState(8, "nym_theme_park_nymNpc") == 1 or player:hasScreenPlayState(16, "nym_theme_park_nymNpc") == 1) then
				return 1
			end
			questItem = "object/tangible/loot/quest/nym_hard_drive.iff"
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/nym_imggc.iff", true) ~= nil) then
				questMsg = "@theme_park_nym/messages:all_nym_needed"
				ThemeParkNym:removeNpcWaypoints(player, playerObject)
				local nymWaypoint = playerObject:addWaypoint("lok", "Return the items to Nym", "Return the items to Nym", ThemeParkNym.waypointMap.nym.x, ThemeParkNym.waypointMap.nym.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
				setQuestStatus(player:getObjectID() .. ":nymWaypointID", nymWaypoint)
			else
				questMsg = "@theme_park_nym/messages:acquired_hard_drive"
			end
			questNpc = "nym"
		elseif (SceneObject(pDroid):getTemplateObjectPath() == "object/tangible/container/loot/placable_loot_crate.iff") then
			if (player:hasScreenPlayState(1, "nym_theme_park_nymNpc") ~= 1 or player:hasScreenPlayState(4, "nym_theme_park_nymNpc") == 1 or player:hasScreenPlayState(16, "nym_theme_park_nymNpc") == 1) then
				return 1
			end
			questItem = "object/tangible/loot/quest/nym_imggc.iff"
			if (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/nym_hard_drive.iff", true) ~= nil) then
				questMsg = "@theme_park_nym/messages:all_nym_needed"
				ThemeParkNym:removeNpcWaypoints(player, playerObject)
				local nymWaypoint = playerObject:addWaypoint("lok", "Return the items to Nym", "Return the items to Nym", ThemeParkNym.waypointMap.nym.x, ThemeParkNym.waypointMap.nym.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
				setQuestStatus(player:getObjectID() .. ":nymWaypointID", nymWaypoint)
			else
				questMsg = "@theme_park_nym/messages:acquired_imggcu"
			end
			questNpc = "nym"
		end
		local pDatapadMain = getContainerObjectByTemplate(pInventory, questItem, true)
		if (pDatapadMain == nil) then
			local pItem = giveItem(pInventory, questItem, -1)
			ObjectManager.withSceneObject(pItem, function(item)
				item:sendTo(pPlayer)
			end)
			player:sendSystemMessage(questMsg)
		end
	end)
end

function ThemeParkNym:completePark(pPlayer)
	ThemeParkLogic:giveBadge(pPlayer, THEME_PARK_NYM_BADGE)
	ObjectManager.withCreatureObject(pPlayer, function(playerCreo)
		local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
		local pItem = giveItem(pInventory, "object/weapon/ranged/carbine/carbine_nym_slugthrower.iff", -1)
		if (pItem ~= nil) then
			ObjectManager.withSceneObject(pItem, function(item)
				item:sendTo(pPlayer)
			end)
		end
		ThemeParkNym:setState(playerCreo, 16, "nym_theme_park_nymNpc")
	end)
end

NymContainerComponent = {}

function NymContainerComponent:transferObject(pContainer, pObj, slot)
	local pPlayer = ThemeParkNym:getObjOwner(pObj)
	
	if (pPlayer == nil) then
		return 0
	end
	
	return ObjectManager.withCreatureAndPlayerObject(pPlayer, function(playerCreo, playerObject)
		local questObjectPath, correctItemMsg, wrongItemMsg, questState, questStateValue
		if (SceneObject(pContainer):getObjectName() == "jinkins") then
			questObjectPath = "object/tangible/loot/quest/nym_droid_memory_chip.iff"
			correctItemMsg = "@celebrity/jinkins:gave_brain"
			wrongItemMsg = "@celebrity/jinkins:whats_this"
			questState = "nym_theme_park_jinkinsNpc"
			questStateValue = 2
		elseif (SceneObject(pContainer):getObjectName() == "kole") then
			questObjectPath = "object/tangible/loot/quest/nym_filtered_gas.iff"
			correctItemMsg = "@celebrity/kole:gave_gas"
			wrongItemMsg = "@celebrity/kole:whats_this"
			questState = "nym_theme_park_koleNpc"
			questStateValue = 2
		elseif (SceneObject(pContainer):getObjectName() == "nym") then
			if (SceneObject(pObj):getTemplateObjectPath() ~= "object/tangible/loot/quest/nym_hard_drive.iff") and (SceneObject(pObj):getTemplateObjectPath() ~= "object/tangible/loot/quest/nym_imggc.iff") then
				spatialChat(pContainer, "@celebrity/jinkins:whats_this") -- Nym has no "whats_this", using jinkins response
				return 0
			end
			if (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/nym_hard_drive.iff") then
				if (playerCreo:hasScreenPlayState(4, "nym_theme_park_nymNpc") == 1) then
					correctItemMsg = "@celebrity/nym:your_the_best" -- Has turned in both items
					ThemeParkNym:removeNpcWaypoints(playerCreo, playerObject)
					ThemeParkNym:completePark(pPlayer)
				else
					correctItemMsg = "@celebrity/nym:now_imggcu"
				end
				questObjectPath = "object/tangible/loot/quest/nym_hard_drive.iff"
				questState = "nym_theme_park_nymNpc"
				questStateValue = 8
			elseif (SceneObject(pObj):getTemplateObjectPath() == "object/tangible/loot/quest/nym_imggc.iff") then
				if (playerCreo:hasScreenPlayState(8, "nym_theme_park_nymNpc") == 1) then
					correctItemMsg = "@celebrity/nym:your_the_best" -- Has turned in both items
					ThemeParkNym:removeNpcWaypoints(playerCreo, playerObject)
					ThemeParkNym:completePark(pPlayer)
				else
					correctItemMsg = "@celebrity/nym:now_drive"
				end
				questObjectPath = "object/tangible/loot/quest/nym_imggc.iff"
				questState = "nym_theme_park_nymNpc"
				questStateValue = 4
			end
		end
		if (SceneObject(pContainer):getObjectName() ~= "nym") and (SceneObject(pObj):getTemplateObjectPath() ~= questObjectPath) then
			spatialChat(pContainer, wrongItemMsg)
		else
			ThemeParkNym:removeNpcWaypoints(playerCreo, playerObject)
			ThemeParkNym:setState(playerCreo, questStateValue, questState)
			SceneObject(pObj):destroyObjectFromWorld()
			spatialChat(pContainer, correctItemMsg)
			SceneObject(pObj):destroyObjectFromDatabase()
		end
		return 1
	end)
end

function ThemeParkNym:removeNpcWaypoints(player, playerObject)
	local caveID = tonumber(getQuestStatus(player:getObjectID() .. ":nymPirateCaveWaypointID"))
	local hermitID = tonumber(getQuestStatus(player:getObjectID() .. ":nymHermitWaypointID"))
	if (caveID ~= 0) then
		playerObject:removeWaypoint(caveID, true)
		removeQuestStatus(player:getObjectID() .. ":nymPirateCaveWaypointID")
	end
	if (hermitID ~= 0) then
		playerObject:removeWaypoint(hermitID, true)
		removeQuestStatus(player:getObjectID() .. ":nymHermitWaypointID")
	end
	local mineID = tonumber(getQuestStatus(player:getObjectID() .. ":nymGasMineWaypointID"))
	local bribeID = tonumber(getQuestStatus(player:getObjectID() .. ":nymBribeWaypointID"))
	if (mineID ~= 0) then
		playerObject:removeWaypoint(mineID, true)
		removeQuestStatus(player:getObjectID() .. ":nymGasMineWaypointID")
	end
	if (bribeID ~= 0) then
		playerObject:removeWaypoint(bribeID, true)
		removeQuestStatus(player:getObjectID() .. ":nymBribeWaypointID")
	end
	local facilityID = tonumber(getQuestStatus(player:getObjectID() .. ":nymFacilityWaypointID"))
	local gamblerID = tonumber(getQuestStatus(player:getObjectID() .. ":nymGamblerWaypointID"))
	if (facilityID ~= 0) then
		playerObject:removeWaypoint(facilityID, true)
		removeQuestStatus(player:getObjectID() .. ":nymFacilityWaypointID")
	end
	if (gamblerID ~= 0) then
		playerObject:removeWaypoint(gamblerID, true)
		removeQuestStatus(player:getObjectID() .. ":nymGamblerWaypointID")
	end
	local nymReturnID = tonumber(getQuestStatus(player:getObjectID() .. ":nymWaypointID"))
	local jinkinsReturnID = tonumber(getQuestStatus(player:getObjectID() .. ":jinkinsWaypointID"))
	local koleReturnID = tonumber(getQuestStatus(player:getObjectID() .. ":koleWaypointID"))

	if (nymReturnID ~= 0) then
		playerObject:removeWaypoint(nymReturnID, true)
		removeQuestStatus(player:getObjectID() .. ":nymWaypointID")
	end
	if (jinkinsReturnID ~= 0) then
		playerObject:removeWaypoint(jinkinsReturnID, true)
		removeQuestStatus(player:getObjectID() .. ":jinkinsWaypointID")
	end
	if (koleReturnID ~= 0) then
		playerObject:removeWaypoint(koleReturnID, true)
		removeQuestStatus(player:getObjectID() .. ":koleWaypointID")
	end
end

function ThemeParkNym:getObjOwner(pObj)
	local pPlayerInv = SceneObject(pObj):getParent()
	
	if (pPlayerInv == nil) then
		return nil
	end
	
	local parent = SceneObject(pPlayerInv):getParent()
	
	if (parent == nil) then
		return nil
	end
	
	if (SceneObject(parent):isCreatureObject()) then
		return parent
	end
    
	return nil
end

function NymContainerComponent:canAddObject(pContainer, pObj, slot)
	local pPlayer = ThemeParkNym:getObjOwner(pObj)
	
	if (pPlayer == nil) then
		return -1
	end
	
	local containerSceo = SceneObject(pContainer)
	local creature = CreatureObject(pPlayer)
	if ((containerSceo:getObjectName() == "jinkins") and (creature:hasScreenPlayState(1, "nym_theme_park_jinkinsNpc") == 1) and (creature:hasScreenPlayState(2, "nym_theme_park_jinkinsNpc") ~= 1)) then
		return true
	elseif ((containerSceo:getObjectName() == "kole") and (creature:hasScreenPlayState(1, "nym_theme_park_koleNpc") == 1) and (creature:hasScreenPlayState(2, "nym_theme_park_koleNpc") ~= 1)) then
		return true
	elseif ((containerSceo:getObjectName() == "nym") and (creature:hasScreenPlayState(1, "nym_theme_park_nymNpc") == 1) and ((creature:hasScreenPlayState(4, "nym_theme_park_nymNpc") ~= 1) or (creature:hasScreenPlayState(8, "nym_theme_park_nymNpc") ~= 1)) and (creature:hasScreenPlayState(16, "nym_theme_park_nymNpc") ~= 1)) then
		return true
	end
	return -1
end

function NymContainerComponent:removeObject(pContainer, pObj, slot)
	return -1
end

registerScreenPlay("ThemeParkNym", true)

theme_park_nym_conv_handler = NymConvoHandler:new {
	themePark = ThemeParkNym
}

-- Custom spawnNpcs to handle setting npcs as containers for quest item turnin
function ThemeParkNym:spawnNpcs()
	for i = 1, # self.npcMap do
		local npcSpawnData = self.npcMap[i].spawnData
		if isZoneEnabled(npcSpawnData.planetName) then
			local pNpc = spawnMobile(npcSpawnData.planetName, npcSpawnData.npcTemplate, 1, npcSpawnData.x, npcSpawnData.z, npcSpawnData.y, npcSpawnData.direction, npcSpawnData.cellID)
			if npcSpawnData.position == SIT then
				CreatureObject(pNpc):setState(STATESITTINGONCHAIR)
			end
			if (npcSpawnData.npcTemplate == "jinkins") or (npcSpawnData.npcTemplate == "kole") or (npcSpawnData.npcTemplate == "nym") then
				SceneObject(pNpc):setContainerComponent("NymContainerComponent")
			end
		end
	end
end

-- Overrides themepark logic to allow custom function to be called to be called
function ThemeParkNym:start()
	if (isZoneEnabled("lok")) then
		ThemeParkNym:spawnLootObjects()
		ThemeParkNym:spawnNpcs()
		self:spawnSceneObjects()
		self:permissionObservers()

		local pCell = getSceneObject(5126336)
		if pCell ~= nil then
			ObjectManager.withSceneObject(pCell, function(cell)
				cell:setContainerInheritPermissionsFromParent(false)
				cell:clearContainerDefaultDenyPermission(WALKIN)
				cell:clearContainerDefaultAllowPermission(WALKIN)
				cell:setContainerAllowPermission("NymPirateCave", WALKIN)
				cell:setContainerDenyPermission("NymPirateCave", MOVEIN)
			end)
		end
	end
end
