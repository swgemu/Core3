imperial_captain = Creature:new {
	objectName = "@mob/creature_names:crackdown_imperial_army_captain",
	socialGroup = "imperial",
	pvpFaction = "imperial",
	faction = "imperial",
	level = 30,
	chanceHit = 0.39,
	damageMin = 290,
	damageMax = 300,
	baseXp = 2914,
	baseHAM = 8400,
	baseHAMmax = 10200,
	armor = 0,
	resists = {0,45,0,-1,40,-1,40,-1,-1},
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
	creatureBitmask = NONE,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_imperial_captain_m.iff"},
	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 5650000},
				{group = "rifles", chance = 550000},
				{group = "pistols", chance = 550000},
				{group = "melee_weapons", chance = 550000},
				{group = "carbines", chance = 550000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000},
				{group = "imperial_officer_common", chance = 450000},
				{group = "wearables_common", chance = 1000000}
			},
			lootChance = 2900000
		}
	},
	weapons = {"imperial_weapons_medium"},
	attacks = merge(riflemanmaster,carbineermaster,brawlermaster),
	conversationTemplate = "imperialRecruiterConvoTemplate",
	optionsBitmask = 136
}

CreatureTemplates:addCreatureTemplate(imperial_captain, "imperial_captain")
