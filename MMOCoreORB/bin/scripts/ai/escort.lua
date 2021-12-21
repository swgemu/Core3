moveEscort = {
	{id="824192424",	name="Selector",	pid="none"},
	{id="1974555353",	name="Not",	pid="824192424"},
	{id="887883781",	name="Sequence",	pid="1974555353"},
	{id="2074092638",	name="If",	pid="887883781"},
	{id="2988186562",	name="CheckPosture",	pid="2074092638",	args={condition=UPRIGHT}},
	{id="2904768555",	name="If",	pid="887883781"},
	{id="396744437",	name="CheckDestination",	pid="2904768555",	args={condition=0.0}},
	{id="2851757642",	name="Sequence",	pid="824192424"},
	{id="2120314997",	name="WriteBlackboard",	pid="2851757642",	args={key="moveMode", val=RUN}},
	{id="3085578776",	name="FindNextPosition",	pid="2851757642"}}
addAiTemplate("moveEscort", moveEscort)

runEscort = {
	{id="2928311771",	name="Selector",	pid="none"},
	{id="3097333621",	name="Sequence",	pid="2928311771"},
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

