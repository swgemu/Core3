rath_kanaz = Creature:new {
	objectName = "",
	customName = "Rath Kanaz",
	socialGroup = "self",
	pvpFaction = "",
	faction = "",
	level = 23,
	chanceHit = 0.28,
	damageMin = 90,
	damageMax = 110,
	baseXp = 870,
	baseHAM = 3200,
	baseHAMmax = 3400,
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

	templates = {"object/mobile/ig_assassin_droid.iff"},
	lootGroups = {
		{
			groups = {
				{group = "junk", chance = 3500000},
				{group = "grenades_looted", chance = 1000000},
				{group = "armor_all", chance = 1500000},
				{group = "pistols", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "tailor_components", chance = 1000000},
				{group = "loot_kit_parts", chance = 1000000}
			},
			lootChance = 2400000
		}				
	},
	conversationTemplate = "",
	defaultWeapon = "object/weapon/ranged/droid/droid_droideka_ranged.iff",
	defaultAttack = "creaturerangedattack"
}

CreatureTemplates:addCreatureTemplate(rath_kanaz, "rath_kanaz")
