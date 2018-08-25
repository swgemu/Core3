juvenile_langlatch = Creature:new {
	objectName = "@mob/creature_names:langlatch_juvenile",
	socialGroup = "langlatch",
	faction = "",
	level = 8,
	chanceHit = 0.27,
	damageMin = 70,
	damageMax = 75,
	baseXp = 235,
	baseHAM = 405,
	baseHAMmax = 495,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 7,
	hideType = "hide_wooly",
	hideAmount = 6,
	boneType = "bone_mammal",
	boneAmount = 6,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/langlatch_juvenile.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 0.8,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(juvenile_langlatch, "juvenile_langlatch")
