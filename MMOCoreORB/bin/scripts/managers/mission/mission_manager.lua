dofile("scripts/managers/mission/mission_npc_spawn_points.lua");

crafting_mission_items = {
	"object/draft_schematic/item/quest_item/attunement_grid.iff",
	"object/draft_schematic/item/quest_item/current_alternator.iff",
	"object/draft_schematic/item/quest_item/feedback_controller.iff",
	"object/draft_schematic/item/quest_item/output_governor.iff",
	"object/draft_schematic/item/quest_item/power_regulator.iff"
}

bh_target_zones = {
	"corellia",
	"dantooine",
	"dathomir",
	"endor",
	"lok",
	"naboo",
	"rori",
	"talus",
	"tatooine",
	"yavin4"
}

bh_targets_at_mission_level = {
	level1 = { --level 1 - 25
		"bh_bodyguard", --level 7
		"bh_pirate_privateer", --level 10
		"bh_naboo_pirate_lieutenant", --level 15
		"bh_dune_stalker_brawler", --level 17
		"bh_pirate_leader", --level 17
		"bh_bodyguard_zabrak_female", --level 18
		"bh_assassin_twilek_mate", --level 18
		"bh_bounty_hunter_thug" --level 24
	},
	level2 = { --level 15 - 45
		"bh_dune_stalker_brawler", --level 17
		"bh_pirate_leader", --level 17
		"bh_assassin_twilek_mate", --level 18
		"bh_bodyguard_zabrak_female", --level 18
		"bh_bounty_hunter_thug", --level 24
		"bh_sennex_guard", --level 32
		"bh_scientist", --level 34
		"bh_canyon_corsair_cutthroat", --level 35
		"bh_mercenary_warlord", --level 44
		"bh_ig_assassin_droid" --level 45
	},
	level3 = { --level 30 - 200 (current highest is 115, probe droids will only have a 5% chance to find targets over level 190)
		"bh_sennex_guard", --level 32
		"bh_scientist", --level 34
		"bh_canyon_corsair_cutthroat", --level 35
		"bh_mercenary_warlord", --level 44
		"bh_ig_assassin_droid", --level 45
		"bh_canyon_corsair_captain", --level 50
		"bh_untrained_wielder_of_the_dark_side", --level 65
		"bh_nightsister_outcast", --level 81
		"bh_force_trained_archaist", --level 90
		"bh_force_sensitive_crypt_crawler", --level 95
		"bh_nightsister_spell_weaver", --level 107
		"bh_singing_mountain_clan_arch_witch", --level 107
		"bh_spiderclan_auspex", --level 107
		"bh_feral_force_wielder", --level 115
		"bh_force_crystal_hunter" --level 115
	}
}

enable_factional_crafting_missions = "true"

enable_factional_recon_missions = "true"

enable_factional_entertainer_missions = "true"
