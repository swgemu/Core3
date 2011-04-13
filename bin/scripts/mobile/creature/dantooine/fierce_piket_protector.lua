fierce_piket_protector = Creature:new {
	objectName = "@mob/creature_names:fierce_piket_protector",
	socialGroup = "Piket",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.450000,
	damageMin = 355,
	damageMax = 420,
	baseXp = 4461,
	baseHAM = 10900,
	baseHAMmax = 10900,
	armor = 0,
	resists = {50,55,-1,0,-1,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_scaley",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/piket.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"dizzyattack","dizzyChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(fierce_piket_protector, "fierce_piket_protector")