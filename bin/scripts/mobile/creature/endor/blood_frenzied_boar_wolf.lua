blood_frenzied_boar_wolf = Creature:new {
	objectName = "@mob/creature_names:blood_frenzied_boar_wolf",
	socialGroup = "Boar Wolf",
	pvpFaction = "",
	faction = "",
	level = 45,
	chanceHit = 0.440000,
	damageMin = 395,
	damageMax = 500,
	baseXp = 4461,
	baseHAM = 11000,
	baseHAMmax = 11000,
	armor = 0,
	resists = {0,0,0,75,75,-1,0,-1,-1},
	meatType = "meat_carnivore",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/boar_wolf.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"creatureareableeding",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blood_frenzied_boar_wolf, "blood_frenzied_boar_wolf")