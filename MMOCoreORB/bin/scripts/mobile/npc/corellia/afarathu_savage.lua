afarathu_savage = Creature:new {
	objectName = "@mob/creature_names:Afarathu_savage",
	socialGroup = "Afarathu",
	pvpFaction = "Afarathu",
	faction = "",
	level = 7,
	chanceHit = 0.26,
	damageMin = 70,
	damageMax = 75,
	baseXp = 187,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_selonian_m_02.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(afarathu_savage, "afarathu_savage")