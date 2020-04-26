le = [1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,1,9,19,1,19,5,23,1,13,23,27,1,27,6,31,2,31,6,35,2,6,35,39,1,39,5,43,1,13,43,47,1,6,47,51,2,13,51,55,1,10,55,59,1,59,5,63,1,10,63,67,1,67,5,71,1,71,10,75,1,9,75,79,2,13,79,83,1,9,83,87,2,87,13,91,1,10,91,95,1,95,9,99,1,13,99,103,2,103,13,107,1,107,10,111,2,10,111,115,1,115,9,119,2,119,6,123,1,5,123,127,1,5,127,131,1,10,131,135,1,135,6,139,1,10,139,143,1,143,6,147,2,147,13,151,1,5,151,155,1,155,5,159,1,159,2,163,1,163,9,0,99,2,14,0,0]

def execute(l, n):
	pos = n * 4
	tkn = l[pos]
	if tkn == 99:
		return (l, True)
	elif tkn == 1:
		val = l[l[pos + 1]] + l[l[pos + 2]]
	elif tkn == 2:
		val = l[l[pos + 1]] * l[l[pos + 2]]
	l[l[pos + 3]] = val
	return (l, False)

def execute_all(l):
	for x in range(0, len(l)):
		(l, flag) = execute(l, x)
		if flag:
			return l[0]
	return 0

def brutforce_execute_all(l, ne):
	for i in range(0, 99):
		for j in range(0, 99):
			tl = l.copy()
			tl[1] = i
			tl[2] = j
			if execute_all(tl) == ne:
				return (i, j)
	return -1

print(brutforce_execute_all(le, 19690720))