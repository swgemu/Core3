shibb_gnarled_rancor = Creature:new {
	objectName = "@mob/creature_names:thug",
	randomNameType = NAME_GENERIC,
	randomNameTag = true,
	socialGroup = "brigand",
	faction = "",
	level = 17,
	chanceHit = 0.32,
	damageMin = 180,
	damageMax = 190,
	baseXp = 1257,
	baseHAM = 3500,
	baseHAMmax = 4300,
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
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,


	templates = {"object/mobile/rancor_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/rancor_hue.iff",
	scale = 1.1,
	lootGroups = {},
	weapons = {},
	attacks = {
		{"stunattack",""},
		{"intimidationattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(shibb_gnarled_rancor, "shibb_gnarled_rancor")

