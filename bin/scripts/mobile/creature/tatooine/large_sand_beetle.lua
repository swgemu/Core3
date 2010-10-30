large_sand_beetle = Creature:new {
	objectName = "@mob/creature_names:large_sand_beetle",
	socialGroup = "Gt. Sand Beet.",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.370000,
	damageMin = 260,
	damageMax = 270,
	baseXp = 3005,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {35,30,0,0,-1,0,0,0,-1},
	meatType = "meat_insect",
	meatAmount = 10,
	hideType = "hide_scaley",
	hideAmount = 14,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_sand_beetle.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(large_sand_beetle, "large_sand_beetle")