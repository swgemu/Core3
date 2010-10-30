Nyms_kusak_guardian = Creature:new {
	objectName = "Nym`s kusak guardian",
	socialGroup = "Nym",
	pvpFaction = "",
	faction = "",
	level = 29,
	chanceHit = 0.370000,
	damageMin = 270,
	damageMax = 280,
	baseXp = 2914,
	baseHAM = 9100,
	baseHAMmax = 9100,
	armor = 0,
	resists = {35,0,0,-1,-1,60,60,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kusak.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(Nyms_kusak_guardian, "Nyms_kusak_guardian")