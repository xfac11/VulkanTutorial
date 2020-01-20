#pragma once

#include"BUILD_ORDER.h"
#include"VulkanConfiguration.h"
#include"Initializers.h"
#include"Validation.h"
class VulkanInstance
{
public:
	VulkanInstance(VulkanConfiguration& vulkanConfig);
	~VulkanInstance();
	VkInstance& getInstance();

private:
	VkInstance instance;

	std::vector<const char*> layers;
	std::vector<const char*> extensions;
};