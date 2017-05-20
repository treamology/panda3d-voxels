class BlockTypes:
    AIR = 0
    NOT_AIR = 1

class Block:
    __slots__ = ("type",)

    def __init__(self, block_type: int=BlockTypes.AIR):
        self.type = block_type

# class Block:
#     def __init__(self, block_type: int=BlockTypes.AIR):
#         self.type = block_type
