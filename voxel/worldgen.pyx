import numpy as np
cimport numpy as np

from voxel.chunk import Chunk
from voxel.block import Block

ctypedef np.uint8_t uint8_t

cdef enum:
    CHUNK_SIZE = 16
    CHUNK_HEIGHT = 256

def generate_chunk(int chunk_x, int chunk_y, int seed):
    cdef np.ndarray[uint8_t, ndim=3] block_array = np.zeros((CHUNK_SIZE, CHUNK_SIZE, CHUNK_HEIGHT), np.uint8)

    for x in range(CHUNK_SIZE):
        for y in range(CHUNK_SIZE):
            block_array[x][y][0] = 1

    chunk = Chunk(block_array)
    return chunk

# def generate_chunk(int chunk_x, int chunk_y, int seed):
#     cdef np.ndarray[object, ndim=3] block_array = np.empty((CHUNK_SIZE, CHUNK_SIZE, CHUNK_HEIGHT), np.object_)
#
#     for x in range(CHUNK_SIZE):
#         for y in range(CHUNK_SIZE):
#             for z in range(CHUNK_SIZE):
#                 block_array[x][y][z] = Block()
#
#     return Chunk(block_array)