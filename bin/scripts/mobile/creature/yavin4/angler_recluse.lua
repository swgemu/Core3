angler_recluse = Creature:new {
	objectName = "@mob/creature_names:angler_recluse",
	socialGroup = "Angler",
	pvpFaction = "",
	faction = "",
	level = 26,
	chanceHit = 0.360000,
	damageMin = 250,
	damageMax = 260,
	baseXp = 2637,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {25,20,-1,0,0,-1,0,-1,-1},
	meatType = "meat_insect",
	meatAmount = 2,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = STALKER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/angler.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(angler_recluse, "angler_recluse")