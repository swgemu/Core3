razor_cat_eviscerator = Creature:new {
	objectName = "@mob/creature_names:razor_cat_eviscerator",
	socialGroup = "Sand Panther",
	pvpFaction = "",
	faction = "",
	level = 24,
	chanceHit = 0.350000,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2543,
	baseHAM = 8000,
	baseHAMmax = 8000,
	armor = 0,
	resists = {10,10,0,15,0,0,-1,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = KILLER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_sand_panther.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"intimidationattack","intimidationChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(razor_cat_eviscerator, "razor_cat_eviscerator")