bull_rancor = Creature:new {
	objectName = "@mob/creature_names:bull_rancor",
	socialGroup = "Rancor",
	pvpFaction = "",
	faction = "",
	level = 65,
	chanceHit = 0.6,
	damageMin = 455,
	damageMax = 620,
	baseXp = 6288,
	baseHAM = 11000,
	baseHAMmax = 14000,
	armor = 1,
	resists = {35,60,15,80,80,80,15,15,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 900,
	boneType = "bone_mammal",
	boneAmount = 850,
	milk = 0,
	tamingChance = 0.01,
	ferocity = 11,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,
	lootChance = 3950000,

	templates = {"object/mobile/bull_rancor.iff"},
	lootgroups = {
		{group = "rancor_common", chance = 3300000},
		{group = "pistols", chance = 3300000},
		{group = "rifles", chance = 3400000}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareadisease",""},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bull_rancor, "bull_rancor")