#include "VulkanInstance.h"

VulkanInstance::VulkanInstance(VulkanConfiguration& vulkanConfig)
{
	VkApplicationInfo applicationInfo = Initializers::ApplicationInfo(vulkanConfig);

	VkInstanceCreateInfo instanceInfo = Initializers::InstanceCreateInfo(applicationInfo, layers, extensions);

	ErrorCheck(vkCreateInstance(&instanceInfo, NULL, &instance));

}

VulkanInstance::~VulkanInstance()
{
	vkDestroyInstance(instance, NULL);
}

VkInstance& VulkanInstance::getInstance()
{
	return instance;
}
