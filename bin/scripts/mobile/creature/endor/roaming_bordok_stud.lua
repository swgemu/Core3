roaming_bordok_stud = Creature:new {
	objectName = "@mob/creature_names:roaming_bordok_stud",
	socialGroup = "Bordok",
	pvpFaction = "",
	faction = "",
	level = 34,
	chanceHit = 0.410000,
	damageMin = 330,
	damageMax = 370,
	baseXp = 3370,
	baseHAM = 10000,
	baseHAMmax = 10000,
	armor = 0,
	resists = {0,-1,0,100,100,0,-1,-1,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "bone_mammal",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/bordok.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"dizzyattack","dizzyChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(roaming_bordok_stud, "roaming_bordok_stud")