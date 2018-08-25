male_snorbal_calf = Creature:new {
	objectName = "@mob/creature_names:male_snorbal_calf",
	socialGroup = "snorbal",
	faction = "",
	level = 22,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 1803,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {130,130,-1,10,10,-1,10,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 500,
	hideType = "hide_leathery",
	hideAmount = 401,
	boneType = "bone_mammal",
	boneAmount = 351,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/male_snorbal_calf.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 0.65,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(male_snorbal_calf, "male_snorbal_calf")
