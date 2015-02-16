drognuz = Creature:new {
	objectName = "",
	customName = "Drognuz",
	socialGroup = "jabba",
	faction = "jabba",
	level = 14,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 650,
	baseHAM = 2550,
	baseHAMmax = 2700,
	armor = 0,
	resists = {0,0,0,0,0,0,0,-1,-1},
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
	creatureBitmask = KILLER,
	optionsBitmask = 128,
	diet = HERBIVORE,

	templates = {"object/mobile/gamorrean.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3500000},
				{group = "armor_all", chance = 2000000},
				{group = "melee_weapons", chance = 2500000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000}
			},
			lootChance = 2200000
		}				
	},
	weapons = {"gamorrean_weapons"},
	conversationTemplate = "",
	attacks = merge(marksmanmid,brawlermid)
}

CreatureTemplates:addCreatureTemplate(drognuz, "drognuz")
