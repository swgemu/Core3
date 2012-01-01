sith_shadow_taskmaster = Creature:new {
	objectName = "@mob/creature_names:Sith_Shadow_taskmaster",
	socialGroup = "Sith Shadow",
	pvpFaction = "Sith Shadow",
	faction = "",
	level = 87,
	chanceHit = 0.75,
	damageMin = 620,
	damageMax = 950,
	baseXp = 8315,
	baseHAM = 12400,
	baseHAMmax = 15200,
	armor = 0,
	resists = {70,70,70,70,70,70,70,70,-1},
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
	creatureBitmask = KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_sith_shadow_hum_m_01.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(sith_shadow_taskmaster, "sith_shadow_taskmaster")