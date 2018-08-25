shaggy_gurk_youth = Creature:new {
	objectName = "@mob/creature_names:shaggy_gurk_youth",
	socialGroup = "gurk",
	faction = "",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 3005,
	baseHAM = 8400,
	baseHAMmax = 10300,
	armor = 0,
	resists = {140,20,20,-1,20,20,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 300,
	hideType = "hide_leathery",
	hideAmount = 275,
	boneType = "bone_mammal",
	boneAmount = 300,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/shaggy_gurk_youth.iff"},
	hues = { 8, 9, 10, 11, 12, 13, 14, 15 },
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(shaggy_gurk_youth, "shaggy_gurk_youth")
