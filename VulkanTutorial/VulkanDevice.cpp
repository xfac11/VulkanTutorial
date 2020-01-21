#include "VulkanDevice.h"

VulkanDevice::VulkanDevice(VulkanInstance* instance, VulkanPhysicalDevice* physicalDevice)
{
	computeQueue = {};
	this->instance = instance;
	this->physicalDevice = physicalDevice;

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	float priority = 1.0f;
	queueCreateInfos.push_back(Initializers::deviceQueueCreate(physicalDevice->getQueueFamilyIndices().computeIndices, priority));

	VkDeviceCreateInfo createInfo = Initializers::deviceCreateInfo(queueCreateInfos, physicalDevice->getPhysicalDeviceFeatures());

	ErrorCheck(vkCreateDevice(
		physicalDevice->getPhysicalDevice(),
		&createInfo,
		nullptr,
		&device
	));

	vkGetDeviceQueue(
		device,
		physicalDevice->getQueueFamilyIndices().computeIndices,
		0,
		&computeQueue
	);

	VkCommandPoolCreateInfo computePoolInfo = Initializers::commandPoolCreateInfo(physicalDevice->getQueueFamilyIndices().computeIndices);

	ErrorCheck(vkCreateCommandPool(
		this->device,
		&computePoolInfo,
		nullptr,
		&theComputeComPool
	));
}

VulkanInstance* VulkanDevice::getInstance()
{
	return this->instance;
}

VkDevice* VulkanDevice::getDevice()
{
	return &this->device;
}

VkQueue* VulkanDevice::getComputeQueue()
{
	return &this->computeQueue;
}

VkCommandPool VulkanDevice::getComputeComPool()
{
	return this->theComputeComPool;
}

void VulkanDevice::getComputeCommand(VkCommandBuffer* buffers, uint32_t count)
{
	VkCommandBufferAllocateInfo commandBufferAllInfo = Initializers::commandBufferAllocateInfo(theComputeComPool, count);

	ErrorCheck(vkAllocateCommandBuffers(
		this->device,
		&commandBufferAllInfo,
		buffers
	));
}

void VulkanDevice::freeComputeCommand(VkCommandBuffer* buffers, uint32_t count)
{
	vkFreeCommandBuffers(
		this->device,
		theComputeComPool,
		count,
		buffers
	);

}

VulkanDevice::~VulkanDevice()
{
	vkDestroyCommandPool(
		this->device,
		this->theComputeComPool,
		nullptr
	);

	vkDestroyDevice(
		this->device,
		nullptr
	);
}
