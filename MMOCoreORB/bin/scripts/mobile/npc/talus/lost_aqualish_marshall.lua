lost_aqualish_marshall = Creature:new {
	objectName = "@mob/creature_names:lost_aqualish_marshal",
	socialGroup = "Lost Aql. Reg.",
	pvpFaction = "Lost Aql. Reg.",
	faction = "",
	level = 25,
	chanceHit = 0.35,
	damageMin = 230,
	damageMax = 240,
	baseXp = 2637,
	baseHAM = 6800,
	baseHAMmax = 8300,
	armor = 0,
	resists = {20,20,0,35,50,-1,-1,-1,-1},
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
	creatureBitmask = PACK + HERD + KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_lost_aqualish_marshal_female_01.iff"},
	lootgroups = {},
	weapons = {"pirate_weapons_heavy"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(lost_aqualish_marshall, "lost_aqualish_marshall")