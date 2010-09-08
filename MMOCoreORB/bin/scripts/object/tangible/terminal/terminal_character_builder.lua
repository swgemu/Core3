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
--
--NOTES ABOUT CHARACTER BUILDER TERMINAL ITEM LIST FORMAT
---------------------------------------------------------
--The item list is an infinitely deep node tree system.
--To create a sub menu, use the following format:
--"Name of the sub menu", {Menu items contained in brackets}
--To create an item that is selectable, use the following format (within brackets of a submenu):
--"Name of the item", "Path to the server or client template."
--Be sure to pay attention to commas.

object_tangible_terminal_terminal_character_builder = object_tangible_terminal_shared_terminal_character_builder:new {
	gameObjectType = 16400,
			
	maxCondition = 0,
	
	performanceBuff = 500,
	
	medicalBuff = 1000,
	
	-- Duration in seconds
	performanceDuration = 1800,
	
	-- Duration in seconds
	medicalDuration = 1800,
	
	templateType = CHARACTERBUILDERTERMINAL,

	itemList = {
		"Character Options",
		{
			"Learn Skill",
			{
				"Architect",
				{
					"Novice", "crafting_architect_novice",
					"Furniture",
					{
						"Furniture I", "crafting_architect_production_01",
						"Furniture II", "crafting_architect_production_02",
						"Furniture III", "crafting_architect_production_03",
						"Furniture IV", "crafting_architect_production_04"
					},
					"Construction",
					{
						"Construction I", "crafting_architect_techniques_01",
						"Construction II", "crafting_architect_techniques_02",
						"Construction III", "crafting_architect_techniques_03",
						"Construction IV", "crafting_architect_techniques_04"
					},
					"Installations",
					{
						"Installations I", "crafting_architect_harvesting_01",
						"Installations II", "crafting_architect_harvesting_02",
						"Installations III", "crafting_architect_harvesting_03",
						"Installations IV", "crafting_architect_harvesting_04"
					},
					"Buildings",
					{
						"Buildings I", "crafting_architect_blueprints_01",
						"Buildings II", "crafting_architect_blueprints_02",
						"Buildings III", "crafting_architect_blueprints_03",
						"Buildings IV", "crafting_architect_blueprints_04"
					},
					"Master", "crafting_architect_master"
				},
				"Armorsmith",
				{
					"Novice", "crafting_armorsmith_novice",
					"Personal Armor",
					{
						"Personal Armor I", "crafting_armorsmith_personal_01",
						"Personal Armor II", "crafting_armorsmith_personal_02",
						"Personal Armor III", "crafting_armorsmith_personal_03",
						"Personal Armor IV", "crafting_armorsmith_personal_04"
					},
					"Layers",
					{
						"Layers I", "crafting_armorsmith_heavy_01",
						"Layers II", "crafting_armorsmith_heavy_02",
						"Layers III", "crafting_armorsmith_heavy_03",
						"Layers IV", "crafting_armorsmith_heavy_04"
					},
					"Deflectors",
					{
						"Deflectors I", "crafting_armorsmith_deflectors_01",
						"Deflectors II", "crafting_armorsmith_deflectors_02",
						"Deflectors III", "crafting_armorsmith_deflectors_03",
						"Deflectors IV", "crafting_armorsmith_deflectors_04"
					},
					"Technique",
					{
						"Technique I", "crafting_armorsmith_complexity_01",
						"Technique II", "crafting_armorsmith_complexity_02",
						"Technique III", "crafting_armorsmith_complexity_03",
						"Technique IV", "crafting_armorsmith_complexity_04"
					},
					"Master", "crafting_armorsmith_master"
				},
				"Artisan",
				{
					"Novice", "crafting_artisan_novice",
					"Engineering",
					{
						"Engineering I", "crafting_artisan_engineering_01",
						"Engineering II", "crafting_artisan_engineering_02",
						"Engineering III", "crafting_artisan_engineering_03",
						"Engineering IV", "crafting_artisan_engineering_04"
					},
					"Domestic Arts",
					{
						"Domestic Arts I", "crafting_artisan_domestic_01",
						"Domestic Arts II", "crafting_artisan_domestic_02",
						"Domestic Arts III", "crafting_artisan_domestic_03",
						"Domestic Arts IV", "crafting_artisan_domestic_04"
					},
					"Business",
					{
						"Business I", "crafting_artisan_business_01",
						"Business II", "crafting_artisan_business_02",
						"Business III", "crafting_artisan_business_03",
						"Business IV", "crafting_artisan_business_04"
					},
					"Surveying",
					{
						"Surveying I", "crafting_artisan_survey_01",
						"Surveying II", "crafting_artisan_survey_02",
						"Surveying III", "crafting_artisan_survey_03",
						"Surveying IV", "crafting_artisan_survey_04"
					},
					"Master", "crafting_artisan_master"
				},
				"Bio-Engineer",
				{
					"Master", "outdoors_bio_engineer_master"
				},
				"Bounty Hunter",
				{
					"Master", "combat_bountyhunter_master"
				},
				"Brawler",
				{
					"Master", "combat_brawler_master"
				},
				"Carbineer",
				{
					"Master", "combat_carbine_master"
				},
				"Chef",
				{
					"Master", "crafting_chef_master"
				},
				"Combat Medic",
				{
					"Master", "science_combatmedic_master"
				},
				"Commando",
				{
					"Master", "combat_commando_master"
				},
				--"Creature Handler",
				--{
					--"Master", "outdoors_creaturehandler_master"
				--},
				"Dancer",
				{
					"Master", "social_dancer_master"
				},
				"Doctor",
				{
					"Master", "science_doctor_master"
				},
				--"Droid Engineer",
				--{
					--"Master", "crafting_droidengineer_master"
				--},
				"Entertainer",
				{
					"Master", "social_entertainer_master"
				},
				"Fencer",
				{
					"Master", "combat_1hsword_master"
				},
				--"Force Sensitive",
				--{
				--},
				"Image Designer",
				{
					"Master", "social_imagedesigner_master"
				},
				--"Jedi",
				--{
				--},
				"Marksman",
				{
					"Master", "combat_marksman_master"
				},
				"Medic",
				{
					"Master", "science_medic_master"
				},
				"Merchant",
				{
					"Master", "crafting_merchant_master"
				},
				"Musician",
				{
					"Master", "social_musician_master"
				},
				"Pikeman",
				{
					"Master", "combat_polearm_master"
				},
				--"Pilot",
				--{
				--},
				"Pistoleer",
				{
					"Master", "combat_pistol_master"
				},
				"Politician",
				{
					"Master", "social_politician_master"
				},
				"Ranger",
				{
					"Master", "outdoors_ranger_master"
				},
				"Rifleman",
				{
					"Master", "combat_rifleman_master"
				},
				"Scout",
				{
					"Master", "outdoors_scout_master"
				},
				--"Shipwright",
				--{
				--},
				"Smuggler",
				{
					"Master", "combat_smuggler_master"
				},
				"Squad Leader",
				{
					"Master", "outdoors_squadleader_master"
				},
				"Swordsman",
				{
					"Master", "combat_2hsword_master"
				},
				"Tailor",
				{
					"Master", "crafting_tailor_master"
				},
				"Teras Kasi Artist",
				{
					"Master", "combat_unarmed_master"
				},
				"Weaponsmith",
				{
					"Master", "crafting_weaponsmith_master"
				}
			},
			"Unlearn All Skills", "unlearn_all_skills",
			"Cleanse Character", "cleanse_character",
			"Enhance Character", "enhance_character"
		},
		"Items",
		{
			"Armor",
			{
				"Bone Armor",
				{
					"Bone Left Bicep", "object/tangible/wearables/armor/bone/armor_bone_s01_bicep_l.iff",
					"Bone Right Bicep", "object/tangible/wearables/armor/bone/armor_bone_s01_bicep_r.iff",
					"Bone Boots", "object/tangible/wearables/armor/bone/armor_bone_s01_boots.iff",
					"Bone Left Bracer", "object/tangible/wearables/armor/composite/armor_composite_bracer_l.iff",
					"Bone Right Bracer", "object/tangible/wearables/armor/bone/armor_bone_s01_bracer_r.iff",
					"Bone Chest Plate", "object/tangible/wearables/armor/bone/armor_bone_s01_chest_plate.iff",
					"Bone Gloves", "object/tangible/wearables/armor/bone/armor_bone_s01_gloves.iff",
					"Bone Helmet", "object/tangible/wearables/armor/bone/armor_bone_s01_helmet.iff",
					"Bone Leggings", "object/tangible/wearables/armor/bone/armor_bone_s01_leggings.iff",
					"Singing Mountain Clan Bicep", "object/tangible/wearables/armor/bone/armor_smc_s01_bicep_l.iff"
				},
				"Bounty Hunter Armor",
				{
					"Bounty Hunter Belt", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_belt.iff",
					"Bounty Hunter Left Bicep", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bicep_l.iff",
					"Bounty Hunter Right Bicep", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bicep_r.iff",
					"Bounty Hunter Boots", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_boots.iff",
					"Bounty Hunter Left Bracer", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bracer_l.iff",
					"Bounty Hunter Right Bracer", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_bracer_r.iff",
					"Bounty Hunter Chest Plate", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_chest_plate.iff",
					"Bounty Hunter Gloves", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_gloves.iff",
					"Bounty Hunter Helmet", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_helmet.iff",
					"Bounty Hunter Leggings", "object/tangible/wearables/armor/bounty_hunter/armor_bounty_hunter_leggings.iff"
				},
				"Chitin Armor",
				{
					"Chitin Left Bicep", "object/tangible/wearables/armor/chitin/armor_chitin_s01_bicep_l.iff",
					"Chitin Right Bicep", "object/tangible/wearables/armor/chitin/armor_chitin_s01_bicep_r.iff",
					"Chitin Boots", "object/tangible/wearables/armor/chitin/armor_chitin_s01_boots.iff",
					"Chitin Left Bracer", "object/tangible/wearables/armor/chitin/armor_chitin_s01_bracer_l.iff",
					"Chitin Right Bracer", "object/tangible/wearables/armor/chitin/armor_chitin_s01_bracer_r.iff",
					"Chitin Chest Plate", "object/tangible/wearables/armor/chitin/armor_chitin_s01_chest_plate.iff",
					"Chitin Gloves", "object/tangible/wearables/armor/chitin/armor_chitin_s01_gloves.iff",
					"Chitin Helmet", "object/tangible/wearables/armor/chitin/armor_chitin_s01_helmet.iff",
					"Chitin Leggings", "object/tangible/wearables/armor/chitin/armor_chitin_s01_leggings.iff"
				},
				"Composite Armor",
				{
					"Composite Left Bicep", "object/tangible/wearables/armor/composite/armor_composite_bicep_l.iff",
					"Composite Right Bicep", "object/tangible/wearables/armor/composite/armor_composite_bicep_r.iff",
					"Composite Boots", "object/tangible/wearables/armor/composite/armor_composite_boots.iff",
					"Composite Left Bracer", "object/tangible/wearables/armor/composite/armor_composite_bracer_l.iff",
					"Composite Right Bracer", "object/tangible/wearables/armor/composite/armor_composite_bracer_r.iff",
					"Composite Chest Plate", "object/tangible/wearables/armor/composite/armor_composite_chest_plate.iff",
					"Composite Gloves", "object/tangible/wearables/armor/composite/armor_composite_gloves.iff",
					"Composite Helmet", "object/tangible/wearables/armor/composite/armor_composite_helmet.iff",
					"Composite Leggings", "object/tangible/wearables/armor/composite/armor_composite_leggings.iff"
				}
			},
			"Clothes",
			{
				"Jedi Robes",
				{
						"Light Jedi Robes",
						{
						"Light Jedi Robe 1", "object/tangible/wearables/robe/robe_jedi_light_s01.iff",
						"Light Jedi Robe 2", "object/tangible/wearables/robe/robe_jedi_light_s02.iff",
						"Light Jedi Robe 3", "object/tangible/wearables/robe/robe_jedi_light_s03.iff",
						"Light Jedi Robe 4", "object/tangible/wearables/robe/robe_jedi_light_s04.iff",
						"Light Jedi Robe 5", "object/tangible/wearables/robe/robe_jedi_light_s05.iff"
						},
						
						"Dark Jedi Robes",
						{
						"Dark Jedi Robe 1", "object/tangible/wearables/robe/robe_jedi_dark_s01.iff",
						"Dark Jedi Robe 2", "object/tangible/wearables/robe/robe_jedi_dark_s02.iff",
						"Dark Jedi Robe 3", "object/tangible/wearables/robe/robe_jedi_dark_s03.iff",
						"Dark Jedi Robe 4", "object/tangible/wearables/robe/robe_jedi_dark_s04.iff",
						"Dark Jedi Robe 5", "object/tangible/wearables/robe/robe_jedi_dark_s05.iff"
						}
				}
			},
			"Consumables",
			{
				"Desserts",
				{
					--"Air Cake", "object/tangible/food/crafted/dessert_air_cake.iff",
					--"Almond Kwevvu Crisp Munchies", "object/tangible/food/crafted/dessert_almond_kwevvu_crisp_munchies.iff",
					--"Bantha Butter", "object/tangible/food/crafted/dessert_bantha_butter.iff",
					--"Blap Biscuit", "object/tangible/food/crafted/dessert_blap_biscuit.iff",
					--"Blob Candy", "object/tangible/food/crafted/dessert_blob_candy.iff",
					--"Bofa Treat", "object/tangible/food/crafted/dessert_bofa_treat.iff",
					--"Cavaellin Creams", "object/tangible/food/crafted/dessert_cavaellin_creams.iff",
					--"Chandad", "object/tangible/food/crafted/dessert_chandad.iff",
					--"Citros Snow Cake", "object/tangible/food/crafted/dessert_citros_snow_cake.iff",
					--"Corellian Fried Icecream", "object/tangible/food/crafted/dessert_corellian_fried_icecream.iff",
					--"Deneelian Fizz Pudding", "object/tangible/food/crafted/dessert_deneelian_fizz_pudding.iff",
					"Dweezel", "object/tangible/food/crafted/dessert_dweezel.iff",
					--"Felbar", "object/tangible/food/crafted/dessert_felbar.iff",
					--"Glazed Glucose Pate", "object/tangible/food/crafted/dessert_glazed_glucose_pate.iff",
					--"Gorrnar", "object/tangible/food/crafted/dessert_gorrnar.iff",
					--"Kiwik Clusjo Swirl", "object/tangible/food/crafted/dessert_kiwik_clusjo_swirl.iff",
					--"Nanana Twist", "object/tangible/food/crafted/dessert_nanana_twist.iff",
					--"Para Roll", "object/tangible/food/crafted/dessert_para_roll.iff",
					--"Parwan Nutricake", "object/tangible/food/crafted/dessert_parwan_nutricake.iff",
					--"Pastebread", "object/tangible/food/crafted/dessert_pastebread.iff",
					"Pikatta Pie", "object/tangible/food/crafted/dessert_pikatta_pie.iff",
					--"Pkneb", "object/tangible/food/crafted/dessert_pkneb.iff",
					--"Puffcake", "object/tangible/food/crafted/dessert_puffcake.iff",
					--"Pyollian Cake", "object/tangible/food/crafted/dessert_pyollian_cake.iff",
					--"Ryshcate", "object/tangible/food/crafted/dessert_ryshcate.iff",
					--"Smugglers Delight", "object/tangible/food/crafted/dessert_smugglers_delight.iff",
					--"Sweesonberry Rolls", "object/tangible/food/crafted/dessert_sweesonberry_rolls.iff",
					--"Sweet Cake Mix", "object/tangible/food/crafted/dessert_sweet_cake_mix.iff",
					--"Tranna Nougat Cream", "object/tangible/food/crafted/dessert_tranna_nougat_cream.iff",
					--"Vagnerian Canape", "object/tangible/food/crafted/dessert_vagnerian_canape.iff",
					--"Wedding Cake", "object/tangible/food/crafted/dessert_wedding_cake.iff",
					--"Won Won", "object/tangible/food/crafted/dessert_won_won.iff",
				},
				--"Dishes",
				--{
					--"Ahrisa", "object/tangible/food/crafted/dish_ahrisa.iff",
					--"Bivoli Tempari", "object/tangible/food/crafted/dish_bivoli_tempari.iff",
					--"Blood Chowder", "object/tangible/food/crafted/dish_blood_chowder.iff",
					--"Braised Canron", "object/tangible/food/crafted/dish_braised_canron.iff",
					--"Cho Nor Hoola", "object/tangible/food/crafted/dish_cho_nor_hoola.iff",
					--"Crispic", "object/tangible/food/crafted/dish_crispic.iff",
					--"Dustcrepe", "object/tangible/food/crafted/dish_dustcrepe.iff",
					--"Exo Protein Wafers", "object/tangible/food/crafted/dish_exo_protein_wafers.iff",
					--"Fire Stew", "object/tangible/food/crafted/dish_fire_stew.iff",
					--"Fried Endwa", "object/tangible/food/crafted/dish_fried_endwa.iff",
					--"Gruuvan Shaal", "object/tangible/food/crafted/dish_gruuvan_shaal.iff",
					--"Havla", "object/tangible/food/crafted/dish_havla.iff",
					--"Kanali Wafers", "object/tangible/food/crafted/dish_kanali_wafers.iff",
					--"Karkan Ribenes", "object/tangible/food/crafted/dish_karkan_ribenes.iff",
					--"Meatlump", "object/tangible/food/crafted/dish_meatlump.iff",
					--"ormachek", "object/tangible/food/crafted/dish_ormachek.iff",
					--"Patot Panak", "object/tangible/food/crafted/dish_patot_panak.iff",
					--"Protato", "object/tangible/food/crafted/dish_protato.iff",
					--"Puk", "object/tangible/food/crafted/dish_puk.iff",
					--"Rakririan Burnout Sauce", "object/tangible/food/crafted/dish_rakririan_burnout_sauce.iff",
					--"Ramorrean Capanata", "object/tangible/food/crafted/dish_ramorrean_capanata.iff",
					--"Rations", "object/tangible/food/crafted/dish_rations.iff",
					--"Scrimpi", "object/tangible/food/crafted/dish_scrimpi.iff",
					--"Soypro", "object/tangible/food/crafted/dish_soypro.iff",
					--"Stewed Gwouch", "object/tangible/food/crafted/dish_stewed_gwouch.iff",
					--"Synthsteak", "object/tangible/food/crafted/dish_synthsteak.iff",
					--"Teltier Noodles", "object/tangible/food/crafted/dish_teltier_noodles.iff",
					--"Terratta", "object/tangible/food/crafted/dish_terratta.iff",
					--"Thakitillo", "object/tangible/food/crafted/dish_thakitillo.iff",
					--"Travel Biscuits", "object/tangible/food/crafted/dish_travel_biscuits.iff",
					--"Trimpian", "object/tangible/food/crafted/dish_trimpian.iff",
					--"Vegeparsine", "object/tangible/food/crafted/dish_vegeparsine.iff",
					--"Veghash", "object/tangible/food/crafted/dish_veghash.iff",
					--"Vercupti of Agazza Boleruuee", "object/tangible/food/crafted/dish_vercupti_of_agazza_boleruuee.iff",
					--"Wastril Bread", "object/tangible/food/crafted/dish_wastril_bread.iff",
					--"Xermaauc", "object/tangible/food/crafted/dish_xermaauc.iff"
				--},
				--"Drinks",
				--{
					--"Accarragm", "object/tangible/food/crafted/drink_accarragm.iff",
					--"Aitha", "object/tangible/food/crafted/drink_aitha.iff",
					--"Alcohol", "object/tangible/food/crafted/drink_alcohol.iff",
					--"Aludium Pu36", "object/tangible/food/crafted/drink_aludium_pu36.iff",
					--"Angerian Fishak Surprise", "object/tangible/food/crafted/drink_angerian_fishak_surprise.iff",
					--"Antakarian Fire Dancer", "object/tangible/food/crafted/drink_antakarian_fire_dancer.iff",
					--"Bantha Blaster", "object/tangible/food/crafted/drink_bantha_blaster.iff",
					--"Bespin Port", "object/tangible/food/crafted/drink_bespin_port.iff",
					--"Blue Milk", "object/tangible/food/crafted/drink_blue_milk.iff",
					--"Breath of Heaven", "object/tangible/food/crafted/drink_breath_of_heaven.iff",
					--"Caf", "object/tangible/food/crafted/drink_caf.iff",
					--"Charde", "object/tangible/food/crafted/drink_charde.iff",
					--"Corellian Ale", "object/tangible/food/crafted/drink_corellian_ale.iff",
					--"Corellian Brandy", "object/tangible/food/crafted/drink_corellian_brandy.iff",
					--"Cortyg", "object/tangible/food/crafted/drink_cortyg.iff",
					--"Deuterium Pyro", "object/tangible/food/crafted/drink_deuterium_pyro.iff",
					--"Double Dip outer Rim Rumdrop", "object/tangible/food/crafted/drink_double_dip_outer_rim_rumdrop.iff",
					--"Durindfire", "object/tangible/food/crafted/drink_durindfire.iff",
					--"Elshandruu Pica Thundercloud", "object/tangible/food/crafted/drink_elshandruu_pica_thundercloud.iff",
					--"Flameout", "object/tangible/food/crafted/drink_flameout.iff",
					--"Garrmorl", "object/tangible/food/crafted/drink_garrmorl.iff",
					--"Gralinyn Juice", "object/tangible/food/crafted/drink_gralinyn_juice.iff",
					--"Ice Blaster", "object/tangible/food/crafted/drink_ice_blaster.iff",
					--"Ithorian Mist", "object/tangible/food/crafted/drink_ithorian_mist.iff",
					--"Jaar", "object/tangible/food/crafted/drink_jaar.iff",
					--"Jawa Beer", "object/tangible/food/crafted/drink_jawa_beer.iff",
					--"Kylessian Fruit Distillate", "object/tangible/food/crafted/drink_kylessian_fruit_distillate.iff",
					--"Mandalorian Wine", "object/tangible/food/crafted/drink_mandalorian_wine.iff",
					--"Ruby Bliel", "object/tangible/food/crafted/drink_ruby_bliel.iff",
					--"Skannbult Likker", "object/tangible/food/crafted/drink_skannbult_likker.iff",
					--"Spiced Tea", "object/tangible/food/crafted/drink_spiced_tea.iff",
					--"Starshine Surprise", "object/tangible/food/crafted/drink_starshine_surprise.iff",
					--"Sullustan Gin", "object/tangible/food/crafted/drink_sullustan_gin.iff",
					--"Tatooine Sunburn", "object/tangible/food/crafted/drink_tatooine_sunburn.iff",
					--"Tilla Tiil", "object/tangible/food/crafted/drink_tilla_tiil.iff",
					--"Tssolok", "object/tangible/food/crafted/drink_tssolok.iff",
					--"Vasarian Brandy", "object/tangible/food/crafted/drink_vasarian_brandy.iff",
					--"Vayerbok", "object/tangible/food/crafted/drink_vayerbok.iff",
					--"Veronian Berry Wine", "object/tangible/food/crafted/drink_veronian_berry_wine.iff"
				--},
				--"Foraged Food",
				--{
					--"Jar of Berries", "object/tangible/food/foraged/edible_jar_berries.iff",
					--"Jar of Bugs", "object/tangible/food/foraged/edible_jar_bugs.iff",
					--"Jar of Fungus", "object/tangible/food/foraged/edible_jar_fungus.iff",
					--"Jar of Funk", "object/tangible/food/foraged/edible_jar_funk.iff",
					--"Jar of Livers", "object/tangible/food/foraged/edible_jar_livers.iff",
					--"Fruit Style 1", "object/tangible/food/foraged/foraged_fruit_s1.iff",
					--"Fruit Style 2", "object/tangible/food/foraged/foraged_fruit_s2.iff",
					--"Fruit Style 3", "object/tangible/food/foraged/foraged_fruit_s3.iff",
					--"Fruit Style 4", "object/tangible/food/foraged/foraged_fruit_s4.iff",
					--"Fruit Style 5", "object/tangible/food/foraged/foraged_fruit_s5.iff",
					--"Vegetable Style 2", "object/tangible/food/foraged/foraged_vegetable_s2.iff",
					--"Vegetable Style 3", "object/tangible/food/foraged/foraged_vegetable_s3.iff",
					--"Vegetable Style 4", "object/tangible/food/foraged/foraged_vegetable_s4.iff",
					--"Vegetable Style 5", "object/tangible/food/foraged/foraged_vegetable_s5.iff"
				--},
				--"Generic Food",
				--{
					--"Bread loaf", "object/tangible/food/bread_loaf_full_s1.iff",
					--"Fruit Melon", "object/tangible/food/fruit_melon.iff",
					--"Meat Kabob", "object/tangible/food/meat_kabob.iff",
					--"Meat Object", "object/tangible/food/meat_object.iff",
					--"Nectar", "object/tangible/food/nectar.iff"
				--},
				"Spice",
				{
					"Booster Blue", "object/tangible/food/spice/spice_booster_blue.iff",
					--"Crash N Burn", "object/tangible/food/spice/spice_brash_n_burn.iff",
					"Droid Lube", "object/tangible/food/spice/spice_droid_lube.iff",
					"Giggledust", "object/tangible/food/spice/spice_giggledust.iff",
					"Grey Gabaki", "object/tangible/food/spice/spice_grey_gabaki.iff",
					"Gunjack", "object/tangible/food/spice/spice_gunjack.iff",
					--"Kliknik Boost", "object/tangible/food/spice/spice_kliknik_boost.iff",
					--"Kwi Boost", "object/tangible/food/spice/spice_kwi_boost.iff",
					"Muon Gold", "object/tangible/food/spice/spice_muon_gold.iff",  
					"Neutron Pixie", "object/tangible/food/spice/spice_neutron_pixey.iff",
					"Pyrepenol", "object/tangible/food/spice/spice_pyrepenol.iff",
					--"Scramjet", "object/tangible/food/spice/spice_Scramjet.iff",
					"Sedative H4B", "object/tangible/food/spice/spice_sedative_h4b.iff",
					"Shadowpaw", "object/tangible/food/spice/spice_shadowpaw.iff",
					"Sweetblossom", "object/tangible/food/spice/spice_sweetblossom.iff",
					"Thruster Head", "object/tangible/food/spice/spice_thruster_head.iff",
					"Yarrock", "object/tangible/food/spice/spice_yarrock.iff"
				}
			},
			"Deeds",
			{
				--"Vehicle Deeds",
				--{
					--"Swoop", "object/tangible/deed/vehicle_deed/speederbike_swoop_deed.iff",
					--"Jetpack", "object/tangible/deed/vehicle_deed/jetpack_deed.iff",
					--"Speederbike", "object/tangible/deed/vehicle_deed/speederbike_deed.iff",
					--"Speederbike Flash", "object/tangible/deed/vehicle_deed/speederbike_flash_deed.iff",
					--"Landspeeder av21", "object/tangible/deed/vehicle_deed/landspeeder_av21_deed.iff",
					--"Landspeeder x31", "object/tangible/deed/vehicle_deed/landspeeder_x31_deed.iff",
					--"Landspeeder x34", "object/tangible/deed/vehicle_deed/landspeeder_x34_deed.iff"
				--},
				"Structure Deeds",
				{
					--"Factional Bases",
					--{
						--"Generic Base 1", "object/tangible/deed/faction_perk/hq/hq_s01.iff",
						--"Generic PVP Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_pvp.iff",
						--"Generic Base 2", "object/tangible/deed/faction_perk/hq/hq_s02.iff",
						--"Generic PVP Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_pvp.iff",
						--"Generic Base 3", "object/tangible/deed/faction_perk/hq/hq_s03.iff",
						--"Generic PVP Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_pvp.iff",
						--"Generic Base 4", "object/tangible/deed/faction_perk/hq/hq_s04.iff",
						--"Generic PVP Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_pvp.iff",
						--"Generic Base 5", "object/tangible/deed/faction_perk/hq/hq_s05.iff",
						--"Generic PVP Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_pvp.iff",
						--"Imperial Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_imp.iff",
						--"Imperial PVP Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_imp_pvp.iff",
						--"Imperial Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_imp.iff",
						--"Imperial PVP Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_imp_pvp.iff",
						--"Imperial Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_imp.iff",
						--"Imperial PVP Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_imp_pvp.iff",
						--"Imperial Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_imp.iff",
						--"Imperial PVP Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_imp_pvp.iff",
						--"Imperial Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_imp.iff",
						--"Imperial PVP Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_imp_pvp.iff",
						--"Rebel Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_reb.iff",
						--"Rebel PVP Base 1", "object/tangible/deed/faction_perk/hq/hq_s01_reb_pvp.iff",
						--"Rebel Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_reb.iff",
						--"Rebel PVP Base 2", "object/tangible/deed/faction_perk/hq/hq_s02_reb_pvp.iff",
						--"Rebel Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_reb.iff",
						--"Rebel PVP Base 3", "object/tangible/deed/faction_perk/hq/hq_s03_reb_pvp.iff",
						--"Rebel Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_reb.iff",
						--"Rebel PVP Base 4", "object/tangible/deed/faction_perk/hq/hq_s04_reb_pvp.iff",
						--"Rebel Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_reb.iff",
						--"Rebel PVP Base 5", "object/tangible/deed/faction_perk/hq/hq_s05_reb_pvp.iff",
					--},
					"Merchant Tent Deeds",
					{
						"Merchant Tent Deed (Style 1)", "object/tangible/deed/player_house_deed/merchant_tent_style_01_deed.iff",
						"Merchant Tent Deed (Style 2)", "object/tangible/deed/player_house_deed/merchant_tent_style_02_deed.iff",
						"Merchant Tent Deed (Style 3)", "object/tangible/deed/player_house_deed/merchant_tent_style_03_deed.iff"
					},
					"Installation Deeds",
					{
						"Harvester Deeds",
						{
							"Creature Harvester Deed", "object/tangible/deed/harvester_deed/harvester_creature_deed.iff",
							"Personal Flora Harvester Deed", "object/tangible/deed/harvester_deed/harvester_flora_deed.iff",
							"Heavy Flora Harvester Deed", "object/tangible/deed/harvester_deed/harvester_flora_deed_heavy.iff",
							"Medium Flora Harvester Deed", "object/tangible/deed/harvester_deed/harvester_flora_deed_medium.iff",
							"Personal Gas Harvester Deed", "object/tangible/deed/harvester_deed/harvester_gas_deed.iff",
							"Heavy Gas Harvester Deed", "object/tangible/deed/harvester_deed/harvester_gas_deed_heavy.iff",
							"Medium Gas Harvester Deed", "object/tangible/deed/harvester_deed/harvester_gas_deed_medium.iff",
							"Personal Liquid Harvester Deed", "object/tangible/deed/harvester_deed/harvester_liquid_deed.iff",
							"Heavy Liquid Harvester Deed", "object/tangible/deed/harvester_deed/harvester_liquid_deed_heavy.iff",
							"Medium Liquid Harvester Deed", "object/tangible/deed/harvester_deed/harvester_liquid_deed_medium.iff",
							"Personal Moisture Harvester Deed", "object/tangible/deed/harvester_deed/harvester_moisture_deed.iff",
							"Heavy Moisture Harvester Deed", "object/tangible/deed/harvester_deed/harvester_moisture_deed_heavy.iff",
							"Medium Moisture Harvester Deed", "object/tangible/deed/harvester_deed/harvester_moisture_deed_medium.iff",
							"Personal Mineral Harvester Deed", "object/tangible/deed/harvester_deed/harvester_ore_s1_deed.iff",
							"Heavy Mineral Harvester Deed", "object/tangible/deed/harvester_deed/harvester_ore_heavy_deed.iff",
							"Medium Mineral Harvester Deed", "object/tangible/deed/harvester_deed/harvester_ore_s2_deed.iff"
						},
						"Generator Deeds",
						{
							"Fusion Generator Deed", "object/tangible/deed/generator_deed/generator_fusion_deed.iff",
							"Photo Bio Generator Deed", "object/tangible/deed/generator_deed/generator_photo_bio_deed.iff",
							"Solar Generator Deed", "object/tangible/deed/generator_deed/generator_solar_deed.iff",
							"Wind Generator Deed", "object/tangible/deed/generator_deed/generator_wind_deed.iff",
						},
						"Factory Deeds",
						{
							"Clothing Factory Deed", "object/tangible/deed/factory_deed/factory_clothing_deed.iff",
							"Food Factory Deed", "object/tangible/deed/factory_deed/factory_food_deed.iff",
							"Item Factory Deed", "object/tangible/deed/factory_deed/factory_item_deed.iff",
							"Structure Factory Deed", "object/tangible/deed/factory_deed/factory_structure_deed.iff"
						}
					},
					"Generic Deeds",
					{
						"Player House Deeds",
						{
							"Large Generic House Deed", "object/tangible/deed/player_house_deed/generic_house_large_deed.iff",
							"Large Generic House Deed (Style 2)", "object/tangible/deed/player_house_deed/generic_house_large_style_02_deed.iff",
							"Medium Generic House Deed", "object/tangible/deed/player_house_deed/generic_house_medium_deed.iff",
							"Medium Generic House Deed (Style 2)", "object/tangible/deed/player_house_deed/generic_house_medium_style_02_deed.iff",
							"Small Generic House Deed", "object/tangible/deed/player_house_deed/generic_house_small_deed.iff",
							"Small Generic House Deed Floorplan 2", "object/tangible/deed/player_house_deed/generic_house_small_floor_02_deed.iff",
							"Small Generic House Deed (Style 2)", "object/tangible/deed/player_house_deed/generic_house_small_style_02_deed.iff",
							"Small Generic House Deed Floorplan 2 (Style 2)", "object/tangible/deed/player_house_deed/generic_house_small_style_02_floor_02_deed.iff",
							"Large Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_large_deed.iff"
						},
						"City Deeds",
						{
							"Large Dantooine Garden", "object/tangible/deed/city_deed/garden_dantooine_lrg_01_deed.iff",
							"Medium Dantooine Garden", "object/tangible/deed/city_deed/garden_dantooine_med_01_deed.iff",
							"Small Dantooine Garden", "object/tangible/deed/city_deed/garden_dantooine_sml_01_deed.iff",
							"Large Dathomir Garden", "object/tangible/deed/city_deed/garden_dathomir_lrg_01_deed.iff",
							"Medium Dathomir Garden", "object/tangible/deed/city_deed/garden_dathomir_med_01_deed.iff",
							"Small Dathomir Garden", "object/tangible/deed/city_deed/garden_dathomir_sml_01_deed.iff",
							"Large Endor Garden", "object/tangible/deed/city_deed/garden_endor_lrg_01_deed.iff",
							"Medium Endor Garden", "object/tangible/deed/city_deed/garden_endor_med_01_deed.iff",
							"Small Endor Garden", "object/tangible/deed/city_deed/garden_endor_sml_01_deed.iff"	
						}
					},
					"Corellia Deeds",
					{
						"Player House Deeds",
						{
							"Corellian Guild Hall Deed", "object/tangible/deed/guild_deed/corellia_guild_deed.iff",
							"Large Corellian House Deed", "object/tangible/deed/player_house_deed/corellia_house_large_deed.iff",
							"Large Corellian House Deed (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_large_style_02_deed.iff",
							"Medium Corellian House Deed", "object/tangible/deed/player_house_deed/corellia_house_medium_deed.iff",
							"Medium Corellian House Deed (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_medium_style_02_deed.iff",
							"Small Corellian House Deed", "object/tangible/deed/player_house_deed/corellia_house_small_deed.iff",
							"Small Corellian House Deed Floorplan 2", "object/tangible/deed/player_house_deed/corellia_house_small_floor_02_deed.iff",
							"Small Corellian House Deed (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_small_style_02_deed.iff",
							"Small Corellian House Deed Floorplan 2 (Style 2)", "object/tangible/deed/player_house_deed/corellia_house_small_style_02_floor_02_deed.iff"
						},
						"City Deeds",
						{
							"Corellia Bank Deed", "object/tangible/deed/city_deed/bank_corellia_deed.iff",
							"Corellia Cantina Deed", "object/tangible/deed/city_deed/cantina_corellia_deed.iff",
							"Corellia Garage Deed", "object/tangible/deed/city_deed/garage_corellia_deed.iff",
							"Corellia Shuttleport Deed", "object/tangible/deed/city_deed/shuttleport_corellia_deed.iff",
							"Corellia City Hall Deed", "object/tangible/deed/city_deed/cityhall_corellia_deed.iff",
							"Corellia Cloning Center Deed", "object/tangible/deed/city_deed/cloning_corellia_deed.iff",
							"Corellia Medical Center Deed", "object/tangible/deed/city_deed/hospital_corellia_deed.iff",
							"Corellia Theater Deed", "object/tangible/deed/city_deed/theater_corellia_deed.iff",
							"Large Corellia Garden (Style 1)", "object/tangible/deed/city_deed/garden_corellia_lrg_01_deed.iff",
							"Large Corellia Garden (Style 2)", "object/tangible/deed/city_deed/garden_corellia_lrg_02_deed.iff",
							"Large Corellia Garden (Style 3)", "object/tangible/deed/city_deed/garden_corellia_lrg_03_deed.iff",
							"Large Corellia Garden (Style 4)", "object/tangible/deed/city_deed/garden_corellia_lrg_04_deed.iff",
							"Large Corellia Garden (Style 5)", "object/tangible/deed/city_deed/garden_corellia_lrg_05_deed.iff",
							"Medium Corellia Garden (Style 1)", "object/tangible/deed/city_deed/garden_corellia_med_01_deed.iff",
							"Medium Corellia Garden (Style 2)", "object/tangible/deed/city_deed/garden_corellia_med_02_deed.iff",
							"Medium Corellia Garden (Style 3)", "object/tangible/deed/city_deed/garden_corellia_med_03_deed.iff",
							"Medium Corellia Garden (Style 4)", "object/tangible/deed/city_deed/garden_corellia_med_04_deed.iff",
							"Medium Corellia Garden (Style 5)", "object/tangible/deed/city_deed/garden_corellia_med_05_deed.iff",
							"Small Corellia Garden (Style 1)", "object/tangible/deed/city_deed/garden_corellia_sml_01_deed.iff",
							"Small Corellia Garden (Style 2)", "object/tangible/deed/city_deed/garden_corellia_sml_02_deed.iff",
							"Small Corellia Garden (Style 3)", "object/tangible/deed/city_deed/garden_corellia_sml_03_deed.iff",
							"Small Corellia Garden (Style 4)", "object/tangible/deed/city_deed/garden_corellia_sml_04_deed.iff",
							"Small Corellia Garden (Style 5)", "object/tangible/deed/city_deed/garden_corellia_sml_05_deed.iff"
						}
					},
					"Naboo Deeds",
					{
						"Player House Deeds",
						{
							"Naboo Guild Hall Deed", "object/tangible/deed/guild_deed/naboo_guild_deed.iff",
							"Large Naboo House Deed", "object/tangible/deed/player_house_deed/naboo_house_large_deed.iff",
							"Medium Naboo House Deed", "object/tangible/deed/player_house_deed/naboo_house_medium_deed.iff",
							"Medium Naboo House Deed (Style 2)", "object/tangible/deed/player_house_deed/naboo_house_medium_style_02_deed.iff",
							"Small Naboo House Deed", "object/tangible/deed/player_house_deed/naboo_house_small_deed.iff",
							"Small Naboo House Deed (Style 2)", "object/tangible/deed/player_house_deed/naboo_house_small_style_02_deed.iff"
						},
						"City Deeds",
						{
							"Naboo Bank Deed", "object/tangible/deed/city_deed/bank_naboo_deed.iff",
							"Naboo Cantina Deed", "object/tangible/deed/city_deed/cantina_naboo_deed.iff",
							"Naboo Garage Deed", "object/tangible/deed/city_deed/garage_naboo_deed.iff",
							"Naboo Shuttleport Deed", "object/tangible/deed/city_deed/shuttleport_naboo_deed.iff",
							"Naboo City Hall Deed", "object/tangible/deed/city_deed/cityhall_naboo_deed.iff",
							"Naboo Cloning Center Deed", "object/tangible/deed/city_deed/cloning_naboo_deed.iff",
							"Naboo Medical Center Deed", "object/tangible/deed/city_deed/hospital_naboo_deed.iff",
							"Naboo Theater Deed", "object/tangible/deed/city_deed/theater_naboo_deed.iff",
							"Large Naboo Garden (Style 1)", "object/tangible/deed/city_deed/garden_naboo_lrg_01_deed.iff",
							"Large Naboo Garden (Style 2)", "object/tangible/deed/city_deed/garden_naboo_lrg_02_deed.iff",
							"Large Naboo Garden (Style 3)", "object/tangible/deed/city_deed/garden_naboo_lrg_03_deed.iff",
							"Large Naboo Garden (Style 4)", "object/tangible/deed/city_deed/garden_naboo_lrg_04_deed.iff",
							"Large Naboo Garden (Style 5)", "object/tangible/deed/city_deed/garden_naboo_lrg_05_deed.iff",
							"Medium Naboo Garden (Style 1)", "object/tangible/deed/city_deed/garden_naboo_med_01_deed.iff",
							"Medium Naboo Garden (Style 2)", "object/tangible/deed/city_deed/garden_naboo_med_02_deed.iff",
							"Medium Naboo Garden (Style 3)", "object/tangible/deed/city_deed/garden_naboo_med_03_deed.iff",
							"Medium Naboo Garden (Style 4)", "object/tangible/deed/city_deed/garden_naboo_med_04_deed.iff",
							"Medium Naboo Garden (Style 5)", "object/tangible/deed/city_deed/garden_naboo_med_05_deed.iff",
							"Small Naboo Garden (Style 1)", "object/tangible/deed/city_deed/garden_naboo_sml_01_deed.iff",
							"Small Naboo Garden (Style 2)", "object/tangible/deed/city_deed/garden_naboo_sml_02_deed.iff",
							"Small Naboo Garden (Style 3)", "object/tangible/deed/city_deed/garden_naboo_sml_03_deed.iff",
							"Small Naboo Garden (Style 4)", "object/tangible/deed/city_deed/garden_naboo_sml_04_deed.iff",
							"Small Naboo Garden (Style 5)", "object/tangible/deed/city_deed/garden_naboo_sml_05_deed.iff"
						}
					},
					"Tatooine Deeds",
					{
						"Player House Deeds",
						{
							"Tatooine Guild Hall Deed", "object/tangible/deed/guild_deed/tatooine_guild_deed.iff",
							"Tatooine Guild Hall (Style 2) Deed", "object/tangible/deed/guild_deed/tatooine_guild_style_02_deed.iff",
							"Large Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_large_deed.iff",
							"Medium Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_medium_deed.iff",
							"Small Tatooine House Deed", "object/tangible/deed/player_house_deed/tatooine_house_small_deed.iff",
							"Small Tatooine House Deed (Style 2)", "object/tangible/deed/player_house_deed/tatooine_house_small_style_02_deed.iff"
						},
						"City Deeds",
						{
							"Tatooine Bank Deed", "object/tangible/deed/city_deed/bank_tatooine_deed.iff",
							"Tatooine Cantina Deed", "object/tangible/deed/city_deed/cantina_tatooine_deed.iff",
							"Tatooine Garage Deed", "object/tangible/deed/city_deed/garage_tatooine_deed.iff",
							"Tatooine Shuttleport Deed", "object/tangible/deed/city_deed/shuttleport_tatooine_deed.iff",
							"Tatooine City Hall Deed", "object/tangible/deed/city_deed/cityhall_tatooine_deed.iff",
							"Tatooine Cloning Center Deed", "object/tangible/deed/city_deed/cloning_tatooine_deed.iff",
							"Tatooine Medical Center Deed", "object/tangible/deed/city_deed/hospital_tatooine_deed.iff",
							"Tatooine Theater Deed", "object/tangible/deed/city_deed/theater_tatooine_deed.iff",
							"Large Tatooine Garden (Style 1)", "object/tangible/deed/city_deed/garden_tatooine_lrg_01_deed.iff",
							"Large Tatooine Garden (Style 2)", "object/tangible/deed/city_deed/garden_tatooine_lrg_02_deed.iff",
							"Large Tatooine Garden (Style 3)", "object/tangible/deed/city_deed/garden_tatooine_lrg_03_deed.iff",
							"Large Tatooine Garden (Style 4)", "object/tangible/deed/city_deed/garden_tatooine_lrg_04_deed.iff",
							"Large Tatooine Garden (Style 5)", "object/tangible/deed/city_deed/garden_tatooine_lrg_05_deed.iff",
							"Medium Tatooine Garden (Style 1)", "object/tangible/deed/city_deed/garden_tatooine_med_01_deed.iff",
							"Medium Tatooine Garden (Style 2)", "object/tangible/deed/city_deed/garden_tatooine_med_02_deed.iff",
							"Medium Tatooine Garden (Style 3)", "object/tangible/deed/city_deed/garden_tatooine_med_03_deed.iff",
							"Medium Tatooine Garden (Style 4)", "object/tangible/deed/city_deed/garden_tatooine_med_04_deed.iff",
							"Medium Tatooine Garden (Style 5)", "object/tangible/deed/city_deed/garden_tatooine_med_05_deed.iff",
							"Small Tatooine Garden (Style 1)", "object/tangible/deed/city_deed/garden_tatooine_sml_01_deed.iff",
							"Small Tatooine Garden (Style 2)", "object/tangible/deed/city_deed/garden_tatooine_sml_02_deed.iff",
							"Small Tatooine Garden (Style 3)", "object/tangible/deed/city_deed/garden_tatooine_sml_03_deed.iff",
							"Small Tatooine Garden (Style 4)", "object/tangible/deed/city_deed/garden_tatooine_sml_04_deed.iff",
							"Small Tatooine Garden (Style 5)", "object/tangible/deed/city_deed/garden_tatooine_sml_05_deed.iff"
						}
					}
				}
			},
			"Furniture",
			{	
				"Paintings",
				{
					"Bestine Painting 1", "object/tangible/painting/bestine_history_quest_painting.iff",
					"Bestine Painting 2", "object/tangible/painting/bestine_quest_painting.iff",
					"Agrilat Swamp", "object/tangible/painting/painting_agrilat_s01.iff",
					"Armor Blueprints", "object/tangible/painting/painting_armor_blueprint.iff",
					"Blue Leaf Temple", "object/tangible/painting/painting_bestine_blueleaf_temple.iff",
					"Blumbush", "object/tangible/painting/painting_bestine_blumbush.iff",
					"Boffa Plant", "object/tangible/painting/painting_bestine_boffa.iff",
					"Abstract Painting of Golden Petals No. 1", "object/tangible/painting/painting_bestine_golden_flower_01.iff",
					"Abstract Painting of Golden Petals No. 2", "object/tangible/painting/painting_bestine_golden_flower_02.iff",
					"Abstract Painting of Golden Petals No. 3", "object/tangible/painting/painting_bestine_golden_flower_03.iff",
					"Krayt Dragon Skeleton", "object/tangible/painting/painting_bestine_krayt_skeleton.iff",
					"Lucky Despot", "object/tangible/painting/painting_bestine_lucky_despot.iff",
					"Mattberry Plant", "object/tangible/painting/painting_bestine_mattberry.iff",
					"Close-up of Mon Calamari Eye 1", "object/tangible/painting/painting_bestine_moncal_eye_01.iff",
					"Close-up of Mon Calamari Eye 2", "object/tangible/painting/painting_bestine_moncal_eye_02.iff",
					"Rainbow Berry Bush", "object/tangible/painting/painting_bestine_rainbow_berry_bush.iff",
					"Raventhorn", "object/tangible/painting/painting_bestine_raventhorn.iff",
					"Ronka", "object/tangible/painting/painting_bestine_ronka.iff",
					"Bothan (female)", "object/tangible/painting/painting_bothan_f.iff",
					"Bothan (male)", "object/tangible/painting/painting_bothan_m.iff",
					"Theed Waterfall", "object/tangible/painting/painting_waterfall.iff",
					"Stormtrooper", "object/tangible/painting/painting_bw_stormtrooper.iff",				
					"Han Solo Wanted", "object/tangible/painting/painting_han_wanted.iff",
					"Luke Skywalker Wanted", "object/tangible/painting/painting_luke_wanted.iff",
					"Princess Leia Wanted", "object/tangible/painting/painting_leia_wanted.iff",
					"Schematic (Droid)", "object/tangible/painting/painting_schematic_droid.iff",
					"Schematic (Transport Ship)", "object/tangible/painting/painting_schematic_transport_ship.iff",
					"Schematic (Weapon)", "object/tangible/painting/painting_schematic_weapon.iff",
					"Veteran Reward (Cast Wing in Flight)", "object/tangible/veteran_reward/one_year_anniversary/painting_01.iff",
					"Veteran Reward (Decimator)", "object/tangible/veteran_reward/one_year_anniversary/painting_02.iff",
					"Veteran Reward (Weapon of War)", "object/tangible/veteran_reward/one_year_anniversary/painting_03.iff",
					"Veteran Reward (Tatooine Dune Speeder)", "object/tangible/veteran_reward/one_year_anniversary/painting_04.iff",
					"Veteran Reward (Fighter Study)", "object/tangible/veteran_reward/one_year_anniversary/painting_05.iff",
					"Veteran Reward (Hutt Greed)", "object/tangible/veteran_reward/one_year_anniversary/painting_06.iff",
					"Veteran Reward (Smuggler's Run)", "object/tangible/veteran_reward/one_year_anniversary/painting_07.iff",
					"Veteran Reward (Imperial TIE Oppressor)", "object/tangible/veteran_reward/one_year_anniversary/painting_08.iff",
					"Veteran Reward (Emperor's Eyes TIE Sentinel)", "object/tangible/veteran_reward/one_year_anniversary/painting_09.iff"
				},
				"Veteran Rewards",
				{
					"YT-1300 Couch Corner", "object/tangible/veteran_reward/frn_couch_falcon_corner_s01.iff",
					"YT-1300 Couch Section", "object/tangible/veteran_reward/frn_couch_falcon_section_s01.iff",
					"Darth Vader Toy", "object/tangible/veteran_reward/frn_vet_darth_vader_toy.iff",
					"Jabba the Hutt Toy", "object/tangible/veteran_reward/frn_vet_jabba_toy.iff",
					"Protocol Droid Toy", "object/tangible/veteran_reward/frn_vet_protocol_droid_toy.iff",
					"R2 Droid Toy", "object/tangible/veteran_reward/frn_vet_r2_toy.iff",
					"Stormtrooper Toy", "object/tangible/veteran_reward/frn_vet_stormtrooper_toy.iff",
					"TIE Fighter Toy", "object/tangible/veteran_reward/frn_vet_tie_fighter_toy.iff",
					"X-Wing Toy", "object/tangible/veteran_reward/frn_vet_x_wing_toy.iff"				
				},
				"Lighting",
				{
					"Candle (Style 1)", "object/tangible/furniture/all/frn_all_lamp_candlestick_free_s01_lit.iff",
					"Candle (Style 2)", "object/tangible/furniture/all/frn_all_lamp_candlestick_free_s02_lit.iff",
					"Candle (Style 3)", "object/tangible/furniture/all/frn_all_lamp_candlestick_tbl_s01.iff",
					"Candle (Style 4)", "object/tangible/furniture/all/frn_all_lamp_candlestick_tbl_s02.iff",
					"Candle (Style 5)", "object/tangible/furniture/all/frn_all_lamp_candlestick_tbl_s03.iff",
					"Desk Lamp (Style 1)", "object/tangible/furniture/all/frn_all_lamp_desk_s01_lit.iff",
					"Desk Lamp (Style 2)", "object/tangible/furniture/all/frn_all_lamp_desk_s01_lit.iff",
					"Freestannding Lamp", "object/tangible/furniture/all/frn_all_lamp_free_s01.iff",
					"Free-Standing Lamp (Style 2", "object/tangible/furniture/all/frn_all_lamp_free_s02.iff"
				},				
				"Rugs",
				{
					"Large Rectangular Rug (Style 1)", "object/tangible/furniture/modern/rug_rect_lg_s01.iff",
					"Large Rectangular Rug (Style 2)", "object/tangible/furniture/modern/rug_rect_lg_s02.iff",
					"Large Round Rug (Style 1)", "object/tangible/furniture/modern/rug_rnd_lg_s01.iff",
					"Large Round Rug (Style 2)", "object/tangible/furniture/modern/rug_rnd_sml_s01.iff",
					"Large Oval Rug (Style 1)", "object/tangible/furniture/modern/rug_oval_sml_s01.iff",
					"Large Oval Rug (Style 2)", "object/tangible/furniture/modern/rug_oval_m_s02.iff",
					"Large Square Rug", "object/tangible/furniture/modern/rug_sqr_m_s01.iff",
					"Ornate Blue Rug", "object/tangible/loot/collectible/collectible_rewards/blue_rug.iff",
					"Ornate Orange Rug", "object/tangible/loot/collectible/collectible_rewards/orange_rug.iff"
				},
				"Plants",
				{
					"Large Potted Plant (Style 1)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s1.iff",
					"Large Potted Plant (Style 2)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s2.iff",
					"Large Potted Plant (Style 3)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s3.iff",
					"Large Potted Plant (Style 4)", "object/tangible/furniture/all/frn_all_plant_potted_lg_s4.iff",
					"Small Potted Plant (Style 1)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s01.ifff",
					"Small Potted Plant (Style 2)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s02.ifff",
					"Small Potted Plant (Style 3)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s03.ifff",
					"Small Potted Plant (Style 4)", "object/tangible/furniture/all/frn_all_potted_plants_sml_s04.ifff",
					"Potted Tree (Style 1)", "object/tangible/furniture/all/frn_all_tree_potted_s1.iff",
					"Potted Tree (Style 2)", "object/tangible/furniture/all/frn_all_tree_potted_s2.iff",
					"Fountain", "object/tangible/furniture/city/fountain_heroic.iff",
					"Brazier", "object/tangible/furniture/city/fountain_brazier_round.iff"
				},
				"Miscellaneous Decorations",
				{
					--"Bacta Tank", "object/tangible/furniture/decorative/bacta_tank.iff",
					"Bottle (Style 1)", "object/tangible/furniture/decorative/bottle_pear.iff",
					"Bottle (Style 2)", "object/tangible/furniture/decorative/bottle_fat.iff",
					"Bottle (Style 3)", "object/tangible/furniture/decorative/bottle_tall.iff",
					"Bowl", "object/tangible/furniture/decorative/carved_bowl.iff",
					"Diagnostic Screen", "object/tangible/furniture/decorative/diagnostic_screen.iff",
					"Microphone", "object/tangible/furniture/decorative/microphone_s01.iff",
					"Radio", "object/tangible/furniture/decorative/radio.iff",
					"Imperial Banner", "object/tangible/furniture/all/bestine_quest_imp_banner.iff",
					"Rebel Banner", "object/tangible/furniture/all/frn_all_banner_rebel.iff",
					"Tiki Torch", "object/tangible/furniture/all/frn_all_tiki_torch_s1.iff",
					"Stuffed Fish", "object/tangible/furniture/decorative/stuffed_fish.iff",
					"Blowfish", "object/tangible/fishing/fish/blowfish.iff",
					"Nabooian Sculpture", "object/tangible/loot/collectible/collectible_rewards/collectible_sculpture_s01.iff",
					"Glass Table", "object/tangible/loot/collectible/collectible_rewards/collectible_table.iff",
					"Bed", "object/tangible/furniture/all/frn_all_bed_lg_s1.iff"
				},			
				"Elegant Furniture",
				{
					"Elegant Armoire", "object/tangible/furniture/elegant/armoire_elegant_s01.iff",
					"Elegant Bookcase", "object/tangible/furniture/elegant/bookcase_s01.iff",
					"Elegant Cabinet", "object/tangible/furniture/elegant/cabinet_s01.iff",
					"Elegant Chair", "object/tangible/furniture/elegant/chair_s01.iff",
					"Elegant Chest", "object/tangible/furniture/elegant/chest_s01.iff",
					"Elegant Coffee Table", "object/tangible/furniture/elegant/coffee_table_s01.iff",
					"Elegant Couch", "object/tangible/furniture/elegant/couch_s01.iff",
					"Elegant End Table", "object/tangible/furniture/elegant/end_table_s01.iff",
					"Elegant Love Seat", "object/tangible/furniture/elegant/love_seat_s01.iff"
				},
				"Cheap Furniture",
				{
					"Cheap Armoire", "object/tangible/furniture/cheap/armoire_s01.iff",
					"Cheap Bookcase", "object/tangible/furniture/cheap/bookcase_s01.iff",
					"Cheap Cabinet", "object/tangible/furniture/cheap/cabinet_s01.iff",
					"Cheap Chair", "object/tangible/furniture/cheap/chair_s01.iff",
					"Cheap Chest", "object/tangible/furniture/cheap/chest_s01.iff",
					"Cheap Coffee Table", "object/tangible/furniture/cheap/coffee_table_s01.iff",
					"Cheap Couch", "object/tangible/furniture/cheap/couch_s01.iff",
					"Cheap End Table", "object/tangible/furniture/cheap/end_table_s01.iff",
					"Cheap Love Seat", "object/tangible/furniture/cheap/love_seat_s01.iff"
				},
				"Technical Furniture",
				{
					"Technical Armoire", "object/tangible/furniture/technical/armoire_s01.iff",
					"Technical Bookcase", "object/tangible/furniture/technical/bookcase_s01.iff",
					"Technical Cabinet", "object/tangible/furniture/technical/cabinet_s01.iff",
					"Technical Chair", "object/tangible/furniture/technical/chair_s01.iff",
					"Technical Chest", "object/tangible/furniture/technical/chest_s01.iff",
					"Technical Coffee Table", "object/tangible/furniture/technical/coffee_table_s01.iff",
					"Technical Couch", "object/tangible/furniture/technical/couch_s01.iff",
					"Technical End Table", "object/tangible/furniture/technical/end_table_s01.iff"
				},
				"Plain Furniture",
				{
					"Plain Armoire", "object/tangible/furniture/plain/plain_armoire_s01.iff",
					"Plain Bookcase", "object/tangible/furniture/plain/plain_bookcase_s01.iff",
					"Plain Cabinet", "object/tangible/furniture/plain/plain_cabinet_s01.iff",
					"Plain Chair", "object/tangible/furniture/plain/plain_chair_s01.iff",
					"Plain Chest", "object/tangible/furniture/plain/plain_chest_s01.iff",
					"Plain Coffee Table", "object/tangible/furniture/plain/plain_coffee_table_s01.iff",
					"Plain Couch", "object/tangible/furniture/plain/plain_couch_s01.iff",
					"Plain End Table", "object/tangible/furniture/plain/plain_end_table_s01.iff",
					"Plain Love Seat", "object/tangible/furniture/plain/plain_love_seat_s01.iff"
				},
	
				"Modern Furniture",
				{
					"Modern Armoire", "object/tangible/furniture/modern/armoire_modern_style_01.iff",
					"Modern Bookcase", "object/tangible/furniture/modern/bookcase_modern_style_01.iff",
					"Modern Cabinet", "object/tangible/furniture/modern/cabinet_modern_style_01.iff",
					"Modern Chair", "object/tangible/furniture/modern/chair_modern_style_01.iff",
					"Modern Chest", "object/tangible/furniture/modern/chest_modern_style_01.iff",
					"Modern Coffee Table", "object/tangible/furniture/modern/coffee_table_modern_style_01.iff",
					"Modern Couch (Style 1)", "object/tangible/furniture/modern/couch_modern_style_01.iff",
					"Modern Couch (Style 2)", "object/tangible/furniture/modern/couch_modern_style_02.iff",
					"Modern Dining Table", "object/tangible/furniture/modern/dining_table_modern_style_01.iff",
					"Modern End Table", "object/tangible/furniture/modern/end_table_large_modern_style_01.iff",
					"Modern Love Seat", "object/tangible/furniture/modern/love_seat_modern_style_01.iff"
				}
				
			},
			"Intruments",
			{
				"Bandfill", "object/tangible/instrument/bandfill.iff",
				"Fanfar", "object/tangible/instrument/fanfar.iff",
				"Fizz", "object/tangible/instrument/fizz.iff",
				"Flute Droopy", "object/tangible/instrument/flute_droopy.iff",
				"Kloo Horn", "object/tangible/instrument/kloo_horn.iff",
				"Mandoviol", "object/tangible/instrument/mandoviol.iff",
				--"Nalargon", "object/tangible/instrument/nalargon.iff",
				--"Ommni Box", "object/tangible/instrument/ommni_box.iff",
				"Slitherhorn", "object/tangible/instrument/slitherhorn.iff",
				"Traz", "object/tangible/instrument/traz.iff"
			},
			"Pharmaceutical",
			{
				"Small StimPack", "object/tangible/medicine/stimpack_sm_s1.iff",
				"StimPack A", "object/tangible/medicine/crafted/crafted_stimpack_sm_s1_a.iff",
				"StimPack B", "object/tangible/medicine/crafted/crafted_stimpack_sm_s1_b.iff",
				"StimPack C", "object/tangible/medicine/crafted/crafted_stimpack_sm_s1_c.iff",
				"StimPack D", "object/tangible/medicine/crafted/crafted_stimpack_sm_s1_d.iff",
				"StimPack E", "object/tangible/medicine/crafted/crafted_stimpack_sm_s1_e.iff",
				"Medpack Grenade Damage A", "object/tangible/medicine/crafted/medpack_grenade_damage_a.iff",
				"Medpack Grenade Damage B", "object/tangible/medicine/crafted/medpack_grenade_damage_b.iff",
				"Medpack Grenade Damage C", "object/tangible/medicine/crafted/medpack_grenade_damage_c.iff",
				"Medpack Grenade Damage D", "object/tangible/medicine/crafted/medpack_grenade_damage_d.iff",
				"Medpack Grenade Damage E", "object/tangible/medicine/crafted/medpack_grenade_damage_e.iff",
				"Medpack Grenade Area A", "object/tangible/medicine/crafted/medpack_grenade_area_a.iff",
				"Medpack Grenade Area B", "object/tangible/medicine/crafted/medpack_grenade_area_b.iff",
				"Medpack Grenade Area C", "object/tangible/medicine/crafted/medpack_grenade_area_c.iff",
				"Medpack Enhance Action A", "object/tangible/medicine/crafted/medpack_enhance_action_a.iff",
				"Medpack Enhance Constitution A", "object/tangible/medicine/crafted/medpack_enhance_constitution_a.iff",
				"Medpack Enhance Disease A", "object/tangible/medicine/crafted/medpack_enhance_disease_a.iff",
				"Medpack Enhance Health A", "object/tangible/medicine/crafted/medpack_enhance_health_a.iff",
				"Medpack Enhance Poison A", "object/tangible/medicine/crafted/medpack_enhance_poison_a.iff",
				"Medpack Enhance Quickness A", "object/tangible/medicine/crafted/medpack_enhance_quickness_a.iff",
				"Medpack Enhance Stamina A", "object/tangible/medicine/crafted/medpack_enhance_stamina_a.iff",
				"Medpack Enhance Strength A", "object/tangible/medicine/crafted/medpack_enhance_strength_a.iff",
				"Fire blanket", "object/tangible/medicine/crafted/medic_fire_blanket.iff",
				"Medpack Cure Disease A", "object/tangible/medicine/crafted/medpack_cure_disease_a.iff",
				"Medpack Cure Disease Area A", "object/tangible/medicine/crafted/medpack_cure_disease_area_a.iff",
				"Medpack Cure Poison A", "object/tangible/medicine/crafted/medpack_cure_poison_a.iff",
				"Medpack Cure Poison Area A", "object/tangible/medicine/crafted/medpack_cure_poison_area_a.iff",
				"Disease Health Area A", "object/tangible/medicine/crafted/medpack_disease_area_health_a.iff",
				"Poison Health Area A", "object/tangible/medicine/crafted/medpack_poison_area_health_a.iff",
				"Medpack Health Wound", "object/tangible/medicine/medpack_wound_health.iff",
				"Medpack Blinded", "object/tangible/medicine/crafted/medpack_blinded_a.iff",
				"Medpack Dizzy", "object/tangible/medicine/crafted/medpack_dizzy_a.iff",
				"Medpack Intimidated", "object/tangible/medicine/crafted/medpack_intimidated_a.iff",
				"Medpack Stunned", "object/tangible/medicine/crafted/medpack_stunned_a.iff",
				"Revive Pack", "object/tangible/medicine/medpack_revive.iff"
			},
			"Resources",
			{
				"Resource Deed", "object/tangible/veteran_reward/resource.iff"
			},
			--"Scout Equipment",
			--{
				--"Camokit",
				--{
					--"Corellia", "object/tangible/scout/camokit/camokit_corellia.iff",
					--"Dantooine", "object/tangible/scout/camokit/camokit_dantooine.iff",
					--"Dathomir", "object/tangible/scout/camokit/camokit_dathomir.iff",
					--"Endor", "object/tangible/scout/camokit/camokit_endor.iff",
					--"Lok", "object/tangible/scout/camokit/camokit_lok.iff",
					--"Naboo", "object/tangible/scout/camokit/camokit_naboo.iff",
					--"Rori", "object/tangible/scout/camokit/camokit_rori.iff",
					--"Talus", "object/tangible/scout/camokit/camokit_talus.iff",
					--"Tatooine", "object/tangible/scout/camokit/camokit_tatooine.iff",
					--"Yavin", "object/tangible/scout/camokit/camokit_yavin.iff"
				--},
				--"Camps",
				--{
					--"Basic", "object/tangible/scout/camp/camp_basic.iff",
					--"Elite", "object/tangible/scout/camp/camp_elite.iff",
					--"Improved", "object/tangible/scout/camp/camp_improved.iff",
					--"Luxury", "object/tangible/scout/camp/camp_luxury.iff",
					--"Multi", "object/tangible/scout/camp/camp_multi.iff",
					--"Quality", "object/tangible/scout/camp/camp_quality.iff"
				--},
				--"Traps",
				--{
					--"Drowsy Dart", "object/tangible/scout/trap/trap_drowsy_dart.iff",
					--"Enraging Spur", "object/tangible/scout/trap/trap_enraging_spur.iff",
					--"Flash Bomb", "object/tangible/scout/trap/trap_flash_bomb.iff",
					--"Melee Defence", "object/tangible/scout/trap/trap_melee_def_1.iff",
					--"Melee Ranged defence", "object/tangible/scout/trap/trap_melee_ranged_def_1.iff",
					--"Noise Maker", "object/tangible/scout/trap/trap_noise_maker.iff",
					--"Ranged Defence", "object/tangible/scout/trap/trap_ranged_def_1.iff",
					--"Ranged Speed", "object/tangible/scout/trap/trap_ranged_speed_1.iff",
					--"Sonic Pulse", "object/tangible/scout/trap/trap_sonic_pulse.iff",
					--"State Defence", "object/tangible/scout/trap/trap_state_def_1.iff",
					--"Tranq Dart", "object/tangible/scout/trap/trap_tranq_dart.iff",
					--"Webber", "object/tangible/scout/trap/trap_webber.iff"
				--}
			--}
			"Tools",
			{
				"Crafting Tools",
				{
					"Clothing Crafting Tool", "object/tangible/crafting/station/clothing_tool.iff",
					"Food Crafting Tool", "object/tangible/crafting/station/food_tool.iff",
					"Generic Crafting Tool", "object/tangible/crafting/station/generic_tool.iff",
					"Jedi Crafting Tool", "object/tangible/crafting/station/jedi_tool.iff",
					"Starship Crafting Tool", "object/tangible/crafting/station/space_tool.iff",
					"Structure Crafting Tool", "object/tangible/crafting/station/structure_tool.iff",
					"Weapon Crafting Tool", "object/tangible/crafting/station/weapon_tool.iff"
				},
				"Crafting Stations",
				{
					"Clothing Crafting Station", "object/tangible/crafting/station/clothing_station.iff",
					"Food Crafting Station", "object/tangible/crafting/station/food_station.iff",
					"Starship Crafting Station", "object/tangible/crafting/station/space_station.iff",
					"Structure Crafting Station", "object/tangible/crafting/station/structure_station.iff",
					"Weapon Crafting Station", "object/tangible/crafting/station/weapon_station.iff"
				},
				"Survey Tools",
				{
					"Gas Survey Tool", "object/tangible/survey_tool/survey_tool_gas.iff",
					--"Inorganic Survey Tool", "oobject/tangible/survey_tool/survey_tool_inorganic.iff",
					"Chemical Survey Tool", "object/tangible/survey_tool/survey_tool_liquid.iff",
					"Flora Survey Tool", "object/tangible/survey_tool/survey_tool_lumber.iff",
					"Mineral Survey Tool", "object/tangible/survey_tool/survey_tool_mineral.iff",
					"Moisture Survey Tool", "object/tangible/survey_tool/survey_tool_moisture.iff",
					--"Organic Survey Tool", "object/tangible/survey_tool/survey_tool_organic.iff",
					"Solar Survey Tool", "object/tangible/survey_tool/survey_tool_solar.iff",
					"Wind Survey Tool", "object/tangible/survey_tool/survey_tool_wind.iff"
				}
				--"Repair Tools",
				--{
					--"Armor Repair", "object/tangible/crafting/station/armor_repair.iff",
					--"Clothing Repair", "object/tangible/crafting/station/clothing_repair.iff",
					--"Droid Repair", "object/tangible/crafting/station/droid_repair.iff",
					--"Structure Repair", "object/tangible/crafting/station/structure_repair.iff",
					--"Weapon Repair", "object/tangible/crafting/station/weapon_repair.iff"
				--}
			},
			"Weapons",
			{
				"Rifles",
				{
					"T21", "object/weapon/ranged/rifle/rifle_t21.iff",
					"Light Lightning Rifle", "object/weapon/ranged/rifle/rifle_lightning.iff"
				},
				"Pistols",
				{
					"Scatter", "object/weapon/ranged/pistol/pistol_scatter.iff"
				},
				"Carbines",
				{
					"DXR6", "object/weapon/ranged/carbine/carbine_dxr6.iff"
				},
				"Swords",
				{
					"Ryyk", "object/weapon/melee/sword/sword_blade_ryyk.iff"
				},
				"Poleam",
				{
					"Lance", "object/weapon/melee/polearm/lance_staff_metal.iff"
				}
			}
		}
	}
}

ObjectTemplates:addTemplate(object_tangible_terminal_terminal_character_builder, "object/tangible/terminal/terminal_character_builder.iff")
