elder_pugoriss = Creature:new {
	objectName = "@mob/creature_names:elder_pugoriss",
	socialGroup = "pugoriss",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {15,15,5,-1,35,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 35,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 45,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/elder_pugoriss.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(elder_pugoriss, "elder_pugoriss")