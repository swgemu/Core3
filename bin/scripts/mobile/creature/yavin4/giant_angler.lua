giant_angler = Creature:new {
	objectName = "@mob/creature_names:giant_angler",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.410000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 9800,
	baseHAMmax = 9800,
	armor = 0,
	resists = {35,0,0,0,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.020000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_angler.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"strongpoison",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(giant_angler, "giant_angler")