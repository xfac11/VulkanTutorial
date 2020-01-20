#pragma once

#include"BUILD_ORDER.h"
#include"VulkanInstance.h"
#include"QueueFamilyIndices.h"
class VulkanPhysicalDevice
{
public:
	~VulkanPhysicalDevice();
	VkPhysicalDevice& getPhysicalDevice();
	QueueFamilyIndices& getQueueFamilyIndices();
	VkPhysicalDeviceProperties& getPhysicalDeviceProps();
	VkPhysicalDeviceFeatures& getPhysicalDeviceFeatures();
	VkPhysicalDeviceMemoryProperties& getPhysicalMemProps();
	static VulkanPhysicalDevice* GetPhysicalDevice(VulkanInstance* instance);
private:
	VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices);
	static std::vector<VkPhysicalDevice> GetAvaliablePhysicalDevices(VulkanInstance* instance);
	static bool PhysicalDeviceSupported(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& familyIndices);
	static bool supportsQueueFamily(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& familyIndices);
	VulkanInstance* theInstance;
	VkPhysicalDevice theDevice;
	QueueFamilyIndices theQueueFamIndices;
	VkPhysicalDeviceProperties thePhysDevProps;
	VkPhysicalDeviceFeatures thePhysDevFeatures;
	VkPhysicalDeviceMemoryProperties thePhysDevMemoryProps;
};
