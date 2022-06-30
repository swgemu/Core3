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


object_building_faction_perk_hq_hq_s02_rebel_pvp = object_building_faction_perk_hq_shared_hq_s02_rebel_pvp:new {
	lotSize = 0,
	faction = "rebel",
	pvpFaction = "rebel",
	pvpStatusBitmask = OVERT,
	maintenanceCost = 0,
	baseMaintenanceRate = 0,
	dataObjectComponent = "DestructibleBuildingDataComponent",
	zoneComponent = "StructureZoneComponent",
	allowedZones = {"dantooine", "naboo", "rori","tatooine", "corellia", "lok", "talus"},
	constructionMarker = "object/building/player/construction/construction_player_house_generic_medium_style_01.iff",
	length = 7,
	width = 6,
	containerComponent = "GCWBaseContainerComponent",
	planetMapCategory = "rebel_hq",
	factionBaseType = 1,

	skillMods = {
		{"private_medical_rating", 100},
		{"private_med_wound_health", 100},
		{"private_med_wound_action", 100},
		--{"private_faction_medical_rating", 25},
	},

	childObjects = {
		{ templateFile = "object/static/structure/general/poi_all_rebl_corral_64x64_s01.iff", x = -0.22, z = 0, y = 15.49, ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1 },
		{ templateFile = "object/static/structure/general/tankfarm_s01.iff", x = -10.19, z = 0, y = -3.82, ox = 0, oy = 0.565, oz = 0, ow = 0.825, cellid = -1, containmentType = -1 },

		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = 16.14, z = 0, y = 32.02, ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1 },
		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = -16.14, z = 0, y = 32.02, ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1 },
		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = 18.17, z = 0, y = -2.43, ox = 0, oy = 1, oz = 0, ow = 0, cellid = -1, containmentType = -1 },
		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = -18.17, z = 0, y = -2.43, ox = 0, oy = 1, oz = 0, ow = 0, cellid = -1, containmentType = -1 },

		{ templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x = -2.75, z = 0, y = 1, ox = 0, oy = -0.707, oz = 0, ow = 0.707, cellid = 2, containmentType = -1 },
		{ templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x = -2.75, z = 0, y = 0, ox = 0, oy = -0.707, oz = 0, ow = 0.707, cellid = 2, containmentType = -1 },
		{ templateFile = "object/tangible/terminal/terminal_hq_turret_control.iff", x = -2.75, z = 0, y = -1, ox = 0, oy = -0.707, oz = 0, ow = 0.707, cellid = 2, containmentType = -1 },

		{ templateFile = "object/installation/faction_perk/covert_detector/detector_32m.iff", x = 0, z = 0, y = 48, ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1 },
		{ templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x = 0, z = 0, y = 39.5, ox = 0, oy = .7, oz = 0, ow = .7, cellid = -1, containmentType = -1 },

		{ templateFile = "object/tangible/terminal/terminal_hq_rebel.iff", x = 0, z = 0.25, y = 1.86, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },

		{ templateFile = "object/tangible/terminal/terminal_mission.iff", x = 0.25, z = -6.8, y = -6.45, ox = 0, oy = -0.707, oz = 0, ow = 0.707, cellid = 5, containmentType = -1 },
		{ templateFile = "object/tangible/terminal/terminal_mission_rebel.iff", x = -9.25, z = -6.8, y = -6.45, ox = 0, oy = 0.707, oz = 0, ow = 0.707, cellid = 5, containmentType = -1 },

		{ templateFile = "object/tangible/terminal/terminal_bank.iff", x = 9.13, z = -6.8, y = -6.98, ox = 0, oy = -0.707, oz = 0, ow = 0.707, cellid = 7, containmentType = -1 },
		{ templateFile = "object/tangible/terminal/terminal_bank.iff", x = 9.13, z = -6.8, y = -2.29, ox = 0, oy = -0.707, oz = 0, ow = 0.707, cellid = 7, containmentType = -1 },

		-- Base Alarms
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack.iff", x = -3.69, z = 3.75, y = 3.19, ow = -0.011, ox = 0.99, oy = 0.017, oz = 0.002550, cellid = 2, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack.iff", x = -4.5, z = -8.3, y = -1.7, ow = 0, ox = 0, oy = 0, oz = 1, cellid = 5, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack.iff", x = -8.2, z = -2.0, y = -15, ow = 0, ox = 0, oy = 0, oz = 1, cellid = 6, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack.iff", x = 5.5, z = -0.9, y = -1.7, ow = 0, ox = 0, oy = 0, oz = 1, cellid = 7, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack.iff", x = -2.49, z = -13.64, y = -8.72, ow = -0.01, ox = -0.01, oy = 0.994, oz = -0.028, cellid = 9, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack_no_sound.iff", x = -3.7, z = 3.75, y = -4.7, ow = 0, ox = 0, oy = 0, oz = 1, cellid = 2, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack_no_sound.iff", x = 3.5, z = -5.3, y = 4.1, ow = 0, ox = 0, oy = 0, oz = 1, cellid = 3, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack_no_sound.iff", x = -4.49, z = -1.66, y = -2.44, ow = -0.009, ox = 0.009, oy = -0.009, oz = 1, cellid = 5, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack_no_sound.iff", x = 0.2, z = -1.8, y = -15, ow = 0, ox = 0, oy = 0, oz = 1, cellid = 6, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack_no_sound.iff", x = 5.5, z = -1.8, y = -1.7, ow = 0, ox = 0, oy = 0, oz = 1, cellid = 7, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_hack_no_sound.iff", x = -2.49, z = -13.64, y = -8.72, ow = -0.01, ox = -0.01, oy = 0.994, oz = -0.028, cellid = 9, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_destruct.iff", x = 1.3245, z = 2.882, y = 3.227, ow = 0.728, ox = -0.005, oy = -0.005, oz = 0.686, cellid = 2, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_destruct_no_sound.iff", x = -5.2, z = 3.4, y = 0.8, ow = 0.005, ox = 0.707, oy = 0.707, oz = 0.005, cellid = 2, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_destruct_no_sound.iff", x = -0.3, z = 3.3, y = -5.5, ow = -0.010, ox = 0.009, oy = 0.716, oz = 0.700, cellid = 3, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_destruct_no_sound.iff", x = -0.5, z = -3.51, y = -3.09, ow = -0.510, ox = 0.504, oy = -0.500, oz = -0.500, cellid = 5, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_destruct_no_sound.iff", x = 0.818, z = -3.44, y = -11.834, ow = -0.028, ox = -0.042, oy = 0.718, oz = -0.694, cellid = 6, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_destruct_no_sound.iff", x = 1.488, z = -3.47, y = -3.09, ow = 0.508, ox = 0.495, oy = 0.5001, oz = -0.495, cellid = 7, containmentType = -1 },
		{ templateFile = "object/tangible/faction_perk/faction_base_item/alarm_destruct_no_sound.iff", x = -2.44, z = -9.15, y = 3.502, ow = 0.0003, ox = 0.014, oy = -0.704, oz = 0.710, cellid = 9, containmentType = -1 },
	},

	childCreatureObjects = {

		{ mobile = "fbase_rebel_command_security_guard_hard", x = -3.5, z = 0, y = -3.9, cellid = 2, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_sharpshooter_hard", x = 2.9, z = 0, y = -4.1, cellid = 3, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_sharpshooter_hard", x = -1, z = -6.75, y = -6.5, cellid = 5, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_recruit_hard", x = -4.5, z = -6.75, y = -3.4, cellid = 5, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_medic_hard", x = -2.3, z = -6.75, y = -16.5, cellid = 6, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_comm_operator_hard", x = 7.2, z = -6.75, y = -14.5, cellid = 6, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_corporal_hard", x = 2.5, z = -6.75, y = -16.5, cellid = 6, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_command_security_guard_hard", x = 8, z = -6.75, y = -6, cellid = 7, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_sergeant_hard", x = 3, z = -6.75, y = -1.8, cellid = 7, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_sharpshooter_hard", x = -5.5, z = -13.75, y = -3, cellid = 9, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_command_security_guard_hard", x = .5, z = -13.75, y = -3 ,cellid = 9, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_warrant_officer_ii_hard", x = .5, z = -13.75, y = -7.2, cellid = 9, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_master_sergeant_hard", x = -5.5, z = -13.75, y = -7.2, cellid = 9, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "fbase_rebel_first_lieutenant_hard", x = -4.1, z = -13.75, y = -17.3, cellid = 9, respawn = 300, containmentType = -1, heading = 0},
		{ mobile = "rebel_recruiter", x = 0, z = -13.75, y = -17, cellid = 9, respawn = 60, containmentType = -1, heading = 0},
	},

	securityPatrols = {
		{patrol = "rebel_small_2", x = -19.8, z = 0, y = 32.5, heading = 0},
		{patrol = "rebel_small_2", x = 23.8, z = 0, y = 32.5, heading = 0},
		{patrol = "rebel_small_2", x = -23.8, z = 0, y = -9.8, heading = 0},
		{patrol = "rebel_small_2", x = 19.8, z = 0, y = -9.8, heading = 0},

		{patrol = "rebel_large_2", x = 0, z = 0, y = 18.1, heading = 0},
		{patrol = "rebel_large_2", x = 0, z = 0, y = 51.2, heading = 0},
		{patrol = "rebel_large_2", x = 0, z = 0, y = -19.5, heading = 0},
	},
}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s02_rebel_pvp, "object/building/faction_perk/hq/hq_s02_rebel_pvp.iff")
