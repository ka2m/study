import vk
import io
import math
import pygame
from urllib2 import urlopen
from graphfau.Algo import Algo as func
from graphfau.GraphGenerator import GraphGenerator as gg

###############################################################################
# This script draws first 50 friends of yours in a undirected, not weighted   #
# graph and builds friendship relationship between them with help of edges    #
# You can click on any friend of yours, select it and the select the other one#
# to find minimal "path" between you two.                                     #
###############################################################################

# Contsants
ACCESS_TOKEN = None
USER_ID = None
with open('token.file', 'r') as f:
    ACCESS_TOKEN = f.readline()[:-1]

with open('uid.file', 'r') as f:
    USER_ID = int(f.readline()[:-1])
USER_ID = 53679402
NUMBER_OF_FRIENDS = 50  # how many friends to evaluate
SIZE = (1440, 880)  # MB Air 13" minus title bar
SCREEN = pygame.display.set_mode(SIZE)  # main window
# Define some colors
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
RED = (255, 0, 0)

CENTER_POS = [SIZE[0] / 2, SIZE[1] / 2]
# Calucalate angle of n-polygon
if NUMBER_OF_FRIENDS < 20:
    radius = 300
else:
    radius = 20 + 6.5 * NUMBER_OF_FRIENDS
angle = 2 * math.pi / NUMBER_OF_FRIENDS

# Functions


def get_image_obj_by_url(url):
    image_str = urlopen(url).read()
    return io.BytesIO(image_str)


def print_text(message):
    SCREEN.fill(WHITE)
    font = pygame.font.SysFont("monospace", 36)
    text = font.render(message, 1, (0, 0, 0))
    SCREEN.blit(text, (0, 0))
    pygame.display.flip()


def draw_friends(g, friend_img_pos):
    for conn in g.get_edges():
        posOne = [x for x in friend_img_pos if x[2] == conn[0]][0]
        posTwo = [x for x in friend_img_pos if x[2] == conn[1]][0]
        pygame.draw.line(SCREEN,
                         RED,
                         [posOne[0], posOne[1]],
                         [posTwo[0], posTwo[1]],
                         1)


def draw_friend_userpics(friend_img_pos):
    for friend in friend_img_pos:
        SCREEN.blit(friend[3], [friend[0], friend[1]])

# Main file
app_mode = 0  # 0 - get info, 1 - get friends, 2 - get path
# Init PyGame window
pygame.init()
print_text('App initialized')
pygame.display.set_caption("VK Friends Graph")

# Auth in VK
print_text('Authenticating')
vkapi = vk.API(access_token=ACCESS_TOKEN)
me = vkapi.users.get(uid=int(USER_ID), fields="photo_50")[0]

print_text('Getting friends list of %s %s' % (me['first_name'],
                                              me['last_name']))

# Get friends of UID from VK
my_friends = vkapi.friends.get(user_id=int(USER_ID),
                               count=NUMBER_OF_FRIENDS,
                               fields="first_name,last_name,photo_50,domain",
                               order="hints")['items']

print_text('Friend list received. Creating base graph')


# Create graph
g = gg.create(params={'directed': False, 'weighted': False},
              adj_list=dict.fromkeys([x['id'] for x in my_friends], []))
vertices = list(g.vertices)

print_text('Finding and adding mutual friends')
mutual = vkapi.friends.getMutual(source_uid=USER_ID,
                                 target_uids=','.join([str(x) for x in vertices]))
for friend in mutual:
    fr_id = friend['id']
    for user in friend['common_friends']:
        if user in g.vertices:
            g.add_edge(fr_id, user)

friend_img_pos = []

print_text('Rendering')
SCREEN.fill(WHITE)

for i in range(NUMBER_OF_FRIENDS):
    img_url = [x['photo_50'] for x in my_friends if x['id'] == vertices[i]][0]
    img = pygame.image.load(get_image_obj_by_url(img_url))

    xc = int(700 + 2 * radius * math.sin(i*angle))
    yc = int(420 + 1.15 * radius * math.cos(i*angle) - 15)
    pygame.draw.line(SCREEN, BLACK, [xc + 25, yc + 25], CENTER_POS, 1)

    friend_img_pos.append([xc, yc, vertices[i], img, False])


me_img = pygame.image.load(get_image_obj_by_url(me['photo_50']))
SCREEN.blit(me_img, [CENTER_POS[0] - 25, CENTER_POS[1] - 25])

draw_friends(g, friend_img_pos)
draw_friend_userpics(friend_img_pos)
done = False
clock = pygame.time.Clock()

bfs_vertices = []
while not done:
    for event in pygame.event.get():
        if event.type == pygame.KEYDOWN:
            pygame.draw.rect(SCREEN, WHITE, [0, 0, 350, 50])
            pygame.display.flip()
            draw_friends(g, friend_img_pos)
            draw_friend_userpics(friend_img_pos)
            for friend in friend_img_pos:
                friend[4] = False
            if event.key == pygame.K_i:
                app_mode = 0
            if event.key == pygame.K_f:
                app_mode = 1
            if event.key == pygame.K_p:
                app_mode = 2
        if event.type == pygame.MOUSEBUTTONUP:
            pos = pygame.mouse.get_pos()
            x = pos[0]
            y = pos[1]
            for friend in friend_img_pos:
                xf = friend[0]
                clr = BLUE if not friend[4] else RED
                yf = friend[1]
                if x >= xf and x <= xf + 50 and y >= yf and y <= yf + 50:
                    # mode 1 - find friends for each of my friends
                    if app_mode == 1:
                        for f in my_friends:
                            if f['id'] == friend[2]:
                                for ff in g.get_connected_vertices(friend[2]):
                                    for fip in friend_img_pos:
                                        if fip[2] == ff:
                                            pygame.draw.line(SCREEN,
                                                             clr,
                                                             [fip[0], fip[1]],
                                                             [friend[0], friend[1]],
                                                             1)
                                friend[4] = not friend[4]
                    if app_mode == 0:
                        fr = [e for e in my_friends if e['id'] == friend[2]][0]
                        font = pygame.font.SysFont("monospace", 12)
                        pygame.draw.rect(SCREEN, WHITE, [0, 0, 350, 50])
                        pygame.display.flip()
                        text = font.render('%s %s (vk.com/%s)' % (fr['first_name'],
                                           fr['last_name'],
                                           fr['domain']), 1, (0, 0, 0))
                        SCREEN.blit(text, (0, 0))
                    if app_mode == 2:
                        bfs_vertices.append(friend[2])
                        if len(bfs_vertices) == 2:
                            gfrom = bfs_vertices[0]
                            gto = bfs_vertices[1]
                            path = func.short_bfs(g, gfrom, gto)
                            bfs_vertices = []
                            edges = []
                            for i in range(len(path)-1):
                                edges.append((path[i], path[i+1]))
                            for pair in edges:
                                k = 0
                                posOne = [e for e in friend_img_pos if e[2] == pair[0]][0]
                                posTwo = [e for e in friend_img_pos if e[2] == pair[1]][0]
                                pygame.draw.line(SCREEN,
                                                 GREEN,
                                                 [posOne[0], posOne[1]],
                                                 [posTwo[0], posTwo[1]],
                                                 1)

        if event.type == pygame.QUIT:
            done = True

        pygame.display.flip()

    clock.tick(60)

pygame.quit()
