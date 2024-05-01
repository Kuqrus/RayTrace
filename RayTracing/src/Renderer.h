#pragma once

#include "Walnut/Image.h"
#include "Walnut/Random.h"
#include "Camera.h"
#include "Ray.h"
#include "Scene.h"

#include <memory>
#include <glm/glm.hpp>

class Renderer {
public:
	struct Settings
	{
		bool Accumulate = true;
		bool SlowRender = true;
		bool UseEmission = false;
	};
public:
	Renderer() = default;

	void OnResize(uint32_t w, uint32_t h);
	void Render(const Scene& scene, const Camera& camera);

	std::shared_ptr<Walnut::Image> GetFinalImage()const { return m_FinalImage; };

	glm::vec3 lightDir{ -1.0f, -1.0f, -1.0f };

	void ResetFrameIndex() { m_FrameIndex = 1; }
	Settings& GetSettings() { return m_Settings; }

private:
	struct HitPayload
	{
		float HitDistance;
		glm::vec3 WorldPosition;
		glm::vec3 WorldNormal;
		int ObjectIndex;
	};

	HitPayload TraceRay(const Ray& ray);
	glm::vec4 PerPixel(uint32_t x, uint32_t y);
	glm::vec4 PerPixel_(uint32_t x, uint32_t y);
	HitPayload ClosesHit(const Ray& ray, float hitDistance, int objectIndex);
	HitPayload Miss(const Ray& ray);

private:
	const Scene* m_ActiveScene = nullptr;
	const Camera* m_ActiveCamera = nullptr;
	std::shared_ptr<Walnut::Image> m_FinalImage;

	std::vector<uint32_t> m_ImageHorizontalIter, m_ImageVecticalIter;

	Settings m_Settings;

	uint32_t* m_ImageData = nullptr;
	glm::vec4* m_AccumulationData = nullptr;
	
	uint32_t m_FrameIndex = 1;
};
