bh_pirate_leader = Creature:new {
	objectName = "@mob/creature_names:pirate_leader",
	socialGroup = "pirate",
	faction = "pirate",
	level = 17,
	chanceHit = 0.320000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
	armor = 0,
	resists = {0,0,0,30,-1,30,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_criminal_assassin_human_female_01.iff",
		"object/mobile/dressed_criminal_smuggler_human_male_01.iff"
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

CreatureTemplates:addCreatureTemplate(bh_pirate_leader, "bh_pirate_leader")
