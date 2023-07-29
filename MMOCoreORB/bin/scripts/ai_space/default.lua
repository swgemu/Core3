attackDefault = {
	{id="682767326",	name="SelectorSpace",	pid="none"},
	{id="2870874038",	name="SequenceSpace",	pid="682767326"},
	{id="445019167",	name="IfSpace",	pid="2870874038"},
	{id="830690666",	name="CheckEvadeChance",	pid="445019167",	args={chance=10}},
	{id="2209712730",	name="SetMovementState",	pid="2870874038",	args={state=EVADING}},
	{id="1083156400",	name="Evade",	pid="2870874038",	args={evadeDelay=1500}},
	{id="2274822948",	name="AlwaysSucceedSpace",	pid="682767326"},
	{id="420201148",	name="SequenceSpace",	pid="2274822948"},
	{id="2376148965",	name="IfSpace",	pid="420201148"},
	{id="1470595374",	name="CheckRefireRate",	pid="2376148965",	args={condition=500}},
	{id="533445839",	name="EngageTarget",	pid="420201148"}}
addAiTemplate("attackDefault", attackDefault)

awareDefault = {
	{id="1214404540",	name="SequenceSpace",	pid="none"},
	{id="1915611982",	name="NotSpace",	pid="1214404540"},
	{id="2125777402",	name="IfSpace",	pid="1915611982"},
	{id="3574561166",	name="CheckMovementState",	pid="2125777402",	args={condition=WATCHING}},
	{id="2152617010",	name="LookForTargetSpace",	pid="1214404540"},
	{id="83649144",	name="SequenceSpace",	pid="2152617010"},
	{id="765304253",	name="CalculateAggroMod",	pid="83649144"},
	{id="4225492471",	name="IfSpace",	pid="83649144"},
	{id="2515118288",	name="CheckProspectInRange",	pid="4225492471"},
	{id="934410611",	name="TreeSocketSpace",	pid="83649144",	args={slot=LOOKATSPACE}}}
addAiTemplate("awareDefault", awareDefault)

evadeDefault = {
	{id="2602567462",	name="SequenceSpace",	pid="none"},
	{id="4002815204",	name="IfSpace",	pid="2602567462"},
	{id="2649809160",	name="CheckMovementState",	pid="4002815204",	args={condition=EVADING}},
	{id="721046627",	name="SequenceSpace",	pid="2602567462"},
	{id="959847675",	name="IfSpace",	pid="721046627"},
	{id="1108311886",	name="CheckStopEvading",	pid="959847675"},
	{id="2242555820",	name="SetMovementState",	pid="721046627",	args={state=ATTACKING}}}
addAiTemplate("evadeDefault", evadeDefault)

idleDefault = {
	{id="3154429038",	name="SequenceSpace",	pid="none"},
	{id="2950938112",	name="NotSpace",	pid="3154429038"},
	{id="1976821924",	name="IfSpace",	pid="2950938112"},
	{id="2316913811",	name="CheckMovementState",	pid="1976821924",	args={condition=ATTACKING}},
	{id="3521391142",	name="NotSpace",	pid="3154429038"},
	{id="3390840483",	name="IfSpace",	pid="3521391142"},
	{id="2770349133",	name="CheckHasPatrol",	pid="3390840483"},
	{id="3954328391",	name="GeneratePatrol",	pid="3154429038",	args={distFromHome=256.0, numPoints=5}}}
addAiTemplate("idleDefault", idleDefault)

lookDefault = {
	{id="2349982047",	name="SequenceSpace",	pid="none"},
	{id="1015056356",	name="SelectorSpace",	pid="2349982047"},
	{id="2178900812",	name="IfSpace",	pid="1015056356"},
	{id="2737704374",	name="CheckMovementState",	pid="2178900812",	args={condition=OBLIVIOUS}},
	{id="3742455244",	name="IfSpace",	pid="1015056356"},
	{id="1948820794",	name="CheckMovementState",	pid="3742455244",	args={condition=PATROLLING}},
	{id="622023069",	name="SetMovementState",	pid="2349982047",	args={state=WATCHING}},
	{id="1344506751",	name="AlwaysSucceedSpace",	pid="2349982047"},
	{id="811185371",	name="SetAlert",	pid="1344506751",	args={duration=5.0, aggroDelay=5.0}}}
addAiTemplate("lookDefault", lookDefault)

moveDefault = {
	{id="438025397",	name="SelectorSpace",	pid="none"},
	{id="807381555",	name="SequenceSpace",	pid="438025397"},
	{id="3765071638",	name="IfSpace",	pid="807381555"},
	{id="1573749740",	name="CheckEnginesDisabled",	pid="3765071638"},
	{id="1831944128",	name="SetDisabledEngineSpeed",	pid="807381555"},
	{id="2561598181",	name="SequenceSpace",	pid="438025397"},
	{id="904574168",	name="IfSpace",	pid="2561598181"},
	{id="323979800",	name="CheckRetreat",	pid="904574168",	args={condition=1500}},
	{id="2078642140",	name="SetMovementState",	pid="2561598181",	args={state=LEASHING}},
	{id="2987325598",	name="Leash",	pid="2561598181"},
	{id="368441587",	name="SequenceSpace",	pid="438025397"},
	{id="3848206840",	name="IfSpace",	pid="368441587"},
	{id="539785228",	name="CheckDestination",	pid="3848206840"},
	{id="910186084",	name="AlwaysFailSpace",	pid="368441587"},
	{id="1331314218",	name="FindNextPosition",	pid="910186084"}}
addAiTemplate("moveDefault", moveDefault)

rootDefault = {
	{id="2051740559",	name="SelectorSpace",	pid="none"},
	{id="1729558672",	name="TreeSocketSpace",	pid="2051740559",	args={slot=MOVESPACE}},
	{id="1447247403",	name="TreeSocketSpace",	pid="2051740559",	args={slot=EVADESPACE}},
	{id="4225713865",	name="SequenceSpace",	pid="2051740559"},
	{id="2182549780",	name="SelectorSpace",	pid="4225713865"},
	{id="215111410",	name="IfSpace",	pid="2182549780"},
	{id="522517531",	name="CheckMovementState",	pid="215111410",	args={condition=ATTACKING}},
	{id="3422660300",	name="IfSpace",	pid="2182549780"},
	{id="1375524373",	name="CheckMovementState",	pid="3422660300",	args={condition=WATCHING}},
	{id="4010272258",	name="TreeSocketSpace",	pid="4225713865",	args={slot=TARGETSPACE}},
	{id="1764650020",	name="AlwaysSucceedSpace",	pid="4225713865"},
	{id="1406904607",	name="TreeSocketSpace",	pid="1764650020",	args={slot=ATTACKSPACE}},
	{id="2499929043",	name="TreeSocketSpace",	pid="2051740559",	args={slot=AWARESPACE}},
	{id="869798738",	name="TreeSocketSpace",	pid="2051740559",	args={slot=IDLESPACE}}}
addAiTemplate("rootDefault", rootDefault)

targetDefault = {
	{id="295814316",	name="SequenceSpace",	pid="none"},
	{id="1628727004",	name="AlwaysSucceedSpace",	pid="295814316"},
	{id="3051594756",	name="SelectorSpace",	pid="1628727004"},
	{id="4219427160",	name="GetProspectFromThreatMap",	pid="3051594756"},
	{id="1280314588",	name="SequenceSpace",	pid="3051594756"},
	{id="1485266457",	name="NotSpace",	pid="1280314588"},
	{id="3575964598",	name="IfSpace",	pid="1485266457"},
	{id="1056287644",	name="CheckMovementState",	pid="3575964598",	args={condition=FLEEING}},
	{id="260549053",	name="GetProspectFromDefenders",	pid="1280314588"},
	{id="3669711549",	name="SelectorSpace",	pid="295814316"},
	{id="2292606827",	name="SequenceSpace",	pid="3669711549"},
	{id="2668746033",	name="NotSpace",	pid="2292606827"},
	{id="1453715206",	name="IfSpace",	pid="2668746033"},
	{id="1228992601",	name="CheckTargetIsValid",	pid="1453715206"},
	{id="627960272",	name="SequenceSpace",	pid="2292606827"},
	{id="3767183712",	name="EraseBlackboard",	pid="627960272",	args={param="aggroMod"}},
	{id="4195634024",	name="EraseBlackboard",	pid="627960272",	args={param="targetShipProspect"}},
	{id="3661684207",	name="ExitCombat",	pid="627960272"},
	{id="2575489275",	name="SetMovementState",	pid="627960272",	args={state=PATROLLING}},
	{id="3784699471",	name="SequenceSpace",	pid="3669711549"},
	{id="3388907248",	name="IfSpace",	pid="3784699471"},
	{id="791512445",	name="CheckAggroDelayPast",	pid="3388907248"},
	{id="2331460897",	name="IfSpace",	pid="3784699471"},
	{id="2459130683",	name="CheckProspectAggression",	pid="2331460897"},
	{id="3308935710",	name="SetDefenderFromProspect",	pid="3784699471"},
	{id="3792515791",	name="SetMovementState",	pid="3784699471",	args={state=ATTACKING}}}
addAiTemplate("targetDefault", targetDefault)

