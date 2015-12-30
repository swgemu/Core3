fbase_stormtrooper_sniper = Creature:new {
	objectName = "@mob/creature_names:fbase_stormtrooper_sniper",
	randomNameType = NAME_STORMTROOPER,
	randomNameTag = true,
	socialGroup = "imperial",
	faction = "imperial",
	level = 39,
	chanceHit = 0.44,
	damageMin = 340,
	damageMax = 390,
	baseXp = 3900,
	baseHAM = 9300,
	baseHAMmax = 11300,
	armor = 0,
	resists = {110,110,140,15,15,15,15,-1,-1},
	meatType = "",
	meatAmount = 0,
	hideType = "",
	hideAmount = 0,
	boneType = "",
	boneAmount = 0,
	milk = 0,
	tamingChance = 0,
	ferocity = 0,
	pvpBitmask = ATTACKABLE,
	creatureBitmask = PACK + KILLER,
	diet = HERBIVORE,
	scale = 1.05,

	templates = {"object/mobile/dressed_stormtrooper_sniper_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 6000000},
				{group = "weapons_all", chance = 1200000},
				{group = "armor_all", chance = 1200000},
				{group = "clothing_attachments", chance = 150000},
				{group = "armor_attachments", chance = 150000},
				{group = "stormtrooper_common", chance = 200000},
				{group = "wearables_all", chance = 1000000}
			}
		}
	},
	weapons = {"st_sniper_weapons"},
	reactionStf = "@npc_reaction/stormtrooper",
	attacks = merge(riflemannovice,brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(fbase_stormtrooper_sniper, "fbase_stormtrooper_sniper")
