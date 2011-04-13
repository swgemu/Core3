female_grassland_slice_hound = Creature:new {
	objectName = "@mob/creature_names:female_grassland_slice_hound",
	socialGroup = "Grassland Slice Hound",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.290000,
	damageMin = 120,
	damageMax = 130,
	baseXp = 609,
	baseHAM = 1700,
	baseHAMmax = 1700,
	armor = 0,
	resists = {0,10,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/female_grassland_slice_hound.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(female_grassland_slice_hound, "female_grassland_slice_hound")