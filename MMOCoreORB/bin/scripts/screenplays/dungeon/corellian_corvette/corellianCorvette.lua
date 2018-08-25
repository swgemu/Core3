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

	missionBadges = {
		imperial_destroy = 112, -- ...has been recognized as an Elite Imperial Soldier, for bravery in the call of duty, eliminating a Rebel Blockade Runner.
		imperial_rescue = 113, -- ...has been recognized for bravery in the face of danger, for rescuing Imperial Loyalists from the Rebel Menace, imprisoned on a Rebel Blockade Runner.
		imperial_assassinate = 114, -- ...has been recognized as an elite Imperial soldier for work in eliminating key Rebel personnel aboard a fully functional Rebel Blockade Runner.
		neutral_destroy = 115, -- ...has been recognized by the Hutt clan for work in destroying Corellian Corvette.
		neutral_rescue = 116, -- ...has been recognized by the Hutt clan for work in freeing our imprisoned friends aboard a Corellian Corvette.
		neutral_assassinate = 117, -- ...has been recognized by the Hutt clan for work in eliminating key personnel at the Hutt's request.
		rebel_destroy = 118, -- ...has been recognized by the Alliance as an elite soldier for work in destroying a captured Rebel Blockade Runner.
		rebel_rescue = 119, -- ...has been recognized by the Alliance as an elite soldier for work in rescuing imprisoned comrades aboard a captured Rebel Blockade Runner.
		rebel_assassinate = 120, -- ...has been recognized by the Alliance as an elite soldier for work in eliminating key Imperial personnel on a captured Rebel Blockade Runner.
	},

	lockedRooms = { "elevator57", "meetingroom38", "armorybackroom55", "officerquarters63", "officerquarters64", "officerquarters65", "bridge66" },

	electricTrapLocs = {
		{ x = 1, z = -14, y = -32 },
		{ x = 1, z = -14, y = -34 },
		{ x = 1, z = -14, y = -36 },
		{ x = 1, z = -14, y = -38 },
		{ x = 1, z = -14, y = -40 },
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
			if pCorvette == nil or not SceneObject(pCorvette):isBuildingObject() then
				printLuaError("CorellianCorvette:initialize tried using a corvette id that was nil or not a building: " .. building.buildingIds[j])
			else
				local corvetteID = SceneObject(pCorvette):getObjectID()
				deleteData("corvetteActive:" .. corvetteID)
				self:ejectAllPlayers(pCorvette)
				deleteData("corvettePlayerCount:" .. corvetteID)
				createObserver(ENTEREDBUILDING, "CorellianCorvette", "onEnterCorvette", pCorvette)
				createObserver(EXITEDBUILDING, "CorellianCorvette", "onExitCorvette", pCorvette)
				num = num + 1
			end
		end
	end
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
	local corvetteID = 0
	for i = 1, #ids, 1 do
		active = readData("corvetteActive:" .. ids[i])

		if (active == 1) then
			local startTime = readData("corvetteStartTime:" .. ids[i])
			local timeLeftSecs = 3600 - (os.time() - startTime) + 120

			if (timeLeftSecs < 0) then
				local pCorvette = getSceneObject(ids[i])

				if (pCorvette ~= nil) then
					self:ejectAllPlayers(pCorvette)
					createEvent(5000, "CorellianCorvette", "doCorvetteCleanup", pCorvette, "")
				end
			end
		else
			corvetteID = ids[i]
			break
		end
	end

	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:corellian_corvette_travel_fail")
		printLuaError("CorellianCorvette:activate unable to find corvette object with id " .. corvetteID)
		return false
	end

	self:startQuest(pCorvette, questType)

	local playerID = SceneObject(pPlayer):getObjectID()
	writeData(playerID .. "corvetteID", corvetteID)
	writeData(corvetteID .. ":ownerID", playerID)
	createEvent(1000, "CorellianCorvette", "transportPlayer", pPlayer, "")

	if (CreatureObject(pPlayer):isGrouped()) then
		local groupSize = CreatureObject(pPlayer):getGroupSize()

		for i = 0, groupSize - 1, 1 do
			local pMember = CreatureObject(pPlayer):getGroupMember(i)
			if pMember ~= nil and pMember ~= pPlayer and CreatureObject(pPlayer):isInRangeWithObject(pMember, 50) and not SceneObject(pMember):isAiAgent() then
				self:sendAuthorizationSui(pMember, pPlayer, pCorvette)
			end
		end
	end

	return true
end

function CorellianCorvette:getFactionCRC(faction)
	if faction == "imperial" then
		return FACTIONIMPERIAL
	elseif faction == "rebel" then
		return FACTIONREBEL
	else
		return FACTIONNEUTRAL
	end
end

function CorellianCorvette:sendAuthorizationSui(pPlayer, pLeader, pCorvette)
	if (pPlayer == nil or pCorvette == nil) then
		return
	end

	local corvetteFaction = self:getBuildingFaction(pCorvette)
	local factionCRC = self:getFactionCRC(corvetteFaction)

	if (corvetteFaction ~= "neutral" and (not ThemeParkLogic:isInFaction(factionCRC, pPlayer) or ThemeParkLogic:isOnLeave(pPlayer) or TangibleObject(pPlayer):isChangingFactionStatus())) then
		return
	end

	writeData(SceneObject(pPlayer):getObjectID() .. "corvetteID", SceneObject(pCorvette):getObjectID())

	local sui = SuiMessageBox.new("CorellianCorvette", "authorizationSuiCallback")
	sui.setTargetNetworkId(SceneObject(pCorvette):getObjectID())
	local corvetteName = getStringId("@dungeon/space_dungeon:corvette_" .. self:getBuildingFaction(pCorvette))
	sui.setTitle("Corellian Corvette")
	sui.setPrompt(CreatureObject(pLeader):getFirstName() .. " has granted you authorization to travel to " .. corvetteName ..". Do you accept this travel offer?")
	sui.setOkButtonText("Yes")
	sui.setCancelButtonText("No")

	local pageId = sui.sendTo(pPlayer)

	createEvent(30 * 1000, "CorellianCorvette", "closeAuthorizationSui", pPlayer, pageId)
end

function CorellianCorvette:authorizationSuiCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		deleteData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
		return
	end

	createEvent(1000, "CorellianCorvette", "transportPlayer", pPlayer, "")
end

function CorellianCorvette:closeAuthorizationSui(pPlayer, pageId)
	local pCorvette = self:getCorvetteObject(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local pageId = tonumber(pageId)

	if (pCorvette ~= nil and SceneObject(pCorvette):getObjectID() == readData(playerID .. "corvetteID")) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):removeSuiBox(pageId)

	deleteData(playerID .. "corvetteID")
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
				CreatureObject(pMobile):setOptionBit(IGNORE_FACTION_STANDING)
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

	local questType = readStringData("corvetteQuestType:" .. SceneObject(pCorvette):getObjectID())

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

	local pH3P0 = spawnMobile("dungeon1", "protocol_droid_h6p0", 0, SceneObject(pDroid):getPositionX() + 1, SceneObject(pDroid):getPositionZ(), SceneObject(pDroid):getPositionY() + 2, 0, cellId)

	if (pH3P0 == nil) then
		return
	end

	writeData(corvetteID .. ":H3P0ID", SceneObject(pH3P0):getObjectID())

	for i = 1, #self.electricTrapLocs, 1 do
		local trapLoc = self.electricTrapLocs[i]
		local pTrap = spawnSceneObject("dungeon1", "object/static/particle/pt_poi_electricity_2x2.iff", trapLoc.x, trapLoc.z, trapLoc.y, cellId, 1, 0, 0, 0)

		if pTrap ~= nil then
			local trapID = SceneObject(pTrap):getObjectID()
			writeData(corvetteID .. ":electricTrap" .. i, trapID)
			local pTrapArea = spawnActiveArea("dungeon1", "object/active_area.iff", SceneObject(pTrap):getWorldPositionX(), SceneObject(pTrap):getWorldPositionZ(), SceneObject(pTrap):getWorldPositionY(), 4, cellId)

			if pTrapArea ~= nil then
				writeData(trapID .. ":trapArea", SceneObject(pTrapArea):getObjectID())
				createObserver(ENTEREDAREA, "CorellianCorvette", "notifyTrapAreaEntered", pTrapArea)
			end
		end
	end

	createObserver(DESTINATIONREACHED, "CorellianCorvette", "repairDroidDestinationReached", pDroid)
	SceneObject(pDroid):setContainerComponent("corvetteBrokenDroidContainerComponent")

	AiAgent(pDroid):setAiTemplate("idlewait") -- Don't move unless patrol point is added to list
	AiAgent(pDroid):setFollowState(4) -- Patrolling

	writeData(corvetteID .. ":electricTrapEnabled", 1)
end

function CorellianCorvette:startRepairDroidMovement(pDroid)
	local pCorvette = self:getCorvetteObject(pDroid)

	if (pCorvette == nil) then
		return
	end

	local pCell = BuildingObject(pCorvette):getNamedCell("thrustersubroom28")

	if (pCell == nil) then
		return
	end

	local cellId = SceneObject(pCell):getObjectID()

	AiAgent(pDroid):stopWaiting()
	AiAgent(pDroid):setWait(0)
	AiAgent(pDroid):setNextPosition(-2.6, -14, -36.35, cellId)
	AiAgent(pDroid):executeBehavior()
end

function CorellianCorvette:repairDroidDestinationReached(pDroid)
	if (pDroid == nil) then
		return 1
	end

	createEvent(3 * 1000, "CorellianCorvette", "startRepairDroidRepairing", pDroid, "")

	return 1
end

function CorellianCorvette:startRepairDroidRepairing(pDroid)
	local pCorvette = self:getCorvetteObject(pDroid)

	if (pCorvette == nil) then
		return 1
	end

	local corvetteID = BuildingObject(pCorvette):getObjectID()
	CreatureObject(pDroid):doAnimation("sp_10")

	createEvent(3 * 1000, "CorellianCorvette", "removeElectricTrap", pCorvette, "")
end

function CorellianCorvette:removeElectricTrap(pCorvette)
	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()

	for i = 1, #self.electricTrapLocs, 1 do
		local trapID = readData(corvetteID .. ":electricTrap" .. i)
		local areaID = readData(trapID .. ":trapArea")

		local pArea = getSceneObject(areaID)

		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end

		local pTrap = getSceneObject(trapID)

		if (pTrap ~= nil) then
			SceneObject(pTrap):destroyObjectFromWorld()
		end

		deleteData(trapID .. ":trapArea")
		deleteData(corvetteID .. ":electricTrap" .. i)
	end

	local H3POID = readData(corvetteID .. ":H3P0ID")
	local pH3PO = getSceneObject(H3POID)

	if (pH3PO ~= nil) then
		spatialChat(pH3PO, "@dungeon/corvette:pdroid_congrats")
		writeData(corvetteID.. ":repairDroidComplete", 1)
	end
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

function CorellianCorvette:setupPrisoner(pPrisoner)
	local pCorvette = self:getCorvetteObject(pPrisoner)

	if (pCorvette == nil) then
		return
	end

	createObserver(DESTINATIONREACHED, "CorellianCorvette", "prisonerDestinationReached", pPrisoner)
	AiAgent(pPrisoner):setAiTemplate("idlewait") -- Don't move unless patrol point is added to list
	AiAgent(pPrisoner):setFollowState(4) -- Patrolling

	if (SceneObject(pPrisoner):getObjectName() == "prisoner") then
		CreatureObject(pPrisoner):setOptionBit(CONVERSABLE)
		local corvetteFaction = self:getBuildingFaction(pCorvette)

		if (corvetteFaction == "neutral") then
			AiAgent(pPrisoner):setConvoTemplate("corvetteNeutralPrisonerConvoTemplate")
		elseif (corvetteFaction == "imperial") then
			AiAgent(pPrisoner):setConvoTemplate("corvetteImperialPrisonerConvoTemplate")
		elseif (corvetteFaction == "rebel") then
			AiAgent(pPrisoner):setConvoTemplate("corvetteRebelPrisonerConvoTemplate")
		end
	end
end

function CorellianCorvette:doPrisonerEscape(pPrisoner)
	local pCorvette = self:getCorvetteObject(pPrisoner)

	if (pCorvette == nil) then
		return
	end

	local pCell = BuildingObject(pCorvette):getNamedCell("elevator57")

	if (pCell == nil) then
		return
	end

	createEvent(60 * 1000, "CorellianCorvette", "removePrisoner", pPrisoner, "")

	local cellId = SceneObject(pCell):getObjectID()

	AiAgent(pPrisoner):stopWaiting()
	AiAgent(pPrisoner):setWait(0)
	AiAgent(pPrisoner):setNextPosition(-18.1, 0, 117.7, cellId)
	AiAgent(pPrisoner):executeBehavior()
end

function CorellianCorvette:prisonerDestinationReached(pPrisoner)
	if (pPrisoner == nil) then
		return 1
	end

	createEvent(2 * 1000, "CorellianCorvette", "removePrisoner", pPrisoner, "")

	return 1
end

function CorellianCorvette:removePrisoner(pPrisoner)
	if (pPrisoner == nil) then
		return
	end

	deleteData(SceneObject(pPrisoner):getObjectID() .. ":alreadyRescued")
	SceneObject(pPrisoner):destroyObjectFromWorld()
end

function CorellianCorvette:setupRoomPanel(pPanel, room)
	if (pPanel == nil or room == "") then
		return
	end

	SceneObject(pPanel):setObjectMenuComponent("CorvetteRoomPanelMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyRoomPanelRemovedFromZone", pPanel)
	writeStringData(SceneObject(pPanel):getObjectID() .. ":panelRoom", room)
end

function CorellianCorvette:notifyRoomPanelRemovedFromZone(pPanel)
	if (pPanel == nil) then
		return 1
	end

	local panelID = SceneObject(pPanel):getObjectID()

	deleteStringData(panelID .. ":panelRoom")
	deleteData(panelID .. ":roomUnlocked")

	return 1
end

function CorellianCorvette:setupKeypad(pKeypad, room)
	if (pKeypad == nil or room == "") then
		return
	end

	SceneObject(pKeypad):setObjectMenuComponent("CorvetteKeypadMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyKeypadRemovedFromZone", pKeypad)
	writeStringData(SceneObject(pKeypad):getObjectID() .. ":keypadRoom", room)
end

function CorellianCorvette:notifyKeypadRemovedFromZone(pKeypad)
	if (pKeypad == nil) then
		return 1
	end

	local keypadID = SceneObject(pKeypad):getObjectID()

	deleteStringData(keypadID .. ":keypadRoom")

	return 1
end

function CorellianCorvette:setupDestroyTerminal(pTerminal, type)
	if (pTerminal == nil or type == "") then
		return
	end

	SceneObject(pTerminal):setObjectMenuComponent("CorvetteDestroyTerminalMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyDestroyTerminalRemovedFromZone", pTerminal)
	writeStringData(SceneObject(pTerminal):getObjectID() .. ":terminalType", type)
end

function CorellianCorvette:notifyDestroyTerminalRemovedFromZone(pTerminal)
	if (pTerminal == nil) then
		return 1
	end

	local keypadID = SceneObject(pTerminal):getObjectID()

	deleteStringData(keypadID .. ":terminalType")

	return 1
end

function CorellianCorvette:setupComputerObject(pComputer, label)
	if (pComputer == nil or label == "") then
		return
	end

	SceneObject(pComputer):setObjectMenuComponent("CorvetteComputerMenuComponent")
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyComputerRemovedFromZone", pComputer)
	writeStringData(SceneObject(pComputer):getObjectID() .. ":computerLabel", label)
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

	-- TODO: pick random spot in room for spawn loc once we can find random good room location
	local pMobile = spawnMobile("dungeon1", spawnTemplate, 0, SceneObject(pComputer):getPositionX(), SceneObject(pComputer):getPositionZ(), SceneObject(pComputer):getPositionY(), 0, SceneObject(pComputer):getParentID())

end

function CorellianCorvette:notifyComputerRemovedFromZone(pComputer)
	if (pComputer == nil) then
		return 1
	end

	local computerID = SceneObject(pComputer):getObjectID()

	deleteStringData(computerID .. ":computerLabel")
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
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyPodRemovedFromZone", pPod)

	local pActiveArea = spawnActiveArea("dungeon1", "object/active_area.iff", SceneObject(pPod):getWorldPositionX(), SceneObject(pPod):getWorldPositionZ(), SceneObject(pPod):getWorldPositionY(), 3, SceneObject(pPod):getParentID())

	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "CorellianCorvette", "notifyEnteredEscapePodArea", pActiveArea)
		writeData(SceneObject(pPod):getObjectID() .. ":areaID", SceneObject(pActiveArea):getObjectID())
	end
end

function CorellianCorvette:notifyPodRemovedFromZone(pPod)
	if (pPod == nil) then
		return 1
	end

	local podID = SceneObject(pPod):getObjectID()
	local areaID = readData(podID .. ":areaID")

	local pArea = getSceneObject(areaID)

	if (pArea ~= nil) then
		SceneObject(pArea):destroyObjectFromWorld()
	end

	deleteData(podID .. ":areaID")

	return 1
end

function CorellianCorvette:notifyPodRadialUsed(pPod, pPlayer, radialSelected)
	if (pPod == nil) then
		return 1
	end

	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature() or not CreatureObject(pPlayer):isInRangeWithObject(pPod, 4)) then
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

function CorellianCorvette:setupLootCrate(pCrate, type)
	if (pCrate == nil) then
		return
	end

	local pCorvette = self:getCorvetteObject(pCrate)

	if (pCorvette == nil) then
		return
	end

	local faction = self:getBuildingFaction(pCorvette)

	if (type == "r2") then
		createLoot(pCrate, "r2droid_loot", 1, false)
	elseif (type == "disk") then
		createLoot(pCrate, "disk_loot", 1, false)
	else
		createLoot(pCrate, faction .. "_corvette_loot", 300, false)
	end

	SceneObject(pCrate):setContainerInheritPermissionsFromParent(false)
	SceneObject(pCrate):setContainerDefaultDenyPermission(MOVEIN)
	SceneObject(pCrate):setContainerDefaultAllowPermission(OPEN + MOVEOUT)

	writeStringData(SceneObject(pCrate):getObjectID() .. ":crateType", type)
	createObserver(OBJECTREMOVEDFROMZONE, "CorellianCorvette", "notifyLootCrateRemovedFromZone", pCrate)
	SceneObject(pCrate):setContainerComponent("corvetteLootCrateContainerComponent")
end

function CorellianCorvette:onCrateLooted(pCrate)
	if (pCrate == nil) then
		return
	end

	local pCorvette = self:getCorvetteObject(pCrate)

	if (pCorvette == nil) then
		return
	end

	local crateID = SceneObject(pCrate):getObjectID()
	local crateType = readStringData(crateID .. ":crateType")

	if (crateType == "r2") then
		createEvent(600 * 1000, "CorellianCorvette", "setupLootCrate", pCrate, "r2")
	elseif (crateType ~= "disk" and readData(crateID .. ":crateLooted") ~= 1) then
		writeData(crateID .. ":crateLooted", 1)
		local faction = self:getBuildingFaction(pCorvette)
		local spawnTemplate

		if (faction == "neutral") then
			spawnTemplate = "corsec_super_battle_droid"
		elseif (faction == "imperial") then
			spawnTemplate = "rebel_super_battle_droid"
		elseif (faction == "rebel") then
			spawnTemplate =  "imperial_super_battle_droid"
		end
		-- TODO: pick random spot in room for spawn loc once we can find random good room location
		local pMobile = spawnMobile("dungeon1", spawnTemplate, 0, SceneObject(pCrate):getPositionX(), SceneObject(pCrate):getPositionZ(), SceneObject(pCrate):getPositionY(), 0, SceneObject(pCrate):getParentID())
	end

	writeData(crateID .. ":crateLooted", 1)
end

function CorellianCorvette:notifyLootCrateRemovedFromZone(pCrate)
	if (pCrate == nil) then
		return 1
	end

	local crateID = SceneObject(pCrate):getObjectID()

	deleteStringData(crateID .. ":crateType")
	deleteData(crateID .. ":crateLooted")

	return 1
end

function CorellianCorvette:transportPlayer(pPlayer)
	if pPlayer == nil then
		return
	end

	-- Make sure the player had no data left over from a previous corvette
	self:doPlayerCleanup(pPlayer)

	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")

	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		printLuaError("CorellianCorvette:transportPlayer nil corvette object using corvette id " .. corvetteID)
		return
	end

	local corvetteFaction = self:getBuildingFaction(pCorvette)
	local factionCRC = self:getFactionCRC(corvetteFaction)

	if (corvetteFaction ~= "neutral" and (not ThemeParkLogic:isInFaction(factionCRC, pPlayer) or ThemeParkLogic:isOnLeave(pPlayer) or TangibleObject(pPlayer):isChangingFactionStatus())) then
		return
	end

	local pCell = BuildingObject(pCorvette):getCell(1)

	if (pCell == nil) then
		return
	end

	local cellID = SceneObject(pCell):getObjectID()
	SceneObject(pPlayer):switchZone("dungeon1", -42.9, 0, 0.1, cellID)
end

function CorellianCorvette:startQuest(pCorvette, questType)
	local dungeonID = self:getNewDungeonID()
	local corvetteID = SceneObject(pCorvette):getObjectID()
	writeData("corvetteDungeonID:" .. corvetteID, dungeonID)
	writeData("corvetteActive:" .. corvetteID, 1)
	writeData("corvetteStartTime:" .. corvetteID, os.time())
	writeStringData("corvetteQuestType:" .. corvetteID, questType)
	createEvent(5 * 60 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")

	self:setupSceneObjects(pCorvette)
	self:spawnNpcs(pCorvette)
	self:lockRooms(pCorvette)
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
	if not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

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

	return 0
end

function CorellianCorvette:onExitCorvette(pCorvette, pPlayer)
	if not SceneObject(pPlayer):isPlayerCreature() then
		return 0
	end

	local playerCount = readData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID())
	writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), playerCount - 1)

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
	elseif (timeLeft >= 3) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_" .. timeLeft)
		createEvent(60 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	elseif (timeLeft >= 2) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_" .. timeLeft)
		createEvent(30 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	elseif (timeLeftSecs >= 90) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_90s")
		createEvent(30 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	elseif (timeLeftSecs >= 60) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_1")
		createEvent(30 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	elseif (timeLeftSecs >= 30) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_30s")
		createEvent(20 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	elseif (timeLeftSecs >= 10) then
		self:broadcastToPlayers(pCorvette, "@dungeon/corvette:timer_10s")
		createEvent(10 * 1000, "CorellianCorvette", "handleCorvetteTimer", pCorvette, "")
	else
		self:handleQuestFailure(pCorvette)
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
	self:ejectAllPlayers(pCorvette)
	createEvent(5000, "CorellianCorvette", "doCorvetteCleanup", pCorvette, "")
end

function CorellianCorvette:handleQuestSuccess(pCorvette)
	self:broadcastToPlayers(pCorvette, "@dungeon/corvette:escape_pods") -- You have completed your assignment! Make your way to the escape pods before time expires and get off this ship!
	self:writeDataToGroup(pCorvette, ":corvetteMissionComplete", 1)
	self:giveBadgeToGroup(pCorvette)
end

function CorellianCorvette:giveBadgeToGroup(pCorvette)
	local corvetteFaction = self:getBuildingFaction(pCorvette)
	local questType = readStringData("corvetteQuestType:" .. SceneObject(pCorvette):getObjectID())
	local missionType = corvetteFaction .. "_" .. questType
	local badgeNum = self.missionBadges[missionType]

	if (badgeNum == nil) then
		printLuaError("Invalid mission type " .. missionType .. " trying to get Corellian Corvette badge.")
		return
	end

	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
					local pGhost = CreatureObject(pObject):getPlayerObject()

					if (pGhost ~= nil and not PlayerObject(pGhost):hasBadge(badgeNum)) then
						PlayerObject(pGhost):awardBadge(badgeNum)
					end
				end
			end
		end
	end
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

function CorellianCorvette:increaseGroupFactionStanding(pCorvette, faction, points)
	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)

				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
					local pGhost = CreatureObject(pObject):getPlayerObject()

					if (pGhost ~= nil) then
						PlayerObject(pGhost):increaseFactionStanding(faction, points)
					end
				end
			end
		end
	end
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
		printLuaError("CorellianCorvette:ejectPlayer unable to find corvette object")
		return
	end

	local faction = self:getBuildingFaction(pCorvette)

	for i = 1, #self.escapePoints, 1 do
		if self.escapePoints[i].faction == faction then
			point = self.escapePoints[i]
		end
	end

	if point == nil then
		printLuaError("CorellianCorvette:ejectPlayer was unable to grab an escape point for faction: " .. faction)
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local ownerID = readData(SceneObject(pCorvette):getObjectID() .. ":ownerID")

	if (readData(playerID .. ":corvetteMissionComplete") == 1) then
		local questType = readStringData("corvetteQuestType:" .. SceneObject(pCorvette):getObjectID())
		local missionType = faction .. "_" .. questType
		writeData(playerID .. ":corvetteComplete:" .. missionType, 1)
	end

	if (playerID == ownerID) then
		if (readData(playerID .. ":corvetteMissionComplete") == 1) then
			setQuestStatus(playerID .. ":activeCorvetteStep", "3")
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:reward") -- You have done well. Return to the person who gave you this assignment and receive your reward.
			deleteData(playerID .. ":corvetteMissionComplete")
		else
			removeQuestStatus(playerID .. ":activeCorvetteQuest")
			removeQuestStatus(playerID .. ":activeCorvetteStep")
			removeQuestStatus(playerID .. ":activeCorvetteQuestType")
		end
	end

	if (isZoneEnabled(point.planet)) then
		SceneObject(pPlayer):switchZone(point.planet, point.x, 0, point.y, 0)
	else
		printLuaError("CorellianCorvette:ejectPlayer attempted to eject a player to a zone that was not enabled.")
	end

	self:doPlayerCleanup(pPlayer)
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

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/corellian_corvette/bootdisk.iff", true)

		if (pItem ~= nil) then
			SceneObject(pItem):destroyObjectFromWorld()
			SceneObject(pItem):destroyObjectFromDatabase()
		end

		pItem = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/droid_maint_module.iff", true)

		if (pItem ~= nil) then
			SceneObject(pItem):destroyObjectFromWorld()
			SceneObject(pItem):destroyObjectFromDatabase()
		end
	end
end

function CorellianCorvette:doCorvetteCleanup(pCorvette)
	if (pCorvette == nil) then
		return
	end

	local corvetteID = SceneObject(pCorvette):getObjectID()

	for i = 1, #self.electricTrapLocs, 1 do
		local trapID = readData(corvetteID .. ":electricTrap" .. i)
		local areaID = readData(trapID .. ":trapArea")

		local pArea = getSceneObject(areaID)

		if (pArea ~= nil) then
			SceneObject(pArea):destroyObjectFromWorld()
		end

		local pTrap = getSceneObject(trapID)

		if (pTrap ~= nil) then
			SceneObject(pTrap):destroyObjectFromWorld()
		end

		deleteData(trapID .. ":trapArea")
		deleteData(corvetteID .. ":electricTrap" .. i)
	end

	for i = 1, 66, 1 do
		local pCell = BuildingObject(pCorvette):getCell(i)

		if (pCell ~= nil) then
			for j = SceneObject(pCell):getContainerObjectsSize() - 1, 0, -1 do
				local pObject = SceneObject(pCell):getContainerObject(j)

				if pObject ~= nil and not SceneObject(pObject):isPlayerCreature() then
					SceneObject(pObject):destroyObjectFromWorld()
				end
			end
		end
	end

	deleteData(corvetteID .. ":fuelSetting")
	deleteData(corvetteID .. ":engineSetting")
	deleteData(corvetteID .. ":hyperdriveSetting")
	deleteData(corvetteID .. ":engineDestroyed")
	deleteData(corvetteID .. ":electricTrapEnabled")
	deleteData(corvetteID .. ":H3P0ID")
	deleteData(corvetteID .. ":repairDroidComplete")
	deleteData(corvetteID .. ":ownerID")
	deleteData("corvetteActive:" .. corvetteID)
	deleteData("corvetteDungeonID:" .. corvetteID)
	deleteData("corvetteStartTime:" .. corvetteID)
end

function CorellianCorvette:getNewDungeonID()
	local lastID = tonumber(getQuestStatus("CorellianCorvette:lastDungeonID"))
	local newID = 0

	if (lastID == nil or lastID == 0) then
		newID = 1
	else
		newID = lastID + 1
	end

	setQuestStatus("CorellianCorvette:lastDungeonID", newID)

	return newID
end

function CorellianCorvette:getCorvetteFromDungeonID(dungeonID)
	local corvetteID = 0
	for i = 1, #self.buildings, 1 do
		local buildingIds = self.buildings[i]

		for j = 1, #buildingIds, 1 do
			local buildingID = buildingIds[j]

			if (readData("corvetteDungeonID:" .. buildingID) == dungeonID) then
				corvetteID = buildingID
			end
		end
	end

	return getSceneObject(corvetteID)
end
