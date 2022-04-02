#include "testlayer.h"
#include <core/log.h>
#include <core/input.h>
#include <core/application.h>
#include <rendering/renderer.h>

static renderer::PosColorVertex cubeVertices[] =
{
    {-1.0f,  1.0f,  1.0f, 0xff000000 },
    { 1.0f,  1.0f,  1.0f, 0xff0000ff },
    {-1.0f, -1.0f,  1.0f, 0xff00ff00 },
    { 1.0f, -1.0f,  1.0f, 0xff00ffff },
    {-1.0f,  1.0f, -1.0f, 0xffff0000 },
    { 1.0f,  1.0f, -1.0f, 0xffff00ff },
    {-1.0f, -1.0f, -1.0f, 0xffffff00 },
    { 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
    0, 1, 2,
    1, 3, 2,
    4, 6, 5,
    5, 6, 7,
    0, 2, 4,
    4, 2, 6,
    1, 5, 3,
    5, 7, 3,
    0, 4, 1,
    4, 5, 1,
    2, 3, 6,
    6, 3, 7,
};

void TestLayer::update(f32 deltaTime) {
    if(Input::isKeyPressed(Escape)) {
        Application::get().close();
    }

	if(Input::isKeyPressed(D)) {
		position.x += 10.0f * deltaTime;
	}

	if(Input::isKeyPressed(A)) {
		position.x -= 10.0f * deltaTime;
		Application::get().removeLayer("name");
	}

	if(Input::isKeyPressed(W)) {
		position.z += 10.0f * deltaTime;
	}

	if(Input::isKeyPressed(S)) {
		position.z -= 10.0f * deltaTime;
	}

	const bx::Vec3 at = position;
	const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};

	float view[16];
	bx::mtxLookAt(view, eye, at);
	bx::mtxTranslate(view, -position.x, -position.y+sin(rotation), -position.z+5.0f);
	float proj[16];
	bx::mtxProj(proj, 60.0f, (float)Application::get().getWindow().width/(float)Application::get().getWindow().height, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(0, view, proj);
	float mtx[16];
	bx::mtxRotateXYZ(mtx, rotation, rotation, rotation);
	bgfx::setTransform(mtx);

	renderer::renderModel(model);

	rotation += 1.0f * deltaTime;
}

void TestLayer::start() {
	model = renderer::loadModel(cubeVertices, sizeof(cubeVertices), cubeTriList, sizeof(cubeTriList));

	vsh = renderer::loadShader("../overture/res/shaders/", "vs_cubes.bin");
	fsh = renderer::loadShader("../overture/res/shaders/", "fs_cubes.bin");

	model.program = bgfx::createProgram(vsh, fsh, true);

    DEBUG("it works");
}

void TestLayer::end() {
		renderer::destroy(model);
}
