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


object_ship_player_player_ykl37r = object_ship_player_shared_player_ykl37r:new {
	name = "player_ykl37r",
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

	reactor = { name = "rct_generic", hitpoints = 393.4749, armor = 392.1788,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.38634, armor = 97.26779, speed = 64.8352, pitch = 53.1233, roll = 51.811, yaw = 20.72012, acceleration = 14.20368, rollRate = 81.44453, pitchRate = 74.89443, deceleration = 13.23707, yawRate = 36.14846,},
	shield_0 = { name = "shd_generic", hitpoints = 399.6198, armor = 488.0886, regen = 2.93632, front = 1559.694, back = 1589.634,},
	armor_0 = { name = "arm_generic", hitpoints = 1092.445, armor = 1065.585,},
	armor_1 = { name = "arm_generic", hitpoints = 1064.248, armor = 1095.966,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.55407, energy = 1101.659,},
	booster = { name = "bst_generic", hitpoints = 19.30068, armor = 19.50534, energy = 96.55447, acceleration = 19.0435, speed = 14.3576, energyUsage = 9.907719, rechargeRate = 4.798415,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 191.7337, armor = 198.4741, rate = 0.3354505, drain = 23.31645, maxDamage = 1452.662, shieldEfficiency = 0, minDamage = 727.0751, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.7502, armor = 193.4968, rate = 0.3280407, drain = 22.70662, maxDamage = 965.8762, shieldEfficiency = 0, minDamage = 601.3749, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_xwing_missile_s01", hitpoints = 19.53581, armor = 19.31941, rate = 5.815926, drain = 23.09743, maxDamage = 22.9824, shieldEfficiency = 0, minDamage = 23.42325, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 247.8035, armor = 245.5052, rate = 0.09767031, drain = 23.58665, maxDamage = 98.10107, shieldEfficiency = 0, minDamage = 24.81069, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
	lots = 4,

	childObjects = {
		{ templateFile = "object/tangible/shipcontrol/shipcontrol_falcon.iff", x = -17.94, z = -1.87, y = 3.53, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 1, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/shipcontrol/shipoperations_falcon.iff", x = -16.26, z = -1.87, y = 3.62, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 1, containmentType = -1, componentSlot = -2 },
		-- Escape Pod
		{ templateFile = "object/tangible/ship/interior_components/escape_pod_hatch.iff", x = -19.39, z = -1.18, y = -3.96, ox = 0, oy = 0.707106, oz = 0, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -2 },
		-- Ship Permissions Terminal
		{ templateFile = "object/tangible/terminal/terminal_pob_ship.iff", x = 6.22, z = -0.5, y = 16.98, ox = 0, oy = -0.707106, oz = 0, ow = 0.707106, cellid = 9, containmentType = -1, componentSlot = -2 },
		-- Turret Control
		{ templateFile = "object/tangible/shipcontrol/turretcontrol_falcon.iff", x = -0.02, z = 0.28, y = -0.22, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 10, containmentType = -1, componentSlot = -2 },
		-- Cockpit
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -18.48, z = -0.74, y = 0.6, ox = 0.000000, oy = 0.000000, oz = -0.707107, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1},
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -15.79, z = -0.74, y = 0.55, ox = 0.000000, oy = 0.000000, oz = -0.707107, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1 },
		-- Airlock
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -17.19, z = 0.45, y = -0.28, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 2, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/capacitor_interior.iff", x = -15.42, z = -1.18, y = -7.27, ox = 0.000000, oy = -0.707106, oz = 0.000000, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = 6 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -18.88, z = -1.15, y = -7.24, ox = 0.000000, oy = 0.707106, oz = 0.000000, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -1 },
		-- Hallmid
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 1.18, z = -0.36, y = -5.29, ox = 0.000000, oy = 0.000000, oz = 0.707107, ow = 0.707107, cellid = 4, containmentType = -1, componentSlot = -2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -1.92, z = -0.41, y = -2.64, ox = 0.000000, oy = 1.000000, oz = 0.000000, ow = 0.000000, cellid = 4, containmentType = -1, componentSlot = -1 },
		-- Hallsb
		{ templateFile = "object/tangible/ship/interior_components/shield_generator_interior.iff", x = 13.86, z = -1.98, y = -4.89, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 5, containmentType = -1, componentSlot = 2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 13.7, z = -0.91, y = -5.14, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 5, containmentType = -1, componentSlot = -1 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 15.6, z = 0.18, y = -3.9, ox = 0.000000, oy = 0.000000, oz = 0.707107, ow = 0.707107, cellid = 5, containmentType = -1, componentSlot = -2 },
		-- Engineering
		{ templateFile = "object/tangible/ship/interior_components/engine_interior.iff", x = 2.95, z = -0.44, y = -5.47, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 6, containmentType = -1, componentSlot = 1 },
		{ templateFile = "object/tangible/ship/interior_components/reactor_interior.iff", x = -3.03, z = -0.44, y = -5.47, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 6, containmentType = -1, componentSlot = 0 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -0.01, z = 1.03, y = -9.9, ox = 0.845235, oy = 0.000000, oz = 0.000000, ow = 0.534396, cellid = 6, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -0.01, z = -1.53, y = -9.93, ox = 0.534396, oy = 0.000000, oz = 0.000000, ow = 0.845235, cellid = 6, containmentType = -1, componentSlot = -2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -5.23, z = -0.47, y = -8.35, ox = 0.000000, oy = 0.707106, oz = 0.000000, ow = 0.707106, cellid = 6, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 5.23, z = -0.57, y = -8.3, ox = 0.000000, oy = -0.707106, oz = 0.000000, ow = 0.707106, cellid = 6, containmentType = -1, componentSlot = -1 },
		-- Hallfore
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -2.99, z = -0.33, y = -2.24, ox = 0.000000, oy = 0.000000, oz = 0.707107, ow = 0.707107, cellid = 7, containmentType = -1, componentSlot = -2 },
		-- Storage
		{ templateFile = "object/tangible/ship/interior_components/weapon_interior.iff", x = 6.5, z = 0.5, y = 7.9, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 8, containmentType = -1, componentSlot = 12 },
		{ templateFile = "object/tangible/ship/interior_components/weapon_interior.iff", x = 6.45, z = 0.5, y = 3.68, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 8, containmentType = -1, componentSlot = 13 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 6.5, z = 0.46, y = 5.9, ox = 0.000000, oy = 0.000000, oz = 0.707107, ow = 0.707107, cellid = 8, containmentType = -1, componentSlot = -2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 6.43, z = -0.13, y = 5.26, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 8, containmentType = -1, componentSlot = -1 },
		-- Cabin
		{ templateFile = "object/tangible/container/drum/pob_ship_loot_box.iff", x = 0.1, z = -0.5, y = 10.6, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 9, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = -2.58, z = 2.75, y = 16.36, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 9, containmentType = -1, componentSlot = -2 },
		{ templateFile = "object/tangible/ship/interior_components/alarm_interior.iff", x = 2.85, z = 2.71, y = 16.44, ox = 1, oy = 0, oz = 0, ow = 0, cellid = 9, containmentType = -1, componentSlot = -2 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -1.85, z = 0.73, y = 10.26, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 9, containmentType = -1, componentSlot = -1 },
		--{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 1.98, z = 0.73, y = 10.31, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 9, containmentType = -1, componentSlot = -1 },
	},

	plasmaConduits = {
		-- Cockpit
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -18.48, z = -0.74, y = 0.6, ox = 0.000000, oy = 0.000000, oz = -0.707107, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -15.79, z = -0.74, y = 0.55, ox = 0.000000, oy = 0.000000, oz = -0.707107, ow = 0.707107, cellid = 1, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		-- Airlock
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -18.88, z = -1.15, y = -7.24, ox = 0.000000, oy = 0.707106, oz = 0.000000, ow = 0.707106, cellid = 2, containmentType = -1, componentSlot = -1, componentDamageSlot = 6 }, -- Capacitor
		-- Hallmid
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -1.92, z = -0.41, y = -2.64, ox = 0.000000, oy = 1.000000, oz = 0.000000, ow = 0.000000, cellid = 4, containmentType = -1, componentSlot = -1, componentDamageSlot = 6 }, -- Capacitor
		-- Hallsb
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 13.7, z = -0.91, y = -5.14, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 5, containmentType = -1, componentSlot = -1, componentDamageSlot = 2 }, -- Shield
		-- Engineering
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -5.23, z = -0.47, y = -8.35, ox = 0.000000, oy = 0.707106, oz = 0.000000, ow = 0.707106, cellid = 6, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 5.23, z = -0.57, y = -8.3, ox = 0.000000, oy = -0.707106, oz = 0.000000, ow = 0.707106, cellid = 6, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		-- Storage
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 6.43, z = -0.13, y = 5.26, ox = 0.000000, oy = -0.707107, oz = 0.000000, ow = 0.707107, cellid = 8, containmentType = -1, componentSlot = -1, componentDamageSlot = 6 }, -- Capacitor
		-- Cabin
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = -1.85, z = 0.73, y = 10.26, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 9, containmentType = -1, componentSlot = -1, componentDamageSlot = 1 }, -- Engine
		{ templateFile = "object/tangible/ship/interior_components/plasma_conduit_interior.iff", x = 1.98, z = 0.73, y = 10.31, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 9, containmentType = -1, componentSlot = -1, componentDamageSlot = 0 }, -- Reactor
	},

	sparkLocations = {
		{cellName = "cockpit",
			{x = -17.94, z = -1.87, y = 3.53},
			{x = -16.26, z = -1.87, y = 3.62},
		},
		{cellName = "airlock",
			{x = -15.79, z = -0.74, y = 0.55},
		},
		{cellName = "hallport",
			{x = -15.42, z = -1.18, y = -7.27},
			{x = -18.88, z = -1.15, y = -7.24},
		},
		{cellName = "hallmid",
			{x = -8.07, z = -1.91, y = -3.58},
		},
		{cellName = "hallsb",
			{x = 1.18, z = -0.36, y = -5.29},
			{x = -1.92, z = -0.41, y = -2.64},
		},
		{cellName = "engineering",
			{x = 13.7, z = -0.91, y = -5.14},
			{x = 15.6, z = 0.18, y = -3.9},
		},
		{cellName = "hallfore",
			{x = -5.23, z = -0.47, y = -8.35},
			{x = 5.23, z = -0.57, y = -8.3},
		},
		{cellName = "storage",
			{x = -3.84, z = -1.02, y = 8.79},
			{x = -2.99, z = -0.33, y = -2.24},
		},
		{cellName = "cabin",
			{x = 6.43, z = -0.13, y = 5.26},
			{x = 0.1, z = -0.5, y = 10.6},
			{x = -0.5, z = -0.5, y = 20.49},
		},
	},

	launchPoints = {
		{cellName = "cockpit",
			{x = -17.1, z  = -1.9, y = -13.0},
		},
	},
}

ObjectTemplates:addTemplate(object_ship_player_player_ykl37r, "object/ship/player/player_ykl37r.iff")
