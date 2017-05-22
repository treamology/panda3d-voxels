#include "ChunkGenManager.h"
#include "Chunk.h"

#include "geomVertexWriter.h"
#include "geomVertexData.h"
#include "geomVertexFormat.h"
#include "geomTriangles.h"
#include "geom.h"

#include "BlockType.h"

ChunkGenManager::ChunkGenManager() : NodePath("wtf") {}

Block*** ChunkGenManager::generate_blocks(int chunk_x, int chunk_y, int seed) {
	Block*** block_array = new Block**[Chunk::CHUNK_WIDTH];
	for (int i = 0; i < Chunk::CHUNK_WIDTH; i++) {
		block_array[i] = new Block*[Chunk::CHUNK_WIDTH];
		for (int j = 0; j < Chunk::CHUNK_WIDTH; j++) {
			block_array[i][j] = new Block[Chunk::CHUNK_HEIGHT];
		}
	}
	return block_array;
}

PT(GeomNode) ChunkGenManager::generate_mesh(Block*** block_data) {
	PT(GeomVertexData) data;
	data = new GeomVertexData("chunk", GeomVertexFormat::get_v3n3c4t2(), Geom::UH_static);
	PT(GeomTriangles) prim;
	prim = new GeomTriangles(Geom::UH_static);

	GeomVertexWriter vertex, normal, color, texcoord;
	vertex = GeomVertexWriter(data, "vertex");
	normal = GeomVertexWriter(data, "normal");
	color = GeomVertexWriter(data, "color");
	texcoord = GeomVertexWriter(data, "texcoord");

	int offset = 0;

	for (int x = 0; x < Chunk::CHUNK_WIDTH; x++) {
		for (int y = 0; y < Chunk::CHUNK_WIDTH; y++) {
			for (int z = 0; z < Chunk::CHUNK_WIDTH; z++) {
				if (block_data[x][y][z].type == BlockType_Air) {
					continue;
				}

				bool xNeg = x > 0 && block_data[x - 1][y][z].type != BlockType_Air;
				bool xPos = x < Chunk::CHUNK_WIDTH - 1 && block_data[x + 1][y][z].type != BlockType_Air;
				bool yNeg = y > 0 && block_data[x][y - 1][z].type != BlockType_Air;
				bool yPos = y < Chunk::CHUNK_WIDTH - 1 && block_data[x][y + 1][z].type != BlockType_Air;
				bool zNeg = z > 0 && block_data[x][y][z - 1].type != BlockType_Air;
				bool zPos = z < Chunk::CHUNK_HEIGHT - 1 && block_data[x][y][z + 1].type != BlockType_Air;

				if (!xNeg) {
					vertex.add_data3f(x + 0, y + 0, z + 1);
					normal.add_data3f(-1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 0, y + 1, z + 1);
					normal.add_data3f(-1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 0, y + 0, z + 0);
					normal.add_data3f(-1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 0, y + 1, z + 0);
					normal.add_data3f(-1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					prim->add_vertices(offset, offset + 1, offset + 2);
					prim->add_vertices(offset + 2, offset + 1, offset + 3);
					offset += 4;
				}

				if (!xPos) {
					vertex.add_data3f(x + 1, y + 1, z + 1);
					normal.add_data3f(1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 1, y + 0, z + 1);
					normal.add_data3f(1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 1, y + 1, z + 0);
					normal.add_data3f(1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 1, y + 0, z + 0);
					normal.add_data3f(1, 0, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					prim->add_vertices(offset, offset + 1, offset + 2);
					prim->add_vertices(offset + 2, offset + 1, offset + 3);
					offset += 4;
				}
			}
		}
	}

	PT(Geom) geom;
	geom = new Geom(data);
	geom->add_primitive(prim);

	PT(GeomNode) node;
	node = new GeomNode("chunkgnode");
	node->add_geom(geom);

	return node;
}