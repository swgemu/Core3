grand_tybis = Creature:new {
	objectName = "@mob/creature_names:tybis_grand",
	socialGroup = "Tybis",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 275,
	hideType = "hide_bristley",
	hideAmount = 200,
	boneType = "bone_mammal",
	boneAmount = 125,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/tybis.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(grand_tybis, "grand_tybis")