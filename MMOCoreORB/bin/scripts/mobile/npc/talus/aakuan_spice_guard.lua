aakuan_spice_guard = Creature:new {
	objectName = "@mob/creature_names:Aa'kuan spice guard",
	socialGroup = "Aa'kuan",
	pvpFaction = "Aa'kuan",
	faction = "",
	level = 27,
	chanceHit = 0.36,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2822,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {30,30,-1,0,0,-1,0,-1,-1},
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

	templates = {"object/mobile/dressed_aakuan_defender_human_male_01.iff"},
	lootgroups = {},
	weapons = {"melee_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(aakuan_spice_guard, "aakuan_spice_guard")