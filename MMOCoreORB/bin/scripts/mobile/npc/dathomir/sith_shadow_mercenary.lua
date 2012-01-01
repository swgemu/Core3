sith_shadow_mercenary = Creature:new {
	objectName = "@mob/creature_names:Sith_Shadow_mercenary",
	socialGroup = "Sith Shadow",
	pvpFaction = "s.s. non-aggro",
	faction = "",
	level = 148,
	chanceHit = 7,
	damageMin = 895,
	damageMax = 1500,
	baseXp = 3327,
	baseHAM = 679000,
	baseHAMmax = 83000,
	armor = 0,
	resists = {80,90,85,85,70,85,85,85,-1},
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

CreatureTemplates:addCreatureTemplate(sith_shadow_mercenary, "sith_shadow_mercenary")