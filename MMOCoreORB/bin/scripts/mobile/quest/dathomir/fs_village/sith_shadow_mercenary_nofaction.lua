sith_shadow_mercenary_nofaction = Creature:new {
	objectName = "@mob/creature_names:shadow_mercenary_nofaction",
	socialGroup = "sith_shadow",
	faction = "",
	level = 148,
	chanceHit = 7,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 3327,
	baseHAM = 67900,
	baseHAMmax = 83000,
	armor = 1,
	resists = {80,90,85,85,70,85,85,85,-1},
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
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = { "sith_shadow" },
	lootGroups = {
		{}
	},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = merge(riflemanmaster,pistoleermaster,carbineermaster,marksmanmaster,brawlermaster)
}

CreatureTemplates:addCreatureTemplate(sith_shadow_mercenary_nofaction, "sith_shadow_mercenary_nofaction")
