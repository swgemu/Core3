mad_angler = Creature:new {
	objectName = "@mob/creature_names:mad_angler",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 95,
	chanceHit = 0.850000,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 9057,
	baseHAM = 14500,
	baseHAMmax = 14500,
	armor = 0,
	resists = {50,50,0,-1,0,-1,-1,0,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/angler.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"strongpoison",""},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(mad_angler, "mad_angler")