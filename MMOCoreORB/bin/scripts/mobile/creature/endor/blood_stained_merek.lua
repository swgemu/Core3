blood_stained_merek = Creature:new {
	objectName = "@mob/creature_names:blood_stained_merek",
	socialGroup = "Merek",
	pvpFaction = "",
	faction = "",
	level = 32,
	chanceHit = 0.400000,
	damageMin = 320,
	damageMax = 350,
	baseXp = 3279,
	baseHAM = 9550,
	baseHAMmax = 9550,
	armor = 0,
	resists = {-1,45,0,60,60,0,75,-1,-1},
	meatType = "meat_wild",
	meatAmount = 0,
	hideType = "hide_leathery",
	hideAmount = 45,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.250000,
	ferocity = 0,
	pvpBitmask = AGGRESSIVE + ATTACKABLE,
	creatureBitmask = KILLER + PACK,
	diet = CARNIVORE,

	templates = {"object/mobile/merek.iff"},
	lootgroups = {},
	weapons = {"creature_spit_small_red"},
	attacks = {
		{"knockdownattack","knockdownChance=50"}
	}
}

CreatureTemplates:addCreatureTemplate(blood_stained_merek, "blood_stained_merek")