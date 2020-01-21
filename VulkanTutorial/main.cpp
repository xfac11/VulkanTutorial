#include"BUILD_ORDER.h"
#include"VulkanDevice.h"
VulkanInstance* instance = nullptr;
VulkanPhysicalDevice* physicalDevice = nullptr;
VulkanDevice* device;
int main()
{
	VulkanConfiguration vulkanConfig;
	vulkanConfig.application_name = "My Vulkan App";
	vulkanConfig.application_version = VK_MAKE_VERSION(1, 0, 0);

	instance = new VulkanInstance(vulkanConfig);
	physicalDevice = VulkanPhysicalDevice::GetPhysicalDevice(instance);
	device = new VulkanDevice(instance, physicalDevice);

	VkCommandBuffer* commands = new VkCommandBuffer[3];
	device->getComputeCommand(commands, 3);

	device->freeComputeCommand(commands, 3);

	delete device;
	delete physicalDevice;
	delete instance;

	system("pause");
	return 0;
}