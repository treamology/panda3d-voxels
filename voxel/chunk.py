import numpy as np


class Chunk:
    def __init__(self, blocks: np.ndarray):
        self.blocks = blocks  # type: np.ndarray
