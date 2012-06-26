--object/tangible/mission/quest_item/shared_warren_device_encryption_key.iff
--object/tangible/mission/quest_item/shared_warren_inquisitor_letter.iff

--object/intangible/data_item/shared_warren_encryption_key.iff
--object/intangible/data_item/shared_warren_evidence_01.iff
--object/intangible/data_item/shared_warren_evidence_02.iff
--object/intangible/data_item/shared_warren_evidence_03.iff
--object/intangible/data_item/shared_warren_evidence_04.iff

--object/mobile/shared_dressed_warren_cyborg_style_01.iff
--object/mobile/shared_dressed_warren_doctor_style_01.iff
--object/mobile/shared_warren_agro_droid_boss.iff
--object/mobile/shared_warren_agro_droid_s01.iff
--object/mobile/shared_warren_agro_droid_s02.iff
--object/mobile/shared_warren_agro_droid_s03.iff
--object/mobile/shared_warren_agro_droid_s04.iff
--object/mobile/shared_warren_bors_teraud.iff
--object/mobile/shared_warren_crazed_imperial.iff
--object/mobile/shared_warren_cyborg_huurton.iff
--object/mobile/shared_warren_cyborg_tuskcat.iff
--object/mobile/shared_warren_cyborg_worker.iff
--object/mobile/shared_warren_dim_u_loyalist.iff
--object/mobile/shared_warren_droideka_loyalist.iff
--object/mobile/shared_warren_dying_loyalist.iff
--object/mobile/shared_warren_insane_comp_sci.iff
--object/mobile/shared_warren_irradiated_worker_s01.iff
--object/mobile/shared_warren_irradiated_worker_s02.iff
--object/mobile/shared_warren_irradiated_worker_s03.iff
--object/mobile/shared_warren_janna_bel_arde.iff
--object/mobile/shared_warren_jerrd_sonclim.iff
--object/mobile/shared_warren_loyalist_commander.iff
--object/mobile/shared_warren_phy_hudgen.iff
--object/mobile/shared_warren_technician.iff
--object/mobile/shared_warren_teraud_loyalist_scientist.iff

ALPHABET = {"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"}

WarrenScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
		mirla = {started = 1, done = 2}
	},
	
	elevatorRelock = 120000, 
	
	lockedCells = {
		8575672
	},
	
	recycleMirla = 120000,
	
	frontDoor = {x = -552, z = 1, y = -3820},
	
	turret = {template = "object/installation/turret/turret_block_med.iff", x = 25.156, z = -20, y = -71.22, cell = 8575695, respawn = 120000},
	
	debris = {x = -54.5, z = -68, y = 0.7, cell = 8575723, respawn = 120000},
	
	terminals = {
		terminal_8575768 = {oid = 8575768, message = "@theme_park/warren/warren_system_messages:welcome_terminal", method="notifyTerminalMessage"},
		terminal_8575769 = {oid = 8575769, message = "@theme_park/warren/warren_system_messages:comm_terminal", method="notifyTerminalMessage"},
		terminal_8575770 = {oid = 8575770, message = "@theme_park/warren/warren_system_messages:diary_terminal", method="notifyTerminalMessage"},
		terminal_8575773 = {oid = 8575773, message = "@theme_park/warren/warren_system_messages:turret_pass_active", method="notifyTurretMessage"}
	},
	
	--Key is the container oid, value is a list of items to spawn in it.
	questItems = {
		container_8465549 = {oid=8465549, items={"object/tangible/mission/quest_item/warren_farewell_letter.iff"}, respawn=12000},
		container_8465550 = {oid=8465550, items={"object/tangible/mission/quest_item/warren_controlroom_passkey1.iff"}, respawn=12000},
		container_8555708 = {oid=8555708, items={"object/tangible/mission/quest_item/warren_controlroom_passkey2.iff"}, respawn=12000},
		container_8555709 = {oid=8555709, items={"object/tangible/mission/quest_item/warren_controlroom_passkey3.iff"}, respawn=12000},
		container_8555710 = {oid=8555710, items={"object/tangible/mission/quest_item/warren_controlroom_passkey4.iff"}, respawn=12000},
		container_8465551 = {oid=8465551, items={"object/tangible/mission/quest_item/warren_turret_sequence.iff"}, respawn=12000},
		container_8465598 = {oid=8465598, items={"object/tangible/mission/quest_item/warren_core_control_rod_s01.iff"}, respawn=12000},
		container_8465597 = {oid=8465597, items={"object/tangible/mission/quest_item/warren_core_control_rod_s02.iff"}, respawn=12000},
		container_8465580 = {oid=8465580, items={"object/tangible/mission/quest_item/warren_inquisitor_letter.iff"}, respawn=12000}
	},
	
	buildingID = 8575671,
	
	entranceKey = "object/tangible/mission/quest_item/warren_passkey_s01.iff"
}

--string/en/theme_park/warren/warren_system_messages.stf	22	turret_pass_deactivated	Turret Defense System has been DEACTIVED.

registerScreenPlay("WarrenScreenPlay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function WarrenScreenPlay:start()
	if (isZoneEnabled("dantooine")) then
		self:lockDoors()
		self:spawnActiveAreas()
		self:spawnSceneObjects()
		self:spawnMobiles()
		self:fillContainers()
		self:setupTerminals()
		self:initializeDungeon()
	end
end

function WarrenScreenPlay:lockDoors()
	local pBuilding = getSceneObject(self.buildingID)
	createObserver(ENTEREDBUILDING, "WarrenScreenPlay", "notifyEnteredWarren", pBuilding)
end

function WarrenScreenPlay:spawnActiveAreas()
end

function WarrenScreenPlay:spawnSceneObjects()
	local pDebris = spawnSceneObject("dantooine", "object/tangible/newbie_tutorial/debris.iff", self.debris.x, self.debris.z, self.debris.y, self.debris.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "WarrenScreenPlay", "notifyDebrisDestroyed", pDebris)
end

function WarrenScreenPlay:spawnMobiles()
	spawnMobile("dantooine", "oevitt_piboi", 1, -558, 0, -3736, 0, 0)
	spawnMobile("dantooine", "mirla", 1, -59.5, -76, -35.3, 26, 8575725)
	spawnMobile("dantooine", "manx_try", 1, 27, -54, -118.8, -62, 8575714)
	spawnMobile("dantooine", "dirk_maggin", 1, -56.1, -28, -89.4, -140, 8575700)
	
	--First Room
	spawnMobile("dantooine", "hostile_huurton", 180, -7.8, -20, -9.9, 53, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 180, 5.9, -20, -8.5, -83, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 180, -21.8, -20, -6.8, 91, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 180, -19, -20, -24.4, 57, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 180, 1.6, -20, -24.9, -45, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 180, 12.7, -20, -19.6, 67, 8575677)
	spawnMobile("dantooine", "hostile_huurton", 180, -25.8, -20, -28.2, 55, 8575677) 
	spawnMobile("dantooine", "warren_imperial_worker", 180, -2.3, -20, -21.7, -34, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 180, 1.5, -20, -12.6, 88, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -14.9, -20, -3.8, 174, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -19.1, -20, -23.5, -136, 8575677)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -3.6, -20, -19.9, -140, 8575677)
	
	--Second Room
	spawnMobile("dantooine", "warren_imperial_worker", 180, -23.6, -20, -50.2, 29, 8575678)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -28.2, -20, -47.8, 38, 8575678)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -26.1, -20, -36.7, 157, 8575678)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -5, -20, -48, -51, 8575678)
	spawnMobile("dantooine", "hostile_huurton", 180, -15.9, -20, -39.5, -144, 8575678)
	spawnMobile("dantooine", "hostile_huurton", 180, -22.5, -20, -39.4, -177, 8575678)
	spawnMobile("dantooine", "hostile_huurton", 180, -16.6, -20, -48.9, 57, 8575678)
	
	--Barracks
	spawnMobile("dantooine", "warren_imperial_worker", 180, -67.9, -18, -96.7, 78, 8575684)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -79.6, -18, -97.9, 18, 8575684)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -82, -18, -79.6, 41, 8575684)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -82.8, -18, -107, 153, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 180, -61.9, -18, -111.7, -44, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 180, -64.4, -18, -112.9, -42, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 180, -69.9, -18, -105.7, -14, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 180, -60.8, -18, -86.4, -14, 8575684)
	spawnMobile("dantooine", "hostile_huurton", 180, -69.8, -18, -73.2, 110, 8575684)
	
	--Droid Room
	spawnMobile("dantooine", "warren_scientist", 180, -23.8, -28, -40.2, 23, 8575689)
	spawnMobile("dantooine", "warren_scientist", 180, -23.2, -28, -42.3, 95, 8575689)
	spawnMobile("dantooine", "warren_scientist", 180, -25.6, -28, -45.8, 124, 8575689)
	spawnMobile("dantooine", "warren_scientist", 180, -1.2, -28, -39.4, 65, 8575689)
	spawnMobile("dantooine", "warren_scientist", 180, -0.3, -28, -41.9, 133, 8575689)
	spawnMobile("dantooine", "warren_scientist", 180, -2.3, -28, -44.6, -141, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 180, 6.8, -28, -52.3, -96, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 180, 9.1, -28, -37.1, -112, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 180, -14.6, -28, -31.7, -164, 8575689)
	spawnMobile("dantooine", "warren_agro_droid", 180, -33.4, -28, -38.4, 143, 8575689)
	spawnMobile("dantooine", "warren_agro_droid_boss", 180, 3.6, -28, -69, 0, 8575692)
	
	spawnMobile("dantooine", "warren_imperial_worker", 180, -59.6, -52, -71.7, -13, 8575709)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -61.4, -52, -70, -131, 8575709)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -65, -52, -72.5, 61, 8575709)
	spawnMobile("dantooine", "warren_imperial_worker", 180, -65.5, -52, -67.6, 150, 8575709)
	
	
	spawnMobile("dantooine", "hostile_huurton", 180, -71.8, -52, -11.9, 6, 8575719)
	spawnMobile("dantooine", "hostile_huurton", 180, -73.6, -52, -7.8, 170, 8575719)
	spawnMobile("dantooine", "hostile_huurton", 180, -60.9, -52, -9.8, -159, 8575719)
	spawnMobile("dantooine", "hostile_huurton", 180, -62.3, -52, -7.4, -173, 8575719)
	
	--Inquisitor Cell Room
	spawnMobile("dantooine", "warren_stormtrooper", 180, -16, -54, -140, -45, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -19.3, -54, -138.6, 60, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -20.9, -54, -132.8, 109, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -32.1, -54, -141.2, 45, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -30, -54, -143, 17, 8575716)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -30.4, -54, -138.3, 131, 8575716)
	
	spawnMobile("dantooine", "warren_imperial_officer", 180, -16.7, -54, -140.3, 25, 8575716)
	spawnMobile("dantooine", "warren_imperial_officer", 180, -16, -54, -145.6, -72, 8575716)
	spawnMobile("dantooine", "warren_imperial_officer", 180, -16.2, -54, -139.2, -136, 8575716)
	
	spawnMobile("dantooine", "teraud_loyalist", 180, -26.1, -54, -127.4, 100, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 180, -26.3, -54, -129.4, 58, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 180, -23.2, -54, -127.5, -47, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 180, -26, -54, -154.3, 18, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 180, -28.2, -54, -153.1, 39, 8575716)
	spawnMobile("dantooine", "teraud_loyalist", 180, -23, -54, -153.2, -9, 8575716)
	
	--Evidence Room 1
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 180, 75.6, -68, 19.1, -2, 8578736)
	spawnMobile("dantooine", "doctor_knag", 180, 95.7, -68, 38.8, 90, 8575737)
	
	--Evidence Room 2
	spawnMobile("dantooine", "warren_imperial_officer", 180, 6.3, -60, 36.6, 58, 8575731)
	spawnMobile("dantooine", "warren_imperial_officer", 180, 9.6, -60, 39.3, -166, 8575731)
	spawnMobile("dantooine", "warren_imperial_officer", 180, 5.3, -60, 29.4, 46, 8575731)
	spawnMobile("dantooine", "cyborg_slice_hound", 180, -11.7, -60, 37.7, 89, 8575731)
	spawnMobile("dantooine", "cyborg_slice_hound", 180, -13.3, -60, 34.1, 121, 8575731)
	spawnMobile("dantooine", "cyborg_slice_hound", 180, -7.3, -60, 28.2, 71, 8575731)
	
	spawnMobile("dantooine", "cyborg_bol", 180, -52.6, -52, 17, -90, 8575726)
	spawnMobile("dantooine", "warren_scientist", 180, -46.4, -52, 16.7, 0, 8575726)
	
	spawnMobile("dantooine", "warren_scientist", 180, -84.7, -52, 0, 3, 8575727)
	spawnMobile("dantooine", "warren_scientist", 180, -84.6, -52, 2.6, 2, 8575727)
	spawnMobile("dantooine", "warren_scientist", 180, -100.5, -52, 13.4, 78, 8575727)
	spawnMobile("dantooine", "warren_scientist", 180, -98.5, -52, 20.9, 22, 8575727)
	spawnMobile("dantooine", "warren_scientist", 180, -87.5, -52, 30.2, 139, 8575727)
	spawnMobile("dantooine", "warren_scientist", 180, -79.4, -52, 28.3, 90, 8575727)
	
	--Evidence Room 3
	spawnMobile("dantooine", "cyborg_dune_lizard", 180, -48.8, -52, 50.5, 0, 8575729)
	spawnMobile("dantooine", "cyborg_dune_lizard", 180, -62.4, -52, 51.7, 0, 8575729)
	
	--At St room
	spawnMobile("dantooine", "warren_altered_atst", 180, 25.7, -84, -28.8, 0, 8575745)
	
	--4 locks room
	spawnMobile("dantooine", "warren_agro_droid", 180, 16.9, -20, -95.4, 0, 8575696)
	spawnMobile("dantooine", "warren_agro_droid", 180, 23, -20, -105.2, 0, 8575696)
	spawnMobile("dantooine", "computer_scientist", 180, 40, -20, -109.5, -50, 8575696)
	
	--Big room in middle
	spawnMobile("dantooine", "teraud_loyalist", 180, -28.3, -52, -38.8, -48, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 180, -32.6, -52, -41.9, -28, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 180, -36.3, -52, -40.5, 32, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 180, 2.4, -52, -65.3, 112, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 180, 2.2, -52, -68.6, 102, 8575740)
	spawnMobile("dantooine", "teraud_loyalist", 180, 5.6, -52, -73, 49, 8575740)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -25.1, -52, -50.2, 143, 8575740)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -29.6, -52, -52.7, 107, 8575740)
	spawnMobile("dantooine", "warren_stormtrooper", 180, -26.2, -52, -55.5, -1, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 180, -23.1, -52, -67.5, 176, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 180, -22.5, -52, -69.2, -129, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 180, -29.1, -52, -71.3, 127, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 180, 16.6, -52, -35.4, 53, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 180, 20.1, -52, -37.6, -3, 8575740)
	spawnMobile("dantooine", "hostile_huurton", 180, 24.4, -52, -36.5, -30, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 180, -17.7, -52, -41.2, 50, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 180, -15.5, -52, -44, 18, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 180, -12.5, -52, -42.5, -48, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 180, 29, -52, -56.4, 121, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 180, 30.9, -52, -53.3, 126, 8575740)
	spawnMobile("dantooine", "warren_imperial_officer", 180, 34.4, -52, -50.7, 153, 8575740)
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 180, 11.7, -52, -57.7, 33, 8575740)
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 180, 14.1, -52, -58.6, 0, 8575740)
	spawnMobile("dantooine", "teraud_loyalist_cyborg", 180, 15.7, -52, -55.5, -51, 8575740)
	
	--Bors Teraud
	spawnMobile("dantooine", "bors_teraud", 180, 119.5, -52, 41.7, -171, 8575758)
end

function WarrenScreenPlay:fillContainers()
	for k, v in pairs(self.questItems) do
		local pContainer = getSceneObject(v.oid)
		
		if (pContainer ~= nil) then
			local container = LuaSceneObject(pContainer)
			
			container:setContainerComponent("RespawnContainerContentsComponent")
			container:setContainerInheritPermissionsFromParent(false)
			container:setContainerDefaultDenyPermission(MOVEIN)
			container:setContainerDefaultAllowPermission(OPEN + MOVEOUT)
			
			if (container:getContainerObjectsSize() < 1) then		
				for j, item in pairs(v.items) do
					giveItem(pContainer, item, -1)
				end
			end
		end
	end
end

function WarrenScreenPlay:setupTerminals()
	for k, v in pairs(self.terminals) do
		local pTerminal = getSceneObject(v.oid)
		
		if (pTerminal ~= nil) then
			createObserver(OBJECTRADIALOPENED, "WarrenScreenPlay", v.method, pTerminal)
		end
	end
	
	--Control Room Terminals
	local pTerminal = getSceneObject(8465559)
	createObserver(OBJECTRADIALOPENED, "WarrenScreenPlay", "notifyUseCRTerminal", pTerminal)
	pTerminal = getSceneObject(8465560)
	createObserver(OBJECTRADIALOPENED, "WarrenScreenPlay", "notifyUseCRTerminal", pTerminal)
	pTerminal = getSceneObject(8465561)
	createObserver(OBJECTRADIALOPENED, "WarrenScreenPlay", "notifyUseCRTerminal", pTerminal) 
	pTerminal = getSceneObject(8465562)
	createObserver(OBJECTRADIALOPENED, "WarrenScreenPlay", "notifyUseCRTerminal", pTerminal)  
	
	--MCR Elevator
	pTerminal = getSceneObject(8575772)
	
	if (pTerminal ~= nil) then
		local terminal = LuaSceneObject(pTerminal)
		terminal:setObjectMenuComponent("MCRElevatorMenuComponent")
	end
end

function WarrenScreenPlay:initializeDungeon()
	--Register spatial chat observer on turret terminal
	local pTerminal = getSceneObject(8575773)
	
	if (pTerminal ~= nil) then
		createObserver(SPATIALCHATRECEIVED, "WarrenScreenPlay", "notifyTurretTerminalChatReceived", pTerminal)
	end
	
	pTerminal = getSceneObject(8465579)
	
	if (pTerminal ~= nil) then
		createObserver(SPATIALCHATRECEIVED, "WarrenScreenPlay", "notifyInquisitorTerminalChatReceived", pTerminal)
	end

	self:activateTurret(nil)
	
	self:deactivateElevator()
	
	self:recycleMirlaPassword()
end

function WarrenScreenPlay:notifyUseCRTerminal(pTerminal, pPlayer)
	local terminal = LuaSceneObject(pTerminal)
	local creature = LuaCreatureObject(pPlayer)
	local pInventory = creature:getSlottedObject("inventory")
	
	if (pInventory == nil) then
		return
	end
	
	if (self:isMCRElevatorActive()) then
		return
	end
	
	local objectid = terminal:getObjectID()
	
	local pObj = nil
	
	if (objectid == 8465559) then
		pObj = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_controlroom_passkey1.iff", true)
		
		if (pObj ~= nil) then
			writeData("warren:elevator:lock1", 0)
		else
			terminal:showFlyText("theme_park/warren/warren_system_messages", "mcr_term_active", 0, 255, 0)
			return
		end
	elseif (objectid == 8465560) then
		pObj = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_controlroom_passkey2.iff", true)
		
		if (pObj ~= nil) then
			writeData("warren:elevator:lock2", 0)
		else
			terminal:showFlyText("theme_park/warren/warren_system_messages", "mcr_term_active", 0, 255, 0)
			return
		end
	elseif (objectid == 8465561) then
		pObj = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_controlroom_passkey3.iff", true)
		
		if (pObj ~= nil) then
			writeData("warren:elevator:lock3", 0)
		else
			terminal:showFlyText("theme_park/warren/warren_system_messages", "mcr_term_active", 0, 255, 0)
			return
		end
	elseif (objectid == 8465562) then
		pObj = getContainerObjectByTemplate(pInventory, "object/tangible/mission/quest_item/warren_controlroom_passkey4.iff", true)
		
		if (pObj ~= nil) then
			writeData("warren:elevator:lock4", 0)
		else
			terminal:showFlyText("theme_park/warren/warren_system_messages", "mcr_term_active", 0, 255, 0)
			return
		end
	else
		return
	end
	
	if (self:isMCRElevatorActive()) then
		--Then they must've just activated it? right?
		createEvent(self.elevatorRelock, "WarrenScreenPlay", "deactivateElevator", pTerminal)
	end
	
	terminal:showFlyText("theme_park/warren/warren_system_messages", "mcr_term_deactivated", 0, 255, 0)
end

function WarrenScreenPlay:isMCRElevatorActive()
	local lock1 = readData("warren:elevator:lock1")
	local lock2 = readData("warren:elevator:lock2")
	local lock3 = readData("warren:elevator:lock3")
	local lock4 = readData("warren:elevator:lock4")
	
	if (lock1 == 0) and (lock2 == 0) and (lock3 == 0) and (lock4 == 0) then
		return true
	end
	
	return false
end

function WarrenScreenPlay:recycleMirlaPassword()
	local code = self:generatePasscode(5)
	writeData("warren:mirla:password", code)
	
	createEvent(self.recyleMirla, "WarrenScreenPlay", "recycleMirlaPassword", nil)
end

function WarrenScreenPlay:generatePasscode(length)
	local code = ''
	
	for i = 1, length, 1 do
		code = code .. ALPHABET[math.random(1,26)]
	end
	
	return code
end

function WarrenScreenPlay:givePasskey1(pPlayer)
	if (pPlayer == nil) then
		return
	end
	
	local player = LuaSceneObject(pPlayer)
	local pPlayerObject = player:getSlottedObject("ghost")
	local playerObject = LuaPlayerObject(pPlayerObject)
	playerObject:addPermissionGroup("warren", true)
	local pInventory = player:getSlottedObject("inventory")
	
	if (pInventory == nil) then
		return
	end
	
	local pItem = giveItem(pInventory, self.entranceKey, -1)
	
	if (pItem ~= nil) then
		local item = LuaSceneObject(pItem)
		item:sendTo(pPlayer)
	end
end

function WarrenScreenPlay:respawnDebris(pDebris)
	if (pDebris == nil) then
		return
	end
	
	local pCell = getSceneObject(self.debris.cell)
	
	if (pCell ~= nil) then
		local cell = LuaSceneObject(pCell)
		local debris = LuaTangibleObject(pDebris)
		debris:setConditionDamage(0, false)
		cell:transferObject(pDebris, -1, true)
	end
end

function WarrenScreenPlay:notifyDebrisDestroyed(pDebris, pPlayer)
	local player = LuaCreatureObject(pPlayer)
	local debris = LuaSceneObject(pDebris)
	debris:destroyObjectFromWorld()
	player:clearCombatState(1)
	
	createEvent(self.debris.respawn, "WarrenScreenPlay", "respawnDebris", pDebris)
	
	return 0
end

function WarrenScreenPlay:deactivateElevator()
	writeData("warren:elevator:lock1", 1)
	writeData("warren:elevator:lock2", 1)
	writeData("warren:elevator:lock3", 1)
	writeData("warren:elevator:lock4", 1)
end

function WarrenScreenPlay:notifyEnteredWarren(pBuilding, pPlayer)
	local obj = LuaSceneObject(pPlayer)
	
	if (not obj:isPlayerCreature()) then
		return
	end
	
	local creature = LuaCreatureObject(pPlayer)
	
	local pInventory = obj:getSlottedObject("inventory")
	
	if (pInventory ~= nil) then
		local pItem = getContainerObjectByTemplate(pInventory, self.entranceKey, true)
		
		if (pItem ~= nil) then
			creature:sendSystemMessage("@theme_park/warren/warren_system_messages:access_granted") --ACCESS GRANTED: Passkey code accepted. Welcome to this Imperial Research Facility
		else
			creature:sendSystemMessage("@theme_park/warren/warren_system_messages:access_denied") --ACCESS DENIED:  YOU DO NOT HAVE THE PROPER PASSKEY TO ENTER THIS FACILITY
			--Kick them out to the front door.
			obj:teleport(self.frontDoor.x, self.frontDoor.z, self.frontDoor.y, 0)
		end
	end
	
	return 0
end

function WarrenScreenPlay:activateTurret(pTerminal)
	local objectID = readData("warren:turret:objectid")
	local pTurret = getSceneObject(objectID)
	
	if (pTurret ~= nil) then
		local pCell = getSceneObject(self.turret.cell)
	
		if (pCell ~= nil) then
			local cell = LuaSceneObject(pCell)
			local turret = LuaSceneObject(pTurret)
			cell:transferObject(pTurret, -1, true)
		end
	else
		local pTurret = spawnSceneObject("dantooine", self.turret.template, self.turret.x, self.turret.z, self.turret.y, self.turret.cell, -0.707107, 0, 0.707107, 0)
		
		if (pTurret ~= nil) then
			local turret = LuaSceneObject(pTurret)
			writeData("warren:turret:objectid", turret:getObjectID())
		end
	end
	
	local code = self:generatePasscode(4)
	writeStringData("warren:turret:code", code)
	writeData("warren:turret:active", 1)
end

function WarrenScreenPlay:deactivateTurret(pTerminal)
	writeData("warren:turret:active", 0)
	
	if (pTerminal ~= nil) then
		local terminal = LuaSceneObject(pTerminal)
		terminal:showFlyText("theme_park/warren/warren_system_messages", "turret_pass_deactivated", 0, 255, 0)
		
		local objectID = readData("warren:turret:objectid")
		local pTurret = getSceneObject(objectID)
		
		if (pTurret ~= nil) then
			local turret = LuaSceneObject(pTurret)
			turret:destroyObjectFromWorld()
		end
	end
	
	createEvent(self.turret.respawn, "WarrenScreenPlay", "activateTurret", pTerminal)
end

function WarrenScreenPlay:refillContainer(pContainer)
	if (pContainer == nil) then
		return
	end
	
	local container = LuaSceneObject(pContainer)
	
	if (container:getContainerObjectsSize() > 0) then
		return
	end
	
	local objectID = container:getObjectID()
	
	for k, item in pairs(self.questItems["container_" .. objectID].items) do
		giveItem(pContainer, item, -1)
	end
end

function WarrenScreenPlay:notifyTerminalMessage(pTerminal, pPlayer)
	local terminal = LuaSceneObject(pTerminal)
	local message = self.terminals["terminal_" .. terminal:getObjectID()].message
	
	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pTerminal, pPlayer, "@sui:swg", message, "@ok", "WarrenScreenPlay", "notifyOkPressed")
	
	return 0
end

function WarrenScreenPlay:notifyTurretMessage(pTerminal, pPlayer)
	local message = "@theme_park/warren/warren_system_messages:turret_pass_active"
	
	if (readData("warren:turret:active") == 0) then
		message = "@theme_park/warren/warren_system_messages:turret_pass_inactive"
	end

	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pTerminal, pPlayer, "@sui:swg", message, "@ok", "WarrenScreenPlay", "notifyOkPressed")
	
	return 0
end

function WarrenScreenPlay:notifyTurretTerminalChatReceived(pTerminal, pChatMessage)
	if (readData("warren:turret:active") == 0) then
		return 0
	end
	
	local msg = getChatMessage(pChatMessage)

	if (msg == readStringData("warren:turret:code")) then
		self:deactivateTurret(pTerminal)
	end
	
	return 0
end

function WarrenScreenPlay:notifyInquisitorTerminalChatReceived(pTerminal, pChatMessage, objectID)
	local msg = getChatMessage(pChatMessage)
	
	if (msg == readData("warren:mirla:password")) then
		
	end
end

function WarrenScreenPlay:notifyOkPressed()
end

WarrenTurrentMenuComponent = {}

function WarrenTurrentMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local suiManager = LuaSuiManager()
	suiManager:sendMessageBox(pSceneObject, pPlayer, "@sui:swg", readStringData("warren:turret:code"), "@ok", "WarrenScreenPlay", "notifyOkPressed")
end

function WarrenTurrentMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
end

MCRElevatorMenuComponent = {}

function MCRElevatorMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(199, 3, "@elevator_text:down")
end

function MCRElevatorMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	local creature = LuaCreatureObject(pPlayer)

	if (selectedID ~= 199) or (not WarrenScreenPlay:isMCRElevatorActive()) then
		creature:sendSystemMessage("This elevator terminal is locked.")
		return
	end

	local obj = LuaSceneObject(pSceneObject)
	
	if (creature:getParent() ~= obj:getParent()) then
		return
	end
	
	local z = creature:getPositionZ() - 10	
	local x = creature:getPositionX()
	local y = creature:getPositionY()
	
	creature:playEffect("clienteffect", "elevator_descend.cef")	
	creature:teleport(x, z, y, obj:getParentID())
end

RespawnContainerContentsComponent = {}

function RespawnContainerContentsComponent:transferObject(pContainer, pObj, slot)
	return -1
end

function RespawnContainerContentsComponent:canAddObject(pContainer, pObj, slot)
	return -1
end

function RespawnContainerContentsComponent:removeObject(pContainer, pObj, slot)	
	if (pContainer ~= nil) then
		local container = LuaSceneObject(pContainer)
		createEvent(WarrenScreenPlay.questItems["container_" .. container:getObjectID()].respawn, "WarrenScreenPlay", "refillContainer", pContainer)
	end
	
	return -1
end


--Convo Handlers
OevittPiboiConversationHandler = Object:new {
}

function OevittPiboiConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	
	local screenID = screen:getScreenID()
	
	if (screenID == "escapee_2") then
		WarrenScreenPlay:givePasskey1(pConversingPlayer)
	end
	
	return pConversationScreen
end

function OevittPiboiConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	
	if (pInventory ~= nil) then
		local pPasskey = getContainerObjectByTemplate(pInventory, WarrenScreenPlay.entranceKey, true)
		
		if (pPasskey ~= nil) then
			return convoTemplate:getScreen("escapee_haskey")
		end
	end
	
	return convoTemplate:getScreen("escapee_start")
end

function OevittPiboiConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local player = LuaCreatureObject(pPlayer)
	local pConversationSession = player:getConversationSession()
	
	local pLastConversationScreen = nil
	
	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end
	
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	
	if (pLastConversationScreen ~= nil) then	
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)
		
		return conversationTemplate:getScreen(optionLink)
	end
	
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end



MirlaConversationHandler = Object:new {
}

function MirlaConversationHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNPC, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	
	local screenID = screen:getScreenID()
	
	if (screenID == "mirla_password") then
		local screen = LuaConversationScreen(pConversationScreen)
		local code = readData("warren:mirla:password")
		screen:setDialogTextTO(code)
	elseif (screenID == "mirla_2") then
		local player = LuaCreatureObject(pConversingPlayer)
		local pPlayerObject = player:getPlayerObject()
		
		if (pPlayerObject) then
			local playerObject = LuaPlayerObject(pPlayerObject)
			playerObject:awardBadge(38) --Warren Compassion
			player:setScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren");
		end
	end
	
	return pConversationScreen
end

function MirlaConversationHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	
	local player = LuaCreatureObject(pPlayer)
	
	if (player:hasScreenPlayState(WarrenScreenPlay.states.mirla.done, "warren") == 1) then
		return convoTemplate:getScreen("mirla_done")
	elseif (player:hasScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren") == 1) then
		return convoTemplate:getScreen("mirla_get_teraud")
	end
	
	return convoTemplate:getScreen("mirla_start")
end

function MirlaConversationHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local player = LuaCreatureObject(pPlayer)
	local pConversationSession = player:getConversationSession()
	
	local pLastConversationScreen = nil
	
	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end
	
	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
	
	if (pLastConversationScreen ~= nil) then	
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)
		
		return conversationTemplate:getScreen(optionLink)
	end
	
	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
