fierce_borgle = Creature:new {
	objectName = "@mob/creature_names:fierce_borgle",
	socialGroup = "borgle",
	faction = "",
	level = 32,
	chanceHit = 0.37,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3279,
	baseHAM = 6300,
	baseHAMmax = 7700,
	armor = 0,
	resists = {140,130,130,-1,175,175,200,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 5,
	hideType = "hide_leathery",
	hideAmount = 5,
	boneType = "bone_avian",
	boneAmount = 5,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle_hue.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	scale = 1.15,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(fierce_borgle, "fierce_borgle")
