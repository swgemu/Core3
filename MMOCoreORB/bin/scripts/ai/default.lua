aggroDefault = {
	{id="2009948435",	name="Sequence",	pid="none"},
	{id="1351912750",	name="If",	pid="2009948435"},
	{id="3646194541",	name="CheckProspectAggression",	pid="1351912750"},
	{id="2493941910",	name="If",	pid="2009948435"},
	{id="1725623190",	name="CheckProspectInRange",	pid="2493941910",	args={condition=0.0}},
	{id="4287005799",	name="If",	pid="2009948435"},
	{id="415432002",	name="CheckProspectLOS",	pid="4287005799"},
	{id="199246519",	name="SetDefenderFromProspect",	pid="2009948435"}}
addAiTemplate("aggroDefault", aggroDefault)

attackDefault = {
	{id="4024177786",	name="Sequence",	pid="none"},
	{id="2812006626",	name="RandomSelector",	pid="4024177786"},
	{id="2322819263",	name="WriteBlackboard",	pid="2812006626",	args={key="attackType", val=DEFAULT}},
	{id="1793608263",	name="EraseBlackboard",	pid="2812006626",	args={param="attackType"}},
	{id="1011850080",	name="EraseBlackboard",	pid="2812006626",	args={param="attackType"}},
	{id="2342191700",	name="EraseBlackboard",	pid="2812006626",	args={param="attackType"}},
	{id="1163120514",	name="EraseBlackboard",	pid="2812006626",	args={param="attackType"}},
	{id="2329787886",	name="SelectAttack",	pid="4024177786",	args={attackNum=-1}},
	{id="180351178",	name="EnqueueAttack",	pid="4024177786"},
	{id="302238494",	name="Selector",	pid="4024177786"},
	{id="3604417668",	name="Sequence",	pid="302238494"},
	{id="763264896",	name="If",	pid="3604417668"},
	{id="1728591479",	name="CheckAttackInRange",	pid="763264896"},
	{id="807085653",	name="If",	pid="3604417668"},
	{id="728357096",	name="CheckAttackIsValid",	pid="807085653"},
	{id="285069068",	name="Sequence",	pid="302238494"},
	{id="4146066819",	name="WriteBlackboard",	pid="285069068",	args={key="attackType", val=DEFAULT}},
	{id="2582933389",	name="SelectAttack",	pid="285069068",	args={attackNum=-1}},
	{id="2327622682",	name="EnqueueAttack",	pid="285069068"}}
addAiTemplate("attackDefault", attackDefault)

awareDefault = {
	{id="4104990252",	name="Selector",	pid="none"},
	{id="48836146",	name="LookForTarget",	pid="4104990252"},
	{id="1957246555",	name="Sequence",	pid="48836146"},
	{id="2060697202",	name="CalculateAggroMod",	pid="1957246555"},
	{id="3934686138",	name="If",	pid="1957246555"},
	{id="3559324712",	name="CheckProspectInRange",	pid="3934686138",	args={condition=0.0}},
	{id="1945988400",	name="TreeSocket",	pid="1957246555",	args={slot=LOOKAT}},
	{id="2161122682",	name="Sequence",	pid="1957246555"},
	{id="1918093601",	name="Selector",	pid="2161122682"},
	{id="3395891290",	name="If",	pid="1918093601"},
	{id="1548623514",	name="CheckFollowState",	pid="3395891290",	args={condition=WATCHING}},
	{id="2148110810",	name="If",	pid="1918093601"},
	{id="3238596965",	name="CheckFollowState",	pid="2148110810",	args={condition=STALKING}},
	{id="2555066128",	name="Selector",	pid="2161122682"},
	{id="3457280844",	name="Sequence",	pid="2555066128"},
	{id="2660217776",	name="If",	pid="3457280844"},
	{id="1619483218",	name="CheckAggroDelayPast",	pid="2660217776"},
	{id="2566615919",	name="TreeSocket",	pid="3457280844",	args={slot=AGGRO}},
	{id="302020086",	name="TreeSocket",	pid="2555066128",	args={slot=SCARE}},
	{id="1616859664",	name="TreeSocket",	pid="4104990252",	args={slot=KILL}},
	{id="3482658823",	name="AlwaysFail",	pid="4104990252"},
	{id="3501565905",	name="Sequence",	pid="3482658823"},
	{id="2093683538",	name="EraseBlackboard",	pid="3501565905",	args={param="aggroMod"}},
	{id="4067732234",	name="EraseBlackboard",	pid="3501565905",	args={param="targetProspect"}}}
addAiTemplate("awareDefault", awareDefault)

equipDefault = {
	{id="2941044245",	name="ParallelSequence",	pid="none"},
	{id="1893489794",	name="Sequence",	pid="2941044245"},
	{id="475418752",	name="UpdateRangeToFollow",	pid="1893489794"},
	{id="3588683982",	name="Selector",	pid="1893489794"},
	{id="284029936",	name="Sequence",	pid="3588683982"},
	{id="848281294",	name="If",	pid="284029936"},
	{id="2143400703",	name="CheckFollowInWeaponRange",	pid="848281294",	args={condition=PRIMARYWEAPON}},
	{id="3507834914",	name="If",	pid="284029936"},
	{id="1423335520",	name="CheckFollowClosestIdealRange",	pid="3507834914",	args={condition=PRIMARYWEAPON}},
	{id="485346421",	name="WriteBlackboard",	pid="284029936",	args={key="stagedWeapon", val=PRIMARYWEAPON}},
	{id="3286553516",	name="Sequence",	pid="3588683982"},
	{id="4256376058",	name="If",	pid="3286553516"},
	{id="1599543891",	name="CheckFollowInWeaponRange",	pid="4256376058",	args={condition=SECONDARYWEAPON}},
	{id="3111019196",	name="If",	pid="3286553516"},
	{id="3429738785",	name="CheckFollowClosestIdealRange",	pid="3111019196",	args={condition=SECONDARYWEAPON}},
	{id="2825297726",	name="WriteBlackboard",	pid="3286553516",	args={key="stagedWeapon", val=SECONDARYWEAPON}},
	{id="1510007529",	name="EquipStagedWeapon",	pid="1893489794"},
	{id="2512472344",	name="EraseBlackboard",	pid="2941044245",	args={param="stagedWeapon"}},
	{id="4004759019",	name="EraseBlackboard",	pid="2941044245",	args={param="followRange"}}}
addAiTemplate("equipDefault", equipDefault)

killDefault = {
	{id="3446643166",	name="Sequence",	pid="none"},
	{id="2438979001",	name="If",	pid="3446643166"},
	{id="1145316404",	name="CheckIsKiller",	pid="2438979001"},
	{id="3202537488",	name="If",	pid="3446643166"},
	{id="3792349256",	name="CheckProspectIsIncapacitated",	pid="3202537488"},
	{id="3121274485",	name="If",	pid="3446643166"},
	{id="1800910595",	name="CheckProspectInRange",	pid="3121274485",	args={condition=0.0}},
	{id="3171471690",	name="If",	pid="3446643166"},
	{id="3828589773",	name="CheckProspectLOS",	pid="3171471690"},
	{id="1512963980",	name="KillProspect",	pid="3446643166"}}
addAiTemplate("killDefault", killDefault)

lookDefault = {
	{id="2391667584",	name="Sequence",	pid="none"},
	{id="3448746212",	name="Selector",	pid="2391667584"},
	{id="1241082520",	name="If",	pid="3448746212"},
	{id="3119101863",	name="CheckFollowState",	pid="1241082520",	args={condition=OBLIVIOUS}},
	{id="1654495102",	name="If",	pid="3448746212"},
	{id="196345155",	name="CheckFollowState",	pid="1654495102",	args={condition=WATCHING}},
	{id="4062139516",	name="If",	pid="3448746212"},
	{id="1006667864",	name="CheckFollowState",	pid="4062139516",	args={condition=PATROLLING}},
	{id="1650016708",	name="If",	pid="2391667584"},
	{id="638753146",	name="CheckProspectLOS",	pid="1650016708"},
	{id="4076527471",	name="SetFollowState",	pid="2391667584",	args={state=WATCHING}},
	{id="411818367",	name="Not",	pid="2391667584"},
	{id="3870509434",	name="If",	pid="411818367"},
	{id="673698221",	name="CheckProspectIsIncapacitated",	pid="3870509434"},
	{id="2037171568",	name="AlwaysSucceed",	pid="2391667584"},
	{id="1583995406",	name="SetAlert",	pid="2037171568",	args={duration=10.0, show=1}}}
addAiTemplate("lookDefault", lookDefault)

moveDefault = {
	{id="95757095",	name="Selector",	pid="none"},
	{id="2725427749",	name="Not",	pid="95757095"},
	{id="2494411167",	name="Sequence",	pid="2725427749"},
	{id="4016651762",	name="If",	pid="2494411167"},
	{id="938685055",	name="CheckPosture",	pid="4016651762",	args={condition=UPRIGHT}},
	{id="2354494630",	name="If",	pid="2494411167"},
	{id="1233890036",	name="CheckDestination",	pid="2354494630",	args={condition=0.0}},
	{id="1049607122",	name="Sequence",	pid="95757095"},
	{id="361808887",	name="If",	pid="1049607122"},
	{id="1901811754",	name="CheckRetreat",	pid="361808887",	args={condition=256}},
	{id="4131275375",	name="Leash",	pid="1049607122"},
	{id="3937110156",	name="ParallelSelector",	pid="95757095"},
	{id="3859304677",	name="Evade",	pid="3937110156",	args={maxEvadeChance=0.07, minEvadeChance=0.02}},
	{id="3690551020",	name="FindNextPosition",	pid="3937110156"}}
addAiTemplate("moveDefault", moveDefault)

rootDefault = {
	{id="714360210",	name="Selector",	pid="none"},
	{id="4192507528",	name="Sequence",	pid="714360210"},
	{id="112941615",	name="TreeSocket",	pid="4192507528",	args={slot=TARGET}},
	{id="1711463331",	name="ParallelSelector",	pid="4192507528"},
	{id="3085594992",	name="Sequence",	pid="1711463331"},
	{id="2197461733",	name="TreeSocket",	pid="3085594992",	args={slot=EQUIP}},
	{id="1754584012",	name="TreeSocket",	pid="3085594992",	args={slot=ATTACK}},
	{id="3434357109",	name="Sequence",	pid="1711463331"},
	{id="2676240638",	name="WriteBlackboard",	pid="3434357109",	args={key="moveMode", val=RUN}},
	{id="4148461600",	name="AlwaysSucceed",	pid="3434357109"},
	{id="4224133747",	name="TreeSocket",	pid="4148461600",	args={slot=MOVE}},
	{id="3497802169",	name="TreeSocket",	pid="714360210",	args={slot=AWARE}},
	{id="1848102505",	name="TreeSocket",	pid="714360210",	args={slot=IDLE}}}
addAiTemplate("rootDefault", rootDefault)

scareDefault = {
	{id="9692099",	name="Sequence",	pid="none"},
	{id="1540135288",	name="If",	pid="9692099"},
	{id="1764032694",	name="CheckOutdoors",	pid="1540135288"},
	{id="700140749",	name="If",	pid="9692099"},
	{id="3760018670",	name="CheckProspectLevel",	pid="700140749"},
	{id="3822915915",	name="If",	pid="9692099"},
	{id="223077338",	name="CheckProspectBackAggression",	pid="3822915915"},
	{id="3929926457",	name="If",	pid="9692099"},
	{id="3129896739",	name="CheckProspectSpeed",	pid="3929926457",	args={condition=FAST}},
	{id="4278456295",	name="If",	pid="9692099"},
	{id="4154513359",	name="CheckProspectFacing",	pid="4278456295"},
	{id="3009279984",	name="If",	pid="9692099"},
	{id="1391512006",	name="CheckProspectLOS",	pid="3009279984"},
	{id="2633134651",	name="RunAway",	pid="9692099",	args={dist=64.0}},
	{id="3135988450",	name="SetAlert",	pid="9692099",	args={duration=10.0, show=0}}}
addAiTemplate("scareDefault", scareDefault)

targetDefault = {
	{id="4111738087",	name="Selector",	pid="none"},
	{id="3879553011",	name="Sequence",	pid="4111738087"},
	{id="3082634307",	name="Sequence",	pid="3879553011"},
	{id="2109205448",	name="AlwaysSucceed",	pid="3082634307"},
	{id="417268659",	name="Selector",	pid="2109205448"},
	{id="1167160726",	name="GetProspectFromThreatMap",	pid="417268659"},
	{id="518009030",	name="GetProspectFromDefenders",	pid="417268659"},
	{id="1116588539",	name="Selector",	pid="3082634307"},
	{id="2048074292",	name="If",	pid="1116588539"},
	{id="2151843468",	name="CheckTargetIsValid",	pid="2048074292"},
	{id="3200087626",	name="AlwaysFail",	pid="1116588539"},
	{id="4242405620",	name="Sequence",	pid="3200087626"},
	{id="70282946",	name="DropProspectFromDefenders",	pid="4242405620"},
	{id="1667318362",	name="EraseBlackboard",	pid="4242405620",	args={param="targetProspect"}},
	{id="1198270730",	name="SetDefenderFromProspect",	pid="3082634307"},
	{id="2169906593",	name="AlwaysSucceed",	pid="3082634307"},
	{id="801245995",	name="Sequence",	pid="2169906593"},
	{id="2064919983",	name="If",	pid="801245995"},
	{id="1297959577",	name="CheckProspectIsType",	pid="2064919983",	args={condition=PLAYERTYPE}},
	{id="2449360311",	name="If",	pid="801245995"},
	{id="1840187439",	name="CheckIsKiller",	pid="2449360311"},
	{id="2430725850",	name="If",	pid="801245995"},
	{id="455203671",	name="CheckProspectIsIncapacitated",	pid="2430725850"},
	{id="474513793",	name="TreeSocket",	pid="801245995",	args={slot=KILL}},
	{id="2799331507",	name="AlwaysSucceed",	pid="3879553011"},
	{id="1092122064",	name="Sequence",	pid="2799331507"},
	{id="760406382",	name="If",	pid="1092122064"},
	{id="1263807142",	name="CheckFollowHasState",	pid="760406382",	args={condition=PEACE}},
	{id="3243539519",	name="If",	pid="1092122064"},
	{id="907649009",	name="CheckRandomLevel",	pid="3243539519",	args={condition=1}},
	{id="4235079436",	name="Not",	pid="1092122064"},
	{id="2741672315",	name="If",	pid="4235079436"},
	{id="3481038322",	name="CheckFollowAggression",	pid="2741672315"},
	{id="2102245599",	name="ExitCombat",	pid="1092122064",	args={clearDefenders=1}},
	{id="2289904783",	name="AlwaysFail",	pid="4111738087"},
	{id="3752919331",	name="ExitCombat",	pid="2289904783",	args={clearDefenders=1}}}
addAiTemplate("targetDefault", targetDefault)

wanderDefault = {
	{id="1564905074",	name="Selector",	pid="none"},
	{id="4029863740",	name="Sequence",	pid="1564905074"},
	{id="3655407871",	name="If",	pid="4029863740"},
	{id="523920708",	name="CheckHasPatrol",	pid="3655407871"},
	{id="536389142",	name="WriteBlackboard",	pid="4029863740",	args={key="moveMode", val=WALK}},
	{id="3269636266",	name="TreeSocket",	pid="4029863740",	args={slot=MOVE}},
	{id="2038642946",	name="Wait",	pid="4029863740",	args={duration=10.0}},
	{id="1529860918",	name="Sequence",	pid="1564905074"},
	{id="529086427",	name="If",	pid="1529860918"},
	{id="636152133",	name="CheckOutdoors",	pid="529086427"},
	{id="2390998747",	name="GeneratePatrol",	pid="1529860918",	args={distFromHome=10.0, numPoints=5}}}
addAiTemplate("wanderDefault", wanderDefault)

