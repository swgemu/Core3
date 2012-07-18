bloodseeker_mite_hunter = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_hunter",
	socialGroup = "bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.36,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3097,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {15,45,-1,80,-1,80,80,15,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/bloodseeker_mite.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_hunter, "bloodseeker_mite_hunter")