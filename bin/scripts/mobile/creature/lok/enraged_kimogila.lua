enraged_kimogila = Creature:new {
	objectName = "@mob/creature_names:enraged_kimogila",
	socialGroup = "Kimogila",
	pvpFaction = "",
	faction = "",
	level = 135,
	chanceHit = 4.750000,
	damageMin = 920,
	damageMax = 1550,
	baseXp = 12801,
	baseHAM = 55500,
	baseHAMmax = 55500,
	armor = 0,
	resists = {45,70,45,70,45,40,100,45,-1},
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
		{"knockdownattack","knockdownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_kimogila, "enraged_kimogila")