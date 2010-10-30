bloodseeker_mite_guardian = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_guardian",
	socialGroup = "Bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.400000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3733,
	baseHAM = 9300,
	baseHAMmax = 9300,
	armor = 0,
	resists = {60,40,-1,70,-1,70,70,-1,-1},
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
		{"stunattack","stunChance=50"},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_guardian, "bloodseeker_mite_guardian")