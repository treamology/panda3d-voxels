from voxel import worldgen


class World:
    def __init__(self):
        self.num_players = 1  # type: int
        self.chunks = []  # type: list

    def place_block(self, x: int, y: int):
        pass

    def place_block_in_chunk(self, chunk_: int, chunk_y: int, block_x: int, block_y: int):
        pass

    def remove_block(self, block_x: int, block_y: int):
        pass

    def remove_block_in_chunk(self, chunk_x: int, chunk_y: int, block_x: int, block_y: int):
        pass


def generate_new_world(size_in_chunks: int=30, seed: int=9999) -> World:
    world = World()
    world.chunks = [[worldgen.generate_chunk(x, y, seed) for x in range(size_in_chunks)] for y in range(size_in_chunks)]
    return world
