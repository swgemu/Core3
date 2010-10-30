kimogila = Creature:new {
	objectName = "@monster_name:kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 95,
	chanceHit = 0.900000,
	damageMin = 630,
	damageMax = 970,
	baseXp = 9057,
	baseHAM = 24500,
	baseHAMmax = 24500,
	armor = 0,
	resists = {45,75,0,75,0,0,100,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kimogila.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"blindattack","blindChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(kimogila, "kimogila")