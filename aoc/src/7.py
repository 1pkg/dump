import itertools

def execute(line, idx):
	global buf
	(tkn, modes) = parse_op(line[idx])
	if tkn == 99:
		return -1
	elif tkn == 1:
		tmp = access(line, idx + 1, modes[0]) + access(line, idx + 2, modes[1])
		access(line, idx + 3, modes[2], tmp)
		idx += 4
	elif tkn == 2:
		tmp = access(line, idx + 1, modes[0]) * access(line, idx + 2, modes[1])
		access(line, idx + 3, modes[2], tmp)
		idx += 4
	elif tkn == 3:
		tmp = buf[0]
		buf[0] = buf[1]
		buf[1] = None
		access(line, idx + 1, modes[0], tmp)
		idx += 2
	elif tkn == 4:
		tmp = access(line, idx + 1, modes[0])
		buf[0] = tmp
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
	return idx

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

def execute_all(line):
	tkn = 0
	while tkn != -1:
		tkn = execute(line, tkn)

buf = None
results = []
line = [3,8,1001,8,10,8,105,1,0,0,21,38,55,72,93,118,199,280,361,442,99999,3,9,1001,9,2,9,1002,9,5,9,101,4,9,9,4,9,99,3,9,1002,9,3,9,1001,9,5,9,1002,9,4,9,4,9,99,3,9,101,4,9,9,1002,9,3,9,1001,9,4,9,4,9,99,3,9,1002,9,4,9,1001,9,4,9,102,5,9,9,1001,9,4,9,4,9,99,3,9,101,3,9,9,1002,9,3,9,1001,9,3,9,102,5,9,9,101,4,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,99,3,9,101,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,99,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,99]
for subset in itertools.permutations(range(5), 5):
	buf = [0,0]
	for phase in subset:
		buf[1] = buf[0]
		buf[0] = phase
		execute_all(line[:])
	results.append(buf[0])
results.sort(reverse=True)
print(results[0])