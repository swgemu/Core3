Warren = ScreenPlay:new {
	suiTerminals = {
		{ 8575768, "welcome_terminal", "" },
		{ 8575769, "comm_terminal", "comm_terminal_name" },
		{ 8575770, "diary_terminal", "diary_terminal_name" },
		{ 8575773, "turret_pass_active", "turret_term_on" },
		{ 8465579, "cell_locked", "" }
	},

	evidenceContainers = {
		{ 8465570, "warren_evidence_01" },
		{ 8465585, "warren_evidence_02" },
		{ 8465590, "warren_evidence_03" },
		{ 8465591, "warren_evidence_04" },
		{ 8465584, "warren_encryption_key" }
	},

	questContainers = {
		{ 8465549, "warren_farewell_letter" },
		{ 8465550, "warren_controlroom_passkey1" },
		{ 8555708, "warren_controlroom_passkey2" },
		{ 8555709, "warren_controlroom_passkey3" },
		{ 8555710, "warren_controlroom_passkey4" },
		{ 8465551, "warren_turret_sequence" },
		{ 8465598, "warren_core_control_rod_s01" },
		{ 8465597, "warren_core_control_rod_s02" },
		{ 8465580, "warren_inquisitor_letter" }
	},
}

registerScreenPlay("Warren", true)

function Warren:start()
	if (isZoneEnabled("dantooine")) then
		local pWarren = self:getBuildingObject()

		if (pWarren == nil) then
			return
		end

		createObserver(ENTEREDBUILDING, "Warren", "notifyEnteredWarren", pWarren)
		createObserver(EXITEDBUILDING, "Warren", "notifyExitedWarren", pWarren)

		self:spawnMobiles()
		self:spawnTurret()
		self:resetPasswords()
		self:spawnDebris()
		self:setupReactorSwitches()
		self:setupMcrTerminals()
		self:setupSuiTerminals()
		self:setupEvidenceContainers()
		self:setupQuestContainers()
		self:setupReactorCore()
		self:spawnCellGuard()
		self:spawnDoctorKnag()
		self:spawnKitchenOfficer()

		self:lockAllRooms()
	end
end

function Warren:lockAllRooms()
	-- Command center
	local pCell = self:getCell("plusroom84")

	if (pCell ~= nil) then
		self:lockRoom(pCell)
	end

	-- Inquisitor room
	local pCell = self:getCell("smallroom47")

	if (pCell ~= nil) then
		self:lockRoom(pCell)
	end

	-- Reactor core
	local pCell = self:getCell("smallroom44")

	if (pCell ~= nil) then
		self:lockRoom(pCell)
	end
end

function Warren:spawnKitchenOfficer()
	local mobileID = readData("warren:kitchenOfficerID")

	local pMobile = getSceneObject(mobileID)

	if (pMobile ~= nil and not CreatureObject(pMobile):isDead()) then
		createEvent(1800 * 1000, "Warren", "spawnKitchenOfficer", pMobile, "")
		return
	end

	pMobile = spawnMobile("dantooine", "warren_imperial_officer", 0, -36.97, -52, -94.43, 90, 8575712)

	if (pMobile == nil) then
		return
	end

	createObserver(OBJECTDESTRUCTION, "Warren", "onKitchenOfficerKilled", pMobile)

	writeData("warren:kitchenOfficerID", SceneObject(pMobile):getObjectID())

	local pActiveArea = spawnActiveArea("dantooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), 15, 8575712)

	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "Warren", "notifyEnteredKitchenOfficerArea", pActiveArea)
	end
end

function Warren:notifyEnteredKitchenOfficerArea(pActiveArea, pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local mobileID = readData("warren:kitchenOfficerID")
	local pMobile = getSceneObject(mobileID)

	if (pMobile == nil) then
		return 1
	end

	if (CreatureObject(pPlayer):getGender() == 0) then
		spatialChat(pMobile, "@theme_park/warren/warren:trooper_greeting_m") -- There's another one of Teraud's people... kill him!
	else
		spatialChat(pMobile, "@theme_park/warren/warren:trooper_greeting_f") -- There's another one of Teraud's people... kill her!
	end

	CreatureObject(pMobile):engageCombat(pPlayer)

	return 1
end

function Warren:onKitchenOfficerKilled(pMobile, pPlayer)
	createEvent(1800 * 1000, "Warren", "spawnKitchenOfficer", pMobile, "")

	return 1
end

function Warren:spawnDoctorKnag()
	local mobileID = readData("warren:doctorKnagID")

	local pMobile = getSceneObject(mobileID)

	if (pMobile ~= nil and not CreatureObject(pMobile):isDead()) then
		createEvent(1800 * 1000, "Warren", "spawnDoctorKnag", pMobile, "")
		return
	end

	pMobile = spawnMobile("dantooine", "doctor_knag", 0, 77.47, -68, 38.95, 90, 8575737)

	if (pMobile == nil) then
		return
	end

	createObserver(OBJECTDESTRUCTION, "Warren", "onDoctorKnagKilled", pMobile)

	writeData("warren:doctorKnagID", SceneObject(pMobile):getObjectID())

	local pActiveArea = spawnActiveArea("dantooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), 10, 8575737)

	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "Warren", "notifyEnteredDoctorKnagArea", pActiveArea)
	end
end

function Warren:notifyEnteredDoctorKnagArea(pActiveArea, pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local mobileID = readData("warren:doctorKnagID")
	local pMobile = getSceneObject(mobileID)

	if (pMobile == nil) then
		return 1
	end

	spatialChat(pMobile, "@theme_park/warren/warren:knag_greeting") -- My children... they'll take over the facility, and kill those Stormtroopers... then Teraud will have to admit that I am smarter than he is... that I am the one that will one day rule!
	CreatureObject(pMobile):engageCombat(pPlayer)

	return 1
end

function Warren:onDoctorKnagKilled(pMobile, pPlayer)
	createEvent(1800 * 1000, "Warren", "spawnDoctorKnag", pMobile, "")

	return 1
end

function Warren:onCellGuardKilled(pMobile, pPlayer)
	createEvent(1800 * 1000, "Warren", "spawnCellGuard", pMobile, "")

	return 1
end

function Warren:spawnCellGuard()
	local mobileID = readData("warren:cellGuardID")

	local pMobile = getSceneObject(mobileID)

	if (pMobile ~= nil and not CreatureObject(pMobile):isDead()) then
		createEvent(1800 * 1000, "Warren", "spawnCellGuard", pMobile, "")
		return
	end

	pMobile = spawnMobile("dantooine", "jerrd_sonclim", 0, 27.35, -50, -149.01, -140, 8575717)

	if (pMobile == nil) then
		return
	end

	SceneObject(pMobile):setCustomObjectName("theme_park/warren/warren_system_messages", "name_jerrd")

	createObserver(OBJECTDESTRUCTION, "Warren", "onCellGuardKilled", pMobile)

	writeData("warren:cellGuardID", SceneObject(pMobile):getObjectID())

	local pActiveArea = spawnActiveArea("dantooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), 15, 8575717)

	if pActiveArea ~= nil then
		writeData(SceneObject(pActiveArea):getObjectID() .. ":areaType", 1)
		createObserver(ENTEREDAREA, "Warren", "notifyEnteredCellGuardArea", pActiveArea)
	end

	pActiveArea = spawnActiveArea("dantooine", "object/active_area.iff", SceneObject(pMobile):getWorldPositionX(), SceneObject(pMobile):getWorldPositionZ(), SceneObject(pMobile):getWorldPositionY(), 8, 8575717)

	if pActiveArea ~= nil then
		writeData(SceneObject(pActiveArea):getObjectID() .. ":areaType", 2)
		createObserver(ENTEREDAREA, "Warren", "notifyEnteredCellGuardArea", pActiveArea)
	end
end

function Warren:onCellGuardKilled(pMobile, pPlayer)
	createEvent(1800 * 1000, "Warren", "spawnCellGuard", pMobile, "")

	return 1
end

function Warren:notifyEnteredCellGuardArea(pActiveArea, pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local mobileID = readData("warren:cellGuardID")
	local pMobile = getSceneObject(mobileID)

	if (pMobile == nil) then
		return 1
	end

	local areaID = SceneObject(pActiveArea):getObjectID()
	local areaType = readData(areaID .. ":areaType")

	if (areaType == 1) then
		spatialChat(pMobile, "@theme_park/warren/warren:guard_warning") -- I'm guarding this cell so you better not come any closer. Just head back the way you came and I won't have to kill you. Go on! You can't open this cell without the password anyway, and I'm sure not going to give it to you. Now get out of here.
	else
		CreatureObject(pMobile):engageCombat(pPlayer)
	end

	deleteData(areaID .. ":areaType")

	return 1
end

function Warren:notifyExitedWarren(pBuilding, pPlayer)
	if (pBuilding == nil or pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	dropObserver(SPATIALCHATSENT, "Warren", "notifyTerminalChatSent", pPlayer)
	dropObserver(PARENTCHANGED, "Warren", "notifyPlayerChangedCell", pPlayer)

	-- Check the building for players, only resetting passwords if the dungeon is empty
	for i = 1, BuildingObject(pBuilding):getTotalCellNumber(), 1 do
		local pCell = BuildingObject(pBuilding):getCell(i)

		if (pCell ~= nil) then
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
					return 0
				end
			end
		end
	end

	self:resetPasswords()

	return 0
end

function Warren:notifyEnteredWarren(pBuilding, pPlayer)
	if (pBuilding == nil or pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_passkey_s01.iff", true)

		if (pItem ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/warren/warren_system_messages:access_granted") --ACCESS GRANTED: Passkey code accepted. Welcome to this Imperial Research Facility
			dropObserver(SPATIALCHATSENT, "Warren", "notifyTerminalChatSent", pPlayer)
			createObserver(SPATIALCHATSENT, "Warren", "notifyTerminalChatSent", pPlayer, 1)
			dropObserver(PARENTCHANGED, "Warren", "notifyPlayerChangedCell", pPlayer)
			createObserver(PARENTCHANGED, "Warren", "notifyPlayerChangedCell", pPlayer, 1)

			local pParent = SceneObject(pPlayer):getParent()

			if (pParent ~= nil) then
				local cellNum = LuaCellObject(pParent):getCellNumber()
				local cellName = BuildingObject(pBuilding):getCellName(cellNum)

				if (cellName == "plusroom84") then
					SceneObject(pPlayer):teleport(79.7, -60, -43.3, 8575749)
				elseif (cellName == "smallroom47") then
					SceneObject(pPlayer):teleport(23.4, -50, -148.9, 8575717)
				elseif (cellName == "smallroom44") then
					SceneObject(pPlayer):teleport(46.4, -54, -125.5, 8575714)
				end
			end
		else
			CreatureObject(pPlayer):sendSystemMessage("@theme_park/warren/warren_system_messages:access_denied") --ACCESS DENIED:  YOU DO NOT HAVE THE PROPER PASSKEY TO ENTER THIS FACILITY
			--Kick them out to the front door.
			SceneObject(pPlayer):teleport(-556, 1, -3820, 0)
		end
	end

	return 0
end

function Warren:notifyPlayerChangedCell(pPlayer)
	if (pPlayer == nil or SceneObject(pPlayer):getParentID() == 0) then
		return 1
	end

	local pParent = SceneObject(pPlayer):getParent()

	if (pParent == nil) then
		return 1
	end

	local pWarren = self:getBuildingObject()

	if (pWarren == nil) then
		return 1
	end

	local cellNum = LuaCellObject(pParent):getCellNumber()

	local cellName = BuildingObject(pWarren):getCellName(cellNum)

	if (cellName == "smallroom78" or cellName == "plusroom84") then -- Command center
		local pCell = self:getCell("plusroom84")

		if (pCell ~= nil) then
			if (readData("warren:reactorOverride") == 1) then
				self:unlockRoom(pCell)
			else
				CreatureObject(pPlayer):sendSystemMessage("@theme_park/warren/warren_system_messages:core_warning") --WARNING: Reactor Core Overload Imminent. Control Center Lock-Down initiated.
				self:lockRoom(pCell)
			end
		end
	elseif (cellName == "smallroom47" or cellName == "smallroom46") then -- Inquisitor room
		local pCell = self:getCell("smallroom47")

		if (pCell ~= nil) then
			if (readData("warren:inquisitorRoomOpened") == 1) then
				self:unlockRoom(pCell)
			else
				self:lockRoom(pCell)
			end
		end
	elseif (cellName == "smallroom44" or cellName == "bigroom43") then -- Reactor core
		local pCell = self:getCell("smallroom44")

		if (pCell ~= nil) then
			if (readData("warren:reactorUnlocked") == 1) then
				self:unlockRoom(pCell)
			else
				self:lockRoom(pCell)
			end
		end
	end

	return 0
end

function Warren:isInWarren(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local parentID = SceneObject(pPlayer):getParentID()

	if (parentID == 0) then
		return false
	end

	local pParent = getSceneObject(parentID)

	if (pParent == nil) then
		return false
	end

	local buildingID = SceneObject(pParent):getParentID()

	return buildingID == 8575671
end

function Warren:setupReactorCore()
	local pCore = getSceneObject(6525464)

	if (pCore == nil) then
		return
	end

	SceneObject(pCore):setCustomObjectName("theme_park/warren/warren_system_messages", "core_name_on")
	createObserver(OBJECTRADIALOPENED, "Warren", "reactorCoreUsed", pCore)
	createObserver(OPENCONTAINER, "Warren", "reactorCoreUsed", pCore)

	local pCore = SceneObject(pCore):getSlottedObject("inventory")

	if (pCore ~= nil) then
		for j = 1, SceneObject(pCore):getContainerObjectsSize(), 1 do
			local pObject = SceneObject(pCore):getContainerObject(j - 1)

			if (pObject ~= nil) then
				SceneObject(pObject):destroyObjectFromWorld()
				SceneObject(pObject):destroyObjectFromDatabase()
			end
		end
	end
end

function Warren:reactorCoreUsed(pCore, pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	if (pCore == nil or not CreatureObject(pPlayer):isInRangeWithObject(pCore, 5)) then
		return 0
	end

	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return 0
	end

	for i = 1, 2, 1 do
		local templateName = "object/tangible/mission/quest_item/warren_core_control_rod_s0" .. i .. ".iff"
		local pRod = getContainerObjectByTemplate(pInventory, templateName, true)

		if (pRod ~= nil and not getContainerObjectByTemplate(pCore, templateName, true)) then
			SceneObject(pRod):destroyObjectFromWorld()
			SceneObject(pRod):destroyObjectFromDatabase()

			local pNewRod = giveItem(pCore, templateName, -1)

			if (pNewRod ~= nil) then
				CreatureObject(pPlayer):sendSystemMessage("@theme_park/warren/warren_system_messages:insert_rod") --You insert the reactor core control rods into the reactor core.
			end
		end
	end

	local numRods = 0

	for i = 1, 2, 1 do
		local templateName = "object/tangible/mission/quest_item/warren_core_control_rod_s0" .. i .. ".iff"

		if (getContainerObjectByTemplate(pCore, templateName, true)) then
			numRods = numRods + 1
		end
	end

	if (numRods > 1) then
		local pCell = self:getCell("plusroom84")

		if (pCell ~= nil) then
			self:unlockRoom(pCell)
		end

		writeData("warren:reactorOverride", 1)
		SceneObject(pCore):showFlyText("theme_park/warren/warren_system_messages", "deactivate_core", 0, 255, 0)
		SceneObject(pCore):setCustomObjectName("theme_park/warren/warren_system_messages", "core_name_off")
		createEvent(3600 * 1000, "Warren", "reactivateCore", pCore, "")

		for j = SceneObject(pCore):getContainerObjectsSize() - 1, 0, -1 do
			local pObject = SceneObject(pCore):getContainerObject(j)

			if (pObject ~= nil) then
				SceneObject(pObject):destroyObjectFromWorld()
				SceneObject(pObject):destroyObjectFromDatabase()
			end
		end
	end

	return 0
end

function Warren:reactivateCore(pCore)
	if (pCore ~= nil) then
		SceneObject(pCore):setCustomObjectName("theme_park/warren/warren_system_messages", "core_name_on")
	end

	deleteData("warren:reactorOverride")

	local pCell = self:getCell("plusroom84")

	if (pCell ~= nil) then
		self:lockRoom(pCell)
	end
end

function Warren:setupMcrTerminals()
	local pTerminal = getSceneObject(8465559)

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "mcr_term_name_on")
		createObserver(OBJECTRADIALOPENED, "Warren", "mcrTerminalUsed", pTerminal)
		writeData(SceneObject(pTerminal):getObjectID() .. ":mcrTerminalNumber", 1)
	end

	pTerminal = getSceneObject(8465560)

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "mcr_term_name_on")
		createObserver(OBJECTRADIALOPENED, "Warren", "mcrTerminalUsed", pTerminal)
		writeData(SceneObject(pTerminal):getObjectID() .. ":mcrTerminalNumber", 2)
	end

	pTerminal = getSceneObject(8465561)

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "mcr_term_name_on")
		createObserver(OBJECTRADIALOPENED, "Warren", "mcrTerminalUsed", pTerminal)
		writeData(SceneObject(pTerminal):getObjectID() .. ":mcrTerminalNumber", 3)
	end

	pTerminal = getSceneObject(8465562)

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "mcr_term_name_on")
		createObserver(OBJECTRADIALOPENED, "Warren", "mcrTerminalUsed", pTerminal)
		writeData(SceneObject(pTerminal):getObjectID() .. ":mcrTerminalNumber", 4)
	end

	pTerminal = getSceneObject(8575772)

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setObjectMenuComponent("WarrenElevatorMenuComponent")
	end
end

function Warren:setupEvidenceContainers()
	for i = 1, #self.evidenceContainers, 1 do
		local evidenceData = self.evidenceContainers[i]
		local pContainer = getSceneObject(evidenceData[1])

		if (pContainer ~= nil) then
			if (evidenceData[2] == "warren_encryption_key") then
				SceneObject(pContainer):setCustomObjectName("theme_park/warren/warren_system_messages", "dev_control_name")
			end

			SceneObject(pContainer):setObjectMenuComponent("WarrenEvidenceMenuComponent")
		end
	end
end

function Warren:setupQuestContainers()
	for i = 1, #self.questContainers, 1 do
		local questData = self.questContainers[i]
		local pContainer = getSceneObject(questData[1])

		if (pContainer ~= nil) then
			SceneObject(pContainer):setContainerComponent("WarrenQuestContainerComponent")
			writeStringData(SceneObject(pContainer):getObjectID() .. ":itemName", questData[2])

			SceneObject(pContainer):setContainerInheritPermissionsFromParent(false)
			SceneObject(pContainer):setContainerDefaultDenyPermission(MOVEIN)
			SceneObject(pContainer):setContainerDefaultAllowPermission(OPEN + MOVEOUT)

			if (SceneObject(pContainer):getContainerObjectsSize() == 0) then
				local itemTemplate = "object/tangible/mission/quest_item/" .. questData[2] .. ".iff"
				giveItem(pContainer, itemTemplate, -1)
			end
		end
	end
end

function Warren:refillQuestContainer(pContainer)
	if (pContainer == nil) then
		return
	end

	if (SceneObject(pContainer):getContainerObjectsSize() > 0) then
		return
	end

	local itemName = readStringData(SceneObject(pContainer):getObjectID() .. ":itemName")
	local itemTemplate = "object/tangible/mission/quest_item/" .. itemName .. ".iff"

	giveItem(pContainer, itemTemplate, -1)
end

function Warren:setupSuiTerminals()
	for i = 1, #self.suiTerminals, 1 do
		local terminalData = self.suiTerminals[i]
		local pTerminal = getSceneObject(terminalData[1])

		if (pTerminal ~= nil) then
			if (terminalData[3] ~= "") then
				SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", terminalData[3])
			end

			SceneObject(pTerminal):setObjectMenuComponent("WarrenTerminalMenuComponent")
		end
	end
end

function Warren:notifyTerminalChatSent(pPlayer, pChatMessage)
	if (pPlayer == nil or not self:isInWarren(pPlayer)) then
		return 1
	end

	if (pChatMessage == nil) then
		return 0
	end

	local terminalMessage = ""
	local chatMessage = getChatMessage(pChatMessage)

	if (chatMessage == nil or chatMessage == "") then
		return 0
	end

	local parentID = SceneObject(pPlayer):getParentID()
	local terminalID

	if (parentID == 8575691) then -- Turret
		terminalID = 8575773
	elseif (parentID == 8575717) then -- Inquisitor
		terminalID = 8465579
	else
		return 0
	end

	local pTerminal = getSceneObject(terminalID)

	if (pTerminal == nil or not CreatureObject(pPlayer):isInRangeWithObject(pTerminal, 10)) then
		return 0
	end

	if (terminalID == 8575773) then
		if (readData("warren:turretDisabled") == 1) then
			return 0
		end

		local turretPassword = readStringData("warren:turretPassword")

		if (string.upper(chatMessage) == turretPassword) then
			SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "turret_term_off")
			writeData("warren:turretDisabled", 1)
			SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "turret_pass_deactivated", 0, 255, 0)
			createEvent(1800 * 1000, "Warren", "reactivateTurretTerminal", pTerminal, "")

			local turretID = readData("warren:turretID")
			local pTurret = getSceneObject(turretID)

			if (pTurret ~= nil) then
				SceneObject(pTurret):destroyObjectFromWorld()
			end
		end
	else
		if (readData("warren:inquisitorRoomOpened") == 1) then
			return 0
		end

		local cellPassword = readStringData("warren:cellPassword")

		if (string.upper(chatMessage) == cellPassword) then
			writeData("warren:inquisitorRoomOpened", 1)

			pCell = self:getCell("smallroom47") -- Inquisitor room

			if (pCell ~= nil) then
				self:unlockRoom(pCell)
			end

			SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "cell_open", 0, 255, 0)
			createEvent(1800 * 1000, "Warren", "relockInquisitorRoom", pTerminal, "")
		end
	end

	return 0
end

function Warren:relockInquisitorRoom()
	deleteData("warren:inquisitorRoomOpened")

	pCell = self:getCell("smallroom47") -- Inquisitor room

	if (pCell ~= nil) then
		self:lockRoom(pCell)
	end
end

function Warren:reactivateTurretTerminal(pTerminal)
	self:spawnTurret()
	deleteData("warren:turretDisabled")

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "turret_term_on")
	end
end

function Warren:sendSuiTerminalMessage(pTerminal, pPlayer)
	if (pTerminal == nil or pPlayer == nil) then
		return
	end

	local terminalMessage = ""
	local terminalID = SceneObject(pTerminal):getObjectID()

	for i = 1, #self.suiTerminals, 1 do
		local terminalData = self.suiTerminals[i]

		if (terminalData[1] == terminalID) then
			terminalMessage = terminalData[2]
		end
	end

	if (terminalMessage == "") then
		return
	elseif (terminalMessage == "turret_pass_active") then
		if (readData("warren:turretDisabled") == 1) then
			terminalMessage = "@theme_park/warren/warren_system_messages:turret_pass_inactive"
		else
			terminalMessage = "@theme_park/warren/warren_system_messages:turret_pass_active"
		end
	elseif (terminalMessage == "cell_locked") then
		if (readData("warren:inquisitorRoomOpened") == 1) then
			terminalMessage = "@theme_park/warren/warren_system_messages:cell_open"
		else
			terminalMessage = "@theme_park/warren/warren_system_messages:cell_locked"
		end
	else
		terminalMessage = "@theme_park/warren/warren_system_messages:" .. terminalMessage
	end

	local sui = SuiMessageBox.new("Warren", "noCallback")
	sui.setTitle("@sui:swg")
	sui.setPrompt(terminalMessage)
	sui.setTargetNetworkId(SceneObject(pTerminal):getObjectID())
	sui.setForceCloseDistance(5)
	sui.sendTo(pPlayer)
end

function Warren:noCallback(pPlayer, pSui, eventIndex, ...)
end

function Warren:mcrTerminalUsed(pTerminal, pPlayer)
	if (pTerminal == nil or pPlayer == nil) then
		return 0
	end

	local terminalNum = readData(SceneObject(pTerminal):getObjectID() .. ":mcrTerminalNumber")
	local terminalDisabled = readData("warren:mcrTerminalDisabled" .. terminalNum)

	if (terminalStatus == 1) then
		SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "mcr_term_deactivated", 0, 255, 0)
		return 0
	end

	local keyTemplate = "object/tangible/mission/quest_item/warren_controlroom_passkey" .. terminalNum .. ".iff"
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil or not getContainerObjectByTemplate(pInventory, keyTemplate, true)) then
		SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "mcr_term_active", 0, 255, 0)
		return 0
	end

	SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "mcr_term_deactivated", 0, 255, 0)
	SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "mcr_term_name_off")
	writeData("warren:mcrTerminalDisabled" .. terminalNum, 1)
	createEvent(1800 * 1000, "Warren", "reactivateMcrTerminal", pTerminal, "")

	return 0
end

function Warren:reactivateMcrTerminal(pTerminal)
	if (pTerminal ~= nil) then
		local terminalNum = readData(SceneObject(pTerminal):getObjectID() .. ":mcrTerminalNumber")

		deleteData("warren:mcrTerminalDisabled" .. terminalNum)
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "mcr_term_name_on")
	end
end

function Warren:setupReactorSwitches()
	local pTerminal = getSceneObject(8465583)

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "switch_name_1")
		createObserver(OBJECTRADIALOPENED, "Warren", "reactorSwitchUsed", pTerminal)
		writeData(SceneObject(pTerminal):getObjectID() .. ":switchNumber", 1)
	end

	pTerminal = getSceneObject(8465578)

	if (pTerminal ~= nil) then
		SceneObject(pTerminal):setCustomObjectName("theme_park/warren/warren_system_messages", "switch_name_2")
		createObserver(OBJECTRADIALOPENED, "Warren", "reactorSwitchUsed", pTerminal)
		writeData(SceneObject(pTerminal):getObjectID() .. ":switchNumber", 2)
	end
end

function Warren:reactorSwitchUsed(pTerminal, pPlayer)
	if (pTerminal == nil) then
		return 0
	end

	if (readData("warren:reactorUnlocked") == 1) then
		self:switchDoneMessage(pTerminal)
		return 0
	end

	local switchNum = readData(SceneObject(pTerminal):getObjectID() .. ":switchNumber")
	local otherSwitchDone = 0

	if (switchNum == 1) then
		otherSwitchDone = readData("warren:reactorSwitchTwo")
		writeData("warren:reactorSwitchOne", 1)
		SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "switch_one", 0, 255, 0)
	else
		otherSwitchDone = readData("warren:reactorSwitchOne")
		writeData("warren:reactorSwitchTwo", 1)
		SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "switch_two", 0, 255, 0)
	end

	if (otherSwitchDone == 1) then
		writeData("warren:reactorUnlocked", 1)

		local pCell = self:getCell("smallroom44") -- Reactor room

		if (pCell ~= nil) then
			self:unlockRoom(pCell)
		end

		createEvent(3000, "Warren", "switchDoneMessage", pTerminal, "")
		createEvent(1800 * 1000, "Warren", "resetReactorSwitches", pTerminal, "")
	end

	return 0
end

function Warren:resetReactorSwitches(pTerminal)
	deleteData("warren:reactorUnlocked")
	deleteData("warren:reactorSwitchOne")
	deleteData("warren:reactorSwitchTwo")

	local pCell = self:getCell("smallroom44") -- Reactor room

	if (pCell ~= nil) then
		self:lockRoom(pCell)
	end
end

function Warren:switchDoneMessage(pTerminal)
	if (pTerminal ~= nil) then
		SceneObject(pTerminal):showFlyText("theme_park/warren/warren_system_messages", "switch_done", 255, 0, 0)
	end
end

function Warren:spawnDebris()
	local pDebris = spawnSceneObject("dantooine", "object/tangible/newbie_tutorial/debris.iff", -54.55, -68.0, .63, 8575723, 1, 0, 0, 0)

	if (pDebris == nil) then
		printLuaError("Unable to spawn warren debris.")
		return
	end

	createObserver(OBJECTDESTRUCTION, "Warren", "notifyDebrisDestroyed", pDebris)
	writeData("warren:debrisID", SceneObject(pDebris):getObjectID())
end

function Warren:notifyDebrisDestroyed(pDebris, pPlayer)
	if (pDebris ~= nil) then
		playClientEffectLoc(SceneObject(pPlayer):getObjectID(), "clienteffect/combat_explosion_lair_large.cef", "dantooine", SceneObject(pDebris):getPositionX(), SceneObject(pDebris):getPositionZ(), SceneObject(pDebris):getPositionY(), SceneObject(pDebris):getParentID())
		createEvent(2000, "Warren", "destroySceneObject", pDebris, "")
	end

	deleteData("warren:debrisID")

	createEvent(1800 * 1000, "Warren", "spawnDebris", nil, "")

	return 1
end

function Warren:destroySceneObject(pObject)
	if (pObject ~= nil) then
		SceneObject(pObject):destroyObjectFromWorld()
	end
end

function Warren:resetPasswords()
	local password = self:generatePasscode(7)
	writeStringData("warren:cellPassword", password)

	password = self:generatePasscode(6)
	writeStringData("warren:turretPassword", password)
end

function Warren:generatePasscode(length)
	local alphabet = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" }

	local code = ''

	for i = 1, length, 1 do
		code = code .. alphabet[getRandomNumber(1,26)]
	end

	return code
end

function Warren:spawnTurret()
	local turretID = readData("warren:turretID")
	local pTurret = getSceneObject(objectID)

	if (pTurret ~= nil) then
		SceneObject(pTurret):destroyObjectFromWorld()
	end

	local pTurret = spawnSceneObject("dantooine", "object/installation/turret/turret_block_med.iff", 22.46, -20, -71.22, 8575695, -0.707107, 0, 0.707107, 0)

	if (pTurret == nil) then
		printLuaError("Failed to spawn warren turret.")
		return
	end

	writeData("warren:turretID", SceneObject(pTurret):getObjectID())
end

function Warren:spawnMobiles()
	spawnMobile("dantooine", "oevitt_piboi", 1, -558, 0, -3736, 0, 0)
	spawnMobile("dantooine", "mirla", 1, -58.56, -76, -35.24, 26, 8575725)
	spawnMobile("dantooine", "manx_try", 1, 29.68, -54, -116.8, -62, 8575714)
	local pMobile = spawnMobile("dantooine", "dirk_maggin", 1, -57.54, -28, -91.04, -140, 8575700)

	if (pMobile ~= nil) then
		CreatureObject(pMobile):setMoodString("scared")
	end

	spawnMobile("dantooine", "phy_hudgen", 1, -7.47, -20, -61.61, -140, 8575680)
	spawnMobile("naboo", "captain_heff", 1, 7.6, 12, 84.2, -180, 1688852)

	--First Room
	spawnMobile("dantooine", "hostile_huurton", 300, -7.8, -20, -9.9, 53, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 300, 5.9, -20, -8.5, -83, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 300, -21.8, -20, -6.8, 91, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 300, -19, -20, -24.4, 57, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 300, 1.6, -20, -24.9, -45, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 300, 12.7, -20, -19.6, 67, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 300, -25.8, -20, -28.2, 55, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -2.3, -20, -21.7, -34, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 300, 1.5, -20, -12.6, 88, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -14.9, -20, -3.8, 174, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -19.1, -20, -23.5, -136, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -3.6, -20, -19.9, -140, 8575677)

	--Second Room
	spawnMobile("dantooine", "warren_imperial_worker", 300, -23.6, -20, -50.2, 29, 8575678)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -28.2, -20, -47.8, 38, 8575678)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -26.1, -20, -36.7, 157, 8575678)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -5, -20, -48, -51, 8575678)
	spawnMobile("dantooine", "hostile_huurton", 300, -15.9, -20, -39.5, -144, 8575678)
	spawnMobile("dantooine", "hostile_huurton", 300, -22.5, -20, -39.4, -177, 8575678)
	spawnMobile("dantooine", "hostile_huurton", 300, -16.6, -20, -48.9, 57, 8575678)

	--Barracks
	spawnMobile("dantooine", "warren_imperial_worker", 300, -67.9, -18, -96.7, 78, 8575684)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -79.6, -18, -97.9, 18, 8575684)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -82, -18, -79.6, 41, 8575684)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -82.8, -18, -107, 153, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 300, -61.9, -18, -111.7, -44, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 300, -64.4, -18, -112.9, -42, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 300, -69.9, -18, -105.7, -14, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 300, -60.8, -18, -86.4, -14, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 300, -69.8, -18, -73.2, 110, 8575684)

	--Droid Room
	spawnMobile("dantooine", "warren_scientist", 300, -23.8, -28, -40.2, 23, 8575689)
	spawnMobile("dantooine", "warren_scientist", 300, -23.2, -28, -42.3, 95, 8575689)
	spawnMobile("dantooine", "warren_scientist", 300, -25.6, -28, -45.8, 124, 8575689)
	spawnMobile("dantooine", "warren_scientist", 300, -1.2, -28, -39.4, 65, 8575689)
	spawnMobile("dantooine", "warren_scientist", 300, -0.3, -28, -41.9, 133, 8575689)
	spawnMobile("dantooine", "warren_scientist", 300, -2.3, -28, -44.6, -141, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 300, 6.8, -28, -52.3, -96, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 300, 9.1, -28, -37.1, -112, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 300, -14.6, -28, -31.7, -164, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 300, -33.4, -28, -38.4, 143, 8575689)
	spawnMobile("dantooine", "warren_agro_droid_boss", 300, 3.6, -28, -69, 0, 8575692)

	spawnMobile("dantooine", "warren_imperial_worker", 300, -59.6, -52, -71.7, -13, 8575709)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -61.4, -52, -70, -131, 8575709)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -65, -52, -72.5, 61, 8575709)
	spawnMobile("dantooine", "warren_imperial_worker", 300, -65.5, -52, -67.6, 150, 8575709)


	spawnMobile("dantooine", "hostile_huurton", 300, -71.8, -52, -11.9, 6, 8575719)
	spawnMobile("dantooine", "hostile_huurton", 300, -73.6, -52, -7.8, 170, 8575719)
	spawnMobile("dantooine", "hostile_huurton", 300, -60.9, -52, -9.8, -159, 8575719)
	spawnMobile("dantooine", "hostile_huurton", 300, -62.3, -52, -7.4, -173, 8575719)

	--Inquisitor Cell Room
	spawnMobile("dantooine", "warren_stormtrooper", 300, -16, -54, -140, -45, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -19.3, -54, -138.6, 60, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -20.9, -54, -132.8, 109, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -32.1, -54, -141.2, 45, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -30, -54, -143, 17, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -30.4, -54, -138.3, 131, 8575716)

	spawnMobile("dantooine", "warren_imperial_officer", 300, -16.7, -54, -140.3, 25, 8575716)
	spawnMobile("dantooine", "warren_imperial_officer", 300, -16, -54, -145.6, -72, 8575716)
	spawnMobile("dantooine", "warren_imperial_officer", 300, -16.2, -54, -139.2, -136, 8575716)

	spawnMobile("dantooine", "teraud_loyalist", 300, -26.1, -54, -127.4, 100, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 300, -26.3, -54, -129.4, 58, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 300, -23.2, -54, -127.5, -47, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 300, -26, -54, -154.3, 18, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 300, -28.2, -54, -153.1, 39, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 300, -23, -54, -153.2, -9, 8575716)

	--Evidence Room 1
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 300, 75.6, -68, 19.1, -2, 8575736)

	--Evidence Room 2
	spawnMobile("dantooine", "warren_imperial_officer", 300, 6.3, -60, 36.6, 58, 8575731)
	spawnMobile("dantooine", "warren_imperial_officer", 300, 9.6, -60, 39.3, -166, 8575731)
	spawnMobile("dantooine", "warren_imperial_officer", 300, 5.3, -60, 29.4, 46, 8575731)
	spawnMobile("dantooine", "cyborg_slice_hound", 300, -11.7, -60, 37.7, 89, 8575731)
	spawnMobile("dantooine", "cyborg_slice_hound", 300, -13.3, -60, 34.1, 121, 8575731)
	spawnMobile("dantooine", "cyborg_slice_hound", 300, -7.3, -60, 28.2, 71, 8575731)

	spawnMobile("dantooine", "cyborg_bol", 300, -52.6, -52, 17, -90, 8575726)
	spawnMobile("dantooine", "warren_scientist", 300, -46.4, -52, 16.7, 0, 8575726)

	spawnMobile("dantooine", "warren_scientist", 300, -84.7, -52, 0, 3, 8575727)
	spawnMobile("dantooine", "warren_scientist", 300, -84.6, -52, 2.6, 2, 8575727)
	spawnMobile("dantooine", "warren_scientist", 300, -100.5, -52, 13.4, 78, 8575727)
	spawnMobile("dantooine", "warren_scientist", 300, -98.5, -52, 20.9, 22, 8575727)
	spawnMobile("dantooine", "warren_scientist", 300, -87.5, -52, 30.2, 139, 8575727)
	spawnMobile("dantooine", "warren_scientist", 300, -79.4, -52, 28.3, 90, 8575727)

	--Evidence Room 3
	spawnMobile("dantooine", "cyborg_dune_lizard", 300, -48.8, -52, 50.5, 0, 8575729)
	spawnMobile("dantooine", "cyborg_dune_lizard", 300, -62.4, -52, 51.7, 0, 8575729)

	--At St room
	spawnMobile("dantooine", "warren_altered_atst", 300, 25.7, -84, -28.8, 0, 8575745)

	--4 locks room
	spawnMobile("dantooine", "warren_agro_droid", 300, 16.9, -20, -95.4, 0, 8575696)
	spawnMobile("dantooine", "warren_agro_droid", 300, 23, -20, -105.2, 0, 8575696)
	spawnMobile("dantooine", "computer_scientist", 300, 40, -20, -109.5, -50, 8575696)

	--Big room in middle
	spawnMobile("dantooine", "teraud_loyalist", 300, -28.3, -52, -38.8, -48, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 300, -32.6, -52, -41.9, -28, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 300, -36.3, -52, -40.5, 32, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 300, 2.4, -52, -65.3, 112, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 300, 2.2, -52, -68.6, 102, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 300, 5.6, -52, -73, 49, 8575740)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -25.1, -52, -50.2, 143, 8575740)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -29.6, -52, -52.7, 107, 8575740)
	spawnMobile("dantooine", "warren_stormtrooper", 300, -26.2, -52, -55.5, -1, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 300, -23.1, -52, -67.5, 176, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 300, -22.5, -52, -69.2, -129, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 300, -29.1, -52, -71.3, 127, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 300, 16.6, -52, -35.4, 53, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 300, 20.1, -52, -37.6, -3, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 300, 24.4, -52, -36.5, -30, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 300, -17.7, -52, -41.2, 50, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 300, -15.5, -52, -44, 18, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 300, -12.5, -52, -42.5, -48, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 300, 29, -52, -56.4, 121, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 300, 30.9, -52, -53.3, 126, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 300, 34.4, -52, -50.7, 153, 8575740)
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 300, 11.7, -52, -57.7, 33, 8575740)
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 300, 14.1, -52, -58.6, 0, 8575740)
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 300, 15.7, -52, -55.5, -51, 8575740)

	--Irradiated Workers
	spawnMobile("dantooine", "warren_irradiated_worker", 300, 56.6, -54, -121.6, -13, 8575715)
	spawnMobile("dantooine", "warren_irradiated_worker", 300, 64, -54, -128.7, 140, 8575715)

	--Bors Teraud
	spawnMobile("dantooine", "bors_teraud", 300, 119.5, -52, 41.7, -171, 8575758)
end

function Warren:getBuildingObject()
	return getSceneObject(8575671)
end

function Warren:getCell(cellName)
	local pWarren = self:getBuildingObject()

	if (pWarren == nil) then
		printLuaError("Unable to get warren building object.")
		return nil
	end

	return BuildingObject(pWarren):getNamedCell(cellName)
end

function Warren:lockRoom(pCell)
	local pWarren = self:getBuildingObject()

	if (pWarren == nil) then
		printLuaError("Unable to get warren building object.")
		return
	end

	if (pCell ~= nil) then
		local cellNum = LuaCellObject(pCell):getCellNumber()

		local cellName = BuildingObject(pWarren):getCellName(cellNum)

		for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
			local pObject = SceneObject(pCell):getContainerObject(j - 1)

			if pObject ~= nil and SceneObject(pObject):isPlayerCreature() then
				if (cellName == "plusroom84" or cellName == "smallroom86" or cellName == "bigroom87" or cellName == "hall85") then
					SceneObject(pObject):teleport(79.7, -60, -43.3, 8575749)
				elseif (cellName == "smallroom47") then
					SceneObject(pObject):teleport(23.4, -50, -148.9, 8575717)
				elseif (cellName == "smallroom44") then
					SceneObject(pObject):teleport(46.4, -54, -125.5, 8575714)
				end
			end
		end

		SceneObject(pCell):setContainerInheritPermissionsFromParent(false)
		SceneObject(pCell):clearContainerDefaultAllowPermission(WALKIN)

		BuildingObject(pWarren):broadcastSpecificCellPermissions(SceneObject(pCell):getObjectID())
	end
end

function Warren:unlockRoom(pCell)
	local pWarren = self:getBuildingObject()

	if (pWarren == nil) then
		printLuaError("Unable to get warren building object.")
		return
	end

	if (pCell ~= nil) then
		SceneObject(pCell):setContainerInheritPermissionsFromParent(true)
		SceneObject(pCell):setContainerDefaultAllowPermission(WALKIN)

		BuildingObject(pWarren):broadcastSpecificCellPermissions(SceneObject(pCell):getObjectID())
	end
end
