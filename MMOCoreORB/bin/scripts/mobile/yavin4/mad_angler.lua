mad_angler = Creature:new {
	objectName = "@mob/creature_names:mad_angler",
	socialGroup = "angler",
	faction = "",
	level = 95,
	chanceHit = 0.85,
	damageMin = 820,
	damageMax = 1350,
	baseXp = 9057,
	baseHAM = 13000,
	baseHAMmax = 16000,
	armor = 0,
	resists = {150,150,20,-1,20,-1,-1,20,-1},
	meatType = "meat_insect",
	meatAmount = 3,
	hideType = "hide_scaley",
	hideAmount = 6,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/angler_hue.iff"},
	scale = 1.4,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(mad_angler, "mad_angler")
