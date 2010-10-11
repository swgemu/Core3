huf_dun = Creature:new {
	templateType = NPCCREATURE,
	gameObjectType = 1024,
	objectName = "@monster_name:huf_dun",
	socialGroup = "Huf Dun",
	pvpFaction = "",
	faction = "",
	level = 21,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	range = 0,
	baseXp = 1609,
	baseHAM = 4550,
	armor = 0,
	resists = {25,0,0,0,-1,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 1350,
	hideType = "hide_leathery",
	hideAmount = 1600,
	boneType = "bone_mammal",
	boneAmount = 1350,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = CARNIVORE,

	templates = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(huf_dun, "huf_dun")
