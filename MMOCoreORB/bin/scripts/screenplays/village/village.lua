-- Additional Includes.
includeFile("village/fs_experience_converter_conv_handler.lua")

local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")
local VillageJediManager = require("managers.jedi.village.village_jedi_manager_common")

VILLAGE_PHASE_ONE = 1
VILLAGE_PHASE_TWO = 2
VILLAGE_PHASE_THREE = 3
VILLAGE_PHASE_FOUR = 4

VillagerMobilesPhaseOne = {
	{"quharek", 60, 5373, 78,-4181, 0, 0},
	{"whip", 60, 5283, 78, -4226, 0, 0},
	{"captain_sarguillo", 60, 5313, 78, -4161, 0, 0},
	{"sivarra_mechaux", 60, 5391, 78, -4075, 0, 0}
}

VillagerMobiles = {
	{"paemos", 60, 5173, 78,-4081, 0, 0}
}

Village = ScreenPlay:new {
	screenplayName = "Village",
}

registerScreenPlay("Village", true)

function Village:start()
	if (isZoneEnabled("dathomir")) then
		VillageJediManager.setCurrentPhaseInit()
		self:spawnMobiles(VillageJediManager.getCurrentPhase())
	end
end

function Village:switchToNextPhase()
		local currentPhase = VillageJediManager.getCurrentPhase()
		local nextPhase = nil
		
		if (currentPhase == VILLAGE_PHASE_ONE) then
			nextPhase = VILLAGE_PHASE_TWO
		elseif (currentPhase == VILLAGE_PHASE_TWO) then
			nextPhase = VILLAGE_PHASE_THREE
		elseif (currentPhase == VILLAGE_PHASE_THREE) then
			nextPhase = VILLAGE_PHASE_FOUR
		elseif (currentPhase == VILLAGE_PHASE_FOUR) then
			nextPhase = VILLAGE_PHASE_ONE
		end

		if (nextPhase ~= nil) then
			VillageJediManager.setCurrentPhase(nextPhase)
			self:despawnMobiles(currentPhase)
			self:spawnMobiles(nextPhase)
		end
end

-- Spawning functions.

function Village:spawnMobiles(pCurrentPhase)

	local spawnedSceneObject = LuaSceneObject(nil)

	for i,v in ipairs(VillagerMobiles) do
		spawnedPointer = spawnMobile("dathomir", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
		spawnedSceneObject:_setObject(spawnedPointer)
		writeData("village:npc:oid", spawnedSceneObject:getObjectID())
	end

	if (pCurrentPhase == VILLAGE_PHASE_ONE) then
		for i,v in ipairs(VillagerMobilesPhaseOne) do
			spawnedPointer = spawnMobile("dathomir", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
			spawnedSceneObject:_setObject(spawnedPointer)
			writeData("village:npc:oid" .. pCurrentPhase, spawnedSceneObject:getObjectID())
		end
	end
end

function Village:despawnMobiles(pCurrentPhase)
	local spawnedSceneObject = LuaSceneObject(nil)

	for i,v in ipairs(VillagerMobiles) do
		local objID = readData("village:npc:oid")

		if (objID ~= nil) then
			spawnedPointer = getSceneObject(objID)
			spawnedSceneObject:_setObject(spawnedPointer)
			spawnedSceneObject:destroyObjectFromWorld()
			spawnedSceneObject:destroyObjectFromDatabase()
		end
	end

	if (pCurrentPhase == VILLAGE_PHASE_ONE) then
		for i,v in ipairs(VillagerMobiles) do
			local objID = readData("village:npc:oid" .. pCurrentPhase)
			if (objID ~= nil) then
				spawnedPointer = getSceneObject(objID)
				spawnedSceneObject:_setObject(spawnedPointer)
				spawnedSceneObject:destroyObjectFromWorld()
				spawnedSceneObject:destroyObjectFromDatabase()
			end
		end
	end
	
end
