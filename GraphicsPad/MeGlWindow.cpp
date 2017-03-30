#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <QtGui\qmouseevent>
#include <QtGui\qkeyevent>
#include "MeGlWindow.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtx\transform.hpp>
#include <Primitives\Vertex.h>
#include <Primitives\ShapeGenerator.h>
#include <QtDeclarative\qdeclarativeview.h>
#include <gtc\constants.hpp>
#include <Camera.h>
#include <MyModel.h>

using namespace std;
using glm::vec3;
using glm::mat4;
using glm::pi;

GLuint passThroughProgramID;
GLuint programID;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE =  NUM_FLOATS_PER_VERTICE * sizeof(float);
Camera camera;

const uint MAX_TRIS = 20;
uint numTris = 0;
glm::vec4 shitTimer(1.0f, 1.0f, 1.0f, 1.0f);
GLuint TEAPOT_NUM_INDICES;
GLuint PLANE_NUM_INDICES;
GLuint ARROW_NUM_INDICES;
GLuint CUBE_NUM_INDICES;
GLuint SPHERE_NUM_INDICES;
GLuint TORUS_NUM_INDICES;

GLuint TEAPOT_NORMALS_NUM_INDICES;
GLuint PLANE_NORMALS_NUM_INDICES;
GLuint ARROW_NORMALS_NUM_INDICES;
GLuint CUBE_NORMALS_NUM_INDICES;
GLuint SPHERE_NORMALS_NUM_INDICES;
GLuint TORUS_NORMALS_NUM_INDICES;

GLuint theBufferID; //its a name of the buffer?

//Objects
GLuint teapotVertexArrayObjectID;
GLuint teapotIndexDataByteOffset;
GLuint arrowVertexArrayObjectID;
GLuint arrowIndexDataByteOffset;
GLuint cubeVertexArrayObjectID;
GLuint cubeIndexDataByteOffset;
GLuint sphereVertexArrayObjectID;
GLuint sphereIndexDataByteOffset;
GLuint torusVertexArrayObjectID;
GLuint torusIndexDataByteOffset;
GLuint planeVertexArrayObjectID;
GLuint planeIndexDataByteOffset;

//Normals
GLuint teapotNormalsVertexArrayObjectID;
GLuint teapotNormalsIndexDataByteOffset;
GLuint arrowNormalsVertexArrayObjectID;
GLuint arrowNormalsIndexDataByteOffset;
GLuint planeNormalsVertexArrayObjectID;
GLuint planeNormalsIndexDataByteOffset;
GLuint cubeNormalsVertexArrayObjectID;
GLuint cubeNormalsIndexDataByteOffset;
GLuint sphereNormalsVertexArrayObjectID;
GLuint sphereNormalsIndexDataByteOffset;
GLuint torusNormalsVertexArrayObjectID;
GLuint torusNormalsIndexDataByteOffset;


GLint ambientLightUniformLocation;
GLint lightPositionUniformLocation;
GLuint eyePositionWorldUniformLocation;
GLuint shittyTimerUniformLocation;

MeGlWindow::MeGlWindow(MyModel* theModel) : theModel(theModel)
{

}

void MeGlWindow::sendDataToOpenGL()
{

	//cube
	ShapeData cube = ShapeGenerator::makeCube();
	ShapeData cubeNormals = ShapeGenerator::generateNormals(cube);
	ShapeData teapot = ShapeGenerator::makeTeapot();
	ShapeData teapotNormals = ShapeGenerator::generateNormals(teapot);
	ShapeData arrow = ShapeGenerator::makeArrow();
	ShapeData arrowNormals = ShapeGenerator::generateNormals(arrow);
	ShapeData plane = ShapeGenerator::makePlane(20);
	ShapeData planeNormals = ShapeGenerator::generateNormals(plane);
	ShapeData torus = ShapeGenerator::makeTorus();
	ShapeData torusNormals = ShapeGenerator::generateNormals(torus);
	ShapeData sphere = ShapeGenerator::makeSphere();
	ShapeData sphereNormals = ShapeGenerator::generateNormals(sphere);


	glGenBuffers(1, &theBufferID); //gl pointer
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);

	glBufferData(GL_ARRAY_BUFFER,
		teapot.vertexBufferSize() + teapot.indexBufferSize() +
		arrow.vertexBufferSize() + arrow.indexBufferSize() +
		cube.vertexBufferSize() + cube.indexBufferSize() +
		plane.vertexBufferSize() + plane.indexBufferSize() +
		torus.vertexBufferSize() + torus.indexBufferSize() +
		sphere.vertexBufferSize() + sphere.indexBufferSize() +
		teapotNormals.vertexBufferSize() + teapotNormals.indexBufferSize() +
		arrowNormals.vertexBufferSize() + arrowNormals.indexBufferSize() +
		cubeNormals.vertexBufferSize() + cubeNormals.indexBufferSize() +
		planeNormals.vertexBufferSize() + planeNormals.indexBufferSize() +
		torusNormals.vertexBufferSize() + torusNormals.indexBufferSize() +
		sphereNormals.vertexBufferSize() + sphereNormals.indexBufferSize(), 0, GL_STATIC_DRAW);

	//Objects
	GLsizeiptr currentOffset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapot.vertexBufferSize(), teapot.vertices);
	currentOffset += teapot.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapot.indexBufferSize(), teapot.indices);
	currentOffset += teapot.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), arrow.vertices);
	currentOffset += arrow.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), arrow.indices);
	currentOffset += arrow.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.vertexBufferSize(), cube.vertices);
	currentOffset += cube.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.indexBufferSize(), cube.indices);
	currentOffset += cube.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.vertexBufferSize(), plane.vertices);
	currentOffset += plane.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.indexBufferSize(), plane.indices);
	currentOffset += plane.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, torus.vertexBufferSize(), torus.vertices);
	currentOffset += torus.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, torus.indexBufferSize(), torus.indices);
	currentOffset += torus.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sphere.vertexBufferSize(), sphere.vertices);
	currentOffset += sphere.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sphere.indexBufferSize(), sphere.indices);
	currentOffset += sphere.indexBufferSize();

	//Object Normals
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapotNormals.vertexBufferSize(), teapotNormals.vertices);
	currentOffset += teapotNormals.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapotNormals.indexBufferSize(), teapotNormals.indices);
	currentOffset += teapotNormals.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrowNormals.vertexBufferSize(), arrowNormals.vertices);
	currentOffset += arrowNormals.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrowNormals.indexBufferSize(), arrowNormals.indices);
	currentOffset += arrowNormals.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, planeNormals.vertexBufferSize(), planeNormals.vertices);
	currentOffset += planeNormals.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, planeNormals.indexBufferSize(), planeNormals.indices);
	currentOffset += planeNormals.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cubeNormals.vertexBufferSize(), cubeNormals.vertices);
	currentOffset += cubeNormals.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cubeNormals.indexBufferSize(), cubeNormals.indices);	
	currentOffset += cubeNormals.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, torusNormals.vertexBufferSize(), torusNormals.vertices);
	currentOffset += torusNormals.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, torusNormals.indexBufferSize(), torusNormals.indices);
	currentOffset += torusNormals.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sphereNormals.vertexBufferSize(), sphereNormals.vertices);
	currentOffset += sphereNormals.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, sphereNormals.indexBufferSize(), sphereNormals.indices);

	//Indicies
	TEAPOT_NUM_INDICES = teapot.numIndices;
	ARROW_NUM_INDICES = arrow.numIndices;
	PLANE_NUM_INDICES = plane.numIndices;
	CUBE_NUM_INDICES = cube.numIndices;
	TORUS_NUM_INDICES = torus.numIndices;
	SPHERE_NUM_INDICES = sphere.numIndices;

	//Normal Indices
	TEAPOT_NORMALS_NUM_INDICES = teapotNormals.numIndices;
	PLANE_NORMALS_NUM_INDICES = planeNormals.numIndices;
	ARROW_NORMALS_NUM_INDICES = arrowNormals.numIndices;
	CUBE_NORMALS_NUM_INDICES = cubeNormals.numIndices;
	TORUS_NORMALS_NUM_INDICES = torusNormals.numIndices;
	SPHERE_NORMALS_NUM_INDICES = sphereNormals.numIndices;

	//Objects
	glGenVertexArrays(1, &teapotVertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);
	glGenVertexArrays(1, &planeVertexArrayObjectID);
	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &torusVertexArrayObjectID);
	glGenVertexArrays(1, &sphereVertexArrayObjectID);

	//Object Normals
	glGenVertexArrays(1, &teapotNormalsVertexArrayObjectID);
	glGenVertexArrays(1, &arrowNormalsVertexArrayObjectID);
	glGenVertexArrays(1, &planeNormalsVertexArrayObjectID);
	glGenVertexArrays(1, &cubeNormalsVertexArrayObjectID);
	glGenVertexArrays(1, &torusNormalsVertexArrayObjectID);
	glGenVertexArrays(1, &sphereNormalsVertexArrayObjectID);

	//Teapot
	glBindVertexArray(teapotVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Arrow
	glBindVertexArray(arrowVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint arrowbyteOffset = teapot.vertexBufferSize() + teapot.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)arrowbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(arrowbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Cube
	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint cubebyteOffset = arrowbyteOffset + arrow.vertexBufferSize() + arrow.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)cubebyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(cubebyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(cubebyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Plane
	glBindVertexArray(planeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint planebyteOffset = cubebyteOffset + cube.vertexBufferSize() + cube.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)planebyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(planebyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(planebyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);


	//Torus
	glBindVertexArray(torusVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint torusbyteOffset = planebyteOffset + plane.vertexBufferSize() + plane.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*) torusbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(torusbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(torusbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Sphere
	glBindVertexArray(sphereVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint spherebyteOffset = torusbyteOffset + torus.vertexBufferSize() + torus.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)spherebyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(spherebyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(spherebyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//TeaPotNormals
	glBindVertexArray(teapotNormalsVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint teapotNormalsbyteOffset = spherebyteOffset + sphere.vertexBufferSize() + sphere.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)teapotNormalsbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(teapotNormalsbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(teapotNormalsbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Arrow Normals
	glBindVertexArray(arrowNormalsVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint arrowNormalsbyteOffset = teapotNormalsbyteOffset + teapotNormals.vertexBufferSize() + teapotNormals.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)arrowNormalsbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowNormalsbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(teapotNormalsbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Plane Normals
	glBindVertexArray(planeNormalsVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint planeNormalsbyteOffset = arrowNormalsbyteOffset + arrowNormals.vertexBufferSize() + arrowNormals.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)planeNormalsbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(planeNormalsbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(planeNormalsbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Cube Normals
	glBindVertexArray(cubeNormalsVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint cubeNormalsbyteOffset = planeNormalsbyteOffset + planeNormals.vertexBufferSize() + planeNormals.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*) cubeNormalsbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(cubeNormalsbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(cubeNormalsbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Torus Normals
	glBindVertexArray(torusNormalsVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint torusNormalsbyteOffset = cubeNormalsbyteOffset + cubeNormals.vertexBufferSize() + cubeNormals.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)torusNormalsbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(torusNormalsbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(torusNormalsbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	//Sphere Normals
	glBindVertexArray(sphereNormalsVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint sphereNormalsbyteOffset = torusNormalsbyteOffset + torusNormals.vertexBufferSize() + torusNormals.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)sphereNormalsbyteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sphereNormalsbyteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sphereNormalsbyteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	arrowIndexDataByteOffset = arrowbyteOffset + arrow.vertexBufferSize();
	teapotIndexDataByteOffset = teapot.vertexBufferSize();
	planeIndexDataByteOffset = planebyteOffset + plane.vertexBufferSize();
	cubeIndexDataByteOffset = cubebyteOffset + cube.vertexBufferSize();

	torusIndexDataByteOffset = torusbyteOffset + torus.vertexBufferSize();
	sphereIndexDataByteOffset = spherebyteOffset + sphere.vertexBufferSize();

	teapotNormalsIndexDataByteOffset = teapotNormalsbyteOffset + teapotNormals.vertexBufferSize();
	arrowNormalsIndexDataByteOffset = arrowNormalsbyteOffset + arrowNormals.vertexBufferSize();
	planeNormalsIndexDataByteOffset = planeNormalsbyteOffset + planeNormals.vertexBufferSize();
	cubeNormalsIndexDataByteOffset = cubeNormalsbyteOffset + cubeNormals.vertexBufferSize();
	torusNormalsIndexDataByteOffset = torusNormalsbyteOffset + torusNormals.vertexBufferSize();
	sphereNormalsIndexDataByteOffset = sphereNormalsbyteOffset + sphereNormals.vertexBufferSize();
	
	teapot.CleanUp();
	arrow.CleanUp();
	plane.CleanUp();
	cube.CleanUp();
	torus.CleanUp();
	sphere.CleanUp();

	teapotNormals.CleanUp();
	arrowNormals.CleanUp();
	planeNormals.CleanUp();
	cubeNormals.CleanUp();
	torusNormals.CleanUp();
	sphereNormals.CleanUp();
}

void MeGlWindow::keyPressEvent()
{

	if (GetAsyncKeyState('D') & 0x8000)
	{
		camera.strafeRight();
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		camera.strafeLeft();
	}

	if (GetAsyncKeyState('W') & 0x8000)
	{
		camera.moveForward();
	}

	if (GetAsyncKeyState('S') & 0x8000)
	{
		camera.moveBackward();
	}

	if (GetAsyncKeyState('R') & 0x8000)
	{
		camera.moveUp();
	}

	if (GetAsyncKeyState('F') & 0x8000)
	{
		camera.moveDown();
	}

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		exit(0);
	}
}

void MeGlWindow::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	mat4 modelToProjectionMatrix;
	mat4 viewToprojectMatrix = glm::perspective(glm::radians(60.0f), ((float)width()) / height(), 0.1f, 20.0f);
	mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	mat4 worldToProjectionMatrix = viewToprojectMatrix * worldToViewMatrix;

	GLuint fullTransformUniformLocation;
	GLuint modelToWorldMatrixUniformLocation;

	fullTransformUniformLocation = glGetUniformLocation(programID, "modelToProjectionMatrix");
	modelToWorldMatrixUniformLocation = glGetUniformLocation(programID, "modelToWorldMatrix");

	glUseProgram(programID);

	glm::vec3 lightPositionWorld = theModel->lightPosition;
	lightPositionUniformLocation = glGetUniformLocation(programID, "lightPositionWorld");
	glUniform3fv(lightPositionUniformLocation, 1, &lightPositionWorld[0]);
	
	//Ambient Light Position
	ambientLightUniformLocation = glGetUniformLocation(programID, "ambientLight");
	glm::vec4 ambientLight(0.15f, 0.15f, 0.15f, 1.0f);
	glUniform4fv(ambientLightUniformLocation, 1, &ambientLight[0]);

	//Eye Position World
	eyePositionWorldUniformLocation = glGetUniformLocation(programID, "eyePositionWorld");
	glm::vec3 eyePosition = camera.getPosition();
	glUniform3fv(eyePositionWorldUniformLocation, 1, &eyePosition[0]);

	//Timer 
	shittyTimerUniformLocation = glGetUniformLocation(programID, "shittyTimer");
	shitTimer.x += 0.01f;
	shitTimer.y += 0.01f;
	shitTimer.z += 0.01f;
	//std::cout << shitTimer.x << std::endl;
	glUniform4f(shittyTimerUniformLocation, shitTimer.x, shitTimer.y, shitTimer.z, shitTimer.t);

	//Teapots
	glBindVertexArray(teapotVertexArrayObjectID);
	mat4 teapot1ModelToWorldMatrix =
		glm::translate(vec3(-3.0f, 0.0f, -6.0f)) *
		glm::rotate(glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));
	modelToProjectionMatrix = worldToProjectionMatrix * teapot1ModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&teapot1ModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, TEAPOT_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)teapotIndexDataByteOffset);
	//glBindVertexArray(teapotNormalsVertexArrayObjectID);
	//glDrawElements(GL_LINES, TEAPOT_NORMALS_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)teapotNormalsIndexDataByteOffset);

	mat4 teapot2ModelToWorldMatrix =
		glm::translate(vec3(3.0f, 0.0f, -6.0f)) *
		glm::rotate(glm::radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)) *
		glm::rotate(glm::radians(-90.0f), vec3(0.0f, 0.0f, 1.0f));
	modelToProjectionMatrix = worldToProjectionMatrix * teapot2ModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&teapot2ModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, TEAPOT_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)teapotIndexDataByteOffset);

	//Arrow 1
	glBindVertexArray(arrowVertexArrayObjectID);
	mat4 arrowModelToWorldMatrix1 =
		glm::translate(vec3(0.0f, 0.0f, -3.0f));
	modelToProjectionMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix1;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&arrowModelToWorldMatrix1[0][0]);
	glDrawElements(GL_TRIANGLES, ARROW_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)arrowIndexDataByteOffset);
	//glBindVertexArray(arrowNormalsVertexArrayObjectID);
	//glDrawElements(GL_LINES, ARROW_NORMALS_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)arrowNormalsIndexDataByteOffset);
	//Arrow 2
	glBindVertexArray(arrowVertexArrayObjectID);
	mat4 arrowModelToWorldMatrix2 =
		glm::translate(vec3(0.0f, 0.0f, 3.0f))*
		glm::rotate(glm::radians(-180.0f), vec3(0.0f, 1.0f, 0.0f));
	modelToProjectionMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix2;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&arrowModelToWorldMatrix2[0][0]);
	glDrawElements(GL_TRIANGLES, ARROW_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)arrowIndexDataByteOffset);
	//glBindVertexArray(arrowNormalsVertexArrayObjectID);
	//glDrawElements(GL_LINES, ARROW_NORMALS_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)arrowNormalsIndexDataByteOffset);

	//Plane
	glBindVertexArray(planeVertexArrayObjectID);
	mat4 planeModelToWorldMatrix;
	modelToProjectionMatrix = worldToProjectionMatrix * planeModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&planeModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, PLANE_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)planeIndexDataByteOffset);
	//glBindVertexArray(planeNormalsVertexArrayObjectID);
	//glDrawElements(GL_LINES, PLANE_NORMALS_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)planeNormalsIndexDataByteOffset);

	//torus
	glBindVertexArray(torusVertexArrayObjectID);
	mat4 torusModelToWorldMatrix = 
		glm::translate(vec3(3.0f, 1.0f, 0.0f));
	modelToProjectionMatrix = worldToProjectionMatrix * torusModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&torusModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, TORUS_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)torusIndexDataByteOffset);

	//sphere
	glBindVertexArray(sphereVertexArrayObjectID);
	mat4 sphereModelToWorldMatrix =
		glm::translate(vec3(-3.0f, 1.0f, 0.0f));;
	modelToProjectionMatrix = worldToProjectionMatrix * sphereModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&sphereModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, SPHERE_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)sphereIndexDataByteOffset);

	//Cube Light
	glBindVertexArray(cubeVertexArrayObjectID);
	mat4 cubeModelToWorldMatrix =
		glm::translate(lightPositionWorld) *
		glm::scale(vec3(0.1f, 0.1f, 0.1f));
	modelToProjectionMatrix = worldToProjectionMatrix * cubeModelToWorldMatrix;
	glUseProgram(passThroughProgramID);
	fullTransformUniformLocation = glGetUniformLocation(passThroughProgramID, "modelToProjectionMatrix");
	glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	modelToWorldMatrixUniformLocation = glGetUniformLocation(passThroughProgramID, "modelToWorldMatrix");
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&cubeModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, CUBE_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)cubeIndexDataByteOffset);
	//glBindVertexArray(cubeNormalsVertexArrayObjectID);
	//glDrawElements(GL_LINES, CUBE_NORMALS_NUM_INDICES, GL_UNSIGNED_SHORT, (void*)cubeNormalsIndexDataByteOffset);
}

bool MeGlWindow::checkStatus(GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint compileStatus;
	glGetShaderiv(objectID, statusType, &compileStatus);

	if (compileStatus != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);

		cout << buffer << endl;
		delete[] buffer;
		return false;
	}

	return true;
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	camera.mouseUpdate(glm::vec2(e->x(), e->y()));
}

//void keyPressEvent(QKeyEvent* e)
//{
//
//	if (GetAsyncKeyState(VK_RIGHT))
//	{
//		camera.strafeRight();
//	}
//
//	if (GetAsyncKeyState(VK_LEFT))
//	{
//		camera.strafeLeft();
//	}
//
//	if (GetAsyncKeyState(VK_UP))
//	{
//		camera.moveForward();
//	}
//
//	if (GetAsyncKeyState(VK_DOWN))
//	{
//		camera.moveBackward();
//	}
//
//
//	switch (e->key())
//	{
//	case Qt::Key::Key_W:
//		//camera.moveForward();
//		break;
//	case Qt::Key::Key_S:
//		//camera.moveBackward();
//		break;
//	case Qt::Key::Key_A:
//		//camera.strafeLeft();
//		break;
//	case Qt::Key::Key_D:
//		//	camera.strafeRight();
//		break;
//	case Qt::Key::Key_R:
//		camera.moveUp();
//		break;
//	case Qt::Key::Key_F:
//		camera.moveDown();
//		break;
//	}
//
//	repaint();
//}

bool MeGlWindow::checkShaderStatus(GLint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool MeGlWindow::checkProgramStatus(GLint programID)
{
	//Somethings not returning the right shit here
	return true;//checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string MeGlWindow::readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);

	if(! meInput.good())
	{
		cout << "File dun Fucked Up...." << fileName;
		exit(1);
	}

	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}

void MeGlWindow::installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);


	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);


	GLuint vertexShaderPassID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderPassID = glCreateShader(GL_FRAGMENT_SHADER);

	temp = readShaderCode("VertexShaderPassThroughCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderPassID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderPassThroughCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderPassID, 1, adapter, 0);

	glCompileShader(vertexShaderPassID);
	glCompileShader(fragmentShaderPassID);

	if (!checkShaderStatus(vertexShaderPassID) || !checkShaderStatus(fragmentShaderPassID))
		return;

	passThroughProgramID = glCreateProgram();
	glAttachShader(passThroughProgramID, vertexShaderPassID);
	glAttachShader(passThroughProgramID, fragmentShaderPassID);

	glLinkProgram(passThroughProgramID);

	if (!checkProgramStatus(passThroughProgramID))
		return;

	glDeleteShader(vertexShaderPassID);
	glDeleteShader(fragmentShaderPassID);

}

void MeGlWindow::initializeGL()
{
	setMinimumSize(1300, 600);
	//QCursor c = cursor();
	//c.setPos(mapToGlobal(QPoint(width() / 2, height() / 2)));
	//c.setShape(Qt::BlankCursor);

	//setCursor(c);
	//setMouseTracking(true);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	sendDataToOpenGL();
	installShaders();

	connect(&mytimer, SIGNAL(timeout()),
		this, SLOT(update()));
	mytimer.start(1);
}

void MeGlWindow::update()
{
	keyPressEvent();
	repaint();


}


 MeGlWindow::~MeGlWindow()
{
	//glDeleteBuffers(1, &theBufferID);
	glUseProgram(0);
	glDeleteProgram(programID);
}