ravenous_roba_stalker = Creature:new {
	objectName = "ravenous roba stalker",
	socialGroup = "Roba",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 3915,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {0,0,0,75,-1,0,0,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/roba.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ravenous_roba_stalker, "ravenous_roba_stalker")