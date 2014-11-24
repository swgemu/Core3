domesticated_merek = Creature:new {
	objectName = "@mob/creature_names:domesticated_merek",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 49,
	chanceHit = 0.5,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4734,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {160,-1,0,180,140,0,140,0,-1},
	meatType = "meat_wild",
	meatAmount = 65,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/merek_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_yellow"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(domesticated_merek, "domesticated_merek")
