Nightsister_enraged_bull_rancor = Creature:new {
	objectName = "Nightsister enraged bull rancor",
	socialGroup = "Nightsister",
	pvpFaction = "",
	faction = "",
	level = 89,
	chanceHit = 0.850000,
	damageMin = 570,
	damageMax = 850,
	baseXp = 8500,
	baseHAM = 14500,
	baseHAMmax = 14500,
	armor = 0,
	resists = {0,70,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 880,
	hideType = "hide_leathery",
	hideAmount = 750,
	boneType = "bone_mammal",
	boneAmount = 670,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bull_rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_enraged_bull_rancor, "Nightsister_enraged_bull_rancor")