jabba_rancor = Creature:new {
	objectName = "@mob/creature_names:jabbas_palace_rancor",
	socialGroup = "Jabba ",
	pvpFaction = "",
	faction = "",
	level = 61,
	chanceHit = 0.590000,
	damageMin = 485,
	damageMax = 680,
	baseXp = 5921,
	baseHAM = 12000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_",
	meatAmount = 0,
	hideType = "hide_",
	hideAmount = 0,
	boneType = "bone_",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/rancor.iff"},
	lootGroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(jabba_rancor, "jabba_rancor")
