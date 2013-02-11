faction_reward_type = {
	armor=1,
	weapon=2,
	uniform=3,
	furniture=4,
	container=5,
	terminal=6,
	installation=7,
	hireling=8,
}

faction_reward_data = {

	rebel_weapons_armor_list = {

		"armor_marine_backpack",
		"armor_marine_helmet",
		"armor_marine_chest_plate",
		"armor_marine_leggings",
		"armor_marine_boots",
		"armor_marine_bicep_l",
		"armor_marine_bicep_r",
		"carbine_laser",
		"pistol_scout_blaster",
		"lance_staff_metal",
		"rocket_launcher",
		"mine_drx",
		"mine_xg",
	},

	rebel_weapons_armor = {
		--armordir = "object/tangible/wearables/armor/marine/",
		--weapondir  = "object/tangible/wearables/armor/marine/",
		-- changed backpack location for troubleshooting purposes to generate an error
		armor_marine_backpack = { index=0, type=faction_reward_type.armor, display="@wearables_name:armor_marine_backpack", item="object/tangible/wearables/armor/marine/armor_marine_backpack.iff",cost=1500},
		armor_marine_bicep_l = { index=1, type=faction_reward_type.armor, display="@wearables_name:armor_marine_bicep_l", item="object/tangible/wearables/armor/marine/armor_marine_bicep_l.iff",cost=2000},
		armor_marine_bicep_r = { index=2, type=faction_reward_type.armor, display="@wearables_name:armor_marine_bicep_r", item="object/tangible/wearables/armor/marine/armor_marine_bicep_r.iff",cost=2000},
		armor_marine_boots = { index=3, type=faction_reward_type.armor, display="@wearables_name:armor_marine_boots", item="object/tangible/wearables/armor/marine/armor_marine_boots.iff",cost=3000},
		armor_marine_chest_plate = { index=4, type=faction_reward_type.armor, display="@wearables_name:armor_marine_chest_plate", item="object/tangible/wearables/armor/marine/armor_marine_chest_plate.iff",cost=4000},
		armor_marine_helmet = { index=5, type=faction_reward_type.armor, display="@wearables_name:armor_marine_helmet", item="object/tangible/wearables/armor/marine/armor_marine_helmet.iff",cost=3000},
		armor_marine_leggings = { index=6, type=faction_reward_type.armor, display="@wearables_name:armor_marine_leggings", item="object/tangible/wearables/armor/marine/armor_marine_leggings.iff",cost=3000},
		carbine_laser = { index=7, type=faction_reward_type.weapon, display="@weapon_name:carbine_laser", item="object/weapon/ranged/carbine/carbine_laser.iff", cost=1500},
		pistol_scout_blaster = { index=8, type=faction_reward_type.weapon, display="@weapon_name:pistol_scout_blaster", item="object/weapon/ranged/pistol/pistol_scout_blaster.iff", cost=1000},
		metal_staff = { index=9, type=faction_reward_type.weapon, display="@weapon_name:sword_02", item="object/weapon/ranged/melee/sword/sword_02.iff", cost=1000},
		rocket_launcher = { index=10, type=faction_reward_type.weapon, display="@weapon_name:rocket_launcher", item="object/weapon/ranged/heavy/heavy_rocket_launcher.iff", cost=5000},
		lance_staff_metal = { index=11, type=faction_reward_type.weapon, display="@weapon_name:lance_staff_metal", item="object/weapon/melee/polearm/lance_staff_metal.iff", cost=1000},
		mine_drx = { type=faction_reward_type.weapon, display="@weapon_name:mine_drx", item="object/weapon/mine/wp_mine_drx55.iff", cost=350},
		mine_xg = { type=faction_reward_type.weapon, display="@weapon_name:mine_xg", item="object/weapon/mine/wp_mine_xg.iff", cost=350},
		

	},

	imperial_weapons_armor_list = {
		"armor_stormtrooper_helmet",
		"armor_stormtrooper_chest_plate",
		"armor_stormtrooper_leggings",
		"armor_stormtrooper_boots",
		"armor_stormtrooper_bicep_l",
		"armor_stormtrooper_bicep_r",
		"armor_stormtrooper_bracer_l",
		"armor_stormtrooper_bracer_r",
		"armor_stormtrooper_gloves",
		"armor_stormtrooper_utility_belt",
		"carbine_e11",
		"pistol_power5",
		"sword_02",
		--"rocket_launcher",
		"mine_drx",
		"mine_xg",
	
	},


	imperial_weapons_armor = {
		--armordir = "object/tangible/wearables/armor/marine/",
		--weapondir  = "object/tangible/wearables/armor",
		--armor_stormtrooper_backpack = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_backpack", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_backpack.iff",cost=1500},
		armor_stormtrooper_bicep_l = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_bicep_l", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bicep_l.iff",cost=1400},
		armor_stormtrooper_bicep_r = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_bicep_r", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bicep_r.iff",cost=1400},
		armor_stormtrooper_boots = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_boots", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_boots.iff",cost=1400},
		armor_stormtrooper_chest_plate = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_chest_plate", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_chest_plate.iff", cost=4000},
		armor_stormtrooper_helmet = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_helmet", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_helmet.iff", cost=2100},
		armor_stormtrooper_leggings = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_leggings", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_leggings.iff",cost=2100},
		armor_stormtrooper_bracer_l = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_bracer_l", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bracer_l.iff",cost=1400},
		armor_stormtrooper_bracer_r = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_bracer_r", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bracer_r.iff",cost=1400},
		armor_stormtrooper_gloves = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_gloves", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_gloves.iff",cost=1400},
		armor_stormtrooper_utility_belt = { type=faction_reward_type.armor, display="@wearables_name:armor_stormtrooper_utility_belt", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_utility_belt.iff",cost=1400},
		pistol_power5 = { type=faction_reward_type.weapon, display="@weapon_name:pistol_power5", item="object/weapon/ranged/pistol/pistol_power5.iff", cost=700},
		carbine_e11 = { type=faction_reward_type.weapon, display="@weapon_name:carbine_e11", item="object/weapon/ranged/carbine/carbine_e11.iff", cost=1050},
		sword_02 = { type=faction_reward_type.weapon, display="@weapon_name:sword_02", item="object/weapon/melee/sword/sword_02.iff", cost=600},
		rocket_launcher = { type=faction_reward_type.weapon, display="@weapon_name:rocket_launcher", item="object/weapon/ranged/heavy/heavy_rocket_launcher.iff", cost=3500},
		mine_drx = { type=faction_reward_type.weapon, display="@weapon_name:mine_drx", item="object/weapon/mine/wp_mine_drx55.iff", cost=350},
		mine_xg = { type=faction_reward_type.weapon, display="@weapon_name:mine_xg", item="object/weapon/mine/wp_mine_xg.iff", cost=350},
		
	},
	imperial_uniform_list = {
		"boots_s14",
		"hat_imp_s01",
		"jacket_s03",
		 "pants_s15",
	
	},

	imperial_uniforms = {
		boots_s14 = { type=faction_reward_type.uniform, display="Boots", item="object/tangible/wearables/boots/boots_s14.iff", cost=140 },
		hat_imp_s01 = { type=faction_reward_type.uniform, display="@wearables_name:hat_imp_s01", item="object/tangible/wearables/hat/hat_imp_s01.iff", cost=140 },
		jacket_s03 = { type=faction_reward_type.uniform, display="Jacket", item="object/tangible/wearables/jacket/jacket_s03.iff", cost=140 },
		pants_s15  = { type=faction_reward_type.uniform, display="Pants", item="object/tangible/wearables/pants/pants_s15.iff", cost=140 },
		
	},

	rebel_furniture_list = {
		"tech_armoire",
		"tech_bookcase",
		"frn_cabinet",
		"chair_s01",
		"tech_chest",
		"frn_coffee_table",
		"frn_couch",
		"frn_end_table",
		"table_s1",
		"data_terminal_s1",
		"data_terminal_s2",
	},


	imperial_installations_list = {
		"hq_s01_pvp_imperial",
		"hq_s01_imperial",
		"hq_s02_pvp_imperial",
		"hq_s02_imperial",
		"hq_s03_pvp_imperial",
		"hq_s03_imperial",
		"hq_s04_pvp_imperial",
		"hq_s04_imperial",
		--"hq_s05_pvp_imperial",
		"turret_block_lg",
		"turret_block_med",
		"turret_block_sm",
		"turret_dish_sm",
		"turret_dish_med",
		"turret_dish_lg",
		"turret_tower_sm",
		"turret_tower_med",
		"turret_tower_lg",
		--"covert_detector_32m",
		"minefield_1x1",
	},

	imperial_installations = {
		hq_s01_pvp_imperial = {type=faction_reward_type.installation, display="@deed:hq_s01_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s01_pvp.iff",
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_imp_pvp.iff", cost=14000},
		
		hq_s01_imperial = {type=faction_reward_type.installation, display="@deed:hq_s01_imperial", item="object/tangible/deed/faction_perk/hq/hq_s01.iff",
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_imp.iff", cost=14000},
					
		hq_s02_pvp_imperial = {type=faction_reward_type.installation, display="@deed:hq_s02_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s02_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_imp_pvp.iff", cost=28000},
			
		hq_s02_imperial = {type=faction_reward_type.installation, display="@deed:hq_s02_imperial", item="object/tangible/deed/faction_perk/hq/hq_s02.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_imp.iff", cost=28000},
			
		hq_s03_pvp_imperial = {type=faction_reward_type.installation, display="@deed:hq_s03_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s03_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_imp_pvp.iff", cost=31500},

		hq_s03_imperial = {type=faction_reward_type.installation, display="@deed:hq_s03_imperial", item="object/tangible/deed/faction_perk/hq/hq_s03.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_imp.iff", cost=31500},
								
		hq_s04_pvp_imperial = {type=faction_reward_type.installation, display="@deed:hq_s04_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s04_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_imp_pvp.iff", cost=42000},
		
		hq_s04_imperial = {type=faction_reward_type.installation, display="@deed:hq_s04_imperial", item="object/tangible/deed/faction_perk/hq/hq_s04.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_imp.iff", cost=42000},
				
		hq_s05_pvp_imperial = {type=faction_reward_type.installation, display="@deed:hq_s05_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s05_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s05_imp_pvp.iff", cost=1},
			
		turret_block_lg = { type=faction_reward_type.installation, display="@deed:turret_block_lg", item="object/tangible/deed/faction_perk/turret/block_lg_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/block_lg.iff", cost=6300 },
		
		turret_block_med = { type=faction_reward_type.installation, display="@deed:turret_block_med", item="object/tangible/deed/faction_perk/turret/block_med_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/block_med.iff", cost=4200 },	
		
		turret_block_sm = { type=faction_reward_type.installation, display="@deed:turret_block_sm", item="object/tangible/deed/faction_perk/turret/block_sm_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/block_sm.iff", cost=1400 },
			
		turret_dish_sm = { type=faction_reward_type.installation, display="@deed:turret_dish_sm", item="object/tangible/deed/faction_perk/turret/dish_sm_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/dish_sm.iff", cost=1400 },
	
		--turret_dish_med = { type=faction_reward_type.installation, display="@deed:turret_dish_med", item="object/tangible/deed/faction_perk/turret/dish_med_deed.iff",
		--	generatedObjectTemplate="object/installation/faction_perk/turret/dish_med.iff", cost=4200 },	
		
		turret_dish_lg = { type=faction_reward_type.installation, display="@deed:turret_dish_lg", item="object/tangible/deed/faction_perk/turret/dish_lg_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/dish_lg.iff", cost=6300 },
			
		turret_tower_sm = { type=faction_reward_type.installation, display="@deed:turret_tower_sm", item="object/tangible/deed/faction_perk/turret/tower_sm_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/tower_sm.iff", cost=1400 },
	
		turret_tower_med = { type=faction_reward_type.installation, display="@deed:turret_tower_med", item="object/tangible/deed/faction_perk/turret/tower_med_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/tower_med.iff", cost=4200 },	
		
		turret_tower_lg = { type=faction_reward_type.installation, display="@deed:turret_tower_lg", item="object/tangible/deed/faction_perk/turret/tower_lg_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/tower_lg.iff", cost=6300 },
		
		covert_detector_32m = { type=faction_reward_type.installation, display="@deed:covert_detector_32m", item="object/tangible/deed/faction_perk/covert_detector/detector_32m_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/covert_detector/detector_base.iff", cost=3000 },
		
		minefield_1x1 = { type=faction_reward_type.installation, display="@deed:minefield_1x1", item="object/tangible/deed/faction_perk/minefield/field_1x1_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/minefield/field_1x1.iff", cost=350 },
	},
	
	rebel_installations_list = {
		"hq_s01_pvp_rebel",
		"hq_s01_rebel",
		"hq_s02_pvp_rebel",
		"hq_s02_rebel",
		"hq_s03_pvp_rebel",
		"hq_s03_rebel",
		"hq_s04_pvp_rebel",
		"hq_s04_rebel",
		--"hq_s05_pvp_rebel",
		"turret_block_lg",
		"turret_block_med",
		"turret_block_sm",
		"turret_dish_sm",
		"turret_dish_med",
		"turret_dish_lg",
		"turret_tower_sm",
		"turret_tower_med",
		"turret_tower_lg",
		"minefield_1x1",
	}, 
	
	rebel_installations = {
		hq_s01_pvp_rebel = {type=faction_reward_type.installation, display="@deed:hq_s01_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s01_pvp.iff",
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_rebel_pvp.iff", cost=20000},
		
		hq_s01_rebel = {type=faction_reward_type.installation, display="@deed:hq_s01_rebel", item="object/tangible/deed/faction_perk/hq/hq_s01.iff",
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_rebel.iff", cost=20000},
		
		hq_s02_pvp_rebel = {type=faction_reward_type.installation, display="@deed:hq_s02_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s02_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_rebel_pvp.iff", cost=40000},
		
		hq_s02_rebel = {type=faction_reward_type.installation, display="@deed:hq_s02_rebel", item="object/tangible/deed/faction_perk/hq/hq_s02.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_rebel.iff", cost=40000},
					
		hq_s03_pvp_rebel = {type=faction_reward_type.installation, display="@deed:hq_s03_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s03_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_rebel_pvp.iff", cost=45000},
	
		hq_s03_rebel = {type=faction_reward_type.installation, display="@deed:hq_s03_rebel", item="object/tangible/deed/faction_perk/hq/hq_s03.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_rebel.iff", cost=45000},
						
		hq_s04_rebel = {type=faction_reward_type.installation, display="@deed:hq_s04_rebel", item="object/tangible/deed/faction_perk/hq/hq_s04.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_rebel.iff", cost=60000},
			
		hq_s04_pvp_rebel = {type=faction_reward_type.installation, display="@deed:hq_s04_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s04_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_rebel_pvp.iff", cost=60000},
		
		hq_s05_pvp_rebel = {type=faction_reward_type.installation, display="@deed:hq_s05_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s05_pvp.iff", 
			generatedObjectTemplate="object/building/faction_perk/hq/hq_s05_rebel_pvp.iff", cost=60000},
					
		turret_block_lg = { type=faction_reward_type.installation, display="@deed:turret_block_lg", item="object/tangible/deed/faction_perk/turret/block_lg_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/block_lg.iff", cost=6300 },
		
		turret_block_med = { type=faction_reward_type.installation, display="@deed:turret_block_med", item="object/tangible/deed/faction_perk/turret/block_med_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/block_med.iff", cost=4200 },	
		
		turret_block_sm = { type=faction_reward_type.installation, display="@deed:turret_block_sm", item="object/tangible/deed/faction_perk/turret/block_sm_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/block_sm.iff", cost=1400 },
			
		turret_dish_sm = { type=faction_reward_type.installation, display="@deed:turret_dish_sm", item="object/tangible/deed/faction_perk/turret/dish_sm_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/dish_sm.iff", cost=1400 },
	
		--turret_dish_med = { type=faction_reward_type.installation, display="@deed:turret_dish_med", item="object/tangible/deed/faction_perk/turret/dish_med_deed.iff",
		--	generatedObjectTemplate="object/installation/faction_perk/turret/dish_med.iff", cost=4200 },	
		
		turret_dish_lg = { type=faction_reward_type.installation, display="@deed:turret_dish_lg", item="object/tangible/deed/faction_perk/turret/dish_lg_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/dish_lg.iff", cost=6300 },
			
		turret_tower_sm = { type=faction_reward_type.installation, display="@deed:turret_tower_sm", item="object/tangible/deed/faction_perk/turret/tower_sm_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/tower_sm.iff", cost=1400 },
	
		turret_tower_med = { type=faction_reward_type.installation, display="@deed:turret_tower_med", item="object/tangible/deed/faction_perk/turret/tower_med_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/tower_med.iff", cost=4200 },	
		
		turret_tower_lg = { type=faction_reward_type.installation, display="@deed:turret_tower_lg", item="object/tangible/deed/faction_perk/turret/tower_lg_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/turret/tower_lg.iff", cost=6300 },
		
		covert_detector_32m = { type=faction_reward_type.installation, display="@deed:covert_detector_32m", item="object/tangible/deed/faction_perk/covert_detector/detector_32m_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/covert_detector/detector_base.iff", cost=3000 },
		
		minefield_1x1 = { type=faction_reward_type.installation, display="@deed:minefield_1x1", item="object/tangible/deed/faction_perk/minefield/field_1x1_deed.iff",
			generatedObjectTemplate="object/installation/faction_perk/minefield/field_1x1.iff", cost=5000 },
	},
	
	rebel_furniture = {
	
		data_terminal_s1 = { type=faction_reward_type.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s1.iff",cost=850},
		data_terminal_s2 = { type=faction_reward_type.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s2.iff",cost=1000},
		--frn_table = { type=faction_reward_type.furniture, display="@frn_n:frn_table", item="object/tangible/furniture/imperial/table_s1.iff",cost=1400},
		tech_armoire = { type=faction_reward_type.container, display="@container_name:tech_armoire", item="object/tangible/furniture/technical/armoire_s01.iff", cost=1400},
		tech_bookcase = { type=faction_reward_type.container, display="@container_name:tech_bookcase", item="object/tangible/furniture/technical/bookcase_s01.iff", cost=1400},
		frn_cabinet = { type=faction_reward_type.furniture, display="@frn_d:frn_cabinet", item="object/tangible/furniture/technical/cabinet_s01.iff", cost=200},
		tech_chair = { type=faction_reward_type.furniture, display="@frn_d:frn_chair", item="object/tangible/furniture/technical/chair_s01.iff", 1000},
		tech_chest =  { type=faction_reward_type.container, display="@container_name:tech_chest", item="object/tangible/furniture/technical/chest_s01.iff", cost=1000},
		frn_coffee_table = { type=faction_reward_type.furniture, display="@frn_d:frn_coffee_table", item="object/tangible/furniture/technical/coffee_table_s01.iff", cost=1200},
		frn_couch = { type=faction_reward_type.furniture, display="@frn_d:frn_couch", item="object/tangible/furniture/technical/couch_s01.iff", cost=1200},
		frn_end_table = { type=faction_reward_type.furniture, display="@frn_d:frn_end_table", item="object/tangible/furniture/technical/end_table_s01.iff", cost=1000},

	},

	imperial_furniture_list = {
		"frn_table",
		"tech_armoire",
		"tech_bookcase",
		"frn_cabinet",
		"chair_s01",
		"tech_chest",
		"frn_coffee_table",
		"frn_couch",
		"frn_end_table",
		"table_s1",
		"data_terminal_s1",
		"data_terminal_s2",
		"data_terminal_s3",
		"data_terminal_s4",
	},

	imperial_furniture = {
	
		data_terminal_s1 = { type=faction_reward_type.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s1.iff",cost=560},
		data_terminal_s2 = { type=faction_reward_type.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s2.iff",cost=700},
		data_terminal_s3 = { type=faction_reward_type.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s3.iff",cost=840},
		data_terminal_s4 = { type=faction_reward_type.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s4.iff",cost=980},
		frn_table = { type=faction_reward_type.furniture, display="@frn_n:frn_table", item="object/tangible/furniture/imperial/table_s1.iff",cost=700},
		tech_armoire = { type=faction_reward_type.container, display="@container_name:tech_armoire", item="object/tangible/furniture/technical/armoire_s01.iff", cost=980},
		tech_bookcase = { type=faction_reward_type.container, display="@container_name:tech_bookcase", item="object/tangible/furniture/technical/bookcase_s01.iff", cost=980},
		frn_cabinet = { type=faction_reward_type.furniture, display="@frn_d:frn_cabinet", item="object/tangible/furniture/technical/cabinet_s01.iff", cost=200},
		tech_chair = { type=faction_reward_type.furniture, display="@frn_d:frn_chair", item="object/tangible/furniture/technical/chair_s01.iff", 700},
		tech_chest =  { type=faction_reward_type.container, display="@container_name:tech_chest", item="object/tangible/furniture/technical/chest_s01.iff", cost=700},
		frn_coffee_table = { type=faction_reward_type.furniture, display="@frn_d:frn_coffee_table", item="object/tangible/furniture/technical/coffee_table_s01.iff", cost=700},
		frn_couch = { type=faction_reward_type.furniture, display="@frn_d:frn_couch", item="object/tangible/furniture/technical/couch_s01.iff", cost=1050},
		frn_end_table = { type=faction_reward_type.furniture, display="@frn_d:frn_end_table", item="object/tangible/furniture/technical/end_table_s01.iff", cost=700},

	},

	imperial_hireling_list = {
		--"assaulttrooper",
		--"atst",
	
	},
	
	imperial_hireling = {
		
	},
	
	rebel_hireling_list = {
		--"Comms Operator",
		--"Senior SpecForce Guerilla",
		--"marine",
	},
	
	rebel_hirelings = {
	
	}


}