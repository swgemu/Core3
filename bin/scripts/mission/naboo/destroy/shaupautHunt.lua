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

theShaupautHunt = Mission:new {
	missionKey = "tsh1", -- UNIQUE internal key used to identify the mission. No spaces, keep small
	
	-- Title/Name:
	stfTitleKey = "", -- key used by client to look up title in mission stf. Can be blank if custom is set
	titleStf = "", -- TRE path to title stf. Can be blank if stfTitleKey isnt used
	customTitle = "The Shaupaut Hunt", -- if stfTitleKey is not used, set a custom title here

	-- General: (type, terminal etc)
	terminalMask = TMASK_GENERAL, -- Terminal Bitmask
	typeStr = "mission_destroy", -- SWG mission type string 
	typeCrc = 1961860067, -- deliver(E5C27EC6,3854728902) or destroy(74EF9BE3,1961860067) SWGCRC of mission type
	creatorName = "David Karivalis", -- Name that appears in game as the assigner of the mission (usually an npc name)
	difficultyLevel = 1, -- Mission difficulty level

	-- Location: Start (npc assigner)
	startX = -4844.0, -- X coordinate for start (aka "target/assigner npc") of mission
	startY = 4155.0, -- Y coordinate for start (aka "target/assigner npc") of mission
	startPlanetStr = "naboo", -- start planet name, must be lowercase

	-- Location: Destination (target)
	destinationX = -4865.0, -- X coordinate for destination of mission
	destinationY = 3916.0, -- Y coordinate for destination of mission
	destinationPlanetStr = "naboo", -- Destination planet name, must be lowercase

	-- Rewards
	rewardCredits = 1500, -- Amount of credits awarded to bank
	rewardXP = "", -- (xpType:value;xpType:value etc) Xp to reward upon mission completion
	rewardBadgeIds = "", -- (badge ids, delimited by commas) Ids of the badge to award
	rewardFactions = "", -- (factionName:points;factionName:points) Faction & points to award to that faction. If points are negative, they will be subtracted from the faction
	rewardObjects = "", -- Serialized string of objects (items) to award the player. See documentation for details

	-- Description
	stfDescriptionKey = "", -- key used by client to look up description in mission stf. Can be blank if custom is set
	descriptionStf = "", -- TRE path to description stf. Can be blank if stfDescriptionKey isnt used
	customDescription = "A bag fertilizer I use for my farm dropped off my ship as I was landing at the starport. Unforunately, local shaupaut have ingested the stuff and, as a side effect, have been reproducing at ten times the natural rate. Please kill 10 of the shaupaut right outside of the city and return to me at (-4895,4193) for your reward.", -- if stfDescriptionKey is not used, set a custom description here

	-- Objective & Target
	targetName = "(10x) shaupaut", --Name of target to display
	depictedObjectCrc = 176125140, -- Object CRC of the object pictured in mission window
	objectiveDefaults = "1:176125140:0:10:shaupaut:0", --Objective String. See documentation for formatting
	instantComplete = 0, --do Mission complete as soon as objectives are complete (no return to npc for evaluation)
}

AddMissionToServer(theShaupautHunt)
