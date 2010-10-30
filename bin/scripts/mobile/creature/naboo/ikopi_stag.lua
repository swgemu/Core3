ikopi_stag = Creature:new {
	objectName = "@mob/creature_names:ikopi_stag",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.390000,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {30,30,0,0,0,-1,-1,-1,-1},
	meatType = "meat_wild",
	meatAmount = 100,
	hideType = "hide_bristley",
	hideAmount = 75,
	boneType = "bone_mammal",
	boneAmount = 75,
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

CreatureTemplates:addCreatureTemplate(ikopi_stag, "ikopi_stag")