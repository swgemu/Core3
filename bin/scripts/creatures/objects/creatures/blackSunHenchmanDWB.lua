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
blackSunHenchmanDWB = Creature:new {
	objectName = "blackSunHenchmanDWB", -- name of the lua Object
	
	name = "a Black Sun Henchman",
	objectCRC = 1930323679,
	socialGroup = "deathwatch",
	named = TRUE,

	level = 200,
	
	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	health = 14500,
	strength = 1000,
	constitution = 1000,

	action = 14500,
	quickness = 1000,
	stamina = 1000,

	mind = 14500,
	focus = 1000,
	willpower = 1000,

	height = 1,

	armor = 2,
	kinetic = 35,
	energy = 35,
	electricity = 60,
	stun = 30,
	blast = 50,
	heat = 25,
	cold = 45,
	acid = 25,
	lightSaber = 0,

	accuracy = 300,

	skills = { "dwbAttack40", "dwbAttack41", "dwbAttack42", "dwbAttack43", "dwbAttack44", "dwbAttack45", "dwbAttack46", "dwbAttack47", "dwbAttack48", "dwbAttack49", "dwbAttack50", "dwbAttack51"  },
	respawnTimer = 600,
}

Creatures:addCreature(blackSunHenchmanDWB, 1930323679) --- Add to global creature table
