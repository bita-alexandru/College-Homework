import copy
import math
import random

di = [0,-1,0,1]
dj = [-1,0,1,0]

solved_bkt = False
solved_bfs = False
solved_hc = False
solved_sa = False

steps = 0

def read_input(fn):
	with open(fn) as fd:
		lines = []
		for string in fd.read().split('\n'):
			line = []
			for char in string:
				line.append(char)
			lines.append(line)
		return lines

def init_state():
	maze = read_input("labirint.txt")
	pos_start = None
	pos_finish = None
	visited = []

	for i in range(len(maze)):
		for j in range(len(maze[i])):
			if maze[i][j] == "S":
				pos_start = [i,j]
			elif maze[i][j] == "F":
				pos_finish = [i,j]
	visited.append(pos_start)
	
	state = { "maze": maze, "pos_curr": pos_start, "pos_finish": pos_finish }
	return state

def check_valid(state, pos_next):
	maze = state["maze"]
	if pos_next == [4,1]:
		print("AICI")
	if pos_next[0] < 0 or pos_next[0] >= len(maze):
		if pos_next == [4,1]:
			print(-1)
		return False
	if pos_next[1] < 0 or pos_next[1] >= len(maze[0]):
		if pos_next == [4,1]:
			print(-2)
		return False
	if maze[pos_next[0]][pos_next[1]] not in " F":
		if pos_next == [4,1]:
			print(-3)
		return False
	
	pos_curr = state["pos_curr"]
	if abs(pos_curr[0]+pos_curr[1] - pos_next[0]-pos_next[1]) > 1:
		if pos_next == [4,1]:
			print(pos_curr)
		return False
		
	return True

def check_finish(state):
	pos_curr = state["pos_curr"]
	pos_finish = state["pos_finish"]

	if pos_curr == pos_finish:
		return True
	
	return False

def make_transition(state, pos_next):
	if check_valid(state, pos_next):
		state_new = copy.copy(state)
		state_new["pos_curr"] = pos_next
		state_new["maze"][pos_next[0]][pos_next[1]] = "o" if pos_next != state["pos_finish"] else "F"
		return state_new
	
	return False

def clear_file(fn):
	global steps
	steps = 0

	open(fn,"w").close()

def draw_steps(maze, fn):
	global steps

	with open(fn,"a") as fd:
		steps += 1
		print("Step " + str(steps), file = fd)
		
		for i in range(len(maze)):
			for j in range(len(maze[0])):
				print(maze[i][j], file = fd, end = "")
			print(file = fd)
		print(file = fd)
		
def solve_bkt(state):
	global di, dj
	global solved_bkt

	draw_steps(state["maze"], "pasi_bkt.txt")

	if check_finish(state):
		solved_bkt = True
		return

	pos_curr = state["pos_curr"]

	for i in range(0,4):
		pos_next = [pos_curr[0]+di[i], pos_curr[1]+dj[i]]

		state_new = make_transition(state, pos_next)
		if state_new != False:
			solve_bkt(state_new)

		if solved_bkt:
			return
	
	state["maze"][pos_curr[0]][pos_curr[1]] = "."

def solve_bfs(state):
	global di, dj
	global solved_bfs
	
	distance = [[0] * len(state["maze"][0]) for i in range(len(state["maze"]))]
	
	queue = [state["pos_curr"]]
	while not solved_bfs and len(queue) > 0:
		pos_curr = queue.pop(0)

		for i in range(0,4):
			pos_next = [pos_curr[0]+di[i], pos_curr[1]+dj[i]]
			
			state["pos_curr"] = pos_next
			state_new = make_transition(state, pos_next)

			if state_new != False:
				distance[pos_next[0]][pos_next[1]] = distance[pos_curr[0]][pos_curr[1]] + 1

				if pos_next == state["pos_finish"]:
					solved_bfs = True
					break
				
				state["maze"] = state_new["maze"]

				queue.append(pos_next)
		
		if not solved_bfs:
			draw_steps(state["maze"], "pasi_bfs.txt")

	pos_curr = state["pos_finish"]
	maze = state["maze"]
	
	while distance[pos_curr[0]][pos_curr[1]] > 1:
		for i in range(0,4):
			pos_next = [pos_curr[0]+di[i], pos_curr[1]+dj[i]]
		
			if distance[pos_next[0]][pos_next[1]] == distance[pos_curr[0]][pos_curr[1]]-1:
				pos_curr = pos_next
				maze[pos_curr[0]][pos_curr[1]] = "."

	for i in range(len(maze)):
		for j in range(len(maze[0])):
			if maze[i][j] == ".":
				maze[i][j] = "o"
				continue
			if maze[i][j] == "o":
				maze[i][j] = "."
			
	draw_steps(state["maze"], "pasi_bfs.txt")

def solve_hc(state):
	global di, dj
	global solved_hc

	draw_steps(state["maze"], "pasi_hc.txt")

	if check_finish(state):
		solved_hc = True
		return

	evaluate = lambda x: round(math.sqrt((state["pos_finish"][0]-x[0])**2 + (state["pos_finish"][1]-x[1])**2), 3)
	pos_curr = state["pos_curr"]

	for i in range(0,4):
		pos_next = [pos_curr[0]+di[i], pos_curr[1]+dj[i]]

		state_new = make_transition(state, pos_next)
		
		if state_new == False:
			continue
		
		if evaluate(pos_next) <= evaluate(pos_curr):
			solve_hc(state_new)

		if solved_hc:
			return

	state["maze"][pos_curr[0]][pos_curr[1]] = "."

def solve_sa(state):
	global di, dj
	global solved_sa
	global steps
	
	evaluate = lambda x: round(math.sqrt((state["pos_finish"][0]-x[0])**2 + (state["pos_finish"][1]-x[1])**2), 3)
	stack = [copy.copy(state)]

	T = 100
	while state["pos_curr"] != state["pos_finish"] and len(stack) > 0:
		state = stack.pop(-1)
		pos_curr = state["pos_curr"]
		eval_curr = evaluate(pos_curr)

		while True:
			draw_steps(state["maze"], "pasi_sa.txt")
			
			if pos_curr == state["pos_finish"]:
				solved_sa = True
				return

			neighbours = []
			for i in range(0,4):
				pos_next = [pos_curr[0]+di[i], pos_curr[1]+dj[i]]
				if state["maze"][pos_next[0]][pos_next[1]] in " F":
					neighbours.append(pos_next)
			random.shuffle(neighbours)
			
			found = False
			while len(neighbours) > 0:
				pos_next = neighbours.pop(0)
				eval_next = evaluate(pos_next)

				if eval_next <= eval_curr:
					found = True
					pos_curr = pos_next
					state["pos_curr"] = pos_curr
					state["maze"][pos_next[0]][pos_next[1]] = "o"
					stack.append(copy.copy(state))
					break
				else:
					p = math.e**(-abs(eval_next-eval_curr)/T)
					if p >= random.random():
						found = True
						pos_curr = pos_next
						state["pos_curr"] = pos_curr
						state["maze"][pos_next[0]][pos_next[1]] = "o"
						stack.append(copy.copy(state))
						break
				
			if not found:
				break
				

		T *= 0.9

read_input("labirint.txt")

# clear_file("pasi_bkt.txt")
# solve_bkt(init_state())
# print("#solved_bkt: " + str(solved_bkt))

# clear_file("pasi_bfs.txt")
# solve_bfs(init_state())
# print("#solved_bfs: " + str(solved_bfs))

# clear_file("pasi_hc.txt")
# solve_hc(init_state())
# print("#solved_hc: " + str(solved_hc))

clear_file("pasi_sa.txt")
solve_sa(init_state())
print("#solved_sa: " + str(solved_sa))