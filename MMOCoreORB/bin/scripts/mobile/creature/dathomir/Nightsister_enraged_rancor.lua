Nightsister_enraged_rancor = Creature:new {
	objectName = "Nightsister enraged rancor",
	socialGroup = "Nightsister",
	pvpFaction = "",
	faction = "",
	level = 80,
	chanceHit = 0.750000,
	damageMin = 570,
	damageMax = 850,
	baseXp = 7668,
	baseHAM = 13500,
	baseHAMmax = 13500,
	armor = 0,
	resists = {0,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 878,
	boneType = "bone_mammal",
	boneAmount = 778,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_enraged_rancor, "Nightsister_enraged_rancor")