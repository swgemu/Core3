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
	-- Server Vars:
	missionKey = "", -- UNIQUE internal key used to identify the mission. No spaces, keep small but informational
	terminalMask = TMASK_GENERAL, -- Terminal Bitmask

	-- Basic Mission Info setup:
	typeStr = "", -- SWG mission type string (03)
	stfDescriptionKey = "", -- key used by client to look up description in mission stf. Can be blank if custom is set (04)
	stfTitleKey = "", -- key used by client to look up title in mission stf. Can be blank if custom is set (04)

	difficultyLevel = 1, -- Mission difficulty level (05)

	destinationX = 0.0, -- X coordinate for destination of mission (06)
	destinationY = 0.0, -- Y coordinate for destination of mission (06)
	destinationPlanetStr = "", -- Destination planet name, must be lowercase (06)

	targetName = "", --Name of target to display
	creatorName = "", -- Name that appears in game as the assigner of the mission (usually an npc name) (07)
	rewardAmount = 0, -- Amount of credits awarded (08)

	startX = 0.0, -- X coordinate for start (aka "target/assigner npc") of mission (09)
	startY = 0.0, -- Y coordinate for start (aka "target/assigner npc") of mission (09)
	startPlanetStr = "", -- start planet name, must be lowercase (09)
	
	depictedObjectCrc = 0, -- Object CRC of the object pictured in mission window (10,0A)
	descriptionStf = "", -- TRE path to description stf. Can be blank if stfDescriptionKey isnt used (11,0B)
	customDescription = "", -- if stfDescriptionKey is not used, set a custom description here (04)
	titleStf = "", -- TRE path to title stf. Can be blank if stfTitleKey isnt used (12,0B)
	customTitle = "", -- if stfTitleKey is not used, set a custom title here (04)

	typeCrc = 0, -- SWGCRC of mission type. (14, 0E)

	objectiveDefaults = "", --Objective String. See documentation for formatting
	instantComplete = 1, --do Mission complete as soon as objectives are complete (no return to npc for evaluation)
}

