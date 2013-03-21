dofile("scripts/managers/mission_npc_spawn_points.lua");

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
	"lok",
	"naboo",
	"rori",
	"talus",
	"tatooine",
	"yavin4"
}

bh_targets_at_mission_level = {
	level1 = {
		"bodyguard",
		"bodyguard_zabrak_female"
	},
	level2 = {
		"dune_stalker_brawler",
		"canyon_corsair_cutthroat"
	},
	level3 = {
		"pirate_leader",
		"sennex_guard",
		"canyon_corsair_captain"
	}
}

enable_factional_crafting_missions = "true"

enable_factional_recon_missions = "true"

enable_factional_entertainer_missions = "true"
