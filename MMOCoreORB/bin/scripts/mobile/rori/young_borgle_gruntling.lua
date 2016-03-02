young_borgle_gruntling = Creature:new {
	objectName = "@mob/creature_names:young_borgle_gruntling",
	socialGroup = "borgle",
	faction = "",
	level = 6,
	chanceHit = 0.25,
	damageMin = 45,
	damageMax = 55,
	baseXp = 147,
	baseHAM = 135,
	baseHAMmax = 165,
	armor = 0,
	resists = {115,105,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 10,
	boneType = "bone_avian",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/borgle.iff"},
	scale = 0.9,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(young_borgle_gruntling, "young_borgle_gruntling")
