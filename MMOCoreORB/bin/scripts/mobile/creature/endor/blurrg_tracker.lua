blurrg_tracker = Creature:new {
	objectName = "@mob/creature_names:blurrg_tracker",
	socialGroup = "Blurrg",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {25,25,15,40,80,15,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blurrg_tracker, "blurrg_tracker")