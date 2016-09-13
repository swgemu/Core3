gleeb_tchotle = Creature:new {
	objectName = "",
	customName = "Gleeb Tchotle",
	socialGroup = "townsperson",
	faction = "townsperson",
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
	pvpBitmask = ATTACKABLE,
	creatureBitmask = HERD,
	optionsBitmask = AIENABLED,
	diet = HERBIVORE,

	templates = {"object/mobile/dressed_patron_ishi_tib_01.iff"},
	lootGroups = {
		{
			groups = {
					{group = "task_loot_ledger_quest_serjix", chance = 10000000}
				},
			lootChance = 10000000
		}
	},
	weapons = {},
	attacks = merge(brawlermaster, teraskasinovice)
}

CreatureTemplates:addCreatureTemplate(gleeb_tchotle, "gleeb_tchotle")
