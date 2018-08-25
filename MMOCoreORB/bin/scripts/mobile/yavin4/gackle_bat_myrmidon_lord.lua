gackle_bat_myrmidon_lord = Creature:new {
	objectName = "@mob/creature_names:gackle_bat_myrmidon_lord",
	socialGroup = "gacklebat",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {115,120,-1,125,-1,-1,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 10,
	boneType = "bone_avian",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.25,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE + ENEMY,
	creatureBitmask = PACK + HERD + KILLER + STALKER,
	optionsBitmask = AIENABLED,
	diet = CARNIVORE,

	templates = {"object/mobile/gackle_bat_hue.iff"},
	hues = { 16, 17, 18, 19, 20, 21, 22, 23 },
	controlDeviceTemplate = "object/intangible/pet/gackle_bat_hue.iff",
	scale = 1.3,
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"stunattack",""},
		{"blindattack",""}
	}
}

CreatureTemplates:addCreatureTemplate(gackle_bat_myrmidon_lord, "gackle_bat_myrmidon_lord")
