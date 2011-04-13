canoid_hunter = Creature:new {
	objectName = "@mob/creature_names:canoid_hunter",
	socialGroup = "Canoid",
	pvpFaction = "",
	faction = "",
	level = 15,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 960,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {15,15,15,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/canoid.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(canoid_hunter, "canoid_hunter")