rhoa_kwi_guardian = Creature:new {
	objectName = "@mob/creature_names:rhoa_kwi_guardian",
	socialGroup = "kwi",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.44,
	damageMin = 320,
	damageMax = 350,
	baseXp = 4461,
	baseHAM = 10000,
	baseHAMmax = 12000,
	armor = 0,
	resists = {40,65,30,80,30,30,15,30,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.15,
	ferocity = 6,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	aiTemplate = "default",

	templates = {"object/mobile/kwi.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_red"},
	conversationTemplate = "",
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi_guardian, "rhoa_kwi_guardian")