bark_mite_burrower = Creature:new {
	objectName = "@mob/creature_names:bark_mite_burrower",
	socialGroup = "Bark Mite",
	pvpFaction = "",
	faction = "",
	level = 55,
	chanceHit = 0.490000,
	damageMin = 415,
	damageMax = 540,
	baseXp = 5373,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {65,40,-1,80,-1,80,80,0,-1},
	meatType = "meat_insect",
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

	templates = {"object/mobile/bark_mite.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareableeding",""},
		{"strongdisease",""}
	}
}

CreatureTemplates:addCreatureTemplate(bark_mite_burrower, "bark_mite_burrower")