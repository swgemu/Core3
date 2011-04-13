skreeg_male = Creature:new {
	objectName = "@mob/creature_names:skreeg_male",
	socialGroup = "Skreeg",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 2006,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {0,25,0,-1,0,-1,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 5,
	hideType = "hide_bristley",
	hideAmount = 9,
	boneType = "bone_mammal",
	boneAmount = 7,
	milk = 0,
	tamingChance = 0.250000,
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

CreatureTemplates:addCreatureTemplate(skreeg_male, "skreeg_male")