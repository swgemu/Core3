ancient_reptilian_flier = Creature:new {
	objectName = "@mob/creature_names:ancient_reptilian_flier",
	socialGroup = "reptilian_flier",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2543,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {120,130,10,150,150,-1,150,-1,-1},
	meatType = "meat_avian",
	meatAmount = 135,
	hideType = "hide_leathery",
	hideAmount = 90,
	boneType = "bone_avian",
	boneAmount = 85,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 7,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/reptilian_flier_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/pet_control.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(ancient_reptilian_flier, "ancient_reptilian_flier")
