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

--[[

	Space Player Management and Checks

]]

-- @param pPlayer pointer grants the novice pilot box
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
	mission:setQuestCRC(questCRC)
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
	PlayerObject(pGhost):activateJournalQuest(questCRC, tonumber(notifyClient))

	-- Send Player Message
	local messageString = LuaStringIdChatParameter("@space/quest:quest_received")
	messageString:setTO("@" .. questString .. ":title")

	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject()) -- " \\#pcontrast3 Mission Received: < \\#pcontrast1 %TO \\#pcontrast3 >"

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
	PlayerObject(pGhost):completeJournalQuest(questCRC, tonumber(notifyClient))

	-- Send Player Message
	local messageString = LuaStringIdChatParameter("@space/quest:quest_won")
	messageString:setTO("@" .. questString .. ":title")

	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject()) -- " \\#pcontrast3 Mission Successful: < \\#pcontrast1 %TO \\#pcontrast3 >"

	CreatureObject(pPlayer):playMusicMessage("sound/music_themequest_victory_rebel.snd")
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

	if (not PlayerObject(pGhost):isJournalQuestActive(questCRC)) then
		return
	end

	if (self.DEBUG_SPACE_HELPERS) then
		print("Failing Space Quest: " .. questString .. " Hash: " .. questCRC)
	end

	if (questType == "patrol") then
		CreatureObject(pPlayer):sendSystemMessage("@space/quest:patrol_abandoned") -- "You abandoned your patrol!"
	end

	-- Failed Message
	CreatureObject(pPlayer):sendSystemMessage("@quest/quests:task_failure")

	-- Clear the Quest from their Journal
	PlayerObject(pGhost):clearJournalQuest(questCRC, false)

	-- Remove the Mission from players datapad
	CreatureObject(pPlayer):abortQuestMission(questCRC)

	-- Send Player Message
	local messageString = LuaStringIdChatParameter("@space/quest:quest_failed")
	messageString:setTO("@" .. questString .. ":title")

	CreatureObject(pPlayer):sendSystemMessage(messageString:_getObject()) -- " \\#pcontrast3 Mission Failed: < \\#pcontrast1 %TO \\#pcontrast3 >"

	CreatureObject(pPlayer):playMusicMessage("sound/music_themequest_fail_criminal.snd")
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

	PlayerObject(pGhost):clearJournalQuest(questCRC, tonumber(notifyClient))
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

	PlayerObject(pGhost):activateJournalQuestTask(questCRC, taskNumber, tonumber(notifyClient))
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

	PlayerObject(pGhost):completeJournalQuestTask(questCRC, taskNumber, tonumber(notifyClient))
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
	PlayerObject(pGhost):clearJournalQuestTask(questCRC, taskNumber,tonumber(notifyClient))
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

	Space Mission Functions

]]


-- @param pPlayer pointer to check quest task on
-- @param questType from tre directory questlist/spacequest
-- @param questName
-- @param taskNumber to check
function SpaceHelpers:spawnSurpriseAttack(pPilot, questScreenplay, questName, questTable)
	if (pPilot == nil) then
		return
	end

	local pPilotShip = SceneObject(pPilot):getRootParent()

	if (pPilotShip == nil or not SceneObject(pPilotShip):isShipObject()) then
		return 0
	end

	local x = SceneObject(pPilotShip):getPositionX()
	local z = SceneObject(pPilotShip):getPositionZ()
	local y = SceneObject(pPilotShip):getPositionY()

	if (self.DEBUG_SPACE_HELPERS) then
		print("SpaceHelpers:spawnSurpriseAttack - Screenplay: " .. questScreenplay .. " Space Quest: " .. questName)
	end

	local spawnZone = questTable.zone
	local shipsTable = questTable.spawns
	local pilotID = SceneObject(pPilot):getObjectID()

	if (self.DEBUG_SPACE_HELPERS) then
		print("spawnSurpriseAttack -- spawnZone: " .. spawnZone .. " shipsTable size: " .. #shipsTable)
	end

	local totalSpawned = 0

	for i = 1, #shipsTable, 1 do
		local count = shipsTable[i].count
		local shipName = shipsTable[i].shipName

		if (self.DEBUG_SPACE_HELPERS) then
			print("spawnSurpriseAttack -- spawning ship: " .. shipName .. " Spawn Count: " .. count)
		end

		for j = 1, count, 1 do
			local pShipAgent = spawnShipAgent(shipName, spawnZone, x + (getRandomNumber(50, 250) - getRandomNumber(50, 250)), z  + (getRandomNumber(50, 250) - getRandomNumber(50, 250)), y  + (getRandomNumber(50, 250) - getRandomNumber(50, 250)))

			if (pShipAgent ~= nil) then
				-- Setup the patrol
				ShipAiAgent(pShipAgent):setMinimumGuardPatrol(200)
				ShipAiAgent(pShipAgent):setMaximumGuardPatrol(1000)

				ShipAiAgent(pShipAgent):setGuardPatrol()

				-- Make sure the extra mobs are despawned if all players leaves the area
				ShipAiAgent(pShipAgent):setDespawnOnNoPlayerInRange(true)

				-- Add kill observer
				createObserver(OBJECTDESTRUCTION, questScreenplay, "notifyShipDestroyed", pShipAgent)

				-- Set the player as ShipAgents Defender
				ShipAiAgent(pShipAgent):setDefender(pPilotShip)

				totalSpawned = totalSpawned + 1

				-- Store the quest owner
				writeData(SceneObject(pShipAgent):getObjectID() .. ":QuestOwner", pilotID)
			end
		end
	end

	if (totalSpawned > 0) then
		writeData(pilotID .. questName .. ":SurpriseAttackCount", totalSpawned)
	end
end

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

return SpaceHelpers