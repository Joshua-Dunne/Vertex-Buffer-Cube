#include <Game.h>

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[36];
GLubyte triangles[12];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	/* Vertices counter-clockwise winding */

	// ------------ 2, 3, 0

	vertex[0].coordinate[0] = 1.0f;
	vertex[0].coordinate[1] = 1.0f;
	vertex[0].coordinate[2] = 1.0f;

	vertex[1].coordinate[0] = -1.0f;
	vertex[1].coordinate[1] = 1.0f;
	vertex[1].coordinate[2] = 1.0f;

	vertex[2].coordinate[0] = -1.0f;
	vertex[2].coordinate[1] = -1.0f;
	vertex[2].coordinate[2] = 1.0f;

	// ------------ 0, 1, 2

	vertex[3].coordinate[0] = -1.0f;
	vertex[3].coordinate[1] = -1.0f;
	vertex[3].coordinate[2] = 1.0f;

	vertex[4].coordinate[0] = 1.0f;
	vertex[4].coordinate[1] = -1.0f;
	vertex[4].coordinate[2] = 1.0f;

	vertex[5].coordinate[0] = 1.0f;
	vertex[5].coordinate[1] = 1.0f;
	vertex[5].coordinate[2] = 1.0f;

	

	// Fill Vector3 data for Matrix3 calculations later on
	for (size_t index = 0; index < 8; ++index)
	{
		points[index].setX(vertex[index].coordinate[0]);
		points[index].setY(vertex[index].coordinate[1]);
		points[index].setZ(vertex[index].coordinate[2]);
	}


	// ------------------------------------------------------------------------

	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	vertex[6].color[0] = 0.7f;
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[7].color[0] = 0.8f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 0.0f;


	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;
	triangles[6] = 6;   triangles[7] = 7;   triangles[8] = 8;
	triangles[9] = 9;   triangles[10] = 10;   triangles[11] = 11;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnable(GL_CULL_FACE);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	//Change vertex data
	/*vertex[0].coordinate[0] += -0.0001f;
	vertex[0].coordinate[1] += -0.0001f;
	vertex[0].coordinate[2] += -0.0001f;*/

	Matrix3 usableMatrix;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{

		usableMatrix = usableMatrix.RotationX(0.6);

		for (int index = 0; index < 8; index++)
		{
			points[index] = usableMatrix * points[index];

			vertex[index].coordinate[0] = points[index].getX();
			vertex[index].coordinate[1] = points[index].getY();
			vertex[index].coordinate[2] = points[index].getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{

		usableMatrix = usableMatrix.Scale(99.9, 99.9);

		for (int index = 0; index < 8; index++)
		{
			points[index] = usableMatrix * points[index];

			vertex[index].coordinate[0] = points[index].getX();
			vertex[index].coordinate[1] = points[index].getY();
			vertex[index].coordinate[2] = points[index].getZ();
		}

	}

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

