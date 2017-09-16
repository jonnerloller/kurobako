#ifndef graphics_vkdeleter_h__
#define graphics_vkdeleter_h__

#include <functional>
#include <vulkan/vulkan.h>

namespace sandcastle::graphics
{

	template<typename T>
	class vkhandle
	{
	public:

		vkhandle() : vkhandle([](T, VkAllocationCallbacks*) {}) {}

		vkhandle(std::function<void(T, VkAllocationCallbacks*)> deletef)
			: m_deleter([=](T obj) {deletef(obj, nullptr); }) {}

		vkhandle(const vkhandle<VkInstance>& instance,
			std::function<void(VkInstance, T, VkAllocationCallbacks*)> deletef)
			: m_deleter([&instance, deletef](T obj) {deletef(instance, obj, nullptr); }) {}

		vkhandle(const vkhandle<VkDevice>& device,
			std::function<void(VkDevice, T, VkAllocationCallbacks*)> deletef)
			: m_deleter([&device, deletef](T obj) {deletef(device, obj, nullptr); }) {}

		~vkhandle() { cleanup(); }

		T* operator&() { return &m_object; }
		const T* operator&() const { return &m_object; }

		T* replace() {
			cleanup();
			return &m_object;
		}

		void operator = (T rhs)
    {
			if (rhs != m_object) {
				cleanup();
				m_object = rhs;
			}
		}

		operator T() const
    {
			return m_object;
		}

		template<typename V>
		bool operator==(V rhs)
    {
			return m_object == T(rhs);
		}

	private:

		T m_object = VK_NULL_HANDLE;

		std::function<void(T)> m_deleter;

		void cleanup()
		{
			if (m_object != VK_NULL_HANDLE) {
				m_deleter(m_object);
				m_object = VK_NULL_HANDLE;
			}
		}

	};

}

#endif
