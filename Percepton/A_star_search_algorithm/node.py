# coding=utf-8


class Node(object):
    pass
    # we start by setting up the coordinates of my node

    def __init__(self, x, y):
        self.x = x
        self.y = y
        # default values of the function nodes will be infinity 
        # represented by this big numbers
        # the value of f(node) function, g(x) + h(x)
        self.f = 1000000
        # the value of g(node) function, distance from start to the node
        self.g = 1000000
        # the value of h(node) function, the heuristic
        self.h = 1000000
        # at the beginning a node isn´t in a path
        self.camefrom = None
        # a list of nodes (neighbors): right->0,left->1,down->2,up->3,
        # up_left->4, up_right->5, down_left->6, down_right->7
        self.nodes = [None, None, None, None, None, None, None, None]

    # this method charges the edges between the node and its neighbors
    # we pass the graph to link my node, with his neighbors by coordinates
    def set_up_nodes(self, graph):
        x = self.x
        y = self.y
        # for limit at right border
        if x < graph["cols"] - 1:
            self.nodes[0] = graph["grid"][x + 1][y]
        # for limit at left border
        if x > 0:
            self.nodes[1] = graph["grid"][x - 1][y]
        # for limit at bottom border
        if y < graph["rows"] - 1:
            self.nodes[2] = graph["grid"][x][y + 1]
        # for limit at upper border
        if y > 0:
            self.nodes[3] = graph["grid"][x][y - 1]
        # for limit at upper-left border
        if x > 0 and y > 0:
            self.nodes[4] = graph["grid"][x - 1][y - 1]
        # for limit at upper-right border
        if x < graph["cols"] - 1 and y > 0:
            self.nodes[5] = graph["grid"][x + 1][y - 1]
        # for limit at bottom-left border
        if x > 0 and y < graph["rows"] - 1:
            self.nodes[6] = graph["grid"][x - 1][y + 1]
        # for limit at bottom-down border
        if x < graph["cols"] - 1 and y < graph["rows"] - 1:
            self.nodes[7] = graph["grid"][x + 1][y + 1]

    def __str__(self):
        pass
        return "x: " + str(self.x) + " -- y: " + str(self.y)

    # this method prints the position of a node in a grid
    def show(self, graph, w, h, col):
        pass
        # w is the width of the window
        # h is the heigth of the window
        fill(col)
        w = w / graph["cols"]  # the width of a node
        h = h / graph["rows"]  # the height of a node
        rect(self.x * w, self.y * h, w, h)
    # this is important because i am using a min heap, that will evaluate
    # the value of f(n) of my nodes
    def __lt__(self, node):
        if(self.f < node.f):
            return True
        else:
            return False
