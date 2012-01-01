stormtrooper_medic = Creature:new {
	objectName = "@mob/creature_names:stormtrooper_medic",
	socialGroup = "Imperial",
	pvpFaction = "Imperial",
	faction = "",
	level = 25,
	chanceHit = 0.36,
	damageMin = 240,
	damageMax = 250,
	baseXp = 2637,
	baseHAM = 7200,
	baseHAMmax = 8800,
	armor = 0,
	resists = {0,0,40,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_stormtrooper_medic_m.iff"},
	lootgroups = {},
	weapons = {"stormtrooper_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(stormtrooper_medic, "stormtrooper_medic")