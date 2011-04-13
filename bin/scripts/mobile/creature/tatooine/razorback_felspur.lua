razorback_felspur = Creature:new {
	objectName = "@mob/creature_names:desert_razorback_felspur",
	socialGroup = "Zucca Boar",
	pvpFaction = "",
	faction = "",
	level = 27,
	chanceHit = 0.360000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 2730,
	baseHAM = 9000,
	baseHAMmax = 9000,
	armor = 0,
	resists = {0,0,0,0,-1,0,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 40,
	boneType = "bone_mammal",
	boneAmount = 25,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/zucca_boar.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(razorback_felspur, "razorback_felspur")