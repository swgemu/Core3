majestic_whisper_bird = Creature:new {
	objectName = "@mob/creature_names:whisper_bird_majestic",
	socialGroup = "Whisperbird",
	pvpFaction = "",
	faction = "",
	level = 19,
	chanceHit = 0.320000,
	damageMin = 170,
	damageMax = 180,
	baseXp = 1426,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,0,0,0,0,0,0,0,-1},
	meatType = "meat_avian",
	meatAmount = 65,
	hideType = "",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 40,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/whisper_bird.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(majestic_whisper_bird, "majestic_whisper_bird")