Nightsister_rancor = Creature:new {
	objectName = "Nightsister rancor",
	socialGroup = "Nightsister",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.500000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 5373,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {30,60,0,100,100,100,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 950,
	hideType = "hide_leathery",
	hideAmount = 876,
	boneType = "bone_mammal",
	boneAmount = 776,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(Nightsister_rancor, "Nightsister_rancor")