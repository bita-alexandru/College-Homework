"""
Replicate the game Trap the Mouse.

Generate a 11x11 board filled with hexagons and place the mouse
in the center.
The player interacts with the board by placing obstacles
on any available hexagon.
The mouse moves each time the player places an obstacle.

The player wins when the mouse has no available hexagons
in the immediate neighbourhood.
The mouse wins when it manages to leave the board.
"""

import pygame
import sys
import copy
import random
from os import environ, system, name
environ['PYGAME_HIDE_SUPPORT_PROMPT'] = '1'

# Constants for representing the window's size
WIDTH = 1028
HEIGHT = 768

# Constants for representing the game matrix's size
ROWS = 11
COLS = 11

# Constants for representing the state of a cell in the game matrix
AVAILABLE = 0
OBSTACLE = 1
MOUSE = 2

# Constants for representing whose turn is to move
# P1 = Player1, P2 = Player2 (the mouse)
P1 = 0
P2 = 1

# Constants for representing the maximum score and the
# penalty for each move
SCORE = 20000
PENALTY = 50

# Constants for representing the minimum and maximum number of
# initially spawned obstacles
OBSTACLES_MAX = 10
OBSTACLES_MIN = 5

# Constant for representing the size of a cell
SIZE = 32

# Constants for representing colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
COLOR_BACKGROUND = (211, 211, 211)  # Light gray
COLOR_AVAILABLE = WHITE
COLOR_OBSTACLE = (0, 0, 0)  # Black
COLOR_MOUSE = (119, 136, 153)  # Gray

# Constants for representing the offsets and paddings
OFFSET = 4
PADDING_X = WIDTH/2 - COLS*(2*SIZE + OFFSET)/2 + OFFSET/2
PADDING_Y = HEIGHT/2 - ROWS*(1.5*SIZE + OFFSET)/2 - 1.5*OFFSET


# Constants for representing which state is currently active
PVP = 0
PVC_EASY = 1
PVC_MEDIUM = 2
PVC_HARD = 3

# Constants for the minimax algorithm
DEPTH = 2*1
INF = 99999


def initialize_board() -> dict:
    """Return a dictionary representing the initial state of the game.
    A state is a dictionary composed by:
    - "board": a matrix denoting whether a hexagone is available,
    occupied by the mouse or occupied by a trap
    - "mouse": a 2-tuple of points denoting the mouse coordinates
    on the matrix (row, column)
    - "turn": an int with the value P1 if the trapper is to move or
    P2 if the mouse is to move
    - "score": an int representing the total of points the winner
    will get
    - "winner": a variable representing whether the game is still
    going on ("PLAYING") or ended in a draw ("DRAW") or a victory
    (P1 if the trapper won or P2 if the mouse won)
    """
    # Initialize a ROWS X COLS matrix
    board = [[AVAILABLE for j in range(COLS)] for i in range(ROWS)]
    mouse = (ROWS//2, COLS//2)
    board[mouse[0]][mouse[1]] = MOUSE

    # Place a random number of traps at random positions
    positions = [(i, j) for i in range(ROWS) for j in range(COLS)]
    positions.remove(mouse)
    random.shuffle(positions)

    obstacles = random.randint(OBSTACLES_MIN, OBSTACLES_MAX)

    for i in range(obstacles):
        row = positions[i][0]
        col = positions[i][1]

        board[row][col] = OBSTACLE

    return {
        "board": board,
        "mouse": mouse,
        "turn": P1,
        "score": SCORE,
        "winner": "PLAYING"
    }


def compute_hexagon(x_left: float, y_peak: float) -> list:
    """Return a list of 6 points denoting a hexagon.

    Keyword arguments:
    x_left -- the leftmost point of the hexagon to be drawn
    y_peak -- the upmost point of the hexagon to be drawn
    """
    x_mid = x_left + SIZE
    x_right = x_mid + SIZE

    y_top = y_peak + SIZE/2
    y_bot = y_top + SIZE
    y_base = y_bot + SIZE/2

    return [
        x_left, x_mid, x_right,
        y_peak, y_top, y_bot, y_base
    ]


def draw_hexagon(screen: pygame.Surface, color: tuple, points: list,
                 update_display: bool = True) -> None:
    """Draw a hexagon on the screen.

    Keyword arguments:
    screen -- the reference to the screen that will print the hexagon
    color -- the color of the hexagon to be drawn
    points -- a list of six points representing the hexagon's relative coordinates
    update_display -- whether the display shall be updated in this function or not (default true)
    """
    x_left, x_mid, x_right = points[:3]
    y_peak, y_top, y_bot, y_base = points[3:]

    hexagon = [
        (x_left, y_top), (x_mid, y_peak), (x_right, y_top),
        (x_right, y_bot), (x_mid, y_base), (x_left, y_bot)
    ]

    pygame.draw.polygon(screen, color, hexagon)

    if not update_display:
        return

    rect = pygame.rect.Rect(x_left, y_peak, 2*SIZE, 2*SIZE)
    pygame.display.update(rect)


def draw_board(screen: pygame.Surface, state: dict) -> list:
    """Display the game matrix on the screen.

    Keyword arguments:
    screen -- the reference to the screen that will print the game board
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    """
    screen.fill(COLOR_BACKGROUND)

    board = state["board"]
    cells = []

    offset_y = PADDING_Y
    for i in range(ROWS):
        if i % 2 == 0:
            offset_x = PADDING_X
        else:
            offset_x = PADDING_X + SIZE + OFFSET/2

        for j in range(COLS):
            points = compute_hexagon(j*SIZE + offset_x, i*SIZE + offset_y)

            if board[i][j] == AVAILABLE:
                color = COLOR_AVAILABLE
            elif board[i][j] == MOUSE:
                color = COLOR_MOUSE
            elif board[i][j] == OBSTACLE:
                color = COLOR_OBSTACLE

            # Memorize the coordinates used to create the hexagon
            # and the position in the matrix
            cell = {
                "points": points,
                "position": (i, j)
            }
            cells.append(cell)

            draw_hexagon(screen, color, cell["points"], update_display=False)

            offset_x += (SIZE + OFFSET)
        offset_y += (SIZE/2 + OFFSET)

    pygame.display.update()

    return cells


def draw_ui(screen: pygame.Surface, state: dict) -> None:
    """Draw the score and indicate whose turn it is.

    Keyword arguments:
    screen -- the reference to the screen that will print the game UI
    elements (trapper's icon, mouse's icon, medal, score text and endgame text)
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    """
    # Draw the trapper icon in the lower left of the window
    cell_p1 = compute_hexagon(
        PADDING_X/2 - SIZE,
        HEIGHT - 2.5*SIZE
    )
    if state["turn"] == P1:
        draw_hexagon(screen, COLOR_OBSTACLE, cell_p1)
    elif state["winner"] == "PLAYING":
        draw_hexagon(screen, WHITE, cell_p1)

    # Draw the mouse icon in the lower right of the window
    cell_p2 = compute_hexagon(
        WIDTH - SIZE - PADDING_X/2,
        HEIGHT - 2.5*SIZE
    )
    if state["turn"] == P2:
        draw_hexagon(screen, COLOR_MOUSE, cell_p2)
    elif state["winner"] == "PLAYING":
        draw_hexagon(screen, WHITE, cell_p2)

    try:
        font = pygame.font.Font("roboto-regular.ttf", 48)
    except FileNotFoundError:
        font = pygame.font.SysFont("calibri", 48)

    # Draw the score on the upper center of the window
    score = str(state["score"] + PENALTY)
    score_text = font.render(score, True, WHITE)
    score_rect = score_text.get_rect()

    score = str(state["score"])
    score_text = font.render(score, True, WHITE)
    rect = pygame.rect.Rect(
        WIDTH/2 - score_rect.w/2, PADDING_Y/2 - score_rect.h/2,
        score_rect.w, score_rect.h
    )
    pygame.draw.rect(screen, COLOR_BACKGROUND, rect)

    score_rect = score_text.get_rect()
    screen.blit(
        score_text,
        (WIDTH/2 - score_rect.w/2, PADDING_Y/2 - score_rect.h/2)
    )
    pygame.display.update(score_rect)

    if state["winner"] == "PLAYING":
        return

    try:
        font = pygame.font.Font("roboto-bold.ttf", 28)
    except FileNotFoundError:
        font = pygame.font.SysFont("arial", 28)

    # Draw the end game message on the lower center of the window
    message = {
        "DRAW": ("It's a draw!- Press R for a rematch...", WHITE),
        P1: (
            "The Trapper- won with " + score + " points! Press R for a rematch...",
            COLOR_OBSTACLE
        ),
        P2: (
            "The Mouse- won with " + score + " points! Press R for a rematch...",
            COLOR_MOUSE
        ),
    }
    message_winner = message[state["winner"]][0].split("-")[0]
    message_rematch = message[state["winner"]][0].split("-")[1]

    message_winner_text = font.render(
        message_winner, True, message[state["winner"]][1])
    message_rematch_text = font.render(message_rematch, True, WHITE)

    message_winner_rect = message_winner_text.get_rect()
    message_rematch_rect = message_rematch_text.get_rect()
    message_rect = pygame.rect.Rect(
        0, 0,
        message_winner_rect.w + message_rematch_rect.w,
        max(message_winner_rect.h, message_rematch_rect.h)
    )

    screen.blit(
        message_winner_text,
        (WIDTH/2 - message_rect.w/2, HEIGHT - PADDING_Y/2 - message_rect.h/2)
    )
    screen.blit(
        message_rematch_text,
        (WIDTH/2 - message_rect.w/2 + message_winner_rect.w,
         HEIGHT - PADDING_Y/2 - message_rect.h/2)
    )
    pygame.display.update(message_rect)

    if state["winner"] == "DRAW":
        return

    try:
        winner = pygame.image.load("medal.png")
    except FileNotFoundError:
        return

    # Draw a medal on top of the winner's icon
    winner_rect = winner.get_rect()

    if state["winner"] == P1:
        winner_rect.x = cell_p1[0]
        winner_rect.y = cell_p1[3]
    elif state["winner"] == P2:
        winner_rect.x = cell_p2[0]
        winner_rect.y = cell_p2[3]

    screen.blit(winner, winner_rect)
    pygame.display.update(winner_rect)


def count_obstacles(board: tuple, position: tuple) -> int:
    """Count the obstacles around a certain cell.

    Keyword arguments:
    board -- a matrix denoting  whether a hexagone is available,
    occupied by the mouse or occupied by a trap
    position -- a 2-tuple of points denoting a certain position in
    the matrix (row, column)
    """
    count = 0

    if position[0] % 2 == 0:
        d_i = [-1, -1, 0, 1, 1, 0]
        d_j = [-1, 0, 1, 0, -1, -1]
    else:
        d_i = [-1, -1, 0, 1, 1, 0]
        d_j = [0, 1, 1, 1, 0, -1]

    for i in range(6):
        neighbour = (position[0] + d_i[i], position[1] + d_j[i])
        row = neighbour[0]
        col = neighbour[1]

        if (row >= 0 and row < ROWS) and (col >= 0 and col < COLS) \
                and board[row][col] == OBSTACLE:
            count += 1

    return count


def generate_all_moves(state: dict, for_mouse: bool = True) -> list:
    """Return a list of all the valid moves one can make.

    Keyword arguments:
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    for_mouse -- whether or not the function shall return a list of
    all the moves the mouse can take (true) or all the moves the trapper
    can take (false) (default true)
    """
    board = state["board"]
    mouse = state["mouse"]
    moves = []

    # Return all the moves the trapper can make
    if not for_mouse:
        for row in range(ROWS):
            for col in range(COLS):
                if board[row][col] == AVAILABLE:
                    moves.append((row, col))
        return moves

    # Return all the moves the mouse can make
    if mouse[0] % 2 == 0:
        d_i = [-1, -1, 0, 1, 1, 0]
        d_j = [-1, 0, 1, 0, -1, -1]
    else:
        d_i = [-1, -1, 0, 1, 1, 0]
        d_j = [0, 1, 1, 1, 0, -1]

    for i in range(6):
        neighbour = (mouse[0] + d_i[i], mouse[1] + d_j[i])
        row = neighbour[0]
        col = neighbour[1]

        if (row >= 0 and row < ROWS) and (col >= 0 and col < COLS) \
                and board[row][col] == AVAILABLE:
            moves.append(neighbour)

    return moves


def check_move(state: dict, position: tuple) -> bool:
    """Check whether a move is valid or not.

    Keyword arguments:
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    position -- a 2-tuple of points denoting a certain position in
    the matrix (row, column)
    """
    board = state["board"]
    turn = state["turn"]

    row = position[0]
    col = position[1]

    if row is None or col is None:
        return False

    # Out of the board's bounds
    if row < 0 or row >= ROWS:
        return False
    if col < 0 or col >= COLS:
        return False

    if board[row][col] != AVAILABLE:
        return False

    # Check the validity of the mouse's move
    if turn == P2:
        if position in generate_all_moves(state):
            return True
        return False

    return True


def check_finish(screen: pygame.Surface, state: dict) -> None:
    """Check whether the game has a winner yet or not.

    Keyword arguments:
    screen -- the reference to the screen to be passed to the
    'draw_ui(screen, state)' function
    elements (trapper's icon, mouse's icon, medal, score text and endgame text)
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    """
    mouse = state["mouse"]

    if state["winner"] != "PLAYING":
        return

    # Check if the mouse reached the bounds
    if mouse[0] in [0, ROWS-1] or mouse[1] in [0, COLS-1]:
        state["winner"] = P2
        draw_ui(screen, state)
        return

    # Check if the mouse has no valid moves available
    if len(generate_all_moves(state)) == 0:
        state["winner"] = P1
        draw_ui(screen, state)
        return

    state["score"] -= PENALTY

    # Check for a draw
    if state["score"] == 0:
        state["winner"] = "DRAW"
        draw_ui(screen, state)
        return

    draw_ui(screen, state)


def compute_shortest_path(board: tuple, mouse: tuple) -> int:
    """Return the minimum distance to the bounds of the board.

    Keyword arguments:
    board -- a matrix denoting whether a hexagone is available,
    occupied by the mouse or occupied by a trap
    mouse -- a 2-tuple of points denoting the mouse coordinates
    on the matrix (row, column)
    """
    dist = [[0 for col in range(COLS)] for row in range(ROWS)]
    dist_min = INF

    state = {
        "board": board,
        "mouse": mouse
    }

    # Run a Lee like algorithm but with weights
    # Weights are calculated based on how many traps surround a cell
    queue = [mouse]
    while len(queue) > 0:
        act = queue.pop(0)

        if act[0] in [0, ROWS-1] or act[1] in [0, COLS-1]:
            dist_min = min(dist_min, dist[act[0]][act[1]])
            continue

        state["mouse"] = act

        moves = generate_all_moves(state)
        for move in moves:
            state["board"][move[0]][move[1]] = MOUSE
            dist[move[0]][move[1]] = dist[act[0]][act[1]] + \
                1 + count_obstacles(board, move)

            queue.append(move)

    return dist_min


def compute_minimax(board: tuple, position: tuple, depth: int, alpha: int, beta: int) -> tuple:
    """Return the best move the mouse can take using minimax alpha-beta pruning.

    Keyword arguments:
    board -- a matrix denoting whether a hexagone is available,
    occupied by the mouse or occupied by a trap
    position -- a 2-tuple of points denoting a certain position in
    the matrix (row, column)
    depth -- the number of the human player's future moves to consider
    alpha -- a number representing the value of the best case scenario
    beta -- a number representing the value of the worst case scenario
    """
    state = {
        "board": board,
        "mouse": position
    }

    moves_mouse = generate_all_moves(state)
    moves_trapper = generate_all_moves(state, False)

    if len(moves_mouse) == 0:  # Mouse loses in this state
        return INF, None
    if position[0] in [0, ROWS-1] or position[1] in [0, COLS-1] == P2:  # Mouse wins in this state
        return -INF, None

    if depth == DEPTH + 1:  # Maximum depth reached, return how good/bad this state is
        fit = compute_shortest_path(board, position)
        return fit, None

    turn = depth % 2

    # Minimize the fittness
    if turn == P2:
        fit_max = INF
        pos_new = None

        # Consider every possible move and pass the resulted configuration on the next call
        for move in moves_mouse:
            board[position[0]][position[1]] = AVAILABLE
            board[move[0]][move[1]] = MOUSE

            fit_curr = compute_minimax(copy.deepcopy(
                board), copy.deepcopy(move), depth+1, alpha, beta)[0]
            fit_max = min(fit_max, fit_curr)
            if fit_max == fit_curr:
                pos_new = move

            board[move[0]][move[1]] = AVAILABLE
            board[position[0]][position[1]] = MOUSE

            alpha = max(alpha, fit_curr)
            if beta <= alpha:
                break

        return fit_max, pos_new
    # Maximize the fitness
    else:
        fit_min = -INF
        pos_new = None

        # consider every possible move and pass the resulted configuration on the next call
        for move in moves_trapper:
            board[move[0]][move[1]] = OBSTACLE

            fit_curr = compute_minimax(copy.deepcopy(
                board), copy.deepcopy(position), depth+1, alpha, beta)[0]
            fit_min = max(fit_min, fit_curr)
            if fit_min == fit_curr:
                pos_new = move

            board[move[0]][move[1]] = AVAILABLE

            beta = min(beta, fit_curr)
            if beta <= alpha:
                break

        return fit_min, pos_new


def generate_ai_move(screen: pygame.Surface, state: dict, level: int, cells: list) -> None:
    """Generate AI's move.

    Keyword arguments:
    screen -- the reference to the screen to be passed to the
    'draw_hexagon(screen, color, points)' function
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    level -- an integer representing the game mode selected by the user
    (0 = pvp, 1 = computer easy, 2 = computer medium, 3 = computer hard)
    cells -- a list containing the absolute coordinates of the hexagons
    on the screen together with their corresponding row and column on the
    matrix
    """
    if state["winner"] != "PLAYING":
        return

    pos_act = state["mouse"]
    board = state["board"]
    moves = generate_all_moves(state)
    pos_next = moves[0]

    if level == PVC_EASY:
        # Make a random move
        index = random.randint(0, len(moves) - 1)
        pos_next = moves[index]
    elif level == PVC_MEDIUM:
        # Make either a random move (50% chance) or a calculated move (50% chance)
        prob = random.random()

        if prob <= 0.5:
            index = random.randint(0, len(moves) - 1)
            pos_next = moves[index]
        else:
            pos_next = compute_minimax(
                copy.deepcopy(board), copy.deepcopy(pos_act),
                1, -INF, INF
            )[1]
    elif level == PVC_HARD:
        # Make a calculated move (best one assuming trapper's next move)
        pos_next = compute_minimax(
            copy.deepcopy(board), copy.deepcopy(pos_act),
            1, -INF, INF
        )[1]

    # Make the move
    points = cells[pos_act[0]*ROWS + pos_act[1]]["points"]
    draw_hexagon(screen, COLOR_AVAILABLE, points)
    state["board"][pos_act[0]][pos_act[1]] = AVAILABLE

    state["mouse"] = pos_next
    state["board"][pos_next[0]][pos_next[1]] = MOUSE

    points = cells[pos_next[0]*ROWS + pos_next[1]]["points"]
    draw_hexagon(screen, COLOR_MOUSE, points)

    state["turn"] = P1
    check_finish(screen, state)


def click_cell(screen: pygame.Surface, state: dict, level: int,
               cursor: tuple, cells: list, hover: dict) -> None:
    """
    Interact with a certain cell(hexagone) from the board.
    Depending on whose turn it is, either place a trap or move the mouse.

    Keyword arguments:
    screen -- the reference to the screen that will mark the desired move
    (if it's valid)
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    level -- an integer representing the game mode selected by the user
    (0 = pvp, 1 = computer easy, 2 = computer medium, 3 = computer hard)
    cursor -- a 2-tuple of points denoting the captured position of the mouse
    relative to the game window
    cells -- a list containing the absolute coordinates of the hexagons
    on the screen together with their corresponding row and column on the
    matrix
    hover -- a dictionary representing the last hexagone being hovered
    """
    if state["winner"] != "PLAYING":
        return

    if hover is not None:  # Remove highlight
        points = hover["points"]
        position = hover["position"]
        x_left = points[0]
        y_peak = points[3]

        rect = pygame.rect.Rect(x_left, y_peak, 2*SIZE, 2*SIZE)
        if state["board"][position[0]][position[1]] == AVAILABLE:
            draw_hexagon(screen, COLOR_AVAILABLE, points)

    mouse = state["mouse"]

    for cell in cells:
        points = cell["points"]
        position = cell["position"]

        x_left = points[0]
        y_peak = points[3]

        rect = pygame.rect.Rect(x_left, y_peak, 2*SIZE, 2*SIZE)

        # Check if current cell has been clicked
        # and if it is represents a valid move
        if rect.collidepoint(cursor) and check_move(state, position):
            # Place an obstacle
            if state["turn"] == P1:
                draw_hexagon(screen, COLOR_OBSTACLE, points)
                state["board"][position[0]][position[1]] = OBSTACLE

                state["turn"] = P2
                check_finish(screen, state)

                if level == PVP:
                    return

                generate_ai_move(screen, state, level, cells)
            # Move the mouse from the previous cell to this one
            else:
                draw_hexagon(screen, COLOR_MOUSE, points)
                state["board"][mouse[0]][mouse[1]] = AVAILABLE

                state["mouse"] = position
                state["board"][position[0]][position[1]] = MOUSE

                points = cells[mouse[0]*ROWS + mouse[1]]["points"]
                draw_hexagon(screen, COLOR_AVAILABLE, points)

                state["turn"] = P1
                check_finish(screen, state)

            return


def hover_cell(screen: pygame.Surface, state: dict,
               cursor: tuple, cells: list, hover: dict) -> dict:
    """Color a cell to indicate that it is available.

    Keyword arguments:
    screen -- the reference to the screen that will highlight the current
    hexagone being hovered (if it represents a potential valid move)
    state -- a dictionary containing the current state of the game
    (see 'initialize_board()')
    cursor -- a 2-tuple of points denoting the captured position of the mouse
    relative to the game window
    cells -- a list containing the absolute coordinates of the hexagons
    on the screen together with their corresponding row and column on the
    matrix
    hover -- a dictionary representing the last hexagone being hovered
    """
    if state["winner"] != "PLAYING":
        return None

    if hover is not None:  # Remove highlight
        points = hover["points"]
        position = hover["position"]
        x_left = points[0]
        y_peak = points[3]

        rect = pygame.rect.Rect(x_left, y_peak, 2*SIZE, 2*SIZE)
        if rect.collidepoint(cursor):  # It is still being hovered
            return hover
        elif state["board"][position[0]][position[1]] == AVAILABLE:
            draw_hexagon(screen, COLOR_AVAILABLE, points)
            return None

    for cell in cells:
        points = cell["points"]
        position = cell["position"]

        x_left = points[0]
        y_peak = points[3]

        rect = pygame.rect.Rect(x_left, y_peak, 2*SIZE, 2*SIZE)

        # Check if current cell has been hovered
        # and if it is represents a valid move
        if rect.collidepoint(cursor) and check_move(state, position):
            if state["turn"] == P1:
                draw_hexagon(screen, COLOR_OBSTACLE, points)
                return cell
            else:
                draw_hexagon(screen, COLOR_MOUSE, points)
                return cell

    return None


def parse_input(play_again: bool = False) -> int:
    """Return the user's desired game mode.

    Keyword arguments:
    play_again -- whether the user shall play the game once more
    or not (default false)
    """
    levels = {
        "0": PVP,
        "1": PVC_EASY,
        "2": PVC_MEDIUM,
        "3": PVC_HARD
    }

    mode = "n/a"

    if not play_again and len(sys.argv) == 2:
        mode = sys.argv[1]

    if mode not in levels:
        if play_again:
            _ = system("cls") if name == "nt" else system("clear")
            print(
                "Wanna try another game mode?\n"
                + "Type a number (or \"exit\" to quit): "
            )
        else:
            _ = system("cls") if name == "nt" else system("clear")
            print(
                "Choose your game mode!\n"
                + "Type a number (or \"exit\" to quit): "
            )

        while True:
            print("  0 - to play locally against someone else")
            print("  1 - to play against the computer at an easy level")
            print("  2 - to play against the computer at a medium level")
            print("  3 - to play against the computer at a high level")
            print()
            print("I'm choosing: ", end="")
            mode = str(input()).lower()

            if mode in ["exit", "quit"]:
                sys.exit()

            if mode in levels:
                return levels[mode]
            else:
                _ = system("cls") if name == "nt" else system("clear")
                print(
                    "Wrong input. Make sure you only type the word before the - sign."
                )

    return levels[mode]


def main(level: int) -> bool:
    """Handle the game execution.

    Keyword arguments:
    level -- an integer representing the game mode selected by the user
    (0 = pvp, 1 = computer easy, 2 = computer medium, 3 = computer hard)
    """
    pygame.init()
    pygame.display.set_caption("Trap the Mouse")
    screen = pygame.display.set_mode((WIDTH, HEIGHT))

    state = initialize_board()
    hover = None

    cells = draw_board(screen, state)
    draw_ui(screen, state)

    while True:
        event = pygame.event.wait()
        if event.type == pygame.QUIT:
            pygame.quit()
            return True
        if event.type == pygame.KEYDOWN:
            if state["winner"] != "PLAYING" and event.key == pygame.K_r:  # Restart the game
                screen.fill(COLOR_BACKGROUND)

                state = initialize_board()

                cells = draw_board(screen, state)
                draw_ui(screen, state)

                hover = None
        elif event.type == pygame.MOUSEMOTION:  # Highlight the cells being hovered
            hover = hover_cell(screen, state, pygame.mouse.get_pos(),
                               cells, hover)
        elif event.type == pygame.MOUSEBUTTONUP:  # Place a trap or move the mouse
            click_cell(screen, state, level,
                       pygame.mouse.get_pos(), cells, hover)


if __name__ == "__main__":
    new_game = False

    while True:
        game_mode = parse_input(new_game)  # Interact with the UI
        new_game = main(game_mode)  # Run the selected game mode
