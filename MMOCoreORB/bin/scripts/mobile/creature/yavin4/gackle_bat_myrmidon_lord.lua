gackle_bat_myrmidon_lord = Creature:new {
	objectName = "@mob/creature_names:gackle_bat_myrmidon_lord",
	socialGroup = "Gacklebat",
	pvpFaction = "",
	faction = "",
	level = 20,
	chanceHit = 0.330000,
	damageMin = 210,
	damageMax = 220,
	baseXp = 1803,
	baseHAM = 4550,
	baseHAMmax = 4550,
	armor = 0,
	resists = {15,20,-1,25,-1,-1,-1,-1,-1},
	meatType = "meat_avian",
	meatAmount = 10,
	hideType = "hide_leathery",
	hideAmount = 10,
	boneType = "bone_avian",
	boneAmount = 10,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + STALKER + PACK + HERD,
	diet = CARNIVORE,

	templates = {"object/mobile/gackle_bat.iff"},
	lootgroups = {},
	weapons = {},
	attacks = {
		{"stunattack","stunChance=50"},
		{"blindattack","blindChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(gackle_bat_myrmidon_lord, "gackle_bat_myrmidon_lord")