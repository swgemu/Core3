nyms_patrol = Creature:new {
	objectName = "@mob/creature_names:nym_patrol_strong",
	socialGroup = "Nym",
	pvpFaction = "Nym",
	faction = "",
	level = 33,
	chanceHit = 0.4,
	damageMin = 305,
	damageMax = 320,
	baseXp = 3370,
	baseHAM = 8600,
	baseHAMmax = 10500,
	armor = 0,
	resists = {35,40,25,25,40,-1,-1,-1,-1},
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
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_nym_patrol_weak_rod_m.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(nyms_patrol, "nyms_patrol")