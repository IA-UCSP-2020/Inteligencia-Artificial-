from heapq import heapify, heappush, heappop
import node
import gc
gc.collect()

# this will be my graph
# cols*rows, represents the number of nodes
graph = {
    # coordinates of the start node
    "start": [0, 0],
    # coordinates of the goal node
    "goal": [99, 99],
    # 100*100 grid, so there is 10000 nodes
    "cols": 100,
    "rows": 100,
    # the grid, of size cols*rows
    "grid": []
}


# i construct the resulting path
def reconstruct_path(current):
    resulting_path = []
    resulting_path.append(current)
    while current.camefrom:
        current = current.camefrom
        path.append(current)
    return path


# openSet will be the list of nodes that can be evaluated
# it will be a min-heap for optimization purposes
# the possible paths
openSet = []
# closed Set will be the best path showed i real time during the proccess
closedSet = []
# the final path
path = []

# start and goal, will be the nodes that we will connect
start = None
goal = None

# p is the probability that the node will be created
# 35% of chance that the node will be created
p = 0.35

def heuristic(node, goal):
    # i calculate the euclidean distance
    # between the node and the goal
    return ((node.x - goal.x)**2 + (node.y - goal.y)**2)**0.5


def cleanMemory():
    # cleaning all my graph
    for i in range(0, graph["cols"]):
        del graph["grid"][i][:]
    del graph["grid"][:]


# setting up all the graph
for i in range(0, graph["cols"]):
    arr = []
    for j in range(0, graph["rows"]):
        if random(1) < p and (i != graph["start"][0] or j != graph["start"][1]) and (i != graph["goal"][0] or j != graph["goal"][1]):
            arr.append(None)
        else:
            arr.append(node.Node(i, j))
    graph["grid"].append(arr)


# connecting all the nodes on my graph-grid
for i in range(0, graph["cols"]):
    for j in range(0, graph["rows"]):
        if graph["grid"][i][j]:
            graph["grid"][i][j].set_up_nodes(graph)

# the upper left corner
start = graph["grid"][graph["start"][0]][graph["start"][1]]
# the bottom right corner
goal = graph["grid"][graph["goal"][0]][graph["goal"][1]]


# i convert to a min-heap my openSet
heapify(openSet)
# i convert to a min-heap my closedSet
heapify(closedSet)

# we start setting the distance from start to start
# which is obviously 0
start.g = 0
heappush(openSet, start)


def setup():
    size(600, 600)


def draw():
    if len(openSet) > 0:
        # current is the node that has the least distance from starting point
        # this operation takes O(1), because we use a min-heap
        current = openSet[0]
        
        # the current node is the goal, so we finish the search
        if current == goal:
            noLoop()
            print("FINISH!!!")

        heappop(openSet)
        heappush(closedSet, current)
        for neighbor in current.nodes:
            # d(current,neighbor) is the weight of the edge from current to neighbor
            # in our simple case d(current,neighbor) = 1
            # tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore = current.g + 1
            if neighbor:
                if tentative_gScore < neighbor.g:
                    # then this path is better, so we have to record it
                    neighbor.camefrom = current
                    neighbor.g = tentative_gScore
                    neighbor.f = neighbor.g + heuristic(neighbor, goal)
                    if not(neighbor in openSet):
                        heappush(openSet, neighbor)

    else:
        print("NO THERE IS A PATH")
        noLoop()
        return

    background(255)

    for i in range(0, len(graph["grid"])):
        for j in range(0, len(graph["grid"][i])):
            if graph["grid"][i][j]:
                graph["grid"][i][j].show(
                    graph, width, height, color(255, 255, 255))
            else:
                w = width / graph["cols"]  # the width of a node
                h = height / graph["rows"]  # the height of a node
                fill(0)
                rect(i * w, j * h, w, h)

    # we show the path openSet
    for i in range(0, len(openSet)):
        openSet[i].show(graph, width, height, color(0, 0, 255))

    # we show the path closedSet
    for i in range(0, len(closedSet)):
        closedSet[i].show(graph, width, height, color(0, 255, 0))

    path = reconstruct_path(current)
    for i in range(0, len(path)):
        path[i].show(graph, width, height, color(255, 0, 0))
