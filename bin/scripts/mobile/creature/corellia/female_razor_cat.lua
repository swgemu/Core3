female_razor_cat = Creature:new {
	objectName = "@mob/creature_names:female_sand_panther",
	socialGroup = "Sand Panther",
	pvpFaction = "",
	faction = "",
	level = 22,
	chanceHit = 0.350000,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2219,
	baseHAM = 5550,
	baseHAMmax = 5550,
	armor = 0,
	resists = {0,0,0,60,0,-1,-1,-1,-1},
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
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_sand_panther.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_razor_cat, "female_razor_cat")