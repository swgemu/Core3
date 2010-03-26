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

Mission = Object:new {
	missionKey = "", -- UNIQUE internal key used to identify the mission. No spaces, keep small
	
	-- Title/Name:
	stfTitleKey = "", -- key used by client to look up title in mission stf. Can be blank if custom is set
	titleStf = "", -- TRE path to title stf. Can be blank if stfTitleKey isnt used
	customTitle = "", -- if stfTitleKey is not used, set a custom title here

	-- General: (type, terminal etc)
	terminalMask = TMASK_GENERAL, -- Terminal Bitmask
	typeStr = "", -- SWG mission type string 
	typeCrc = 0, -- deliver(E5C27EC6,3854728902) or destroy(74EF9BE3,1961860067) SWGCRC of mission type
	creatorName = "", -- Name that appears in game as the assigner of the mission (usually an npc name)
	difficultyLevel = 1, -- Mission difficulty level

	-- Location: Start (npc assigner)
	startX = 0.0, -- X coordinate for start (aka "target/assigner npc") of mission
	startY = 0.0, -- Y coordinate for start (aka "target/assigner npc") of mission
	startPlanetStr = "", -- start planet name, must be lowercase

	-- Location: Destination (target)
	destinationX = 0.0, -- X coordinate for destination of mission
	destinationY = 0.0, -- Y coordinate for destination of mission
	destinationPlanetStr = "", -- Destination planet name, must be lowercase

	-- Rewards
	rewardCredits = 0, -- Amount of credits awarded to bank
	rewardXP = "", -- (xpType:value;xpType:value etc) Xp to reward upon mission completion
	rewardBadgeIds = "", -- (badge ids, delimited by commas) Ids of the badge to award
	rewardFactions = "", -- (factionName:points;factionName:points etc) Faction & points to award to that faction. If points are negative, they will be subtracted from the faction
	rewardObjects = "", -- Serialized string of objects (items) to award the player. See documentation for details

	-- Description
	stfDescriptionKey = "", -- key used by client to look up description in mission stf. Can be blank if custom is set
	descriptionStf = "", -- TRE path to description stf. Can be blank if stfDescriptionKey isnt used
	customDescription = "", -- if stfDescriptionKey is not used, set a custom description here

	-- Objective & Target
	targetName = "", --Name of target to display
	depictedObjectCrc = 0, -- Object CRC of the object pictured in mission window
	objectiveDefaults = "", --Objective String. See documentation for formatting
	instantComplete = 1, --do Mission complete as soon as objectives are complete (no return to npc for evaluation)
}

