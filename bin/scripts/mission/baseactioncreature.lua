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
--combatFlags: ATTACKABLE_FLAG, AGGRESSIVE_FLAG, ENEMY_FLAG
	
ActionCreature = Object:new {
	objectName = "actcreature", -- name of the lua Object

	missionKey = "", -- key for mission creature is part of

	-- Regular Creature Settings:
	
	stfName = "",
	speciesName = "",
	name = "",
	level = 15,
	objectCRC = 0,
	planet = -1, -- THIS MUST BE SET. If left at -1, server will not load npc.
	
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
	
	combatFlags = NPC_FLAG,
	
	height = 1,
	
	positionX = 0,
	positionY = 0,
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
