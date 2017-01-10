#pragma once

class Mesh
{
public:
	Mesh() {}

private:
	Vector3* m_Vertices;
	unsigned int m_VertexCount;

	Vector3* m_Normals;
	Vector3* m_Tangents;
	Vector2* m_Uv;
	Vector2* m_Uv2;
	Vector2* m_Uv3;
	Vector2* m_Uv4;
	unsigned int* m_Triangles;
	Color* m_Colors;


};