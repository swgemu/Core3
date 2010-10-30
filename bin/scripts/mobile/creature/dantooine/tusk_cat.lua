tusk_cat = Creature:new {
	objectName = "@mob/creature_names:warren_tuskcat",
	socialGroup = "Tusk Cat",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.310000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2200,
	baseHAMmax = 2200,
	armor = 0,
	resists = {0,0,0,30,30,-1,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 75,
	hideType = "hide_bristley",
	hideAmount = 45,
	boneType = "bone_mammal",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/tusk_cat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(tusk_cat, "tusk_cat")