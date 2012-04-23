dantari_raider = Creature:new {
	objectName = "@mob/creature_names:dantari_raider",
	socialGroup = "dantari_raiders",
	pvpFaction = "dantari_raiders",
	faction = "dantari_raiders",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {25,15,15,15,-1,15,-1,15,-1},
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

	templates = {"object/mobile/dantari_male.iff",
		"object/mobile/dantari_female.iff"},
	lootGroups = {},
	weapons = {"primitive_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(dantari_raider, "dantari_raider")
