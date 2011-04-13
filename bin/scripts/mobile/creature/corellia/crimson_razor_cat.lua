crimson_razor_cat = Creature:new {
	objectName = "@mob/creature_names:crimson_sand_panther",
	socialGroup = "Sand Panther",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.390000,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3005,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {35,35,-1,-1,0,-1,-1,-1,-1},
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
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_sand_panther.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crimson_razor_cat, "crimson_razor_cat")