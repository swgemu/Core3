kunga_clan_leader = Creature:new {
	objectName = "@mob/creature_names:kunga_clan_leader",
	socialGroup = "Kunga Tribe",
	pvpFaction = "Kunga Tribe",
	faction = "",
	level = 75,
	chanceHit = 0.750000,
	damageMin = 520,
	damageMax = 750,
	baseXp = 7207,
	baseHAM = 12000,
	baseHAMmax = 15000,
	armor = 0,
	resists = {0,60,-1,0,0,100,0,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0.000000,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER + HERD,
	diet = HERBIVORE,

	templates = {},
	lootgroups = {},
	weapons = {"primitive_weapons"},
	attacks = {}
}

CreatureTemplates:addCreatureTemplate(kunga_clan_leader, "kunga_clan_leader")