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

		elapsed = clock.getElapsedTime();

		if (elapsed.asSeconds() > 1.0f / 60.0f)
		{
			clock.restart();
			update();
			render();
		}
		
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[8];
GLubyte triangles[36]
{
		2, 3, 0,
		0, 1, 2,
		7, 6, 5,
		5, 4, 7,
		6, 7, 3,
		3, 2, 6,
		1, 0, 4,
		4, 5, 1,
		3, 7, 4,
		4, 0, 3,
		6, 2, 1,
		1, 5, 6 
};

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

	glTranslatef(0.0f, 0.0f, -10.0f);
	glEnable(GL_CULL_FACE);

	glewInit();

	/* Vertices counter-clockwise winding */

	vertex[0].coordinate[0] = -1.0f;
	vertex[0].coordinate[1] = -1.0f;
	vertex[0].coordinate[2] = 1.0f;

	vertex[1].coordinate[0] = 1.0f;
	vertex[1].coordinate[1] = -1.0f;
	vertex[1].coordinate[2] = 1.0f;

	vertex[2].coordinate[0] = 1.0f;
	vertex[2].coordinate[1] = 1.0f;
	vertex[2].coordinate[2] = 1.0f;

	vertex[3].coordinate[0] = -1.0f;
	vertex[3].coordinate[1] = 1.0f;
	vertex[3].coordinate[2] = 1.0f;

	vertex[4].coordinate[0] = -1.0f;
	vertex[4].coordinate[1] = -1.0f;
	vertex[4].coordinate[2] = -1.0f;

	vertex[5].coordinate[0] = 1.0f;
	vertex[5].coordinate[1] = -1.0f;
	vertex[5].coordinate[2] = -1.0f;

	vertex[6].coordinate[0] = 1.0f;
	vertex[6].coordinate[1] = 1.0f;
	vertex[6].coordinate[2] = -1.0f;

	vertex[7].coordinate[0] = -1.0f;
	vertex[7].coordinate[1] = 1.0f;
	vertex[7].coordinate[2] = -1.0f;

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

	vertex[7].color[0] = 1.0f;
	vertex[7].color[1] = 0.1f;
	vertex[7].color[2] = 0.0f;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
}

void Game::update()
{
	

	//Change vertex data
	/*vertex[0].coordinate[0] += -0.0001f;
	vertex[0].coordinate[1] += -0.0001f;
	vertex[0].coordinate[2] += -0.0001f;*/

	Matrix3 usableMatrix;

	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
			p = usableMatrix.RotationX(2.8125) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
			vertex[index].coordinate[2] = p.getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{

		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
			p = usableMatrix.RotationY(2.8125) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
			vertex[index].coordinate[2] = p.getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{

		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
			p = usableMatrix.RotationZ(2.8125) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
			vertex[index].coordinate[2] = p.getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{

		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
			p = usableMatrix.Scale(100.5, 100.5) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
			vertex[index].coordinate[2] = p.getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{

		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], vertex[index].coordinate[2] };
			p = usableMatrix.Scale(99.5, 99.5) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
			vertex[index].coordinate[2] = p.getZ();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = usableMatrix.Translate(0, 0.2) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = usableMatrix.Translate(0, -0.2) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = usableMatrix.Translate(-0.2, 0) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
		}

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int index = 0; index < 8; index++)
		{
			Vector3 p{ vertex[index].coordinate[0], vertex[index].coordinate[1], 1 };
			p = usableMatrix.Translate(0.2, 0) * p;

			vertex[index].coordinate[0] = p.getX();
			vertex[index].coordinate[1] = p.getY();
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

