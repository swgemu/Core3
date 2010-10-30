ominous_skreeg = Creature:new {
	objectName = "@mob/creature_names:skreeg_ominous",
	socialGroup = "Skreeg",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.360000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2443,
	baseHAM = 7550,
	baseHAMmax = 7550,
	armor = 0,
	resists = {0,25,0,-1,0,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 9,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/skreeg.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ominous_skreeg, "ominous_skreeg")