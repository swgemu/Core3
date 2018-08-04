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


object_building_faction_perk_hq_hq_s02_rebel = object_building_faction_perk_hq_shared_hq_s02_rebel:new {
	lotSize = 0,
	faction = "rebel",
	pvpFaction = "rebel",
	maintenanceCost = 0,
	baseMaintenanceRate = 0,
	dataObjectComponent = "DestructibleBuildingDataComponent",
	zoneComponent = "StructureZoneComponent",
	allowedZones = {"dantooine", "naboo", "rori","tatooine", "corellia", "lok", "talus"},
	constructionMarker = "object/building/player/construction/construction_player_house_generic_medium_style_01.iff",
	length = 7,
	width = 6,
	containerComponent = "GCWBaseContainerComponent",
	factionBaseType = 1,

	skillMods = {
		{"private_medical_rating", 100},
		{"private_med_wound_health", 100},
		{"private_med_wound_action", 100},
	},

	childObjects = {
		{ templateFile = "object/static/structure/general/poi_all_rebl_corral_64x64_s01.iff", x = -0.22, z = 0, y = 15.49, ox = 0, oy = 0, oz = 0, ow = 1, cellid=-1, containmentType = -1 }, -- left column 1
		{ templateFile = "object/static/structure/general/tankfarm_s01.iff", x = -10.19, z = 0, y = -3.82, ox = 0, oy = 0.565, oz = 0, ow = 0.825, cellid=-1, containmentType = -1 }, -- left column 1

		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = 16.14, z = 0, y = 32.02, ox = 0, oy = 0, oz = 0, ow = 1, cellid=-1, containmentType = -1 }, -- left turret front
		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = -16.14, z = 0, y = 32.02, ox = 0, oy = 0, oz = 0, ow = 1, cellid=-1, containmentType = -1 },
		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = 18.17, z = 0, y = -2.43, ox = 0, oy = 1, oz = 0, ow = 0, cellid=-1, containmentType = -1 }, -- back turret left
		{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = -18.17, z = 0, y = -2.43, ox = 0, oy = 1, oz = 0, ow = 0, cellid=-1, containmentType = -1 },

		{ templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x = 0, z = 0, y = 39.5, ox = 0, oy = .7, oz = 0, ow = .7, cellid=-1, containmentType = -1 },

		{ templateFile = "object/tangible/terminal/terminal_mission_rebel.iff", x = 5, z = .25, y = -3, ow = -.7, ox = 0, oz = 0, oy = .7, cellid=3, containmentType = -1 },
		{ templateFile = "object/tangible/terminal/terminal_mission.iff", x = 5, z = .25, y = -4.75, ow = -.7, ox = 0, oz = 0, oy = .7, cellid=3, containmentType = -1 },

		{ templateFile = "object/tangible/terminal/terminal_bank.iff", x = -9, z = -6.66, y = -7, ow = .7, ox = 0, oz = 0, oy = .7, cellid=5, containmentType = -1 },

		{ templateFile = "object/tangible/terminal/terminal_hq_rebel.iff", x = .38, z = .25, y = 1.75, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },
		{ templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x =.375, z = -6.75, y =-8, ow = 1, ox =0, oz = 0, oy = .7, cellid = 5, containmentType = -1 },
		{ templateFile = "object/tangible/hq_destructible/security_terminal.iff", x =8, z =-6.75, y =-17.75, ox = 0, oy = 0, oz = 0, ow =1, cellid = 6, containmentType = -1 },
		{ templateFile = "object/tangible/hq_destructible/override_terminal.iff", x =2.75, z =-6.75, y = .25, ox = 0, oy = 1, oz =0, ow =0, cellid = 7, containmentType = -1 },
		{ templateFile = "object/tangible/hq_destructible/power_regulator.iff", x =-6.5, z =-13.75, y =-17, ox = 0, oy =0, oz = 0, ow =1, cellid =9, containmentType = -1 },
	},

	childCreatureObjects = {

		{ mobile="fbase_rebel_guard_captain", x = 5, z = 0, y = 18, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_grenadier", x = -5, z = 0, y = 18, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_grenadier", x = 0, z = 0, y = 53, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_guardsman", x = 2.5, z = 0, y = 50, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_soldier", x = -2.5, z = 0, y = 50, cellid=-1, respawn=360, containmentType = -1, heading = 0},

		{ mobile="fbase_rebel_rifleman", x = -28, z = 0, y = 0, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_rifleman", x = -33, z = 0, y = 0, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_squad_leader", x = -30.5, z = 0, y = 2.5, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_commando", x = -28, z = 0, y = 5, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_grenadier", x = -33, z = 0, y = 5, cellid=-1, respawn=360, containmentType = -1, heading = 0},

		{ mobile="fbase_rebel_heavy_trooper", x = 28, z = 0, y = 0, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_heavy_trooper", x = 33, z = 0, y = 0, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_liberator", x = 30.5, z = 0, y = 2.5, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_commando", x = 28, z = 0, y = 5, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_grenadier", x = 33, z = 0, y = 5, cellid=-1, respawn=360, containmentType = -1, heading = 0},

		{ mobile="fbase_rebel_heavy_trooper", x = -22, z = 0, y = 32, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_heavy_trooper", x = -27, z = 0, y = 32, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_guardsman", x = -24.5, z = 0, y = 34.5, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_commando", x = -22, z = 0, y = 37, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_corporal", x = -27, z = 0, y = 37, cellid=-1, respawn=360, containmentType = -1, heading = 0},

		{ mobile="fbase_rebel_heavy_trooper", x = 22, z = 0, y = 32, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_heavy_trooper", x = 27, z = 0, y = 32, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_squad_leader", x = 24.5, z = 0, y = 34.5, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_commando", x = 22, z = 0, y = 37, cellid=-1, respawn=360, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_rifleman", x = 27, z = 0, y = 37, cellid=-1, respawn=360, containmentType = -1, heading = 0},

		{ mobile="fbase_rebel_squad_leader", x = -3.5, z = 0, y = -3.9, cellid=2, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_cadet", x = 2.9, z = 0, y = -4.1, cellid=3, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_heavy_trooper", x = -1, z = -6.75, y = -6.5, cellid=5, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_commando", x = -4.5, z = -6.75, y = -3.4, cellid=5, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_cadet", x = -2.3, z = -6.75, y = -16.5, cellid=6, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_heavy_trooper", x = 7.2, z = -6.75, y = -14.5, cellid=6, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_commando", x = 2.5, z = -6.75, y = -16.5, cellid=6, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_heavy_trooper", x = 8, z = -6.75, y = -6, cellid=7, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_squad_leader", x = 3, z = -6.75, y = -1.8, cellid=7, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_guardsman", x = -5.5, z = -13.75, y = -3, cellid=9, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_medic_hard", x = .5, z = -13.75, y = -3 ,cellid=9, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_army_captain", x = .5, z = -13.75, y = -7.2, cellid=9, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_liberator", x = -5.5, z = -13.75, y = -7.2 ,cellid=9, respawn=300, containmentType = -1, heading = 0},
		{ mobile="fbase_rebel_colonel", x = -4.1, z = -13.75, y = -17.3 ,cellid=9, respawn=300, containmentType = -1, heading = 0},
		{ mobile="rebel_recruiter", x = 0, z = -13.75, y = -17, cellid=9, containmentType = -1, respawn=60, heading = 0},

	},

}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s02_rebel, "object/building/faction_perk/hq/hq_s02_rebel.iff")
