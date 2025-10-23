idleAttackablespacestation = {
	{id="3514328923",	name="SequenceSpace",	pid="none"}}
addAiTemplate("idleAttackablespacestation", idleAttackablespacestation)

rootAttackablespacestation = {
	{id="3348004110",	name="SelectorSpace",	pid="none"},
	{id="372913136",	name="SequenceSpace",	pid="3348004110"},
	{id="567071168",	name="SelectorSpace",	pid="372913136"},
	{id="2982020736",	name="TreeSocketSpace",	pid="567071168",	args={slot=TARGETSPACE}},
	{id="2089452580",	name="TreeSocketSpace",	pid="567071168",	args={slot=AWARESPACE}},
	{id="3500631497",	name="IfSpace",	pid="567071168"},
	{id="3281121397",	name="CheckMovementState",	pid="3500631497",	args={condition=ATTACKING}},
	{id="3575304462",	name="TreeSocketSpace",	pid="372913136",	args={slot=ATTACKSPACE}},
	{id="2155200216",	name="TreeSocketSpace",	pid="3348004110",	args={slot=IDLESPACE}}}
addAiTemplate("rootAttackablespacestation", rootAttackablespacestation)

