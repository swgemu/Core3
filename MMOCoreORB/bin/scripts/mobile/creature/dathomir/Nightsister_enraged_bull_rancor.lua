Nightsister_enraged_bull_rancor = Creature:new {
	objectName = "@mob/creature_names:nightsister_enraged_bull_rancor",
	socialGroup = "Nightsister",
	pvpFaction = "",
	faction = "",
	level = 89,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8500,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 1,
	resists = {0,70,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 880,
	hideType = "hide_leathery",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 670,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,
	lootChance = 4200000,

	templates = {"object/mobile/bull_rancor.iff"},
	lootgroups = {
		{group = "rancor_common", chance = 3300000},
		{group = "pistols", chance = 3300000},
		{group = "rifles", chance = 3400000}
	},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"creatureareaknockdown","knockdownChance=30"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_enraged_bull_rancor, "Nightsister_enraged_bull_rancor")