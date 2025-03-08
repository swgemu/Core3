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
	DEBUG_SPACE_HELPERS = false,

	pilotSkills = {
		neutralPilot = {
			"pilot_neutral_master",
			"pilot_neutral_droid_04", "pilot_neutral_procedures_04", "pilot_neutral_starships_04", "pilot_neutral_weapons_04",
			"pilot_neutral_droid_03", "pilot_neutral_procedures_03", "pilot_neutral_starships_03", "pilot_neutral_weapons_03",
			"pilot_neutral_droid_02", "pilot_neutral_procedures_02", "pilot_neutral_starships_02", "pilot_neutral_weapons_02",
			"pilot_neutral_droid_01", "pilot_neutral_procedures_01", "pilot_neutral_starships_01", "pilot_neutral_weapons_01",
			"pilot_neutral_novice"
		},
		rebelPilot = {
			"pilot_rebel_navy_master",
			"pilot_rebel_navy_droid_04", "pilot_rebel_navy_procedures_04", "pilot_rebel_navy_starships_04", "pilot_rebel_navy_weapons_04",
			"pilot_rebel_navy_droid_03", "pilot_rebel_navy_procedures_03", "pilot_rebel_navy_starships_03", "pilot_rebel_navy_weapons_03",
			"pilot_rebel_navy_droid_02", "pilot_rebel_navy_procedures_02", "pilot_rebel_navy_starships_02", "pilot_rebel_navy_weapons_02",
			"pilot_rebel_navy_droid_01", "pilot_rebel_navy_procedures_01", "pilot_rebel_navy_starships_01", "pilot_rebel_navy_weapons_01",
			"pilot_rebel_navy_novice"
		},
		imperialPilot = {
			"pilot_imperial_navy_master",
			"pilot_imperial_navy_droid_04", "pilot_imperial_navy_procedures_04", "pilot_imperial_navy_starships_04", "pilot_imperial_navy_weapons_04",
			"pilot_imperial_navy_droid_03", "pilot_imperial_navy_procedures_03", "pilot_imperial_navy_starships_03", "pilot_imperial_navy_weapons_03",
			"pilot_imperial_navy_droid_02", "pilot_imperial_navy_procedures_02", "pilot_imperial_navy_starships_02", "pilot_imperial_navy_weapons_02",
			"pilot_imperial_navy_droid_01", "pilot_imperial_navy_procedures_01", "pilot_imperial_navy_starships_01", "pilot_imperial_navy_weapons_01",
			"pilot_imperial_navy_novice"
		}
	}
}

--[[

	Space Player Management and Checks

]]

-- @param pPlayer pointer grants the novice pilot box
-- @param skillName - pilot skill name to correlate with the pilotSkills table
function SpaceHelpers:grantNovicePilot(pPlayer, skillName)
	if (pPlayer == nil) then
		return
	end

	local pilotSkills = self.pilotSkills[skillName]
	local noviceSkill = pilotSkills[#pilotSkills]

	if (CreatureObject(pPlayer):hasSkill(noviceSkill)) then
		return
	end

	awardSkill(pPlayer, noviceSkill)

	local messageString = LuaStringIdChatParameter("@skill_teacher:" .. "prose_skill_learned")
	messageString:setTO("@skl_n:" .. noviceSkill)

	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())
end

-- @param pPlayer pointer grants the novice pilot box
-- @param skillString - string for skill to grant the player
-- @param deductExperience - boolean to charge experience from the player
function SpaceHelpers:grantSpaceSkill(pPlayer, skillString, deductExperience)
	if (pPlayer == nil) then
		return
	end

	if (CreatureObject(pPlayer):hasSkill(skillString)) then
		return
	end

	if (deductExperience) then
		local skillManager = LuaSkillManager()

		skillManager:awardSkill(pPlayer, skillString)
	else
		awardSkill(pPlayer, skillString)
	end

	local messageString = LuaStringIdChatParameter("@skill_teacher:" .. "prose_skill_learned")
	messageString:setTO("@skl_n:" .. skillString)

	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject())

	CreatureObject(pPlayer):playMusicMessage("sound/music_themequest_acc_general.snd")
end

-- @param pPlayer pointer grants the novice pilot box
function SpaceHelpers:setSquadronType(pPlayer, squadron)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	PlayerObject(pGhost):setSquadronType(squadron)
end

-- @param pPlayer pointer checked if neutral pilot
function SpaceHelpers:isNeutralPilot(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):isNeutralPilot()
end

-- @param pPlayer pointer checked if is in Corsec Squadron
function SpaceHelpers:isCorsecSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(CORSEC_SQUADRON)
end

-- @param pPlayer pointer checked if is in RSF Squadron
function SpaceHelpers:isRSFSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(RSF_SQUADRON)
end

-- @param pPlayer pointer checked if is in Smuggler Alliance Squadron
function SpaceHelpers:isSmugglerSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(SMUGGLER_SQUADRON)
end

-- @param pPlayer pointer to check if rebel pilot
function SpaceHelpers:isRebelPilot(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):isRebelPilot()
end

-- @param pPlayer pointer checked if is in Akron's Havoc Squadron
function SpaceHelpers:isHavocSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(HAVOC_SQUADRON)
end

-- @param pPlayer pointer checked if is in Vortex Squadron
function SpaceHelpers:isVortexSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(VORTEX_SQUADRON)
end

-- @param pPlayer pointer checked if is in Crimson Phoenix Squadron
function SpaceHelpers:isCrimsonPhoenixSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(CRIMSON_PHOENIX_SQUADRON)
end

-- @param pPlayer pointer to check if imperial pilot
function SpaceHelpers:isImperialPilot(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):isImperialPilot()
end

-- @param pPlayer pointer checked if is in Black Epsilon Squadron
function SpaceHelpers:isBlackEpsilonSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(BLACK_EPSILON_SQUADRON)
end

-- @param pPlayer pointer checked if is in Storm Squadron
function SpaceHelpers:isStormSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(STORM_SQUADRON)
end

-- @param pPlayer pointer checked if is in Inquisition Squadron
function SpaceHelpers:isInquisitionSquadron(pPlayer)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	return PlayerObject(pGhost):isSquadronType(INQUISITION_SQUADRON)
end

-- @param pPlayer pointer to return faction string by squadron type
function SpaceHelpers:getPlayerSpaceFactionString(pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local squadronType = PlayerObject(pGhost):getSquadronType()
	local factionString = ""

	if (squadronType == CORSEC_SQUADRON) then
		factionString = "corsec"
	elseif (squadronType == SMUGGLER_SQUADRON) then
		factionString = "smuggler"
	elseif (squadronType == RSF_SQUADRON) then
		factionString = "rsf"
	elseif (squadronType == BLACK_EPSILON_SQUADRON or squadronType == STORM_SQUADRON or squadronType == INQUISITION_SQUADRON) then
		factionString = "imperial"
	elseif (squadronType == HAVOC_SQUADRON or squadronType == VORTEX_SQUADRON or squadronType == CRIMSON_PHOENIX_SQUADRON) then
		factionString = "rebel"
	end

	return factionString
end

-- @param pPlayer pointer to return faction hash by squadron type
function SpaceHelpers:getPlayerSpaceFactionHash(pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	local squadronType = PlayerObject(pGhost):getSquadronType()
	local factionHash = 0

	if (squadronType == CORSEC_SQUADRON) then
		factionHash = getHashCode("corsec")
	elseif (squadronType == SMUGGLER_SQUADRON) then
		factionHash = getHashCode("smuggler")
	elseif (squadronType == RSF_SQUADRON) then
		factionHash = getHashCode("rsf")
	elseif (squadronType == BLACK_EPSILON_SQUADRON or squadronType == STORM_SQUADRON or squadronType == INQUISITION_SQUADRON) then
		factionHash = getHashCode("imperial")
	elseif (squadronType == HAVOC_SQUADRON or squadronType == VORTEX_SQUADRON or squadronType == CRIMSON_PHOENIX_SQUADRON) then
		factionHash = getHashCode("rebel")
	end

	return factionHash
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
		return false
	end

	local spaceXP = PlayerObject(pGhost):getExperience("space_combat_general")

	return (spaceXP > 0)
end

-- @param pPlayer pointer checks if the player has a ship, can exlude Yacht
function SpaceHelpers:hasCertifiedShip(pPlayer, skipYacht)
	if (pPlayer == nil) then
		return false
	end

	return CreatureObject(pPlayer):hasCertifiedShip(skipYacht)
end

-- @param pPlayer pointer surrenders the entire pilot profession and resets all of the quests
function SpaceHelpers:surrenderPilot(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	local pilotSquadron = PlayerObject(pGhost):getSquadronType()
	local pilotProfession = ""

	if (pilotSquadron == CORSEC_SQUADRON or pilotSquadron == SMUGGLER_SQUADRON or pilotSquadron == RSF_SQUADRON) then
		pilotProfession = "neutralPilot"

		-- All the Space Quests need to be reset here
		CorsecSquadronScreenplay:resetRheaQuests(pPlayer)

	elseif (pilotSquadron == BLACK_EPSILON_SQUADRON or pilotSquadron == STORM_SQUADRON or pilotSquadron == INQUISITION_SQUADRON) then
		pilotProfession = "imperialPilot"
	elseif (pilotSquadron == HAVOC_SQUADRON or pilotSquadron == VORTEX_SQUADRON or pilotSquadron == CRIMSON_PHOENIX_SQUADRON) then
		pilotProfession = "rebelPilot"
	end

	local pilotSkills = self.pilotSkills[pilotProfession]

	for i = 1, #pilotSkills, 1 do
		local skillName = pilotSkills[i]

		if (CreatureObject(pPlayer):hasSkill(skillName)) then
			CreatureObject(pPlayer):surrenderSkill(skillName)
		end
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):resetPilotTier()
end

-- @param pPlayer pointer adds waypoint to the starting neutral Corsec Squadron trainer
function SpaceHelpers:addCorsecPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("corellia", "@npc_spawner_n:rhea", "@npc_spawner_n:rhea", -274, 0, -4730, WAYPOINT_BLUE, true, true, 0)
end


-- @param pPlayer pointer adds waypoint to the starting neutral RSF Squadron trainer
function SpaceHelpers:addRSFPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("naboo", "@npc_spawner_n:dinge", "@npc_spawner_n:dinge", -5496, 0, 4579, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the starting neutral Smugglers Alliance Squadron trainer
function SpaceHelpers:addSmugglersPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("tatooine", "@npc_spawner_n:dravis", "@npc_spawner_n:dravis", 3429, 0, -4788, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the starting rebel pilot coordinator
function SpaceHelpers:addRebelPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("corellia", "@npc_spawner_n:j_pai_brek", "@npc_spawner_n:j_pai_brek", -5072, 0, -2343, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Rebel Vortex Squad Tier1 Trainer
function SpaceHelpers:addVortexSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("naboo", "@npc_spawner_n:v3_fx", "@npc_spawner_n:v3_fx", 4764, 0, -4795, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Rebel Akron's Havok Squad Tier1 Trainer
function SpaceHelpers:addAkronSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("corellia", "@npc_spawner_n:kreezo", "@npc_spawner_n:kreezo", -5176, 0, -2281, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Rebel Crimson Phoenix Squadron Tier1 Trainer
function SpaceHelpers:addCrimsonSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("tatooine", "@npc_spawner_n:da_la_socuna", "@npc_spawner_n:da_la_socuna", -3002, 0, 2202, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the starting imperial pilot coordinator
function SpaceHelpers:addImperialPilotWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("naboo", "@npc_spawner_n:landau", "@npc_spawner_n:landau", -5516, 0, 4403, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Imperial Black Epsilon Squad
function SpaceHelpers:addBlackEpsilonSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("talus", "@npc_spawner_n:hakassha_sireen", "@npc_spawner_n:hakassha_sireen", -2184, 0, 2273, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Imperial Storm Squadron
function SpaceHelpers:addStormSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("tatooine", "@npc_spawner_n:akal_colzet", "@npc_spawner_n:akal_colzet", -1132, 0, -3542, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer adds waypoint to the Imperial Inquisition Squadron
function SpaceHelpers:addImperialInquisitionSquadWaypoint(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):addWaypoint("naboo", "@npc_spawner_n:barn_sinkko", "@npc_spawner_n:barn_sinkko", 5182, 0, 6750, WAYPOINT_BLUE, true, true, 0)
end

-- @param pPlayer pointer to check for skills
-- @param factionString - neutral, rebel_navy, imperial_navy
-- @param tierNumber
function SpaceHelpers:hasPilotTierSkill(pPlayer, factionString, tierNumber)
	if (pPlayer == nil or factionString == "" or tierNumber < 1 or tierNumber > 5) then
		return false
	end

	local skillsTable = {"_droid_0", "_procedures_0", "_starships_0", "_weapons_0"}
	local tierString = tostring(tierNumber)

	for i = 1, 4, 1 do
		if (CreatureObject(pPlayer):hasSkill("pilot_" .. factionString .. skillsTable[i] .. tierString)) then
			return true
		end
	end

	return false
end

-- @param pPlayer pointer to check for skills
-- @param factionString - neutral, rebel_navy, imperial_navy
function SpaceHelpers:hasMasterSkill(pPlayer, factionString)
	if (pPlayer == nil or factionString == "") then
		return false
	end

	return CreatureObject(pPlayer):hasSkill("pilot_" .. factionString .. "_master")
end

-- @param pPlayer - pointer to check for skills
-- @param factionString - neutral, rebel_navy, imperial_navy
-- @param tierNumber
function SpaceHelpers:hasCompletedPilotTier(pPlayer, factionString, tierNumber)
	if (pPlayer == nil or factionString == "" or tierNumber < 1 or tierNumber > 5) then
		return false
	end

	local skillsTable = {"_droid_0", "_procedures_0", "_starships_0", "_weapons_0"}
	local tierString = tostring(tierNumber)

	return CreatureObject(pPlayer):hasSkill("pilot_" .. factionString .. skillsTable[1] .. tierString) and CreatureObject(pPlayer):hasSkill("pilot_" .. factionString .. skillsTable[2] .. tierString) and
			CreatureObject(pPlayer):hasSkill("pilot_" .. factionString .. skillsTable[3] .. tierString) and CreatureObject(pPlayer):hasSkill("pilot_" .. factionString .. skillsTable[4] .. tierString)
end

-- @param pPlayer - pointer to check for skills
-- @param tierNumber
function SpaceHelpers:hasExperienceForTraining(pPlayer, tierNumber)
	if (pPlayer == nil or tierNumber < 1 or tierNumber > 5) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local xpNeeded = -1

	if (tierNumber == 1) then
		xpNeeded = 7500
	elseif (tierNumber == 2) then
		xpNeeded = 60000
	elseif (tierNumber == 3) then
		xpNeeded = 200000
	elseif (tierNumber == 4) then
		xpNeeded = 1000000
	elseif (tierNumber == 5) then
		xpNeeded = 7500000
	end

	return (PlayerObject(pGhost):getExperience("space_combat_general") >= xpNeeded)
end

--[[

		Space Quest Handling
--]]

-- @param pPlayer pointer to activate quest on
-- @param questType from tre questlist/spacequest
-- @param questName
function SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, questType, questName, notifyClient)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (PlayerObject(pGhost):isJournalQuestActive(questCRC)) then
		return
	end

	local pDatapad = SceneObject(pPlayer):getSlottedObject("datapad")

	if (pDatapad == nullptr) then
		return
	end

	local isDutyMission = string.find(questName, "_duty")

	if (isDutyMission) then
		local hasDuty = false

		for j = 1, SceneObject(pDatapad):getContainerObjectsSize(), 1 do
			if (not hasDuty) then
				local pObject = SceneObject(pDatapad):getContainerObject(j - 1)

				if (pObject ~= nil and SceneObject(pObject):isMissionObject() and MissionObject(pObject):isSpaceDutyMission()) then
					hasDuty = true
				end
			end
		end

		if (hasDuty) then
			CreatureObject(pPlayer):sendSystemMessage("@space/quest:duty_already")
			return
		end
	end

	-- Create datapad mission object
	local pMission = giveItem(pDatapad, "object/mission/mission_object.iff", -1)

	if (pMission == nil) then
		Logger:log("ERROR: Failed to create Space Mission Object for Player: " .. SceneObject(pPlayer):getDisplayedName() .. " ID: " .. SceneObject(pPlayer):getObjectID(), LT_ERROR)
		return
	end

	local mission = LuaMissionObject(pMission)

	if (mission == nil) then
		Logger:log("ERROR: nil LuaMissionObject for Player: " .. SceneObject(pPlayer):getDisplayedName() .. " ID: " .. SceneObject(pPlayer):getObjectID(), LT_ERROR)
		return
	end

	mission:setTypeCRC(getHashCode("space_" .. questType))
	mission:setQuestType(questType)
	mission:setQuestName(questName)
	mission:setMissionTitle("space/quest", questType)
	mission:setMissionDescription(questString, "title_d")

	if (pNpc ~= nil) then
		mission:setCreatorName(SceneObject(pNpc):getObjectName());
	end

	if (isDutyMission) then
		mission:setSpaceDutyMission()
	end

	-- Broadcast mission to player
	SceneObject(pMission):sendTo(pPlayer)

	if (self.DEBUG_SPACE_HELPERS) then
		print("Activating Space Quest: " .. questString .. " Hash: " .. questCRC)
	end

	-- Update the players journal
	PlayerObject(pGhost):activateJournalQuest(questCRC, notifyClient)

	-- Send Player Messages
	local missionMsg= LuaStringIdChatParameter("@space/quest:quest_received") -- " \\#pcontrast3 Mission Received: < \\#pcontrast1 %TO \\#pcontrast3 >"
	missionMsg:setTO("@" .. questString .. ":title")

	CreatureObject(pPlayer):sendSystemMessage(missionMsg:_getObject())

	CreatureObject(pPlayer):playMusicMessage("sound/music_themequest_acc_criminal.snd")
end

-- @param pPlayer pointer to complete quest on
-- @param questType from tre questlist/spacequest
-- @param questName
function SpaceHelpers:completeSpaceQuest(pPlayer, questType, questName, notifyClient)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (not PlayerObject(pGhost):isJournalQuestActive(questCRC)) then
		return
	end

	if (self.DEBUG_SPACE_HELPERS) then
		print("Completing Space Quest: " .. questString .. " Hash: " .. questCRC)
	end

	-- Complete the Mission Object
	CreatureObject(pPlayer):removeQuestMission(questCRC)

	-- Complete Quest in Journal
	PlayerObject(pGhost):completeJournalQuest(questCRC, false)

	if (notifyClient) then
		-- Send Player Message
		SpaceHelpers:sendQuestSuccess(pPlayer, "@" .. questString .. ":title")

		CreatureObject(pPlayer):playMusicMessage("sound/music_themequest_victory_rebel.snd")
	end
end

-- @param pPlayer pointer to complete quest on
-- @param questType from tre questlist/spacequest
-- @param questName
function SpaceHelpers:failSpaceQuest(pPlayer, questType, questName, notifyClient)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (self.DEBUG_SPACE_HELPERS) then
		print("Failing Space Quest: " .. questString .. " Hash: " .. questCRC)
	end

	if (notifyClient) then
		if (questType == "patrol") then
			SpaceHelpers:sendQuestUpdate(pPlayer, "@space/quest:patrol_abandoned") -- "You abandoned your patrol!"
		elseif (questType == "destroy_surpriseattack") then
			SpaceHelpers:sendQuestUpdate(pPlayer, "@space/quest:destroy_surprise_abandoned") -- "You ran away from the attack and abandoned your duty!"
		elseif (questType == "escort_duty" or questType == "destroy_duty") then
			SpaceHelpers:sendDutyUpdate(pPlayer, "@space/quest:mission_abandoned") -- "You abandoned your mission!"
		else
			-- Failed Message
			SpaceHelpers:sendQuestUpdate(pPlayer, "@quest/quests:task_failure")
		end
	end

	-- Clear the Quest from their Journal
	PlayerObject(pGhost):clearJournalQuest(questCRC, false)

	-- Remove the Mission from players datapad
	CreatureObject(pPlayer):failQuestMission(questCRC)

	if (notifyClient) then
		if (string.find(questType, "duty")) then
			SpaceHelpers:sendMissionEnded(pPlayer, "@" .. questString .. ":title")
		else
			SpaceHelpers:sendMissionFailed(pPlayer, "@" .. questString .. ":title")
		end

		CreatureObject(pPlayer):playMusicMessage("sound/music_themequest_fail_criminal.snd")
	end
end

-- @param pPlayer pointer to check quest on
-- @param questType from tre questlist/spacequest
-- @param questName
function SpaceHelpers:isSpaceQuestActive(pPlayer, questType, questName)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (self.DEBUG_SPACE_HELPERS) then
		print("checking isActive for Space Quest: " .. questString .. " Hash: " .. questCRC)
	end

	return PlayerObject(pGhost):isJournalQuestActive(questCRC)
end

-- @param pPlayer pointer to clear quest on
-- @param questType from tre questlist/spacequest
-- @param questName
function SpaceHelpers:clearSpaceQuest(pPlayer, questType, questName, notifyClient)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (self.DEBUG_SPACE_HELPERS) then
		print("Clearing Space Quest: " .. questString .. " Hash: " .. questCRC)
	end

	PlayerObject(pGhost):clearJournalQuest(questCRC, notifyClient)
end

-- @param pPlayer pointer to activate quest on
-- @param questType from tre questlist/spacequest
-- @param questName
-- @param taskNumber to activate
function SpaceHelpers:activateSpaceQuestTask(pPlayer, questType, questName, taskNumber, notifyClient)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (self.DEBUG_SPACE_HELPERS) then
		print("Activating Space Quest Task: " .. questString .. " Hash: " .. questCRC .. " Task Num: " .. taskNumber)
	end

	PlayerObject(pGhost):activateJournalQuestTask(questCRC, taskNumber, notifyClient)
end

-- @param pPlayer pointer to complete quest task on
-- @param questType from tre directory questlist/spacequest
-- @param questName
-- @param taskNumber to clear
function SpaceHelpers:completeSpaceQuestTask(pPlayer, questType, questName, taskNumber, notifyClient)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (not PlayerObject(pGhost):isJournalQuestActive(questCRC)) then
		return
	end

	if (self.DEBUG_SPACE_HELPERS) then
		print("Completing Space Quest Task: " .. questString .. " Hash: " .. questCRC .. " Task Num: " .. taskNumber)
	end

	PlayerObject(pGhost):completeJournalQuestTask(questCRC, taskNumber, notifyClient)
end

-- @param pPlayer pointer to check for quest task on
-- @param questType from tre directory questlist/spacequest
-- @param questName
-- @param taskNumber to clear
function SpaceHelpers:isSpaceQuestTaskActive(pPlayer, questType, questName, taskNumber)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (not PlayerObject(pGhost):isJournalQuestActive(questCRC)) then
		return
	end

	if (self.DEBUG_SPACE_HELPERS) then
		print("Checking isActive for Space Quest Task: " .. questString .. " Hash: " .. questCRC .. " Task Num: " .. taskNumber)
	end

	return PlayerObject(pGhost):isJournalQuestTaskActive(questCRC, taskNumber)
end

-- @param pPlayer pointer to clear quest task on
-- @param questType from tre directory questlist/spacequest
-- @param questName
-- @param taskNumber to clear
function SpaceHelpers:clearSpaceQuestTask(pPlayer, questType, questName, taskNumber, notifyClient)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (self.DEBUG_SPACE_HELPERS) then
		print("Clearing Space Quest Task: " .. questString .. " Hash: " .. questCRC .. " Task Num: " .. taskNumber)
	end

	if (questCRC == 0) then
		return
	end

	-- Clear quest task from Journal
	PlayerObject(pGhost):clearJournalQuestTask(questCRC, taskNumber,notifyClient)
end

-- @param pPlayer pointer to check quest on
-- @param questType from tre questlist/spacequest
-- @param questName
function SpaceHelpers:isSpaceQuestComplete(pPlayer, questType, questName)
	if (pPlayer == nil) then
		return false
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (self.DEBUG_SPACE_HELPERS) then
		print("Checking completion for Space Quest: " .. questString .. " Hash: " .. questCRC)
	end

	return PlayerObject(pGhost):isJournalQuestComplete(questCRC)
end

-- @param pPlayer pointer to check quest task on
-- @param questType from tre directory questlist/spacequest
-- @param questName
-- @param taskNumber to check
function SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, questType, questName, taskNumber)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local questString = "spacequest/" .. questType .. "/" .. questName
	local questCRC = getHashCode(questString)

	if (self.DEBUG_SPACE_HELPERS) then
		print("Checking completion for Space Quest Task: " .. questString .. " Hash: " .. questCRC .. " Task Num: " .. taskNumber)
	end

	return PlayerObject(pGhost):isJournalQuestTaskComplete(questCRC, taskNumber)
end

--[[

	Space General Mission Functions

]]

-- @param pPlayer pointer to player to receive credits
-- @param amount - total credits to give
function SpaceHelpers:spaceCreditReward(pPlayer, amount)
	if (pPlayer == nil) then
		return
	end

	-- Send Player Message
	local messageString = LuaStringIdChatParameter("@space/quest:quest_reward")
	messageString:setDI(amount)

	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject()) -- "A payment of %DI credits have been transferred to your bank account."

	-- Give the Credits to bank
	CreatureObject(pPlayer):addBankCredits(amount, true)
end

-- @param pPlayer pointer to player to receive credits
-- @param itemString - string for item reward
function SpaceHelpers:spaceItemReward(pPlayer, itemString)
	if (pPlayer == nil or itemString == "") then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory == nil) then
		return
	end

	local pItem = giveItem(pInventory, itemString, -1)

	if (pItem ~= nil) then
		local messageString = LuaStringIdChatParameter("@space/quest:quest_rewarded")
		messageString:setTO(SceneObject(pItem):getDisplayedName())

		CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject()) -- " \\#pcontrast3 Reward Received: < \\#pcontrast1 %TO \\#pcontrast3 >"
	end
end

-- @param pPlayer pointer to player to receive message
-- @param message string
function SpaceHelpers:sendDelayedMessage(pPlayer, message)
	if (pPlayer == nil) then
		return
	end

	CreatureObject(pPlayer):sendSystemMessage(message)
end

-- @param pPlayer - pointer to player to remove waypoint from
-- @param questClass
function SpaceHelpers:clearQuestWaypoint(pPlayer, questClass)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local waypointID = tonumber(getQuestStatus(playerID .. ":" .. questClass .. ":waypointID"))

	-- Clear the waypointID and waypoint off the player
	removeQuestStatus(playerID .. ":" .. questClass .. ":waypointID")

	-- Clear the waypoint from the player object
	PlayerObject(pGhost):removeWaypoint(waypointID, true)
end

-- @param pPlayer - pointer to player to remove waypoints table from
-- @param questClass
function SpaceHelpers:clearQuestWaypoints(pPlayer, questClass)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local waypointTable = readStringVectorSharedMemory(playerID .. ":" .. questClass .. ":waypointVector")

	for i = 1, #waypointTable, 1 do
		local waypointID = tonumber(waypointTable[i])

		-- Clear the waypoint from the player object
		PlayerObject(pGhost):removeWaypoint(waypointID, true)
	end

	-- Clear the waypointIDs vector
	deleteStringVectorSharedMemory(playerID .. ":" .. questClass .. ":waypointVector")
end

-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendQuestUpdate(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local updateMsg = LuaStringIdChatParameter("@space/quest:quest_update_s") --" \\#pcontrast3 Mission Update: < \\#pcontrast1 %TO \\#pcontrast3 >"
	updateMsg:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(updateMsg:_getObject())
end

-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendDutyUpdate(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local updateMsg = LuaStringIdChatParameter("@space/quest:duty_update_s") -- " \\#pcontrast3 Duty Update: < \\#pcontrast1 %TO \\#pcontrast3 >"
	updateMsg:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(updateMsg:_getObject())
end


-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendQuestProgess(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local progressMsg = LuaStringIdChatParameter("@space/quest:quest_in_progress") -- " \\#pcontrast3 Mission in Progress: < \\#pcontrast1 %TO \\#pcontrast3 > \\#pcontrast2 (You must complete the mission before leaving this sector.) \\#pcontrast3 "
	progressMsg:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(progressMsg:_getObject())

	CreatureObject(pPlayer):playMusicMessage("sound/mus_quest_theme_opening.snd")
end

-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendQuestAlert(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local alertMsg = LuaStringIdChatParameter("@space/quest:quest_alert_s") -- " \\#pcontrast2 Mission Alert: \\#pcontrast3 < \\#pcontrast1 %TO \\#pcontrast3 >"
	alertMsg:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(alertMsg:_getObject())
end

-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendQuestReward(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local alertMsg = LuaStringIdChatParameter("@space/quest:quest_rewarded") -- " \\#pcontrast3 Reward Received: < \\#pcontrast1 %TO \\#pcontrast3 >"
	alertMsg:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(alertMsg:_getObject())

	CreatureObject(pPlayer):playMusicMessage("sound/music_themequest_victory_rebel.snd")
end

-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendQuestSuccess(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local successString = LuaStringIdChatParameter("@space/quest:quest_won")
	successString:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(successString:_getObject()) -- " \\#pcontrast3 Mission Successful: < \\#pcontrast1 %TO \\#pcontrast3 >"
end

-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendMissionEnded(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local successString = LuaStringIdChatParameter("@space/quest:quest_ended")
	successString:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(successString:_getObject()) -- " \\#pcontrast3 Mission Ended: < \\#pcontrast1 %TO \\#pcontrast3 >"
end

-- @param pPlayer - pointer to player
-- @param messageString
function SpaceHelpers:sendMissionFailed(pPlayer, messageString)
	if (pPlayer == nil) then
		return
	end

	local successString = LuaStringIdChatParameter("@space/quest:quest_failed")
	successString:setTO(messageString)

	CreatureObject(pPlayer):sendSystemMessage(successString:_getObject()) -- " \\#pcontrast3 Mission Failed: < \\#pcontrast1 %TO \\#pcontrast3 >"
end

-- @param pShipAgent - pointer to ShipAiAgent to destroy
function SpaceHelpers:delayedDestroyShipAgent(pShipAgent)
	if (pShipAgent == nil) then
		return
	end

	SceneObject(pShipAgent):destroyObjectFromWorld()
end

-- @param x, z, y - center coordinates
-- @param minRange - min distance to find the location
-- @param maxRange - max distance to find the location
function SpaceHelpers:getRandomPositionInSphere(x, z, y, minRange, maxRange)
	local radius = getRandomNumber(minRange, maxRange)
	local theta = math.random() * (2 * math.pi)  -- Random angle in XY plane
	local phi = math.acos(2 * math.random() - 1) -- Random angle in vertical plane

	local dx = radius * math.sin(phi) * math.cos(theta)
	local dy = radius * math.sin(phi) * math.sin(theta)
	local dz = radius * math.cos(phi)

	return {x = x + dx, z = z + dz, y = y + dy}
end

return SpaceHelpers