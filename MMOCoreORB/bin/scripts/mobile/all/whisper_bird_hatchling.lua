whisper_bird_hatchling = Creature:new {
	objectName = "@mob/creature_names:whisper_bird_hatchling",
	socialGroup = "whisperbird",
	pvpFaction = "",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 55,
	damageMax = 65,
	baseXp = 187,
	baseHAM = 270,
	baseHAMmax = 330,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,0},
	meatType = "meat_avian",
	meatAmount = 55,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 30,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 0,
	diet = HERBIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/whisper_bird_hatchling.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(whisper_bird_hatchling, "whisper_bird_hatchling")