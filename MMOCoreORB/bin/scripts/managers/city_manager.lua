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


------------------------------
--  Global City Settings
------------------------------
CitySpecializationCooldown = 604800000 --Milliseconds: 1 Week = 604800000
TreasuryWithdrawalCooldown = 86400000 --Milliseconds: 1 Day = 86400000
CityVotingDuration = 1814400 --Seconds until the next vote occurs.
CityUpdateInterval = 30 --Minutes between city rank updates (60 = 1 hour, 1440 = 1 day, 10080 = 1 week)
NewCityGracePeriod = 60 --Minutes before a new city has to reach rank 1 citizens before it decays.

CitizensPerRank = {1, 5, 10, 15, 20}
--CitizensPerRank = {10, 20, 35, 55, 85}
RadiusPerRank = {150, 200, 300, 400, 450}

------------------------------
--  Cities Per Planet
------------------------------
--{rank1, rank2, rank3, rank4, rank5}
-- -1 = 255 cities which is the max amount
CitiesAllowed = {
	{"corellia", {20, 20, 15, 10, 10}},
	{"dantooine", {50, 50, 30, 20, 20}},
	{"dathomir", {0, 0, 0, 0, 0}},
	{"endor", {0, 0, 0, 0, 0}},
	{"lok", {50, 50, 30, 20, 20}},
	{"naboo", {20, 20, 15, 10, 10}},
	{"rori", {50, 50, 30, 20, 20}},
	{"talus", {50, 50, 30, 20, 20}},
	{"tatooine", {20, 20, 15, 10, 10}},
	{"yavin4", {0, 0, 0, 0, 0}}
}

CitySpecializations = {
	{"@city/city:city_spec_sample_rich", { --Sample Rich
		}
	},
	{"@city/city:city_spec_industry", { --Manufacturing Center
			{"advanced_assembly", 15},
			{"armor_assembly", 15},
			{"bio_engineer_assembly", 15},
			{"booster_assembly", 15},
			{"chassis_assembly", 15},
			{"clothing_assembly", 15},
			{"combat_medicine_assembly", 15},
			{"creature_assembly", 15},
			{"droid_assembly", 15},
			{"engine_assembly", 15},
			{"food_assembly", 15},
			{"force_assembly", 15},
			{"general_assembly", 15},
			{"grenade_assembly", 15},
			{"instrument_assembly", 15},
			{"jedi_saber_assembly", 15},
			{"medicine_assembly", 15},
			{"shields_assembly", 15},
			{"spice_assembly", 15},
			{"structure_assembly", 15},
			{"tissue_assembly", 15},
			{"weapon_assembly", 15}
		}
	},
	{"@city/city:city_spec_doctor", { --Medical Center
			{"private_medical_rating", 10}
		}
	},
	{"@city/city:city_spec_clone", { --Clone Lab
			{"private_medical_rating", 10}
		}
	},
	{"@city/city:city_spec_research", { --Research Center
			{"private_medical_rating", 10}
		}
	},
	{"@city/city:city_spec_missions", { --Improved Job Market
			{"private_medical_rating", 10}
		}
	},
	{"@city/city:city_spec_entertainer", { --Entertainment District
			{"private_medical_rating", 10}
		}
	},
	{"@city/city:city_spec_stronghold", { --Stronghold
			{"melee_defense", 50},
			{"ranged_defense", 50}
		}
	},
	{"@city/city:city_spec_master_healing", { --Scientific Society
			{"private_medical_rating", 10}
		}
	},
	{"@city/city:city_spec_master_manufacturing", { --Industrial Society
			{"advanced_assembly", 15},
			{"armor_assembly", 15},
			{"bio_engineer_assembly", 15},
			{"booster_assembly", 15},
			{"chassis_assembly", 15},
			{"clothing_assembly", 15},
			{"combat_medicine_assembly", 15},
			{"creature_assembly", 15},
			{"droid_assembly", 15},
			{"engine_assembly", 15},
			{"food_assembly", 15},
			{"force_assembly", 15},
			{"general_assembly", 15},
			{"grenade_assembly", 15},
			{"instrument_assembly", 15},
			{"jedi_saber_assembly", 15},
			{"medicine_assembly", 15},
			{"shields_assembly", 15},
			{"spice_assembly", 15},
			{"structure_assembly", 15},
			{"tissue_assembly", 15},
			{"weapon_assembly", 15}
		}
	},
}
