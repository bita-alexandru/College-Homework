import random

M = []
h = []
c = []

SIZE = 4
HUMAN = 0
COMPUTER = 1
DEPTH = 2*2
INF = 99999

def init_state():
    # initialize pieces' locations
    h = [(SIZE-1, column) for column in range(SIZE)]
    c = [(0, column) for column in range(SIZE)]

    # fill the matrix accordingly
    M = []
    for line in range(SIZE):
        row = []
        for column in range(SIZE):
            # computer's pieces: A,B,C,D
            if (line, column) in h:
                row.append("ABCD"[column])
            # human's pieces: 1,2,3,4
            elif (line, column) in c:
                row.append("1234"[column])
            # available spot
            else:
                row.append("·")
        M.append(row)

    return M, h, c

def check_valid(M, p, pos_curr, pos_new):
    line_curr, column_curr = pos_curr[0], pos_curr[1]
    line_new, column_new = pos_new[0], pos_new[1]

    # out of bounds
    if line_new < 0 or line_new >= SIZE:
        return False
    if column_new < 0 or column_new >= SIZE:
        return False

    # position is unavailable
    if M[line_new][column_new] != "·":
        return False

    # position out of range
    if abs(line_new-line_curr) > 1:
        return False
    if abs(column_new-column_curr) > 1:
        return False
    
    # no piece on current position
    if pos_curr not in p:
        return False
    
    return True

def check_finish(h, c):
    # check if human player won, return 0 if so
    won_h = True
    for line in h:
        if line[0] != 0:
            won_h = False
            break
    
    if won_h:
        return HUMAN
    
    # check if computer player won, return 1 if so
    won_c = True
    for line in c:
        if line[0] != SIZE-1:
            won_c = False
            break

    if won_c:
        return COMPUTER

    # no player won yet
    return -1

def make_transition(M, p, pos_curr, pos_new):
    line_curr, column_curr = pos_curr[0], pos_curr[1]
    line_new, column_new = pos_new[0], pos_new[1]

    # update state
    if check_valid(M, p, pos_curr, pos_new):
        M[line_new][column_new] = M[line_curr][column_curr]
        M[line_curr][column_curr] = "·"

        if turn == HUMAN:
            h[h.index(pos_curr)] = pos_new
        else:
            c[c.index(pos_curr)] = pos_new
        
        return M, h, c
    
    return False

def generate_moves(M, p):
    di = [0,-1,-1,-1,0,1,1,1]
    dj = [-1,-1,0,1,1,1,0,-1]

    moves = dict()

    # check available positions in neighbourhood 
    for pos in p:
        possible_moves = []

        for i in range(8):
            pos_new = (pos[0]+di[i], pos[1]+dj[i])

            if check_valid(M, p, pos, pos_new):
                possible_moves.append(pos_new)
        
        moves[pos] = possible_moves

    return moves

def draw_thinking(h, c):
    # fill the matrix accordingly
    M = []
    for line in range(SIZE):
        row = []
        for column in range(SIZE):
            row.append("·")
        M.append(row)
    
    for i in range(4):
        M[h[i][0]][h[i][1]] = "ABCD"[i] 
        M[c[i][0]][c[i][1]] = "1234"[i] 
    
    print("### BEGIN THINKING ###")
    for i in range(4):
        for j in range(4):
            print(M[i][j],end="")
        print()
    print("### END THINKING ###")

def pick_move(M, h, c, depth, alpha, beta):
    sum_h, sum_c = 0, 0
    for i in range(SIZE):
        sum_h += h[i][0]
        sum_c += c[i][0]
    
    if check_finish(h, c) == HUMAN:
        return -INF, None, None
    if check_finish(h, c) == COMPUTER:
        return INF, None, None

    if depth == DEPTH+1:
        rnd = random.uniform(0.95, 1.0)
        eval = rnd * (sum_h + sum_c - SIZE*(SIZE-1))
        return eval, None, None
    
    # print("DPTH="+str(depth))
    turn = depth % 2
    
    # maximizing player
    if turn == COMPUTER:
        eval_max = -INF
        pos_curr, pos_new = None, None

        moves = generate_moves(M, c).copy()
        # consider every possible move and pass the resulted configuration on the next call
        for move in moves:
            label = c.index(move)
            for move_next in moves[move]:
                c[label] = move_next
                M[move_next[0]][move_next[1]] = "1234"[label]
                M[move[0]][move[1]] = "·"

                eval_curr = pick_move(M.copy(), h.copy(), c.copy(), depth+1, alpha, beta)[0]
                eval_max = max(eval_max, eval_curr)
                if eval_max == eval_curr:
                    pos_curr = move
                    pos_new = move_next
                
                M[move_next[0]][move_next[1]] = "·"
                M[move[0]][move[1]] = "1234"[label]

                alpha = max(alpha, eval_curr)
                if beta <= alpha:
                    break
            c[label] = move
        return eval_max, pos_curr, pos_new
    # minimizing player
    else:
        eval_min = INF
        pos_curr, pos_new = None, None

        moves = generate_moves(M, h).copy()
        # consider every possible move and pass the resulted configuration on the next call
        for move in moves:
            label = h.index(move)
            for move_next in moves[move]:
                h[label] = move_next
                M[move_next[0]][move_next[1]] = "ABCD"[label]
                M[move[0]][move[1]] = "·"
                
                eval_curr = pick_move(M.copy(), h.copy(), c.copy(), depth+1, alpha, beta)[0]
                eval_min = min(eval_min, eval_curr)
                if eval_min == eval_curr:
                    pos_curr = move
                    pos_new = move_next

                M[move_next[0]][move_next[1]] = "·"
                M[move[0]][move[1]] = "ABCD"[label]

                beta = min(beta, eval_curr)
                if beta <= alpha:
                    break
            h[label] = move
        return eval_min, None, None

def is_blocked(M, p):
    di = [0,-1,-1,-1,0,1,1,1]
    dj = [-1,-1,0,1,1,1,0,-1]

    blocked = True
    for pos in p:
        line_curr, column_curr = pos[0], pos[1]
        for i in range(8):
            if not (0 <= line_curr+di[i] < SIZE and 0 <= column_curr+dj[i] < SIZE):
                continue
            
            if M[line_curr+di[i]][column_curr+dj[i]] == "·":
                blocked = False
                break
        
        if not blocked:
            break
    
    return blocked

def draw_game(M):
    # draw the matrix
    for line in range(SIZE):
        # draw guidance (line indexes on the left)
        print(line, end=" ")

        for column in range(SIZE):
            print(M[line][column], end="")
        print()

    # draw guidance (column indexes above)
    print(end="  ")
    for i in range(SIZE):
        print("-", end="")
    print()
    
    print(end="  ")
    for i in range(SIZE):
        print(i, end="")
    print()

def parse_input(h):
    pos_curr = None
    pos_new = None

    valid_input = False
    while not valid_input:
        print("<piece_label> <line> <column>: ", end="")
        valid_input = False

        move = str(input()).replace(" ", "")
        if len(move) != 3:
            continue
        
        label, line, column = move[0].upper(), move[1], move[2]

        if label not in "ABCD":
            continue

        if not line.isdigit():
            continue

        if not column.isdigit():
            continue

        pos_curr = h["ABCD".index(label)]
        pos_new = (int(line), int(column))
        
        valid_input = True
    
    return pos_curr, pos_new

M, h, c = init_state()
turn = HUMAN

# game is running
is_running = check_finish(h, c)
while is_running == -1:
    # human's turn
    if turn == HUMAN:
        draw_game(M)

        print("COMP pieces: 1, 2, 3, 4")
        print("YOUR pieces: A, B, C, D")

        if is_blocked(M, h):
            print("No moves available, computer will take your turn! (press Enter)")
            input()
        else:
            pos_curr, pos_new = parse_input(h)
            
            transition = make_transition(M, h, pos_curr, pos_new)
            while not transition:
                draw_game(M)
                print("invalid move")

                pos_curr, pos_new = parse_input(h)
                transition = make_transition(M, h, pos_curr, pos_new)
            M, h, c = transition
    # computer's turn
    else:
        if is_blocked(M, c):
            print("No moves available, human will take your turn! (press Enter)")
            input()
        else:
            eval, pos_curr, pos_new = pick_move(M.copy(), h.copy(), c.copy(), depth=1, alpha=-INF, beta=INF)
            print(eval)

            M, h, c = make_transition(M, c, pos_curr, pos_new)

    turn = (turn+1) % 2
    is_running = check_finish(h, c)
draw_game(M)

if is_running == HUMAN:
    print("Human WON!")
    
    print("type gg to show respect: ", end="")
    gg = str(input())
    if gg.upper() != "GG":
        print("Computer: :<")
    else:
        print("Computer: gg")
else:
    print("Computer WON!")

    print("type gg to show respect: ", end="")
    gg = str(input())
    if gg.upper() != "GG":
        print("Computer: :<")