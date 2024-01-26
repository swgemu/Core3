aggroDefault = {
	{id="945589948",	name="SequenceSpace",	pid="none"},
	{id="1631029490",	name="IfSpace",	pid="945589948"},
	{id="368523102",	name="CheckProspectAggression",	pid="1631029490"},
	{id="2014626606",	name="IfSpace",	pid="945589948"},
	{id="1176105024",	name="CheckProspectInRange",	pid="2014626606"},
	{id="1957806964",	name="IfSpace",	pid="945589948"},
	{id="851346818",	name="CheckProspectLOS",	pid="1957806964"},
	{id="3986427247",	name="SetDefenderFromProspect",	pid="945589948"}}
addAiTemplate("aggroDefault", aggroDefault)

attackDefault = {
	{id="848497664",	name="SequenceSpace",	pid="none"},
	{id="87769704",	name="IfSpace",	pid="848497664"},
	{id="2250329166",	name="CheckRefireRate",	pid="87769704",	args={condition=500}},
	{id="772823324",	name="EngageTarget",	pid="848497664"}}
addAiTemplate("attackDefault", attackDefault)

awareDefault = {
	{id="1214404540",	name="SequenceSpace",	pid="none"},
	{id="3841927422",	name="NotSpace",	pid="1214404540"},
	{id="957850819",	name="IfSpace",	pid="3841927422"},
	{id="3395630515",	name="CheckMovementState",	pid="957850819",	args={condition=EVADING}},
	{id="2152617010",	name="LookForTargetSpace",	pid="1214404540"},
	{id="83649144",	name="SequenceSpace",	pid="2152617010"},
	{id="765304253",	name="CalculateAggroMod",	pid="83649144"},
	{id="4225492471",	name="IfSpace",	pid="83649144"},
	{id="2515118288",	name="CheckProspectInRange",	pid="4225492471"},
	{id="3076853086",	name="AlwaysSucceedSpace",	pid="83649144"},
	{id="934410611",	name="TreeSocketSpace",	pid="3076853086",	args={slot=LOOKATSPACE}},
	{id="1270556892",	name="IfSpace",	pid="83649144"},
	{id="2923824875",	name="CheckMovementState",	pid="1270556892",	args={condition=WATCHING}},
	{id="2797098288",	name="IfSpace",	pid="83649144"},
	{id="576735143",	name="CheckAggroDelayPast",	pid="2797098288"},
	{id="1799039580",	name="TreeSocketSpace",	pid="83649144",	args={slot=AGGROSPACE}}}
addAiTemplate("awareDefault", awareDefault)

evadeDefault = {
	{id="2857060179",	name="SelectorSpace",	pid="none"},
	{id="2602567462",	name="SequenceSpace",	pid="2857060179"},
	{id="4002815204",	name="IfSpace",	pid="2602567462"},
	{id="2649809160",	name="CheckMovementState",	pid="4002815204",	args={condition=EVADING}},
	{id="937592621",	name="AlwaysSucceedSpace",	pid="2602567462"},
	{id="721046627",	name="SequenceSpace",	pid="937592621"},
	{id="959847675",	name="IfSpace",	pid="721046627"},
	{id="1108311886",	name="CheckStopEvading",	pid="959847675"},
	{id="2242555820",	name="SetMovementState",	pid="721046627",	args={state=ATTACKING}},
	{id="105533972",	name="SequenceSpace",	pid="2857060179"},
	{id="239981461",	name="IfSpace",	pid="105533972"},
	{id="2845710209",	name="CheckEvadeChance",	pid="239981461",	args={chance=10}},
	{id="2176893155",	name="SetMovementState",	pid="105533972",	args={state=EVADING}},
	{id="3574481783",	name="Evade",	pid="105533972",	args={evadeDelay=2000}}}
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
	{id="811185371",	name="SetAlert",	pid="1344506751",	args={aggroDelay=5.0}}}
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
	{id="2158110177",	name="SelectorSpace",	pid="4225713865"},
	{id="4010272258",	name="TreeSocketSpace",	pid="2158110177",	args={slot=TARGETSPACE}},
	{id="2499929043",	name="TreeSocketSpace",	pid="2158110177",	args={slot=AWARESPACE}},
	{id="215111410",	name="IfSpace",	pid="4225713865"},
	{id="522517531",	name="CheckMovementState",	pid="215111410",	args={condition=ATTACKING}},
	{id="1406904607",	name="TreeSocketSpace",	pid="4225713865",	args={slot=ATTACKSPACE}},
	{id="869798738",	name="TreeSocketSpace",	pid="2051740559",	args={slot=IDLESPACE}}}
addAiTemplate("rootDefault", rootDefault)

targetDefault = {
	{id="295814316",	name="SequenceSpace",	pid="none"},
	{id="3051594756",	name="SelectorSpace",	pid="295814316"},
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
	{id="3784699471",	name="SequenceSpace",	pid="3669711549"},
	{id="3308935710",	name="SetDefenderFromProspect",	pid="3784699471"},
	{id="3792515791",	name="SetMovementState",	pid="3784699471",	args={state=ATTACKING}}}
addAiTemplate("targetDefault", targetDefault)

