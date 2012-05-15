greater_shaupaut = Creature:new {
	objectName = "@mob/creature_names:greater_shaupaut",
	socialGroup = "shaupaut",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 150,
	damageMax = 160,
	baseXp = 714,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_bristley",
	hideAmount = 6,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/greater_shaupaut.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(greater_shaupaut, "greater_shaupaut")