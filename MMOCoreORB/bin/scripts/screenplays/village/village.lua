-- Additional Includes.
-- N/A

local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

local VILLAGE_PHASE_CHANGE_TIME = 120 * 1000 -- Three Weeks.
--local VILLAGE_PHASE_CHANGE_TIME = 3 * 7 * 24 * 60 * 60 * 1000 -- Three Weeks.

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

	local phase1 = getServerEvent("VillagePhase1")
	local phase2 = getServerEvent("VillagePhase2")
	local phase3 = getServerEvent("VillagePhase3")
	local phase4 = getServerEvent("VillagePhase4")

	if (phase1 == true) then
		self:spawnMobilesPhaseOne()
		--self:spawnMobilesPhaseAll()
	elseif (phase2 == true) then
		--self:spawnMobilesPhaseOne()
		--self:spawnMobilesPhaseAll()
	elseif (phase3 == true) then
		--self:spawnMobilesPhaseOne()
		--self:spawnMobilesPhaseAll()
	elseif (phase4 == true) then
		--self:spawnMobilesPhaseOne()
		--self:spawnMobilesPhaseAll()
	else
		self:initializePhase()
	end
end

function Village:initializePhase()

	Logger:log("Initializing Village phases at Phase One, please wait...", LT_INFO)

	-- Create persistent event to change the phase.
	createServerEvent(VILLAGE_PHASE_CHANGE_TIME, "Village", "switchToNextPhase", "VillagePhase1")
	
	-- Spawn Phase One.
	self:spawnMobilesPhaseOne()
	--self:spawnMobilesPhaseAll()
end

function Village:switchToNextPhase()
	
	local phase1 = getServerEvent("VillagePhase1")
	local phase2 = getServerEvent("VillagePhase2")
	local phase3 = getServerEvent("VillagePhase3")
	local phase4 = getServerEvent("VillagePhase4")
	
	if ((phase1 == true and phase2 == false) or (phase2 == true and phase3 == false) or (phase3 == true and phase4 == false) or (phase4 == true and phase1 == false)) then
		local nextPhase = nil

		if (phase1 == true) then
			nextPhase = "2"
		elseif (phase2 == true) then
			nextPhase = "3"
		elseif (phase3 == true) then
			nextPhase = "4"
		elseif (phase4 == true) then
			nextPhase = "1"
		end

		if (nextPhase ~= nil) then
			Logger:log("Switching to Phase " .. nextPhase .. ".", LT_INFO)

			-- Create another persistent event to keep the cycles going...
			createServerEvent(VILLAGE_PHASE_CHANGE_TIME, "Village", "switchToNextPhase", "VillagePhase" .. nextPhase)

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
