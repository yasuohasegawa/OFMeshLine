#include "Line.h"

// constructor
Line::Line()
{
	m.glScale(100, 100, 100);
	//m.glRotate(20, 0, 0, 1);

	vector<glm::vec3> l;

	int numOfPolygons = 12;
	for (int i = 0; i <= numOfPolygons; i++) {
		float rad = (360.0 / (float)numOfPolygons) * i * PI / 180.0;
		float dist = 3.5;
		float x = cos(rad)*dist;
		float y = sin(rad)*dist;
		l.push_back(glm::vec3(x,y, 0.0));
	}

	/*
	l.push_back(glm::vec3(-4.0, 1.0, 0.0));
	l.push_back(glm::vec3(-3.0, 0.0, 0.0));
	l.push_back(glm::vec3(-2.0, -0.5, 0.0));
	l.push_back(glm::vec3(-1.0, 0.0, 0.0));
	l.push_back(glm::vec3(0.0,0.0,0.0));
	l.push_back(glm::vec3(1.0, 0.0, 0.0));
	l.push_back(glm::vec3(2.0, 0.5, 0.0));
	l.push_back(glm::vec3(3.0, 0.0, 0.0));
	l.push_back(glm::vec3(4.0, -1.0, 0.0));
	*/

	createMesh(&m, l, 0.15, glm::vec3(1.0, 0.5, 0.5));
}

// destructor
Line::~Line()
{

}

void Line::createMesh(ofMatrix4x4 * mat, vector<glm::vec3> points, float width, glm::vec3 color) {
	int faceCount = 0;
	float startUvX = 0.0;
	float endUvX = 0.0;

	glm::vec3 next = points[1];
	glm::vec3 now = points[0];
	glm::vec3 dir = next - now;
	dir = glm::normalize(dir);

	glm::vec3 plus90 = now + glm::vec3(-dir.y, dir.x, 0.0) * width;
	glm::vec3 minus90 = now + glm::vec3(dir.y, -dir.x, 0.0) * width;

	vertices.push_back(ofVec3f(minus90.x, minus90.y, 0)* *mat);
	vertices.push_back(ofVec3f(plus90.x, plus90.y, 0)* *mat);

	colors.push_back(ofFloatColor(color.x, color.y, color.z, 1.0));
	colors.push_back(ofFloatColor(color.x, color.y, color.z, 1.0));

	uvs.push_back(glm::vec2(0, 1));
	uvs.push_back(glm::vec2(0, 0));

	for (int i = 1; i < points.size(); i++)
	{
		glm::vec3 prev = points[i - 1];
		glm::vec3 now = points[i];
		glm::vec3 dir = now - prev;
		dir = glm::normalize(dir);

		glm::vec3 plus90 = now + glm::vec3(-dir.y, dir.x, 0.0) * width;
		glm::vec3 minus90 = now + glm::vec3(dir.y, -dir.x, 0.0) * width;

		vertices.push_back(ofVec3f(minus90.x, minus90.y, 0)* *mat);
		vertices.push_back(ofVec3f(plus90.x, plus90.y, 0)* *mat);

		colors.push_back(ofFloatColor(color.x, color.y, color.z, 1.0));
		colors.push_back(ofFloatColor(color.x, color.y, color.z, 1.0));

		indices.push_back(faceCount);
		indices.push_back(faceCount + 1);
		indices.push_back(faceCount + 2);
		indices.push_back(faceCount + 1);
		indices.push_back(faceCount + 3);
		indices.push_back(faceCount + 2);

		faceCount += 2;

		float uvOffsetX = (float)i / (float)(points.size()) * 1.0;
		uvs.push_back(ofVec2f(uvOffsetX, 0));
		uvs.push_back(ofVec2f(uvOffsetX, 1));
	}

	vboMesh.addVertices(vertices);
	vboMesh.addColors(colors);
	vboMesh.addIndices(indices);
	vboMesh.addTexCoords(uvs);
}

void Line::drawMesh() {

	vboMesh.drawWireframe();
	vboMesh.enableNormals();

	vboMesh.draw();
	//vboMesh.draw(OF_MESH_WIREFRAME);
}