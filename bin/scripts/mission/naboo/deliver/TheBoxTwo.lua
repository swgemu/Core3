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

theBoxTwoMission = Mission:new {
	-- Server Vars:
	missionKey = "tb2d", -- UNIQUE internal key used to identify the mission. No spaces, keep small but informational
	terminalMask = TMASK_GENERAL, -- Terminal Bitmask

	-- Basic Mission Info setup:
	typeStr = "mission_deliver", -- SWG mission type string (03)
	stfDescriptionKey = "", -- key used by client to look up description in mission stf. Can be blank if custom is set (04)
	stfTitleKey = "", -- key used by client to look up title in mission stf. Can be blank if custom is set (04)

	difficultyLevel = 1, -- Mission difficulty level (05)

	destinationX = -5049.0, -- X coordinate for destination of mission (06)
	destinationY = 4225.0, -- Y coordinate for destination of mission (06)
	destinationPlanetStr = "naboo", -- SWGCRC for destination planet name (06)

	creatorName = "Ramsey", -- Name that appears in game as the assigner of the mission (usually an npc name) (07)
	rewardAmount = 0, -- Amount of credits awarded (08)

	startX = -4844.0, -- X coordinate for start (aka "target/assigner npc") of mission (09)
	startY = 4155.0, -- Y coordinate for start (aka "target/assigner npc") of mission (09)
	startPlanetStr = "naboo", -- SWGCRC for start (aka "target/assigner npc") planet name (09)
	
	depictedObjectCrc = 2610980168, -- Object CRC of the object pictured in mission window (10,0A)
	descriptionStf = "", -- TRE path to description stf. Can be blank if stfDescriptionKey isnt used (11,0B)
	customDescription = "The box...has returned! Help me get rid of it by handing this box over to THE MAN.", -- if stfDescriptionKey is not used, set a custom description here (04)
	titleStf = "", -- TRE path to title stf. Can be blank if stfTitleKey isnt used (12,0B)
	customTitle = "The Box Two", -- if stfTitleKey is not used, set a custom title here (04)

	typeCrc = 3854728902 -- deliver crc SWGCRC of mission type. (14, 0E)
}

manoactiontwo = Object:new {
	objectName = "ManOAction2", -- name of the lua Object

	missionKey = "tb2d", -- key for mission creature is part of

-- Regular Creature Settings:
	
	stfName = "",
	speciesName = "",
	name = "ManOActionTwo",
	level = 15,
	objectCRC = 675581684,
	planet = 5, -- THIS MUST BE SET. If left at -1, server will not load npc.
	
	faction = "",
	factionPoints = 0,
	gender = "",
	boneType = "",
	hideType = "",
	meatType = "",
	lootGroup = "",
	
	healthMax = 1,
	healthMin = 0,
	strength = 0,
	constitution = 0,

	actionMax = 0,
	actionMin = 0,
	quickness = 0,
	stamina = 0,

 	mindMax = 0,
	mindMin = 0,
 	focus = 0,
 	willpower = 0,
	
	armor = 0,

	kinetic = 15,
	energy = 15,
	electricity = 15,
	stun = 0,
	blast = 15,
	heat = 15,
	cold = 15,
	acid = 15,
	lightSaber = 0,

	xp = 0,
	
	combatFlags = 0,
	
	height = 1,
	
	positionX = -4844.0,
	positionY = 4150.0,
	positionZ = 0,
	
	
	directionX = 0,
	directionZ = 0,
	directionY = 0,
	directionW = 0,
	
	accuracy = 200,
	
	creatureBitmask = 0,
	
	speed = 5.76,
	acceleration = 1.549,
	
	respawnTimer = 60,

	skills = { },

	cellID = 0,
	
	randomMovement = 1,

	randomizeRespawnPoint = false,
	
	mood = ""
}

testact = Action:new {
	objectName = "testact", -- name of the lua Object
	actionKey = "am_cnv", -- UNIQUE internal key used to identify the action. No spaces, keep small but informational

	prereqMask = 0,
	actionMask = ATYPE_CONVERSE,

	-- Optional Triggers
	onConverse = 1,
	onTrade = 0,
	onAttack = 0,
	onDeath = 0,
	--
	
	--------
	-- Prerequisite Vars:
	--------

	-- Has mission:
	meet_hasMission = "", -- Fill in w/ mission key to check if player has specified mission

	-- Kill Count Limit - KILL COUNTING / TRACKING
	meet_killLimitList = "", -- List of creature crc / limit value pairs. See documentation for more information.

	--------
	-- Action Vars:
	--------

	-- Conversation Vars
	convoScreenList = "0,refuse", -- Keep this updated with ALL your screen ids. ScreenID "0" is REQUIRED.
	--
}

-- Build Conversation Screens for testact

    -- Opening Screen
    basicHelloScreen = ConvoScreen:new()
    basicHelloScreen:setId("0")
    basicHelloScreen:setDialog("Hello from LEFT DIAG")
    basicHelloScreen:addOption("Got candy?", "refuse", "none")
    basicHelloScreen:addOption("Goodbye", "ENDCNV", "none")
    ScreenTable:addConvoScreen(basicHelloScreen)
    
    -- Candy Refusal Screen
    refuseScreen = ConvoScreen:new()
    refuseScreen:setId("refuse")
    refuseScreen:setDialog("No, I do not have candy.")
    refuseScreen:addOption("Goodbye", "ENDCNV", "none")
    ScreenTable:addConvoScreen(refuseScreen)
    
-- End Conversation Building

testacttwo = Action:new {
	actionKey = "blah2", -- UNIQUE internal key used to identify the action. No spaces, keep small but informational

	prereqMask = 0,
	actionMask = 0,

	-- Optional Triggers
	onConverse = 0,
	onTrade = false,
	onAttack = false,
	onDeath = false,
	--
	
	--------
	-- Prerequisite Vars:
	--------

	-- Has mission:
	meet_hasMission = "", -- Fill in w/ mission key to check if player has specified mission

	-- Kill Count Limit - KILL COUNTING / TRACKING
	meet_killLimitList = "", -- List of creature crc / limit value pairs. See documentation for more information.

	--------
	-- Action Vars:
	--------

	-- Conversation Vars
	convoScreenList = "", -- Keep this updated with ALL your screen ids. ScreenID "0" is REQUIRED.
	--
}

MissionTable:addMission(theBoxTwoMission, "tb2d")
AddActionCreatureToServer(testact, manoactiontwo)
