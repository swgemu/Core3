-- Additional Includes.
-- includeFile("village/fs_experience_converter_conv_handler.lua")

local ObjectManager = require("managers.object.object_manager")
local ScreenPlay = require("screenplays.screenplay")

-- Utils.
local Logger = require("utils.logger")
require("utils.helpers")

VillageJediManagerTownship = ScreenPlay:new {
	screenplayName = "VillageJediManagerTownship"
}

local currentPhase = Object:new {phase = nil}

VILLAGE_CONFIGURATION_FILE_STRING = "./conf/villagephase.txt"


VILLAGE_PHASE_ONE = 1
VILLAGE_PHASE_TWO = 2
VILLAGE_PHASE_THREE = 3
VILLAGE_PHASE_FOUR = 4
VILLAGE_TOTAL_NUMBER_OF_PHASES = 4

local VILLAGE_PHASE_CHANGE_TIME = 120 * 1000 -- Testing value.
--local VILLAGE_PHASE_CHANGE_TIME = 3 * 7 * 24 * 60 * 60 * 1000 -- Three Weeks.

-- Key is the mobile name, value is the spawn parameters.
VillagerMobilesPhaseOne = {
	quharek = {name="quharek",respawn=60, x=5373, z=78, y=-4181, header=0, cellid=0},
	whip = {name="whip",respawn=60, x=5283, z=78, y=-4226, header=0, cellid=0},
	captain_sarguillo = {name="captain_sarguillo",respawn=60, x=5313, z=78,y= -4161, header=0, cellid=0},
	sivarra_mechaux = {name="sivarra_mechaux",respawn=60, x=5391, z=78, y=-4075, header=0, cellid=0}
}

VillagerMobiles = {
	paemos = {name="paemos",respawn=60, x=5173, z=78, y=-4081, header=0, cellid=0}
}

-- Set the current Village Phase for the first time.
function VillageJediManagerTownship.setCurrentPhaseInit()
	local phaseChange = hasServerEvent("VillagePhaseChange")
	if (phaseChange == false) then
		VillageJediManagerTownship.setCurrentPhase(VILLAGE_PHASE_ONE)
		createServerEvent(VILLAGE_PHASE_CHANGE_TIME, "VillageJediManagerTownship", "switchToNextPhase", "VillagePhaseChange")
	end
end

-- Set the current Village Phase.
function VillageJediManagerTownship.setCurrentPhase(nextPhase)
	currentPhase.phase = nextPhase

	local file = io.open(VILLAGE_CONFIGURATION_FILE_STRING, "w+")
	file:write(nextPhase)
	file:flush()
	file:close()
end

function VillageJediManagerTownship.getCurrentPhase()
	if (currentPhase.phase == nil) then
		local file = io.open(VILLAGE_CONFIGURATION_FILE_STRING)
		local thePhase = file:read()
		VillageJediManagerTownship.setCurrentPhase(thePhase)
		file:close()
	end
	return currentPhase.phase
end

function VillageJediManagerTownship:switchToNextPhase()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	VillageJediManagerTownship:despawnMobiles(currentPhase)

	currentPhase = currentPhase + 1 % VILLAGE_TOTAL_NUMBER_OF_PHASES
	VillageJediManagerTownship.setCurrentPhase(currentPhase)
	VillageJediManagerTownship:spawnMobiles(currentPhase)
end

function VillageJediManagerTownship:start()
	if (isZoneEnabled("dathomir")) then
		Logger:log("Starting the Village Township Screenplay.", LT_INFO)
		VillageJediManagerTownship.setCurrentPhaseInit()
		VillageJediManagerTownship:spawnMobiles(VillageJediManagerTownship.getCurrentPhase())
	end
end

-- Spawning functions.

function VillageJediManagerTownship:spawnMobiles(pCurrentPhase)
	foreach(VillagerMobiles, function(mobile)
			local theSpawnedMobile = spawnMobile("dathomir", mobile.name, mobile.respawn, mobile.x, mobile.z, mobile.y, mobile.header, mobile.cellid)
			Logger:log("Spawning a Village NPC at " .. mobile.x .. " - " .. mobile.y, LT_INFO)
			ObjectManager.withSceneObject(theSpawnedMobile, function(villageMobile)
				writeData("village:npc:oid:" .. mobile.name, villageMobile:getObjectID())
				Logger:log("Saving a Village NPC with a objectID of " .. villageMobile:getObjectID(), LT_INFO)
			end)
	end)
	if (pCurrentPhase == VILLAGE_PHASE_ONE) then
		foreach(VillagerMobilesPhaseOne, function(mobile)
			local theSpawnedMobile = spawnMobile("dathomir", mobile.name, mobile.respawn, mobile.x, mobile.z, mobile.y, mobile.header, mobile.cellid)
			Logger:log("Spawning a Village NPC at " .. mobile.x .. " - " .. mobile.y, LT_INFO)
			ObjectManager.withSceneObject(theSpawnedMobile, function(villageMobile)
				writeData("village:npc:oid:" .. mobile.name, villageMobile:getObjectID())
				Logger:log("Saving a Village NPC with a objectID of " .. villageMobile:getObjectID(), LT_INFO)
			end)
		end)
	end
end

-- Despawn and cleanup all possible mobiles.
function VillageJediManagerTownship:despawnMobiles(pCurrentPhase)
	foreach(VillagerMobiles, function(mobile)
		local objectID = readData("village:npc:oid:".. mobile.name)
		local spawnedLookup = getSceneObject(objectID)
		ObjectManager.withSceneObject(spawnedLookup, function(villageMobile)
			villageMobile:destroyObjectFromWorld()
			villageMobile:destroyObjectFromDatabase()
			deleteData("village:npc:oid:".. mobile.name)
			Logger:log("Despawning " .. mobile.name, LT_INFO)
		end)
	end)
	foreach(VillagerMobilesPhaseOne, function(mobile)
		local objectID = readData("village:npc:oid:".. mobile.name)
		local spawnedLookup = getSceneObject(objectID)
		ObjectManager.withSceneObject(spawnedLookup, function(villageMobile)
			villageMobile:destroyObjectFromWorld()
			villageMobile:destroyObjectFromDatabase()
			deleteData("village:npc:oid:".. mobile.name)
			Logger:log("Despawning " .. mobile.name, LT_INFO)
		end)
	end)
end

registerScreenPlay("VillageJediManagerTownship", true)

return VillageJediManagerTownship
