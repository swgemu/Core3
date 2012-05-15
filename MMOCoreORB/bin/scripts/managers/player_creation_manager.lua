--Should all created players start with God Mode? 1 = yes, 0 = no
freeGodMode = 0;
--How many cash credits new characters start with after creating a character (changed during test phase, normal value is 100)
startingCash = 100
--startingCash = 100000
--How many bank credits new characters start with after creating a character (changed during test phase, normal value is 1000)
startingBank = 1000
--startingBank = 100000
--How many skill points a new characters start with
skillPoints = 250

professions = {
	"combat_brawler",
	"combat_marksman",
	"crafting_artisan",
	"jedi",
	"outdoors_scout",
	"science_medic",
	"social_entertainer"
}

cdefPistol = "object/weapon/ranged/pistol/pistol_cdef.iff"
	
cdefRifle = "object/weapon/ranged/rifle/rifle_cdef.iff"

cdefCarbine = "object/weapon/ranged/carbine/carbine_cdef.iff"

survivalKnife = "object/weapon/melee/knife/knife_survival.iff"

generic_tool = "object/tangible/crafting/station/generic_tool.iff"

mineral_tool = "object/tangible/survey_tool/survey_tool_mineral.iff"

chemical_tool = "object/tangible/survey_tool/survey_tool_liquid.iff"

slitherhorn = "object/tangible/instrument/slitherhorn.iff"

maroj_melon = "object/tangible/food/foraged/foraged_fruit_s1.iff"

professionSpecificItems = {
	combat_brawler = { survivalKnife },
	combat_marksman = { cdefPistol, cdefCarbine, cdefRifle },
	crafting_artisan = { cdefPistol, survivalKnife, generic_tool, mineral_tool, chemical_tool },
	jedi = { },
	outdoors_scout = { cdefPistol, generic_tool},
	science_medic = { cdefPistol, generic_tool, survivalKnife },
	social_entertainer = { cdefPistol, survivalKnife, slitherhorn }
}

commonStartingItems = { maroj_melon }
