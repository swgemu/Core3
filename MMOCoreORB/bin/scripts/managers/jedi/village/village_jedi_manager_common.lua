local ObjectManager = require("managers.object.object_manager")
local ScreenPlay = require("screenplays.screenplay")

local VillageJediManagerCommon = ScreenPlay:new {}

local CurrentPhase = Object:new {Phase = nil}

VILLAGE_CONFIGURATION_FILE_STRING = "conf/villagephase.txt"

VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING = "VillageJediProgression"
VILLAGE_JEDI_PROGRESSION_GLOWING = 1
VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL = 2
VILLAGE_JEDI_PROGRESSION_HAS_VILLAGE_ACCESS = 4
VILLAGE_JEDI_PROGRESSION_COMPLETED_VILLAGE = 8
VILLAGE_JEDI_PROGRESSION_DEFEATED_MELLIACHAE = 16

VILLAGE_PHASE_ONE = 1
VILLAGE_PHASE_TWO = 2
VILLAGE_PHASE_THREE = 3
VILLAGE_PHASE_FOUR = 4

local VILLAGE_PHASE_CHANGE_TIME = 120 * 1000 -- Testing value.
--local VILLAGE_PHASE_CHANGE_TIME = 3 * 7 * 24 * 60 * 60 * 1000 -- Three Weeks.

-- Set the jedi progression screen play state on the player.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param state the state to set.
function VillageJediManagerCommon.setJediProgressionScreenPlayState(pCreatureObject, state)
	ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		creatureObject:setScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING)
	end)
end

-- Check if the player has the jedi progression screen play state.
-- @param pCreatureObject pointer to the creature object of the player.
-- @param state the state to check if the player has.
-- @return true if the player has the state.
function VillageJediManagerCommon.hasJediProgressionScreenPlayState(pCreatureObject, state)
	return ObjectManager.withCreatureObject(pCreatureObject, function(creatureObject)
		return creatureObject:hasScreenPlayState(state, VILLAGE_JEDI_PROGRESSION_SCREEN_PLAY_STATE_STRING) == 1
	end) == true
end

-- Get the current Village Phase.
-- @return int based on what the phase is.
function VillageJediManagerCommon.setCurrentPhaseInit()
	
	local phaseChange = hasServerEvent("VillagePhaseChange")
	if (phaseChange == false) then
		VillageJediManagerCommon.setCurrentPhase(VILLAGE_PHASE_ONE)
		createServerEvent(VILLAGE_PHASE_CHANGE_TIME, "Village", "switchToNextPhase", "VillagePhaseChange")
	end
end

function VillageJediManagerCommon.setCurrentPhase(pNextPhase)
	CurrentPhase.Phase = pNextPhase

	local file = io.open(VILLAGE_CONFIGURATION_FILE_STRING, "w+")
	file:write(pNextPhase)
	file:flush()
	file:close()
end

function VillageJediManagerCommon.getCurrentPhase()
	
	if (CurrentPhase.Phase == nil) then
		local file = io.open(VILLAGE_CONFIGURATION_FILE_STRING)
		local thePhase = file:read()
		VillageJediManagerCommon.setCurrentPhase(thePhase)
		file:close()
	end
	
	return CurrentPhase.Phase
end

return VillageJediManagerCommon
