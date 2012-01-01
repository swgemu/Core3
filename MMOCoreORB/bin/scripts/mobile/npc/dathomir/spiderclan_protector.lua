spiderclan_protector = Creature:new {
	objectName = "@mob/creature_names:Spiderclan_protector",
	socialGroup = "Sp. Nightsister",
	pvpFaction = "Sp. Nightsister",
	faction = "",
	level = 131,
	chanceHit = 4.75,
	damageMin = 770,
	damageMax = 1250,
	baseXp = 12424,
	baseHAM = 50000,
	baseHAMmax = 61000,
	armor = 1,
	resists = {85,95,100,85,100,100,85,100,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_dathomir_spider_nightsister_protector.iff"},
	lootgroups = {},
	weapons = {"mixed_force_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(spiderclan_protector, "spiderclan_protector")