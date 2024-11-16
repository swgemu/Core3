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


object_ship_player_player_yt1300 = object_ship_player_shared_player_yt1300:new {
	name = "player_yt1300",
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

	reactor = { name = "rct_generic", hitpoints = 391.9558, armor = 381.4522,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.82562, armor = 98.25301, speed = 63.97898, pitch = 52.14573, roll = 52.79561, yaw = 20.14787, acceleration = 14.34252, rollRate = 81.50523, pitchRate = 74.24856, deceleration = 13.13524, yawRate = 36.47185,},
	shield_0 = { name = "shd_generic", hitpoints = 396.4766, armor = 477.7777, regen = 2.886155, front = 1573.84, back = 1576.103,},
	armor_0 = { name = "arm_generic", hitpoints = 1050.284, armor = 1075.379,},
	armor_1 = { name = "arm_generic", hitpoints = 1065.105, armor = 1082.513,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.81905, energy = 1104.78,},
	booster = { name = "bst_generic", hitpoints = 19.69748, armor = 19.60778, energy = 99.83335, acceleration = 19.59531, speed = 14.5217, energyUsage = 9.508913, rechargeRate = 4.955956,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 195.9011, armor = 190.4336, rate = 0.3411672, drain = 23.1761, maxDamage = 1473.524, shieldEfficiency = 0, minDamage = 723.5058, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 193.3382, armor = 194.2152, rate = 0.3371132, drain = 23.31378, maxDamage = 966.0139, shieldEfficiency = 0, minDamage = 597.9089, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_xwing_missile_s01", hitpoints = 19.89749, armor = 19.02803, rate = 5.740155, drain = 23.16122, maxDamage = 22.6369, shieldEfficiency = 0, minDamage = 22.91667, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 19.2737, armor = 19.12519, rate = 0.3286487, drain = 23.17929, maxDamage = 22.90508, shieldEfficiency = 0, minDamage = 23.23277, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	lots = 4,

	childObjects = {
		{ templateFile = "object/tangible/shipcontrol/shipcontrol_falcon.iff", x = 12.26, z = 0.14, y = 12.55, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/shipcontrol/shipoperations_falcon.iff", x = 13.56, z = 0.14, y = 12.55, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1, componentSlot = -2 },
		-- Escape Pod
		{ templateFile = "object/tangible/ship/interior_components/escape_pod_hatch.iff", x = 11.61, z = -0.59, y = 1.02, ox = 0, oy = 1, oz = 0, ow = 0, cellid = 1, containmentType = -1, componentSlot = -2 },
		-- Ship Permissions Terminal
		{ templateFile = "object/tangible/terminal/terminal_pob_ship.iff", x = -9.95, z = -1.67, y = 1.72, ox = 0, oy = 0.707106, oz = 0, ow = 0.707106, cellid = 4, containmentType = -1, componentSlot = -2 },
		-- Turret Control
		{ templateFile = "object/tangible/shipcontrol/turretcontrol_falcon.iff", x = -4.28, z = -0.303, y = 0.023, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 7, containmentType = -1, componentSlot = -2 },
		-- Hall 1
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 8.29, z = 2.06, y = 2.15, ox = 0.707106, oy = 0, oz = 0.707106, ow = 0, cellid = 1, containmentType = -1, componentSlot = -2 }, -- Upside down on ceilding
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 9.62, z = 1.65, y = 6.17, ox = 0.707106, oy = 0, oz = 0.7071061, ow = 0, cellid = 1, containmentType = -1, componentSlot = -2 }, -- Upside down on ceilding
		-- Cockpit
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 10.94, z = 0.52, y = 10.51, ox = 0, oy = 0.707106, oz = 0, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 14.86, z = 0.52, y = 10.62, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -1 },
		-- Lounge
		{ templateFile = "object/tangible/ship/interior_components/shield_generator_interior.iff", x = 2.48, z = -0.44, y = 11.7, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 3, containmentType = -1, componentSlot = 2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 3.33, z = -0.01, y = 2.84, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 3, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -1.25, z = 0.48, y = 3.52, ox = 0, oy = 0.707106, oz = 0.707106, ow = 0, cellid = 3, containmentType = -1, componentSlot = -2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -2.57, z = -1.03, y = 13.45, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 3, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -0.12, z = -1.03, y = 13.46, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 3, containmentType = -1, componentSlot = -1 },
		-- Hall 4
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -6.43, z = 1.63, y = -0.02, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 4, containmentType = -1, componentSlot = -1 },
		-- Storage 5
		{ templateFile = "object/tangible/ship/interior_components/engine_interior.iff", x = -8.64, z = -0.05, y = -9.85, ox = 0.000000, oy = 0.409834, oz = 0.000000, ow = 0.912159, cellid = 5, containmentType = -1, componentSlot = 1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -2.1, z = -0.34, y = -7.17, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 5, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -4.51, z = 1.26, y = -1.96, ox = -0.707106, oy = 0.036321, oz = 0.032809, ow = 0.707106, cellid = 5, containmentType = -1, componentSlot = -2 }, -- Faces south? on flat wall
		{ templateFile = "object/tangible/ship/interior_components/weapon_interior.iff", x = -4.48, z = 0.04, y = -2.04, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 5, containmentType = -1, componentSlot = 12 },
		{ templateFile = "object/tangible/ship/interior_components/weapon_interior.iff", x = -3.23, z = 0.04, y = -1.99, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 5, containmentType = -1, componentSlot = 13 },
		{ templateFile = "object/tangible/container/drum/pob_ship_loot_box.iff", x = -10.2, z = -1.7, y = -2.7, ox = 0, oy = 0.65, oz = 0, ow = 0.85, cellid = 5, containmentType = -1, componentSlot = -2 },
		-- Storage6
		{ templateFile = "object/tangible/ship/interior_components/reactor_interior.iff", x = 8.61, z = -0.24, y = -9.87, ox = 0.000000, oy = -0.409834, oz = 0.000000, ow = 0.912159, cellid = 6, containmentType = -1, componentSlot = 0 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 2.04, z = -0.4, y = -7.1, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 6, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/capacitor_interior.iff", x = 3.47, z = -0.15, y = -2.01, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 6, containmentType = -1, componentSlot = 6 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 3.51, z = 0.61, y = -2, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 6, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 10.73, z = 0.11, y = -7.75, ox = 0.640273, oy = -0.293599, oz = 0.291632, ow = 0.647147, cellid = 6, containmentType = -1, componentSlot = -2 }, -- Faces NW on flat wall
	},

	plasmaConduits = {
		-- Cockpit
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 10.94, z = 0.52, y = 10.51, ox = 0, oy = 0.707106, oz = 0, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 14.86, z = 0.52, y = 10.62, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
		-- Lounge
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 3.33, z = -0.01, y = 2.84, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 3, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -2.57, z = -1.03, y = 13.45, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 3, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -0.12, z = -1.03, y = 13.46, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 3, containmentType = -1, componentSlot = -1, componentDamageSlot = 2 }, -- Shield
		-- Hall 4
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -6.43, z = 1.63, y = -0.02, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 4, containmentType = -1, componentSlot = -1, componentDamageSlot = 6 }, -- Capacitor
		-- Storage 5
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -2.1, z = -0.34, y = -7.17, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 5, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		-- Storage6
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 2.04, z = -0.4, y = -7.1, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 6, containmentType = -1, componentSlot = -1, componentDamageSlot = 6 }, -- Capacitor
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 3.51, z = 0.61, y = -2, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 6, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
	},

	sparkLocations = {
		{cellName = "hall1",
			{x = 5.095, z = -1.6, y = 7.27},
			{x = 11.53, z = -0.8, y = 6.73},
			{x = 11.69, z = -1.6, y = 0.25},
			{x = 8.31, z = -1.6, y = 2.85},
			{x = 7.0, z = -1.6, y = 5.55},
			{x = 11.53, z = -1.6, y = 0.36},
		},
		{cellName = "cockpit",
			{x = 11.72, z = 0.14, y = 11.14},
			{x = 14.17, z = 0.14, y = 11.61},
			{x = 12.81, z = 0.14, y = 13.37},
			{x = 12.9, z = -0.3, y = 9.951},
		},
		{cellName = "lounge",
			{x = -2.88, z = -1.85, y = 7.67},
			{x = -1.62, z = -1.85, y = 4.25},
			{x = 2.78, z = -1.84, y = 4.26},
			{x = -0.070, z = -1.85, y = 11.25},
			{x = 0.52, z = -1.8, y = 8.48},
		},
		{cellName = "hall4",
			{x = -6.14, z = -1.6, y = 6.84},
			{x = -8.01, z = -1.6, y = 4.88},
			{x = -8.96, z = -1.6, y = -0.088},
			{x = -8.80, z = -1.6, y = 0.975},
			{x = -6.14, z = -1.6, y = 6.84},
		},
		{cellName = "storage5",
			{x = -7.64, z = -1.7, y = -1.96},
			{x = -9.09, z = -1.7, y = -4.60},
			{x = -4.37, z = -1.7, y = -9.76},
			{x = -2, z = -1.7, y = -3.38},
			{x = -8.2, z = -1.7, y = -6.53},
		},
		{cellName = "storage6",
			{x = 4.54, z = -1.7, y = -9.45},
			{x = 6.20, z = -1.7, y = 6.20},
			{x = 4.21, z = -1.7, y = -2.93},
			{x = 8.0, z = -1.7, y = -6.77},
		},
	},

	launchPoints = {
		{cellName = "hall1",
			{x = 12.25, z  = -1.6, y = 0},
			{x = 10.39, z  = -1.6, y = 0},
			{x = 8.3, z  = -1.6, y = 0},
		},
		{cellName = "cockpit",
			{x = 13.43, z  = 0.14, y = 12.88},
		},
		{cellName = "lounge",
			{x = 2.63, z  = -1.85, y = 9.01},
			{x = 2.15, z  = -1.85, y = 7.77},
			{x = 0.48, z  = -1.85, y = 7.83},
			{x = -1.19, z  = -1.85, y = 6.76},
			{x = -1.48, z  = -1.85, y = 9.67},
		},
		{cellName = "storage5",
			{x = -4.36, z  = -1.7, y = -4.78},
			{x = -6.96, z  = -1.7, y = -3.28},
			{x = -9.37, z  = -1.7, y = -4.52},
		},
		{cellName = "storage6",
			{x = 8.48, z  = -1.7, y = -2.17},
			{x = 3.51, z  = -1.7, y = -4.61},
			{x = 8.19, z  = -1.7, y = -6.55},
		},
	},
}

ObjectTemplates:addTemplate(object_ship_player_player_yt1300, "object/ship/player/player_yt1300.iff")
