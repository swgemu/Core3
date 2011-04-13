kwi = Creature:new {
	objectName = "@monster_name:kwi",
	socialGroup = "Kwi",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.270000,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 300,
	baseHAMmax = 300,
	armor = 0,
	resists = {10,10,0,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 100,
	hideType = "hide_leathery",
	hideAmount = 85,
	boneType = "bone_mammal",
	boneAmount = 75,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kwi, "kwi")