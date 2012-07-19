blood_stained_merek = Creature:new {
	objectName = "@mob/creature_names:blood_stained_merek",
	socialGroup = "merek",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.4,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3279,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {-1,45,20,60,60,20,75,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blood_stained_merek, "blood_stained_merek")