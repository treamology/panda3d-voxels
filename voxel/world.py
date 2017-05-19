class World:
    def __init__(self, seed=9999):
        self.seed = seed # world isn't being randomly generated yet so this is unused
        self.num_players = 1
        self.chunks = []

    def place_block(self, x, y):
        pass

    def place_block_in_chunk(self, chunk_x, chunk_y, block_x, block_y):
        pass

    def remove_block(self, blockx, blocky):
        pass

    def remove_block_in_chunk(self, chunk_x, chunk_y, block_x, block_y):
        pass
