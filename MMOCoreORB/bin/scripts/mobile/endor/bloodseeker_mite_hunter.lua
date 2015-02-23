bloodseeker_mite_hunter = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_hunter",
	socialGroup = "bloodseeker",
	faction = "",
	level = 31,
	chanceHit = 0.36,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3097,
	baseHAM = 5900,
	baseHAMmax = 7200,
	armor = 0,
	resists = {115,145,-1,180,-1,180,180,15,-1},
	meatType = "meat_insect",
	meatAmount = 15,
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
	scale = 1.1,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_hunter, "bloodseeker_mite_hunter")
