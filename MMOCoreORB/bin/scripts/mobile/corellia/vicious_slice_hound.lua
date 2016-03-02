vicious_slice_hound = Creature:new {
	objectName = "",
	customName = "a vicious slice hound",
	socialGroup = "slice_hound",
	faction = "",
	level = 9,
	chanceHit = 0.27,
	damageMin = 120,
	damageMax = 130,
	baseXp = 292,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 65,
	hideType = "hide_bristley",
	hideAmount = 35,
	boneType = "bone_mammal",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/corellian_slice_hound.iff"},
	controlDeviceTemplate = "object/intangible/pet/corellian_slice_hound_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(vicious_slice_hound, "vicious_slice_hound")
