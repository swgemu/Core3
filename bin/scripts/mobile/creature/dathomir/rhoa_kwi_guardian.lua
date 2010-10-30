rhoa_kwi_guardian = Creature:new {
	objectName = "rhoa kwi guardian",
	socialGroup = "Rhoa Kwi",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 4461,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {40,65,0,80,0,0,15,0,-1},
	meatType = "meat_carnivore",
	meatAmount = 120,
	hideType = "hide_leathery",
	hideAmount = 86,
	boneType = "bone_mammal",
	boneAmount = 76,
	milk = 0,
	tamingChance = 0.150000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/kwi.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(rhoa_kwi_guardian, "rhoa_kwi_guardian")