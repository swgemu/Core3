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


object_ship_player_player_decimator = object_ship_player_shared_player_decimator:new {
	name = "player_decimator",
	slideFactor = 1.85,
	chassisHitpoints = 5000,
	chassisMass = 5000000,

	containerComponent = "PobShipContainerComponent",

	-- POBSHIP
	gameObjectType = 536870917,
	category = "pob",
	level = 5,

	attributes = {
		{"speedRotationFactorMin", 0.2},
		{"speedRotationFactorOptimal", 0.3},
		{"speedRotationFactorMax", 0.3},
		{"slideDamp", 1.2},
		{"engineAccel", 5},
		{"engineDecel", 5},
		{"engineYawAccel", 50},
		{"enginePitchAccel", 50},
		{"engineRollAccel", 37.5},
		{"maxSpeed", 0.8},
	},

	reactor = { name = "rct_generic", hitpoints = 395.0898, armor = 393.2448,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.26176, armor = 96.47783, speed = 63.61601, pitch = 53.90641, roll = 53.77215, yaw = 20.96006, acceleration = 14.29806, rollRate = 80.7669, pitchRate = 73.72273, deceleration = 13.31472, yawRate = 37.25309,},
	shield_0 = { name = "shd_generic", hitpoints = 383.4029, armor = 490.7114, regen = 2.854131, front = 1576.617, back = 1591.529,},
	armor_0 = { name = "arm_generic", hitpoints = 1092.34, armor = 1052.53,},
	armor_1 = { name = "arm_generic", hitpoints = 1051.848, armor = 1070.727,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.51637, energy = 1101.85,},
	booster = { name = "bst_generic", hitpoints = 19.69023, armor = 19.73825, energy = 98.89352, acceleration = 19.44626, speed = 14.42604, energyUsage = 9.96958, rechargeRate = 4.918709,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 190.0977, armor = 192.0175, rate = 0.3419655, drain = 22.89144, maxDamage = 1468.528, shieldEfficiency = 0, minDamage = 745.0324, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 191.437, armor = 192.2777, rate = 0.331361, drain = 22.71493, maxDamage = 949.7935, shieldEfficiency = 0, minDamage = 609.7089, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_xwing_missile_s01", hitpoints = 19.22288, armor = 19.00229, rate = 5.818878, drain = 23.56116, maxDamage = 22.4802, shieldEfficiency = 0, minDamage = 23.33798, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 243.146, armor = 243.0917, rate = 0.09659296, drain = 23.08529, maxDamage = 99.77181, shieldEfficiency = 0, minDamage = 24.74274, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
	lots = 4,

	childObjects = {
		{ templateFile = "object/tangible/shipcontrol/shipcontrol_falcon.iff", x = -0.65, z = 3.38, y = 5.3, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 1, containmentType = -1 },
		{ templateFile = "object/tangible/shipcontrol/shipoperations_falcon.iff", x = 0.76, z = 3.4, y = 5.19, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 1, containmentType = -1 },
		-- Turret Control
		{ templateFile = "object/tangible/shipcontrol/turretcontrol_vt49.iff", x = 0.014, z = 4.26, y = -7.35, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 1, containmentType = -1 },
		-- Ship Permissions Terminal
		{ templateFile = "object/tangible/terminal/terminal_pob_ship.iff", x = -0.88, z = -2.57, y = 19.68, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 3, containmentType = -1 },
		-- Cockpit
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -2.83, z = 4.18, y = 0.66, ox = 0.000000, oy = 0.000000, oz = -0.159900, ow = 0.987133, cellid = 1, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 2.83, z = 4.18, y = 0.66, ox = 0.000000, oy = 0.000000, oz = 0.159900, ow = 0.987133, cellid = 1, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 0.03, z = 2.76, y = -4.26, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 1, containmentType = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 5.54, z = 3.03, y = -2.09, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -5.54, z = 3.03, y = -2.09, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1 },
		-- Storage 2
		{ templateFile = "object/tangible/ship/interior_components/engine_interior.iff", x = -7.27, z = 0.71, y = -4.27, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -6.77, z = -0.17, y = 2.03, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 2, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/reactor_interior.iff", x = 6.48, z = -0.11, y = -4.25, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1, componentSlot = 0 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 4.76, z = -0.36, y = -2.06, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 6.51, z = 2.14, y = -1.19, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 2, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -6.51, z = 2.14, y = -1.22, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 2, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/escape_pod_hatch.iff", x = -8.98, z = 0.3, y = -2.5, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/escape_pod_hatch.iff", x = 8.87, z = 0.30, y = -2.49, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/escape_pod_hatch.iff", x = 10.21, z = 0.93, y = -1.57, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/weapon_interior.iff", x = 2.37, z = -0.48, y = -2.9, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = 12 },
		{ templateFile = "object/tangible/ship/interior_components/weapon_interior.iff", x = -2.37, z = -0.48, y = -2.9, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = 13 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 5.64, z = -1.5, y = 5.75, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -5.39, z = -1.5, y = 5.93, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/capacitor_interior.iff", x = 3.7, z = 0.06, y = 9.17, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 2, containmentType = -1, componentSlot = 6 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 1.47, z = 0.84, y = 9.26, ox = -0.707107, oy = 0.000000, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -2 },
		-- Storage3
		{ templateFile = "object/tangible/container/drum/pob_ship_loot_box.iff", x = 0.27, z = -2.57, y = 9.91, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 3, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 0.21, z = 0.2, y = 19.81, ox = -0.707107, oy = 0.000000, oz = 0.000000, ow = 0.707107, cellid = 3, containmentType = -1, componentSlot = -2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 4.46, z = -1.91, y = 16.71, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 3, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -4.47, z = -1.94, y = 16.72, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 3, containmentType = -1, componentSlot = -1 },
		-- Lounge
		{ templateFile = "object/tangible/ship/interior_components/shield_generator_interior.iff", x = -1.4, z = -1.09, y = 20.2, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 4, containmentType = -1, componentSlot = -2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -4.1, z = -1.66, y = 22.01, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 4, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 3.47, z = -0.22, y = 27.4, ox = 0.628251, oy = -0.628251, oz = -0.324501, ow = 0.324501, cellid = 4, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -0.03, z = 2.82, y = 24.43, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 4, containmentType = -1, componentSlot = -2 },
	},

	plasmaConduits = {
		-- Cockpit
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 5.54, z = 3.03, y = -2.09, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -5.54, z = 3.03, y = -2.09, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		-- Storage 2
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -6.77, z = -0.17, y = 2.03, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 2, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 4.76, z = -0.36, y = -2.06, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 5.64, z = -1.5, y = 5.75, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -1, componentDamageSlot = 6 }, -- Capacitor
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -5.39, z = -1.5, y = 5.93, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 2, containmentType = -1, componentSlot = -1, componentDamageSlot = 6 }, -- Capacitor
		-- Storage3
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 4.46, z = -1.91, y = 16.71, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 3, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -4.47, z = -1.94, y = 16.72, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 3, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
		-- Lounge
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -4.1, z = -1.66, y = 22.01, ox = 0.000000, oy = 0.707107, oz = 0.000000, ow = 0.707107, cellid = 4, containmentType = -1, componentSlot = -1, componentDamageSlot = 2 }, -- Shield
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 3.47, z = -0.22, y = 27.4, ox = 0.628251, oy = -0.628251, oz = -0.324501, ow = 0.324501, cellid = 4, containmentType = -1, componentSlot = -1, componentDamageSlot = 2 }, -- Shield
	},

	sparkLocations = {
		{cellName = "cockpit",
			{x = 0.76, z = 3.41, y = 5.19},
			{x = 0.01, z = 4.26, y = -7.35},
			{x = -0.46, z = 0.4, y = -5.45},
			{x = -5, z = 2.4, y = -5.29},
			{x = 5, z = 2.4, y = -0.35},
		},
		{cellName = "storage2",
			{x = 6.48, z = -0.11, y = -4.25},
			{x = 4.76, z = -0.36, y = -2.06},
			{x = -1.06, z = -1.9, y = 2.79},
			{x = -3.77, z = -1.68, y = -1.85},
			{x = -9.07, z = -0.93, y = -2.46},
			{x = -7.54, z = -1.5, y = 1.56},
			{x = -4.83, z = -1.9, y = 4.94},
			{x = -4.76, z = -1.9, y = 8.75},
			{x = 4.09, z = -1.9, y = 8.75},
			{x = 5.1, z = -1.9, y = 4.53},
			{x = 3.65, z = -1.68, y = -1.7},
			{x = 7.79, z = -1.5, y = 1.57},
			{x = 7.79, z = -1.5, y = -3.8},
		},
		{cellName = "storage3",
			{x = 8.87, z = 0.3, y = -2.49},
			{x = 0.27, z = -2.57, y = 9.91},
			{x = -4.07, z = -2.57, y = 11.24},
			{x = -3.7, z = -2.57, y = 15.15},
			{x = 3.72, z = -2.57, y = 14.88},
			{x = -0.63, z = -2.57, y = 15.03},
		},
		{cellName = "lounge",
			{x = 4.46, z = -1.91, y = 16.71},
			{x = -4.47, z = -1.94, y = 16.72},
			{x = 2.63, z = -2.86, y = 22.58},
			{x = -2.77, z = -2.86, y = 21.52},
		},
	},

	launchPoints = {
		{cellName = "cockpit",
			{x = 1.4, z = 2.9, y = 3.6},
			{x = -2.1, z = 2.9, y = 3.7},
			{x = 0, z = 0.4, y = -5.3},
		},
		{cellName = "storage2",
			{x = 3.1, z = -1.9, y = 6.6},
		},
		{cellName = "storage3",
			{x = 3, z = -2.6, y = 12.7},
		},
		{cellName = "lounge",
				{x = -2.2, z = -2.9, y = 23.2},
				{x = 0.1, z = -1.9, y = 28.7},
		},
	},
}

ObjectTemplates:addTemplate(object_ship_player_player_decimator, "object/ship/player/player_decimator.iff")
