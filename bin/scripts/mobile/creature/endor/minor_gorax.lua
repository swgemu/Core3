minor_gorax = Creature:new {
	objectName = "@mob/creature_names:minor_gorax",
	socialGroup = "Gorax",
	pvpFaction = "",
	faction = "",
	level = 131,
	chanceHit = 4.000000,
	damageMin = 745,
	damageMax = 1200,
	baseXp = 12424,
	baseHAM = 99000,
	baseHAMmax = 99000,
	armor = 0,
	resists = {65,65,50,50,50,0,50,50,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/gorax.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareaattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(minor_gorax, "minor_gorax")