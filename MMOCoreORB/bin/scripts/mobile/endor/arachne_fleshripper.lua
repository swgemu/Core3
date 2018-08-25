arachne_fleshripper = Creature:new {
	objectName = "@mob/creature_names:arachne_fleshripper",
	socialGroup = "arachne",
	faction = "",
	level = 30,
	chanceHit = 0.36,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {110,140,-1,120,120,15,120,15,-1},
	meatType = "meat_insect",
	meatAmount = 55,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/angler_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/angler_hue.iff",
	scale = 1.05,
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"strongpoison",""},
		{"posturedownattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_fleshripper, "arachne_fleshripper")
