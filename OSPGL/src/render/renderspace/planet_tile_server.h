#pragma once
#include <unordered_map>
#include "../../orbital/planet.h"
#include "quad_tree_node.h"
#include "../../util/defines.h"
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../renderlow/mesh.h"
#include "../../util/math_util.h"
#include <vector>

struct PlanetTilePath
{
	enum PlanetSide
	{
		PX, NX, PY, NY, PZ, NZ
	};

	std::vector<QuadTreeNode::QuadTreeQuadrant> path;
	PlanetSide side;

	size_t get_depth();
	glm::dvec2 getMin();
	double getSize();

	glm::vec3 get_tile_origin();
	glm::vec3 get_tile_rotation();
	glm::vec3 get_tile_translation(bool spheric = false);
	glm::vec3 get_tile_scale();

	PlanetTilePath(std::vector<QuadTreeNode::QuadTreeQuadrant> path, PlanetSide side)
	{
		this->path = path;
		this->side = side;
	}
};

bool operator==(const PlanetTilePath& a, const PlanetTilePath& b);

struct PlanetTilePathHasher
{
	std::size_t operator()(const PlanetTilePath &t) const
	{
		std::size_t ret = 0;
		hash_combine(ret, t.side);
		for (size_t i = 0; i < t.path.size(); i++)
		{
			hash_combine(ret, t.path[i]);
		}

		return ret;
	}
};

struct PlanetTile
{
	PlanetTilePath path;

	std::vector<float> verts;
	std::vector<uint16_t> indices;

	int users;

	GLuint vbo, vao, ebo;

	bool isUploaded();
	// Any combination of sides may be a lower quality (TODO)
	void upload(bool u_lowq, bool r_lowq, bool d_lowq, bool l_downq);
	void unload();

	PlanetTile(PlanetTilePath nPath, size_t verticesPerSide, const Planet& planet);
};


// Handles generation and caching of planetary tiles
class PlanetTileServer
{
public:

	

	Planet* planet;

	std::unordered_map<PlanetTilePath, PlanetTile*, PlanetTilePathHasher> tiles;

	PlanetTile* load(PlanetTilePath path);
	void unload(PlanetTilePath path, bool unload_now = false);

	// Unloads all unused tiles
	void unload_unused();

	// Minimum depth at which tiles get unloaded, bigger tiles
	// will be loaded even if not used
	size_t minDepthToUnload = 2;

	// Vertices in the side of each tile, smallest tiles
	// simply get smallest heightmap samples
	size_t verticesPerSide = 8;

	PlanetTileServer(Planet* planet);
	~PlanetTileServer();
};

