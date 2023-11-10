import sys, pygame
from pygame import draw

# pygame control variables and setup
pygame.init()
#pygame.font.init()
pygame.display.set_caption("Ulam Spiral")

screen_fps = 60
screen_size = WIDTH, HEIGHT = 600, 600
clock = pygame.time.Clock()
screen = pygame.display.set_mode(screen_size)

# colors
black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)

# spiral control variables
step = 1
dir = 0
stepsPerDir = 1
sc = 0 # SC = Steps Controller

# loop control variables
maxSteps = 0 # 3599
iterationsPerFrame = 2 # how many steps of the spiral it does per frame
run = True

# visual variables
dotSize = 3
lineWidth = 1
dpd = 10 #distance per dot
targetPos = [WIDTH // 2 + (dpd / 2), HEIGHT // 2 + (dpd / 2)] # starting pos is screen center + half step size
lastPos = [targetPos[0] - dpd, targetPos[1]]

# responsiveness
dimension = (HEIGHT / dpd) * (HEIGHT / dpd)
maxSteps = dimension - 1

# returns if a number is prime or not
def isPrime(num):
    for x in range(2, int(num / 2) + 1):
        if float(num) % x == 0: return False

    return True

# returns the adjusted pos for the dots
def adjustPos(pos):
    x = pos[0] - (dotSize / 2)
    y = pos[1] - (dotSize / 2)

    adjusted = (x, y)

    return adjusted

# draws the dot
def drawDot():
    # variables
    global targetPos
    global step
    global stepsPerDir
    global sc
    global dir
    global lastPos

    # draw
    if isPrime(step + 1):
        lePos = adjustPos(targetPos)
        draw.circle(screen, white, lePos, dotSize)
    
    # start/end of line
    uwu = adjustPos(lastPos)
    owo = adjustPos(targetPos)

    # draws line
    draw.line(screen, white, uwu, owo, lineWidth)

    # updates screen
    pygame.display.update()

    # control direction
    # modulo to see remainder
    if step % stepsPerDir == 0:
        # next position
        dir = (dir + 1) % 4
        # increase turn counter
        sc += 1
        # if already turned 2 times
        if sc == 2:
            # increases steps per direction and reset turn counter
            stepsPerDir += 1
            sc = 0

    step += 1
        
    # update last pos
    lastPos = (targetPos[0], targetPos[1])

    # prepare next pos
    if dir == 0:
        targetPos[0] += dpd
    elif dir == 1:
        targetPos[1] -= dpd
    elif dir == 2:
        targetPos[0] -= dpd
    elif dir == 3:
        targetPos[1] += dpd

    if step == maxSteps:
        print("Finished!")
    pass

# program running loop
while run:
    # pygame func to control framerate
    clock.tick(screen_fps)

    # program closing control
    for event in pygame.event.get():
        if event.type == pygame.QUIT: run = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE: run = False

    # loop for more iterations per frame
    for x in range(iterationsPerFrame):
        if step <= maxSteps:
            drawDot()

    pass

sys.exit()