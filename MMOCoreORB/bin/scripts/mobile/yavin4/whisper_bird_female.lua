whisper_bird_female = Creature:new {
	objectName = "@mob/creature_names:whisper_bird_female",
	socialGroup = "whisperbird",
	faction = "",
	level = 15,
	chanceHit = 0.31,
	damageMin = 170,
	damageMax = 180,
	baseXp = 831,
	baseHAM = 2000,
	baseHAMmax = 2400,
	armor = 0,
	resists = {5,5,5,5,5,5,5,5,-1},
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
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(whisper_bird_female, "whisper_bird_female")