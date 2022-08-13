awareEscort = {
	{id="1174153914",	name="Selector",	pid="none"},
	{id="510816692",	name="LookForTarget",	pid="1174153914"},
	{id="4080409789",	name="Sequence",	pid="510816692"},
	{id="1104730125",	name="Not",	pid="4080409789"},
	{id="530248364",	name="If",	pid="1104730125"},
	{id="2987915460",	name="CheckIsEscort",	pid="530248364"},
	{id="1525061186",	name="CalculateAggroMod",	pid="4080409789"},
	{id="2951514284",	name="If",	pid="4080409789"},
	{id="1491247834",	name="CheckProspectInRange",	pid="2951514284",	args={condition=0.0}},
	{id="3524174291",	name="If",	pid="4080409789"},
	{id="912485548",	name="CheckIsCamouflaged",	pid="3524174291"},
	{id="1484839356",	name="AlwaysSucceed",	pid="4080409789"},
	{id="462277531",	name="TreeSocket",	pid="1484839356",	args={slot=LOOKAT}},
	{id="1309909222",	name="Sequence",	pid="4080409789"},
	{id="29650036",	name="Selector",	pid="1309909222"},
	{id="811268585",	name="If",	pid="29650036"},
	{id="4022376893",	name="CheckMovementState",	pid="811268585",	args={condition=OBLIVIOUS}},
	{id="1679770289",	name="If",	pid="29650036"},
	{id="2862541032",	name="CheckMovementState",	pid="1679770289",	args={condition=OBLIVIOUS}},
	{id="3188946710",	name="Selector",	pid="1309909222"},
	{id="1405127172",	name="Sequence",	pid="3188946710"},
	{id="3897217871",	name="If",	pid="1405127172"},
	{id="763357740",	name="CheckAggroDelayPast",	pid="3897217871"},
	{id="994038108",	name="TreeSocket",	pid="1405127172",	args={slot=AGGRO}},
	{id="1976648974",	name="TreeSocket",	pid="3188946710",	args={slot=SCARE}},
	{id="3192574190",	name="AlwaysFail",	pid="1174153914"},
	{id="3075903024",	name="Sequence",	pid="3192574190"},
	{id="375543417",	name="EraseBlackboard",	pid="3075903024",	args={param="aggroMod"}},
	{id="1685361113",	name="EraseBlackboard",	pid="3075903024",	args={param="targetProspect"}}}
addAiTemplate("awareEscort", awareEscort)

moveEscort = {
	{id="824192424",	name="Selector",	pid="none"},
	{id="4020137705",	name="AlwaysFail",	pid="824192424"},
	{id="2904768555",	name="If",	pid="4020137705"},
	{id="396744437",	name="CheckDestination",	pid="2904768555",	args={condition=0.0}},
	{id="2851757642",	name="Sequence",	pid="824192424"},
	{id="2074092638",	name="If",	pid="2851757642"},
	{id="2988186562",	name="CheckPosture",	pid="2074092638",	args={condition=UPRIGHT}},
	{id="2120314997",	name="WriteBlackboard",	pid="2851757642",	args={key="moveMode", val=RUN}},
	{id="3085578776",	name="FindNextPosition",	pid="2851757642"}}
addAiTemplate("moveEscort", moveEscort)

runEscort = {
	{id="2928311771",	name="Selector",	pid="none"},
	{id="3097333621",	name="Sequence",	pid="2928311771"},
	{id="911353460",	name="If",	pid="3097333621"},
	{id="1225716325",	name="CheckIsEscort",	pid="911353460"},
	{id="2773567267",	name="SetMovementState",	pid="3097333621",	args={state=FOLLOWING}},
	{id="3216658477",	name="WriteBlackboard",	pid="3097333621",	args={key="moveMode", val=RUN}},
	{id="3054819924",	name="TreeSocket",	pid="3097333621",	args={slot=MOVE}},
	{id="599779045",	name="Wait",	pid="2928311771",	args={duration=-1.0}}}
addAiTemplate("runEscort", runEscort)

walkEscort = {
	{id="437268100",	name="Selector",	pid="none"},
	{id="1489268495",	name="Sequence",	pid="437268100"},
	{id="4183990835",	name="WriteBlackboard",	pid="1489268495",	args={key="moveMode", val=WALK}},
	{id="3093889889",	name="TreeSocket",	pid="1489268495",	args={slot=MOVE}},
	{id="70283378",	name="Wait",	pid="437268100",	args={duration=-1.0}}}
addAiTemplate("walkEscort", walkEscort)

