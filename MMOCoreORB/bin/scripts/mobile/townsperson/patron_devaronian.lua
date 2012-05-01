patron_devaronian = Creature:new {
	objectName = "@mob/creature_names:patron_devaronian_male",
	socialGroup = "Townsperson",
	pvpFaction = "Townsperson",
	faction = "",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
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
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {
		"object/mobile/dressed_patron_devaronian_01.iff"
	},
	lootGroups = {},
	weapons = {"rebel_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(patron_devaronian, "patron_devaronian")