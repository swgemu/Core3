bloodseeker_mite_hunter = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_hunter",
	socialGroup = "Bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 31,
	chanceHit = 0.360000,
	damageMin = 315,
	damageMax = 340,
	baseXp = 3097,
	baseHAM = 6550,
	baseHAMmax = 6550,
	armor = 0,
	resists = {15,45,-1,80,-1,80,80,0,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bloodseeker_mite.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_hunter, "bloodseeker_mite_hunter")