arachne_fleshripper = Creature:new {
	objectName = "@mob/creature_names:arachne_fleshripper",
	socialGroup = "arachne",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.36,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 7700,
	baseHAMmax = 9400,
	armor = 0,
	resists = {10,40,-1,20,20,15,20,15,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.05,
	ferocity = 10,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + KILLER + STALKER,
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/angler_hue.iff"},
	lootGroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	conversationTemplate = "",
	attacks = {
		{"posturedownattack","postureDownChance=50"},
		{"strongpoison",""}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_fleshripper, "arachne_fleshripper")