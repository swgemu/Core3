ciwi_mosregri = Creature:new {
	objectName = "@npc_name:twilek_base_female",
	customName = "Ciwi Mo-sregri",
	socialGroup = "rebel",
	faction = "rebel",
	level = 6,
	chanceHit = 0.250000,
	damageMin = 50,
	damageMax = 55,
	baseXp = 113,
	baseHAM = 180,
	baseHAMmax = 220,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = NONE,
	creatureBitmask = HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_rebel_trooper_twk_female_01.iff"},
	lootGroups = {},
	weapons = {"rebel_weapons_light"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(ciwi_mosregri, "ciwi_mosregri")
