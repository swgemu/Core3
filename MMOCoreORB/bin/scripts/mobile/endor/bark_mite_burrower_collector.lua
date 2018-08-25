bark_mite_burrower_collector = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower_collector",
	socialGroup = "mite",
	faction = "",
	level = 36,
	chanceHit = 0.4,
	damageMin = 335,
	damageMax = 380,
	baseXp = 3551,
	baseHAM = 8600,
	baseHAMmax = 10600,
	armor = 0,
	resists = {20,140,-1,170,-1,165,170,20,-1},
	meatType = "meat_insect",
	meatAmount = 50,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.2,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bark_mite_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/bark_mite_hue.iff",
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower_collector, "bark_mite_burrower_collector")
