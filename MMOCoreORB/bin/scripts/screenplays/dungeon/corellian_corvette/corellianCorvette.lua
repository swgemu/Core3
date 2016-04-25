local ObjectManager = require("managers.object.object_manager")

CorellianCorvetteScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	buildings = {
		{ faction = "neutral", buildingIds = { 1945494, 1945561, 1945628, 1945695, 1945762, 1945829, 1945896, 1945963, 1946030, 1946097, 1946164, 4335861, 4335928, 4335995, 4336062, 4336129 } },
		{ faction = "imperial", buildingIds = { 1946231, 1946298, 1946365, 1946432, 1946499, 1946566, 1946633, 1946700, 1946767, 1946834, 1946901, 4336196, 4336263, 4336330, 4336397, 4336464 } },
		{ faction = "rebel", buildingIds = { 1946968, 1947035, 1947102, 1947169, 1947236, 1947303, 1947370, 1947437, 1947504, 1947571, 1947638, 4336531, 4336598, 4336665, 4336732, 4336799 } }
	},

	escapePoints = {
		--{ faction = "neutral", planet = "tatooine", x = -6150, y = -6350 }, -- TODO find correct coords
		{ faction = "neutral", planet = "tatooine", x = -6176, y = -6379 }, -- TODO find correct coords
		{ faction = "imperial", planet = "naboo", x = 2430, y = -3415 }, -- TODO find correct coords
		{ faction = "rebel", planet = "corellia", x = -6460, y = 5972 },
	},
	
	lockedRooms= {"elevator57", "meetingroom38", "armorybackroom55", "officerquarters63", "officerquarters64", "officerquarters65", "bridge66"},
	
	electric_trap = {
		{ x = 0, z = -14, y = -32 },
		{ x = 0, z = -14, y = -34 },
		{ x = 0, z = -14, y = -36 },
		{ x = 0, z = -14, y = -38 },
		{ x = 0, z = -14, y = -40 },
	},
	
	keypadTerminals = { 
		{ x = -13.05, z = -10.8, y = 6.65, cell = "hall37",  dw = -0.707107, dx = 0, dy = 0.707107, dz = 0, room="meetingroom38" }, -- to meetingroom38
		{ x = -9.45, z = -10.8, y = 128.85, cell = "armory54", dw = 0, dx = 0, dy = -1, dz = 0, room="armorybackroom55"  }, -- armory
		{ x = -16.9, z = -10.8, y = 115.65, cell = "hall53", dw = 0, dx = 0, dy = 1, dz = 0, room = "elevator57"},
		{ x =16.71, z = 1.2, y = 115.5, cell = "hall61",  dw = 0, dx = 0, dy = 1, dz = 0, room="officerquarters63"  }, -- to officerquarters63 x =16.9, z = 1.2, y = 115.75,
		{ x = 1.85, z = 1.2, y = 129.5, cell = "hall62", dw = 0.707107, dx = 0, dy = -0.707107, dz = 0, room = "officerquarters64" }, --to officerquarters64
		{ x = -1.85, z = 1.2, y = 126.53, cell = "hall62",  dw = 0.707107, dx = 0, dy = 0.707107, dz = 0, room = "officerquarters65"  },--to officerquarters65
		{ x = 1.1, z = 1.2, y = 142.57, cell = "hall62", dw = 0, dx = 0, dy = -1, dz = 0, room="bridge66" } --to bridge66
	},


	escapeTerminals = {
		{ x = -10, z = 0, y = 5.8, cell = "hall4", dw = 0.707107, dx = 0, dy = 0, dz = 0 },
		{ x = 20.04, z = 0, y = 45.2, cell = "hall10", dw = 0, dx = 0, dy = 1, dz = 0 },
		{ x = 19.89, z = 0, y = 4.8, cell = "hall10", dw = 0, dx = 0, dy = 0, dz = 0 },
		{ x = 24.95, z = -12, y = -20.2, cell = "escapepods34", dw = 0, dx = 0, dy = 0, dz = 0 },
		{ x = 25.02, z = -12, y = 36.2, cell = "escapepods34", dw = 0, dx = 0, dy = 1, dz = 0 },
		{ x = -25.02, z = -12, y = 36.2, cell = "escapepods39", dw = 0, dx = 0, dy = 1, dz = 0 },
		{ x = -25.06, z = -12, y = -20.19, cell = "escapepods39", dw = 0, dx = 0, dy = 0, dz = 0 }
	},

	lootContainers = {
		{ x = 12.9, z = -12, y = 132.97, cell = "armorybackroom55",template = "object/tangible/container/general/tech_armoire.iff", dw = 1, dx = 0, dy = 0, dz = 0 },
		{ x = 22.7, z = -12, y = 52.08, cell = "spawnroom49",template =  "object/tangible/container/general/tech_armoire.iff", dw = 1, dx = 0, dy = 0, dz = 0 },
		{ x = 5.9, z =  12, y = -90, cell = "vipquarters22", template =  "object/tangible/container/general/tech_armoire.iff", dw = 1, dx = 0, dy = 0, dz = 0 },
		{ x = 22.1, z = -12, y =  51.9, cell =  "spawnroom49",template =   "object/tangible/container/loot/astromech_container.iff", dw = 1, dx = 0, dy = 0, dz = 0 },
		{ x = 0.5, z = 12, y = -8.9, cell = "vipquarters21",template =  "object/tangible/container/general/tech_chest.iff", dw = 1, dx = 0, dy = 0, dz = 0 },
	},

	computerTerminals = { --object/tangible/dungeon/computer_desktop.iff
		{ x = 8.21, z = 0.8, y = -36.11, cell ="thrusterroom24", dw = 0.707107, dx = 0, dy = -0.707107, dz = 0, name="One"}, --computer one
		{ x = 8.21, z = 0.77, y = -41.03, cell ="thrusterroom24", dw = 0.707107, dx = 0, dy = -0.707107, dz = 0 , name="Two"}, -- computer two
		{ x = -8.5, z = 0.75, y = -36.54, cell ="thrusterroom24", dw = 0.707107, dx = 0, dy = 0.707107, dz = 0 , name="Three" }, -- computer three
		{ x = -8.4, z = 0.75, y = -40.89, cell ="thrusterroom24", dw = 0.707107, dx = 0, dy = 0.707107, dz = 0, name="Four"}, --computer four
		{ x = 2.81, z = 12.75, y = 4.73, cell ="vipquarters22", dw = 0, dx = 0, dy = 1, dz = 0, name="Five" } -- computer five
	},
	
	impComputerTerminals = {
		{ x = 4.03, z = 12.75, y = -1.45, cell =  "vipquarters21", dw = 0, dx = 0, dy = 1, dz = 0, name="Ten" } -- computer ten (imp only)
	},

	rebComputerterminals = {
		{ x = 4.03, z = 12.75, y = -1.45, cell =  "vipquarters21", dw = 0, dx = 0, dy = 1, dz = 0, name="Nine" } -- computer nine (reb only)
	},
	
	computerMainframeOne = { -- object/tangible/dungeon/computer_mainframe.iff
		{ x = -15.4, z = -12, y = 66.65, cell = "radarroom46", dw = 0, dx = 0, dy = 0, dz = 0, name="Six" },-- computer six
		{ x = 26.6, z = -12, y = 65.9, cell = "navroom45", dw = 0, dx = 0, dy = 0, dz = 0, name="Seven"}, -- computer seven
		{ x = -1.6, z = -27, y = 78.5, cell = "lowerturret60", dw = 0, dx = 0, dy = 0, dz = 0, name="Eight" },--computer eight
	},

	computerMainframeTwo = {  -- object/tangible/dungeon/computer_mainframe.iff
		{ x = 5.6, z = -12, y = 69.7, cell = "hyperdrive47", dw = 0, dx = 0, dy = 0, dz = 0, name="Hyperdrive Console", quest="hyperdrive"  },  --Hyperdrive Console
		{ x = -9, z = -6.7, y = -38, cell = "thrustersubroom27", dw = 0, dx = 0, dy = 1, dz = 0, name="Fuel Intake Control", quest="fuel" },--Fuel Intake Control
	},
	
	terminalS4 = { --object/tangible/dungeon/wall_terminal_s4.iff
	 { x = -7.5, z = 0, y = 152, cell = "bridge66", dw =0.707107, dx = 0, dy = 0.707107, dz = 0, name = "Bridge Controls" , quest="engine"}
	},
	
	terminalFree = {--  object/tangible/dungeon/terminal_free_s1.iff
		{ x = -11.9, z = -12, y = 4.29, cell = "meetingroom38", dw = 0.707107, dx = 0, dy = 0.707107, dz = 0, name="Elevator Control", quest="elevator57" } -- Elevator Control
	},
	
	security38 = { -- object/tangible/dungeon/computer_mainframe.iff
	 { x = -4.5, z = -14, y = -36.4, cell = "thrustersubroom28", dw = 0, dx = 0, dy = 1, dz = 0, name="SECURITY CONSOLE", quest="meetingroom38" }, -- SECURITY CONSOLE
	},
	


	elevatorTerminals = {
		{ x = 5, z = 0, y = -13.4, cell = "elevator18", dw = 0, dx = 0, dy = 1, dz = 0 },-- up
		{ x = 0, z = -12, y = 37.6, cell = "elevator19", dw = 0, dx = 0, dy = 1, dz = 0 }, -- up
		{ x = 18, z = -24,  y = 120.6, cell = "elevator56", dw = 0, dx = 0, dy = -1, dz = 0 }, -- up
		{ x = -18, z = -12,  y = 120.6, cell = "elevator57", dw = 0, dx = 0, dy = 1, dz = 0 },--up
		
		{ x = 5, z = 12, y = -13.4, cell = "elevator18", dw = 0, dx = 0, dy = 1, dz = 0 },--down
		{ x = 0, z = 0, y = 37.6, cell = "elevator19", dw = 0, dx = 0, dy = 1, dz = 0 },--down
		{ x = 18, z = -12, y = 120.6, cell = "elevator56", dw = 0, dx = 0, dy = -1, dz = 0 },--down
		{ x = -18, z =  0, y = 120.6, cell = "elevator57", dw = 0, dx = 0, dy = 1, dz = 0 },--down
	},
	
	--timeLimit = 300, --5 minutes
	bootDisk = "object/tangible/loot/dungeon/corellian_corvette/bootdisk.iff",
	droidPart = "object/tangible/dungeon/droid_maint_module.iff",
	
}

registerScreenPlay("CorellianCorvetteScreenPlay", true)

function CorellianCorvetteScreenPlay:start()
	if (isZoneEnabled("dungeon1")) then
		self:initialize()
	end
end

function CorellianCorvetteScreenPlay:initialize()
	local num = 0
	for i = 1, #self.buildings, 1 do
		local building = self.buildings[i]
		for j = 1, #building.buildingIds, 1 do
			local pCorvette = getSceneObject(building.buildingIds[j])
			if pCorvette ~= nil then
				ObjectManager.withSceneObject(pCorvette, function(corvette)
					if not corvette:isBuildingObject() then
						print("Corvette id isn't a building: " .. building.buildingIds[j])
					else
						writeData("corvetteActive:" .. corvette:getObjectID(), 0)
						self:ejectAllPlayers(pCorvette)
						writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), 0)
						createObserver(ENTEREDBUILDING, "CorellianCorvetteScreenPlay", "onEnterCorvette", pCorvette)
						createObserver(EXITEDBUILDING, "CorellianCorvetteScreenPlay", "onExitCorvette", pCorvette)
						num = num + 1
					end
				end)
			else
				print("Corvette id isn't valid: " .. building.buildingIds[j])
			end
		end
	end

	print(num .. " corvette buildings initialized.")
end

function CorellianCorvetteScreenPlay:getCorvetteID(pPlayer)
	if (pPlayer == nil) then
		return nil
	end
	local pCell = SceneObject(pPlayer):getParent()
	if (pCell == nil) then
		return nil
	end
	return SceneObject(pCell):getParent()
end

function CorellianCorvetteScreenPlay:lockRooms(pCorvette)
		--{"meetingroom38", "armorybackroom55", "officerquarters63", "officerquarters64", "officerquarters65", "bridge66"},
	ObjectManager.withBuildingObject(pCorvette, function(corvette)
		for i = 1 ,#self.lockedRooms, 1 do
			local pCell = corvette:getNamedCell(self.lockedRooms[i])
			if (pCell ~= nil) then
				ObjectManager.withSceneObject(pCell, function(cell)
					cell:setContainerInheritPermissionsFromParent(false)
					cell:clearContainerDefaultDenyPermission(WALKIN)
					cell:clearContainerDefaultAllowPermission(WALKIN)
					cell:setContainerAllowPermission(corvette:getObjectID()..self.lockedRooms[i], WALKIN)
					cell:setContainerDenyPermission(corvette:getObjectID()..self.lockedRooms[i], MOVEIN)
				end)
			end
		end
	end)
end

function CorellianCorvetteScreenPlay:givePermission(pPlayer, permissionGroup)
	ObjectManager.withCreaturePlayerObject(pPlayer, function(ghost)
		ghost:addPermissionGroup(permissionGroup, true)
	end)
end

function CorellianCorvetteScreenPlay:removePermission(pPlayer, permissionGroup)
	ObjectManager.withCreaturePlayerObject(pPlayer, function(ghost)
		if (ghost:hasPermissionGroup(permissionGroup)) then
			ghost:removePermissionGroup(permissionGroup, true)
		end
	end)
end

function CorellianCorvetteScreenPlay:spawnSceneObjects(pCorvette)

	ObjectManager.withBuildingObject(pCorvette, function(corvette)
		--spawn escape pods
		for i = 1, #self.escapeTerminals, 1 do
			local escTerm = self.escapeTerminals[i]
			local pCell = corvette:getNamedCell(escTerm.cell)
			local cellId = SceneObject(pCell):getObjectID()
			spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/terminal/terminal_geo_bunker.iff", escTerm.x, escTerm.z, escTerm.y, cellId, escTerm.dw, escTerm.dx, escTerm.dy, escTerm.dz)
			SceneObject(spawnedPointer):setCustomObjectName("Escape Pod Controls")
			createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "notifyEscapePod", spawnedPointer)
			local pActiveArea = spawnActiveArea("dungeon1", "object/active_area.iff", SceneObject(spawnedPointer):getWorldPositionX(), SceneObject(spawnedPointer):getWorldPositionZ(), SceneObject(spawnedPointer):getWorldPositionY(), 3, cellId)
			if pActiveArea ~= nil then
				createObserver(ENTEREDAREA, "CorellianCorvetteScreenPlay", "notifyEnteredEscapePodArea", pActiveArea)
			end
		end
		
		-- {"meetingroom38", "armorybackroom55", "elevator57", "officerquarters63", "officerquarters64", "officerquarters65", "bridge66"},
		for i = 1, #self.keypadTerminals, 1 do
			local kp = self.keypadTerminals[i]
			local cellId = SceneObject(corvette:getNamedCell(kp.cell)):getObjectID()
			local spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/keypad_terminal.iff", kp.x, kp.z, kp.y, cellId, kp.dw, kp.dx, kp.dy, kp.dz)
			if (spawnedPointer ~= nil) then
				writeData(corvette:getObjectID()..":"..kp.room..":keypad",SceneObject(spawnedPointer):getObjectID())
				writeData(SceneObject(spawnedPointer):getObjectID()..":locked",1)
				writeStringData(SceneObject(spawnedPointer):getObjectID()..":room",kp.room)
				createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "notifyKeypadUsed", spawnedPointer)
			end
		end

		for i = 1,#self.computerTerminals,1 do
			local ct = self.computerTerminals[i]
			local cellId = SceneObject(corvette:getNamedCell(ct.cell)):getObjectID()
			local spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/computer_desktop.iff", ct.x, ct.z, ct.y, cellId, ct.dw, ct.dx, ct.dy, ct.dz)
			writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":computerName",ct.name)
			writeData(corvette:getObjectID()..":"..ct.name..":used",0)
			createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "notifyComputerUsed", spawnedPointer)
		end
		
		for i = 1,4,1 do
			local et = self.elevatorTerminals[i]
			local cellId = SceneObject(corvette:getNamedCell(et.cell)):getObjectID()
			spawnSceneObject("dungeon1","object/tangible/terminal/terminal_elevator_up.iff", et.x, et.z, et.y, cellId, et.dw, et.dx, et.dy, et.dz)
		end

		for i = 5,8,1 do
			local et = self.elevatorTerminals[i]
			local cellId = SceneObject(corvette:getNamedCell(et.cell)):getObjectID()      
			spawnSceneObject("dungeon1","object/tangible/terminal/terminal_elevator_down.iff", et.x, et.z, et.y, cellId, et.dw, et.dx, et.dy, et.dz)
		end

	-- spawn electric trap
	local cellId = SceneObject(corvette:getNamedCell("thrustersubroom28")):getObjectID()
	for i = 1,#self.electric_trap,1 do
		local et = self.electric_trap[i]
		local pShock = spawnSceneObject("dungeon1", "object/static/particle/pt_poi_electricity_2x2.iff",et.x,et.z,et.y,cellId,1,0,0,0)
		if pShock ~= nil then
			writeData(corvette:getObjectID()..":shock"..i, SceneObject(pShock):getObjectID())
			local pShockArea = spawnActiveArea("dungeon1", "object/active_area.iff", SceneObject(pShock):getWorldPositionX(), SceneObject(pShock):getWorldPositionZ(), SceneObject(pShock):getWorldPositionY(), 6, cellId)
			if pShockArea ~= nil then
				createObserver(ENTEREDAREA, "CorellianCorvetteScreenPlay", "notifyElectroShock", pShockArea)
			end
		end
	end
	writeData(corvette:getObjectID()..":electricity_on",1)
		--spawn droids for electric trap quest
		local cellId = SceneObject(corvette:getNamedCell("thrustersubroom28")):getObjectID()
		local pDroid1 = spawnMobile("dungeon1", "corvette_r3", 0, 6, -14, -37, 96, cellId)
		CreatureObject(pDroid1):setCustomObjectName("R3-F1")
		createObserver(DESTINATIONREACHED, "CorellianCorvetteScreenPlay", "repairDroidDestinationReached", pDroid1)
		AiAgent(pDroid1):setAiTemplate("manualescortwalk")
		AiAgent(pDroid1):setFollowState(4)
		SceneObject(pDroid1):setContainerComponent("brokenDroidContainerComponent")
		local pDroid2 = spawnMobile("dungeon1", "protocol_droid_h6p0", 0, 6.58, -14, -34.82,96,cellId)
		writeData(corvette:getObjectID()..":pDroid1", SceneObject(pDroid1):getObjectID())
		writeData(corvette:getObjectID()..":pDroid2", SceneObject(pDroid2):getObjectID())
		writeData(corvette:getObjectID()..":DroidFixed", 0)

	for i = 1,#self.computerMainframeOne,1 do
		local cm = self.computerMainframeOne[i]
		local cellId = SceneObject(corvette:getNamedCell(cm.cell)):getObjectID()
		local spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/computer_mainframe.iff", cm.x, cm.z, cm.y, cellId, cm.dw, cm.dx, cm.dy, cm.dz)
		writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":computerName",cm.name)
		writeData(corvette:getObjectID()..":"..cm.name..":used",0)
		createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "notifyComputerUsed", spawnedPointer)
    end

	for i = 1,#self.computerMainframeTwo,1 do
		local cm = self.computerMainframeTwo[i]
		local cellId = SceneObject(corvette:getNamedCell(cm.cell)):getObjectID()
		local spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/computer_mainframe.iff", cm.x, cm.z, cm.y, cellId, cm.dw, cm.dx, cm.dy, cm.dz)
		SceneObject(spawnedPointer):setCustomObjectName(cm.name)
		writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":quest",cm.quest)
		writeData(corvette:getObjectID()..":"..cm.quest,0)
		SceneObject(spawnedPointer):setObjectMenuComponent("CorvetteTerminalMenuComponent")
	end

	local tf = self.terminalFree[1]
	local cellId = SceneObject(corvette:getNamedCell(tf.cell)):getObjectID()
	local spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/terminal_free_s1.iff", tf.x, tf.z, tf.y, cellId, tf.dw, tf.dx, tf.dy, tf.dz)
	SceneObject(spawnedPointer):setCustomObjectName(tf.name)
	writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":computerName",tf.quest)
	writeData(corvette:getObjectID()..":"..tf.quest,0)
	createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "notifyComputerUsed", spawnedPointer)
	
	local tf = self.terminalS4[1]
	local cellId = SceneObject(corvette:getNamedCell(tf.cell)):getObjectID()
	spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/wall_terminal_s4.iff", tf.x, tf.z, tf.y, cellId, tf.dw, tf.dx, tf.dy, tf.dz)
	SceneObject(spawnedPointer):setCustomObjectName(tf.name)
	writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":quest",tf.quest)
	writeData(corvette:getObjectID()..":"..tf.quest,0)
	SceneObject(spawnedPointer):setObjectMenuComponent("CorvetteTerminalMenuComponent")
	
	local sr = self.security38[1]
	local cellId = SceneObject(corvette:getNamedCell(sr.cell)):getObjectID()
	spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/computer_mainframe.iff", sr.x, sr.z, sr.y, cellId, sr.dw, sr.dx, sr.dy, sr.dz)
	SceneObject(spawnedPointer):setCustomObjectName(sr.name)
	writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":computerName",sr.quest)
	writeData(corvette:getObjectID()..":"..sr.quest,0)
	createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "notifyComputerUsed", spawnedPointer)
	
	if (self:getBuildingFaction(pCorvette) == "imperial") or (self:getBuildingFaction(pCorvette) == "rebel") then
		local it = self.impComputerTerminals[1]
		local cellId = SceneObject(corvette:getNamedCell(it.cell)):getObjectID()
		if self:getBuildingFaction(pCorvette) == "rebel" then
			writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":quest","Nine")
		else
			writeStringData(SceneObject(spawnedPointer):getObjectID() .. ":quest","Ten")
		end
		spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/dungeon/computer_desktop.iff", it.x, it.z, it.y, cellId, it.dw, it.dx, it.dy, it.dz)
		createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "notifyComputerUsed", spawnedPointer)
	end
	end)
end

function CorellianCorvetteScreenPlay:repairDroidDestinationReached(pDroid)
	local pCorvette = self:getCorvetteID(pDroid)
	local corvetteId = BuildingObject(pCorvette):getObjectID()
	
	self:removeElectricTrap(pCorvette)
	
	local droid2ID = readData(corvetteId..":pDroid2")
	local pDroid2 = getSceneObject(droid2ID)
	if (pDroid2 ~= nil) then
		spatialChat(pDroid2, "@dungeon/corvette:pdroid_congrats")
		writeData(corvetteId.. ":DroidFixed",1)
	end
	return 0
end


function CorellianCorvetteScreenPlay:removeElectricTrap(pCorvette)
	if (pCorvette == nil) then
		return
	end
		
	for i = 1,#self.electric_trap,1 do
		local shockID = readData(BuildingObject(pCorvette):getObjectID()..":shock"..i)
		print(shockID)
		print(BuildingObject(pCorvette):getObjectID()..":shock"..i)
		local pShock = getSceneObject(shockID)
		if pShock ~= nil then
			SceneObject(pShock):destroyObjectFromWorld()
		end
	end
	writeData(BuildingObject(pCorvette):getObjectID()..":electricity_on", 0)
	return 0
end

function CorellianCorvetteScreenPlay:notifyElectroShock(pActiveArea,pMovingObject)
	if (pMovingObject == nil or pActiveArea == nil or not SceneObject(pMovingObject):isCreatureObject()) then
		return 0
	end

	if (SceneObject(pMovingObject):isAiAgent() and not AiAgent(pMovingObject):isPet()) then
		return 0
	end
	local pCorvette = self:getCorvetteID(pMovingObject)
	local isPowerOn = readData(SceneObject(pCorvette):getObjectID()..":electricity_on")
	if (isPowerOn == 0) then
		return 0
	end
	
	CreatureObject(pMovingObject):inflictDamage(pMovingObject, 0,100000, 1)
	CreatureObject(pMovingObject):sendSystemMessage("@quest/corvetter_trap:shocked") --You feel electricity coursing through your body!
	return 0
end

function CorellianCorvetteScreenPlay:notifyKeypadUsed(pKeypad, pPlayer, radialSelected)
	if (pKeypad == nil or pPlayer == nil) then
		return 0
	end
	local cellId = readStringData(SceneObject(pKeypad):getObjectID() .. ":room")
	local pCorvette = self:getCorvetteID(pPlayer)
	local corvetteId = SceneObject(pCorvette):getObjectID()
	
	if cellId == "meetingroom38" then
			if (readData(corvetteId.."meetingroom38") == 0) then
				CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:meeting_room_locked")
			end
			return 0
		end

		if cellId == "elevator57" then
			if readData(corvetteId.."elevator57") == 0 then
				CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:elevator_locked")
			end
			return 0
		end
	
	if (radialSelected == 20) then
		local suiManager = LuaSuiManager()
		suiManager:sendKeypadSui(pKeypad, pPlayer, "CorellianCorvetteScreenPlay", "keypadSuiCallback")
	end
	return 0
end


function CorellianCorvetteScreenPlay:keypadSuiCallback(pPlayer, pSui, cancelPressed, enteredCode, pressedButton)
	if (pPlayer == nil or pSui == nil) then
		return
	end

	local suiBox = LuaSuiBox(pSui)
	
	local pUsingObject = suiBox:getUsingObject()

	if (pUsingObject == nil) then
		return
	end
	
	local pCorvette = self:getCorvetteID(pPlayer)
	local corvetteId = SceneObject(pCorvette):getObjectID()

	
	local keypadCode = readData(SceneObject(pUsingObject):getObjectID() .. ":keypad_code")
	local cellId = readStringData(SceneObject(pUsingObject):getObjectID() .. ":room")
	local locked = readData(SceneObject(pUsingObject):getObjectID()..":locked")
	
	if (locked == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:already_open")
		return
	end

	if (keypadCode == nil) or (keypadCode == 0) then
		return
	end
	if (pressedButton == "slice") then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:does_nothing")
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:lock") 
	end
	if (pressedButton == "keycard") then
		CreatureObct(pPlayer):sendSystemMessage("@dungeon/corvette:does_nothing") 
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:lock") 
	end
	
	if (pressedButton == "enter") then
		if (tonumber(enteredCode) == keypadCode) then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:open") 
			--This door is now unlocked.
			if (CreatureObject(pPlayer):isGrouped()) then
				local groupSize = CreatureObject(pPlayer):getGroupSize()

				for i = 0, groupSize - 1, 1 do
					local pMember = CreatureObject(pPlayer):getGroupMember(i)
					if pMember ~= nil then
							self:givePermission(pMember, corvetteId..cellId)
					end
				end
			else
				self:givePermission(pPlayer, corvetteId..cellId)
				writeData(SceneObject(pUsingObject):getObjectID()..":locked",0)
			end
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:lock") 
			--This door is still locked.		
			return
		end
	end
end

function CorellianCorvetteScreenPlay:setLootBoxPermissions(pContainer)
	ObjectManager.withSceneObject(pContainer, function(container)
		container:setContainerInheritPermissionsFromParent(false)
		container:setContainerDefaultDenyPermission(MOVEIN)
		container:setContainerDefaultAllowPermission(OPEN + MOVEOUT)
	end)
end

--loot containers
function CorellianCorvetteScreenPlay:spawnLootContainers(pCorvette)
	if (pCorvette == nil) then
		return
	end
	local spawnedSceneObject = LuaSceneObject(nil)
	local corvFaction = self:getBuildingFaction(pCorvette)

	local pCell = BuildingObject(pCorvette):getNamedCell("armorybackroom55")
	if (pCell ~= nil) then
		local cellID = SceneObject(pCell):getObjectID()
		local spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/container/general/tech_armoire.iff",13.2,-12,132.9,cellID,0.707107,0,-0.707107,0)
		self:setLootBoxPermissions(spawnedPointer)
		spawnedSceneObject:_setObject(spawnedPointer)
		--SceneObject(spawnedPointer):setCustomObjectName("")
		writeData(spawnedSceneObject:getObjectID() .. "lootbox", 1)
		createLoot(spawnedPointer, corvFaction.."_corvette_loot", 1, false)
		--createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "spawnSecurity", spawnedPointer)
	end

	local pCell = BuildingObject(pCorvette):getNamedCell("spawnroom49")
	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()
		spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/container/general/tech_armoire.iff",22.7,-12,52.08,cellID,0.707107,0,-0.707107,0)
		self:setLootBoxPermissions(spawnedPointer)
		spawnedSceneObject:_setObject(spawnedPointer)
		--SceneObject(spawnedPointer):setCustomObjectName("")
		writeData(spawnedSceneObject:getObjectID() .. "lootbox", 2)
		createLoot(spawnedPointer, corvFaction.."_corvette_loot", 1, false)
		--createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "spawnSecurity", spawnedPointer)
	end
	local pCell = BuildingObject(pCorvette):getNamedCell("vipquarters22")
	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()
		spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/container/general/tech_armoire.iff",6.45,12,13,cellID,0.707107,0,-0.707107,0)
		self:setLootBoxPermissions(spawnedPointer)
		spawnedSceneObject:_setObject(spawnedPointer)
		--SceneObject(spawnedPointer):setCustomObjectName("")
		writeData(spawnedSceneObject:getObjectID() .. "lootbox", 3)
		createLoot(spawnedPointer, corvFaction.."_corvette_loot", 1, false)
		--createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "spawnSecurity", spawnedPointer)
	end
	local pCell = BuildingObject(pCorvette):getNamedCell("vipquarters21")
	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()
		spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/container/general/tech_chest.iff",0.5,12,-8.91,cellID,1,0,0,0)
		self:setLootBoxPermissions(spawnedPointer)
		spawnedSceneObject:_setObject(spawnedPointer)
		--SceneObject(spawnedPointer):setCustomObjectName("")
		writeData(spawnedSceneObject:getObjectID() .. "lootbox", 4)
		createLoot(spawnedPointer, "disk_loot", 1, false)
		createEvent(600, "CorellianCorvetteScreenPlay", "opDisk_loot", spawnedPointer,"")
		--createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "spawnSecurity", spawnedPointer)
	end
	local pCell = BuildingObject(pCorvette):getNamedCell("spawnroom8")
	if (pCell ~= nil) then
		cellID = SceneObject(pCell):getObjectID()		
		spawnedPointer = spawnSceneObject("dungeon1", "object/tangible/container/loot/astromech_container.iff",-13.9,0,51.44,cellID,0,0,1,0)
		spawnedSceneObject:_setObject(spawnedPointer)
		SceneObject(spawnedPointer):setCustomObjectName("spare droid (for parts)")
		self:setLootBoxPermissions(spawnedPointer)
		writeData(spawnedSceneObject:getObjectID() .. "lootbox", 5)
		createLoot(spawnedPointer, "r2droid_loot", 1, false)
		createEvent(600, "CorellianCorvetteScreenPlay", "r2_loot", spawnedPointer,"")
		--createObserver(OBJECTRADIALUSED, "CorellianCorvetteScreenPlay", "spawnSecurity", spawnedPointer)
	end
end


function CorellianCorvetteScreenPlay:opDisk_loot(pSceneObject)
	if (pSceneObject == nil) then
		return
	end

	writeData(SceneObject(pSceneObject):getObjectID() .. ":spawned", 0)

	if (SceneObject(pSceneObject):getContainerObjectsSize() == 0) then
		createLoot(pSceneObject, "disk_loot", 1, false)
	end
end

function CorellianCorvetteScreenPlay:r2_loot(pSceneObject)
	if (pSceneObject == nil) then
		return
	end

	writeData(SceneObject(pSceneObject):getObjectID() .. ":spawned", 0)

	if (SceneObject(pSceneObject):getContainerObjectsSize() == 0) then
		createLoot(pSceneObject, "r2droid_loot", 1, false)
	end
end

function CorellianCorvetteScreenPlay:notifyEnteredEscapePodArea(pSceneObject,pPlayer,radialSelected)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:escape_pod_message")
	return 0
end

function CorellianCorvetteScreenPlay:notifyEscapePod(pSceneObject,pPlayer,radialSelected)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end
	if radialSelected == 20 then
		createEvent(2 * 1000, "CorellianCorvetteScreenPlay", "ejectPlayer", pPlayer,"")
		return 0
	end

	return 0
end

function CorellianCorvetteScreenPlay:notifyComputerUsed(pComputer, pPlayer, radialSelected)
	if (pPlayer == nil or pComputer == nil) then
		return 0
	end
	if not CreatureObject(pPlayer):isInRangeWithObject(pComputer, 4) then
		return 0
	end
	
	local computerName = readStringData(SceneObject(pComputer):getObjectID() .. ":computerName")
	local pCorvette = self:getCorvetteID(pPlayer)
	local corvetteId = SceneObject(pCorvette):getObjectID()

	if (radialSelected == 20) then
		if readData(corvetteId..":"..computerName..":used") ~= 1 then 
			--self:spawnEnemies(pPlayer, pCorvette)
		end
		
		if (computerName == "One") then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:computer_one")
			writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Two") then
			local keypadID = readData(corvetteId..":armorybackroom55:keypad")
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:armory_code")
			if (readData(keypadID..":keypad_code") == 0) then
				local secCode55 = getRandomNumber (10000, 99999)
				writeData(keypadID..":keypad_code",secCode55)
			end
		CreatureObject(pPlayer):sendSystemMessage(" ", readData(keypadID..":keypad_code"))
		writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Three") then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:computer_three")
			writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Four") then
			local booted = readData(corvetteId..":"..computerName..":rebooted")
			local keypadID = readData(corvetteId..":bridge66:keypad")
			local pBootDisk = nil
			
			local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
			if (pInventory ~= nil) then 
				pBootDisk = getContainerObjectByTemplate(pInventory, self.bootDisk, true)
			end
			
			if (booted == 1) then
				if (readData(keypadID..":keypad_code") == 0) then
					local secCode66 = getRandomNumber (10000, 99999)
					writeData(keypadID..":keypad_code",secCode66)
					writeData(corvetteId..":"..computerName..":used",1)
				end
				CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:bridge_code")
				CreatureObject(pPlayer):sendSystemMessage(" ",readData(keypadID..":keypad_code"))
				return 0
			else 
				if (pBootDisk == nil) then 
					local slicer_skill = self:checkSlicingSkill(pPlayer)
					local chance = getRandomNumber(1,8)
					if (chance > slicer_skill) or (readData(corvetteId..":"..computerName..":attemptedSlice") == 1) then
						CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:reboot")--This computer needs to be rebooted.Please insert Operations Disk #4 into the terminal.
						writeData(corvetteId..":"..computerName..":attemptedSlice", 1)
					else 
						CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:sliced") --The computer was down, but your slicing skill allows you to reboot it without the disk.
						writeData(corvetteId..":"..computerName..":attemptedSlice", 1)
						writeData(corvetteId..":"..computerName..":rebooted", 1)
						writeData(corvetteId..":"..computerName..":used",1)
 					end
				else
					CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:insert_disk")
					SceneObject(pBootDisk):destroyObjectFromWorld()
					SceneObject(pBootDisk):destroyObjectFromDatabase()
				end
			writeData(corvetteId..":"..computerName..":rebooted", 1)
			writeData(corvetteId..":"..computerName..":used",1)
		end
		if (readData(keypadID..":keypad_code") == 0) then
			secCode66 = getRandomNumber (10000, 99999)
			writeData(keypadID..":keypad_code",secCode66)
			writeData(corvetteId..":"..computerName..":used",1)
		end
	end --Four

		if (computerName == "Five") then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:journal")
			writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Six") then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:officer_starboard") --Printing Out Security Code for Officer Quarters, Starboard Side:
			local keypadID = readData(corvetteId..":officerquarters64:keypad")
			if (readData(keypadID..":keypad_code") == 0) then
				local secCode64 = getRandomNumber (10000, 99999)
				writeData(keypadID..":keypad_code",secCode64)
			end
			CreatureObject(pPlayer):sendSystemMessage(" ", readData(keypadID..":keypad_code"))
			writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Seven") then
			local keypadID = readData(corvetteId..":officerquarters65:keypad")
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:officer_port")
			if (readData(keypadID..":keypad_code") == 0) then
				local secCode65 = getRandomNumber (10000, 99999)
				writeData(keypadID..":keypad_code",secCode65)
			end
			CreatureObject(pPlayer):sendSystemMessage(" ", readData(keypadID..":keypad_code"))
			writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Eight") then
			local keypadID = readData(corvetteId..":officerquarters63:keypad")
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:prison_code")
			if (readData(keypadID..":keypad_code") == 0) then
				local secCode63 = getRandomNumber (10000, 99999)
				writeData(keypadID..":keypad_code",secCode63)
			end
			CreatureObject(pPlayer):sendSystemMessage(" ", readData(keypadID..":keypad_code"))
			writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Nine") then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:droid_explanation_rebel")
			writeData(corvetteId..":"..computerName..":used",1)
		end

		if (computerName == "Ten") then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:droid_explanation_imperial")
			writeData(corvetteId..":"..computerName..":used",1)
		end
		
		if (computerName == "elevator57") then
			if readData(corvetteId..":elevator57") ~= 0 then
				CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:already_open")
			else
				if (CreatureObject(pPlayer):isGrouped()) then
					local groupSize = CreatureObject(pPlayer):getGroupSize()
					for i = 0, groupSize - 1, 1 do
						local pMember = CreatureObject(pPlayer):getGroupMember(i)
						if pMember ~= nil then
							self:givePermission(pMember, corvetteId.."elevator57")
						end
					end
				else
					self:givePermission(pPlayer, corvetteId.."elevator57")
					CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:unlock_elevator")
					writeData(corvetteId..":elevator57",1)
				end
			end
		end
		
		if (computerName == "meetingroom38") then
			if readData(corvetteId..":meetingroom38") ~= 0 then
				CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:already_open")
			else
				if (CreatureObject(pPlayer):isGrouped()) then
					local groupSize = CreatureObject(pPlayer):getGroupSize()
					for i = 0, groupSize - 1, 1 do
						local pMember = CreatureObject(pPlayer):getGroupMember(i)
						if pMember ~= nil then
							self:givePermission(pMember, corvetteId.."meetingroom38")
						end
					end
				else
					self:givePermission(pPlayer, corvetteId.."meetingroom38")
					CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:unlock_meeting")
					writeData(corvetteId..":meetingroom38",1)
				end
			end
		end
		
	end
	return 0
end

function CorellianCorvetteScreenPlay:checkSlicingSkill(pPlayer)
	if (pPlayer == nil) then
		return
	end
	
	local slicingskill = 0
	if (CreatureObject(pPlayer):hasSkill("combat_smuggler_novice") ~= false) then
		if (CreatureObject(pPlayer):hasSkill("combat_smuggler_novice")) then
			slicingskill = slicingskill + 1;
		elseif (CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_master")) then
			slicingskill = slicingskill + 1;
		elseif (CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_02")) then
			slicingskill = slicingskill + 1;
		elseif (CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_03")) then
			slicingskill = slicingskill + 1;
		elseif (CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_03")) then
			slicingskill = slicingskill + 1;
		elseif (CreatureObject(pPlayer):hasSkill("combat_smuggler_slicing_04")) then
			slicingskill = slicingskill + 2;
		end
	end
	return slicingskill;
end

function CorellianCorvetteScreenPlay:activate(pPlayer, faction, questType)
	if (isZoneEnabled("dungeon1")) then
		local ids = nil
		for i = 1, #self.buildings, 1 do
			if self.buildings[i].faction == faction then
				ids = self.buildings[i].buildingIds
			end
		end

		if ids == nil then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:corellian_corvette_travel_fail") -- The Corellian corvette is currently out of transport range making transportation impossible.
			return 0
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
			if (CreatureObject(pPlayer):isGrouped()) then
				local groupSize = CreatureObject(pPlayer):getGroupSize()
				for i = 0, groupSize - 1, 1 do
					local pMember = CreatureObject(pPlayer):getGroupMember(i)
					if pMember ~= nil then
						writeData(SceneObject(pMember):getObjectID() .. "corvetteId", corvetteId)
						writeStringData(SceneObject(pMember):getObjectID() .. "questType", questType)
						createEvent(1000, "CorellianCorvetteScreenPlay", "transportPlayer", pMember, "")		
					end
				end
			else
				writeData(SceneObject(pPlayer):getObjectID() .. "corvetteId", corvetteId)
				writeStringData(SceneObject(pPlayer):getObjectID() .. "questType", questType)
				createEvent(1000, "CorellianCorvetteScreenPlay", "transportPlayer", pPlayer, "")
		 	end
			--TODO prompt nearby group members for travel
			return 1
		else
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:corellian_corvette_travel_fail") -- The Corellian corvette is currently out of transport range making transportation impossible.
			return 0
		end
	else
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:unable_to_find_dungeon") -- That area is currently unavailable. Please try again later.
		return 0
	end
end

function CorellianCorvetteScreenPlay:transportPlayer(pPlayer)
	if pPlayer == nil then
		return
	end

	local questType = readStringData(SceneObject(pPlayer):getObjectID() .. "questType")
	local corvetteId = readData(SceneObject(pPlayer):getObjectID() .. "corvetteId")
	local pCorvette = getSceneObject(corvetteId)
	
	ObjectManager.withBuildingObject(pCorvette, function(corvette)
		self:startQuest(pCorvette, questType)
		
		local cellId = SceneObject(corvette:getCell(1)):getObjectID()
		SceneObject(pPlayer):switchZone("dungeon1", -44, 0, 0, cellId)
		for i = 1, #self.lockedRooms, 1 do
			self:removePermission(pPlayer, corvetteId..self.lockedRooms[i])
		end
		print(self:getBuildingFaction(pcorvette))
		if self:getBuildingFaction(pCorvette) ~= "neutral" then
			print("transportPlayer: Observer created",pPlayer)
			createObserver(PLAYERCLONED, "CorellianCorvetteScreenPlay", "setPlayerOvert", pPlayer)
		end
	end)
end

function CorellianCorvetteScreenPlay:setPlayerOvert(pPlayer)
	if pPlayer == nil then
		return 0
	end
	print("setting player overt")
	ObjectManager.withCreatureAndPlayerObject(pPlayer, function(player, playerObject)
		print("overt ="..tostring(OVERT))
		playerObject:setFactionStatus(OVERT)
	end)
	createObserver(PLAYERCLONED, "CorellianCorvetteScreenPlay", "setPlayerOvert", pPlayer)
end


function CorellianCorvetteScreenPlay:doTimerEvents(pCorvette)
	if (pCorvette == nil) then
		return
	end
	
	local isActive = readData("corvetteActive:" .. SceneObject(pCorvette):getObjectID())
	if isActive == 0 then
			return
	end
	local currentTime = os.time()
	local startTime = readData( SceneObject(pCorvette):getObjectID()..":groupTime")
	local timeLeft = currentTime - startTime
	
	timeLeft = 3600 - timeLeft
	timeLeft = timeLeft / 60
	self:broadcastMessage (pCorvette, "You now have "..timeLeft.." minutes left to complete your assignment.")
	if timeLeft > 10 then
		createEvent(5 * 60 * 1000, "CorellianCorvetteScreenPlay", "doTimerEvents", pCorvette, "") --every 5 minutes
	else
		createEvent(60 * 1000, "CorellianCorvetteScreenPlay", "doTimerEvents", pCorvette, "") --every 1 minute
	end
	if timeLeft < 1 then
		createEvent(10 * 1000, "CorellianCorvetteScreenPlay", "handleQuestFailure", pCorvette, "")
	end
end

function CorellianCorvetteScreenPlay:startQuest(pCorvette, questType)
	writeData("corvetteActive:" .. SceneObject(pCorvette):getObjectID(), 1)
	--TODO add timer countdowns
	local startTime = os.time()
	writeData(SceneObject(pCorvette):getObjectID()..":groupTime",startTime)
	self:broadcastMessage (pCorvette, "You have 60 minutes left to complete your assignment.")
	self:doTimerEvents(pCorvette)
	--TODO spawn quest mobs, scene objects, and objectives
	self:lockRooms(pCorvette)
	self:spawnLootContainers(pCorvette)
	self:spawnSceneObjects(pCorvette)
end

function CorellianCorvetteScreenPlay:getBuildingFaction(pCorvette)
	return ObjectManager.withSceneObject(pCorvette, function(corvette)
		if string.find(corvette:getTemplateObjectPath(), "imperial") ~= nil then
			return "imperial"
		elseif string.find(corvette:getTemplateObjectPath(), "rebel") ~= nil then
			return "rebel"
		else
			return "neutral"
		end
	end)
end


function CorellianCorvetteScreenPlay:setGroupPermissions(pCorvette, pPlayer)
--set initial permissions for locked rooms
	if (CreatureObject(pPlayer):isGrouped()) then
		local groupSize = CreatureObject(pPlayer):getGroupSize()
		for i = 0, groupSize - 1, 1 do
			local pMember = CreatureObject(pPlayer):getGroupMember(i)
			if pMember ~= nil then
				for i = 1, #self.lockedRooms, 1 do
					local pCell = BuildingObject(pCorvette):getNamedCell(self.lockedRooms[i])
					if (pCell ~= nil) then
						local cellID = SceneObject(pCell):getObjectID()
						local corvetteId = SceneObject(pCorvette):getObjectID()
						self:removePermission(pPlayer, corvetteId..cellId)
					end
				end
			end
		end
	end
	return
end


function CorellianCorvetteScreenPlay:onEnterCorvette(pCorvette, pPlayer)
	if SceneObject(pPlayer):isPlayerCreature() then
		local active = readData("corvetteActive:" .. SceneObject(pCorvette):getObjectID())
		if active ~= 1 then
			createEvent(10 * 1000, "CorellianCorvetteScreenPlay", "handleNotAuthorized", pPlayer, "")
			return 0
		end

		local playerCount = readData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID())

		writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), playerCount + 1)

		if playerCount > 10 then
			createEvent(10 * 1000, "CorellianCorvetteScreenPlay", "handleTooMany", pPlayer, "")
			return 0
		end
	end
	return 0
end



function CorellianCorvetteScreenPlay:broadcastMessage(pCorvette, message)
ObjectManager.withBuildingObject(pCorvette, function(corvette)
		local playersToSend = {}
		for i = 1, 66, 1 do
			local pCell = corvette:getCell(i)
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if SceneObject(pObject):isPlayerCreature() then
					table.insert(playersToSend, pObject)
				end
			end
		end

		for i = 1, #playersToSend, 1 do
			local pObject = playersToSend[i]
			CreatureObject(pObject):sendSystemMessage(message)
		end
	end)
end


function CorellianCorvetteScreenPlay:cleanOutDungeon(pCorvette)
		ObjectManager.withBuildingObject(pCorvette, function(corvette)
		local objectsToDestroy = {}
		for i = 1, 66, 1 do
			local pCell = corvette:getCell(i)
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if (not SceneObject(pObject):isPlayerCreature()) then
					table.insert(objectsToDestroy, pObject)
				end
			end
		end

		for i = 1, #objectsToDestroy, 1 do
			local pObject = objectsToDestroy[i]
			SceneObject(pObject):destroyObjectFromWorld()
			SceneObject(pObject):destroyObjectFromDatabase()
		end
	end)
end

function CorellianCorvetteScreenPlay:onExitCorvette(pCorvette, pPlayer)
	if SceneObject(pPlayer):isPlayerCreature() then
		local playerCount = readData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID())
		writeData("corvettePlayerCount:" .. SceneObject(pCorvette):getObjectID(), playerCount - 1)
	end
	return 0
end

function CorellianCorvetteScreenPlay:handleNotAuthorized(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:not_authorized") -- You do not have the proper authorization to be in this area.
	createEvent(2 * 1000, "CorellianCorvetteScreenPlay", "ejectPlayer", pPlayer, "")
end

function CorellianCorvetteScreenPlay:handleTooMany(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/space_dungeon:no_room_remaining") -- There are too many people in this area. Return transportation initiated.
	createEvent(2 * 1000, "CorellianCorvetteScreenPlay", "ejectPlayer", pPlayer, "")
end

function CorellianCorvetteScreenPlay:handleQuestFailure(pCorvette)
	--TODO reset ticket giver quest
	self:ejectAllPlayers(pCorvette)
	self:cleanOutDungeon(pCorvette)
	writeData("corvetteActive:" .. SceneObject(pCorvette):getObjectID(), 0)
end

function CorellianCorvetteScreenPlay:ejectAllPlayers(pCorvette)
	ObjectManager.withBuildingObject(pCorvette, function(corvette)
		local playersToEject = {}
		for i = 1, 66, 1 do
			local pCell = corvette:getCell(i)
			for j = 1, SceneObject(pCell):getContainerObjectsSize(), 1 do
				local pObject = SceneObject(pCell):getContainerObject(j - 1)
				if SceneObject(pObject):isPlayerCreature() then
					table.insert(playersToEject, pObject)
				end
			end
		end

		for i = 1, #playersToEject, 1 do
			local pObject = playersToEject[i]
			createEvent(1000, "CorellianCorvetteScreenPlay", "ejectPlayer", pObject, "")
		end
	end)
end

function CorellianCorvetteScreenPlay:ejectPlayer(pPlayer)
	if pPlayer == nil then
		return 0
	end

	local point = nil
	local pCorvette = SceneObject(SceneObject(pPlayer):getParent()):getParent()
	if pCorvette == nil or not SceneObject(pCorvette):isBuildingObject() then
		print("Error: unable to get corvette in CorellianCorvetteScreenPlay:ejectPlayer")
		return 0
	end

	local faction = self:getBuildingFaction(pCorvette)

	for i = 1, #self.escapePoints, 1 do
		if self.escapePoints[i].faction == faction then
			point = self.escapePoints[i]
		end
	end

	if point == nil then
		print("Error: nil escape point for faction: " .. faction)
		return 0
	end
	--remove Extras
	local pInventory = SceneObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then 
		local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/loot/dungeon/corellian_corvette/bootdisk.iff", true)
		if pItem ~= nil then
			SceneObject(pItem):destroyObjectFromWorld()
			SceneObject(pItem):destroyObjectFromDatabase()
		end
		local pItem = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/droid_maint_module.iff", true)
		if pItem ~= nil then
			SceneObject(pItem):destroyObjectFromWorld()
			SceneObject(pItem):destroyObjectFromDatabase()
		end
	end

	if (isZoneEnabled(point.planet)) then
		SceneObject(pPlayer):switchZone(point.planet, point.x, 0, point.y, 0)
		print("Ejecting player " .. SceneObject(pPlayer):getCustomObjectName() .. " from corvette.")
	else
		print("Error: escape zone for corvette transfer is not enabled.")
	end
end
