giant_angler = Creature:new {
	objectName = "@mob/creature_names:giant_angler",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 35,
	chanceHit = 0.41,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3460,
	baseHAM = 8800,
	baseHAMmax = 10800,
	armor = 0,
	resists = {35,25,25,25,25,-1,25,-1,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.02,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/giant_angler.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(giant_angler, "giant_angler")