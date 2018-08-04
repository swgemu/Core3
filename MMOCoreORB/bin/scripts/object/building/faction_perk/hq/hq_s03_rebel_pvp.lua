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


object_building_faction_perk_hq_hq_s03_rebel_pvp = object_building_faction_perk_hq_shared_hq_s03_rebel_pvp:new {

		lotSize = 0,
		containerComponent = "GCWBaseContainerComponent",
		zoneComponent = "StructureZoneComponent",
		maintenanceCost = 0,
		baseMaintenanceRate = 0,
		faction = "rebel",
		pvpFaction = "rebel",
		pvpStatusBitmask = OVERT,
		dataObjectComponent = "DestructibleBuildingDataComponent",
		allowedZones = {"dantooine", "naboo", "rori","tatooine", "corellia", "lok", "talus"},
		constructionMarker = "object/building/player/construction/construction_player_house_generic_medium_style_01.iff",
		length = 7,
		width = 6,
		planetMapCategory = "rebel_hq",
		alwaysPublic = 1,
		factionBaseType = 1,

		skillMods = {
			{"private_buff_mind", 100},
			{"private_faction_buff_mind", 25},
			{"private_med_battle_fatigue", 5},
			{"private_faction_mind_heal", 10},
			{"private_medical_rating", 100},
			{"private_faction_medical_rating", 25},
		},

		childObjects = {
			{ templateFile = "object/static/structure/general/poi_all_rebl_corral_64x64_s01.iff", x = 0.28, z = 0, y = 7.35, ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1 },
			{ templateFile = "object/static/structure/general/tankfarm_s01.iff", x = 10.04, z = 0, y = -12, ox = 0, oy = -0.579, oz = 0, ow = 0.815, cellid = -1, containmentType = -1 },
			{ templateFile = "object/static/structure/general/tankfarm_s01.iff", x = -9.27, z = 0, y = -11.87, ox = 0, oy = 0.565, oz = 0, ow = 0.825, cellid = -1, containmentType = -1 },

			{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = 16.14, z = 0, y = 32.02, ox = 0, oy = 0,  oz = 0, ow = 1, cellid = -1, containmentType = -1 },
			{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = -16.14, z = 0, y = 32.02,  ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1 },
			{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = 18.17, z = 0, y = -2.43, ox = 0, oy = 1,  oz = 0, ow = 0, cellid = -1, containmentType = -1 },
			{ templateFile = "object/installation/faction_perk/turret/tower_lg.iff", x = -18.17, z = 0, y = -2.43,  ox = 0, oy = 1, oz = 0, ow = 0, cellid = -1, containmentType = -1 },

			{ templateFile = "object/installation/faction_perk/minefield/field_1x1.iff", x = 0, z = 0, y = 31.7,  ox = 0, oy = 0, oz = 0, ow = 1, cellid = -1, containmentType = -1 },

			{ templateFile = "object/tangible/terminal/terminal_hq_rebel.iff", x = .38, z = .25, y = 1.75, ox = 0, oy = 0, oz = 0, ow = 1, cellid = 2, containmentType = -1 },

			{ templateFile = "object/tangible/hq_destructible/uplink_terminal.iff", x =5, z =.25, y =-4, ow =-.662, ox =0, oz = 0, oy =.749, cellid = 3, containmentType = -1 },
			{ templateFile = "object/tangible/hq_destructible/security_terminal.iff", x =-5, z =-13.75, y =4.5, ox = 0, oy =.076, oz = 0, ow =1, cellid = 7, containmentType = -1 },
			{ templateFile = "object/tangible/hq_destructible/override_terminal.iff", x =3, z =-20.75, y = 1.5,  ox = 0, oy = 0, oz = 0, ow = 1, cellid = 9, containmentType = -1 },
			{ templateFile = "object/tangible/hq_destructible/power_regulator.iff", x = 4.25, z =-20.75, y =36, ox = 0, oy =1, oz = 0, ow =0, cellid = 10, containmentType = -1 },

			{ templateFile = "object/tangible/terminal/terminal_mission.iff", x = -11, z = -13.75, y = 7, ow = .7, ox = 0, oz = 0, oy = .7, cellid = 7, containmentType = -1 },
			{ templateFile = "object/tangible/terminal/terminal_bank.iff", x = 6, z = -13.75, y = 10, ow = 0, ox = 0, oz = 0, oy = 1, cellid = 7, containmentType = -1 },
			{ templateFile = "object/tangible/terminal/terminal_insurance.iff", x = -9, z = -13.75, y = 10, ow = 0, ox = 0, oz = 0, oy = 1, cellid = 7, containmentType = -1 },
			{ templateFile = "object/tangible/terminal/terminal_mission_rebel.iff", x = 8, z = -13.75, y = 7, ow = -.7, ox = 0, oz = 0, oy = .7, cellid = 7, containmentType = -1 },
		},

		childCreatureObjects = {
			{ mobile="fbase_rebel_rifleman_hard", x=-4.5, z=0, y=-2, cellid=2, respawn=300, containmentType=-1, heading=4.71},
			{ mobile="fbase_rebel_grenadier_hard", x=-4.5, z=0, y=0.9, cellid=2, respawn=300, containmentType=-1, heading=4.71},

			{ mobile="fbase_rebel_guardsman_hard", x=4, z=-3.25, y=5, cellid=4, respawn=300, containmentType=-1, heading=3.14},

			{ mobile="fbase_rebel_squad_leader_hard", x=-5, z=-10.25, y=-6, cellid=5, respawn=300, containmentType=-1, heading=0},

			{ mobile="fbase_rebel_liberator_hard", x=-2.7, z=-13.75, y=7, cellid=7, respawn=300, containmentType=-1, heading=1.57},
			{ mobile="fbase_rebel_soldier_hard", x=-5, z=-13.75, y=7, cellid=7, respawn=300, containmentType=-1, heading=1.57},

			{ mobile="fbase_rebel_army_captain_hard", x=-1.85, z=-20.75, y=5.1, cellid=9, respawn=300, containmentType=-1, heading=4.71},
			{ mobile="fbase_rebel_guard_captain_hard", x=4.6, z=-20.75, y=5.1, cellid=9, respawn=300, containmentType=-1, heading=1.57},

			{ mobile="fbase_rebel_cadet_hard", x=-1, z=-20.75, y=16, cellid=10, containmentType=-1, respawn=300, heading=1.57},
			{ mobile="fbase_rebel_heavy_trooper_hard", x=-3.5, z=-20.75, y=23, cellid=10, containmentType=-1, respawn=300, heading=1.57},
			{ mobile="fbase_rebel_heavy_trooper_hard", x=5, z=-20.75, y=16, cellid=10, containmentType=-1, respawn=300, heading=4.71},
			{ mobile="fbase_rebel_heavy_trooper_hard", x=6.5, z=-20.75, y=23, cellid=10, containmentType=-1, respawn=300, heading=4.71},
			{ mobile="fbase_rebel_commando_hard", x=2.6, z=-20.75, y=29.9, cellid=10, containmentType=-1, respawn=300, heading=3.14},
			{ mobile="fbase_rebel_guard_captain_hard", x=5.8, z=-20.75, y=29.9, cellid=10, containmentType=-1, respawn=300, heading=4.71},
			{ mobile="fbase_rebel_colonel_hard", x=5.5, z=-20.75, y=35, cellid=10, containmentType=-1, respawn=600, heading=3.14},
			{ mobile="rebel_recruiter", x=-2, z=-20.75, y=34, cellid=10, containmentType=-1, respawn=60, heading=3.14},
		},
}

ObjectTemplates:addTemplate(object_building_faction_perk_hq_hq_s03_rebel_pvp, "object/building/faction_perk/hq/hq_s03_rebel_pvp.iff")
