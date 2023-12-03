#pragma once

#include "RenderEngine.h"
#include "Cube.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


struct DirectionalLight {
	//arah cahaya
	glm::vec3 direction;
	glm::vec3 color;
};

struct PointLight {//Point Cahaya
	glm::vec3 position;
	glm::vec3 color;
	float constant;
	float linear;
	float quadratic;
};

class Application :
    public RenderEngine
{
public:
    Application();
    ~Application();
private:
	Shader *shader;
	Cube* cube; 
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	float angle;
	float yaw;
	float pitch;
	bool firstMouse;
	double lastX;
	double lastY;
	float sensitivity;

	glm::vec3 viewPos;

	
	
	

	//Properti cahaya
	glm::vec3 ambientLight;
	DirectionalLight directionalLight;
	PointLight pointLight;

	void setupPerspective();
	void setupCamera();
	void setupLighting(); 
	virtual void Init();
	virtual void DeInit(); 
	virtual void Update(double deltaTime);
	virtual void Render();
	virtual void ProcessInput(GLFWwindow* window);
	

	GLuint depthMapFBO;
	GLuint depthMap;
	glm::mat4 lightSpaceMatrix;
	Shader* shadowShader;

	void setupShadowMap();
	void renderShadowMap();
	void renderSceneFromLight(const Shader& shader);
};

