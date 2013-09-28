package.path = package.path .. ";scripts/managers/?.lua"
require("jedi_manager")

jediManagerName = "HolocronJediManager"

NUMBEROFPROFESSIONSTOMASTER = 6

HolocronJediManager = JediManager:new {
	jediManagerName = jediManagerName,
	jediProgressionType = HOLOCRONJEDIPROGRESSION,
	startingEvent = nil,
}

function HolocronJediManager:getGrindableProfessionList()
	local grindableProfessions = {
		-- String Id, badge number
		--{ "pilot_rebel_navy_corellia", 		131 },
		--{ "pilot_imperial_navy_corellia", 	134 },
		--{ "pilot_neutral_corellia", 		137 },
		--{ "pilot_rebel_navy_tatooine", 		132 },
		--{ "pilot_imperial_navy_naboo", 		133 },
		{ "crafting_architect_master", 		54  },
		{ "crafting_armorsmith_master", 	55  },
		{ "crafting_artisan_master", 		56  },
		{ "outdoors_bio_engineer_master", 	62  },
		{ "combat_bountyhunter_master", 	44  },
		{ "combat_brawler_master", 		45  },
		{ "combat_carbine_master", 		46  },
		{ "crafting_chef_master", 		57  },
		{ "science_combatmedic_master", 	67  },
		{ "combat_commando_master", 		47  },
		--{ "outdoors_creaturehandler_master", 	63  },
		{ "social_dancer_master", 		70  },
		{ "science_doctor_master", 		68  },
		{ "crafting_droidengineer_master", 	58  },
		{ "social_entertainer_master", 		71  },
		{ "combat_1hsword_master", 		42  },
		{ "social_imagedesigner_master", 	72  },
		{ "combat_marksman_master", 		48  },
		{ "science_medic_master", 		69  },
		{ "crafting_merchant_master", 		59  },
		{ "social_musician_master", 		73  },
		{ "combat_polearm_master", 		50  },
		{ "combat_pistol_master", 		49  },
		{ "social_politician_master", 		74  },
		{ "outdoors_ranger_master", 		64  },
		{ "combat_rifleman_master", 		51  },
		{ "outdoors_scout_master", 		65  },
		--{ "crafting_shipwright", 		129 },
		{ "combat_smuggler_master", 		52  },
		{ "outdoors_squadleader_master", 	66  },
		{ "combat_2hsword_master", 		43  },
		{ "crafting_tailor_master", 		60  },
		{ "crafting_weaponsmith_master", 	61  },
		--{ "pilot_neutral_naboo", 		136 },
		--{ "pilot_neutral_tatooine", 		138 },
		--{ "pilot_imperial_navy_tatooine", 	135 },
		{ "combat_unarmed_master", 		53  },
		--{ "pilot_rebel_navy_naboo", 		130 }
	}
	return grindableProfessions
end

function HolocronJediManager:onPlayerCreation(pCreature)
	if (pCreature == nil) then
		return
	end

	local skillList = self:getGrindableProfessionList()

	local creature = LuaCreatureObject(pCreature)

	local pPlayer = creature.getPlayerObject()

	if (pPlayer == nil) then
		return
	end

	local player = LuaPlayerObject(pPlayer)

	for i = 1, NUMBEROFPROFESSIONSTOMASTER, 1 do
		local numberOfSkillsInList = table.getn(skillList)
		local skillNumber = math.random(1, numberOfSkillsInList)
		player.addHologrindProfession(skillList[skillNumber][2])
		table.remove(skillList, skillNumber)
	end
end
