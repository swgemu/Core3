local ObjectManager = require("managers.object.object_manager")

CorellianCorvette = ScreenPlay:new {
	buildings = {
		{ faction = "neutral", buildingIds = { 1945494, 1945561, 1945628, 1945695, 1945762, 1945829, 1945896, 1945963, 1946030, 1946097, 1946164, 4335861, 4335928, 4335995, 4336062, 4336129 } },
		{ faction = "imperial", buildingIds = { 1946231, 1946298, 1946365, 1946432, 1946499, 1946566, 1946633, 1946700, 1946767, 1946834, 1946901, 4336196, 4336263, 4336330, 4336397, 4336464 } },
		{ faction = "rebel", buildingIds = { 1946968, 1947035, 1947102, 1947169, 1947236, 1947303, 1947370, 1947437, 1947504, 1947571, 1947638, 4336531, 4336598, 4336665, 4336732, 4336799 } }
	},

	escapePoints = {
		{ faction = "neutral", planet = "tatooine", x = -5842, y = -6191 },
		{ faction = "imperial", planet = "naboo", x = 2445, y = -3913 },
		{ faction = "rebel", planet = "corellia", x = -6460, y = 5972 },
	},

	lockedRooms = { "elevator57", "meetingroom38", "armorybackroom55", "officerquarters63", "officerquarters64", "officerquarters65", "bridge66" },

	electricTrapLocs = {
		{ x = 0, z = -14, y = -32 },
		{ x = 0, z = -14, y = -34 },
		{ x = 0, z = -14, y = -36 },
		{ x = 0, z = -14, y = -38 },
		{ x = 0, z = -14, y = -40 },
	},
}

registerScreenPlay("CorellianCorvette", true)

function CorellianCorvette:start()
	if (isZoneEnabled("dungeon1")) then
		self:initialize()
	end
end

function CorellianCorvette:initialize()
	local num = 0
	for i = 1, #self.buildings, 1 do
		local building = self.buildings[i]
		for j = 1, #building.buildingIds, 1 do
			local pCorvette = getSceneObject(building.buildingIds[j])
			if pCorvette ~= nil then
				if not SceneObject(pCorvette):isBuildingObject() then
					print("Corvette id isn't a building: " .. building.buildingIds[j])
				else
					local corvetteID = SceneObject(pCorvette):getObjectID()
					writeData("corvetteActive:" .. corvetteID, 0)
					self:ejectAllPlayers(pCorvette)
					writeData("corvettePlayerCount:" .. corvetteID, 0)
					createObserver(ENTEREDBUILDING, "CorellianCorvette", "onEnterCorvette", pCorvette)
					createObserver(EXITEDBUILDING, "CorellianCorvette", "onExitCorvette", pCorvette)
					num = num + 1
				end
			else
				print("Corvette id isn't valid: " .. building.buildingIds[j])
			end
		end
	end

	print(num .. " corvette buildings initialized.")
end

function CorellianCorvette:activate(pPlayer, faction, questType)
	if (not isZoneEnabled("dungeon1")) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:unable_to_find_dungeon") -- That area is currently unavailable. Please try again later.
		return false
	end

	local ids = nil
	for i = 1, #self.buildings, 1 do
		if self.buildings[i].faction == faction then
			ids = self.buildings[i].buildingIds
		end
	end

	if ids == nil then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:corellian_corvette_travel_fail") -- The Corellian corvette is currently out of transport range making transportation impossible.
		return false
	end

	local active = 1
	local corvetteId = 0
	for i = 1, #ids, 1 do
		active = readData("corvetteActive:" .. ids[i])

		if active ~= 1 then
			corvetteId = ids[i]
			break
		end
	end

	if corvetteId ~= 0 then
		writeData(SceneObject(pPlayer):getObjectID() .. "corvetteId", corvetteId)
		writeStringData(SceneObject(pPlayer):getObjectID() .. "questType", questType)
		createEvent(1000, "CorellianCorvette", "transportPlayer", pPlayer, "")
		--TODO prompt nearby group members for travel
		return true
	end

	CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:corellian_corvette_travel_fail") -- The Corellian corvette is currently out of transport range making transportation impossible.
	return false
end

function CorellianCorvette:lockRooms(pCorvette)
	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()

	for i = 1 ,#self.lockedRooms, 1 do
		local pCell = BuildingObject(pCorvette):getNamedCell(self.lockedRooms[i])

		if (pCell ~= nil) then
			SceneObject(pCell):setContainerInheritPermissionsFromParent(false)
			SceneObject(pCell):setContainerDefaultDenyPermission(WALKIN)
			SceneObject(pCell):clearContainerDefaultAllowPermission(WALKIN)
		end
	end
end

function CorellianCorvette:unlockRoom(pCorvette, roomName)
	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()

	local pCell = BuildingObject(pCorvette):getNamedCell(roomName)

	if (pCell ~= nil) then
		SceneObject(pCell):clearContainerDefaultDenyPermission(WALKIN)
		SceneObject(pCell):setContainerDefaultAllowPermission(WALKIN)
		local cellID = SceneObject(pCell):getObjectID()
		BuildingObject(pCorvette):broadcastSpecificCellPermissions(cellID)
	end
end

function CorellianCorvette:setupSceneObjects(pCorvette)
	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()
	local corvetteFaction = self:getBuildingFaction(pCorvette)

	if (readData("corvetteActive:" .. corvetteID) ~= 1) then
		return
	end

	for i = 1, #corvetteStaticSpawns, 1 do
		local spawnData = corvetteStaticSpawns[i]
		local pCell = BuildingObject(pCorvette):getNamedCell(spawnData[5])

		if (pCell ~= nil) then
			if (spawnData[10] == nil or spawnData[10] == "" or spawnData[10] == corvetteFaction) then
				local pObject = spawnSceneObject("dungeon1", spawnData[1], spawnData[2], spawnData[3], spawnData[4], SceneObject(pCell):getObjectID(), math.rad(spawnData[6]))

				if (pObject == nil) then
					printLuaError("CorellianCorvette:setupSceneObjects unable to spawn scene object " .. spawnData[1] .. " for corvette ID " .. corvetteID)
				else
					if (spawnData[7] ~= nil and spawnData[7] ~= "") then
						SceneObject(pObject):setCustomObjectName(spawnData[7])
					end

					if (spawnData[8] ~= nil and spawnData[8] ~= "") then
						local extraData = spawnData[9]

						if (extraData == nil) then
							extraData = ""
						end

						createEvent(100, "CorellianCorvette", spawnData[8], pObject, extraData)
					end
				end
			end
		else
			printLuaError("Unable to grab cell object for cell named " .. spawnData[5] .. " when trying to spawn object " .. spawnData[1] .. ".")
		end
	end
end

function CorellianCorvette:spawnNpcs(pCorvette)
	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()
	local corvetteFaction = self:getBuildingFaction(pCorvette)

	if (readData("corvetteActive:" .. corvetteID) ~= 1) then
		return
	end

	local spawnTable = corvetteNeutralSpawns

	if (corvetteFaction == "imperial") then
		spawnTable = corvetteImperialSpawns
	elseif (corvetteFaction == "rebel") then
		spawnTable = corvetteRebelSpawns
	end

	for i = 1, #spawnTable, 1 do
		local spawnData = spawnTable[i]
		local pCell = BuildingObject(pCorvette):getNamedCell(spawnData[6])

		if (pCell ~= nil) then
			local cellID = SceneObject(pCell):getObjectID()
			local pMobile = spawnMobile("dungeon1", spawnData[1], 0, spawnData[2], spawnData[3], spawnData[4], spawnData[5], cellID)

			if (pMobile == nil) then
				printLuaError("CorellianCorvette:setupSceneObjects unable to spawn mobile " .. spawnData[1] .. " for " .. corvetteFaction .. " corvette ID " .. corvetteID)
			else
				if (spawnData[7] ~= nil and spawnData[7] ~= "") then
					createEvent(100, "CorellianCorvette", spawnData[7], pMobile, "")
				end
			end
		else
			printLuaError("Unable to grab cell object for cell named " .. spawnData[6] .. " in corvette ID " .. corvetteID .. " when trying to spawn " .. spawnData[1])
		end
	end
end

function CorellianCorvette:setupAssassinationTarget(pTarget)
	if (pTarget == nil) then
		return
	end

	local pCorvette = self:getCorvetteObject(pTarget)

	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()

	if (readData("corvetteActive:" .. corvetteID) ~= 1) then
		return
	end

	createObserver(OBJECTDESTRUCTION, "CorellianCorvette", "onAssassinationTargetKilled", pTarget)
end

function CorellianCorvette:onAssassinationTargetKilled(pTarget, pKiller)
	if (pTarget == nil or pKiller == nil) then
		return 1
	end

	local pCorvette = self:getCorvetteObject(pTarget)

	if (pCorvette == nil) then
		return 1
	end

	local questType = readStringData(SceneObject(pKiller):getObjectID() .. "questType")

	if (questType ~= "assassinate") then
		return 1
	end

	CorellianCorvette:handleQuestSuccess(pCorvette)

	return 1
end

function CorellianCorvette:setupBrokenDroid(pDroid)
	if (pDroid == nil) then
		return
	end

	local pCorvette = self:getCorvetteObject(pDroid)

	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()

	if (readData("corvetteActive:" .. corvetteID) ~= 1) then
		return
	end

	local pCell = BuildingObject(pCorvette):getNamedCell("thrustersubroom28")

	if (pCell == nil) then
		return
	end

	local cellId = SceneObject(pCell):getObjectID()
	for i = 1, #self.electricTrapLocs, 1 do
		local trapLoc = self.electricTrapLocs[i]
		local pTrap = spawnSceneObject("dungeon1", "object/static/particle/pt_poi_electricity_2x2.iff", trapLoc.x, trapLoc.z, trapLoc.y, cellId, 1, 0, 0, 0)

		if pTrap ~= nil then
			local trapID = SceneObject(pTrap):getObjectID()
			writeData(corvetteID .. ":electricTrap" .. i, trapID)
			local pTrapArea = spawnActiveArea("dungeon1", "object/active_area.iff", trapLoc.x, trapLoc.z, trapLoc.y, 4, cellId)

			if pTrapArea ~= nil then
				writeData(trapID .. ":trapArea", SceneObject(pTrapArea):getObjectID())
				createObserver(ENTEREDAREA, "CorellianCorvette", "notifyTrapAreaEntered", pTrapArea)
			end
		end
	end

	writeData(corvetteID .. ":electricTrapEnabled", 1)
end

function CorellianCorvette:notifyTrapAreaEntered(pActiveArea, pMovingObject)
	if (pActiveArea == nil) then
		return 1
	end

	if (pMovingObject == nil or not SceneObject(pMovingObject):isCreatureObject()) then
		return 0
	end

	if (SceneObject(pMovingObject):isAiAgent() and not AiAgent(pMovingObject):isPet()) then
		return 0
	end

	local pCorvette = self:getCorvetteObject(pMovingObject)

	if (pCorvette == nil) then
		return 1
	end

	if (readData(SceneObject(pCorvette):getObjectID() .. ":electricTrapEnabled") ~= 1) then
		return 0
	end

	CreatureObject(pMovingObject):inflictDamage(pMovingObject, 0, getRandomNumber(15000,20000), 1)
	CreatureObject(pMovingObject):sendSystemMessage("@quest/corvetter_trap:shocked") --You feel electricity coursing through your body!

	return 0
end

function CorellianCorvette:setupRoomPanel(pPanel, room)
	if (pPanel == nil or room == "") then
		return
	end

	SceneObject(pPanel):setObjectMenuComponent("CorvetteRoomPanelMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyRoomPanelRemovedFromZone", pPanel, 1)
	writeStringSharedMemory(SceneObject(pPanel):getObjectID() .. ":panelRoom", room)
end

function CorellianCorvette:notifyRoomPanelRemovedFromZone(pPanel)
	if (pPanel == nil) then
		return 1
	end

	local panelID = SceneObject(pPanel):getObjectID()

	deleteStringSharedMemory(panelID .. ":panelRoom")
	deleteData(panelID .. ":roomUnlocked")

	return 1
end

function CorellianCorvette:setupKeypad(pKeypad, room)
	if (pKeypad == nil or room == "") then
		return
	end

	SceneObject(pKeypad):setObjectMenuComponent("CorvetteKeypadMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyKeypadRemovedFromZone", pKeypad, 1)
	writeStringSharedMemory(SceneObject(pKeypad):getObjectID() .. ":keypadRoom", room)
end

function CorellianCorvette:notifyKeypadRemovedFromZone(pKeypad)
	if (pKeypad == nil) then
		return 1
	end

	local keypadID = SceneObject(pKeypad):getObjectID()

	deleteStringSharedMemory(keypadID .. ":keypadRoom")

	return 1
end

function CorellianCorvette:setupDestroyTerminal(pTerminal, type)
	if (pTerminal == nil or type == "") then
		return
	end

	SceneObject(pTerminal):setObjectMenuComponent("CorvetteDestroyTerminalMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyDestroyTerminalRemovedFromZone", pTerminal, 1)
	writeStringSharedMemory(SceneObject(pTerminal):getObjectID() .. ":terminalType", type)
end

function CorellianCorvette:notifyDestroyTerminalRemovedFromZone(pTerminal)
	if (pTerminal == nil) then
		return 1
	end

	local keypadID = SceneObject(pTerminal):getObjectID()

	deleteStringSharedMemory(keypadID .. ":terminalType")

	return 1
end

function CorellianCorvette:setupComputerObject(pComputer, label)
	if (pComputer == nil or label == "") then
		return
	end

	SceneObject(pComputer):setObjectMenuComponent("CorvetteComputerMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyComputerRemovedFromZone", pComputer, 1)
	writeStringSharedMemory(SceneObject(pComputer):getObjectID() .. ":computerLabel", label)
end

function CorellianCorvette:spawnComputerEnemies(pCorvette, pComputer)
	if (pCorvette == nil or pComputer == nil) then
		return
	end

	local corvetteFaction = self:getBuildingFaction(pCorvette)
	local spawnTemplate

	if (corvetteFaction == "neutral") then
		spawnTemplate = "corsec_super_battle_droid"
	elseif (corvetteFaction == "imperial") then
		spawnTemplate = "rebel_super_battle_droid"
	elseif (corvetteFaction == "rebel") then
		spawnTemplate = "imperial_super_battle_droid"
	else
		return
	end

	local cellID = SceneObject(pComputer):getParentID()

	-- TODO: Spawn the mobile after we can pick a good random room location
end

function CorellianCorvette:notifyComputerRemovedFromZone(pComputer)
	if (pComputer == nil) then
		return 1
	end

	local computerID = SceneObject(pComputer):getObjectID()

	deleteStringSharedMemory(computerID .. ":computerLabel")
	deleteData(computerID .. ":accessCode")
	deleteData(computerID .. ":spawnedEnemies")
	deleteData(computerID .. ":terminalRebooted")
	deleteData(computerID .. ":sliceAttempted")

	return 1
end

function CorellianCorvette:setupEscapePod(pPod)
	if (pPod == nil) then
		return
	end

	createObserver(OBJECTRADIALUSED, "CorellianCorvette", "notifyPodRadialUsed", pPod)

	local pActiveArea = spawnActiveArea("dungeon1", "object/active_area.iff", SceneObject(pPod):getWorldPositionX(), SceneObject(pPod):getWorldPositionZ(), SceneObject(pPod):getWorldPositionY(), 3, SceneObject(pPod):getParentID())

	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "CorellianCorvette", "notifyEnteredEscapePodArea", pActiveArea)
	end
end

function CorellianCorvette:notifyPodRadialUsed(pPod, pPlayer, radialSelected)
	if (pPod == nil) then
		return 1
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	if (radialSelected == 20) then
		createEvent(2 * 1000, "CorellianCorvette", "ejectPlayer", pPlayer,"")
		return 0
	end

	return 0
end

function CorellianCorvette:notifyEnteredEscapePodArea(pActiveArea, pPlayer)
	if (pActiveArea == nil) then
		return 1
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:escape_pod_message")

	return 0
end

function CorellianCorvette:transportPlayer(pPlayer)
	if pPlayer == nil then
		return
	end

	local questType = readStringData(SceneObject(pPlayer):getObjectID() .. "questType")
	local corvetteId = readData(SceneObject(pPlayer):getObjectID() .. "corvetteId")
	local pCorvette = getSceneObject(corvetteId)

	self:startQuest(pCorvette, questType)
	local pCell = BuildingObject(pCorvette):getCell(1)

	if (pCell == nil) then
		return
	end
	local cellID = SceneObject(pCell):getObjectID()
	SceneObject(pPlayer):switchZone("dungeon1", -42.9, 0, 0.1, cellID)
end

function CorellianCorvette:startQuest(pCorvette, questType)
	writeData("corvetteActive:" .. SceneObject(pCorvette):getObjectID(), 1)
	writeData("corvetteStartTime:" .. SceneObject(pCorvette):getObjectID(), os.time())
	createEvent(5 * 60 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")

	self:setupSceneObjects(pCorvette)
	self:spawnNpcs(pCorvette)
	self:lockRooms(pCorvette)
	--TODO spawn quest mobs, and objectives
end

function CorellianCorvette:getBuildingFaction(pCorvette)
	local templatePath = SceneObject(pCorvette):getTemplateObjectPath()
	if string.find(templatePath, "imperial") ~= nil then
		return "imperial"
	elseif string.find(templatePath, "rebel") ~= nil then
		return "rebel"
	else
		return "neutral"
	end
end

function CorellianCorvette:onEnterCorvette(pCorvette, pPlayer)
	if SceneObject(pPlayer):isPlayerCreature() then
		local active = readData("corvetteActive:" .. SceneObject(pCorvette):getObjectID())
		if active ~= 1 then
			createEvent(10 * 1000, "CorellianCorvette", "handleNotAuthorized", pPlayer, "")
			return 0
		end

		local playerCount = readData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID())

		writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), playerCount + 1)

		if playerCount > 10 then
			createEvent(10 * 1000, "CorellianCorvette", "handleTooMany", pPlayer, "")
			return 0
		end
	end

	return 0
end

function CorellianCorvette:onExitCorvette(pCorvette, pPlayer)
	if not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local playerCount = readData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID())
	writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), playerCount - 1)

	self:doPlayerCleanup(pPlayer)

	return 0
end

function CorellianCorvette:handleNotAuthorized(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:not_authorized") -- You do not have the proper authorization to be in this area.
	createEvent(2 * 1000, "CorellianCorvette", "ejectPlayer", pPlayer, "")
end

function CorellianCorvette:handleTooMany(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:no_room_remaining") -- There are too many people in this area. Return transportation initiated.
	createEvent(2 * 1000, "CorellianCorvette", "ejectPlayer", pPlayer, "")
end

function CorellianCorvette:handleCorvetteTimer(pCorvette)
	local startTime = readData("corvetteStartTime:" .. SceneObject(pCorvette):getObjectID())
	local timeLeftSecs = 3600 - (os.time() - startTime)
	local timeLeft = math.floor(timeLeftSecs / 60)

	if (timeLeft > 10) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_" .. timeLeft)
		createEvent(5 * 60 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	elseif (timeLeftSecs <= 90) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_" .. timeLeftSecs .. "s")
		if (timeLeftSecs == 0) then
			self:handleQuestFailure(pCorvette)
		elseif (timeLeftSecs <= 10) then
			createEvent(10 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
		else
			createEvent(30 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
		end
	else
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_" .. timeLeft)
		createEvent(60 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	end
end

function CorellianCorvette:getCorvetteObject(pPlayer)
	if (pPlayer == nil) then
		return nil
	end

	local pCell = SceneObject(pPlayer):getParent()

	if (pCell == nil) then
		return nil
	end

	return SceneObject(pCell):getParent()
end

function CorellianCorvette:handleQuestFailure(pCorvette)
	--TODO reset ticket giver quest
	self:ejectAllPlayers(pCorvette)
	writeData("corvetteActive:" .. SceneObject(pCorvette):getObjectID(), 0)
end

function CorellianCorvette:handleQuestSuccess(pCorvette)
	self:broadcastToPlayers(pCorvette, "@dungeon/corvette:escape_pods") -- You have completed your assignment! Make your way to the escape pods before time expires and get off this ship!
	self:writeDataToGroup(pCorvette, ":corvetteMissionComplete", 1)
end

function CorellianCorvette:broadcastToPlayers(pCorvette, message)
	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if SceneObject(pObject):isPlayerCreature() then
					CreatureObject(pObject):sendSystemMessage(message)
				end
			end
		end
	end
end

function CorellianCorvette:ejectAllPlayers(pCorvette)
	local playersToEject = {}
	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
					table.insert(playersToEject, pObject)
				end
			end
		end
	end

	for i = 1, #playersToEject, 1 do
		local pObject = playersToEject[i]
		createEvent(1000, "CorellianCorvette", "ejectPlayer", pObject, "")
	end
end

function CorellianCorvette:writeDataToGroup(pCorvette, key, data)
	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
					writeData(SceneObject(pObject):getObjectID() .. key, data)
				end
			end
		end
	end
end

function CorellianCorvette:readDataFromGroup(pCorvette, key)
	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)

				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
					local data = readData(SceneObject(pObject):getObjectID() .. key)

					if (data ~= 0) then
						return data
					end
				end
			end
		end
	end

	return 0
end

function CorellianCorvette:checkSlicingSkill(pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local slicingSkill = 0

	if (not CreatureObject(pPlayer):hasSkill("combat_smuggler_novice")) then
		return slicingSkill
	end

	slicingSkill = 1

	for i = 1, 4, 1 do
		if (CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_0" .. i)) then
			slicingSkill = slicingSkill + 1
		end
	end

	if (CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_master")) then
		slicingSkill = slicingSkill + 1;
	end

	return slicingSkill;
end

function CorellianCorvette:ejectPlayer(pPlayer)
	if pPlayer == nil then
		return
	end

	local point = nil

	local pParent = SceneObject(pPlayer):getParent()

	if (pParent == nil) then
		return
	end

	local pCorvette = SceneObject(pParent):getParent()

	if pCorvette == nil or not SceneObject(pCorvette):isBuildingObject() then
		print("Error: unable to get corvette in CorellianCorvette:ejectPlayer")
		return
	end

	local faction = self:getBuildingFaction(pCorvette)

	for i = 1, #self.escapePoints, 1 do
		if self.escapePoints[i].faction == faction then
			point = self.escapePoints[i]
		end
	end

	if point == nil then
		print("Error: nil escape point for faction: " .. faction)
		return
	end

	if (isZoneEnabled(point.planet)) then
		SceneObject(pPlayer):switchZone(point.planet, point.x, 0, point.y, 0)
		print("Ejecting player " .. SceneObject(pPlayer):getCustomObjectName() .. " from corvette.")
	else
		print("Error: escape zone for corvette transfer is not enabled.")
	end
end

function CorellianCorvette:doPlayerCleanup(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":code:armorybackroom55")
	deleteData(playerID .. ":code:bridge66")
	deleteData(playerID .. ":code:officerquarters63")
	deleteData(playerID .. ":code:officerquarters64")
	deleteData(playerID .. ":code:officerquarters65")
	deleteData(playerID .. ":unlocked:elevator57")
	deleteData(playerID .. ":unlocked:meetingroom38")
end

function CorellianCorvette:doCorvetteCleanup(pCorvette)
	if (pCorvette == nil) then
		return
	end

	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)

				if pObject ~= nil and not SceneObject(pObject):isPlayerCreature() then
					SceneObject(pObject):destroyObjectFromWorld()
				end
			end
		end
	end


	local corvetteID = SceneObject(pCorvette):getObjectID()

	deleteData(corvetteID .. ":fuelSetting")
	deleteData(corvetteID .. ":engineSetting")
	deleteData(corvetteID .. ":hyperdriveSetting")
	deleteData(corvetteID .. ":engineDestroyed")
	deleteData(corvetteID .. ":electricTrapEnabled")

	for i = 1, #self.electricTrapLocs, 1 do
		local trapID = readData(corvetteID .. ":electricTrap" .. i)
		deleteData(trapID .. ":trapArea")
		deleteData(corvetteID .. ":electricTrap" .. i)
	end
end
