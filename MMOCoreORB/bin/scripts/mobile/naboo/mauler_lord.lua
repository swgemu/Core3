mauler_lord = Creature:new {
	objectName = "@mob/creature_names:mauler_lord",
	socialGroup = "mauler",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {20,40,0,0,0,0,-1,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mauler_lord.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "carbines", chance = 1000000},
				{group = "mauler_common", chance = 2000000}
			},
			lootChance = 2700000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	reactionStf = "@npc_reaction/fancy",
	attacks = merge(brawlermaster,marksmanmaster,bountyhuntermaster)
}

CreatureTemplates:addCreatureTemplate(mauler_lord, "mauler_lord")
