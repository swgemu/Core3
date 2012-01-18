gnarled_rancor = Creature:new {
	objectName = "@mob/creature_names:gnarled_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 46,
	chanceHit = 0.47,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4552,
	baseHAM = 9700,
	baseHAMmax = 11900,
	armor = 1,
	resists = {0,30,-1,50,50,50,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 876,
	boneType = "bone_mammal",
	boneAmount = 775,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,
	lootChance = 3600000,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {
		{group = "rancor_common", chance = 3300000},
		{group = "pistols", chance = 3300000},
		{group = "rifles", chance = 3400000}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gnarled_rancor, "gnarled_rancor")