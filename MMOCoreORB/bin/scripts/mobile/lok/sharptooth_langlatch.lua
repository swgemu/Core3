sharptooth_langlatch = Creature:new {
	objectName = "@mob/creature_names:sharptooth_langlatch",
	socialGroup = "langlatch",
	pvpFaction = "",
	faction = "",
	level = 17,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1102,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {0,115,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 16,
	hideType = "hide_wooly",
	hideAmount = 16,
	boneType = "bone_mammal",
	boneAmount = 16,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/langlatch_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/langlatch_hue.iff",
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(sharptooth_langlatch, "sharptooth_langlatch")
