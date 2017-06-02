#include "mesh_generation_task.h"

#include "geomVertexData.h"
#include "geomTriangles.h"
#include "geomVertexWriter.h"

#include "lvector3.h"

MeshGenerationTask::MeshGenerationTask(Chunk& chunk, string done_event_name) : AsyncTask("MeshGenerationTask"),
	chunk(chunk) {
	set_done_event(done_event_name);
	set_sort(2);
}

AsyncTask::DoneStatus MeshGenerationTask::do_task() {
	ChunkBlockData& blocks = *chunk.blocks;
	
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
			for (int z = 0; z < Chunk::CHUNK_HEIGHT; z++) {
				if (blocks(x, y, z).type == BlockType_Air) {
					continue;
				}

				bool xNeg = x > 0 && blocks(x - 1, y, z).type != BlockType_Air;
				bool xPos = x < Chunk::CHUNK_WIDTH - 1 && blocks(x + 1, y, z).type != BlockType_Air;
				bool yNeg = y > 0 && blocks(x, y - 1, z).type != BlockType_Air;
				bool yPos = y < Chunk::CHUNK_WIDTH - 1 && blocks(x, y + 1, z).type != BlockType_Air;
				bool zNeg = z > 0 && blocks(x, y, z - 1).type != BlockType_Air;
				bool zPos = z < Chunk::CHUNK_HEIGHT - 1 && blocks(x, y, z + 1).type != BlockType_Air;



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

				if (!yNeg) {
					vertex.add_data3f(x + 0, y + 0, z + 1);
					normal.add_data3f(0, -1, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 1, y + 0, z + 1);
					normal.add_data3f(0, -1, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 0, y + 0, z + 0);
					normal.add_data3f(0, -1, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 1, y + 0, z + 0);
					normal.add_data3f(0, -1, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					prim->add_vertices(offset, offset + 1, offset + 2);
					prim->add_vertices(offset + 2, offset + 1, offset + 3);
					offset += 4;
				}

				if (!yPos) {
					vertex.add_data3f(x + 1, y + 1, z + 1);
					normal.add_data3f(0, 1, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 0, y + 1, z + 1);
					normal.add_data3f(0, 1, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 1, y + 1, z + 0);
					normal.add_data3f(0, 1, 0);
					color.add_data4f(1, 1, 1, 1);
					texcoord.add_data2f(1, 1);

					vertex.add_data3f(x + 0, y + 1, z + 0);
					normal.add_data3f(0, 1, 0);
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

	finished_geom_node = new GeomNode("chunkgnode");
	finished_geom_node->add_geom(geom);

	return AsyncTask::DS_done;
}