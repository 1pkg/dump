def is_visible(mp, first, second):
	if first[0] == second[0]:
		y = first[0]
		low, up = (first[1], second[1]) if first[1] < second[1] else (second[1], first[1])
		for x in range(low + 1, up):
			if mp[y][x] == '#':
				return False
		return True

	y, yto = first[0], second[0]
	diff = (second[1] - first[1], abs(first[0] - second[0]))
	xstep = diff[0] / diff[1]
	ystep = +1 if first[0] < second[0] else -1

	x = first[1]
	while y != yto:
		y += ystep
		x += xstep
		if first == (19,18):
			print(first, second, y, x)
		if y == yto:
			break
		if abs(float(round(x)) - float(x)) > 0.01:
			continue
		if mp[y][int(round(x,5))] == '#':
			return False
	return True

def parse_mp(raw):
	mp = []
	raw = raw.strip('\n')
	rmp = raw.split('\n')
	for line in rmp:
		mp.append([char for char in line])
	return mp


def traverse(mp, func):
	for i in range(0, len(mp)):
		for j in range(0, len(mp[i])):
				if mp[i][j] == '#':
					func((i,j))

def count_single_point(mp, results, first):
	results[first] = 0
	def count(second):
		if first == second:
			return
		visible = int(is_visible(mp, first, second))
		results[first] += visible
		if first == (19,18):
			print(first, second, bool(visible), results[first])
	traverse(mp, count)

inpt = '''
#....#.....#...#.#.....#.#..#....#
#..#..##...#......#.....#..###.#.#
#......#.#.#.....##....#.#.....#..
..#.#...#.......#.##..#...........
.##..#...##......##.#.#...........
.....#.#..##...#..##.....#...#.##.
....#.##.##.#....###.#........####
..#....#..####........##.........#
..#...#......#.#..#..#.#.##......#
.............#.#....##.......#...#
.#.#..##.#.#.#.#.......#.....#....
.....##.###..#.....#.#..###.....##
.....#...#.#.#......#.#....##.....
##.#.....#...#....#...#..#....#.#.
..#.............###.#.##....#.#...
..##.#.........#.##.####.........#
##.#...###....#..#...###..##..#..#
.........#.#.....#........#.......
#.......#..#.#.#..##.....#.#.....#
..#....#....#.#.##......#..#.###..
......##.##.##...#...##.#...###...
.#.....#...#........#....#.###....
.#.#.#..#............#..........#.
..##.....#....#....##..#.#.......#
..##.....#.#......................
.#..#...#....#.#.....#.........#..
........#.............#.#.........
#...#.#......#.##....#...#.#.#...#
.#.....#.#.....#.....#.#.##......#
..##....#.....#.....#....#.##..#..
#..###.#.#....#......#...#........
..#......#..#....##...#.#.#...#..#
.#.##.#.#.....#..#..#........##...
....#...##.##.##......#..#..##....
'''
mp = parse_mp(inpt)
counts = {}
traverse(mp, lambda point: count_single_point(mp, counts, point))
print({k: v for k, v in sorted(counts.items(), key=lambda item: item[1])})
