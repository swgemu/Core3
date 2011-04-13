mountain_ikopi = Creature:new {
	objectName = "@mob/creature_names:mountain_ikopi",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 3200,
	baseHAMmax = 3200,
	armor = 0,
	resists = {15,0,0,0,0,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 60,
	boneType = "bone_mammal",
	boneAmount = 50,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/ikopi.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mountain_ikopi, "mountain_ikopi")