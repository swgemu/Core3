rorgungan_boss = Creature:new {
	objectName = "@mob/creature_names:rorgungan_boss",
	randomNameType = NAME_GENERIC_TAG,
	socialGroup = "rorgungan",
	faction = "rorgungan",
	level = 22,
	chanceHit = 0.33,
	damageMin = 190,
	damageMax = 200,
	baseXp = 2006,
	baseHAM = 5000,
	baseHAMmax = 6100,
	armor = 0,
	resists = {25,25,0,-1,30,0,-1,-1,-1},
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
	creatureBitmask = PACK + HERD,
	diet = HERBIVORE,

	templates = {"object/mobile/gungan_s03_male.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 5500000},
				{group = "gungan_common", chance = 2000000},
				{group = "tailor_components", chance = 500000},
				{group = "loot_kit_parts", chance = 1500000},
				{group = "color_crystals", chance = 250000},
				{group = "crystals_poor", chance = 250000}
			}
		}
	},
	weapons = {"pirate_weapons_medium"},
	attacks = merge(brawlermaster,marksmanmaster)
}

CreatureTemplates:addCreatureTemplate(rorgungan_boss, "rorgungan_boss")
