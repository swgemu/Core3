eopie = Creature:new {
	objectName = "@monster_name:eopie",
	socialGroup = "Eopie",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.260000,
	damageMin = 45,
	damageMax = 50,
	baseXp = 147,
	baseHAM = 450,
	baseHAMmax = 450,
	armor = 0,
	resists = {0,0,0,10,10,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 315,
	hideType = "hide_leathery",
	hideAmount = 250,
	boneType = "bone_mammal",
	boneAmount = 150,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/eopie.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(eopie, "eopie")