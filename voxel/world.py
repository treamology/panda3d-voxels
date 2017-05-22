from panda3d.core import NodePath

from voxel import Chunk, ChunkGenManager


class World(NodePath):
    def __init__(self, size=32):
        NodePath.__init__(self, "World")
        self.size = size

        self.chunks = [[Chunk() for _ in range(size)] for _ in range(size)]
        cgm = ChunkGenManager()
        for x in range(size):
            for y in range(size):
                pass
                # cgm.generate_blocks(0, 0, 0)
                # self.chunks[x][y].attach_new_node(cgm.generate_mesh(self.chunks[x][y].block_array))
                # self.chunks[x][y].reparent_to(self)
                #self.chunks[x][y].generate_geometry()
                # self.chunks[x][y].set_pos(x * 16, y * 16, 0)
                #self.chunks[x][y].setRenderModeWireframe()
