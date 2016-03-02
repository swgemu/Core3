blood_stained_merek = Creature:new {
	objectName = "@mob/creature_names:blood_stained_merek",
	socialGroup = "merek",
	faction = "",
	level = 32,
	chanceHit = 0.4,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3279,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {-1,145,20,160,160,20,175,-1,-1},
	meatType = "meat_wild",
	meatAmount = 55,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	controlDeviceTemplate = "object/intangible/pet/merek_hue.iff",
	scale = 0.9,
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"knockdownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(blood_stained_merek, "blood_stained_merek")
