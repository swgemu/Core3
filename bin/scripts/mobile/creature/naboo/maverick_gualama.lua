maverick_gualama = Creature:new {
	objectName = "@mob/creature_names:maverick_gualama",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 14,
	chanceHit = 0.300000,
	damageMin = 150,
	damageMax = 160,
	baseXp = 609,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,10,0,0,0,0,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 200,
	hideType = "hide_wooly",
	hideAmount = 150,
	boneType = "bone_mammal",
	boneAmount = 90,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = NONE,
	diet = CARNIVORE,

	templates = {"object/mobile/gualama.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(maverick_gualama, "maverick_gualama")