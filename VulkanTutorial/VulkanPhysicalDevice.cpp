#include "VulkanPhysicalDevice.h"

VulkanPhysicalDevice::~VulkanPhysicalDevice()
{
}

VkPhysicalDevice& VulkanPhysicalDevice::getPhysicalDevice()
{
	return this->theDevice;
}

QueueFamilyIndices& VulkanPhysicalDevice::getQueueFamilyIndices()
{
	return this->theQueueFamIndices;
}

VkPhysicalDeviceProperties& VulkanPhysicalDevice::getPhysicalDeviceProps()
{
	return this->thePhysDevProps;
}

VkPhysicalDeviceFeatures& VulkanPhysicalDevice::getPhysicalDeviceFeatures()
{
	return this->thePhysDevFeatures;
}

VkPhysicalDeviceMemoryProperties& VulkanPhysicalDevice::getPhysicalMemProps()
{
	return this->thePhysDevMemoryProps;
}

VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanInstance* instance, VkPhysicalDevice device, QueueFamilyIndices indices)
{

	this->thePhysDevFeatures = {};
	this->thePhysDevMemoryProps = {};
	this->thePhysDevProps = {};

	theInstance = instance;
	theDevice = device;
	theQueueFamIndices = indices;

	vkGetPhysicalDeviceProperties(
		theDevice,
		&thePhysDevProps
	);

	vkGetPhysicalDeviceFeatures(
		theDevice,
		&thePhysDevFeatures
	);

	vkGetPhysicalDeviceMemoryProperties(
		theDevice,
		&thePhysDevMemoryProps
	);
}
VulkanPhysicalDevice* VulkanPhysicalDevice::GetPhysicalDevice(VulkanInstance* instance)
{
	std::vector<VkPhysicalDevice> devices = GetAvaliablePhysicalDevices(instance);

	VkPhysicalDevice secondDevice = VK_NULL_HANDLE;
	QueueFamilyIndices secondQueue;

	for (auto& device : devices)
	{
		QueueFamilyIndices queueFamily;
		if (PhysicalDeviceSupported(instance, device, queueFamily))
		{
			VkPhysicalDeviceProperties physDeviceProps;
			vkGetPhysicalDeviceProperties(
				device,
				&physDeviceProps
			);

			if (physDeviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				return new VulkanPhysicalDevice(instance,device,queueFamily);
			}
			else
			{
				secondDevice = device;
				secondQueue = queueFamily;
			}
		}
	}

	if (secondDevice == VK_NULL_HANDLE) return nullptr;


	return new VulkanPhysicalDevice(instance, secondDevice, secondQueue);
}

std::vector<VkPhysicalDevice> VulkanPhysicalDevice::GetAvaliablePhysicalDevices(VulkanInstance* instance)
{
	uint32_t deviceCount = 0;

	vkEnumeratePhysicalDevices(
		instance->getInstance(),
		&deviceCount,
		nullptr
	);

	std::vector<VkPhysicalDevice> devices(deviceCount);

	vkEnumeratePhysicalDevices(
		instance->getInstance(),
		&deviceCount,
		devices.data()
	);

	return devices;
}

bool VulkanPhysicalDevice::PhysicalDeviceSupported(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& familyIndices)
{
	bool supportQFam = supportsQueueFamily(instance, device, familyIndices);

	return supportQFam;
}

bool VulkanPhysicalDevice::supportsQueueFamily(VulkanInstance* instance, VkPhysicalDevice& device, QueueFamilyIndices& familyIndices)
{
	uint32_t queueFamCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(
		device,
		&queueFamCount,
		nullptr
	);

	std::vector<VkQueueFamilyProperties> queueFamProps(queueFamCount);

	vkGetPhysicalDeviceQueueFamilyProperties(
		device,
		&queueFamCount,
		queueFamProps.data()
	);
	uint32_t i = 0;
	for (auto& queueFam:queueFamProps)
	{
		if (queueFam.queueCount > 0)
		{
			if (queueFam.queueFlags & VK_QUEUE_GRAPHICS_BIT)
				familyIndices.graphicsIndices = i;
			if (queueFam.queueFlags & VK_QUEUE_COMPUTE_BIT)
				familyIndices.computeIndices = i;
		}
		if (familyIndices.graphicsIndices < UINT32_MAX && familyIndices.computeIndices < UINT32_MAX)
		{
			return true;
		}

		i++;
	}

	return false;
}
