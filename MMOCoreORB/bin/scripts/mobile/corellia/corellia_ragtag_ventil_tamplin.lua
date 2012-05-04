corellia_ragtag_ventil_tamplin = Creature:new {
	objectName = "@mob/creature_names:corellia_ragtag_ventil_tamplin",
	socialGroup = "Corellia Times",
	pvpFaction = "",
	faction = "",
	level = 10,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 356,
	baseHAM = 810,
	baseHAMmax = 990,
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
	pvpBitmask = NONE,
	creatureBitmask = PACK,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_blood_razor_pirate_captain_nikto_m.iff"
				},
	lootGroups = {},
	weapons = {"pirate_weapons_light"},
	conversationTemplate = "",
	attacks = {
	}
}

CreatureTemplates:addCreatureTemplate(corellia_ragtag_ventil_tamplin, "corellia_ragtag_ventil_tamplin")