forest_slice_hound = Creature:new {
	objectName = "@mob/creature_names:forest_slice_hound",
	socialGroup = "slice_hound",
	faction = "",
	level = 16,
	chanceHit = 0.3,
	damageMin = 160,
	damageMax = 170,
	baseXp = 960,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {115,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 2,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/forest_slice_hound.iff"},
	controlDeviceTemplate = "object/intangible/pet/corellian_slice_hound_hue.iff",
	scale = 1.2,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(forest_slice_hound, "forest_slice_hound")
