#pragma once

#include"BUILD_ORDER.h"
#include"VulkanPhysicalDevice.h"
class VulkanDevice
{
public:
	VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physicalDevice);
	VulkanInstance* getInstance();
	VkDevice* getDevice();
	VkQueue* getComputeQueue();
	VkCommandPool getComputeComPool();

	void getComputeCommand(VkCommandBuffer* buffers, uint32_t count);
	void freeComputeCommand(VkCommandBuffer* buffers, uint32_t count);
	~VulkanDevice();
private:
	VulkanInstance* instance;
	VkDevice device;
	VulkanPhysicalDevice* physicalDevice;
	VkQueue computeQueue;
	VkCommandPool theComputeComPool;
};
