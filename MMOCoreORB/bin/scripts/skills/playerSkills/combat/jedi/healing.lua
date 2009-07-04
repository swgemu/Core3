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

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "healallself2",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 470,
	
	HealHealth = 1500,
	HealAction = 1500,
	HealMind = 1500,

	speed = 4.0,

	healDizzy = 0,
	healStun = 0,
	healBlind = 0,
	healIntimidate = 0,

	healPoison = 0,
	healFire = 0,
	healBleeding = 0,
	healDisease = 0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "healstatesself",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 50,
	
	healHealth = 0,
	healAction = 0,
	healMind = 0,

	speed = 1.0,

	healDizzy = 1,
	healStun = 1,
	healBlind = 1,
	healIntimidate = 1,

	healPoison = 0,
	healFire = 0,
	healBleeding = 0,
	healDisease = 0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

HealTargetSk = {
	skillname = "healallother2",
	effect = "clienteffect/pl_force_healing.cef",
	animation = "force_healing_1",
	
	--forceCost = 400,
	healHealth = 2000,
	healAction = 2000,
	healMind = 2000,

	speed = 3.0,
	
	range = 32
}

AddHealTargetSkill(HealTargetSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "healallself1",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 340,
	HealHealth = 500,
	HealAction = 500,
	HealMind = 500,
	
	speed = 4.0,
	
	healDizzy = 0,
	healStun = 0,
	healBlind = 0,
	healIntimidate = 0,

	healPoison = 0,
	healFire = 0,
	healBleeding = 0,
	healDisease = 0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "healhealthself2",
	effect = "clienteffect/pl_force_healing.cef",
	
	forceCost = 100,
	
	HealHealth = 1500,
	HealAction = 0,
	HealMind = 0,

	speed = 3.0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "healactionself2",
	effect = "clienteffect/pl_force_healing.cef",
	
	forceCost = 100,
	
	HealHealth = 0,
	HealAction = 1500,
	HealMind = 0,

	speed = 3.0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "healmindself2",
	effect = "clienteffect/pl_force_healing.cef",
	
	forceCost = 100,
	
	HealHealth = 0,
	HealAction = 0,
	HealMind = 1500,

	speed = 3.0
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "stopbleeding",
	effect = "clienteffect/pl_force_healing.cef",
	
	forceCost = 75,
	
	healHealth = 0,
	healAction = 0,
	healMind = 0,

	speed = 4.0,

	healDizzy = 0,
	healStun = 0,
	healBlind = 0,
	healIntimidate = 0,

	healPoison = 0,
	healFire = 0,
	healBleeding = 1,
	healDisease = 0
	
}

AddForceHealSelfSkill(ForceHealSk)


-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "forcecuredisease",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 75,
	
	healHealth = 0,
	healAction = 0,
	healMind = 0,

	speed = 4.0,

	healDizzy = 0,
	healStun = 0,
	healBlind = 0,
	healIntimidate = 0,

	healPoison = 0,
	healFire = 0,
	healBleeding = 0,
	healDisease = 1
	
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "forcecurepoison",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 75,
	
	healHealth = 0,
	healAction = 0,
	healMind = 0,

	speed = 4.0,

	healDizzy = 0,
	healStun = 0,
	healBlind = 0,
	healIntimidate = 0,

	healPoison = 1,
	healFire = 0,
	healBleeding = 0,
	healDisease = 0
	
}

AddForceHealSelfSkill(ForceHealSk)

-----------------------------------------------------------------------

ForceHealSk = {
	skillname = "totalhealself",
	effect = "clienteffect/pl_force_healing.cef",

	forceCost = 1000,
	
	HealHealth = 5000,
	HealAction = 5000,
	HealMind = 5000,

	speed = 4.0,

	healDizzy = 1,
	healStun = 1,
	healBlind = 1,
	healIntimidate = 1,

	healPoison = 1,
	healFire = 1,
	healBleeding = 1,
	healDisease = 1
	
}

AddForceHealSelfSkill(ForceHealSk)