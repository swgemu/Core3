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


object_ship_star_destroyer = object_ship_shared_star_destroyer:new {
	objectName = "@space/space_mobile_type:star_destroyer",

	name = "star_destroyer",
	type = "star_destroyer",
	faction = "imperial",
	difficulty = "",

	slideFactor = 1.88,
	chassisHitpoints = 100000,
	chassisMass = 50000,

	gameObjectType = 536870920,

	reactor = {name = "rct_generic", hitpoints = 50000, armor = 25000},
	engine = {name = "eng_incom_fusialthrust", hitpoints = 50000, armor = 25000, speed = 0, acceleration = 0, deceleration = 0, yaw = 0, yawRate = 0, pitch = 0, pitchRate = 0, roll = 0, rollRate = 0},
	shield_0 = {name = "shd_generic", hitpoints = 50000, armor = 25000, front = 75000, back = 75000, regen = 5},
	shield_1 = {name = "shd_generic", hitpoints = 50000, armor = 25000, front = 75000, back = 75000, regen = 5},
	armor_0 = {name = "arm_generic", hitpoints = 50000, armor = 25000},
	armor_1 = {name = "arm_generic", hitpoints = 50000, armor = 25000},
	capacitor = {name = "cap_generic", hitpoints = 50000, armor = 25000, energy = 1740.8, rechargeRate = 69.632},
	bridge = {name = "bdg_generic", hitpoints = 200000, armor = 200000},
	hangar = {name = "hgr_generic", hitpoints = 200000, armor = 200000},
	targeting_station = {name = "tst_generic", hitpoints = 200000, armor = 200000},

	weapon_0 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_1 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_2 = {name = "wpn_star_destroyer_turret_square", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_3 = {name = "wpn_star_destroyer_turret_square", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_4 = {name = "wpn_star_destroyer_turret_square", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_5 = {name = "wpn_star_destroyer_turret_square", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_6 = {name = "wpn_star_destroyer_turret_square", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_7 = {name = "wpn_star_destroyer_turret_square", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_8 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_9 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_10 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_11 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_12 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_13 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_14 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_15 = {name = "wpn_star_destroyer_turret_med", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_16 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_17 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_18 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_19 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_20 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_21 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_22 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_23 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_24 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_25 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_26 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_27 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_28 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_29 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_30 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_31 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_32 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_33 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_34 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_35 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_36 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_37 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_38 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_39 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_40 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_41 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_42 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_43 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_44 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_45 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_46 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_47 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_48 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_49 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_50 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_51 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_52 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_53 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_54 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_55 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_56 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_57 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_58 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_59 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_60 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_61 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_62 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_63 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_64 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_65 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_66 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_67 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_68 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_69 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_70 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_71 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_72 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_73 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_74 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_75 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_76 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_77 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_78 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_79 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_80 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_81 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_82 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_83 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_84 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_85 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_86 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_87 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_88 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_89 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},

	weapon_90 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_91 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_92 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_93 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_94 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	--weapon_95 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_96 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_97 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_98 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
	weapon_99 = {name = "wpn_star_destroyer_turret_dome", hitpoints = 50000, armor = 50000, rate = 0.531, drain = 0, maxDamage = 400, minDamage = 150, shieldEfficiency = 1, armorEfficiency = 1, ammo = 0, ammo_type = 0},
}

ObjectTemplates:addTemplate(object_ship_star_destroyer, "object/ship/star_destroyer.iff")
