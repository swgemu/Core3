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

