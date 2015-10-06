shibb_gnarled_rancor = Creature:new {
	objectName = "@mob/creature_names:gnarled_rancor",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "thug",
	faction = "thug",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE + AGGRESSIVE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,


	templates = {"object/mobile/rancor_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/rancor_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(shibb_gnarled_rancor, "shibb_gnarled_rancor")
