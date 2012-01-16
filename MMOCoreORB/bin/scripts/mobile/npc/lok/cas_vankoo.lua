cas_vankoo = Creature:new {
	objectName = "@mob/creature_names:cas_vankoo",
	socialGroup = "Kimogila",
	pvpFaction = "Bandit",
	faction = "",
	level = 117,
	chanceHit = 3.4,
	damageMin = 725,
	damageMax = 1160,
	baseXp = 11109,
	baseHAM = 40000,
	baseHAMmax = 49000,
	armor = 0,
	resists = {75,75,-1,0,0,0,0,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_lok_cas_vankoo.iff"},
	lootgroups = {},
	weapons = {"cas_vankoo's_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(cas_vankoo, "cas_vankoo")