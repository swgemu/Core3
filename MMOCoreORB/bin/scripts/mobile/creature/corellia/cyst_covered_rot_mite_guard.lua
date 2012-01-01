cyst_covered_rot_mite_guard = Creature:new {
	objectName = "@mob/creature_names:cyst_covered_rot_mite_guard",
	socialGroup = "Decay Mite",
	pvpFaction = "",
	faction = "",
	level = 13,
	chanceHit = 0.3,
	damageMin = 140,
	damageMax = 150,
	baseXp = 609,
	baseHAM = 1500,
	baseHAMmax = 1900,
	armor = 0,
	resists = {0,0,0,0,0,0,15,-1,-1},
	meatType = "meat_insect",
	meatAmount = 9,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + HERD,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/rot_mite.iff"},
	lootgroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"mediumdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(cyst_covered_rot_mite_guard, "cyst_covered_rot_mite_guard")