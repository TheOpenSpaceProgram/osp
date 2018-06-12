#include "dbillboard.h"



void DBillboard::draw(glm::mat4 view, glm::mat4 proj)
{
	if (Shader == NULL)
	{
		Shader = g_shader;
	}

	Shader->use();

	// We need to remove rotation from view matrix
	glm::vec3 pos = glm::vec3(view[3][0], view[3][1], view[3][2]);

	glm::vec3 vpos = glm::vec3(view[0][2], view[1][2], view[2][2]);

	glm::mat4 view_final;
	view_final = glm::translate(view_final, pos);

	glm::vec3 viewdir = vpos - tform.pos;
	viewdir = glm::normalize(viewdir);

	Shader->setvec3("viewdir", viewdir);
	Shader->setmat4("nview", view);
	Shader->setmat4("view", view_final);
	Shader->setmat4("proj", proj);
	Shader->setmat4("model", tform.build_matrix());

	glBindVertexArray(square.vao);
	glDrawArrays(GL_TRIANGLES, 0, square.vertices.size());
}

DBillboard::DBillboard()
{
	square = Mesh();

	Vertex v;

	// . .
	//   .
	// Top left
	v.pos = { -1, -1, 0 };
	v.col = { 1, 1, 1 };
	v.uv = { 0, 0 };
	square.vertices.push_back(v);

	// Top right
	v.pos = { 1, -1, 0 };
	v.col = { 1, 1, 1 };
	v.uv = { 1, 0 };
	square.vertices.push_back(v);

	// Bottom Right

	v.pos = { 1, 1, 0 };
	v.col = { 1, 1, 1 };
	v.uv = { 1, 1 };
	square.vertices.push_back(v);


	// .
	// . .

	// Top left
	v.pos = { -1, -1, 0 };
	v.col = { 1, 1, 1 };
	v.uv = { 0, 0 };
	square.vertices.push_back(v);

	// Bottom Left

	v.pos = { -1, 1, 0 };
	v.col = { 1, 1, 1 };
	v.uv = { 0, 1 };
	square.vertices.push_back(v);

	// Bottom Right

	v.pos = { 1, 1, 0 };
	v.col = { 1, 1, 1 };
	v.uv = { 1, 1 };
	square.vertices.push_back(v);
	
	square.build_array();
	square.upload();
}


DBillboard::~DBillboard()
{
}
