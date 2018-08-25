whisper_bird_male = Creature:new {
	objectName = "@mob/creature_names:whisper_bird_male",
	socialGroup = "whisperbird",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 960,
	baseHAM = 2900,
	baseHAMmax = 3500,
	armor = 0,
	resists = {5,5,5,5,5,5,5,-1,-1},
	meatType = "meat_avian",
	meatAmount = 65,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/whisper_bird_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	scale = 1.05,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(whisper_bird_male, "whisper_bird_male")
