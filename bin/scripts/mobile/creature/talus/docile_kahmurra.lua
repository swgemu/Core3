docile_kahmurra = Creature:new {
	objectName = "@mob/creature_names:docile_kahmurra",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.280000,
	damageMin = 80,
	damageMax = 90,
	baseXp = 292,
	baseHAM = 1100,
	baseHAMmax = 1100,
	armor = 0,
	resists = {0,0,10,0,0,0,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 45,
	hideType = "hide_bristley",
	hideAmount = 27,
	boneType = "bone_mammal",
	boneAmount = 32,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/kahmurra.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(docile_kahmurra, "docile_kahmurra")