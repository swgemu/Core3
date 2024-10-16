--Copyright (C) 2007 <SWGEmu>

--This File is part of Core3.

--This program is free software; you can redistribute
--it and/or modify it under the terms of the GNU Lesser
--General Public License as published by the Free Software
--Foundation; either version 2 of the License,
--or (at your option) any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--See the GNU Lesser General Public License for
--more details.

--You should have received a copy of the GNU Lesser General
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

--Linking Engine3 statically or dynamically with other modules
--is making a combined work based on Engine3.
--Thus, the terms and conditions of the GNU Lesser General Public License
--cover the whole combination.

--In addition, as a special exception, the copyright holders of Engine3
--give you permission to combine Engine3 program with free software
--programs or libraries that are released under the GNU LGPL and with
--code included in the standard release of Core3 under the GNU LGPL
--license (or modified versions of such code, with unchanged license).
--You may copy and distribute such a system following the terms of the
--GNU LGPL for Engine3 and the licenses of the other code concerned,
--provided that you include the source code of that other code when
--and as the GNU LGPL requires distribution of source code.

--Note that people who make modified versions of Engine3 are not obligated
--to grant this special exception for their modified versions;
--it is their choice whether to do so. The GNU Lesser General Public License
--gives permission to release a modified version without this exception;
--this exception also makes it possible to release a modified version
--which carries forward this exception.

local ObjectManager = require("managers.object.object_manager")
local Logger = require("utils.logger")

SpaceHelpers = {
	pilotSkills = {
		neutralPilot = {
			"pilot_neutral_master", "pilot_neutral_droid_04", "pilot_neutral_procedures_04", "pilot_neutral_starships_04",
			"pilot_neutral_weapons_04", "pilot_neutral_droid_03", "pilot_neutral_procedures_03", "pilot_neutral_starships_03", "pilot_neutral_weapons_03",
			"pilot_neutral_droid_02", "pilot_neutral_procedures_02", "pilot_neutral_starships_02", "pilot_neutral_weapons_02",
			"pilot_neutral_droid_01", "pilot_neutral_procedures_01", "pilot_neutral_starships_01", "pilot_neutral_weapons_01",
			"pilot_neutral_novice"
		},
		rebelPilot = {
			"pilot_rebel_navy_master", "pilot_rebel_navy_droid_04", "pilot_rebel_navy_procedures_04", "pilot_rebel_navy_starships_04",
			"pilot_rebel_navy_weapons_04", "pilot_rebel_navy_droid_03", "pilot_rebel_navy_procedures_03", "pilot_rebel_navy_starships_03", "pilot_rebel_navy_weapons_03",
			"pilot_rebel_navy_droid_02", "pilot_rebel_navy_procedures_02", "pilot_rebel_navy_starships_02", "pilot_rebel_navy_weapons_02",
			"pilot_rebel_navy_droid_01", "pilot_rebel_navy_procedures_01", "pilot_rebel_navy_starships_01", "pilot_rebel_navy_weapons_01",
			"pilot_rebel_navy_novice"
		},
		imperialPilot = {
			"pilot_imperial_navy_master", "pilot_imperial_navy_droid_04", "pilot_imperial_navy_procedures_04", "pilot_imperial_navy_starships_04",
			"pilot_imperial_navy_weapons_04", "pilot_imperial_navy_droid_03", "pilot_imperial_navy_procedures_03", "pilot_imperial_navy_starships_03", "pilot_imperial_navy_weapons_03",
			"pilot_imperial_navy_droid_02", "pilot_imperial_navy_procedures_02", "pilot_imperial_navy_starships_02", "pilot_imperial_navy_weapons_02",
			"pilot_imperial_navy_droid_01", "pilot_imperial_navy_procedures_01", "pilot_imperial_navy_starships_01", "pilot_imperial_navy_weapons_01",
			"pilot_imperial_navy_novice"
		}
	}
}

-- @param pPlayer pointer checked if neutral pilot
function SpaceHelpers:isNeutralPilot(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):isNeutralPilot()
end

-- @param pPlayer pointer to check if rebel pilot
function SpaceHelpers:isRebelPilot(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):isRebelPilot()
end

-- @param pPlayer pointer to check if imperial pilot
function SpaceHelpers:isImperialPilot(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):isImperialPilot()
end

-- @param pPlayer pointer checks if the player has any type of pilot skills
function SpaceHelpers:isPilot(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return (CreatureObject(pPlayer):isNeutralPilot() or CreatureObject(pPlayer):isRebelPilot() or CreatureObject(pPlayer):isImperialPilot())
end

-- @param pPlayer pointer checks if the player has space experience
function SpaceHelpers:hasEarnedSpaceXP(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local spaceXP = PlayerObject(pGhost):getExperience("space_combat_general")

	return (spaceXP > 0)
end

-- @param pPlayer pointer checks if the player has space experience
-- @param ignoreYacht bool value passed to ignore the Sorosuub Yacht when checking for ships in players datapad
function SpaceHelpers:hasShips(pPlayer, ignoreYacht)
	if (pPlayer == nil) then
		return true
	end

	return CreatureObject(pPlayer):hasShips()
end

-- @param pPlayer pointer surrenders the entire pilot profession
-- @param pilotProfession string to match table above with list of skill boxes in selected pilot profession: neutralPilot, rebelPilot, imperialPilot
function SpaceHelpers:surrenderPilot(pPlayer, pilotProfession)
	if (pPlayer == nil) then
		return
	end

	local pilotSkills = self.pilotSkills[pilotProfession]

	for i = 1, #pilotSkills, 1 do
		local skillName = pilotSkills[i]

		if (CreatureObject(pPlayer):hasSkill(skillName)) then
			CreatureObject(pPlayer):surrenderSkill(skillName)
		end
	end
end

-- @param pPlayer pointer adds waypoint to the starting neutral pilot trainer
function SpaceHelpers:addCorsecPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("corellia", "@npc_spawner_n:rhea", "@npc_spawner_n:rhea", -274, -4730, WAYPOINTBLUE, true, true, 0)
end


-- @param pPlayer pointer adds waypoint to the starting neutral pilot trainer
function SpaceHelpers:addRSFPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("naboo", "@npc_spawner_n:dinge", "@npc_spawner_n:dinge", -5496, 4579, WAYPOINTBLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the starting rebel pilot trainer
function SpaceHelpers:addTatooinePilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("tatooine", "@npc_spawner_n:dravis", "@npc_spawner_n:dravis", 3429, -4788, WAYPOINTBLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the starting rebel pilot coordinator
function SpaceHelpers:addRebelPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("corellia", "@npc_spawner_n:j_pai_brek", "@npc_spawner_n:j_pai_brek", -5072, -2343, WAYPOINTBLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Rebel Vortex Squad Tier1 Trainer
function SpaceHelpers:addVortexSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("naboo", "@npc_spawner_n:v3_fx", "@npc_spawner_n:v3_fx", 4764, -4795, WAYPOINTBLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Rebel Akron's Havok Squad Tier1 Trainer
function SpaceHelpers:addAkronSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("corellia", "@npc_spawner_n:kreezo", "@npc_spawner_n:kreezo", -5176, -2281, WAYPOINTBLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Rebel Crimson Phoenix Squadron Tier1 Trainer
function SpaceHelpers:addCrimsonSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("tatooine", "@npc_spawner_n:da_la_socuna", "@npc_spawner_n:da_la_socuna", -3002, 2202, WAYPOINTBLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the starting imperial pilot coordinator
function SpaceHelpers:addImperialPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("naboo", "@npc_spawner_n:landau", "@npc_spawner_n:landau", -5516, 4403, WAYPOINTBLUE, true, true, 0)
end

return SpaceHelpers