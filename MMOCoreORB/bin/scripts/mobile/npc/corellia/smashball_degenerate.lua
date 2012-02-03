smashball_degenerate = Creature:new {
	objectName = "@mob/creature_names:smashball_degenerate",
	socialGroup = "Smashball",
	pvpFaction = "Smashball",
	faction = "",
	level = 9,
	chanceHit = 0.270000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 292,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {},
	lootGroups = {
		{
			groups = {
				{group = "loot_kit_items", chance = 10000000}
			},
			lootChance = 3300000
		}
	},
	weapons = {"pirate_weapons_heavy"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(smashball_degenerate, "smashball_degenerate")