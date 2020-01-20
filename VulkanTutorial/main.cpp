#include"BUILD_ORDER.h"
#include"VulkanPhysicalDevice.h"
VulkanInstance* instance = nullptr;
VulkanPhysicalDevice* physicalDevice = nullptr;
int main()
{
	VulkanConfiguration vulkanConfig;
	vulkanConfig.application_name = "My Vulkan App";
	vulkanConfig.application_version = VK_MAKE_VERSION(1, 0, 0);

	instance = new VulkanInstance(vulkanConfig);
	physicalDevice = VulkanPhysicalDevice::GetPhysicalDevice(instance);

	delete physicalDevice;
	delete instance;

	system("pause");
	return 0;
}