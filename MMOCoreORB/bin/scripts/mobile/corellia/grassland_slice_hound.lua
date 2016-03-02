grassland_slice_hound = Creature:new {
	objectName = "@mob/creature_names:grassland_slice_hound",
	socialGroup = "slice_hound",
	faction = "",
	level = 14,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 831,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {105,115,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/female_grassland_slice_hound.iff"},
	controlDeviceTemplate = "object/intangible/pet/corellian_slice_hound_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(grassland_slice_hound, "grassland_slice_hound")
