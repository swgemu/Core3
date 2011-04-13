crazed_gurreck = Creature:new {
	objectName = "@mob/creature_names:crazed_gurreck",
	socialGroup = "Gurreck",
	pvpFaction = "",
	faction = "",
	level = 25,
	chanceHit = 0.360000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2543,
	baseHAM = 5000,
	baseHAMmax = 5000,
	armor = 0,
	resists = {0,30,0,0,0,0,-1,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_wooly",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER,
	diet = CARNIVORE,

	templates = {"object/mobile/gurreck.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(crazed_gurreck, "crazed_gurreck")