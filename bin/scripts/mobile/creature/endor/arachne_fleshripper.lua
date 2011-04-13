arachne_fleshripper = Creature:new {
	objectName = "@mob/creature_names:arachne_fleshripper",
	socialGroup = "Arachne",
	pvpFaction = "",
	faction = "",
	level = 30,
	chanceHit = 0.360000,
	damageMin = 310,
	damageMax = 330,
	baseXp = 3097,
	baseHAM = 8550,
	baseHAMmax = 8550,
	armor = 0,
	resists = {10,40,-1,20,20,0,20,0,-1},
	meatType = "meat_insect",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.050000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/angler.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_toxicgreen"},
	attacks = {
		{"strongpoison",""},
		{"posturedownattack","postureDownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(arachne_fleshripper, "arachne_fleshripper")