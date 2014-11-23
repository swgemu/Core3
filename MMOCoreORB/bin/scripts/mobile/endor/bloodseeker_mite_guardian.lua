bloodseeker_mite_guardian = Creature:new {
	objectName = "@mob/creature_names:bloodseeker_mite_guardian",
	socialGroup = "bloodseeker",
	pvpFaction = "",
	faction = "",
	level = 38,
	chanceHit = 0.4,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3733,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {160,140,-1,170,-1,170,170,20,-1},
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
	scale = 1.15,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"strongdisease",""},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(bloodseeker_mite_guardian, "bloodseeker_mite_guardian")
