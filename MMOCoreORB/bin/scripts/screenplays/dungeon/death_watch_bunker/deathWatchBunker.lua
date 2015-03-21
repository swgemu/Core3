local ObjectManager = require("managers.object.object_manager")

DeathWatchBunkerScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	passkey = {
		hall = "object/tangible/dungeon/death_watch_bunker/passkey_hall.iff",
		storage = "object/tangible/dungeon/death_watch_bunker/passkey_storage.iff",
		mine = "object/tangible/dungeon/death_watch_bunker/passkey_mine.iff"
	},

	buildingIds = {
		outside = 5996315,
		entrance = 5996316,
		areaA = 5996326,
		areaB = 5996338,
		mines = 5996352,
		armorArea = 5996374,
		droidEngineerArea = 5996370,
		tailorArea = 5996368
	},

	bunkerItems = {
		alumMineral = "object/tangible/loot/dungeon/death_watch_bunker/mining_drill_reward.iff",
		mandoHelmet = "object/tangible/wearables/armor/mandalorian/armor_mandalorian_helmet.iff",
		mandoRebreather = "object/tangible/wearables/goggles/rebreather.iff",
		filter = "object/tangible/dungeon/death_watch_bunker/filter.iff",
		enhancedFilter = "object/tangible/dungeon/death_watch_bunker/enhanced_filter.iff",
		alumGel = "object/tangible/dungeon/death_watch_bunker/gel_packet.iff",
		medicine = "object/tangible/dungeon/death_watch_bunker/crazed_miner_medicine.iff",
		drillBattery = "object/tangible/dungeon/death_watch_bunker/drill_battery.iff",
		drillBatteryClean = "object/tangible/dungeon/death_watch_bunker/drill_battery_clean.iff",
		jetPackBase = "object/tangible/loot/dungeon/death_watch_bunker/jetpack_base.iff",
		jetPackStabilizer = "object/tangible/loot/dungeon/death_watch_bunker/jetpack_stabilizer.iff",
		ductedFan = "object/tangible/loot/dungeon/death_watch_bunker/ducted_fan.iff",
		injectorTank = "object/tangible/loot/dungeon/death_watch_bunker/fuel_injector_tank.iff",
		dispersionUnit = "object/tangible/loot/dungeon/death_watch_bunker/fuel_dispersion_unit.iff",
		binaryLiquid = "object/tangible/loot/dungeon/death_watch_bunker/binary_liquid.iff",
		protectiveLiquid = "object/tangible/loot/dungeon/death_watch_bunker/emulsion_protection.iff"
	},

	targetItems = {
		--Armorsmith Crafting Terminal
		{ "object/tangible/wearables/armor/mandalorian/armor_mandalorian_chest_plate.iff",
			"object/tangible/wearables/armor/mandalorian/armor_mandalorian_shoes.iff",
			"object/tangible/wearables/armor/mandalorian/armor_mandalorian_bicep_l.iff",
			"object/tangible/wearables/armor/mandalorian/armor_mandalorian_bicep_r.iff" },
		--Droid Engineer Crafting Terminal
		{ "object/tangible/wearables/armor/mandalorian/armor_mandalorian_helmet.iff",
			"object/tangible/wearables/armor/mandalorian/armor_mandalorian_bracer_l.iff",
			"object/tangible/wearables/armor/mandalorian/armor_mandalorian_bracer_r.iff" },
		--Tailor Crafting Terminal
		{ "object/tangible/wearables/armor/mandalorian/armor_mandalorian_leggings.iff",
			"object/tangible/wearables/armor/mandalorian/armor_mandalorian_gloves.iff",
			"object/tangible/wearables/armor/mandalorian/armor_mandalorian_belt.iff" },
		-- Jetpack Crafting Terminal
		{ "object/tangible/deed/vehicle_deed/jetpack_deed.iff" },
	},

	doorData = {
		{ cellAccess = 5996316, lockTime = 10, doorType = 1 }, -- Entrance
		{ cellAccess = 5996326, lockTime = 10, doorType = 2 }, -- Area A
		{ cellAccess = 5996338, lockTime = 10, doorType = 2 }, -- Area B
		{ cellAccess = 5996352, lockTime = 10, doorType = 2 }, -- Mines
		{ cellAccess = 5996374, lockTime = 6, doorType = 3 }, -- Armorsmith area
		{ cellAccess = 5996370, lockTime = 6, doorType = 3 }, -- DE area
		{ cellAccess = 5996368, lockTime = 6, doorType = 3 } -- Tailor area
	},

	states = {
		2,--entrance unlocked
		4,--terminal a unlocked
		8,--terminal b unlocked
		16,--terminal mines unlocked
		32,--armorsmith door unlocked
		64,--droidengineer door unlocked
		128--tailor door unlocked
	},

	doorMessages = {
		{ unlock = "@dungeon/death_watch:access_granted", lock = "@dungeon/death_watch:terminal_locked" },
		{ unlock = "@dungeon/death_watch:access_granted", lock = "@dungeon/death_watch:terminal_locked" },
		{ unlock = "@dungeon/death_watch:access_granted", lock = "@dungeon/death_watch:terminal_locked" },
		{ unlock = "@dungeon/death_watch:access_granted", lock = "@dungeon/death_watch:terminal_locked" },
		{ unlock = "@dungeon/death_watch:unlock_door", lock = "@dungeon/death_watch:room_in_use" },
		{ unlock = "@dungeon/death_watch:unlock_door", lock = "@dungeon/death_watch:room_in_use" },
		{ unlock = "@dungeon/death_watch:unlock_door", lock = "@dungeon/death_watch:room_in_use" }
	},

	requiredDoorItems = {
		{ },
		{ "object/tangible/dungeon/death_watch_bunker/passkey_hall.iff" },
		{ "object/tangible/dungeon/death_watch_bunker/passkey_storage.iff" },
		{ "object/tangible/dungeon/death_watch_bunker/passkey_mine.iff" },

		--ARMORSMITHDOOR
		{	"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_chest_plate.iff",
			"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_boots.iff",
			"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bicep_l.iff",
			"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bicep_r.iff"
		},

		--DROIDENGINEERDOOR
		{	"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_helmet.iff",
			"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bracer_l.iff",
			"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bracer_r.iff"
		},

		--TAILORDOOR
		{	"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_leggings.iff",
			"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_gloves.iff",
			"object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_belt.iff" },

		-- Jetpack Crafting Terminal
		{ "object/tangible/deed/vehicle_deed/jetpack_deed.iff" },
	},

	partStrings = { "@dungeon/death_watch:armorsmith_items", "@dungeon/death_watch:droid_engineer_items", "@dungeon/death_watch:tailored_items" },

	terminalSkills = { "", "", "", "", "crafting_armorsmith_master", "crafting_droidengineer_master", "crafting_tailor_master", "crafting_artisan_master" },

	terminalSkillMessage = { "@dungeon/death_watch:master_armorsmith_required", "@dungeon/death_watch:master_droidengineer_required", "@dungeon/death_watch:master_tailor_required", "@dungeon/death_watch:master_artisan_required" },

	missingSkillMessage = { "", "", "", "", "@dungeon/death_watch:not_enough_armorsmith_skill", "@dungeon/death_watch:not_enough_droidengineer_skill", "@dungeon/death_watch:not_enough_tailor_skill" },

	mineCells = { 5996352, 5996353, 5996354, 5996355, 5996356, 5996357, 5996358, 5996359, 5996360, 5996361, 5996362, 5996363, 5996364,
		5996365, 5996366, 5996367, 5996369, 5996372, 5996373, 5996375, 5996376, 5996377 },

	deathWatchValveEffects = { {42.2316,-30.5,-72.5555}, {56.0941,-30.5,-61.251}, {73.7982,-30.5,-76.4291}, {55.5855,-30.5,-92.8} },
	ventDroidPatrolPoints = {
		{{-19.9,-52.0,-131.0,5996345},{6.0,-52.0,-130.8, 5996345},{5.4,-52.0,-120.4,5996379},{-6.2, -52, -120.8,5996379}},
		{{-21.8, -52, -117.4,5996379},{-21.8, -52, -114.3,5996379},{-5.7, -54.1, -112,5996379}},
	},

	spawnGroups = { "", "terminalAnextSpawn", "terminalBnextSpawn", "terminalCnextSpawn" },

	spawnEvents = { "", "spawnNextA", "spawnNextB", "spawnNextC" },

	containerRespawnTime = 20 * 60 * 1000, -- 20 minutes
	debrisRespawnTime = 10 * 60 * 1000, -- 10 minutes

	primaryArmorColors = { 48, 55, 60, 95, 111, 127, 135, 143 },
	secondaryArmorColors = { 42, 90, 236, 244, 252, 253, 254, 255 }
}

registerScreenPlay("DeathWatchBunkerScreenPlay", true)

function DeathWatchBunkerScreenPlay:start()
	if (isZoneEnabled("endor")) then
		local pBunker = getSceneObject(5996314)

		if pBunker == nil then
			return 0
		end

		self:spawnObjects()
		self:spawnMobiles()
		self:setupPermissionGroups()

		writeData("dwb:ventDroidAvailable", 1)

		createEvent(1000 * 45, "DeathWatchBunkerScreenPlay", "poisonEvent", pBunker)
		createObserver(ENTEREDBUILDING, "DeathWatchBunkerScreenPlay", "onEnterDWB", pBunker)
		createObserver(EXITEDBUILDING, "DeathWatchBunkerScreenPlay", "onExitDWB", pBunker)
	end
end

function DeathWatchBunkerScreenPlay:setupPermissionGroups()
	for i = 1, #self.doorData, 1 do
		local pCell = getSceneObject(self.doorData[i].cellAccess)
		if pCell ~= nil then
			ObjectManager.withSceneObject(pCell, function(cell)
				cell:setContainerInheritPermissionsFromParent(false)
				cell:clearContainerDefaultDenyPermission(WALKIN)
				cell:clearContainerDefaultAllowPermission(WALKIN)
				cell:setContainerAllowPermission("DeathWatchBunkerDoor" .. i, WALKIN)
				cell:setContainerDenyPermission("DeathWatchBunkerDoor" .. i, MOVEIN)
			end)
		end
	end
end

function DeathWatchBunkerScreenPlay:givePermission(pPlayer, permissionGroup)
	ObjectManager.withCreaturePlayerObject(pPlayer, function(ghost)
		ghost:addPermissionGroup(permissionGroup, true)
	end)
end

function DeathWatchBunkerScreenPlay:removePermission(pPlayer, permissionGroup)
	ObjectManager.withCreaturePlayerObject(pPlayer, function(ghost)
		if (ghost:hasPermissionGroup(permissionGroup)) then
			ghost:removePermissionGroup(permissionGroup, true)
		end
	end)
end

function DeathWatchBunkerScreenPlay:hasPermission(pPlayer, permissionGroup)
	return ObjectManager.withCreaturePlayerObject(pPlayer, function(ghost)
		return ghost:hasPermissionGroup(permissionGroup)
	end)
end

function DeathWatchBunkerScreenPlay:spawnMobiles()
	for i,v in ipairs(deathWatchStaticSpawns) do
		spawnMobile("endor", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
	end
	for i,v in ipairs(deathWatchQuestNpcs) do
		spawnMobile("endor", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
	end
end

function DeathWatchBunkerScreenPlay:spawnObjects()
	local spawnedSceneObject = LuaSceneObject(nil)
	local spawnedPointer

	-- Door Access Terminal Outside
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -18.016,-12,-8.55806, 5996315, 1, 0, 0, 0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access1", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 1)

	-- Outside locked door message
	local pActiveArea = spawnActiveArea("endor", "object/active_area.iff", -4680.6, 0.4, 4324.5, 5, 5996315)
	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "DeathWatchBunkerScreenPlay", "notifyEnteredOutsideLockedDoorArea", pActiveArea)
	end

	-- Door Access Terminal A
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -84.4526,-20,-50.504,5996323,-0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access2", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 2)

	-- Door Access Terminal B
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -8.3714,-32,-95.3985,5996331,-0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access3", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 3)

	-- Door Access Terminal Mines
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", 26.1493,-64,-95.4288,5996347,0,0,1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	writeData(5996314 .. ":dwb:access4", spawnedSceneObject:getObjectID())
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 4)

	-- Voice Recognition Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",74.7941,-54,-143.444,5996348,-0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Voice Control Terminal")
	createObserver(SPATIALCHATRECEIVED, "DeathWatchBunkerScreenPlay", "voiceTerminalSpatialReceived", spawnedPointer)

	-- Voice Terminal Instruction message
	local pActiveArea = spawnActiveArea("endor", "object/active_area.iff", -4588, -41.6, 4182.3, 10, 5996348)
	if pActiveArea ~= nil then
		createObserver(ENTEREDAREA, "DeathWatchBunkerScreenPlay", "notifyEnteredVoiceTerminalArea", pActiveArea)
	end

	--Blastromech
	local spawn = deathWatchSpecialSpawns["bombdroid"]
	local spawnedPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	CreatureObject(spawnedPointer):setPvpStatusBitmask(0)
	CreatureObject(spawnedPointer):setCustomObjectName("R2-M2")
	AiAgent(spawnedPointer):setAiTemplate("idlewait") -- Don't move unless patrol point is added to list
	AiAgent(spawnedPointer):setFollowState(4) -- Patrolling
	writeData("dwb:bombDroid", SceneObject(spawnedPointer):getObjectID())
	createObserver(OBJECTDESTRUCTION, "DeathWatchBunkerScreenPlay", "bombDroidDetonated", spawnedPointer)

	-- Bomb Droid Debris
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/invulnerable_debris.iff", 112.552,-63.7,-116.21,5996348,0.925444,0,0.378885,0)
	writeData("dwb:bombDebris", SceneObject(spawnedPointer):getObjectID())
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/invulnerable_debris.iff", 113.134,-63.8,-149.44,5996348,0.376442,0,0.92644,0)
	writeData("dwb:bombDebris2", SceneObject(spawnedPointer):getObjectID())

	-- Armorsmith Access Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -232.11,-60,-219.996,5996373,0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Armorsmith Crafting Room Entry Terminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 5)

	-- Droid Engineer Crafting Room Entry Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -230.09,-60,-124.003,5996367,0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Droid Engineer Crafting Room Entry Terminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 6)

	-- Master Armorsmith Crafting Droid
	local spawn = deathWatchSpecialSpawns["armorsmithdroid"]

	spawnedPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Crafting Droid")
	spawnedSceneObject:setContainerComponent("deathWatchCraftingDroid")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 1)

	local droidId = spawnedSceneObject:getObjectID()

	-- Armorsmith Crafting Terminal (Biceps, Chest, Boots)
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-246.097,-60,-245.163,5996374,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
	spawnedSceneObject:setObjectMenuComponent("deathWatchMandalorianCraftingTerminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droidId)


	-- Master Droid Engineer Crafting Droid
	spawn = deathWatchSpecialSpawns["droidengineerdroid"]
	spawnedPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Crafting Droid")
	spawnedSceneObject:setContainerComponent("deathWatchCraftingDroid")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 2)

	droidId = spawnedSceneObject:getObjectID()

	-- Master Droid Engineer Crafting Terminal (Bracer, Helmet)
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-234.536,-40,-84.8062,5996370,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
	spawnedSceneObject:setObjectMenuComponent("deathWatchMandalorianCraftingTerminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 2)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droidId)


	-- Master Tailor Crafting Droid
	spawn = deathWatchSpecialSpawns["tailordroid"]
	spawnedPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Crafting Droid")
	spawnedSceneObject:setContainerComponent("deathWatchCraftingDroid")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 3)

	droidId = spawnedSceneObject:getObjectID()

	-- Tailor Crafting Terminal (Pants, Gloves, Belt)
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-141.981,-60,-74.3199,5996368,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
	spawnedSceneObject:setObjectMenuComponent("deathWatchMandalorianCraftingTerminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 3)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droidId)

	-- Jetpack Crafting Droid
	spawn = deathWatchSpecialSpawns["jetpackdroid"]
	spawnedPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Jetpack Crafting Droid")
	spawnedSceneObject:setContainerComponent("deathWatchJetpackCraftingDroid")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 4)

	droidId = spawnedSceneObject:getObjectID()

	-- Master Artisan Crafting Terminal (Jetpack)
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/terminal_free_s1.iff",-265.425,-50.0002,-84.957,5996370,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Mandalorian Engineering Unit")
	spawnedSceneObject:setObjectMenuComponent("deathWatchMandalorianCraftingTerminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:craftingterminal", 4)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:droid", droidId)

	-- Tailor Access Terminal
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/door_control_terminal.iff", -151.045,-60,-98.8703,5996365,0,0,1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Tailor Crafting Room Entry Terminal")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:accessEnabled", 1)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 7)

	-- Spawn Haldo
	local halnum = getRandomNumber(1,3)
	spawn = deathWatchSpecialSpawns["haldo" .. halnum]
	spawnedPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	spawnedSceneObject:_setObject(spawnedPointer)
	createObserver(DAMAGERECEIVED, "DeathWatchBunkerScreenPlay", "haldoDamage", spawnedPointer)

	-- Water Pressure Valve Control A
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",42.2316,-32,-72.5555,5996340,-0.707107,0,-0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("deathWatchWaterValve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 1)
	writeData("dwb:valve1", 1)
	self:spawnValveEffect(1, 1)

	-- Water Pressure Valve Control B
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",56.0941,-32,-61.251,5996340,0,0,-1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("deathWatchWaterValve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 2)
	writeData("dwb:valve2", 1)
	self:spawnValveEffect(2, 1)

	-- Water Pressure Valve Control C
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",73.7982,-32,-76.4291,5996340,0.707107,0,-0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("deathWatchWaterValve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 3)
	writeData("dwb:valve3", 0)
	self:spawnValveEffect(3, 0)

	-- Water Pressure Valve Control D
	spawnedPointer = spawnSceneObject("endor","object/tangible/terminal/terminal_water_pressure.iff",55.5855,-32,-92.8,5996340,1,0,0,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	spawnedSceneObject:setObjectMenuComponent("deathWatchWaterValve")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:terminal", 4)
	writeData("dwb:valve4", 1)
	self:spawnValveEffect(4, 1)

	-- Rebreather Filter Dispenser
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/filter_dispenser.iff",-12.8382,-52,-147.565,5996378,0,0,1,0)

	-- Rebreather Workbench
	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/workbench.iff",-16.2596,-52,-147.091,5996378,0,0,1,0)

	-- Loot Boxes
	spawnedPointer = spawnSceneObject("endor", "object/tangible/container/general/tech_chest.iff", -3.10801,-12,36.7064,5996318,0,0,-1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	self:setLootBoxPermissions(spawnedPointer)
	spawnedSceneObject:setCustomObjectName("Chest")
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:lootbox", 1)
	createEvent(1000, "DeathWatchBunkerScreenPlay", "refillContainer", spawnedPointer)
	createObserver(OBJECTRADIALUSED, "DeathWatchBunkerScreenPlay", "boxLooted", spawnedPointer)

	spawnedPointer = spawnSceneObject("endor", "object/tangible/dungeon/coal_bin_container.iff",6.01353,-32,-102.05,5996337,0.707107,0,0.707107,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	self:setLootBoxPermissions(spawnedPointer)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:lootbox", 2)
	createEvent(1000, "DeathWatchBunkerScreenPlay", "refillContainer", spawnedPointer)
	createObserver(OBJECTRADIALUSED, "DeathWatchBunkerScreenPlay", "boxLooted", spawnedPointer)

	spawnedPointer = spawnSceneObject("endor", "object/tangible/container/loot/placable_loot_crate_tech_armoire.iff", -2.78947,-32,-27.1899,5996335,0,0,1,0)
	spawnedSceneObject:_setObject(spawnedPointer)
	self:setLootBoxPermissions(spawnedPointer)
	writeData(spawnedSceneObject:getObjectID() .. ":dwb:lootbox", 3)
	createEvent(1000, "DeathWatchBunkerScreenPlay", "refillContainer", spawnedPointer)
	createObserver(OBJECTRADIALUSED, "DeathWatchBunkerScreenPlay", "boxLooted", spawnedPointer)
end

function DeathWatchBunkerScreenPlay:setLootBoxPermissions(pContainer)
	ObjectManager.withSceneObject(pContainer, function(container)
		container:setContainerInheritPermissionsFromParent(false)
		container:setContainerDefaultDenyPermission(MOVEIN)
		container:setContainerDefaultAllowPermission(OPEN + MOVEOUT)
	end)
end

function DeathWatchBunkerScreenPlay:onEnterDWB(sceneObject, creatureObject)
	return ObjectManager.withCreatureObject(creatureObject, function(creature)
		if (creature:isAiAgent()) then
			return 0
		end

		self:lockAll(creatureObject)

		return 0
	end)
end

function DeathWatchBunkerScreenPlay:onExitDWB(sceneObject, creatureObject, long)
	return ObjectManager.withCreatureObject(creatureObject, function(creature)
		if (creature:isAiAgent() == true) then
			return 0
		end

		if long == self.buildingIds.outside or long == 0 then
			self:lockAll(creatureObject)
		end

		return 0
	end)
end

function DeathWatchBunkerScreenPlay:diedWhileCrafting(pCreature, pAttacker, long)
	if pCreature == nil then
		return 1
	end

	local isCrafting = readData(CreatureObject(pCreature):getObjectID() .. ":dwb:currentlycrafting")

	if iscrafting == 0 then
		return 1
	else
		local id = readData(CreatureObject(pCreature):getObjectID() .. ":dwb:terminal")
		if id ~= 0 then
			local pTerminal = getSceneObject(id)
			if pTerminal ~= nil then
				CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:died_during_crafting")
				self:stopCraftingProcess(pCreature, pTerminal, false, false)
			end
		end
	end
	return 1
end

function DeathWatchBunkerScreenPlay:enableAccess(pSceneObject)
	writeData(SceneObject(pSceneObject):getObjectID() .. ":dwb:accessEnabled", 1)
end

function DeathWatchBunkerScreenPlay:respawnHaldo(creatureObject)
	local halNum = getRandomNumber(1,3)
	local spawn = deathWatchSpecialSpawns["haldo" .. halNum]
	local spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	createObserver(DAMAGERECEIVED, "DeathWatchBunkerScreenPlay", "haldoDamage", spawnPointer)
end

function DeathWatchBunkerScreenPlay:boxLooted(pSceneObject, pCreature, selectedID)
	if selectedID ~= 16 then
		return 0
	end

	if readData(SceneObject(pSceneObject):getObjectID() .. ":dwb:spawned") == 1 then
		return 0
	else
		local boxId = readData(SceneObject(pSceneObject):getObjectID() .. ":dwb:lootbox")
		writeData(SceneObject(pSceneObject):getObjectID() .. ":dwb:spawned", 1)

		--spawn enemies
		if boxId == 1 then
			local spawn = deathWatchSpecialSpawns["lootbox1mob1"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		elseif boxId == 2 then
			local spawn = deathWatchSpecialSpawns["lootbox2mob1"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		elseif boxId == 3 then
			local spawn = deathWatchSpecialSpawns["lootbox3mob1"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
			local spawn = deathWatchSpecialSpawns["lootbox3mob2"]
			spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		end

		createEvent(self.containerRespawnTime, "DeathWatchBunkerScreenPlay", "refillContainer", pSceneObject)
	end

	return 0
end

function DeathWatchBunkerScreenPlay:refillContainer(pSceneObject)
	if (pSceneObject == nil) then
		return
	end

	writeData(SceneObject(pSceneObject):getObjectID() .. ":dwb:spawned", 0)

	if (SceneObject(pSceneObject):getContainerObjectsSize() == 0) then
		createLoot(pSceneObject, "death_watch_bunker_lootbox", 1, false)
		if getRandomNumber(100) > 95 then
			createLoot(pSceneObject, "death_watch_bunker_lootbox", 1, false)
		end
	end
end

function DeathWatchBunkerScreenPlay:poisonEvent(pSceneObject)
	if (readData("dwb:ventsEnabled") == 0) then
		for i,v in ipairs(self.mineCells) do
			local pCell = getSceneObject(v)
			if pCell ~= nil then
				local cellSize = SceneObject(pCell):getContainerObjectsSize()

				for j = 0, cellSize - 1, 1 do
					local pObject = SceneObject(pCell):getContainerObject(j)

					if pObject ~= nil then
						if (SceneObject(pObject):isCreatureObject() and not CreatureObject(pObject):isAiAgent() and not self:hasRebreather(pObject)
							and not CreatureObject(pObject):isDead() and not CreatureObject(pObject):isIncapacitated()) then
							self:doPoison(pObject)
						end
					end
				end
			end
		end
	end
	createEvent(1000 * 45, "DeathWatchBunkerScreenPlay", "poisonEvent", pSceneObject)
end

function DeathWatchBunkerScreenPlay:timeWarning(pCreature)
	if pCreature == nil then
		return
	end

	if (readData(CreatureObject(pCreature):getObjectID() .. ":teleportedFromBunker") == 1) then
		return
	end

	if (CreatureObject(pCreature):isGrouped()) then
		local groupSize = CreatureObject(pCreature):getGroupSize()

		for i = 0, groupSize - 1, 1 do
			local pMember = CreatureObject(pCreature):getGroupMember(i)
			if pMember ~= nil then
				if CreatureObject(pMember):getParentID() > 5996313 and CreatureObject(pMember):getParentID() < 5996380 then
					CreatureObject(pMember):sendSystemMessage("@dungeon/death_watch:thirty_seconds")
				end
			end
		end
	else
		CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:thirty_seconds")
	end
end

function DeathWatchBunkerScreenPlay:removeFromBunker(pCreature)
	if (pCreature == nil) then
		return 0
	end

	if (CreatureObject(pCreature):isGrouped()) then
		local groupSize = CreatureObject(pCreature):getGroupSize()

		for i = 0, groupSize - 1, 1 do
			local pMember = CreatureObject(pCreature):getGroupMember(i)
			if pMember ~= nil then
				if CreatureObject(pMember):getParentID() > 5996313 and CreatureObject(pMember):getParentID() < 5996380 then
					createEvent(500, "DeathWatchBunkerScreenPlay", "teleportPlayer", pMember)
				end
			end
		end
	else
		createEvent(500, "DeathWatchBunkerScreenPlay", "teleportPlayer", pCreature)
	end
end

function DeathWatchBunkerScreenPlay:teleportPlayer(pCreature)
	if (pCreature == nil) then
		return 0
	end

	if (readData(CreatureObject(pCreature):getObjectID() .. ":teleportedFromBunker") == 1 or CreatureObject(pCreature):getParentID() == self.buildingIds.outside or CreatureObject(pCreature):getParentID() == 0) then
		return 0
	end

	writeData(CreatureObject(pCreature):getObjectID() .. ":teleportedFromBunker", 1)
	CreatureObject(pCreature):teleport(-4657, 14.4, 4322.3, 0)
	self:lockAll(pCreature)
end

function DeathWatchBunkerScreenPlay:voiceTerminalSpatialReceived(pTerminal, pChatMessage, playerID)
	local pPlayer = getSceneObject(playerID)

	if (pPlayer == nil or CreatureObject(pPlayer):isAiAgent()) then
		return 0
	end

	if (not SceneObject(pTerminal):isInRangeWithObject(pPlayer, 10)) then
		return 0
	elseif (not SceneObject(pTerminal):isInRangeWithObject(pPlayer, 3)) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:too_far_from_terminal")
		return 0
	end

	local bombDroidHandlerID = readData("dwb:bombDroidHandler")
	local terminalUserID = CreatureObject(pPlayer):getObjectID()

	if (bombDroidHandlerID == 0) then
		writeData("dwb:bombDroidHandler", terminalUserID)
		writeData("dwb:bombDroidHandlerLastUse", os.time())
	elseif (bombDroidHandlerID ~= terminalUserID) then
		local lastTerminalUse = readData("dwb:bombDroidHandlerLastUse")
		if (os.difftime(os.time(), lastTerminalUse) < 120) then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:terminal_in_use")
			return 0
		else
			writeData("dwb:bombDroidHandler", bombDroidHandlerID)
			writeData("dwb:bombDroidHandlerLastUse", os.time())
		end
	end

	local spatialMsg = getChatMessage(pChatMessage)

	local tokenizer = {}
	for word in spatialMsg:gmatch("%w+") do table.insert(tokenizer, word) end

	local spatialCommand = tokenizer[1]
	local moveDistance = 0

	if (spatialCommand == "reset") then
		local lastDetonate = readData("dwb:lastDroidDetonate")
		if (lastDetonate ~= 0 and os.difftime(os.time(), lastDetonate) < 180) then
			CreatureObject(pPlayer):sendSystemMessage("@dungeon/death_watch:reload_voice_pattern")
			return 0
		end
		self:respawnBombDroid()
		return 0
	end

	local bombDroidID = readData("dwb:bombDroid")
	local pBombDroid = getSceneObject(bombDroidID)

	if (pBombDroid == nil or not SceneObject(pBombDroid):isAiAgent()) then
		return 0
	end

	if (spatialCommand == "detonate") then
		CreatureObject(pBombDroid):playEffect("clienteffect/combat_grenade_proton.cef", "")
		CreatureObject(pBombDroid):inflictDamage(pBombDroid, 0, 1000000, 1)
		writeData("dwb:lastDroidDetonate", os.time())
		return 0
	end

	if (tokenizer[2] ~= nil) then
		moveDistance = tonumber(tokenizer[2])

		if (moveDistance == nil) then
			return 0
		end

		if (moveDistance > 10) then
			moveDistance = 10
		elseif (moveDistance <= 0) then
			moveDistance = 1
		end
	end

	local droidLoc = { x = SceneObject(pBombDroid):getPositionX(), z = SceneObject(pBombDroid):getPositionZ(), y = SceneObject(pBombDroid):getPositionY(), cell = SceneObject(pBombDroid):getParentID() }

	if (spatialCommand == "forward") then
		droidLoc.x = droidLoc.x + moveDistance
		if (droidLoc.x > 115) then
			droidLoc.x = 115
		end
	elseif (spatialCommand == "backward") then
		droidLoc.x = droidLoc.x - moveDistance
		if (droidLoc.x < 76) then
			droidLoc.x = 76
		end
	elseif (spatialCommand == "left") then
		droidLoc.y = droidLoc.y + moveDistance
		if (droidLoc.y > -114) then
			droidLoc.y = -114
		end
	elseif (spatialCommand == "right") then
		droidLoc.y = droidLoc.y - moveDistance
		if (droidLoc.y < -152) then
			droidLoc.y = -152
		end
	end

	local pCell = getSceneObject(droidLoc.cell)

	if (pCell == nil) then
		return 0
	end

	AiAgent(pBombDroid):stopWaiting()
	AiAgent(pBombDroid):setWait(0)
	AiAgent(pBombDroid):setNextPosition(droidLoc.x, droidLoc.z, droidLoc.y, pCell)
	AiAgent(pBombDroid):executeBehavior()

	return 0
end

function DeathWatchBunkerScreenPlay:notifyEnteredVoiceTerminalArea(pArea, pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if (player:isAiAgent()) then
			return 0
		end

		player:sendSystemMessage("@dungeon/death_watch:rc_mouse_instructions")
		return 0
	end)
end

function DeathWatchBunkerScreenPlay:notifyEnteredOutsideLockedDoorArea(pArea, pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		if (player:isAiAgent()) then
			return 0
		end

		if (player:hasScreenPlayState(1, "death_watch_bunker") == 0) then
			player:sendSystemMessage("@dungeon/death_watch:entrance_denied")
		end

		return 0
	end)
end

function DeathWatchBunkerScreenPlay:bombDroidDetonated(pBombDroid, pBombDroid2)
	if (pBombDroid == nil) then
		return 1
	end

	local debrisID = readData("dwb:bombDebris")
	local debrisID2 = readData("dwb:bombDebris2")

	local pDebris = getSceneObject(debrisID)
	local pDebris2 = getSceneObject(debrisID2)

	if (pDebris == nil and pDebris2 == nil) then
		return 1
	end

	if (pDebris ~= nil and SceneObject(pBombDroid):isInRangeWithObject(pDebris, 5)) then
		SceneObject(pDebris):playEffect("clienteffect/combat_grenade_proton.cef", "")
		createEvent(1000, "DeathWatchBunkerScreenPlay", "destroyDebris", pDebris)
	elseif (pDebris2 ~= nil and SceneObject(pBombDroid):isInRangeWithObject(pDebris2, 5)) then
		SceneObject(pDebris2):playEffect("clienteffect/combat_grenade_proton.cef", "")
		createEvent(1000, "DeathWatchBunkerScreenPlay", "destroyDebris", pDebris2)
	end

	return 1
end

function DeathWatchBunkerScreenPlay:respawnDebris(pOldDebris)
	local oldDebrisID = SceneObject(pOldDebris):getObjectID()
	if (oldDebrisID == readData("dwb:bombDebris")) then
		local pDebris = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/invulnerable_debris.iff", 112.552,-64,-116.21,5996348,0.925444,0,0.378885,0)
		writeData("dwb:bombDebris", SceneObject(pDebris):getObjectID())
	elseif (oldDebrisID == readData("dwb:bombDebris2")) then
		local pDebris = spawnSceneObject("endor", "object/tangible/dungeon/death_watch_bunker/invulnerable_debris.iff", 113.134,-64,-149.44,5996348,0.376442,0,0.92644,0)
		writeData("dwb:bombDebris2", SceneObject(pDebris):getObjectID())
	end
end

function DeathWatchBunkerScreenPlay:destroyDebris(pDebris)
	if (pDebris ~= nil) then
		createEvent(self.debrisRespawnTime, "DeathWatchBunkerScreenPlay", "respawnDebris", pDebris)
		SceneObject(pDebris):destroyObjectFromWorld()
	end
end

function DeathWatchBunkerScreenPlay:respawnBombDroid(pDroid)
	local spawn = deathWatchSpecialSpawns["bombdroid"]
	local pBombDroid = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	CreatureObject(pBombDroid):setPvpStatusBitmask(0)
	CreatureObject(pBombDroid):setCustomObjectName("R2-M2")
	AiAgent(pBombDroid):setAiTemplate("idlewait") -- Don't move unless patrol point is added to list
	AiAgent(pBombDroid):setFollowState(4) -- Patrolling
	writeData("dwb:bombDroid", SceneObject(pBombDroid):getObjectID())
	createObserver(OBJECTDESTRUCTION, "DeathWatchBunkerScreenPlay", "bombDroidDetonated", pBombDroid)
end

function DeathWatchBunkerScreenPlay:haldoTimer(pCreature)
	ObjectManager.withCreatureObject(pCreature, function(creature)
		if creature:hasScreenPlayState(4, "death_watch_foreman_stage") == 0 then
			creature:removeScreenPlayState(1, "death_watch_foreman_stage")
			creature:removeScreenPlayState(2, "death_watch_foreman_stage")
			creature:removeScreenPlayState(4, "death_watch_foreman_stage")
			creature:sendSystemMessage("@dungeon/death_watch:haldo_failed")
			if (creature:hasScreenPlayState(2, "death_watch_haldo") == 0) then
				creature:removeScreenPlayState(1, "death_watch_haldo")
			end
		end
	end)
end

function DeathWatchBunkerScreenPlay:haldoKilled(pHaldo, pPlayer)
	createEvent(1000 * 240, "DeathWatchBunkerScreenPlay", "respawnHaldo", pPlayer)
	return ObjectManager.withCreatureObject(pPlayer, function(creature)
		if (creature:hasScreenPlayState(2, "death_watch_foreman_stage") == 1 and creature:hasScreenPlayState(4, "death_watch_foreman_stage") == 0) then
			local pInventory = creature:getSlottedObject("inventory")
			if (pInventory == nil) then
				creature:sendSystemMessage("Error: Unable to find player inventory.")
			else
				if (SceneObject(pInventory):hasFullContainerObjects() == true) then
					creature:sendSystemMessage("@error_message:inv_full")
					return 1
				else
					local pBattery = getContainerObjectByTemplate(pInventory, "object/tangible/dungeon/death_watch_bunker/drill_battery.iff", true)
					if (pBattery == nil) then
						pBattery = giveItem(pInventory,"object/tangible/dungeon/death_watch_bunker/drill_battery.iff", -1)
						if (pBattery == nil) then
							creature:sendSystemMessage("Error: Unable to generate item.")
						else
							creature:sendSystemMessage("@dungeon/death_watch:recovered_battery")
							creature:setScreenPlayState(4, "death_watch_haldo")
						end
					end
				end
			end
		end

		return 1
	end)
end

function DeathWatchBunkerScreenPlay:haldoDamage(pHaldo, pPlayer, damage)
	if pHaldo == nil or pPlayer == nil then
		return 1
	end

	return ObjectManager.withCreatureObject(pHaldo, function(haldo)
		if ((haldo:getHAM(0) <= (haldo:getMaxHAM(0) * 0.9)) or (haldo:getHAM(3) <= (haldo:getMaxHAM(3) * 0.9)) or (haldo:getHAM(6) <= (haldo:getMaxHAM(6) * 0.9))) then
			local spawnLoc = { x = haldo:getPositionX(), z = haldo:getPositionZ(), y = haldo:getPositionY(), cell = haldo:getParentID(), angle = haldo:getDirectionAngle() }
			local spawnHam = { h = haldo:getHAM(0), a = haldo:getHAM(3), m = haldo:getHAM(6) }
			SceneObject(pHaldo):destroyObjectFromWorld()

			local pNewHaldo = spawnMobile("endor", "mand_bunker_crazed_miner_converse", 0, spawnLoc.x, spawnLoc.z, spawnLoc.y, spawnLoc.angle, spawnLoc.cell)

			if (pNewHaldo == nil) then
				return 1
			end
			CreatureObject(pNewHaldo):setPvpStatusBitmask(0)
			CreatureObject(pNewHaldo):setHAM(0, spawnHam.h)
			CreatureObject(pNewHaldo):setHAM(3, spawnHam.a)
			CreatureObject(pNewHaldo):setHAM(6, spawnHam.m)

			spatialChat(pNewHaldo, "@dungeon/death_watch:help_me")
		end

		return 1
	end)
end

function DeathWatchBunkerScreenPlay:spawnAggroHaldo(pOldHaldo, pPlayer)
	ObjectManager.withCreatureObject(pOldHaldo, function(haldo)
		local spawnLoc = { x = haldo:getPositionX(), z = haldo:getPositionZ(), y = haldo:getPositionY(), cell = haldo:getParentID(), angle = haldo:getDirectionAngle() }
		local spawnHam = { h = haldo:getHAM(0), a = haldo:getHAM(3), m = haldo:getHAM(6) }
		SceneObject(pOldHaldo):destroyObjectFromWorld()

		local pNewHaldo = spawnMobile("endor", "mand_bunker_crazed_miner", 0, spawnLoc.x, spawnLoc.z, spawnLoc.y, spawnLoc.angle, spawnLoc.cell)

		if (pNewHaldo == nil) then
			return
		end

		CreatureObject(pNewHaldo):setHAM(0, spawnHam.h)
		CreatureObject(pNewHaldo):setHAM(3, spawnHam.a)
		CreatureObject(pNewHaldo):setHAM(6, spawnHam.m)

		createObserver(OBJECTDESTRUCTION, "DeathWatchBunkerScreenPlay", "haldoKilled", pNewHaldo)
		spatialChat(pNewHaldo, "@conversation/death_watch_insane_miner:s_99f3d3be")
		CreatureObject(pNewHaldo):engageCombat(pPlayer)
	end)
end

function DeathWatchBunkerScreenPlay:pumpTimer(pCreature)
	ObjectManager.withCreatureObject(pCreature, function(creature)
		if creature:hasScreenPlayState(64, "death_watch_foreman_stage") == 0 then
			creature:removeScreenPlayState(32, "death_watch_foreman_stage")
			creature:setScreenPlayState(2, "death_watch_foreman_stage_failed")
			creature:sendSystemMessage("@dungeon/death_watch:water_pressure_failed")
		end
	end)
end

function DeathWatchBunkerScreenPlay:destroyIngredient(pIngredient)
	if pIngredient ~= nil then
		SceneObject(pIngredient):destroyObjectFromWorld()
		SceneObject(pIngredient):destroyObjectFromDatabase()
	end
end

--------------------------------------------------------------
--   Key Spawn Events                                        -
--------------------------------------------------------------
function DeathWatchBunkerScreenPlay:spawnNextA(pCreature)
	local nextSpawn = readData(5996314 .. ":dwb:terminalAnextSpawn")

	if nextSpawn == 0 then
		return 0
	elseif nextSpawn == 1 then
		writeData(5996314 .. ":dwb:terminalAnextSpawn", 2)
		local spawn = deathWatchSpecialSpawns["rageon_vart_assist1"]
		createEvent((getRandomNumber(0, 10) + 30) * 1000, "DeathWatchBunkerScreenPlay", "spawnNextA", pCreature)
		local spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 102)
	elseif nextSpawn == 2 then
		writeData(5996314 .. ":dwb:terminalAnextSpawn", 3)
		local spawn = deathWatchSpecialSpawns["rageon_vart_assist2"]
		createEvent((getRandomNumber(0, 10) + 30) * 1000, "DeathWatchBunkerScreenPlay", "spawnNextA", pCreature)
		local spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 40)
	else
		writeData(5996314 .. ":dwb:terminalAnextSpawn", 0)
		local spawn = deathWatchSpecialSpawns["rageon_vart"]
		spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	end
end

function DeathWatchBunkerScreenPlay:spawnNextB(pCreature)
	local nextSpawn = readData(5996314 .. ":dwb:terminalBnextSpawn")

	if nextSpawn == 0 then
		return 0
	elseif nextSpawn == 1 then
		writeData(5996314 .. ":dwb:terminalBnextSpawn", 2)
		local spawn = deathWatchSpecialSpawns["klin_nif_assist1"]
		createEvent((getRandomNumber(0, 10) + 30) * 1000, "DeathWatchBunkerScreenPlay", "spawnNextB", pCreature)
		local spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 31)
	elseif nextSpawn == 2 then
		writeData(5996314 .. ":dwb:terminalBnextSpawn", 3)
		local spawn = deathWatchSpecialSpawns["klin_nif_assist2"]
		createEvent((getRandomNumber(0, 10) + 30) * 1000, "DeathWatchBunkerScreenPlay", "spawnNextB", pCreature)
		local spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 67)
	else
		writeData(5996314 .. ":dwb:terminalBnextSpawn", 0)
		local spawn = deathWatchSpecialSpawns["klin_nif"]
		spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	end
end

function DeathWatchBunkerScreenPlay:spawnNextC(creatureObject)
	local nextSpawn = readData(5996314 .. ":dwb:terminalCnextSpawn")
	if nextSpawn == 0 then
		return 0
	elseif nextSpawn == 1 then
		writeData(5996314 .. ":dwb:terminalCnextSpawn", 2)
		local spawn = deathWatchSpecialSpawns["fenri_dalso_assist1"]
		createEvent((getRandomNumber(0, 10) + 30) * 1000, "DeathWatchBunkerScreenPlay", "spawnNextC", creatureObject)
		local spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 37)
	elseif nextSpawn == 2 then
		writeData(5996314 .. ":dwb:terminalCnextSpawn", 3)
		local spawn = deathWatchSpecialSpawns["fenri_dalso_assist2"]
		createEvent((getRandomNumber(0, 10) + 30) * 1000, "DeathWatchBunkerScreenPlay", "spawnNextC", creatureObject)
		local spawnPointer = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spatialMoodChat(spawnPointer, "@dungeon/death_watch:call_back_up", 21)
	else
		writeData(5996314 .. ":dwb:terminalCnextSpawn", 0)
		local spawn = deathWatchSpecialSpawns["fenri_dalso_add1"]
		spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawn = deathWatchSpecialSpawns["fenri_dalso_add2"]
		spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawn = deathWatchSpecialSpawns["fenri_dalso_add3"]
		spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawn = deathWatchSpecialSpawns["fenri_dalso_add4"]
		spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawn = deathWatchSpecialSpawns["fenri_dalso"]
		spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
	end
end

--   DeathWatchBunkerScreenPlay whether a creature has sufficient skill to access a particular crafting room
function DeathWatchBunkerScreenPlay:hasRequiredSkill(room, pCreature)
	if (room < 1 or room > 8) then
		return false
	end

	return CreatureObject(pCreature):hasSkill(self.terminalSkills[room])
end

-- Checks whether a creature has an Alum Mineral
function DeathWatchBunkerScreenPlay:hasAlumMineral(pCreature)
	if pCreature == nil then
		return false
	end

	local pInventory = SceneObject(pCreature):getSlottedObject("inventory")

	if (pInventory == nil) then
		return false
	end

	return getContainerObjectByTemplate(pInventory, self.bunkerItems.alumMineral, true) ~= nil
end

-- Checks whether a creature has all necessary items to access a particular crafting room  -
function DeathWatchBunkerScreenPlay:findRequiredItem(room, pCreature)
	if (pCreature == nil) then
		return nil
	end

	if (room < 1 or room > 7) then
		return nil
	end

	local pInventory = SceneObject(pCreature):getSlottedObject("inventory")

	if (pInventory == nil) then
		return nil
	end

	local table = self.requiredDoorItems[room]

	for i,v in ipairs(table) do
		local pObj = getContainerObjectByTemplate(pInventory, v, true)
		if (pObj ~= nil) then
			return pObj
		end
	end
	return nil
end

--   Checks whether a creature has sufficient protection against alum mine poison  -
function DeathWatchBunkerScreenPlay:hasRebreather(pSceneObject)
	local pRebreather = SceneObject(pSceneObject):getSlottedObject("eyes")

	if (pRebreather == nil) then
		return false
	end

	local headSlot = SceneObject(pRebreather):getTemplateObjectPath()

	if (headSlot == self.bunkerItems.mandoRebreather) then
		return SceneObject(pRebreather):getCustomObjectName() == "Advanced Rebreather"
	elseif (headSlot == self.bunkerItems.mandoHelmet) then
		return true
	end
	return false
end

--   Inflict poison damage on a creature
function DeathWatchBunkerScreenPlay:doPoison(pCreature)
	if pCreature == nil then
		return 0
	end

	CreatureObject(pCreature):inflictDamage(pCreature, 0, 100, 0)
	CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:bad_air")
end

--   Lock all restricted cells to a creature  -
function DeathWatchBunkerScreenPlay:lockAll(pCreature)
	ObjectManager.withCreatureObject(pCreature, function(creature)
		creature:removeScreenPlayState(2, "death_watch_bunker")
		creature:removeScreenPlayState(4, "death_watch_bunker")
		creature:removeScreenPlayState(8, "death_watch_bunker")
		creature:removeScreenPlayState(16, "death_watch_bunker")
		creature:removeScreenPlayState(32, "death_watch_bunker")
		creature:removeScreenPlayState(64, "death_watch_bunker")
		creature:removeScreenPlayState(128, "death_watch_bunker")

		for i = 1, #self.doorData, 1 do
			self:removePermission(pCreature, "DeathWatchBunkerDoor" .. i)
		end

		creature:sendSystemMessage("@dungeon/death_watch:relock")
	end)
end

function DeathWatchBunkerScreenPlay:spawnDefenders(number, pCreature)
	if number < 1 or number > 4 then
		return 0
	end

	if number == 1 then
		local spawn = deathWatchSpecialSpawns["entrance1"]
		local spawnPointer1 = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		spawn = deathWatchSpecialSpawns["entrance2"]
		local spawnPointer2 = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])

		if pCreature ~= nil then
			CreatureObject(spawnPointer1):engageCombat(pCreature)
			CreatureObject(spawnPointer2):engageCombat(pCreature)
		end
	else
		writeData(5996314 .. ":dwb:" .. self.spawnGroups[number], 1)
		createEvent(2 * 1000, "DeathWatchBunkerScreenPlay", self.spawnEvents[number], pCreature)
	end
end

function DeathWatchBunkerScreenPlay:unlockForGroup(number, pCreature, cells)
	ObjectManager.withCreatureObject(pCreature, function(creature)
		-- screenplaystates for login/logout
		if (creature:isGrouped()) then
			local groupSize = creature:getGroupSize()

			for i = 0, groupSize - 1, 1 do
				local pMember = creature:getGroupMember(i)
				if pMember ~= nil then
					local groupMember = LuaCreatureObject(pMember)

					local parentID = groupMember:getParentID()

					if (cells and parentID > 5996313 and parentID < 5996380) or ((not cells) and groupMember:getZoneName() == "endor") then
						groupMember:setScreenPlayState(self.states[number], "death_watch_bunker")
						self:givePermission(pMember, "DeathWatchBunkerDoor" .. number)
						groupMember:sendSystemMessage(self.doorMessages[number].unlock)
					end
				end
			end
		else
			creature:setScreenPlayState(self.states[number], "death_watch_bunker")
			self:givePermission(pCreature, "DeathWatchBunkerDoor" .. number)
			creature:sendSystemMessage(self.doorMessages[number].unlock)
		end
	end)
end

function DeathWatchBunkerScreenPlay:checkDoor(pSceneObject, pCreature)
	if pCreature == nil or pSceneObject == nil then
		return
	end

	ObjectManager.withCreatureObject(pCreature, function(creature)
		local doorEnabled = readData(SceneObject(pSceneObject):getObjectID() .. ":dwb:accessEnabled")
		local doorNumber = readData(SceneObject(pSceneObject):getObjectID() .. ":dwb:terminal")

		local doorType = self.doorData[doorNumber].doorType

		if doorType == 1 then
			local state = creature:hasScreenPlayState(1, "death_watch_bunker")
			if state == 0 then
				if (doorEnabled == 0) then
					creature:sendSystemMessage(self.doorMessages[doorNumber].lock)
					return
				end

				creature:sendGroupMessage("@dungeon/death_watch:airlock_backup")
				self:spawnDefenders(doorNumber, pCreature)
			else
				self:unlockForGroup(doorNumber, pCreature, false)
				return
			end
		elseif doorType == 2 then
			local requiredItem = self:findRequiredItem(doorNumber, pCreature)
			if (requiredItem == nil) then
				if (doorEnabled == 0) then
					creature:sendSystemMessage(self.doorMessages[doorNumber].lock)
					return
				end

				creature:sendGroupMessage("@dungeon/death_watch:denied_access")
				self:spawnDefenders(doorNumber, pCreature)
			else
				self:unlockForGroup(doorNumber, pCreature, true)
				SceneObject(requiredItem):destroyObjectFromWorld()
				SceneObject(requiredItem):destroyObjectFromDatabase()
				return
			end
		elseif doorType == 3 then
			if (doorEnabled == 0) then
				creature:sendSystemMessage(self.doorMessages[doorNumber].lock)
				return
			end

			if (self:findRequiredItem(doorNumber, pCreature) == nil or self:hasAlumMineral(pCreature) == false) then
				creature:sendSystemMessage("@dungeon/death_watch:not_enough_ingredients")
				return
			end

			if (self:hasRequiredSkill(doorNumber, pCreature) == false) then
				creature:sendSystemMessage(self.missingSkillMessage[doorNumber])
				return
			end

			self:unlockForGroup(doorNumber, pCreature, true)

			local pCell = getSceneObject(self.doorData[doorNumber].cellAccess)
			if pCell == nil then
				return
			end

			if (creature:isGrouped()) then
				local groupSize = creature:getGroupSize()

				for i = 0, groupSize - 1, 1 do
					local pMember = creature:getGroupMember(i)
					if pMember ~= nil then
						writeData(CreatureObject(pMember):getObjectID() .. ":teleportedFromBunker", 0)
					end
				end
			else
				writeData(creature:getObjectID() .. ":teleportedFromBunker", 0)
			end

			createEvent(1000 * 60 * 5, "DeathWatchBunkerScreenPlay", "removeFromBunker", pCreature)
			createEvent(1000 * 60 * 4.5, "DeathWatchBunkerScreenPlay", "timeWarning", pCreature)
			createEvent(1000 * 60 * 5.5, "DeathWatchBunkerScreenPlay", "despawnCell", pCell)
		end

		writeData(SceneObject(pSceneObject):getObjectID() .. ":dwb:accessEnabled", 0)
		createEvent(1000 * 60 * self.doorData[doorNumber].lockTime, "DeathWatchBunkerScreenPlay", "enableAccess", pSceneObject)
	end)
end

function DeathWatchBunkerScreenPlay:despawnCell(pCell)
	if pCell == nil then
		return
	end

	local cellSize = SceneObject(pCell):getContainerObjectsSize()
	for i = 0, cellSize - 1, 1 do
		local pObject = SceneObject(pCell):getContainerObject(i)
		if pObject ~= nil then
			if SceneObject(pObject):isCreatureObject() then
				local template = SceneObject(pObject):getTemplateObjectPath()

				if string.find(template, "death_watch") ~= nil or string.find(template, "battle_droid") ~= nil then
					createEvent(1000, "DeathWatchBunkerScreenPlay", "despawnCreature", pObject)
				end
			end
		end
	end
end

function DeathWatchBunkerScreenPlay:despawnCreature(pObject)
	if pObject ~= nil then
		SceneObject(pObject):destroyObjectFromWorld()
	end
end

function DeathWatchBunkerScreenPlay:startForemanQuestStage(number, pCreature)
	if pCreature == nil then
		return
	end

	if number == 1 then
		createEvent(1000 * 60 * 60, "DeathWatchBunkerScreenPlay", "haldoTimer", pCreature)
	elseif number == 2 then
		createEvent(1000 * 60 * 60, "DeathWatchBunkerScreenPlay", "pumpTimer", pCreature)
	end
end

function DeathWatchBunkerScreenPlay:storeTime(pCreature)
	if pCreature ~= nil then
		local time = os.time()
		writeScreenPlayData(pCreature, "DeathWatchBunkerScreenPlay", "time", time)
	end
end

function DeathWatchBunkerScreenPlay:checkTime(pCreature)
	if pCreature == nil then
		return false
	end

	local currentTime = os.time()
	local receivedTime = readScreenPlayData(pCreature, "DeathWatchBunkerScreenPlay", "time")

	if receivedTime == "" then
		return false
	end

	local seconds = os.difftime(currentTime, receivedTime)

	if (seconds > 216000) then --more then 60 hours passed
		return true
	end

	return false
end

function DeathWatchBunkerScreenPlay:cancelCrafting(pTerm)
	if pTerm == nil then
		return
	end

	local isCrafting = readData(SceneObject(pTerm):getObjectID() .. ":dwb:currentlycrafting")

	if isCrafting > 0 and isCrafting < 4 then
		local id = readData(SceneObject(pTerm):getObjectID() .. ":dwb:user")
		if id ~= 0 then
			local pCreature = getSceneObject(id)
			if pCreature ~= nil then
				CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:took_too_long")
				self:stopCraftingProcess(pCreature, pTerm, false, true)
			end
		end
	end
end

function DeathWatchBunkerScreenPlay:stopCraftingProcess(pCreature, pTerm, successful, teleport)
	if pCreature == nil or pTerm == nil then
		return
	end

	ObjectManager.withSceneObject(pTerm, function(terminal)
		local number = readData(terminal:getObjectID() .. ":dwb:craftingterminal")
		local target = readData(terminal:getObjectID() .. ":dwb:targetitemindex")

		writeData(CreatureObject(pCreature):getObjectID() .. ":dwb:currentlycrafting", 0)
		writeData(terminal:getObjectID() .. ":dwb:currentlycrafting", 0)

		if successful == true then
			local creo = LuaSceneObject(pCreature)
			local pInventory = creo:getSlottedObject("inventory")

			if (pInventory == nil) then
				return 0
			end

			local targetItems = self.targetItems[number]
			local pReward = giveItem(pInventory, targetItems[target], -1)


			CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:crafting_finished")

			if (pReward == nil) then
				CreatureObject(pCreature):sendSystemMessage("Error: Unable to generate item.")
				return 0
			end

			if (number ~= 4) then
				TangibleObject(pReward):setCustomizationVariable("/private/index_color_1", self.primaryArmorColors[getRandomNumber(1,8)])
				TangibleObject(pReward):setCustomizationVariable("/private/index_color_2", self.secondaryArmorColors[getRandomNumber(1,8)])
			end
		end


		writeData(CreatureObject(pCreature):getObjectID() .. ":dwb:terminal", 0)
		writeData(terminal:getObjectID() .. ":dwb:user", 0)
		writeData(terminal:getObjectID() .. ":dwb:targetitemindex", 0)


		if number == 4 then
			writeData(terminal:getObjectID() .. ":dwb:alummineral", 0)
			writeData(terminal:getObjectID() .. ":dwb:jetpackbase", 0)
			writeData(terminal:getObjectID() .. ":dwb:jetpackstabilizer", 0)
			writeData(terminal:getObjectID() .. ":dwb:ductedfan", 0)
			writeData(terminal:getObjectID() .. ":dwb:injectortank", 0)
			writeData(terminal:getObjectID() .. ":dwb:dispersionunit", 0)
		else
			writeData(terminal:getObjectID() .. ":dwb:alummineral", 0)
			writeData(terminal:getObjectID() .. ":dwb:binary", 0)
			writeData(terminal:getObjectID() .. ":dwb:protective", 0)
			writeData(terminal:getObjectID() .. ":dwb:bharmorpart", 0)
		end

		if teleport == true then
			if (number == 4) then
				createEvent(5000, "DeathWatchBunkerScreenPlay", "removeFromBunker", pCreature)
			else
				createEvent(500, "DeathWatchBunkerScreenPlay", "teleportPlayer", pCreature)
			end
		end
	end)
end

function DeathWatchBunkerScreenPlay:sendUseTerminalMessage(pCreature)
	if pCreature ~= nil then
		CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:use_terminal")
	end
end

function DeathWatchBunkerScreenPlay:swapValveState(pCreature, valveNumber, notifyPlayer)
	local curState = readData("dwb:valve" .. valveNumber)
	local newState

	if (curState == 1) then
		if (notifyPlayer) then
			CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:valve_off")
		end
		curState = 0
	else
		if (notifyPlayer) then
			CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:valve_on")
		end
		curState = 1
	end
	writeData("dwb:valve" .. valveNumber, curState)

	self:spawnValveEffect(valveNumber, curState)
end

function DeathWatchBunkerScreenPlay:spawnValveEffect(valveNumber, valveState)
	local effectID = readData("dwb:valve_effect" .. valveNumber)
	local pEffect = getSceneObject(effectID)

	if (pEffect ~= nil) then
		SceneObject(pEffect):destroyObjectFromWorld()
	end

	local pValveEffect
	local valveData = self.deathWatchValveEffects[valveNumber]
	if (valveState == 1) then
		pValveEffect = spawnSceneObject("endor","object/static/particle/pt_light_streetlamp_green.iff",valveData[1],valveData[2],valveData[3],5996340,0,0,0,0)
	else
		pValveEffect = spawnSceneObject("endor","object/static/particle/pt_light_streetlamp_red.iff",valveData[1],valveData[2],valveData[3],5996340,0,0,0,0)
	end

	if (pValveEffect ~= nil) then
		writeData("dwb:valve_effect" .. valveNumber, SceneObject(pValveEffect):getObjectID())
	end
end

function DeathWatchBunkerScreenPlay:doValveSwitch(pCreature, valveNumber)
	if valveNumber == 1 then
		self:swapValveState(pCreature, 1, true)
		self:swapValveState(pCreature, 4, false)
	elseif valveNumber == 2 then
		self:swapValveState(pCreature, 2, true)
		self:swapValveState(pCreature, 3, false)
	elseif valveNumber == 3 then
		self:swapValveState(pCreature, 2, false)
		self:swapValveState(pCreature, 3, true)
		self:swapValveState(pCreature, 4, false)
	elseif valveNumber == 4 then
		self:swapValveState(pCreature, 1, false)
		self:swapValveState(pCreature, 3, false)
		self:swapValveState(pCreature, 4, true)
	end

	local state1 = readData("dwb:valve1")
	local state2 = readData("dwb:valve2")
	local state3 = readData("dwb:valve3")
	local state4 = readData("dwb:valve4")

	if (state1 == 1 and state2 == 1 and state3 == 1 and state4 == 1) then
		CreatureObject(pCreature):setScreenPlayState(64, "death_watch_foreman_stage")
		CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:restored_pressure")
		-- Reset valves to starting state with A, B and D active
		self:swapValveState(pCreature, 3, false)
	end
end

function DeathWatchBunkerScreenPlay:startCraftingProcess(pCreature, pTerminal)
	if pCreature == nil or pTerminal == nil then
		return
	end

	createEvent(1000 * 30, "DeathWatchBunkerScreenPlay", "cancelCrafting", pTerminal)
	createEvent(1000, "DeathWatchBunkerScreenPlay", "sendUseTerminalMessage", pCreature)
	writeData(CreatureObject(pCreature):getObjectID() .. ":dwb:currentlycrafting", 1)
	createObserver(OBJECTDESTRUCTION, "DeathWatchBunkerScreenPlay", "diedWhileCrafting", pCreature)
end

function DeathWatchBunkerScreenPlay:nextCraftingStep(pTerm)
	if pTerm == nil then
		return
	end

	writeData(SceneObject(pTerm):getObjectID() .. ":dwb:currentlycrafting", 3)
	local creoId = readData(SceneObject(pTerm):getObjectID() .. ":dwb:user")
	if creoId ~= 0 then
		local pCreature = getSceneObject(creoId)
		if pCreature ~= nil then
			CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:use_terminal")
		end
	end
end

function DeathWatchBunkerScreenPlay:finishCraftingStep(pTerm)
	if pTerm == nil then
		return
	end

	local creoId = readData(SceneObject(pTerm):getObjectID() .. ":dwb:user")
	if creoId ~= 0 then
		local pCreature = getSceneObject(creoId)
		if pCreature ~= nil then
			self:stopCraftingProcess(pCreature, pTerm, true, true)
		end
	end
end

function DeathWatchBunkerScreenPlay:getObjOwner(pObj)
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

function DeathWatchBunkerScreenPlay:craftingConfirmCallback(pCreature, pSui, cancelPressed)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()

	if (pUsingObject == nil) then
		return 0
	end

	local step = readData(SceneObject(pUsingObject):getObjectID() .. ":dwb:currentlycrafting")

	if step == 1 then
		writeData(SceneObject(pUsingObject):getObjectID() .. ":dwb:currentlycrafting", 2)
		CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:alum_process_begun")
		createEvent(30 * 1000, "DeathWatchBunkerScreenPlay", "nextCraftingStep", pUsingObject)
	elseif step == 3 then
		writeData(SceneObject(pUsingObject):getObjectID() .. ":dwb:currentlycrafting", 4)
		CreatureObject(pCreature):sendSystemMessage("@dungeon/death_watch:aeration_process_begun")
		createEvent(30 * 1000, "DeathWatchBunkerScreenPlay", "finishCraftingStep", pUsingObject)
	end

	return 0
end

function DeathWatchBunkerScreenPlay:doVentDroidStep(pDroid)
	local curStep = readData("dwb:ventDroidStep")

	local pCell = getSceneObject(5996379)

	if (pCell == nil) then
		return
	end

	if (curStep == -1) then
		return
	end

	if (curStep == 0) then -- Initial spawn at toolbox, wait 30 seconds
		local spawn = deathWatchSpecialSpawns["ventdroid"]
		pDroid = spawnMobile("endor", spawn[1], spawn[2], spawn[3], spawn[4], spawn[5], spawn[6], spawn[7])
		SceneObject(pDroid):setCustomObjectName("Ventilation Repair Droid")
		CreatureObject(pDroid):setPvpStatusBitmask(0)
		createObserver(DESTINATIONREACHED, "DeathWatchBunkerScreenPlay", "ventDroidDestinationReached", pDroid)
		AiAgent(pDroid):setAiTemplate("manualescortwalk") -- Don't move unless patrol point is added to list, walking speed
		AiAgent(pDroid):setFollowState(4) -- Patrolling
		createEvent(30 * 1000, "DeathWatchBunkerScreenPlay", "doVentDroidStep", pDroid)
		writeData("dwb:ventDroidStep", curStep + 1)
	elseif (curStep == 1) then -- Move to toolbox
		self:sendMessageToCell(5996345, "@dungeon/death_watch:protect_tools")
		self:sendMessageToCell(5996378, "@dungeon/death_watch:protect_tools")
		self:sendMessageToCell(5996379, "@dungeon/death_watch:protect_tools")
		self:doVentDroidMove(pDroid)
	elseif (curStep == 2) then -- Wait 120 seconds
		self:sendMessageToCell(5996379, "@dungeon/death_watch:protect_tools")
		spawnMobile("endor", "death_watch_bloodguard", 0, -7.4, -52, -119.1, 120, 5996379)
		spawnMobile("endor", "death_watch_bloodguard", 0, -4.6, -52, -117.2, 172, 5996379)
		spawnMobile("endor", "death_watch_bloodguard", 0, -3.1, -52, -120.7, -113, 5996379)
		createEvent(120 * 1000, "DeathWatchBunkerScreenPlay", "doVentDroidStep", pDroid)
		writeData("dwb:ventDroidStep", curStep + 1)
	elseif (curStep == 3) then -- move to first center boxed area
		self:sendMessageToCell(5996379, "@dungeon/death_watch:protect_fix")
		self:doVentDroidMove(pDroid)
	elseif (curStep == 4) then -- Start repair effect, wait 120 seconds
		spawnMobile("endor", "death_watch_bloodguard", 0, -1.9, -54.1, -112.9, -66, 5996379)
		spawnMobile("endor", "death_watch_bloodguard", 0, -1.7, -54.1, -110.0, -137, 5996379)
		spawnMobile("endor", "death_watch_bloodguard", 0, -8.3, -54.1, -113.9, 83, 5996379)
		SceneObject(pDroid):updateDirection(0)
		local pValveEffect = spawnSceneObject("endor","object/static/particle/pt_poi_droid_weld_sparks.iff",-6.0, -53.2, -112,5996379,0.707,0.707,0,0)
		if (pValveEffect ~= nil) then
			writeData("dwb:ventDroidEffectID", SceneObject(pValveEffect):getObjectID())
		end
		createEvent(120 * 1000, "DeathWatchBunkerScreenPlay", "doVentDroidStep", pDroid)
		writeData("dwb:ventDroidStep", curStep + 1)
	elseif (curStep == 5) then -- End effect, Despawn droid, complete quest
		local effectID = readData("dwb:ventDroidEffectID")
		local pEffect = getSceneObject(effectID)
		if (pEffect ~= nil) then
			SceneObject(pEffect):destroyObjectFromWorld()
		end

		local starterID = readData("dwb:droidEscortStarter")

		local pStarter = getSceneObject(starterID)

		SceneObject(pDroid):destroyObjectFromWorld()
		writeData("dwb:ventDroidEffectID", 0)
		writeData("dwb:ventDroidStep", 0)
		self:sendMessageToCell(5996378, "@dungeon/death_watch:ventilation_repair")
		self:sendMessageToCell(5996379, "@dungeon/death_watch:ventilation_repair")
		writeData("dwb:droidEscortStatus", 0)
		writeData("dwb:droidEscortStarter", 0)
		writeData("dwb:ventsEnabled", 1)


		if (pStarter == nil) then
			return
		end

		CreatureObject(pStarter):setScreenPlayState(2, "death_watch_bunker_technician_sidequest")

		createEvent(60 * 60 * 1000, "DeathWatchBunkerScreenPlay", "disableVents", pStarter) -- Disable vents after an hour
	end
end

function DeathWatchBunkerScreenPlay:ventDroidDestinationReached(pDroid)
	createEvent(2000, "DeathWatchBunkerScreenPlay", "doVentDroidMove", pDroid)
	return 1
end

function DeathWatchBunkerScreenPlay:doVentDroidMove(pDroid)
	local curStep = readData("dwb:ventDroidStep")
	local patrolPoints
	if (curStep == 1) then
		patrolPoints = self.ventDroidPatrolPoints[1]
	elseif (curStep == 3) then
		patrolPoints = self.ventDroidPatrolPoints[2]
	else
		printf("ERROR: DeathWatchBunkerScreenPlay:doVentDroidMove called on wrong step.\n")
		return
	end

	local patrolPointCount = table.getn(patrolPoints)
	local onCurrentPoint = readData("dwb:ventDroidCurrentPoint")

	if (onCurrentPoint == patrolPointCount) then
		writeData("dwb:ventDroidCurrentPoint", 0)
		writeData("dwb:ventDroidStep", curStep + 1)
		self:doVentDroidStep(pDroid)
		return
	end

	local nextPoint = patrolPoints[onCurrentPoint + 1]
	local pCell = getSceneObject(nextPoint[4])

	if (pCell == nil) then
		return 0
	end

	AiAgent(pDroid):stopWaiting()
	AiAgent(pDroid):setWait(0)
	AiAgent(pDroid):setNextPosition(nextPoint[1], nextPoint[2], nextPoint[3], pCell)
	AiAgent(pDroid):executeBehavior()

	writeData("dwb:ventDroidCurrentPoint", onCurrentPoint + 1)
end

function DeathWatchBunkerScreenPlay:disableVents()
	writeData("dwb:ventsEnabled", 0)
end

-- Not used until droid is made attackable by spawns
function DeathWatchBunkerScreenPlay:failVentEscort(pDroid)
	writeData("dwb:droidEscortStatus", 0)
	writeData("dwb:droidEscortStarter", 0)
	writeData("dwb:ventDroidAvailable", 0)
	writeData("dwb:ventDroidStep", -1)
	self:sendMessageToCell(5996379, "@dungeon/death_watch:repair_failed")
	self:sendMessageToCell(5996378, "@dungeon/death_watch:repair_failed")
	createEvent(5 * 60 * 1000, "DeathWatchBunkerScreenPlay", "createNewVentDroid", pDroid) -- New vent droid available 5 mins after failing
end

function DeathWatchBunkerScreenPlay:createNewVentDroid()
	writeData("dwb:ventDroidAvailable", 1)
	writeData("dwb:ventDroidStep", 0)
end

function DeathWatchBunkerScreenPlay:sendMessageToCell(cellID, string)
	local pCell = getSceneObject(cellID)

	if pCell == nil then
		return
	end

	local cellSize = SceneObject(pCell):getContainerObjectsSize()
	for i = 0, cellSize - 1, 1 do
		local pObject = SceneObject(pCell):getContainerObject(i)
		if pObject ~= nil then
			if SceneObject(pObject):isPlayerCreature() then
				CreatureObject(pObject):sendSystemMessage(string)
			end
		end
	end
end
