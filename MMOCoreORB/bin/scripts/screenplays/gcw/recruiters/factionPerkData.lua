factionRewardType = {
	armor = 1,
	weapon = 2,
	uniform = 3,
	furniture = 4,
	container = 5,
	terminal = 6,
	installation = 7,
	hireling = 8,
}

rebelRewardData = {
	weaponsArmorList = {
		"armor_marine_backpack", "armor_marine_helmet", "armor_marine_chest_plate", "armor_marine_leggings", "armor_marine_boots", "armor_marine_bicep_l",
		"armor_marine_bicep_r", "carbine_laser", "pistol_scout_blaster", "lance_staff_metal", "rocket_launcher", "mine_drx", "mine_xg",
	},

	weaponsArmor = {
		armor_marine_backpack = { index=0, type=factionRewardType.armor, display="@wearables_name:armor_marine_backpack", item="object/tangible/wearables/armor/marine/armor_marine_backpack.iff",cost=1500},
		armor_marine_bicep_l = { index=1, type=factionRewardType.armor, display="@wearables_name:armor_marine_bicep_l", item="object/tangible/wearables/armor/marine/armor_marine_bicep_l.iff",cost=2000},
		armor_marine_bicep_r = { index=2, type=factionRewardType.armor, display="@wearables_name:armor_marine_bicep_r", item="object/tangible/wearables/armor/marine/armor_marine_bicep_r.iff",cost=2000},
		armor_marine_boots = { index=3, type=factionRewardType.armor, display="@wearables_name:armor_marine_boots", item="object/tangible/wearables/armor/marine/armor_marine_boots.iff",cost=3000},
		armor_marine_chest_plate = { index=4, type=factionRewardType.armor, display="@wearables_name:armor_marine_chest_plate", item="object/tangible/wearables/armor/marine/armor_marine_chest_plate.iff",cost=4000},
		armor_marine_helmet = { index=5, type=factionRewardType.armor, display="@wearables_name:armor_marine_helmet", item="object/tangible/wearables/armor/marine/armor_marine_helmet.iff",cost=3000},
		armor_marine_leggings = { index=6, type=factionRewardType.armor, display="@wearables_name:armor_marine_leggings", item="object/tangible/wearables/armor/marine/armor_marine_leggings.iff",cost=3000},
		carbine_laser = { index=7, type=factionRewardType.weapon, display="@weapon_name:carbine_laser", item="object/weapon/ranged/carbine/carbine_laser.iff", cost=1500},
		pistol_scout_blaster = { index=8, type=factionRewardType.weapon, display="@weapon_name:pistol_scout_blaster", item="object/weapon/ranged/pistol/pistol_scout_blaster.iff", cost=1000},
		metal_staff = { index=9, type=factionRewardType.weapon, display="@weapon_name:sword_02", item="object/weapon/ranged/melee/sword/sword_02.iff", cost=1000},
		rocket_launcher = { index=10, type=factionRewardType.weapon, display="@weapon_name:rocket_launcher", item="object/weapon/ranged/heavy/heavy_rocket_launcher.iff", cost=5000},
		lance_staff_metal = { index=11, type=factionRewardType.weapon, display="@weapon_name:lance_staff_metal", item="object/weapon/melee/polearm/lance_staff_metal.iff", cost=1000},
		mine_drx = { type=factionRewardType.weapon, display="@weapon_name:mine_drx", item="object/weapon/mine/wp_mine_drx55.iff", cost=350},
		mine_xg = { type=factionRewardType.weapon, display="@weapon_name:mine_xg", item="object/weapon/mine/wp_mine_xg.iff", cost=350},
	},

	installationsList = {
		"hq_s01_pvp_rebel", "hq_s01_rebel", "hq_s02_pvp_rebel", "hq_s02_rebel", "hq_s03_pvp_rebel", "hq_s03_rebel", "hq_s04_pvp_rebel", "hq_s04_rebel", --"hq_s05_pvp_rebel",
		"turret_block_lg", "turret_block_med", "turret_block_sm", "turret_dish_sm", "turret_dish_lg", "turret_tower_sm", "turret_tower_med", "turret_tower_lg",
		"minefield_1x1",
	},

	installations = {
		hq_s01_pvp_rebel = {type=factionRewardType.installation, display="@deed:hq_s01_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s01_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_rebel_pvp.iff", cost=20000, bonus={"hq_s01_rebel","hq_s01_rebel"} },
		hq_s01_rebel = {type=factionRewardType.installation, display="@deed:hq_s01_rebel", item="object/tangible/deed/faction_perk/hq/hq_s01.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_rebel.iff", cost=10000},
		hq_s02_pvp_rebel = {type=factionRewardType.installation, display="@deed:hq_s02_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s02_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_rebel_pvp.iff", cost=40000, bonus={"hq_s02_rebel","hq_s02_rebel"} },
		hq_s02_rebel = {type=factionRewardType.installation, display="@deed:hq_s02_rebel", item="object/tangible/deed/faction_perk/hq/hq_s02.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_rebel.iff", cost=20000},
		hq_s03_pvp_rebel = {type=factionRewardType.installation, display="@deed:hq_s03_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s03_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_rebel_pvp.iff", cost=45000, bonus={"hq_s03_rebel","hq_s03_rebel"} },
		hq_s03_rebel = {type=factionRewardType.installation, display="@deed:hq_s03_rebel", item="object/tangible/deed/faction_perk/hq/hq_s03.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_rebel.iff", cost=22500},
		hq_s04_pvp_rebel = {type=factionRewardType.installation, display="@deed:hq_s04_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s04_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_rebel_pvp.iff", cost=60000, bonus={"hq_s04_rebel","hq_s04_rebel"} },
		hq_s04_rebel = {type=factionRewardType.installation, display="@deed:hq_s04_rebel", item="object/tangible/deed/faction_perk/hq/hq_s04.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_rebel.iff", cost=30000},
		hq_s05_pvp_rebel = {type=factionRewardType.installation, display="@deed:hq_s05_pvp_rebel", item="object/tangible/deed/faction_perk/hq/hq_s05_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s05_rebel_pvp.iff", cost=60000},
		turret_block_lg = { type=factionRewardType.installation, display="@deed:turret_block_lg", item="object/tangible/deed/faction_perk/turret/block_lg_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/block_lg.iff", cost=6300 },
		turret_block_med = { type=factionRewardType.installation, display="@deed:turret_block_med", item="object/tangible/deed/faction_perk/turret/block_med_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/block_med.iff", cost=4200 },
		turret_block_sm = { type=factionRewardType.installation, display="@deed:turret_block_sm", item="object/tangible/deed/faction_perk/turret/block_sm_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/block_sm.iff", cost=1400 },
		turret_dish_sm = { type=factionRewardType.installation, display="@deed:turret_dish_sm", item="object/tangible/deed/faction_perk/turret/dish_sm_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/dish_sm.iff", cost=1400 },
		turret_dish_lg = { type=factionRewardType.installation, display="@deed:turret_dish_lg", item="object/tangible/deed/faction_perk/turret/dish_lg_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/dish_lg.iff", cost=6300 },
		turret_tower_sm = { type=factionRewardType.installation, display="@deed:turret_tower_sm", item="object/tangible/deed/faction_perk/turret/tower_sm_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/tower_sm.iff", cost=1400 },
		turret_tower_med = { type=factionRewardType.installation, display="@deed:turret_tower_med", item="object/tangible/deed/faction_perk/turret/tower_med_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/tower_med.iff", cost=4200 },
		turret_tower_lg = { type=factionRewardType.installation, display="@deed:turret_tower_lg", item="object/tangible/deed/faction_perk/turret/tower_lg_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/tower_lg.iff", cost=6300 },
		covert_detector_32m = { type=factionRewardType.installation, display="@deed:covert_detector_32m", item="object/tangible/deed/faction_perk/covert_detector/detector_32m_deed.iff", generatedObjectTemplate="object/installation/faction_perk/covert_detector/detector_base.iff", cost=3000 },
		minefield_1x1 = { type=factionRewardType.installation, display="@deed:minefield_1x1", item="object/tangible/deed/faction_perk/minefield/field_1x1_deed.iff", generatedObjectTemplate="object/installation/faction_perk/minefield/field_1x1.iff", cost=5000 },
	},

	furnitureList = {
		"tech_armoire", "tech_bookcase", "frn_cabinet", "tech_chair", "tech_chest", "frn_coffee_table", "frn_couch", "frn_end_table"
	},

	furniture = {
		tech_armoire = { type=factionRewardType.container, display="@container_name:tech_armoire", item="object/tangible/furniture/technical/armoire_s01.iff", cost=1400},
		tech_bookcase = { type=factionRewardType.container, display="@container_name:tech_bookcase", item="object/tangible/furniture/technical/bookcase_s01.iff", cost=1400},
		frn_cabinet = { type=factionRewardType.furniture, display="@frn_n:frn_cabinet", item="object/tangible/furniture/technical/cabinet_s01.iff", cost=200},
		tech_chair = { type=factionRewardType.furniture, display="@frn_n:frn_chair", item="object/tangible/furniture/technical/chair_s01.iff", cost=1000},
		tech_chest =  { type=factionRewardType.container, display="@container_name:tech_chest", item="object/tangible/furniture/technical/chest_s01.iff", cost=1000},
		frn_coffee_table = { type=factionRewardType.furniture, display="@frn_n:frn_coffee_table", item="object/tangible/furniture/technical/coffee_table_s01.iff", cost=1200},
		frn_couch = { type=factionRewardType.furniture, display="@frn_n:frn_couch", item="object/tangible/furniture/technical/couch_s01.iff", cost=1200},
		frn_end_table = { type=factionRewardType.furniture, display="@frn_n:frn_end_table", item="object/tangible/furniture/technical/end_table_s01.iff", cost=1000},
	},

	hirelingList = {
		"rebel_trooper", "senior_specforce_heavy_weapons_specialist", "senior_specforce_infiltrator", "senior_specforce_marine", "senior_specforce_pathfinder", "senior_specforce_technician",
		"senior_specforce_urban_guerrilla", "senior_specforce_wilderness_fighter", "specforce_heavy_weapons_specialist", "specforce_infiltrator", "specforce_interrogator", "specforce_marine",
		"specforce_procurement_specialist", "specforce_technician",	"specforce_wilderness_operative", "rebel_specforce_guerrilla",
	},

	hirelings = {
		rebel_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:rebel_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="rebel_trooper", cost=150},
		senior_specforce_heavy_weapons_specialist = { type=factionRewardType.hireling, display="@mob/creature_names:senior_specforce_heavy_weapons_specialist", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="senior_specforce_heavy_weapons_specialist", cost=450},
		senior_specforce_infiltrator = { type=factionRewardType.hireling, display="@mob/creature_names:senior_specforce_infiltrator", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="senior_specforce_infiltrator", cost=450},
		senior_specforce_marine = { type=factionRewardType.hireling, display="@mob/creature_names:senior_specforce_marine", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="senior_specforce_marine", cost=450},
		senior_specforce_pathfinder = { type=factionRewardType.hireling, display="@mob/creature_names:senior_specforce_pathfinder", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="senior_specforce_pathfinder", cost=450},
		senior_specforce_technician = { type=factionRewardType.hireling, display="@mob/creature_names:senior_specforce_technician", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="senior_specforce_technician", cost=450},
		senior_specforce_urban_guerrilla = { type=factionRewardType.hireling, display="@mob/creature_names:senior_specforce_guerrilla", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="senior_specforce_urban_guerrilla", cost=450},
		senior_specforce_wilderness_fighter = { type=factionRewardType.hireling, display="@mob/creature_names:senior_specforce_wilderness_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="senior_specforce_wilderness_fighter", cost=450},
		specforce_heavy_weapons_specialist = { type=factionRewardType.hireling, display="@mob/creature_names:specforce_heavy_weapons_specialist", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="specforce_heavy_weapons_specialist", cost=375},
		specforce_infiltrator = { type=factionRewardType.hireling, display="@mob/creature_names:specforce_infiltrator", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="specforce_infiltrator", cost=375},
		specforce_interrogator = { type=factionRewardType.hireling, display="@mob/creature_names:specforce_interrogator", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="specforce_interrogator", cost=375},
		specforce_marine = { type=factionRewardType.hireling, display="@mob/creature_names:specforce_marine", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="specforce_marine", cost=375},
		specforce_procurement_specialist = { type=factionRewardType.hireling, display="@mob/creature_names:specforce_procurement_specialist", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="specforce_procurement_specialist", cost=375},
		specforce_technician = { type=factionRewardType.hireling, display="@mob/creature_names:specforce_technician", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="specforce_technician", cost=375},
		specforce_wilderness_operative = { type=factionRewardType.hireling, display="@mob/creature_names:specforce_wilderness_operative", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="specforce_wilderness_operative", cost=375},
		rebel_specforce_guerrilla = { type=factionRewardType.hireling, display="@mob/creature_names:rebel_specforce_guerrilla", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="rebel_specforce_urban_guerrilla", cost=375},
	}
}

imperialRewardData = {
	weaponsArmorList = {
		"armor_stormtrooper_helmet", "armor_stormtrooper_chest_plate", "armor_stormtrooper_leggings", "armor_stormtrooper_boots", "armor_stormtrooper_bicep_l", "armor_stormtrooper_bicep_r",
		"armor_stormtrooper_bracer_l", "armor_stormtrooper_bracer_r", "armor_stormtrooper_gloves", "armor_stormtrooper_utility_belt", "carbine_e11", "pistol_power5", "sword_02",
		"rocket_launcher", "mine_drx", "mine_xg",
	},

	weaponsArmor = {
		--armor_stormtrooper_backpack = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_backpack", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_backpack.iff",cost=1500},
		armor_stormtrooper_bicep_l = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_bicep_l", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bicep_l.iff",cost=1400},
		armor_stormtrooper_bicep_r = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_bicep_r", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bicep_r.iff",cost=1400},
		armor_stormtrooper_boots = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_boots", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_boots.iff",cost=1400},
		armor_stormtrooper_chest_plate = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_chest_plate", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_chest_plate.iff", cost=4000},
		armor_stormtrooper_helmet = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_helmet", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_helmet.iff", cost=2100},
		armor_stormtrooper_leggings = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_leggings", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_leggings.iff",cost=2100},
		armor_stormtrooper_bracer_l = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_bracer_l", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bracer_l.iff",cost=1400},
		armor_stormtrooper_bracer_r = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_bracer_r", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_bracer_r.iff",cost=1400},
		armor_stormtrooper_gloves = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_gloves", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_gloves.iff",cost=1400},
		armor_stormtrooper_utility_belt = { type=factionRewardType.armor, display="@wearables_name:armor_stormtrooper_utility_belt", item="object/tangible/wearables/armor/stormtrooper/armor_stormtrooper_utility_belt.iff",cost=1400},
		pistol_power5 = { type=factionRewardType.weapon, display="@weapon_name:pistol_power5", item="object/weapon/ranged/pistol/pistol_power5.iff", cost=700},
		carbine_e11 = { type=factionRewardType.weapon, display="@weapon_name:carbine_e11", item="object/weapon/ranged/carbine/carbine_e11.iff", cost=1050},
		sword_02 = { type=factionRewardType.weapon, display="@weapon_name:sword_02", item="object/weapon/melee/sword/sword_02.iff", cost=600},
		rocket_launcher = { type=factionRewardType.weapon, display="@weapon_name:rocket_launcher", item="object/weapon/ranged/heavy/heavy_rocket_launcher.iff", cost=3500},
		mine_drx = { type=factionRewardType.weapon, display="@weapon_name:mine_drx", item="object/weapon/mine/wp_mine_drx55.iff", cost=350},
		mine_xg = { type=factionRewardType.weapon, display="@weapon_name:mine_xg", item="object/weapon/mine/wp_mine_xg.iff", cost=350},
	},

	uniformList = {
		"boots_s14", "hat_imp_s01", "jacket_s03", "pants_s15",
	},

	uniforms = {
		boots_s14 = { type=factionRewardType.uniform, display="@wearables_name:boots_s14", item="object/tangible/wearables/boots/boots_s14.iff", cost=140 },
		hat_imp_s01 = { type=factionRewardType.uniform, display="@wearables_name:hat_imp_s01", item="object/tangible/wearables/hat/hat_imp_s01.iff", cost=140 },
		jacket_s03 = { type=factionRewardType.uniform, display="@wearables_name:jacket_s03", item="object/tangible/wearables/jacket/jacket_s03.iff", cost=140 },
		pants_s15  = { type=factionRewardType.uniform, display="@wearables_name:pants_s15", item="object/tangible/wearables/pants/pants_s15.iff", cost=140 },
	},

	installationsList = {
		"hq_s01_pvp_imperial", "hq_s01_imperial", "hq_s02_pvp_imperial", "hq_s02_imperial", "hq_s03_pvp_imperial", "hq_s03_imperial", "hq_s04_pvp_imperial", "hq_s04_imperial",
		--"hq_s05_pvp_imperial",
		"turret_block_lg", "turret_block_med", "turret_block_sm", "turret_dish_sm", "turret_dish_lg", "turret_tower_sm", "turret_tower_med", "turret_tower_lg",
		--"covert_detector_32m",
		"minefield_1x1",
	},

	installations = {
		hq_s01_pvp_imperial = {type=factionRewardType.installation, display="@deed:hq_s01_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s01_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_imp_pvp.iff", cost=14000, bonus={"hq_s01_imperial","hq_s01_imperial"} },
		hq_s01_imperial = {type=factionRewardType.installation, display="@deed:hq_s01_imperial", item="object/tangible/deed/faction_perk/hq/hq_s01.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s01_imp.iff", cost=7000},
		hq_s02_pvp_imperial = {type=factionRewardType.installation, display="@deed:hq_s02_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s02_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_imp_pvp.iff", cost=28000, bonus={"hq_s02_imperial","hq_s02_imperial"}},
		hq_s02_imperial = {type=factionRewardType.installation, display="@deed:hq_s02_imperial", item="object/tangible/deed/faction_perk/hq/hq_s02.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s02_imp.iff", cost=14000},
		hq_s03_pvp_imperial = {type=factionRewardType.installation, display="@deed:hq_s03_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s03_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_imp_pvp.iff", cost=31500, bonus={"hq_s03_imperial","hq_s03_imperial"}},
		hq_s03_imperial = {type=factionRewardType.installation, display="@deed:hq_s03_imperial", item="object/tangible/deed/faction_perk/hq/hq_s03.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s03_imp.iff", cost=15750},
		hq_s04_pvp_imperial = {type=factionRewardType.installation, display="@deed:hq_s04_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s04_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_imp_pvp.iff", cost=42000, bonus={"hq_s04_imperial","hq_s04_imperial"}},
		hq_s04_imperial = {type=factionRewardType.installation, display="@deed:hq_s04_imperial", item="object/tangible/deed/faction_perk/hq/hq_s04.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s04_imp.iff", cost=21000 },
		hq_s05_pvp_imperial = {type=factionRewardType.installation, display="@deed:hq_s05_pvp_imperial", item="object/tangible/deed/faction_perk/hq/hq_s05_pvp.iff", generatedObjectTemplate="object/building/faction_perk/hq/hq_s05_imp_pvp.iff", cost=1},
		turret_block_lg = { type=factionRewardType.installation, display="@deed:turret_block_lg", item="object/tangible/deed/faction_perk/turret/block_lg_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/block_lg.iff", cost=6300 },
		turret_block_med = { type=factionRewardType.installation, display="@deed:turret_block_med", item="object/tangible/deed/faction_perk/turret/block_med_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/block_med.iff", cost=4200 },
		turret_block_sm = { type=factionRewardType.installation, display="@deed:turret_block_sm", item="object/tangible/deed/faction_perk/turret/block_sm_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/block_sm.iff", cost=1400 },
		turret_dish_sm = { type=factionRewardType.installation, display="@deed:turret_dish_sm", item="object/tangible/deed/faction_perk/turret/dish_sm_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/dish_sm.iff", cost=1400 },
		turret_dish_lg = { type=factionRewardType.installation, display="@deed:turret_dish_lg", item="object/tangible/deed/faction_perk/turret/dish_lg_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/dish_lg.iff", cost=6300 },
		turret_tower_sm = { type=factionRewardType.installation, display="@deed:turret_tower_sm", item="object/tangible/deed/faction_perk/turret/tower_sm_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/tower_sm.iff", cost=1400 },
		turret_tower_med = { type=factionRewardType.installation, display="@deed:turret_tower_med", item="object/tangible/deed/faction_perk/turret/tower_med_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/tower_med.iff", cost=4200 },
		turret_tower_lg = { type=factionRewardType.installation, display="@deed:turret_tower_lg", item="object/tangible/deed/faction_perk/turret/tower_lg_deed.iff", generatedObjectTemplate="object/installation/faction_perk/turret/tower_lg.iff", cost=6300 },
		covert_detector_32m = { type=factionRewardType.installation, display="@deed:covert_detector_32m", item="object/tangible/deed/faction_perk/covert_detector/detector_32m_deed.iff", generatedObjectTemplate="object/installation/faction_perk/covert_detector/detector_base.iff", cost=3000 },
		minefield_1x1 = { type=factionRewardType.installation, display="@deed:minefield_1x1", item="object/tangible/deed/faction_perk/minefield/field_1x1_deed.iff", generatedObjectTemplate="object/installation/faction_perk/minefield/field_1x1.iff", cost=350 },
	},

	furnitureList = {
		"data_terminal_s1", "data_terminal_s2", "data_terminal_s3", "data_terminal_s4", "frn_table", "tech_armoire", "tech_bookcase", "frn_cabinet", "tech_chair",
		"tech_chest", "frn_coffee_table", "frn_couch", "frn_end_table"
	},

	furniture = {
		data_terminal_s1 = { type=factionRewardType.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s1.iff",cost=560},
		data_terminal_s2 = { type=factionRewardType.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s2.iff",cost=700},
		data_terminal_s3 = { type=factionRewardType.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s3.iff",cost=840},
		data_terminal_s4 = { type=factionRewardType.terminal, display="@frn_n:frn_data_terminal", item="object/tangible/furniture/imperial/data_terminal_s4.iff",cost=980},
		frn_table = { type=factionRewardType.furniture, display="@frn_n:frn_table", item="object/tangible/furniture/imperial/table_s1.iff",cost=700},
		tech_armoire = { type=factionRewardType.container, display="@container_name:tech_armoire", item="object/tangible/furniture/technical/armoire_s01.iff", cost=980},
		tech_bookcase = { type=factionRewardType.container, display="@container_name:tech_bookcase", item="object/tangible/furniture/technical/bookcase_s01.iff", cost=980},
		frn_cabinet = { type=factionRewardType.furniture, display="@frn_n:frn_cabinet", item="object/tangible/furniture/technical/cabinet_s01.iff", cost=200},
		tech_chair = { type=factionRewardType.furniture, display="@frn_n:frn_chair", item="object/tangible/furniture/technical/chair_s01.iff", cost=700},
		tech_chest =  { type=factionRewardType.container, display="@container_name:tech_chest", item="object/tangible/furniture/technical/chest_s01.iff", cost=700},
		frn_coffee_table = { type=factionRewardType.furniture, display="@frn_n:frn_coffee_table", item="object/tangible/furniture/technical/coffee_table_s01.iff", cost=700},
		frn_couch = { type=factionRewardType.furniture, display="@frn_n:frn_couch", item="object/tangible/furniture/technical/couch_s01.iff", cost=1050},
		frn_end_table = { type=factionRewardType.furniture, display="@frn_n:frn_end_table", item="object/tangible/furniture/technical/end_table_s01.iff", cost=700},
	},

	hirelingList = {
		"assault_trooper", "bombardier", "command_security_guard", "compforce_trooper", "dark_trooper", "gunner", "imperial_private", "imperial_trooper", "sand_trooper", "scout_trooper",
		"storm_commando", "stormtrooper", "stormtrooper_bombardier", "stormtrooper_medic", "stormtrooper_rifleman", "stormtrooper_sniper", "swamp_trooper", "at_st"
	},

	hirelings = {
		assault_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:assault_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="assault_trooper", cost=420},
		bombardier = { type=factionRewardType.hireling, display="@mob/creature_names:bombardier", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="bombardier", cost=105},
		command_security_guard = { type=factionRewardType.hireling, display="@mob/creature_names:command_security_guard", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="command_security_guard", cost=105},
		compforce_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:compforce_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="compforce_trooper", cost=367},
		dark_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:dark_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="dark_trooper", cost=2100},
		gunner = { type=factionRewardType.hireling, display="@mob/creature_names:gunner", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="gunner", cost=105},
		imperial_private = { type=factionRewardType.hireling, display="@mob/creature_names:imperial_private", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="imperial_private", cost=105},
		imperial_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:imperial_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="imperial_trooper", cost=105},
		sand_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:sand_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="sand_trooper", cost=420},
		scout_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:scout_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="scout_trooper", cost=420},
		storm_commando = { type=factionRewardType.hireling, display="@mob/creature_names:storm_commando", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="storm_commando", cost=462},
		stormtrooper = { type=factionRewardType.hireling, display="@mob/creature_names:stormtrooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="stormtrooper", cost=420},
		stormtrooper_bombardier = { type=factionRewardType.hireling, display="@mob/creature_names:stormtrooper_bombardier", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="stormtrooper_bombardier", cost=420},
		stormtrooper_medic = { type=factionRewardType.hireling, display="@mob/creature_names:stormtrooper_medic", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="stormtrooper_medic", cost=420},
		stormtrooper_rifleman = { type=factionRewardType.hireling, display="@mob/creature_names:stormtrooper_rifleman", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="stormtrooper_rifleman", cost=420},
		stormtrooper_sniper = { type=factionRewardType.hireling, display="@mob/creature_names:stormtrooper_sniper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="stormtrooper_sniper", cost=420},
		swamp_trooper = { type=factionRewardType.hireling, display="@mob/creature_names:swamp_trooper", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="swamp_trooper", cost=420},
		at_st = { type=factionRewardType.hireling, display="@mob/creature_names:at_st", item="object/intangible/pet/pet_control.iff", controlledObjectTemplate="at_st", cost=9450},
	},
}
