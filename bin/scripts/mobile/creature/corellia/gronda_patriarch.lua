gronda_patriarch = Creature:new {
	objectName = "gronda patriarch",
	socialGroup = "Gronda",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4461,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {65,50,80,0,0,0,10,25,-1},
	meatType = "meat_carnivore",
	meatAmount = 360,
	hideType = "hide_leathery",
	hideAmount = 270,
	boneType = "bone_mammal",
	boneAmount = 180,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gronda.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gronda_patriarch, "gronda_patriarch")