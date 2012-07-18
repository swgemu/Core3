gackle_bat_myrmidon_lord = Creature:new {
	objectName = "@mob/creature_names:gackle_bat_myrmidon_lord",
	socialGroup = "gacklebat",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.33,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 4100,
	baseHAMmax = 5000,
	armor = 0,
	resists = {15,20,-1,25,-1,-1,-1,-1,-1},
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
	optionsBitmask = 128,
	diet = CARNIVORE,

	templates = {"object/mobile/gackle_bat_hue.iff"},
	lootGroups = {},
	weapons = {},
	conversationTemplate = "",
	attacks = {
		{"blindattack","blindChance=50"},
		{"stunattack","stunChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gackle_bat_myrmidon_lord, "gackle_bat_myrmidon_lord")