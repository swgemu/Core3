mauler_master = Creature:new {
	objectName = "@mob/creature_names:mauler_master",
	socialGroup = "mauler",
	pvpFaction = "",
	faction = "",
	level = 54,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 5190,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 1,
	resists = {65,35,90,90,90,-1,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mauler_master.iff"},
	lootGroups = {
	    {
			groups = {
				{group = "junk", chance = 3000000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "carbines", chance = 1000000},
				{group = "mauler_common", chance = 2000000},
				{group = "wearables_uncommon", chance = 1000000}
			},
			lootChance = 3000000
		}					
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(brawlermaster,marksmanmaster,bountyhuntermaster)
}

CreatureTemplates:addCreatureTemplate(mauler_master, "mauler_master")
