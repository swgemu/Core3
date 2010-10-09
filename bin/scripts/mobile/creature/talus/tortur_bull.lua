tortur_bull = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@mob/creature_names:tortur_bull",
	socialGroup = "Tortur",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 305,
	damageMax = 320,
	range = 0,
	baseXp = 2543,
	baseHAM = 5550,
	armor = 0,
	resists = {0,0,0,-1,-1,-1,-1,100,-1},
	meatType = "meat_carnivore",
	meatAmount = 1300,
	hideType = "hide_leathery",
	hideAmount = 1151,
	boneType = "bone_mammal",
	boneAmount = 1301,
	milk = 0.000000,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tortur_bull, "tortur_bull")
