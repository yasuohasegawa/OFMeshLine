#pragma once
#include <stdio.h>
#include "ofMain.h"

class Line
{
private:
	void createMesh(ofMatrix4x4 * mat, vector<glm::vec3> points, float width, glm::vec3 color);
public:
	Line();
	~Line();

	void drawMesh();

	ofVboMesh vboMesh;
	ofMatrix4x4 m;

	vector<glm::vec3> vertices;
	vector<unsigned> indices;
	vector<glm::vec2> uvs;
	vector<ofFloatColor> colors;
};