disciple_of_lord_nyax = Creature:new {
	objectName = "@mob/creature_names:lord_nyax_disciple",
	socialGroup = "Lord Nyax",
	pvpFaction = "Lord Nyax",
	faction = "",
	level = 16,
	chanceHit = 0.31,
	damageMin = 160,
	damageMax = 170,
	baseXp = 1102,
	baseHAM = 2400,
	baseHAMmax = 3000,
	armor = 0,
	resists = {5,15,5,5,-1,-1,5,-1,-1},
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
	creatureBitmask = PACK + KILLER + HEALER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/human_male.iff"},
	lootGroups = {
		{
			groups = {
				{group = "nyax", chance = 1000000},
				{group = "pistols", chance = 4500000},
				{group = "rifles", chance = 4500000}
			},
			lootChance = 3800000
		}
	},
	weapons = {"ranged_weapons"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(disciple_of_lord_nyax, "disciple_of_lord_nyax")