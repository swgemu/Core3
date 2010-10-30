demolishing_snorbal_titan = Creature:new {
	objectName = "@mob/creature_names:snorbal_titanic_demolisher",
	socialGroup = "Snorbal",
	pvpFaction = "",
	faction = "",
	level = 40,
	chanceHit = 0.470000,
	damageMin = 345,
	damageMax = 400,
	baseXp = 4006,
	baseHAM = 10300,
	baseHAMmax = 10300,
	armor = 0,
	resists = {45,30,0,0,-1,-1,0,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 570,
	hideType = "hide_leathery",
	hideAmount = 455,
	boneType = "bone_mammal",
	boneAmount = 420,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/snorbal.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"intimidationattack","intimidationChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(demolishing_snorbal_titan, "demolishing_snorbal_titan")