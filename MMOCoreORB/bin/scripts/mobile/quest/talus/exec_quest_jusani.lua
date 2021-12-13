exec_quest_jusani = Creature:new {
	objectName = "@mob/creature_names:businessman",
	socialGroup = "townsperson",
	faction = "townsperson",
	mobType = MOB_NPC,
	level = 4,
	chanceHit = 0.24,
	damageMin = 40,
	damageMax = 45,
	baseXp = 62,
	baseHAM = 113,
	baseHAMmax = 138,
	armor = 0,
	resists = {10,10,10,10,10,10,10,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	optionsBitmask = AIENABLED + CONVERSABLE,
	diet = HERBIVORE,

	templates = {	"object/mobile/dressed_commoner_fat_zabrak_male_01.iff",
					"object/mobile/dressed_commoner_tatooine_ishitib_male_01.iff",
					"object/mobile/dressed_commoner_old_zabrak_male_01.iff",
					"object/mobile/dressed_commoner_tatooine_sullustan_male_03.iff",
					"object/mobile/dressed_commoner_naboo_human_male_08.iff",
					"object/mobile/dressed_commoner_tatooine_nikto_male_03.iff",
					"object/mobile/dressed_commoner_tatooine_nikto_male_07.iff",
					"object/mobile/dressed_commoner_tatooine_bith_male_05.iff",
					"object/mobile/dressed_commoner_tatooine_ishitib_male_01.iff",
					"object/mobile/dressed_commoner_naboo_human_male_03.iff",
					"object/mobile/dressed_commoner_tatooine_bith_male_02.iff",
					"object/mobile/dressed_commoner_tatooine_trandoshan_male_02.iff",
					"object/mobile/dressed_commoner_tatooine_bith_male_01.iff",
					"object/mobile/dressed_diplomat_human_male_01.iff",
					"object/mobile/dressed_diplomat_human_male_02.iff",
					"object/mobile/dressed_diplomat_human_male_03.iff",
					"object/mobile/dressed_diplomat_trando_male_01.iff",
					"object/mobile/dressed_diplomat_zabrak_male_01.iff",
					"object/mobile/dressed_diplomat_zabrak_male_02.iff"
					},
	lootGroups = {
		{
			groups = {
					{group = "task_loot_briefcase_quest_jusani", chance = 10000000}
				},
			lootChance = 10000000
		}
	},

	-- Primary and secondary weapon should be different types (rifle/carbine, carbine/pistol, rifle/unarmed, etc)
	-- Unarmed should be put on secondary unless the mobile doesn't use weapons, in which case "unarmed" should be put primary and "none" as secondary
	primaryWeapon = "pirate_weapons_light",
	secondaryWeapon = "unarmed",
	reactionStf = "@npc_reaction/slang",
	conversationTemplate = "jusani_zhord_mission_target_convotemplate",
	
	-- primaryAttacks and secondaryAttacks should be separate skill groups specific to the weapon type listed in primaryWeapon and secondaryWeapon
	-- Use merge() to merge groups in creatureskills.lua together. If a weapon is set to "none", set the attacks variable to empty brackets
	primaryAttacks = merge(brawlermaster, marksmanmaster),
	secondaryAttacks = { }
}

CreatureTemplates:addCreatureTemplate(exec_quest_jusani, "exec_quest_jusani")
