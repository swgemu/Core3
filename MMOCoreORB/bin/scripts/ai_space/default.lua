aggroDefault = {
	{id="2719762403",	name="SetDefenderFromProspect",	pid="none"}}
addAiTemplate("aggroDefault", aggroDefault)

attackDefault = {
	{id="620638771",	name="SequenceSpace",	pid="none"},
	{id="4063013086",	name="AlwaysFailSpace",	pid="620638771"}}
addAiTemplate("attackDefault", attackDefault)

awareDefault = {
	{id="2528207054",	name="SelectorSpace",	pid="none"},
	{id="2152617010",	name="LookForTargetSpace",	pid="2528207054"},
	{id="83649144",	name="SequenceSpace",	pid="2152617010"},
	{id="745742367",	name="CalculateAggroMod",	pid="83649144"},
	{id="4225492471",	name="IfSpace",	pid="83649144"},
	{id="2515118288",	name="CheckProspectInRange",	pid="4225492471"},
	{id="3812255102",	name="AlwaysSucceedSpace",	pid="83649144"},
	{id="934410611",	name="TreeSocketSpace",	pid="3812255102",	args={slot=LOOKATSPACE}},
	{id="1564864881",	name="SequenceSpace",	pid="83649144"},
	{id="1385674649",	name="IfSpace",	pid="1564864881"},
	{id="1982712854",	name="CheckMovementState",	pid="1385674649",	args={condition=WATCHING}},
	{id="4198580351",	name="SelectorSpace",	pid="1564864881"},
	{id="1541649393",	name="IfSpace",	pid="4198580351"},
	{id="1784206860",	name="CheckAggroDelayPast",	pid="1541649393"},
	{id="2867430638",	name="TreeSocketSpace",	pid="4198580351",	args={slot=AGGROSPACE}},
	{id="464125663",	name="SetMovementState",	pid="4198580351",	args={state=FOLLOWING}},
	{id="3659533500",	name="AlwaysFailSpace",	pid="2528207054"},
	{id="3683815365",	name="SequenceSpace",	pid="3659533500"},
	{id="617640316",	name="EraseBlackboard",	pid="3683815365",	args={param="aggroMod"}},
	{id="1391402118",	name="EraseBlackboard",	pid="3683815365",	args={param="targetProspect"}}}
addAiTemplate("awareDefault", awareDefault)

idleDefault = {
	{id="3154429038",	name="SequenceSpace",	pid="none"},
	{id="3521391142",	name="NotSpace",	pid="3154429038"},
	{id="3390840483",	name="IfSpace",	pid="3521391142"},
	{id="2770349133",	name="CheckHasPatrol",	pid="3390840483"},
	{id="3954328391",	name="GeneratePatrol",	pid="3154429038",	args={distFromHome=500.0, numPoints=10}}}
addAiTemplate("idleDefault", idleDefault)

lookDefault = {
	{id="2349982047",	name="SequenceSpace",	pid="none"},
	{id="1015056356",	name="SelectorSpace",	pid="2349982047"},
	{id="2178900812",	name="IfSpace",	pid="1015056356"},
	{id="2737704374",	name="CheckMovementState",	pid="2178900812",	args={condition=OBLIVIOUS}},
	{id="3742455244",	name="IfSpace",	pid="1015056356"},
	{id="1948820794",	name="CheckMovementState",	pid="3742455244",	args={condition=PATROLLING}},
	{id="622023069",	name="SetMovementState",	pid="2349982047",	args={state=WATCHING}},
	{id="2290190299",	name="AlwaysSucceedSpace",	pid="2349982047"},
	{id="811185371",	name="SetAlert",	pid="2290190299",	args={duration=5.0}}}
addAiTemplate("lookDefault", lookDefault)

moveDefault = {
	{id="368441587",	name="SequenceSpace",	pid="none"},
	{id="3848206840",	name="IfSpace",	pid="368441587"},
	{id="539785228",	name="CheckDestination",	pid="3848206840"},
	{id="910186084",	name="AlwaysFailSpace",	pid="368441587"},
	{id="1331314218",	name="FindNextPosition",	pid="910186084"}}
addAiTemplate("moveDefault", moveDefault)

rootDefault = {
	{id="2051740559",	name="SelectorSpace",	pid="none"},
	{id="195953072",	name="ParallelSelectorSpace",	pid="2051740559"},
	{id="1752525902",	name="TreeSocketSpace",	pid="195953072",	args={slot=TARGETSPACE}},
	{id="1729558672",	name="TreeSocketSpace",	pid="195953072",	args={slot=MOVESPACE}},
	{id="2499929043",	name="TreeSocketSpace",	pid="2051740559",	args={slot=AWARESPACE}},
	{id="869798738",	name="TreeSocketSpace",	pid="2051740559",	args={slot=IDLESPACE}}}
addAiTemplate("rootDefault", rootDefault)

targetDefault = {
	{id="1083217022",	name="SelectorSpace",	pid="none"},
	{id="1455589660",	name="AlwaysFailSpace",	pid="1083217022"},
	{id="3716750796",	name="ExitCombat",	pid="1455589660",	args={clearDefenders=1}}}
addAiTemplate("targetDefault", targetDefault)

