#pragma once
#include"BUILD_ORDER.h"
#include<vulkan/vulkan.h>
#include"VulkanConfiguration.h"
namespace Initializers
{
	VkApplicationInfo ApplicationInfo(VulkanConfiguration& config);

	VkInstanceCreateInfo InstanceCreateInfo(VkApplicationInfo& app_info, std::vector<const char*>& layers, std::vector<const char*>& extensions);

	VkDeviceQueueCreateInfo deviceQueueCreate(uint32_t queueFamIndex, float &priority);

	VkDeviceCreateInfo deviceCreateInfo(std::vector<VkDeviceQueueCreateInfo>& queueCreateInfos, VkPhysicalDeviceFeatures& deviceFeatures);

	VkCommandPoolCreateInfo commandPoolCreateInfo(uint32_t queueFamIndex, VkCommandPoolCreateFlags flags = 0);

	VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool pool, uint32_t count);
}