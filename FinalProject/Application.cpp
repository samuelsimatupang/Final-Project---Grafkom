#include "Application.h"

Application::Application()
{
	angle = 0;

	screenWidth = 1500;
	cameraPos = glm::vec3(-0.1f, 0.2f, 0.5f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	yaw = -90.0f;
	pitch = 0.0f;
	firstMouse = true;
	lastX = 400.0;
	lastY = 300.0;
	sensitivity = 0.1f;

	//inisialisasi properti cahaya
	ambientLight = glm::vec3(0.2f, 0.2f, 0.2f);
	directionalLight.direction = glm::vec3(-0.5f, -1.0f, -0.5f);
	directionalLight.color = glm::vec3(1.0f, 1.0f, 1.0f);
	pointLight.position = glm::vec3(0.0f, 1.0f, 0.0f);
	pointLight.constant = 1.0f;
	pointLight.linear = 0.09f;
	pointLight.quadratic = 0.032f;


	
}

Application::~Application()
{
}

void Application::setupPerspective()
{
	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	shader->setMat4("projection", projection);
}

void Application::setupCamera()
{
	// LookAt camera (position, target/direction, up)
	viewPos = glm::vec3(0, 0, 3);
	glm::mat4 view = glm::lookAt(viewPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	shader->setMat4("view", view);
}

void Application::setupLighting()
{
	// set lighting attributes
	glm::vec3 lightPos = glm::vec3( 4, 4, 0);
	shader->setVec3("lightPos", lightPos);
	shader->setVec3("viewPos", viewPos);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	shader->setVec3("lightColor", lightColor);

	//set ambient cahaya
	shader->setVec3("ambientLight", ambientLight);

	//set arah cahaya
	shader->setVec3("dirLight.direction", directionalLight.direction);
	shader->setVec3("dirLight.color", directionalLight.color);
	
	//set poin cahaya
	shader->setVec3("pointLight.position", pointLight.position);
	shader->setVec3("pointLight.color", pointLight.color);
	shader->setFloat("pointLight.constant", pointLight.constant);
	shader->setFloat("pointLght.linear", pointLight.linear);
	shader->setFloat("pointLight.quadratic", pointLight.quadratic);
}

void Application::Init()
{
	// Build a lighting map shader
	shader = new Shader("cube.vert", "cube.frag");
	shader->Init();
	// Create instance of cube
	cube = new Cube(shader);
	cube->Init();
	cube->SetRotation(0, 0, 1, 0);
	
	// setup perspective 
	setupPerspective();
	// setup camera
	setupCamera();
	// setup lighting
	setupLighting();
}

void Application::DeInit()
{
	delete cube;
}

void Application::Update(double deltaTime)
{
	angle += 0;
		//(float)((deltaTime * 0.5f) / 1000);
	cube->SetRotation(angle, 0, 1, 0);

	glm::vec3 cameraTarget = cameraPos + cameraFront;
	glm::mat4 view = glm::lookAt(cameraPos, cameraTarget, cameraUp);
	shader->setMat4("view", view);
}



void Application::Render()
{
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SetBackgroundColor(94, 232, 247);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);


	//Mesin Arcade
	// Layer 1
	cube->SetPosition(1.25f, -0.65f, -0.20f);
	cube->SetColor(255.0f, 0, 0);
	cube ->SetScale(0.75f, 0.75f, 0.75f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(1.25f, -0.165f, -0.075f);
	cube->SetColor(71.0f, 61.0f, 61.0f);
	cube->SetScale(0.75f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(1.25f, 0.315f, -0.30f);
	cube->SetColor(255.0f, 0, 0);
	cube->SetScale(0.75f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(1.25f, 0.855f, -0.075f);
	cube->SetColor(71.0f, 61.0f, 61.0f);
	cube->SetScale(0.75f, 0.315f, 1.0f);
	cube->Draw();

	
	//Sisi Kiri
	cube->SetPosition(1.625f, 0.025f, -0.20f);
	cube->SetColor(71.0f, 61.0f, 61.0f);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();
	
	//Sisi Kanan
	cube->SetPosition(0.875f, 0.025f, -0.20f);
	cube->SetColor(71.0f, 61.0f, 61.0f);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();
	

	//Layar 
	cube->SetPosition(1.25f, 0.315f, -0.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();

	//JoyStick
	cube->SetPosition(1.025f, 0.0f, 0.25f);
	cube->SetColor(255.0f,255.0f, 255.0f);
	cube->SetScale(0.025f, 0.125f, 0.025f);
	cube->Draw();

	cube->SetPosition(1.025f, 0.040f, 0.25f);
	cube->SetColor(255.0f,0.0f, 0.0f);
	cube->SetScale(0.050f, 0.050f, 0.05f);
	cube->Draw();

	//Mesin Arcade 2
	// Layer 1
	cube->SetPosition(2.25f, -0.65f, -0.20f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.75f, 0.75f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(2.25f, -0.165f, -0.075f);
	cube->SetColor(229, 229, 229);
	cube->SetScale(0.75f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(2.25f, 0.315f, -0.30f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(2.25f, 0.855f, -0.075f);
	cube->SetColor(229, 229, 229);
	cube->SetScale(0.75f, 0.315f, 1.0f);
	cube->Draw();


	//Sisi Kiri
	cube->SetPosition(2.625f, 0.025f, -0.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan
	cube->SetPosition(1.875f, 0.025f, -0.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();


	//Layar 
	cube->SetPosition(2.25f, 0.315f, -0.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();

	//JoyStick
	cube->SetPosition(2.025f, 0.0f, 0.25f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.025f, 0.125f, 0.025f);
	cube->Draw();

	cube->SetPosition(2.025f, 0.040f, 0.25f);
	cube->SetColor(255.0f, 0.0f, 0.0f);
	cube->SetScale(0.050f, 0.050f, 0.05f);
	cube->Draw();

	//Mesin Arcade 3
	// Layer 1
	cube->SetPosition(3.25f, -0.65f, -0.20f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.75f, 0.75f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(3.25f, -0.165f, -0.075f);
	cube->SetColor(229, 229, 229);
	cube->SetScale(0.75f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(3.25f, 0.315f, -0.30f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(3.25f, 0.855f, -0.075f);
	cube->SetColor(229, 229, 229);
	cube->SetScale(0.75f, 0.315f, 1.0f);
	cube->Draw();


	//Sisi Kiri
	cube->SetPosition(3.625f, 0.025f, -0.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan
	cube->SetPosition(2.875f, 0.025f, -0.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();


	//Layar 
	cube->SetPosition(3.25f, 0.315f, -0.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();

	//JoyStick
	cube->SetPosition(3.025f, 0.0f, 0.25f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.025f, 0.125f, 0.025f);
	cube->Draw();

	cube->SetPosition(3.025f, 0.040f, 0.25f);
	cube->SetColor(255.0f, 0.0f, 0.0f);
	cube->SetScale(0.050f, 0.050f, 0.05f);
	cube->Draw();

	//Mesin Arcade 4
	// Layer 1
	cube->SetPosition(3.25f, -0.65f, 4.20f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.75f, 0.75f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(3.25f, -0.165f, 4.075f);
	cube->SetColor(229, 229, 229);
	cube->SetScale(0.75f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(3.25f, 0.315f, 4.30f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(3.25f, 0.855f, 4.075f);
	cube->SetColor(229, 229, 229);
	cube->SetScale(0.75f, 0.315f, 1.0f);
	cube->Draw();


	//Sisi Kiri
	cube->SetPosition(3.625f, 0.025f, 4.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan
	cube->SetPosition(2.875f, 0.025f, 4.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();


	//Layar 
	cube->SetPosition(3.25f, 0.315f, 4.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();

	//JoyStick
	cube->SetPosition(3.025f, 0.0f, 3.80f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.025f, 0.125f, 0.025f);
	cube->Draw();

	cube->SetPosition(3.025f, 0.040f, 3.80f);
	cube->SetColor(255.0f, 0.0f, 0.0f);
	cube->SetScale(0.050f, 0.050f, 0.05f);
	cube->Draw();

	//Mesin Arcade 5
	// Layer 1
	cube->SetPosition(2.25f, -0.65f, 4.20f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.75f, 0.75f, 0.75f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(2.25f, -0.165f, 4.075f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.75f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(2.25f, 0.315f, 4.30f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.75f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(2.25f, 0.855f, 4.075f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.75f, 0.315f, 1.0f);
	cube->Draw();


	//Sisi Kiri
	cube->SetPosition(2.625f, 0.025f, 4.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan
	cube->SetPosition(1.875f, 0.025f, 4.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();


	//Layar 
	cube->SetPosition(2.25f, 0.315f, 4.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();

	//JoyStick
	cube->SetPosition(2.025f, 0.0f, 3.80f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.025f, 0.125f, 0.025f);
	cube->Draw();

	cube->SetPosition(2.025f, 0.040f, 3.80f);
	cube->SetColor(255.0f, 0.0f, 0.0f);
	cube->SetScale(0.050f, 0.050f, 0.05f);
	cube->Draw();

	//Mesin Arcade 6
	// Layer 1
	cube->SetPosition(1.25f, -0.65f, 4.20f);
	cube->SetColor(0, 202, 4);
	cube->SetScale(0.75f, 0.75f, 0.75f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(1.25f, -0.165f, 4.075f);
	cube->SetColor(0, 2025, 4);
	cube->SetScale(0.75f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(1.25f, 0.315f, 4.30f);
	cube->SetColor(0, 202, 4);
	cube->SetScale(0.75f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(1.25f, 0.855f, 4.075f);
	cube->SetColor(0, 225, 4);
	cube->SetScale(0.75f, 0.315f, 1.0f);
	cube->Draw();


	//Sisi Kiri
	cube->SetPosition(1.625f, 0.025f, 4.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan
	cube->SetPosition(0.875f, 0.025f, 4.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();


	//Layar 
	cube->SetPosition(1.25f, 0.315f, 4.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();

	//JoyStick
	cube->SetPosition(1.025f, 0.0f, 3.80f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.025f, 0.125f, 0.025f);
	cube->Draw();

	cube->SetPosition(1.025f, 0.040f, 3.80f);
	cube->SetColor(255.0f, 0.0f, 0.0f);
	cube->SetScale(0.050f, 0.050f, 0.05f);
	cube->Draw();


	//Mesin Pump it
	// Layer 1
	cube->SetPosition(2.25f, -0.65f, 8.20f);
	cube->SetColor(134, 93, 255);
	cube->SetScale(1.25f, 0.75f, 0.75f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(2.25f, -0.165f, 8.075f);
	cube->SetColor(0, 9, 44);
	cube->SetScale(1.25f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(2.25f, 0.315f, 8.30f);
	cube->SetColor(134, 93, 255);
	cube->SetScale(1.25f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(2.25f, 0.855f, 8.25f);
	cube->SetColor(0, 9, 44);
	cube->SetScale(1.75f, 0.315f, 0.750f);
	cube->Draw();


	//Sisi Kiri
	cube->SetPosition(2.625f, 0.025f, 8.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan
	cube->SetPosition(1.875f, 0.025f, 8.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();


	//Layar 
	cube->SetPosition(2.25f, 0.315f, 8.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();

	//Pump it 

	cube->SetPosition(2.25f, -1.0f, 6.80f);
	cube->SetColor(0, 9, 44);
	cube->SetScale(2.0f, 0.15f, 2.25f);
	cube->Draw();
	
	//Tombol 1
	cube->SetPosition(2.25f, -0.9f, 6.70f);
	cube->SetColor(148, 0, 255);
	cube->SetScale(0.45f, 0.025f, 0.45f);
	cube->Draw();

	//Tombol 2
	cube->SetPosition(2.75f, -0.9f, 6.20f);
	cube->SetColor(22, 225, 0);
	cube->SetScale(0.45f, 0.025f, 0.45f);
	cube->Draw();

	//Tombol 3
	cube->SetPosition(1.75f, -0.9f, 6.20f);
	cube->SetColor(22, 225, 0);
	cube->SetScale(0.45f, 0.025f, 0.45f);
	cube->Draw();

	//Tombol 4
	cube->SetPosition(2.75f, -0.9f, 7.20f);
	cube->SetColor(255, 0, 0);
	cube->SetScale(0.45f, 0.025f, 0.45f);
	cube->Draw();

	//Tombol 5
	cube->SetPosition(1.75f, -0.9f, 7.20f);
	cube->SetColor(255, 0, 0);
	cube->SetScale(0.45f, 0.025f, 0.45f);
	cube->Draw();

	//tiang
	cube->SetPosition(1.75f, -0.9f, 7.20f);
	cube->SetColor(255, 0, 0);
	cube->SetScale(0.45f, 0.025f, 0.45f);
	cube->Draw();

	//Mesin Pemukul
	
	// Layer 1
	cube->SetPosition(-1.25f, -0.65f, 7.50f);
	cube->SetColor(134, 93, 255);
	cube->SetScale(1.25f, 0.75f, 2.5f);
	cube->Draw();

	//Layer 2
	cube->SetPosition(-1.25f, -0.165f, 8.075f);
	cube->SetColor(0, 9, 44);
	cube->SetScale(1.25f, 0.215f, 1.0f);
	cube->Draw();

	//Layer 3
	cube->SetPosition(-1.25f, 0.315f, 8.30f);
	cube->SetColor(134, 93, 255);
	cube->SetScale(1.25f, 0.75f, 0.55f);
	cube->Draw();

	//Layer 4
	cube->SetPosition(-1.25f, 0.855f, 8.25f);
	cube->SetColor(0, 9, 44);
	cube->SetScale(1.75f, 0.315f, 0.750f);
	cube->Draw();


	//Sisi Kiri
	cube->SetPosition(-1.625f, 0.025f, 8.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kiri2
	cube->SetPosition(-1.875f, 0.025f, 8.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan
	cube->SetPosition(-0.625f, 0.025f, 8.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();

	//Sisi Kanan2
	cube->SetPosition(-0.875f, 0.025f, 8.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.015f, 2.10f, 0.75f);
	cube->Draw();


	//Layar 
	cube->SetPosition(-1.25f, 0.315f, 8.025f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.70f, 0.65f, 0.009f);
	cube->Draw();
	
	//Lubang
	cube->SetPosition(-0.85f, -0.25f, 7.25f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-1.25f, -0.25f, 7.25f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-1.65f, -0.25f, 7.25f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-0.85f, -0.25f, 6.95f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-1.25f, -0.25f, 6.95f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-1.65f, -0.25f, 6.95f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-0.85f, -0.25f, 6.65f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-1.25f, -0.25f, 6.65f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	cube->SetPosition(-1.65f, -0.25f, 6.65f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.25f, 0.015f, 0.25f);
	cube->Draw();

	//Vending Machine
	cube->SetPosition(-0.25f, -0.15f, -0.20f);
	cube->SetColor(255.0f, 255.0f, 0);
	cube->SetScale(1.25f, 1.75f, 0.5f);
	cube->Draw();

	//Bagian bawah
	cube->SetPosition(-0.45f, -0.75f, 0.050f);
	cube->SetColor(110, 107, 86);
	cube->SetScale(0.55f, 0.25f, 0.01f);
	cube->Draw();

	//Tempat minuman
	cube->SetPosition(-0.45f, 0.15f, 0.050f);
	cube->SetColor(232, 233, 235);
	cube->SetScale(0.75f, 1.0f, 0.01f);
	cube->Draw();

	//Tempat coin
	cube->SetPosition(0.15f, 0.15f, 0.050f);
	cube->SetColor(110, 107, 86);
	cube->SetScale(0.25f, 0.40f, 0.01f);
	cube->Draw();


	//Crane Machine

	//Layer 1
	cube->SetPosition(-1.75f, -0.65f, -0.25f);
	cube->SetColor(50, 168, 82);
	cube->SetScale(0.85f, 0.75f, 0.65f);
	cube->Draw();

	cube->SetPosition(-1.75f, -0.35f, 0.15f);
	cube->SetColor(50, 168, 82);
	cube->SetScale(0.85f, 0.15f, 0.25f);
	cube->Draw();

	//Tiang
	cube->SetPosition(-1.35f, 0.1f, 0.05f);
	cube->SetColor(255, 255, 255);
	cube->SetScale(0.02f, 1.75f, 0.02f);
	cube->Draw();

	cube->SetPosition(-1.35f, 0.1f, -0.55f);
	cube->SetColor(255, 255, 255);
	cube->SetScale(0.02f, 1.75f, 0.02f);
	cube->Draw();

	cube->SetPosition(-2.15f, 0.1f, 0.05f);
	cube->SetColor(255, 255, 255);
	cube->SetScale(0.02f, 1.75f, 0.02f);
	cube->Draw();

	cube->SetPosition(-2.15f, 0.1f, -0.55f);
	cube->SetColor(255, 255, 255);
	cube->SetScale(0.02f, 1.75f, 0.02f);
	cube->Draw();

	//Layer Atas
	cube->SetPosition(-1.75f, 0.955f, -0.25f);
	cube->SetColor(50, 168, 82);
	cube->SetScale(0.85f, 0.25f, 0.65f);
	cube->Draw();

	//Crane
	cube->SetPosition(-1.75f, 0.65f, -0.25f);
	cube->SetColor(255.0f, 255.0f, 255.0f);
	cube->SetScale(0.03f, 0.3f, 0.03f);
	cube->Draw();

	cube->SetPosition(-1.75f, 0.50f, -0.25f);
	cube->SetColor(255.0f, 255.0f, 255.0f);
	cube->SetScale(0.15f, 0.03f, 0.03f);
	cube->Draw();

	cube->SetPosition(-1.68f, 0.45f, -0.25f);
	cube->SetColor(255.0f, 255.0f, 255.0f);
	cube->SetScale(0.03f, 0.15f, 0.03f);
	cube->Draw();

	cube->SetPosition(-1.825f, 0.45f, -0.25f);
	cube->SetColor(255.0f, 255.0f, 255.0f);
	cube->SetScale(0.03f, 0.15f, 0.03f);
	cube->Draw();

	//Joy Stick
	cube->SetPosition(-1.825f, -0.21f, 0.15f);
	cube->SetColor(255.0f, 255.0f, 255.0f);
	cube->SetScale(0.025f, 0.125f, 0.025f);
	cube->Draw();

	cube->SetPosition(-1.825f, -0.15f, 0.15f);
	cube->SetColor(50, 168, 82);
	cube->SetScale(0.050f, 0.050f, 0.05f);
	cube->Draw();

	//Tombol
	cube->SetPosition(-1.625f, -0.275f, 0.15f);
	cube->SetColor(255.0f, 255.0f, 255.0f);
	cube->SetScale(0.070f, 0.020f, 0.070f);
	cube->Draw();

	//Pengambilan Hadiah
	cube->SetPosition(-1.55f, -0.65f, 0.075f);
	cube->SetColor(31, 99, 49);
	cube->SetScale(0.25f, 0.35f, 0.01f);
	cube->Draw();


	// Kursi

	cube->SetPosition(1.25f, -0.85f, 1.20f);
	cube->SetColor(255.0f, 0, 0);
	cube->SetScale(0.75f, 0.55f, 0.75f);
	cube->Draw();

	cube->SetPosition(1.25f, -0.55f, 1.20f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.79f, 0.15f, 0.85f);
	cube->Draw();

	// Kursi 2

	cube->SetPosition(2.25f, -0.85f, 1.20f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.55f, 0.75f);
	cube->Draw();

	cube->SetPosition(2.25f, -0.55f, 1.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.79f, 0.15f, 0.85f);
	cube->Draw();

	// Kursi 3

	cube->SetPosition(3.25f, -0.85f, 1.20f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.55f, 0.75f);
	cube->Draw();

	cube->SetPosition(3.25f, -0.55f, 1.20f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.79f, 0.15f, 0.85f);
	cube->Draw();

	// Kursi 4

	cube->SetPosition(1.25f, -0.85f, 3.0f);
	cube->SetColor(255.0f, 0, 0);
	cube->SetScale(0.75f, 0.55f, 0.75f);
	cube->Draw();

	cube->SetPosition(1.25f, -0.55f, 3.0f);
	cube->SetColor(0, 0, 0);
	cube->SetScale(0.79f, 0.15f, 0.85f);
	cube->Draw();

	// Kursi 5

	cube->SetPosition(2.25f, -0.85f, 3.0f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.55f, 0.75f);
	cube->Draw();

	cube->SetPosition(2.25f, -0.55f, 3.0f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.79f, 0.15f, 0.85f);
	cube->Draw();


	// Kursi 6

	cube->SetPosition(3.25f, -0.85f, 3.0f);
	cube->SetColor(247, 128, 0);
	cube->SetScale(0.75f, 0.55f, 0.75f);
	cube->Draw();

	cube->SetPosition(3.25f, -0.55f, 3.0f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.79f, 0.15f, 0.85f);
	cube->Draw();


	//Meja
	//Bagian depan
	cube->SetPosition(-3.0f, -0.55f, 4.0f);
	cube->SetColor(255, 95, 0);
	cube->SetScale(0.120f,  1.0f, 3.0f);
	cube->Draw();

	//Sisi kiri
	cube->SetPosition(-3.5f, -0.55f, 5.5f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(1.10f, 1.0f, 0.025f);
	cube->Draw();

	//Sisi kanan
	cube->SetPosition(-3.5f, -0.55f, 2.5f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(1.10f, 1.0f, 0.025f);
	cube->Draw();

	//Sisi atas
	cube->SetPosition(-3.25f, -0.05f, 4.0f);
	cube->SetColor(238, 238, 238);
	cube->SetScale(1.15f, 0.025f, 3.0f);
	cube->Draw();

	//Pembatas kiri
	cube->SetPosition(-3.2f, -0.55f, 0.5f);
	cube->SetColor(238, 238, 238);
	cube->SetScale(0.120f, 1.0f, 4.0f);
	cube->Draw();

	//Aksen kiri
	cube->SetPosition(-3.14f, -0.85f, 0.5f);
	cube->SetColor(255, 95, 0);
	cube->SetScale(0.01f, 0.075f, 4.0f);
	cube->Draw();

	cube->SetPosition(-3.14f, -0.75f, 0.5f);
	cube->SetColor(255, 95, 0);
	cube->SetScale(0.01f, 0.015f, 4.0f);
	cube->Draw();

	cube->SetPosition(-3.14f, -0.25f, 0.5f);
	cube->SetColor(20, 33, 61);;
	cube->SetScale(0.01f, 0.075f, 4.0f);
	cube->Draw();

	//Pembatas kanan
	cube->SetPosition(-3.2f, -0.55f, 6.5f);
	cube->SetColor(238, 238, 238);
	cube->SetScale(0.120f, 1.0f, 2.3f);
	cube->Draw();

	

	//Aksen kanan
	cube->SetPosition(-3.14f, -0.85f, 6.5f);
	cube->SetColor(255, 95, 0);
	cube->SetScale(0.01f, 0.075f, 2.3f);
	cube->Draw();

	cube->SetPosition(-3.14f, -0.75f, 6.5f);
	cube->SetColor(255, 95, 0);
	cube->SetScale(0.01f, 0.015f, 2.3f);
	cube->Draw();

	cube->SetPosition(-3.14f, -0.25f, 6.5f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(0.01f, 0.075f, 2.3f);
	cube->Draw();

	//Sisi kanan
	cube->SetPosition(-3.75f, -0.55f, 7.5f);
	cube->SetColor(20, 33, 61);
	cube->SetScale(1.10f, 1.0f, 0.025f);
	cube->Draw();


	//Poster 1
	cube->SetPosition(-4.95f, 2.25f, 4.0f);
	cube->SetColor(255, 255, 255);
	cube->SetScale(0.05f, 2.0f, 1.0f);
	cube->Draw();

	cube->SetPosition(-4.93f, 2.25f, 4.0f);
	cube->SetColor(5, 199, 247);
	cube->SetScale(0.05f, 1.85f, 0.85f);
	cube->Draw();

	cube->SetPosition(-4.90f, 2.6f, 4.1f);
	cube->SetColor(255, 0, 0);
	cube->SetScale(0.01f, 0.30f, 0.15f);
	cube->Draw();


	cube->SetPosition(-4.90f, 2.6f, 3.9f);
	cube->SetColor(255,0,0);
	cube->SetScale(0.01f, 0.30f, 0.09f);
	cube->Draw();

	cube->SetPosition(-4.90f, 2.5f, 4.0f);
	cube->SetColor(255, 0, 0);
	cube->SetScale(0.01f, 0.05f, 0.30f);
	cube->Draw();

	cube->SetPosition(-4.90f, 2.3f, 4.0f);
	cube->SetColor(32, 122, 7);
	cube->SetScale(0.01f, 0.45f, 0.025f);
	cube->Draw();

	cube->SetPosition(-4.90f, 2.2f, 4.0f);
	cube->SetColor(32, 122, 7);
	cube->SetScale(0.01f, 0.25f, 0.45f);
	cube->Draw();

	cube->SetPosition(-4.90f, 2.05f, 4.0f);
	cube->SetColor(32, 122, 7);
	cube->SetScale(0.01f, 0.55f, 0.35f);
	cube->Draw();


	cube->SetPosition(-4.90f, 1.52f, 4.0f);
	cube->SetColor(186, 104, 45);
	cube->SetScale(0.01f, 0.5f, 0.85f);
	cube->Draw();
	
	



	//Lantai
	cube->SetPosition(0.0f, -1.25f, 4.0f);
	cube->SetColor(82, 109, 130);
	cube->SetScale(18.0f, 0.50f, 10.0f);
	cube->Draw();

	//DindingA
	cube->SetPosition(0.0f, 2.25f, -1.0f);
	cube->SetColor(23, 107, 135);
	cube->SetScale(15.0f, 8.0f, 0.05f);
	cube->Draw();

	//DindingB
	cube->SetPosition(0.0f, 2.25f, 9.0f);
	cube->SetColor(23, 107, 135);
	cube->SetScale(15.0f, 8.0f, 0.05f);
	cube->Draw();

	//DindingC
	cube->SetPosition(-5.0f, 2.25f, 4.0f);
	cube->SetColor(23, 107, 135);
	cube->SetScale(0.05f, 8.0f, 10.05f);
	cube->Draw();

	//Atap

	cube->SetPosition(0.0f, 5.0f, 4.0f);
	
	cube->SetColor(194, 217, 255);
	cube->SetScale(15.0f, 0.01f, 10.0f);
	cube->Draw();

	//Lampu1
	cube->SetPosition(0.0f, 4.9f, 4.0f);

	cube->SetColor(194, 217, 255);
	cube->SetScale(1.5f, 0.04f, 1.0f);
	cube->Draw();


	glDisable(GL_DEPTH_TEST);

}

void Application::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	const float cameraSpeed = 0.03f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	// Handle camera rotation using mouse input
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// Clamp pitch to prevent flipping
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	// Update camera front direction
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	//update posisi poin cahaya
	float radius = 2.0f;
	float lightX = sin(glfwGetTime()) * radius;
	float lightZ = cos(glfwGetTime()) * radius;
	pointLight.position = glm::vec3(lightX, 1.0f, lightZ);

}


int main(int argc, char** argv) {
	Application app = Application();
	app.Start("Cube Example", 
		1366, 768, 
		false, 
		false);
}