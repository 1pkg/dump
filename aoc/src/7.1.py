import itertools

def execute(line, idx):
	global inp, oup
	(tkn, modes) = parse_op(line[idx])
	if tkn == 99:
		return (idx, False, True)
	elif tkn == 1:
		tmp = access(line, idx + 1, modes[0]) + access(line, idx + 2, modes[1])
		access(line, idx + 3, modes[2], tmp)
		idx += 4
	elif tkn == 2:
		tmp = access(line, idx + 1, modes[0]) * access(line, idx + 2, modes[1])
		access(line, idx + 3, modes[2], tmp)
		idx += 4
	elif tkn == 3:
		if len(inp) == 0:
			return (idx, True, False)
		tmp = inp[0]
		inp = inp[:len(inp)-1]
		access(line, idx + 1, modes[0], tmp)
		idx += 2
	elif tkn == 4:
		oup = access(line, idx + 1, modes[0])
		idx += 2
	elif tkn == 5:
		tmp = access(line, idx + 1, modes[0])
		if tmp != 0:
			idx = access(line, idx + 2, modes[1])
		else:
			idx += 3
	elif tkn == 6:
		tmp = access(line, idx + 1, modes[0])
		if tmp == 0:
			idx = access(line, idx + 2, modes[1])
		else:
			idx += 3
	elif tkn == 7:
		tmp1 = access(line, idx + 1, modes[0])
		tmp2 = access(line, idx + 2, modes[1])
		if tmp1 < tmp2:
			access(line, idx + 3, modes[2], 1)
		else:
			access(line, idx + 3, modes[2], 0)
		idx += 4
	elif tkn == 8:
		tmp1 = access(line, idx + 1, modes[0])
		tmp2 = access(line, idx + 2, modes[1])
		if tmp1 == tmp2:
			access(line, idx + 3, modes[2], 1)
		else:
			access(line, idx + 3, modes[2], 0)
		idx += 4
	return (idx, False, False)

def parse_op(raw):
	raw = str(raw).rjust(5, '0')
	tkn = raw[-2:]
	modes = (raw[:-2])[::-1]
	return (
		int(tkn),
		[bool(int(s)) for s in modes],
	)

def access(line, idx, immediate = False, value = None):
	if value is not None:
		line[line[idx]] = value
	if immediate:
		return line[idx]
	else:
		return line[line[idx]]

def execute_all(line, tkn = 0):
	while True:
		(tkn, hang, halt) = execute(line, tkn)
		if hang or halt:
			return (tkn, halt)
	return (tkn, True)

line = [3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10]
inp, oup, results = [0], 0, []

for subset in itertools.permutations(range(5, 10), 5):
	inp, oup, alus = [0], 0, {}
	for phase in subset:
		alus[phase] = [line[:], 0]

	idx, halt_count = 0, 0
	while halt_count < 5:
		for phase in subset:
			if idx == 0:
				inp = [phase, oup]
			else:
				inp = [oup]

			print('before', subset, phase, oup)
			alu = alus[phase]
			result = execute_all(alu[0], alu[1])
			alu[1] = result[0]
			print('after',  subset, phase, oup)
			halt_count += int(result[1])
		idx += 1

	results.append(oup)
results.sort(reverse=True)
print(results)