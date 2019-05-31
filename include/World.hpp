#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <gfx.h>


class ChunkMesh
{

};

class BlockMesh
{

};

class BlockQuadMesh
{
};

class PackedBlockQuadMesh // 192 bit | 24 bytes
{
	glm::i32vec4 corners;	// 2_10_10_10_REV -> remaining bits for flags?
	glm::i16vec4 uvs;		// 8_8
};