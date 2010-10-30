blurrg_tracker = Creature:new {
	objectName = "@mob/creature_names:blurrg_tracker",
	socialGroup = "Blurrg",
	pvpFaction = "",
	faction = "",
	level = 28,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {25,25,0,40,80,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_avian",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/blurrg.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_yellow"},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blurrg_tracker, "blurrg_tracker")