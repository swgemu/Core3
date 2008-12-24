update skills set skill_commands = "private_scout_novice,harvestCorpse,throwWiredMeshTrap,throwLecepaninDart" where skill_name like "%scout_novice%";
update skills set skill_commands = "private_scout_tools_1,throwGlowJuiceTrap,throwSharpBoneSpur" where skill_name like "%scout_tools_01%";
update skills set skill_commands = "private_scout_tools_2,throwNoiseMaker,throwStinkBomb" where skill_name like "%scout_tools_02%";
update skills set skill_commands = "private_scout_tools_3,throwGlowWireTrap,throwPhecnacineDart" where skill_name like "%scout_tools_03%";
update skills set skill_commands = "private_scout_tools_4,throwAdhesiveMesh" where skill_name like "%scout_tools_04%";

update skills set skill_commands = "throwFlashBomb" where skill_name like "%ranger_support_02%";
update skills set skill_commands = "throwSonicPulse" where skill_name like "%ranger_support_03%";


