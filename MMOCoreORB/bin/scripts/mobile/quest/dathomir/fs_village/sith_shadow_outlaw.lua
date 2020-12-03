sith_shadow_outlaw = Creature:new {
	objectName = "@mob/creature_names:shadow_outlaw",
	socialGroup = "sith_shadow",
	faction = "sith_shadow",
	level = 17,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1257,
	baseHAM = 2430,
	baseHAMmax = 2970,
	armor = 0,
	resists = {15,15,15,15,15,15,15,15,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = { "sith_shadow" },
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 1500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "printer_parts", chance = 1000000},
				{group = "wearables_common", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000},
			},
		},
		{
			groups = {
				{group = "village_resources", chance =  10000000}
			},
			lootChance = 7500000
		},
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(sith_shadow_outlaw, "sith_shadow_outlaw")
