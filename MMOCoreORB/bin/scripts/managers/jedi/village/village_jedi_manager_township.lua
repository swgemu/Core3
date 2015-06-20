local ObjectManager = require("managers.object.object_manager")
local ScreenPlay = require("screenplays.screenplay")

require("screenplays.village.village_spawn_table")

-- Utils.
local Logger = require("utils.logger")
require("utils.helpers")

VillageJediManagerTownship = ScreenPlay:new {
	screenplayName = "VillageJediManagerTownship"
}

VILLAGE_PHASE_ONE = 1
VILLAGE_PHASE_TWO = 2
VILLAGE_PHASE_THREE = 3
VILLAGE_PHASE_FOUR = 4
VILLAGE_TOTAL_NUMBER_OF_PHASES = 1 -- Temporarily set to 1 for testing until other phases begin development

local VILLAGE_PHASE_CHANGE_TIME = 24 * 60 * 60 * 1000 -- Testing value.
--local VILLAGE_PHASE_CHANGE_TIME = 5 * 60 * 1000
--local VILLAGE_PHASE_CHANGE_TIME = 3 * 7 * 24 * 60 * 60 * 1000 -- Three Weeks.

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
	setQuestStatus("Village:CurrentPhase", nextPhase)
end

function VillageJediManagerTownship.getCurrentPhase()
	local curPhase = tonumber(getQuestStatus("Village:CurrentPhase"))

	if (curPhase == nil) then
		return 1
	end

	return curPhase
end

function VillageJediManagerTownship:switchToNextPhase()
	local currentPhase = VillageJediManagerTownship.getCurrentPhase()
	VillageJediManagerTownship:despawnMobiles(currentPhase)
	VillageJediManagerTownship:despawnSceneObjects(currentPhase)

	currentPhase = currentPhase + 1
	if currentPhase > VILLAGE_TOTAL_NUMBER_OF_PHASES then
		currentPhase = 1
	end

	VillageJediManagerTownship.setCurrentPhase(currentPhase)
	VillageJediManagerTownship:spawnMobiles(currentPhase, false)
	VillageJediManagerTownship:spawnSceneObjects(currentPhase, false)
	Logger:log("Switching village phase to " .. currentPhase, LT_INFO)

	-- Schedule another persistent event.
	if (not hasServerEvent("VillagePhaseChange")) then
		createServerEvent(VILLAGE_PHASE_CHANGE_TIME, "VillageJediManagerTownship", "switchToNextPhase", "VillagePhaseChange")
	end
end

function VillageJediManagerTownship:start()
	if (isZoneEnabled("dathomir")) then
		Logger:log("Starting the Village Township Screenplay.", LT_INFO)
		VillageJediManagerTownship.setCurrentPhaseInit()
		VillageJediManagerTownship:spawnMobiles(VillageJediManagerTownship.getCurrentPhase(), true)
		VillageJediManagerTownship:spawnSceneObjects(VillageJediManagerTownship.getCurrentPhase(), true)
	end
end

-- Spawning functions.

function VillageJediManagerTownship:spawnMobiles(currentPhase, spawnStaticMobs)
	if (spawnStaticMobs == true) then
		local mobileTable = villageMobileSpawns[0]

		for i = 1, table.getn(mobileTable), 1 do
			local mobile = mobileTable[i]
			local pMobile = spawnMobile("dathomir", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], 0)
			if (pMobile ~= nil) then
				CreatureObject(pMobile):setPvpStatusBitmask(0)
				if (mobile[6] ~= "") then
					self[mobile[6]](pMobile)
				end
				if (mobile[7] ~= "") then
					CreatureObject(pMobile):setOptionsBitmask(136)
					AiAgent(pMobile):setConvoTemplate(mobile[7])
				end
			end
		end
	end

	local mobileTable = villageMobileSpawns[currentPhase]

	for i = 1, table.getn(mobileTable), 1 do
		local mobile = mobileTable[i]
		local pMobile = spawnMobile("dathomir", mobile[1], 0, mobile[2], mobile[3], mobile[4], mobile[5], 0)

		if (pMobile ~= nil) then
			CreatureObject(pMobile):setPvpStatusBitmask(0)
			if (mobile[6] ~= "") then
				self[mobile[6]](pMobile)
			end
			if (mobile[7] ~= "") then
				CreatureObject(pMobile):setOptionsBitmask(136)
				AiAgent(pMobile):setConvoTemplate(mobile[7])
			end
			local mobileID = SceneObject(pMobile):getObjectID()
			writeData("village:npc:object:" .. i, mobileID)
		end
	end
end

-- Despawn and cleanup current phase mobiles.
function VillageJediManagerTownship:despawnMobiles(currentPhase)
	local mobileTable = villageMobileSpawns[currentPhase]
	for i = 1, table.getn(mobileTable), 1 do
		local objectID = readData("village:npc:object:" .. i)
		local pMobile = getSceneObject(objectID)

		if (pMobile ~= nil) then
			SceneObject(pMobile):destroyObjectFromWorld()
			deleteData("village:npc:object:" .. i)
		end
	end
end

function VillageJediManagerTownship:spawnSceneObjects(currentPhase, spawnStaticObjects)
	if (spawnStaticObjects == true) then
		local objectTable = villageObjectSpawns[0]
		foreach(objectTable, function(sceneObject)
			spawnSceneObject("dathomir", sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], 0, sceneObject[5])
		end)
	end

	local objectTable = villageObjectSpawns[currentPhase]
	for i = 1, table.getn(objectTable), 1 do
		local sceneObject = objectTable[i]
		local pObject = spawnSceneObject("dathomir", sceneObject[1], sceneObject[2], sceneObject[3], sceneObject[4], 0, sceneObject[5])

		if (pObject ~= nil) then
			local objectID = SceneObject(pObject):getObjectID()
			writeData("village:scene:object:" .. i, objectID)
		end
	end
end

-- Despawn and cleanup current phase scene objects.
function VillageJediManagerTownship:despawnSceneObjects(currentPhase)
	local objectTable = villageObjectSpawns[currentPhase]
	for i = 1, table.getn(objectTable), 1 do
		local objectID = readData("village:scene:object:" .. i)
		local pObject = getSceneObject(objectID)

		if (pObject ~= nil) then
			SceneObject(pObject):destroyObjectFromWorld()
			deleteData("village:npc:object:" .. i)
		end
	end
end

function VillageJediManagerTownship.initPukingVillager(pNpc)
	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPukingVillager", pNpc) -- 2-5 minute initial delay
end

function VillageJediManagerTownship:doPukingVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	CreatureObject(pNpc):doAnimation("heavy_cough_vomit")

	spatialChat(pNpc, "@quest/force_sensitive/fs_sick:fs_response0" .. getRandomNumber(1,7))

	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPukingVillager", pNpc) -- 2-5 minute delay
end

function VillageJediManagerTownship.initPanickedVillager(pNpc)
	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPanickedVillager", pNpc) -- 2-5 minute initial delay
end

function VillageJediManagerTownship:doPanickedVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	local rand = getRandomNumber(1,20)

	CreatureObject(pNpc):doAnimation("weeping")

	if (rand < 10) then
		spatialChat(pNpc, "@quest/force_sensitive/fs_panicked:fs_response0" .. rand)
	else
		spatialChat(pNpc, "@quest/force_sensitive/fs_panicked:fs_response" .. rand)
	end

	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doPanickedVillager", pNpc) -- 2-5 minute delay
end

function VillageJediManagerTownship.initWoundedVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	CreatureObject(pNpc):setPosture(KNOCKEDDOWN)
	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doWoundedVillager", pNpc) -- 2-5 minute initial delay
end

function VillageJediManagerTownship:doWoundedVillager(pNpc)
	if (pNpc == nil) then
		return
	end

	local rand = getRandomNumber(1,10)

	if (rand < 10) then
		spatialChat(pNpc, "@quest/force_sensitive/fs_lamentations:fs_response0" .. rand)
	else
		spatialChat(pNpc, "@quest/force_sensitive/fs_lamentations:fs_response" .. rand)
	end

	createEvent(getRandomNumber(120, 300) * 1000, "VillageJediManagerTownship", "doWoundedVillager", pNpc) -- 2-5 minute delay
end

registerScreenPlay("VillageJediManagerTownship", true)

return VillageJediManagerTownship
