-- Additional Includes.
-- N/A

local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

local VILLAGE_PHASE_CHANGE_TIME = 1814400 * 1000 -- Three Weeks.

Village = ScreenPlay:new {
	screenplayName = "Village",
}

registerScreenPlay("Village", true)

function Village:start()
	if (isZoneEnabled("dathomir")) then
		self:checkCurrentPhase()
	end
end

function Village:checkCurrentPhase()
	local phase = readStringData("village:phases")

	if (phase == "") then
		Logger:log("Initializing Village phases, please wait...", LT_INFO)
		self:initializePhase()
	elseif (phase == "1") then
		self:spawnMobilesPhaseOne()
		--self:spawnSceneObjectsPhaseOne()
	elseif (phase == "2") then
		--self:spawnMobilesPhaseTwo()
		--self:spawnSceneObjectsPhaseTwo()
	elseif (phase == "3") then
		--self:spawnMobilesPhaseOne()
		--self:spawnSceneObjectsPhaseThree()
	elseif (phase == "4") then
		--self:spawnMobilesPhaseOne()
		--self:spawnSceneObjectsPhaseFour()
	end

	if (phase ~= "") then
		--self:spawnMobilesAllPhase()
		--self:spawnSceneObjectsAllPhase()
		Logger:log("Village Phase " .. phase .. " loaded.", LT_INFO)
	end
end

function Village:initializePhase()
	local firstPhase = "1"
	writeStringData("village:phases", firstPhase)

	-- Create persistent event to change the phase.
	createEvent(true, VILLAGE_PHASE_CHANGE_TIME, "Village", "switchToNextPhase", firstPhase)
	
	-- Restart the screenplay since we are now on Phase 1.
	self:checkCurrentPhase()
end

function Village:switchToNextPhase(pFirstPhase)
	local phase = readStringData("village:phases")
	
	if (phase ~= nil and phase ~= "") then
		local nextPhase = nil

		if (phase == 4) then
			nextPhase = "1"
		else 
			nextPhase = phase + 1
		end

		if (nextPhase ~= nil) then
			Logger:log("Switching to Phase " .. nextPhase .. "./n", LT_INFO)
			writeStringData("village:phases", nextPhase)

			-- Don't restart the screenplay yet, changes will take effect on server restart.
		end

	end
	
end

-- Spawning functions.

function Village:spawnMobilesPhaseOne()
	
	-- Primary Villagers.
	spawnMobile("dathomir", "quharek", 60, 5373, 78,-4181, 0, 0)
	spawnMobile("dathomir", "whip", 60, 5283, 78, -4226, 0, 0)
	spawnMobile("dathomir", "captain_sarguillo", 60, 5313, 78, -4161, 0, 0)
	spawnMobile("dathomir", "sivarra_mechaux", 60, 5391, 78, -4075, 0, 0)

	-- Filler Villagers.
end
