malkloc_plainswalker = Creature:new {
	objectName = "@mob/creature_names:malkloc_plainswalker",
	socialGroup = "Malkloc PW",
	pvpFaction = "",
	faction = "",
	level = 84,
	chanceHit = 0.700000,
	damageMin = 535,
	damageMax = 780,
	baseXp = 7945,
	baseHAM = 32500,
	baseHAMmax = 32500,
	armor = 0,
	resists = {100,50,0,-1,-1,-1,0,100,-1},
	meatType = "meat_herbivore",
	meatAmount = 1000,
	hideType = "hide_leathery",
	hideAmount = 1000,
	boneType = "bone_mammal",
	boneAmount = 1000,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/malkloc.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"creatureareaknockdown","knockdownChance=30"}
	}
}

CreatureTemplates:addCreatureTemplate(malkloc_plainswalker, "malkloc_plainswalker")