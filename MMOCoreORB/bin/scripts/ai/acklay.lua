moveAcklay = {
	{id="2146344445",	name="Sequence",	pid="none"},
	{id="3789520168",	name="Sequence",	pid="2146344445"},
	{id="2027156567",	name="CheckPosture",	pid="3789520168",	args={condition=UPRIGHT}},
	{id="343960498",	name="CheckDestination",	pid="3789520168",	args={condition=0.0}},
	{id="561214299",	name="Selector",	pid="2146344445"},
	{id="2932876314",	name="Sequence",	pid="561214299"},
	{id="253025363",	name="If",	pid="2932876314"},
	{id="3043826936",	name="CheckRetreat",	pid="253025363",	args={condition=40}},
	{id="1319649080",	name="Leash",	pid="2932876314"},
	{id="3014359456",	name="FindNextPosition",	pid="561214299"}}
addAiTemplate("moveAcklay", moveAcklay)