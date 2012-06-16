bloodseeker_mite_queen = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_queen",
	socialGroup = "bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.41,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3824,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {40,45,-1,80,-1,80,80,-1,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/bloodseeker_mite_queen.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_queen, "bloodseeker_mite_queen")