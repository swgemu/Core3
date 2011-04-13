forest_slice_hound = Creature:new {
	objectName = "@mob/creature_names:forest_slice_hound",
	socialGroup = "Forest Slice Hound",
	pvpFaction = "",
	faction = "",
	level = 16,
	chanceHit = 0.300000,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 2700,
	baseHAMmax = 2700,
	armor = 0,
	resists = {15,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/forest_slice_hound.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(forest_slice_hound, "forest_slice_hound")