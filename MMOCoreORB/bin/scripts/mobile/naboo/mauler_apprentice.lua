mauler_apprentice = Creature:new {
	objectName = "@mob/creature_names:mauler_apprentice",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "mauler",
	faction = "",
	level = 12,
	chanceHit = 0.29,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 810,
	baseHAMmax = 990,
	armor = 0,
	resists = {0,0,10,0,0,0,0,-1,-1},
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
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_mauler_apprentice.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 4000000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 2000000},
				{group = "carbines", chance = 1000000},
				{group = "mauler_common", chance = 2000000}
			},
			lootChance = 2400000
		}
	},
	weapons = {"pirate_weapons_medium"},
	reactionStf = "@npc_reaction/fancy",
	attacks = merge(brawlermid,marksmanmid)
}

CreatureTemplates:addCreatureTemplate(mauler_apprentice, "mauler_apprentice")
