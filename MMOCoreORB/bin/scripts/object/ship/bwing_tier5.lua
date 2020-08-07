--Copyright (C) 2010 <SWGEmu>


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


object_ship_bwing_tier5 = object_ship_shared_bwing_tier5:new {

	name = "bwing_tier5",
	slideFactor = 1.67,
	chassisHitpoints = 2949.12,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3666.989, armor = 3796.521,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3802.117, armor = 3645.021, speed = 46.90529, pitch = 25.6751, roll = 32.16349, yaw = 20.02636, acceleration = 11.19581, rollRate = 56.43748, pitchRate = 50.76598, deceleration = 9.656651, yawRate = 42.29537,},
	shield_0 = { name = "shd_generic", hitpoints = 3736.481, armor = 3742.38, regen = 22.50838, front = 14764.85, back = 14777.5,},
	armor_0 = { name = "arm_generic", hitpoints = 7967.488, armor = 7801.471,},
	armor_1 = { name = "arm_generic", hitpoints = 7753.859, armor = 7824.613,},
	capacitor = { name = "cap_generic", hitpoints = 3645.117, armor = 3693.623, rechargeRate = 97.65691, energy = 4822.805,},
	weapon_0 = { name = "wpn_bwing_blaster", hitpoints = 3805.758, armor = 3676.211, rate = 0.7774719, drain = 0.9763737, maxDamage = 350.7338, shieldEfficiency = 0.55013, minDamage = 216.9212, ammo = 0, ammo_type = 0, armorEfficiency = 0.5465078,},
	weapon_1 = { name = "wpn_bwing_blaster", hitpoints = 3688.053, armor = 3708.341, rate = 0.769612, drain = 0.9658349, maxDamage = 351.0966, shieldEfficiency = 0.5458498, minDamage = 222.4749, ammo = 0, ammo_type = 0, armorEfficiency = 0.5415144,},
	weapon_2 = { name = "wpn_bwing_blaster", hitpoints = 3633.208, armor = 3632.452, rate = 0.7598686, drain = 0.9694598, maxDamage = 352.2643, shieldEfficiency = 0.5449794, minDamage = 216.8951, ammo = 0, ammo_type = 0, armorEfficiency = 0.5567271,},
	weapon_3 = { name = "wpn_bwing_blaster", hitpoints = 3707.016, armor = 3662.767, rate = 0.7638378, drain = 0.9962587, maxDamage = 353.9543, shieldEfficiency = 0.5433153, minDamage = 218.7249, ammo = 0, ammo_type = 0, armorEfficiency = 0.5324981,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 3817.339, armor = 3785.206, rate = 2.967133, drain = 0.966063, maxDamage = 1057.759, shieldEfficiency = 0.726448, minDamage = 437.9447, ammo = 4, ammo_type = 20, armorEfficiency = 0.7239467,},
}

ObjectTemplates:addTemplate(object_ship_bwing_tier5, "object/ship/bwing_tier5.iff")
