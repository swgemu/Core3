sith_shadow_pirate = Creature:new {
	objectName = "@mob/creature_names:Sith_Shadow_pirate",
	socialGroup = "Sith Shadow",
	pvpFaction = "s.s. non-aggro",
	faction = "",
	level = 90,
	chanceHit = 0.85,
	damageMin = 570,
	damageMax = 850,
	baseXp = 1864,
	baseHAM = 13300,
	baseHAMmax = 16300,
	armor = 0,
	resists = {65,65,50,75,75,70,70,65,-1},
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

	templates = {"object/mobile/dressed_sith_shadow_hum_m_01.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(sith_shadow_pirate, "sith_shadow_pirate")