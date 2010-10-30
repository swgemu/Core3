female_swamp_tusk_cat = Creature:new {
	objectName = "@mob/creature_names:female_swamp_tusk_cat",
	socialGroup = "Swamp Tusk Cat",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 3900,
	baseHAMmax = 3900,
	armor = 0,
	resists = {0,0,0,-1,30,-1,35,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/tusk_cat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_swamp_tusk_cat, "female_swamp_tusk_cat")