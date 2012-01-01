aakuan_guardian = Creature:new {
	objectName = "@mob/creature_names:Aa'kuan_guardian",
	socialGroup = "Aa'kuan",
	pvpFaction = "Aa'kuan",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 220,
	damageMax = 230,
	baseXp = 2637,
	baseHAM = 5400,
	baseHAMmax = 6600,
	armor = 0,
	resists = {30,30,0,0,0,0,0,0,-1},
	meatType = "",
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
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_aakuan_guardian_trandoshan_male_01.iff"},
	lootgroups = {},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aakuan_guardian, "aakuan_guardian")