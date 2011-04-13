enraged_defender = Creature:new {
	objectName = "@mob/creature_names:piket_enraged_defender",
	socialGroup = "Piket",
	pvpFaction = "",
	faction = "",
	level = 49,
	chanceHit = 0.470000,
	damageMin = 385,
	damageMax = 480,
	baseXp = 4734,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {40,40,20,0,0,0,0,0,-1},
	meatType = "meat_herbivore",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK,
	diet = HERBIVORE,

	templates = {"object/mobile/piket.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(enraged_defender, "enraged_defender")