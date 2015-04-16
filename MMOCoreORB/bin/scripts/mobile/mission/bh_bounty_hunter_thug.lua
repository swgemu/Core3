bh_bounty_hunter_thug = Creature:new {
	objectName = "@mob/creature_names:bounty_hunter",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "mercenary",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2443,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {20,20,0,0,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	optionsBitmask = 128,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_bountyhunter_trainer_01.iff",
		"object/mobile/dressed_bountyhunter_trainer_02.iff",
		"object/mobile/dressed_bountyhunter_trainer_03.iff",
		"object/mobile/dressed_bounty_hunter_zabrak_female_01.iff"
	},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 6000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 4500000
		},
		{
			groups = {
				{group = "color_crystals", chance = 1500000},
				{group = "crystals_poor", chance = 1000000},
				{group = "crystals_okay", chance = 1000000},
				{group = "melee_two_handed", chance = 1500000},
				{group = "carbines", chance = 1500000},
				{group = "pistols", chance = 1500000},
				{group = "clothing_attachments", chance = 1000000},
				{group = "armor_attachments", chance = 1000000}
			},
			lootChance = 6000000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	reactionStf = "@npc_reaction/slang",
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(bh_bounty_hunter_thug, "bh_bounty_hunter_thug")
