bloodseeker_mite = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite",
	socialGroup = "bloodseeker",
	faction = "",
	level = 31,
	chanceHit = 0.39,
	damageMin = 325,
	damageMax = 360,
	baseXp = 3097,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {-1,140,-1,200,-1,200,200,-1,-1},
	meatType = "meat_insect",
	meatAmount = 15,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/bloodseeker_mite.iff"},
	hues = { 24, 25, 26, 27, 28, 29, 30, 31 },
	controlDeviceTemplate = "object/intangible/pet/bark_mite_hue.iff",
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite, "bloodseeker_mite")
