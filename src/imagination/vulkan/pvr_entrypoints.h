
/* Copyright © 2015-2021 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */
/* This file generated from vk_entrypoints_gen.py, don't edit directly. */

#include "vk_dispatch_table.h"


#ifndef PVR_ENTRYPOINTS_H
#define PVR_ENTRYPOINTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Entrypoint symbols are optional, and resolves to NULL if undefined.
 * On Unix, this semantics is achieved through weak symbols.
 * Note that we only declare the symbols as weak when it needs to be optional;
 * otherwise, the symbol is declared as a regular symbol.
 * This is to workaround a MinGW limitation: on MinGW, the definition for a
 * weak symbol must be regular, or the linker will end up resolving to one of
 * the fallback symbols with the absolute value of 0.
 * On MSVC, weak symbols are not well supported, so we use the functionally
 * equivalent /alternatename.
 */
#if !defined(_MSC_VER) && defined(VK_ENTRY_USE_WEAK)
#define VK_ENTRY_WEAK __attribute__ ((weak))
#else
#define VK_ENTRY_WEAK
#endif

/* On Unix, we explicitly declare the symbols as hidden, as -fvisibility=hidden
 * only applies to definitions, not declarations.
 * Windows uses hidden visibility by default (requiring dllexport for public
 * symbols), so we don't need to deal with visibility there.
 */
#ifndef _WIN32
#define VK_ENTRY_HIDDEN __attribute__ ((visibility("hidden")))
#else
#define VK_ENTRY_HIDDEN
#endif

extern const struct vk_instance_entrypoint_table pvr_instance_entrypoints;

extern const struct vk_physical_device_entrypoint_table pvr_physical_device_entrypoints;

extern const struct vk_device_entrypoint_table pvr_device_entrypoints;
extern const struct vk_device_entrypoint_table pvr_rogue_device_entrypoints;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumeratePhysicalDevices(VkInstance instance, uint32_t* pPhysicalDeviceCount, VkPhysicalDevice* pPhysicalDevices) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL pvr_GetInstanceProcAddr(VkInstance instance, const char* pName) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumerateInstanceVersion(uint32_t* pApiVersion) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_OHOS
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateSurfaceOHOS(VkInstance instance, const VkSurfaceCreateInfoOHOS* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_OHOS
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_DestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#ifdef VK_USE_PLATFORM_VI_NN
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateViSurfaceNN(VkInstance instance, const VkViSurfaceCreateInfoNN* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_VI_NN
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#ifdef VK_USE_PLATFORM_UBM_SEC
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateUbmSurfaceSEC(VkInstance instance, const VkUbmSurfaceCreateInfoSEC* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_UBM_SEC
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_XLIB_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_XLIB_KHR
#ifdef VK_USE_PLATFORM_XCB_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_XCB_KHR
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDirectFBSurfaceEXT(VkInstance instance, const VkDirectFBSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateImagePipeSurfaceFUCHSIA(VkInstance instance, const VkImagePipeSurfaceCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_GGP
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateStreamDescriptorSurfaceGGP(VkInstance instance, const VkStreamDescriptorSurfaceCreateInfoGGP* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_GGP
#ifdef VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateScreenSurfaceQNX(VkInstance instance, const VkScreenSurfaceCreateInfoQNX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_DebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* pLayerPrefix, const char* pMessage) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t* pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#ifdef VK_USE_PLATFORM_IOS_MVK
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateIOSSurfaceMVK(VkInstance instance, const VkIOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_IOS_MVK
#ifdef VK_USE_PLATFORM_MACOS_MVK
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateMacOSSurfaceMVK(VkInstance instance, const VkMacOSSurfaceCreateInfoMVK* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_MACOS_MVK
#ifdef VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateMetalSurfaceEXT(VkInstance instance, const VkMetalSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_SubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateHeadlessSurfaceEXT(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetExternalComputeQueueDataNV(VkExternalComputeQueueNV externalQueue, VkExternalComputeQueueDataParamsNV* params, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;

  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties* pQueueFamilyProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties* pMemoryProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures* pFeatures) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties* pFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties* pImageFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t* pPropertyCount, VkSparseImageFormatProperties* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPropertiesKHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlanePropertiesKHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t* pDisplayCount, VkDisplayKHR* pDisplays) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModePropertiesKHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDisplayModeKHR* pMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR* pCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#ifdef VK_USE_PLATFORM_WAYLAND_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL pvr_GetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display* display) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_WAYLAND_KHR
#ifdef VK_USE_PLATFORM_UBM_SEC
  VKAPI_ATTR VkBool32 VKAPI_CALL pvr_GetPhysicalDeviceUbmPresentationSupportSEC(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct ubm_device* device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_UBM_SEC
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL pvr_GetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_XLIB_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL pvr_GetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display* dpy, VisualID visualID) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_XLIB_KHR
#ifdef VK_USE_PLATFORM_XCB_KHR
  VKAPI_ATTR VkBool32 VKAPI_CALL pvr_GetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t* connection, xcb_visualid_t visual_id) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_XCB_KHR
#ifdef VK_USE_PLATFORM_DIRECTFB_EXT
  VKAPI_ATTR VkBool32 VKAPI_CALL pvr_GetPhysicalDeviceDirectFBPresentationSupportEXT(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, IDirectFB* dfb) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_DIRECTFB_EXT
#ifdef VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkBool32 VKAPI_CALL pvr_GetPhysicalDeviceScreenPresentationSupportQNX(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct _screen_window* window) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV* pExternalImageFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2* pFeatures) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2* pFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2* pImageFormatInfo, VkImageFormatProperties2* pImageFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pQueueFamilyPropertyCount, VkQueueFamilyProperties2* pQueueFamilyProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2* pMemoryProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo, uint32_t* pPropertyCount, VkSparseImageFormatProperties2* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo* pExternalBufferInfo, VkExternalBufferProperties* pExternalBufferProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo, VkExternalSemaphoreProperties* pExternalSemaphoreProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo* pExternalFenceInfo, VkExternalFenceProperties* pExternalFenceProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_ReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, VkDisplayKHR display) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ifdef VK_USE_PLATFORM_XLIB_XRANDR_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display* dpy, RROutput rrOutput, VkDisplayKHR* pDisplay) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_XLIB_XRANDR_EXT
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireWinrtDisplayNV(VkPhysicalDevice physicalDevice, VkDisplayKHR display) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetWinrtDisplayNV(VkPhysicalDevice physicalDevice, uint32_t deviceRelativeId, VkDisplayKHR* pDisplay) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT* pSurfaceCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pRectCount, VkRect2D* pRects) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT* pMultisampleProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkSurfaceCapabilities2KHR* pSurfaceCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pSurfaceFormatCount, VkSurfaceFormat2KHR* pSurfaceFormats) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayProperties2KHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkDisplayPlaneProperties2KHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t* pPropertyCount, VkDisplayModeProperties2KHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR* pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR* pCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceCalibrateableTimeDomainsKHR(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainKHR* pTimeDomains) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t* pTimeDomainCount, VkTimeDomainKHR* pTimeDomains) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceCooperativeMatrixPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesNV* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSurfacePresentModes2EXT(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t* pCounterCount, VkPerformanceCounterKHR* pCounters, VkPerformanceCounterDescriptionKHR* pCounterDescriptions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR* pPerformanceQueryCreateInfo, uint32_t* pNumPasses) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(VkPhysicalDevice physicalDevice, uint32_t* pCombinationCount, VkFramebufferMixedSamplesCombinationNV* pCombinations) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceToolProperties(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t* pToolCount, VkPhysicalDeviceToolProperties* pToolProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceFragmentShadingRatesKHR(VkPhysicalDevice physicalDevice, uint32_t* pFragmentShadingRateCount, VkPhysicalDeviceFragmentShadingRateKHR* pFragmentShadingRates) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceVideoCapabilitiesKHR(VkPhysicalDevice physicalDevice, const VkVideoProfileInfoKHR* pVideoProfile, VkVideoCapabilitiesKHR* pCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceVideoFormatPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoFormatInfoKHR* pVideoFormatInfo, uint32_t* pVideoFormatPropertyCount, VkVideoFormatPropertiesKHR* pVideoFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceVideoEncodeQualityLevelInfoKHR* pQualityLevelInfo, VkVideoEncodeQualityLevelPropertiesKHR* pQualityLevelProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireDrmDisplayEXT(VkPhysicalDevice physicalDevice, int32_t drmFd, VkDisplayKHR display) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDrmDisplayEXT(VkPhysicalDevice physicalDevice, int32_t drmFd, uint32_t connectorId, VkDisplayKHR* display) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceOpticalFlowImageFormatsNV(VkPhysicalDevice physicalDevice, const VkOpticalFlowImageFormatInfoNV* pOpticalFlowImageFormatInfo, uint32_t* pFormatCount, VkOpticalFlowImageFormatPropertiesNV* pImageFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceCooperativeMatrixPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixPropertiesKHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceCooperativeMatrixProperties2EXT(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceCooperativeMatrixInfo2EXT* pCooperativeMatrixInfo, uint32_t* pPropertyCount, VkCooperativeMatrixProperties2EXT* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeMatrixFlexibleDimensionsPropertiesNV* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceCooperativeVectorPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkCooperativeVectorPropertiesNV* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumeratePhysicalDeviceShaderInstrumentationMetricsARM(VkPhysicalDevice physicalDevice, uint32_t* pDescriptionCount, VkShaderInstrumentationMetricDescriptionARM* pDescriptions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceExternalTensorPropertiesARM(VkPhysicalDevice                             physicalDevice, const VkPhysicalDeviceExternalTensorInfoARM* pExternalTensorInfo, VkExternalTensorPropertiesARM*               pExternalTensorProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyDataGraphPropertiesARM(VkPhysicalDevice                     physicalDevice, uint32_t                             queueFamilyIndex, uint32_t*                            pQueueFamilyDataGraphPropertyCount, VkQueueFamilyDataGraphPropertiesARM* pQueueFamilyDataGraphProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(VkPhysicalDevice                                 physicalDevice, const VkPhysicalDeviceQueueFamilyDataGraphProcessingEngineInfoARM* pQueueFamilyDataGraphProcessingEngineInfo, VkQueueFamilyDataGraphProcessingEnginePropertiesARM*               pQueueFamilyDataGraphProcessingEngineProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_EnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t* pCounterCount, VkPerformanceCounterARM* pCounters, VkPerformanceCounterDescriptionARM* pCounterDescriptions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL pvr_GetPhysicalDeviceDescriptorSizeEXT(VkPhysicalDevice                                    physicalDevice, VkDescriptorType                                    descriptorType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(VkPhysicalDevice                                 physicalDevice, uint32_t                                         queueFamilyIndex, const VkQueueFamilyDataGraphPropertiesARM*       pQueueFamilyDataGraphProperties, VkBaseOutStructure*        pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(VkPhysicalDevice                                physicalDevice, uint32_t                                        queueFamilyIndex, const VkQueueFamilyDataGraphPropertiesARM*      pQueueFamilyDataGraphProperties, const VkDataGraphOpticalFlowImageFormatInfoARM* pOpticalFlowImageFormatInfo, uint32_t*                 pFormatCount, VkDataGraphOpticalFlowImageFormatPropertiesARM* pImageFormatProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;

  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL pvr_GetDeviceProcAddr(VkDevice device, const char* pName) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL pvr_rogue_GetDeviceProcAddr(VkDevice device, const char* pName) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueWaitIdle(VkQueue queue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueWaitIdle(VkQueue queue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_DeviceWaitIdle(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_DeviceWaitIdle(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UnmapMemory(VkDevice device, VkDeviceMemory memory) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UnmapMemory(VkDevice device, VkDeviceMemory memory) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetFenceStatus(VkDevice device, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetFenceStatus(VkDevice device, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetEventStatus(VkDevice device, VkEvent event) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetEventStatus(VkDevice device, VkEvent event) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetEvent(VkDevice device, VkEvent event) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetEvent(VkDevice device, VkEvent event) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ResetEvent(VkDevice device, VkEvent event) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ResetEvent(VkDevice device, VkEvent event) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_ResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_ResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreatePipelineBinariesKHR(VkDevice device, const VkPipelineBinaryCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineBinaryHandlesInfoKHR* pBinaries) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreatePipelineBinariesKHR(VkDevice device, const VkPipelineBinaryCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineBinaryHandlesInfoKHR* pBinaries) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyPipelineBinaryKHR(VkDevice device, VkPipelineBinaryKHR pipelineBinary, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyPipelineBinaryKHR(VkDevice device, VkPipelineBinaryKHR pipelineBinary, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPipelineKeyKHR(VkDevice device, const VkPipelineCreateInfoKHR* pPipelineCreateInfo, VkPipelineBinaryKeyKHR* pPipelineKey) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPipelineKeyKHR(VkDevice device, const VkPipelineCreateInfoKHR* pPipelineCreateInfo, VkPipelineBinaryKeyKHR* pPipelineKey) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPipelineBinaryDataKHR(VkDevice device, const VkPipelineBinaryDataInfoKHR* pInfo, VkPipelineBinaryKeyKHR* pPipelineBinaryKey, size_t* pPipelineBinaryDataSize, void* pPipelineBinaryData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPipelineBinaryDataKHR(VkDevice device, const VkPipelineBinaryDataInfoKHR* pInfo, VkPipelineBinaryKeyKHR* pPipelineBinaryKey, size_t* pPipelineBinaryDataSize, void* pPipelineBinaryData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ReleaseCapturedPipelineDataKHR(VkDevice device, const VkReleaseCapturedPipelineDataInfoKHR* pInfo, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ReleaseCapturedPipelineDataKHR(VkDevice device, const VkReleaseCapturedPipelineDataInfoKHR* pInfo, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI(VkDevice device, VkRenderPass renderpass, VkExtent2D* pMaxWorkgroupSize) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetRenderingAreaGranularity(VkDevice device, const VkRenderingAreaInfo* pRenderingAreaInfo, VkExtent2D* pGranularity) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetRenderingAreaGranularity(VkDevice device, const VkRenderingAreaInfo* pRenderingAreaInfo, VkExtent2D* pGranularity) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetRenderingAreaGranularityKHR(VkDevice device, const VkRenderingAreaInfo* pRenderingAreaInfo, VkExtent2D* pGranularity) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetRenderingAreaGranularityKHR(VkDevice device, const VkRenderingAreaInfo* pRenderingAreaInfo, VkExtent2D* pGranularity) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_EndCommandBuffer(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_EndCommandBuffer(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetPrimitiveRestartIndexEXT(VkCommandBuffer commandBuffer, uint32_t primitiveRestartIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetPrimitiveRestartIndexEXT(VkCommandBuffer commandBuffer, uint32_t primitiveRestartIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetAttachmentFeedbackLoopEnableEXT(VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetAttachmentFeedbackLoopEnableEXT(VkCommandBuffer commandBuffer, VkImageAspectFlags aspectMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport* pViewports) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D* pScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMultiEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawInfoEXT* pVertexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMultiIndexedEXT(VkCommandBuffer commandBuffer, uint32_t drawCount, const VkMultiDrawIndexedInfoEXT* pIndexInfo, uint32_t instanceCount, uint32_t firstInstance, uint32_t stride, const int32_t* pVertexOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSubpassShadingHUAWEI(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawClusterHUAWEI(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawClusterIndirectHUAWEI(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdUpdatePipelineIndirectBufferNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint           pipelineBindPoint, VkPipeline                    pipeline) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdUpdatePipelineIndirectBufferNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint           pipelineBindPoint, VkPipeline                    pipeline) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryIndirectKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryIndirectInfoKHR* pCopyMemoryIndirectInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryIndirectKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryIndirectInfoKHR* pCopyMemoryIndirectInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryToImageIndirectNV(VkCommandBuffer commandBuffer, VkDeviceAddress copyBufferAddress, uint32_t copyCount, uint32_t stride, VkImage dstImage, VkImageLayout dstImageLayout, const VkImageSubresourceLayers* pImageSubresources) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryToImageIndirectKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToImageIndirectInfoKHR* pCopyMemoryToImageIndirectInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryToImageIndirectKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToImageIndirectInfoKHR* pCopyMemoryToImageIndirectInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment* pAttachments, uint32_t rectCount, const VkClearRect* pRects) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT* pConditionalRenderingBegin) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginCustomResolveEXT(VkCommandBuffer commandBuffer, const VkBeginCustomResolveInfoEXT* pBeginCustomResolveInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginCustomResolveEXT(VkCommandBuffer commandBuffer, const VkBeginCustomResolveInfoEXT* pBeginCustomResolveInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndRenderPass(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndRenderPass(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_DebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT* pNameInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_DebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT* pTagInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR void VKAPI_CALL pvr_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdExecuteGeneratedCommandsNV(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPreprocessGeneratedCommandsNV(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoNV* pGeneratedCommandsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindPipelineShaderGroupNV(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline, uint32_t groupIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetGeneratedCommandsMemoryRequirementsNV(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateIndirectCommandsLayoutNV(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutNV* pIndirectCommandsLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyIndirectCommandsLayoutNV(VkDevice device, VkIndirectCommandsLayoutNV indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdExecuteGeneratedCommandsEXT(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdExecuteGeneratedCommandsEXT(VkCommandBuffer commandBuffer, VkBool32 isPreprocessed, const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPreprocessGeneratedCommandsEXT(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo, VkCommandBuffer stateCommandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPreprocessGeneratedCommandsEXT(VkCommandBuffer commandBuffer, const VkGeneratedCommandsInfoEXT* pGeneratedCommandsInfo, VkCommandBuffer stateCommandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetGeneratedCommandsMemoryRequirementsEXT(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetGeneratedCommandsMemoryRequirementsEXT(VkDevice device, const VkGeneratedCommandsMemoryRequirementsInfoEXT* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateIndirectCommandsLayoutEXT(VkDevice device, const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateIndirectCommandsLayoutEXT(VkDevice device, const VkIndirectCommandsLayoutCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectCommandsLayoutEXT* pIndirectCommandsLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyIndirectCommandsLayoutEXT(VkDevice device, VkIndirectCommandsLayoutEXT indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyIndirectCommandsLayoutEXT(VkDevice device, VkIndirectCommandsLayoutEXT indirectCommandsLayout, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateIndirectExecutionSetEXT(VkDevice device, const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectExecutionSetEXT* pIndirectExecutionSet) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateIndirectExecutionSetEXT(VkDevice device, const VkIndirectExecutionSetCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkIndirectExecutionSetEXT* pIndirectExecutionSet) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyIndirectExecutionSetEXT(VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyIndirectExecutionSetEXT(VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UpdateIndirectExecutionSetPipelineEXT(VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, uint32_t executionSetWriteCount, const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UpdateIndirectExecutionSetPipelineEXT(VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, uint32_t executionSetWriteCount, const VkWriteIndirectExecutionSetPipelineEXT* pExecutionSetWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UpdateIndirectExecutionSetShaderEXT(VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, uint32_t executionSetWriteCount, const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UpdateIndirectExecutionSetShaderEXT(VkDevice device, VkIndirectExecutionSetEXT indirectExecutionSet, uint32_t executionSetWriteCount, const VkWriteIndirectExecutionSetShaderEXT* pExecutionSetWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_TrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_TrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR* pMemoryWin32HandleProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR* pGetFdInfo, int* pFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR* pMemoryFdProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryZirconHandleFUCHSIA(VkDevice device, const VkMemoryGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryZirconHandlePropertiesFUCHSIA(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, zx_handle_t zirconHandle, VkMemoryZirconHandlePropertiesFUCHSIA* pMemoryZirconHandleProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryRemoteAddressNV(VkDevice device, const VkMemoryGetRemoteAddressInfoNV* pMemoryGetRemoteAddressInfo, VkRemoteAddressNV* pAddress) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR* pImportSemaphoreWin32HandleInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR* pGetFdInfo, int* pFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR* pImportSemaphoreFdInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkSemaphoreGetZirconHandleInfoFUCHSIA* pGetZirconHandleInfo, zx_handle_t* pZirconHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ImportSemaphoreZirconHandleFUCHSIA(VkDevice device, const VkImportSemaphoreZirconHandleInfoFUCHSIA* pImportSemaphoreZirconHandleInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR* pGetWin32HandleInfo, HANDLE* pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR* pImportFenceWin32HandleInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR* pGetFdInfo, int* pFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR* pImportFenceFdInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_DisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT* pDisplayPowerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_RegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT* pDeviceEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_RegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT* pDisplayEventInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t* pCounterValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags* pPeerMemoryFeatures) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR* pDeviceGroupPresentCapabilities) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR* pModes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR* pAcquireInfo, uint32_t* pImageIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorUpdateTemplate* pDescriptorUpdateTemplate) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSetWithTemplate(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSetWithTemplate(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_SetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, const VkHdrMetadataEXT* pMetadata) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE* pDisplayTimingProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pPresentationTimingCount, VkPastPresentationTimingGOOGLE* pPresentationTimings) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV* pViewportWScalings) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D* pDiscardRectangles) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDiscardRectangleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 discardRectangleEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDiscardRectangleModeEXT(VkCommandBuffer commandBuffer, VkDiscardRectangleModeEXT discardRectangleMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT* pSampleLocationsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceBufferMemoryRequirements(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceBufferMemoryRequirementsKHR(VkDevice device, const VkDeviceBufferMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceImageMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceImageMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceImageSparseMemoryRequirements(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceImageSparseMemoryRequirementsKHR(VkDevice device, const VkDeviceImageMemoryRequirements* pInfo, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2* pSparseMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSamplerYcbcrConversion* pYcbcrConversion) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkValidationCacheEXT* pValidationCache) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_MergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT* pSrcCaches) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, VkDescriptorSetLayoutSupport* pSupport) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSwapchainGrallocUsageANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSwapchainGrallocUsage2ANDROID(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, VkSwapchainImageUsageFlagsANDROID swapchainImageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AcquireImageANDROID(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueSignalReleaseImageANDROID(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t* pInfoSize, void* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_SetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetCalibratedTimestampsKHR(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetCalibratedTimestampsKHR(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoKHR* pTimestampInfos, uint64_t* pTimestamps, uint64_t* pMaxDeviation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT* pNameInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT* pTagInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_QueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_QueueEndDebugUtilsLabelEXT(VkQueue queue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_QueueEndDebugUtilsLabelEXT(VkQueue queue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_QueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT* pLabelInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHostPointer, VkMemoryHostPointerPropertiesEXT* pMemoryHostPointerProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo*      pRenderPassBegin, const VkSubpassBeginInfo*      pSubpassBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo*      pSubpassBeginInfo, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfo*        pSubpassEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t* pValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo* pWaitInfo, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo* pSignalInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetAndroidHardwareBufferPropertiesANDROID(VkDevice device, const struct AHardwareBuffer* buffer, VkAndroidHardwareBufferPropertiesANDROID* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_ANDROID_KHR
#ifdef VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryAndroidHardwareBufferANDROID(VkDevice device, const VkMemoryGetAndroidHardwareBufferInfoANDROID* pInfo, struct AHardwareBuffer** pBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_ANDROID_KHR
  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void* pCheckpointMarker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetQueueCheckpointDataNV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointDataNV* pCheckpointData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer* pCounterBuffers, const VkDeviceSize* pCounterBufferOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D* pExclusiveScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetExclusiveScissorEnableNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkBool32* pExclusiveScissorEnables) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV* pShadingRatePalettes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV* pCustomSampleOrders) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksEXT(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksIndirectEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksIndirectCountEXT(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureNV* pAccelerationStructure) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindInvocationMaskHUAWEI(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyAccelerationStructureKHR(VkDevice device, VkAccelerationStructureKHR accelerationStructure, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeKHR mode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyAccelerationStructureToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyAccelerationStructureToMemoryKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyAccelerationStructureToMemoryInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryToAccelerationStructureKHR(VkCommandBuffer commandBuffer, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyMemoryToAccelerationStructureKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToAccelerationStructureInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteAccelerationStructuresPropertiesKHR(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV* pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV* pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WriteAccelerationStructuresPropertiesKHR(VkDevice device, uint32_t accelerationStructureCount, const VkAccelerationStructureKHR* pAccelerationStructures, VkQueryType  queryType, size_t       dataSize, void* pData, size_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdTraceRaysKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, uint32_t width, uint32_t height, uint32_t depth) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetRayTracingShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetRayTracingCaptureReplayShaderGroupHandlesKHR(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateRayTracingPipelinesKHR(VkDevice device, VkDeferredOperationKHR deferredOperation, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdTraceRaysIndirectKHR(VkCommandBuffer commandBuffer, const VkStridedDeviceAddressRegionKHR* pRaygenShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pMissShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pHitShaderBindingTable, const VkStridedDeviceAddressRegionKHR* pCallableShaderBindingTable, VkDeviceAddress indirectDeviceAddress) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdTraceRaysIndirect2KHR(VkCommandBuffer commandBuffer, VkDeviceAddress indirectDeviceAddress) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetClusterAccelerationStructureBuildSizesNV(VkDevice device, const VkClusterAccelerationStructureInputInfoNV* pInfo, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetClusterAccelerationStructureBuildSizesNV(VkDevice device, const VkClusterAccelerationStructureInputInfoNV* pInfo, VkAccelerationStructureBuildSizesInfoKHR* pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBuildClusterAccelerationStructureIndirectNV(VkCommandBuffer                     commandBuffer, const VkClusterAccelerationStructureCommandsInfoNV*  pCommandInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBuildClusterAccelerationStructureIndirectNV(VkCommandBuffer                     commandBuffer, const VkClusterAccelerationStructureCommandsInfoNV*  pCommandInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceAccelerationStructureCompatibilityKHR(VkDevice device, const VkAccelerationStructureVersionInfoKHR* pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkDeviceSize VKAPI_CALL pvr_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkDeviceSize VKAPI_CALL pvr_rogue_GetRayTracingShaderGroupStackSizeKHR(VkDevice device, VkPipeline pipeline, uint32_t group, VkShaderGroupShaderKHR groupShader) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRayTracingPipelineStackSizeKHR(VkCommandBuffer commandBuffer, uint32_t pipelineStackSize) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint32_t VKAPI_CALL pvr_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint32_t VKAPI_CALL pvr_rogue_GetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint64_t VKAPI_CALL pvr_GetImageViewHandle64NVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint64_t VKAPI_CALL pvr_rogue_GetImageViewHandle64NVX(VkDevice device, const VkImageViewHandleInfoNVX* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetImageViewAddressNVX(VkDevice device, VkImageView imageView, VkImageViewAddressPropertiesNVX* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint64_t VKAPI_CALL pvr_GetDeviceCombinedImageSamplerIndexNVX(VkDevice device, uint64_t imageViewIndex, uint64_t samplerIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint64_t VKAPI_CALL pvr_rogue_GetDeviceCombinedImageSamplerIndexNVX(VkDevice device, uint64_t imageViewIndex, uint64_t samplerIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeviceGroupSurfacePresentModes2EXT(VkDevice device, const VkPhysicalDeviceSurfaceInfo2KHR* pSurfaceInfo, VkDeviceGroupPresentModeFlagsKHR* pModes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AcquireFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
#ifdef VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ReleaseFullScreenExclusiveModeEXT(VkDevice device, VkSwapchainKHR swapchain) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_WIN32_KHR
  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_ReleaseProfilingLockKHR(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_ReleaseProfilingLockKHR(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint64_t VKAPI_CALL pvr_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint64_t VKAPI_CALL pvr_rogue_GetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint64_t VKAPI_CALL pvr_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint64_t VKAPI_CALL pvr_rogue_GetBufferOpaqueCaptureAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_rogue_GetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_rogue_GetBufferDeviceAddressKHR(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_rogue_GetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_InitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL* pInitializeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UninitializePerformanceApiINTEL(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UninitializePerformanceApiINTEL(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL* pMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL* pOverrideInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_AcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo, VkPerformanceConfigurationINTEL* pConfiguration) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL* pValue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint64_t VKAPI_CALL pvr_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint64_t VKAPI_CALL pvr_rogue_GetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint64_t VKAPI_CALL pvr_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint64_t VKAPI_CALL pvr_rogue_GetDeviceMemoryOpaqueCaptureAddressKHR(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPipelineExecutablePropertiesKHR(VkDevice                        device, const VkPipelineInfoKHR*        pPipelineInfo, uint32_t* pExecutableCount, VkPipelineExecutablePropertiesKHR* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPipelineExecutableStatisticsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pStatisticCount, VkPipelineExecutableStatisticKHR* pStatistics) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPipelineExecutableInternalRepresentationsKHR(VkDevice                        device, const VkPipelineExecutableInfoKHR*  pExecutableInfo, uint32_t* pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR* pInternalRepresentations) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLineStipple(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLineStipple(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLineStippleKHR(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLineStippleKHR(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateAccelerationStructureKHR(VkDevice                                           device, const VkAccelerationStructureCreateInfoKHR*        pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkAccelerationStructureKHR*                        pAccelerationStructure) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBuildAccelerationStructuresKHR(VkCommandBuffer                                    commandBuffer, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBuildAccelerationStructuresIndirectKHR(VkCommandBuffer                  commandBuffer, uint32_t                                           infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkDeviceAddress*             pIndirectDeviceAddresses, const uint32_t*                    pIndirectStrides, const uint32_t* const*             ppMaxPrimitiveCounts) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BuildAccelerationStructuresKHR(VkDevice                                           device, VkDeferredOperationKHR deferredOperation, uint32_t infoCount, const VkAccelerationStructureBuildGeometryInfoKHR* pInfos, const VkAccelerationStructureBuildRangeInfoKHR* const* ppBuildRangeInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_rogue_GetAccelerationStructureDeviceAddressKHR(VkDevice device, const VkAccelerationStructureDeviceAddressInfoKHR* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateDeferredOperationKHR(VkDevice device, const VkAllocationCallbacks* pAllocator, VkDeferredOperationKHR* pDeferredOperation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyDeferredOperationKHR(VkDevice device, VkDeferredOperationKHR operation, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR uint32_t VKAPI_CALL pvr_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR uint32_t VKAPI_CALL pvr_rogue_GetDeferredOperationMaxConcurrencyKHR(VkDevice device, VkDeferredOperationKHR operation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeferredOperationResultKHR(VkDevice device, VkDeferredOperationKHR operation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_DeferredOperationJoinKHR(VkDevice device, VkDeferredOperationKHR operation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetPipelineIndirectMemoryRequirementsNV(VkDevice device, const VkComputePipelineCreateInfo* pCreateInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetPipelineIndirectMemoryRequirementsNV(VkDevice device, const VkComputePipelineCreateInfo* pCreateInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_GetPipelineIndirectDeviceAddressNV(VkDevice device, const VkPipelineIndirectDeviceAddressInfoNV* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkDeviceAddress VKAPI_CALL pvr_rogue_GetPipelineIndirectDeviceAddressNV(VkDevice device, const VkPipelineIndirectDeviceAddressInfoNV* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_AntiLagUpdateAMD(VkDevice device, const VkAntiLagDataAMD* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_AntiLagUpdateAMD(VkDevice device, const VkAntiLagDataAMD* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCullMode(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCullModeEXT(VkCommandBuffer commandBuffer, VkCullModeFlags cullMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetFrontFace(VkCommandBuffer commandBuffer, VkFrontFace frontFace) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetFrontFaceEXT(VkCommandBuffer commandBuffer, VkFrontFace frontFace) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetPrimitiveTopology(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetPrimitiveTopologyEXT(VkCommandBuffer commandBuffer, VkPrimitiveTopology primitiveTopology) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetViewportWithCount(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetViewportWithCountEXT(VkCommandBuffer commandBuffer, uint32_t viewportCount, const VkViewport* pViewports) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetScissorWithCount(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetScissorWithCountEXT(VkCommandBuffer commandBuffer, uint32_t scissorCount, const VkRect2D* pScissors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindIndexBuffer2(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindIndexBuffer2(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindIndexBuffer2KHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindIndexBuffer2KHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkDeviceSize size, VkIndexType indexType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindVertexBuffers2(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindVertexBuffers2EXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets, const VkDeviceSize* pSizes, const VkDeviceSize* pStrides) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthWriteEnable(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthWriteEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthWriteEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthCompareOp(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthCompareOpEXT(VkCommandBuffer commandBuffer, VkCompareOp depthCompareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthBoundsTestEnable(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthBoundsTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBoundsTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetStencilTestEnable(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetStencilTestEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stencilTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetStencilOp(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetStencilOpEXT(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetPatchControlPointsEXT(VkCommandBuffer commandBuffer, uint32_t patchControlPoints) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRasterizerDiscardEnable(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRasterizerDiscardEnableEXT(VkCommandBuffer commandBuffer, VkBool32 rasterizerDiscardEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthBiasEnable(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthBiasEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthBiasEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLogicOpEXT(VkCommandBuffer commandBuffer, VkLogicOp logicOp) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetPrimitiveRestartEnable(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetPrimitiveRestartEnableEXT(VkCommandBuffer commandBuffer, VkBool32 primitiveRestartEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetTessellationDomainOriginEXT(VkCommandBuffer commandBuffer, VkTessellationDomainOrigin domainOrigin) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthClampEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClampEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetPolygonModeEXT(VkCommandBuffer commandBuffer, VkPolygonMode polygonMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRasterizationSamplesEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  rasterizationSamples) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetSampleMaskEXT(VkCommandBuffer commandBuffer, VkSampleCountFlagBits  samples, const VkSampleMask*    pSampleMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetAlphaToCoverageEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToCoverageEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetAlphaToOneEnableEXT(VkCommandBuffer commandBuffer, VkBool32 alphaToOneEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLogicOpEnableEXT(VkCommandBuffer commandBuffer, VkBool32 logicOpEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetColorBlendEnableEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkBool32* pColorBlendEnables) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetColorBlendEquationEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendEquationEXT* pColorBlendEquations) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetColorWriteMaskEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorComponentFlags* pColorWriteMasks) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRasterizationStreamEXT(VkCommandBuffer commandBuffer, uint32_t rasterizationStream) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetConservativeRasterizationModeEXT(VkCommandBuffer commandBuffer, VkConservativeRasterizationModeEXT conservativeRasterizationMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetExtraPrimitiveOverestimationSizeEXT(VkCommandBuffer commandBuffer, float extraPrimitiveOverestimationSize) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthClipEnableEXT(VkCommandBuffer commandBuffer, VkBool32 depthClipEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetSampleLocationsEnableEXT(VkCommandBuffer commandBuffer, VkBool32 sampleLocationsEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetColorBlendAdvancedEXT(VkCommandBuffer commandBuffer, uint32_t firstAttachment, uint32_t attachmentCount, const VkColorBlendAdvancedEXT* pColorBlendAdvanced) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetProvokingVertexModeEXT(VkCommandBuffer commandBuffer, VkProvokingVertexModeEXT provokingVertexMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLineRasterizationModeEXT(VkCommandBuffer commandBuffer, VkLineRasterizationModeEXT lineRasterizationMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetLineStippleEnableEXT(VkCommandBuffer commandBuffer, VkBool32 stippledLineEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthClipNegativeOneToOneEXT(VkCommandBuffer commandBuffer, VkBool32 negativeOneToOne) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetViewportWScalingEnableNV(VkCommandBuffer commandBuffer, VkBool32 viewportWScalingEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetViewportSwizzleNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportSwizzleNV* pViewportSwizzles) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCoverageToColorEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageToColorEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCoverageToColorLocationNV(VkCommandBuffer commandBuffer, uint32_t coverageToColorLocation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCoverageModulationModeNV(VkCommandBuffer commandBuffer, VkCoverageModulationModeNV coverageModulationMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCoverageModulationTableEnableNV(VkCommandBuffer commandBuffer, VkBool32 coverageModulationTableEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCoverageModulationTableNV(VkCommandBuffer commandBuffer, uint32_t coverageModulationTableCount, const float* pCoverageModulationTable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetShadingRateImageEnableNV(VkCommandBuffer commandBuffer, VkBool32 shadingRateImageEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetCoverageReductionModeNV(VkCommandBuffer commandBuffer, VkCoverageReductionModeNV coverageReductionMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRepresentativeFragmentTestEnableNV(VkCommandBuffer commandBuffer, VkBool32 representativeFragmentTestEnable) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreatePrivateDataSlot(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreatePrivateDataSlotEXT(VkDevice device, const VkPrivateDataSlotCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPrivateDataSlot* pPrivateDataSlot) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyPrivateDataSlot(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyPrivateDataSlotEXT(VkDevice device, VkPrivateDataSlot privateDataSlot, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetPrivateData(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetPrivateDataEXT(VkDevice device, VkObjectType objectType, uint64_t objectHandle, VkPrivateDataSlot privateDataSlot, uint64_t* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyBuffer2(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferInfo2* pCopyBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyImage2(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyImage2KHR(VkCommandBuffer commandBuffer, const VkCopyImageInfo2* pCopyImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBlitImage2(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBlitImage2KHR(VkCommandBuffer commandBuffer, const VkBlitImageInfo2* pBlitImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyBufferToImage2(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyBufferToImage2KHR(VkCommandBuffer commandBuffer, const VkCopyBufferToImageInfo2* pCopyBufferToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyImageToBuffer2(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyImageToBuffer2KHR(VkCommandBuffer commandBuffer, const VkCopyImageToBufferInfo2* pCopyImageToBufferInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdResolveImage2(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdResolveImage2KHR(VkCommandBuffer commandBuffer, const VkResolveImageInfo2* pResolveImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetFragmentShadingRateKHR(VkCommandBuffer           commandBuffer, const VkExtent2D*                           pFragmentSize, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetFragmentShadingRateEnumNV(VkCommandBuffer           commandBuffer, VkFragmentShadingRateNV                     shadingRate, const VkFragmentShadingRateCombinerOpKHR    combinerOps[2]) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetAccelerationStructureBuildSizesKHR(VkDevice                                            device, VkAccelerationStructureBuildTypeKHR                 buildType, const VkAccelerationStructureBuildGeometryInfoKHR*  pBuildInfo, const uint32_t*  pMaxPrimitiveCounts, VkAccelerationStructureBuildSizesInfoKHR*           pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetVertexInputEXT(VkCommandBuffer commandBuffer, uint32_t vertexBindingDescriptionCount, const VkVertexInputBindingDescription2EXT* pVertexBindingDescriptions, uint32_t vertexAttributeDescriptionCount, const VkVertexInputAttributeDescription2EXT* pVertexAttributeDescriptions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetColorWriteEnableEXT(VkCommandBuffer       commandBuffer, uint32_t                                attachmentCount, const VkBool32*   pColorWriteEnables) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdResetEvent2(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdResetEvent2KHR(VkCommandBuffer                   commandBuffer, VkEvent                                             event, VkPipelineStageFlags2               stageMask) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWaitEvents2(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWaitEvents2KHR(VkCommandBuffer                   commandBuffer, uint32_t                                            eventCount, const VkEvent*                     pEvents, const VkDependencyInfo*            pDependencyInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPipelineBarrier2(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPipelineBarrier2KHR(VkCommandBuffer                   commandBuffer, const VkDependencyInfo*                             pDependencyInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueSubmit2(VkQueue                          queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueSubmit2(VkQueue                          queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueSubmit2KHR(VkQueue                          queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueSubmit2KHR(VkQueue                          queue, uint32_t                            submitCount, const VkSubmitInfo2*              pSubmits, VkFence           fence) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteTimestamp2(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteTimestamp2KHR(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkQueryPool                                         queryPool, uint32_t                                            query) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteBufferMarker2AMD(VkCommandBuffer                   commandBuffer, VkPipelineStageFlags2               stage, VkBuffer                                            dstBuffer, VkDeviceSize                                        dstOffset, uint32_t                                            marker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetQueueCheckpointData2NV(VkQueue queue, uint32_t* pCheckpointDataCount, VkCheckpointData2NV* pCheckpointData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyMemoryToImage(VkDevice device, const VkCopyMemoryToImageInfo*    pCopyMemoryToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyMemoryToImage(VkDevice device, const VkCopyMemoryToImageInfo*    pCopyMemoryToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyMemoryToImageEXT(VkDevice device, const VkCopyMemoryToImageInfo*    pCopyMemoryToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyMemoryToImageEXT(VkDevice device, const VkCopyMemoryToImageInfo*    pCopyMemoryToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyImageToMemory(VkDevice device, const VkCopyImageToMemoryInfo*    pCopyImageToMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyImageToMemory(VkDevice device, const VkCopyImageToMemoryInfo*    pCopyImageToMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyImageToMemoryEXT(VkDevice device, const VkCopyImageToMemoryInfo*    pCopyImageToMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyImageToMemoryEXT(VkDevice device, const VkCopyImageToMemoryInfo*    pCopyImageToMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyImageToImage(VkDevice device, const VkCopyImageToImageInfo*    pCopyImageToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyImageToImage(VkDevice device, const VkCopyImageToImageInfo*    pCopyImageToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyImageToImageEXT(VkDevice device, const VkCopyImageToImageInfo*    pCopyImageToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyImageToImageEXT(VkDevice device, const VkCopyImageToImageInfo*    pCopyImageToImageInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_TransitionImageLayout(VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo*    pTransitions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_TransitionImageLayout(VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo*    pTransitions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_TransitionImageLayoutEXT(VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo*    pTransitions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_TransitionImageLayoutEXT(VkDevice device, uint32_t transitionCount, const VkHostImageLayoutTransitionInfo*    pTransitions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateVideoSessionKHR(VkDevice device, const VkVideoSessionCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionKHR* pVideoSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyVideoSessionKHR(VkDevice device, VkVideoSessionKHR videoSession, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateVideoSessionParametersKHR(VkDevice device, const VkVideoSessionParametersCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkVideoSessionParametersKHR* pVideoSessionParameters) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_UpdateVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkVideoSessionParametersUpdateInfoKHR* pUpdateInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetEncodedVideoSessionParametersKHR(VkDevice device, const VkVideoEncodeSessionParametersGetInfoKHR* pVideoSessionParametersInfo, VkVideoEncodeSessionParametersFeedbackInfoKHR* pFeedbackInfo, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetEncodedVideoSessionParametersKHR(VkDevice device, const VkVideoEncodeSessionParametersGetInfoKHR* pVideoSessionParametersInfo, VkVideoEncodeSessionParametersFeedbackInfoKHR* pFeedbackInfo, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyVideoSessionParametersKHR(VkDevice device, VkVideoSessionParametersKHR videoSessionParameters, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetVideoSessionMemoryRequirementsKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t* pMemoryRequirementsCount, VkVideoSessionMemoryRequirementsKHR* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindVideoSessionMemoryKHR(VkDevice device, VkVideoSessionKHR videoSession, uint32_t bindSessionMemoryInfoCount, const VkBindVideoSessionMemoryInfoKHR* pBindSessionMemoryInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDecodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoDecodeInfoKHR* pDecodeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoBeginCodingInfoKHR* pBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdControlVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoCodingControlInfoKHR* pCodingControlInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndVideoCodingKHR(VkCommandBuffer commandBuffer, const VkVideoEndCodingInfoKHR* pEndCodingInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEncodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoEncodeInfoKHR* pEncodeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEncodeVideoKHR(VkCommandBuffer commandBuffer, const VkVideoEncodeInfoKHR* pEncodeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDecompressMemoryNV(VkCommandBuffer commandBuffer, uint32_t decompressRegionCount, const VkDecompressMemoryRegionNV* pDecompressMemoryRegions) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDecompressMemoryIndirectCountNV(VkCommandBuffer commandBuffer, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetPartitionedAccelerationStructuresBuildSizesNV(VkDevice device, const VkPartitionedAccelerationStructureInstancesInputNV* pInfo, VkAccelerationStructureBuildSizesInfoKHR*                  pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetPartitionedAccelerationStructuresBuildSizesNV(VkDevice device, const VkPartitionedAccelerationStructureInstancesInputNV* pInfo, VkAccelerationStructureBuildSizesInfoKHR*                  pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBuildPartitionedAccelerationStructuresNV(VkCommandBuffer                     commandBuffer, const VkBuildPartitionedAccelerationStructureInfoNV*  pBuildInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBuildPartitionedAccelerationStructuresNV(VkCommandBuffer                     commandBuffer, const VkBuildPartitionedAccelerationStructureInfoNV*  pBuildInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDecompressMemoryEXT(VkCommandBuffer commandBuffer, const VkDecompressMemoryInfoEXT* pDecompressMemoryInfoEXT) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDecompressMemoryEXT(VkCommandBuffer commandBuffer, const VkDecompressMemoryInfoEXT* pDecompressMemoryInfoEXT) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDecompressMemoryIndirectCountEXT(VkCommandBuffer commandBuffer, VkMemoryDecompressionMethodFlagsEXT decompressionMethod, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t maxDecompressionCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDecompressMemoryIndirectCountEXT(VkCommandBuffer commandBuffer, VkMemoryDecompressionMethodFlagsEXT decompressionMethod, VkDeviceAddress indirectCommandsAddress, VkDeviceAddress indirectCommandsCountAddress, uint32_t maxDecompressionCount, uint32_t stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateCuModuleNVX(VkDevice device, const VkCuModuleCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuModuleNVX* pModule) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateCuFunctionNVX(VkDevice device, const VkCuFunctionCreateInfoNVX* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCuFunctionNVX* pFunction) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyCuModuleNVX(VkDevice device, VkCuModuleNVX module, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyCuFunctionNVX(VkDevice device, VkCuFunctionNVX function, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCuLaunchKernelNVX(VkCommandBuffer commandBuffer, const VkCuLaunchInfoNVX* pLaunchInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDescriptorSetLayoutSizeEXT(VkDevice device, VkDescriptorSetLayout layout, VkDeviceSize* pLayoutSizeInBytes) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDescriptorSetLayoutBindingOffsetEXT(VkDevice device, VkDescriptorSetLayout layout, uint32_t binding, VkDeviceSize* pOffset) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDescriptorEXT(VkDevice device, const VkDescriptorGetInfoEXT* pDescriptorInfo, size_t dataSize, void* pDescriptor) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindDescriptorBuffersEXT(VkCommandBuffer commandBuffer, uint32_t bufferCount, const VkDescriptorBufferBindingInfoEXT* pBindingInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDescriptorBufferOffsetsEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t setCount, const uint32_t* pBufferIndices, const VkDeviceSize* pOffsets) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindDescriptorBufferEmbeddedSamplersEXT(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetBufferOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkBufferCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetImageOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetImageViewOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkImageViewCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSamplerOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkSamplerCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetAccelerationStructureOpaqueCaptureDescriptorDataEXT(VkDevice device, const VkAccelerationStructureCaptureDescriptorDataInfoEXT* pInfo, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_SetDeviceMemoryPriorityEXT(VkDevice       device, VkDeviceMemory memory, float          priority) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WaitForPresent2KHR(VkDevice device, VkSwapchainKHR swapchain, const VkPresentWait2InfoKHR* pPresentWait2Info) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WaitForPresent2KHR(VkDevice device, VkSwapchainKHR swapchain, const VkPresentWait2InfoKHR* pPresentWait2Info) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WaitForPresentKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t presentId, uint64_t timeout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateBufferCollectionFUCHSIA(VkDevice device, const VkBufferCollectionCreateInfoFUCHSIA* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferCollectionFUCHSIA* pCollection) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetBufferCollectionBufferConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkBufferConstraintsInfoFUCHSIA* pBufferConstraintsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetBufferCollectionImageConstraintsFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkImageConstraintsInfoFUCHSIA* pImageConstraintsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR void VKAPI_CALL pvr_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyBufferCollectionFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
#ifdef VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetBufferCollectionPropertiesFUCHSIA(VkDevice device, VkBufferCollectionFUCHSIA collection, VkBufferCollectionPropertiesFUCHSIA* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_FUCHSIA
  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginRendering(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginRenderingKHR(VkCommandBuffer                   commandBuffer, const VkRenderingInfo*                              pRenderingInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndRendering(VkCommandBuffer                   commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndRendering(VkCommandBuffer                   commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndRendering2KHR(VkCommandBuffer                   commandBuffer, const VkRenderingEndInfoKHR*        pRenderingEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndRendering2KHR(VkCommandBuffer                   commandBuffer, const VkRenderingEndInfoKHR*        pRenderingEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndRendering2EXT(VkCommandBuffer                   commandBuffer, const VkRenderingEndInfoKHR*        pRenderingEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndRendering2EXT(VkCommandBuffer                   commandBuffer, const VkRenderingEndInfoKHR*        pRenderingEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndRenderingKHR(VkCommandBuffer                   commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDescriptorSetLayoutHostMappingInfoVALVE(VkDevice device, const VkDescriptorSetBindingReferenceVALVE* pBindingReference, VkDescriptorSetLayoutHostMappingInfoVALVE* pHostMapping) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDescriptorSetHostMappingVALVE(VkDevice device, VkDescriptorSet descriptorSet, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*                     pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                                     pMicromap) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateMicromapEXT(VkDevice                                           device, const VkMicromapCreateInfoEXT*                     pCreateInfo, const VkAllocationCallbacks*       pAllocator, VkMicromapEXT*                                     pMicromap) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBuildMicromapsEXT(VkCommandBuffer             commandBuffer, uint32_t                                      infoCount, const VkMicromapBuildInfoEXT* pInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBuildMicromapsEXT(VkCommandBuffer             commandBuffer, uint32_t                                      infoCount, const VkMicromapBuildInfoEXT* pInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BuildMicromapsEXT(VkDevice                                      device, VkDeferredOperationKHR        deferredOperation, uint32_t                                      infoCount, const VkMicromapBuildInfoEXT* pInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BuildMicromapsEXT(VkDevice                                      device, VkDeferredOperationKHR        deferredOperation, uint32_t                                      infoCount, const VkMicromapBuildInfoEXT* pInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyMicromapEXT(VkDevice                                        device, VkMicromapEXT micromap, const VkAllocationCallbacks*    pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyMicromapEXT(VkDevice                                        device, VkMicromapEXT micromap, const VkAllocationCallbacks*    pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT*      pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMicromapEXT(VkCommandBuffer commandBuffer, const VkCopyMicromapInfoEXT*      pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyMicromapEXT(VkDevice                               device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT*           pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyMicromapEXT(VkDevice                               device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapInfoEXT*           pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMicromapToMemoryEXT(VkCommandBuffer    commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMicromapToMemoryEXT(VkCommandBuffer    commandBuffer, const VkCopyMicromapToMemoryInfoEXT* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyMicromapToMemoryEXT(VkDevice                               device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT*   pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyMicromapToMemoryEXT(VkDevice                               device, VkDeferredOperationKHR deferredOperation, const VkCopyMicromapToMemoryInfoEXT*   pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryToMicromapEXT(VkCommandBuffer    commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryToMicromapEXT(VkCommandBuffer    commandBuffer, const VkCopyMemoryToMicromapInfoEXT* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CopyMemoryToMicromapEXT(VkDevice                               device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT*   pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CopyMemoryToMicromapEXT(VkDevice                               device, VkDeferredOperationKHR deferredOperation, const VkCopyMemoryToMicromapInfoEXT*   pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t                                 micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType        queryType, VkQueryPool                              queryPool, uint32_t                                 firstQuery) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteMicromapsPropertiesEXT(VkCommandBuffer commandBuffer, uint32_t                                 micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType        queryType, VkQueryPool                              queryPool, uint32_t                                 firstQuery) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WriteMicromapsPropertiesEXT(VkDevice                                 device, uint32_t                                 micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType                              queryType, size_t                                   dataSize, void*                     pData, size_t                                   stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WriteMicromapsPropertiesEXT(VkDevice                                 device, uint32_t                                 micromapCount, const VkMicromapEXT* pMicromaps, VkQueryType                              queryType, size_t                                   dataSize, void*                     pData, size_t                                   stride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceMicromapCompatibilityEXT(VkDevice                                 device, const VkMicromapVersionInfoEXT*          pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceMicromapCompatibilityEXT(VkDevice                                 device, const VkMicromapVersionInfoEXT*          pVersionInfo, VkAccelerationStructureCompatibilityKHR* pCompatibility) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetMicromapBuildSizesEXT(VkDevice                            device, VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT*       pBuildInfo, VkMicromapBuildSizesInfoEXT*        pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetMicromapBuildSizesEXT(VkDevice                            device, VkAccelerationStructureBuildTypeKHR buildType, const VkMicromapBuildInfoEXT*       pBuildInfo, VkMicromapBuildSizesInfoEXT*        pSizeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetShaderModuleIdentifierEXT(VkDevice device, VkShaderModule shaderModule, VkShaderModuleIdentifierEXT* pIdentifier) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetShaderModuleCreateInfoIdentifierEXT(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, VkShaderModuleIdentifierEXT* pIdentifier) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageSubresourceLayout2(VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageSubresourceLayout2(VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageSubresourceLayout2KHR(VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageSubresourceLayout2KHR(VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetImageSubresourceLayout2EXT(VkDevice device, VkImage image, const VkImageSubresource2* pSubresource, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoKHR* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPipelinePropertiesEXT(VkDevice device, const VkPipelineInfoKHR* pPipelineInfo, VkBaseOutStructure* pPipelineProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR void VKAPI_CALL pvr_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_ExportMetalObjectsEXT(VkDevice device, VkExportMetalObjectsInfoEXT* pMetalObjectsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindTileMemoryQCOM(VkCommandBuffer commandBuffer, const VkTileMemoryBindInfoQCOM* pTileMemoryBindInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindTileMemoryQCOM(VkCommandBuffer commandBuffer, const VkTileMemoryBindInfoQCOM* pTileMemoryBindInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetFramebufferTilePropertiesQCOM(VkDevice device, VkFramebuffer framebuffer, uint32_t* pPropertiesCount, VkTilePropertiesQCOM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDynamicRenderingTilePropertiesQCOM(VkDevice device, const VkRenderingInfo* pRenderingInfo, VkTilePropertiesQCOM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateOpticalFlowSessionNV(VkDevice device, const VkOpticalFlowSessionCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkOpticalFlowSessionNV* pSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyOpticalFlowSessionNV(VkDevice device, VkOpticalFlowSessionNV session, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindOpticalFlowSessionImageNV(VkDevice device, VkOpticalFlowSessionNV session, VkOpticalFlowSessionBindingPointNV bindingPoint, VkImageView view, VkImageLayout layout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdOpticalFlowExecuteNV(VkCommandBuffer commandBuffer, VkOpticalFlowSessionNV session, const VkOpticalFlowExecuteInfoNV* pExecuteInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeviceFaultInfoEXT(VkDevice device, VkDeviceFaultCountsEXT* pFaultCounts, VkDeviceFaultInfoEXT* pFaultInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeviceFaultReportsKHR(VkDevice device, uint64_t timeout, uint32_t* pFaultCounts, VkDeviceFaultInfoKHR* pFaultInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeviceFaultReportsKHR(VkDevice device, uint64_t timeout, uint32_t* pFaultCounts, VkDeviceFaultInfoKHR* pFaultInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDeviceFaultDebugInfoKHR(VkDevice device, VkDeviceFaultDebugInfoKHR* pDebugInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDeviceFaultDebugInfoKHR(VkDevice device, VkDeviceFaultDebugInfoKHR* pDebugInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthBias2EXT(VkCommandBuffer commandBuffer, const VkDepthBiasInfoEXT*         pDepthBiasInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthBias2EXT(VkCommandBuffer commandBuffer, const VkDepthBiasInfoEXT*         pDepthBiasInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ReleaseSwapchainImagesKHR(VkDevice device, const VkReleaseSwapchainImagesInfoKHR* pReleaseInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ReleaseSwapchainImagesKHR(VkDevice device, const VkReleaseSwapchainImagesInfoKHR* pReleaseInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoKHR* pReleaseInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ReleaseSwapchainImagesEXT(VkDevice device, const VkReleaseSwapchainImagesInfoKHR* pReleaseInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceImageSubresourceLayout(VkDevice device, const VkDeviceImageSubresourceInfo* pInfo, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceImageSubresourceLayout(VkDevice device, const VkDeviceImageSubresourceInfo* pInfo, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceImageSubresourceLayoutKHR(VkDevice device, const VkDeviceImageSubresourceInfo* pInfo, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceImageSubresourceLayoutKHR(VkDevice device, const VkDeviceImageSubresourceInfo* pInfo, VkSubresourceLayout2* pLayout) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_MapMemory2(VkDevice device, const VkMemoryMapInfo* pMemoryMapInfo, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_MapMemory2(VkDevice device, const VkMemoryMapInfo* pMemoryMapInfo, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_MapMemory2KHR(VkDevice device, const VkMemoryMapInfo* pMemoryMapInfo, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_MapMemory2KHR(VkDevice device, const VkMemoryMapInfo* pMemoryMapInfo, void** ppData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_UnmapMemory2(VkDevice device, const VkMemoryUnmapInfo* pMemoryUnmapInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_UnmapMemory2(VkDevice device, const VkMemoryUnmapInfo* pMemoryUnmapInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfo* pMemoryUnmapInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_UnmapMemory2KHR(VkDevice device, const VkMemoryUnmapInfo* pMemoryUnmapInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateShadersEXT(VkDevice device, uint32_t createInfoCount, const VkShaderCreateInfoEXT* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkShaderEXT* pShaders) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyShaderEXT(VkDevice device, VkShaderEXT shader, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetShaderBinaryDataEXT(VkDevice device, VkShaderEXT shader, size_t* pDataSize, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindShadersEXT(VkCommandBuffer commandBuffer, uint32_t stageCount, const VkShaderStageFlagBits* pStages, const VkShaderEXT* pShaders) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetSwapchainPresentTimingQueueSizeEXT(VkDevice device, VkSwapchainKHR swapchain, uint32_t size) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetSwapchainPresentTimingQueueSizeEXT(VkDevice device, VkSwapchainKHR swapchain, uint32_t size) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSwapchainTimingPropertiesEXT(VkDevice device, VkSwapchainKHR swapchain, VkSwapchainTimingPropertiesEXT* pSwapchainTimingProperties, uint64_t* pSwapchainTimingPropertiesCounter) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSwapchainTimingPropertiesEXT(VkDevice device, VkSwapchainKHR swapchain, VkSwapchainTimingPropertiesEXT* pSwapchainTimingProperties, uint64_t* pSwapchainTimingPropertiesCounter) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetSwapchainTimeDomainPropertiesEXT(VkDevice device, VkSwapchainKHR swapchain, VkSwapchainTimeDomainPropertiesEXT* pSwapchainTimeDomainProperties, uint64_t* pTimeDomainsCounter) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetSwapchainTimeDomainPropertiesEXT(VkDevice device, VkSwapchainKHR swapchain, VkSwapchainTimeDomainPropertiesEXT* pSwapchainTimeDomainProperties, uint64_t* pTimeDomainsCounter) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetPastPresentationTimingEXT(VkDevice device, const VkPastPresentationTimingInfoEXT* pPastPresentationTimingInfo, VkPastPresentationTimingPropertiesEXT* pPastPresentationTimingProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetPastPresentationTimingEXT(VkDevice device, const VkPastPresentationTimingInfoEXT* pPastPresentationTimingInfo, VkPastPresentationTimingPropertiesEXT* pPastPresentationTimingProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetScreenBufferPropertiesQNX(VkDevice device, const struct _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetScreenBufferPropertiesQNX(VkDevice device, const struct _screen_buffer* buffer, VkScreenBufferPropertiesQNX* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_SCREEN_QNX
  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateGpaSessionAMD(VkDevice                                     device, const VkGpaSessionCreateInfoAMD*             pCreateInfo, const VkAllocationCallbacks* pAllocator, VkGpaSessionAMD*                             pGpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateGpaSessionAMD(VkDevice                                     device, const VkGpaSessionCreateInfoAMD*             pCreateInfo, const VkAllocationCallbacks* pAllocator, VkGpaSessionAMD*                             pGpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyGpaSessionAMD(VkDevice                                          device, VkGpaSessionAMD gpaSession, const VkAllocationCallbacks*      pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyGpaSessionAMD(VkDevice                                          device, VkGpaSessionAMD gpaSession, const VkAllocationCallbacks*      pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetGpaDeviceClockModeAMD(VkDevice                     device, VkGpaDeviceClockModeInfoAMD* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetGpaDeviceClockModeAMD(VkDevice                     device, VkGpaDeviceClockModeInfoAMD* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetGpaDeviceClockInfoAMD(VkDevice                    device, VkGpaDeviceGetClockInfoAMD* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetGpaDeviceClockInfoAMD(VkDevice                    device, VkGpaDeviceGetClockInfoAMD* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CmdBeginGpaSessionAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CmdBeginGpaSessionAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CmdEndGpaSessionAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CmdEndGpaSessionAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CmdBeginGpaSampleAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession, const VkGpaSampleBeginInfoAMD*    pGpaSampleBeginInfo, uint32_t*                         pSampleID) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CmdBeginGpaSampleAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession, const VkGpaSampleBeginInfoAMD*    pGpaSampleBeginInfo, uint32_t*                         pSampleID) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndGpaSampleAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession, uint32_t                          sampleID) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndGpaSampleAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession, uint32_t                          sampleID) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetGpaSessionStatusAMD(VkDevice        device, VkGpaSessionAMD gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetGpaSessionStatusAMD(VkDevice        device, VkGpaSessionAMD gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetGpaSessionResultsAMD(VkDevice                                 device, VkGpaSessionAMD                          gpaSession, uint32_t                                 sampleID, size_t*            pSizeInBytes, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetGpaSessionResultsAMD(VkDevice                                 device, VkGpaSessionAMD                          gpaSession, uint32_t                                 sampleID, size_t*            pSizeInBytes, void* pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_ResetGpaSessionAMD(VkDevice        device, VkGpaSessionAMD gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ResetGpaSessionAMD(VkDevice        device, VkGpaSessionAMD gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyGpaSessionResultsAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyGpaSessionResultsAMD(VkCommandBuffer commandBuffer, VkGpaSessionAMD                   gpaSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindDescriptorSets2(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo*   pBindDescriptorSetsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindDescriptorSets2(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo*   pBindDescriptorSetsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindDescriptorSets2KHR(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo*   pBindDescriptorSetsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindDescriptorSets2KHR(VkCommandBuffer commandBuffer, const VkBindDescriptorSetsInfo*   pBindDescriptorSetsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushConstants2(VkCommandBuffer commandBuffer, const VkPushConstantsInfo*        pPushConstantsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushConstants2(VkCommandBuffer commandBuffer, const VkPushConstantsInfo*        pPushConstantsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushConstants2KHR(VkCommandBuffer commandBuffer, const VkPushConstantsInfo*        pPushConstantsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushConstants2KHR(VkCommandBuffer commandBuffer, const VkPushConstantsInfo*        pPushConstantsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSet2(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo*    pPushDescriptorSetInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSet2(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo*    pPushDescriptorSetInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSet2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo*    pPushDescriptorSetInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSet2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetInfo*    pPushDescriptorSetInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSetWithTemplate2(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSetWithTemplate2(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDescriptorSetWithTemplate2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDescriptorSetWithTemplate2KHR(VkCommandBuffer commandBuffer, const VkPushDescriptorSetWithTemplateInfo* pPushDescriptorSetWithTemplateInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDescriptorBufferOffsets2EXT(VkCommandBuffer commandBuffer, const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDescriptorBufferOffsets2EXT(VkCommandBuffer commandBuffer, const VkSetDescriptorBufferOffsetsInfoEXT* pSetDescriptorBufferOffsetsInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindDescriptorBufferEmbeddedSamplers2EXT(VkCommandBuffer commandBuffer, const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindDescriptorBufferEmbeddedSamplers2EXT(VkCommandBuffer commandBuffer, const VkBindDescriptorBufferEmbeddedSamplersInfoEXT* pBindDescriptorBufferEmbeddedSamplersInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_SetLatencySleepModeNV(VkDevice device, VkSwapchainKHR swapchain, const VkLatencySleepModeInfoNV* pSleepModeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_SetLatencySleepModeNV(VkDevice device, VkSwapchainKHR swapchain, const VkLatencySleepModeInfoNV* pSleepModeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_LatencySleepNV(VkDevice device, VkSwapchainKHR swapchain, const VkLatencySleepInfoNV* pSleepInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_LatencySleepNV(VkDevice device, VkSwapchainKHR swapchain, const VkLatencySleepInfoNV* pSleepInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_SetLatencyMarkerNV(VkDevice device, VkSwapchainKHR swapchain, const VkSetLatencyMarkerInfoNV* pLatencyMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_SetLatencyMarkerNV(VkDevice device, VkSwapchainKHR swapchain, const VkSetLatencyMarkerInfoNV* pLatencyMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetLatencyTimingsNV(VkDevice device, VkSwapchainKHR swapchain, VkGetLatencyMarkerInfoNV* pLatencyMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetLatencyTimingsNV(VkDevice device, VkSwapchainKHR swapchain, VkGetLatencyMarkerInfoNV* pLatencyMarkerInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_QueueNotifyOutOfBandNV(VkQueue queue, const VkOutOfBandQueueTypeInfoNV* pQueueTypeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_QueueNotifyOutOfBandNV(VkQueue queue, const VkOutOfBandQueueTypeInfoNV* pQueueTypeInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_SetLatencySleepModeLegacyNV(VkDevice device, VkBool32 lowLatencyMode, VkBool32 lowLatencyBoost, uint32_t minimumIntervalUs) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_SetLatencySleepModeLegacyNV(VkDevice device, VkBool32 lowLatencyMode, VkBool32 lowLatencyBoost, uint32_t minimumIntervalUs) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_LatencySleepLegacyNV(VkDevice device, VkSemaphore signalSemaphore, uint64_t value) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_LatencySleepLegacyNV(VkDevice device, VkSemaphore signalSemaphore, uint64_t value) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_SetLatencyMarkerLegacyNV(VkDevice device, uint64_t frameID, uint32_t marker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_SetLatencyMarkerLegacyNV(VkDevice device, uint64_t frameID, uint32_t marker) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetLatencyTimingsLegacyNV(VkDevice device, void* pTimings) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetLatencyTimingsLegacyNV(VkDevice device, void* pTimings) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_QueueNotifyOutOfBandLegacyNV(VkQueue queue, uint32_t queueType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_QueueNotifyOutOfBandLegacyNV(VkQueue queue, uint32_t queueType) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetSleepStatusLegacyNV(VkDevice device, VkBool32* pLowLatencyMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetSleepStatusLegacyNV(VkDevice device, VkBool32* pLowLatencyMode) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_ShutdownLatencyDeviceLegacyNV(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_ShutdownLatencyDeviceLegacyNV(VkDevice device) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRenderingAttachmentLocations(VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo* pLocationInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRenderingAttachmentLocations(VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo* pLocationInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRenderingAttachmentLocationsKHR(VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo* pLocationInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRenderingAttachmentLocationsKHR(VkCommandBuffer commandBuffer, const VkRenderingAttachmentLocationInfo* pLocationInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRenderingInputAttachmentIndices(VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRenderingInputAttachmentIndices(VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetRenderingInputAttachmentIndicesKHR(VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetRenderingInputAttachmentIndicesKHR(VkCommandBuffer commandBuffer, const VkRenderingInputAttachmentIndexInfo* pInputAttachmentIndexInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDepthClampRangeEXT(VkCommandBuffer commandBuffer, VkDepthClampModeEXT depthClampMode, const VkDepthClampRangeEXT* pDepthClampRange) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDepthClampRangeEXT(VkCommandBuffer commandBuffer, VkDepthClampModeEXT depthClampMode, const VkDepthClampRangeEXT* pDepthClampRange) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryMetalHandleEXT(VkDevice device, const VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, void** pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryMetalHandleEXT(VkDevice device, const VkMemoryGetMetalHandleInfoEXT* pGetMetalHandleInfo, void** pHandle) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_METAL_EXT
#ifdef VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryMetalHandlePropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryMetalHandlePropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void* pHandle, VkMemoryMetalHandlePropertiesEXT* pMemoryMetalHandleProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_METAL_EXT
  VKAPI_ATTR VkResult VKAPI_CALL pvr_ConvertCooperativeVectorMatrixNV(VkDevice device, const VkConvertCooperativeVectorMatrixInfoNV* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_ConvertCooperativeVectorMatrixNV(VkDevice device, const VkConvertCooperativeVectorMatrixInfoNV* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdConvertCooperativeVectorMatrixNV(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkConvertCooperativeVectorMatrixInfoNV* pInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdConvertCooperativeVectorMatrixNV(VkCommandBuffer commandBuffer, uint32_t infoCount, const VkConvertCooperativeVectorMatrixInfoNV* pInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDispatchTileQCOM(VkCommandBuffer commandBuffer, const VkDispatchTileInfoQCOM* pDispatchTileInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDispatchTileQCOM(VkCommandBuffer commandBuffer, const VkDispatchTileInfoQCOM* pDispatchTileInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginPerTileExecutionQCOM(VkCommandBuffer commandBuffer, const VkPerTileBeginInfoQCOM* pPerTileBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginPerTileExecutionQCOM(VkCommandBuffer commandBuffer, const VkPerTileBeginInfoQCOM* pPerTileBeginInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndPerTileExecutionQCOM(VkCommandBuffer commandBuffer, const VkPerTileEndInfoQCOM* pPerTileEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndPerTileExecutionQCOM(VkCommandBuffer commandBuffer, const VkPerTileEndInfoQCOM* pPerTileEndInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateExternalComputeQueueNV(VkDevice device, const VkExternalComputeQueueCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkExternalComputeQueueNV* pExternalQueue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateExternalComputeQueueNV(VkDevice device, const VkExternalComputeQueueCreateInfoNV* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkExternalComputeQueueNV* pExternalQueue) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyExternalComputeQueueNV(VkDevice device, VkExternalComputeQueueNV externalQueue, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyExternalComputeQueueNV(VkDevice device, VkExternalComputeQueueNV externalQueue, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateShaderInstrumentationARM(VkDevice device, const VkShaderInstrumentationCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderInstrumentationARM* pInstrumentation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateShaderInstrumentationARM(VkDevice device, const VkShaderInstrumentationCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderInstrumentationARM* pInstrumentation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyShaderInstrumentationARM(VkDevice device, VkShaderInstrumentationARM instrumentation, const VkAllocationCallbacks*    pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyShaderInstrumentationARM(VkDevice device, VkShaderInstrumentationARM instrumentation, const VkAllocationCallbacks*    pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginShaderInstrumentationARM(VkCommandBuffer commandBuffer, VkShaderInstrumentationARM instrumentation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginShaderInstrumentationARM(VkCommandBuffer commandBuffer, VkShaderInstrumentationARM instrumentation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndShaderInstrumentationARM(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndShaderInstrumentationARM(VkCommandBuffer commandBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetShaderInstrumentationValuesARM(VkDevice device, VkShaderInstrumentationARM instrumentation, uint32_t* pMetricBlockCount, void* pMetricValues, VkShaderInstrumentationValuesFlagsARM flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetShaderInstrumentationValuesARM(VkDevice device, VkShaderInstrumentationARM instrumentation, uint32_t* pMetricBlockCount, void* pMetricValues, VkShaderInstrumentationValuesFlagsARM flags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_ClearShaderInstrumentationMetricsARM(VkDevice device, VkShaderInstrumentationARM instrumentation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_ClearShaderInstrumentationMetricsARM(VkDevice device, VkShaderInstrumentationARM instrumentation) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateTensorARM(VkDevice device, const VkTensorCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkTensorARM* pTensor) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateTensorARM(VkDevice device, const VkTensorCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkTensorARM* pTensor) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyTensorARM(VkDevice device, VkTensorARM tensor, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyTensorARM(VkDevice device, VkTensorARM tensor, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateTensorViewARM(VkDevice device, const VkTensorViewCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkTensorViewARM* pView) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateTensorViewARM(VkDevice device, const VkTensorViewCreateInfoARM* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkTensorViewARM* pView) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyTensorViewARM(VkDevice device, VkTensorViewARM tensorView, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyTensorViewARM(VkDevice device, VkTensorViewARM tensorView, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetTensorMemoryRequirementsARM(VkDevice device, const VkTensorMemoryRequirementsInfoARM* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetTensorMemoryRequirementsARM(VkDevice device, const VkTensorMemoryRequirementsInfoARM* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindTensorMemoryARM(VkDevice device, uint32_t bindInfoCount, const VkBindTensorMemoryInfoARM* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindTensorMemoryARM(VkDevice device, uint32_t bindInfoCount, const VkBindTensorMemoryInfoARM* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDeviceTensorMemoryRequirementsARM(VkDevice device, const VkDeviceTensorMemoryRequirementsARM* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDeviceTensorMemoryRequirementsARM(VkDevice device, const VkDeviceTensorMemoryRequirementsARM* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyTensorARM(VkCommandBuffer commandBuffer, const VkCopyTensorInfoARM* pCopyTensorInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyTensorARM(VkCommandBuffer commandBuffer, const VkCopyTensorInfoARM* pCopyTensorInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetTensorOpaqueCaptureDescriptorDataARM(VkDevice                                    device, const VkTensorCaptureDescriptorDataInfoARM* pInfo, void*                                       pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetTensorOpaqueCaptureDescriptorDataARM(VkDevice                                    device, const VkTensorCaptureDescriptorDataInfoARM* pInfo, void*                                       pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetTensorViewOpaqueCaptureDescriptorDataARM(VkDevice                                        device, const VkTensorViewCaptureDescriptorDataInfoARM* pInfo, void*                                           pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetTensorViewOpaqueCaptureDescriptorDataARM(VkDevice                                        device, const VkTensorViewCaptureDescriptorDataInfoARM* pInfo, void*                                           pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDataGraphPipelinesARM(VkDevice               device, VkDeferredOperationKHR deferredOperation, VkPipelineCache        pipelineCache, uint32_t               createInfoCount, const VkDataGraphPipelineCreateInfoARM* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline*     pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateDataGraphPipelinesARM(VkDevice               device, VkDeferredOperationKHR deferredOperation, VkPipelineCache        pipelineCache, uint32_t               createInfoCount, const VkDataGraphPipelineCreateInfoARM* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline*     pPipelines) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateDataGraphPipelineSessionARM(VkDevice                                     device, const VkDataGraphPipelineSessionCreateInfoARM*   pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDataGraphPipelineSessionARM*                   pSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateDataGraphPipelineSessionARM(VkDevice                                     device, const VkDataGraphPipelineSessionCreateInfoARM*   pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDataGraphPipelineSessionARM*                   pSession) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDataGraphPipelineSessionBindPointRequirementsARM(VkDevice device, const VkDataGraphPipelineSessionBindPointRequirementsInfoARM* pInfo, uint32_t* pBindPointRequirementCount, VkDataGraphPipelineSessionBindPointRequirementARM* pBindPointRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDataGraphPipelineSessionBindPointRequirementsARM(VkDevice device, const VkDataGraphPipelineSessionBindPointRequirementsInfoARM* pInfo, uint32_t* pBindPointRequirementCount, VkDataGraphPipelineSessionBindPointRequirementARM* pBindPointRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_GetDataGraphPipelineSessionMemoryRequirementsARM(VkDevice device, const VkDataGraphPipelineSessionMemoryRequirementsInfoARM* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_GetDataGraphPipelineSessionMemoryRequirementsARM(VkDevice device, const VkDataGraphPipelineSessionMemoryRequirementsInfoARM* pInfo, VkMemoryRequirements2* pMemoryRequirements) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_BindDataGraphPipelineSessionMemoryARM(VkDevice device, uint32_t bindInfoCount, const VkBindDataGraphPipelineSessionMemoryInfoARM* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_BindDataGraphPipelineSessionMemoryARM(VkDevice device, uint32_t bindInfoCount, const VkBindDataGraphPipelineSessionMemoryInfoARM* pBindInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_DestroyDataGraphPipelineSessionARM(VkDevice device, VkDataGraphPipelineSessionARM session, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_DestroyDataGraphPipelineSessionARM(VkDevice device, VkDataGraphPipelineSessionARM session, const VkAllocationCallbacks* pAllocator) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDispatchDataGraphARM(VkCommandBuffer commandBuffer, VkDataGraphPipelineSessionARM session, const VkDataGraphPipelineDispatchInfoARM* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDispatchDataGraphARM(VkCommandBuffer commandBuffer, VkDataGraphPipelineSessionARM session, const VkDataGraphPipelineDispatchInfoARM* pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDataGraphPipelineAvailablePropertiesARM(VkDevice device, const VkDataGraphPipelineInfoARM* pPipelineInfo, uint32_t* pPropertiesCount, VkDataGraphPipelinePropertyARM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDataGraphPipelineAvailablePropertiesARM(VkDevice device, const VkDataGraphPipelineInfoARM* pPipelineInfo, uint32_t* pPropertiesCount, VkDataGraphPipelinePropertyARM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetDataGraphPipelinePropertiesARM(VkDevice                          device, const VkDataGraphPipelineInfoARM* pPipelineInfo, uint32_t                          propertiesCount, VkDataGraphPipelinePropertyQueryResultARM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetDataGraphPipelinePropertiesARM(VkDevice                          device, const VkDataGraphPipelineInfoARM* pPipelineInfo, uint32_t                          propertiesCount, VkDataGraphPipelinePropertyQueryResultARM* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#ifdef VK_USE_PLATFORM_OHOS
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetNativeBufferPropertiesOHOS(VkDevice device, const struct OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetNativeBufferPropertiesOHOS(VkDevice device, const struct OH_NativeBuffer* buffer, VkNativeBufferPropertiesOHOS* pProperties) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_OHOS
#ifdef VK_USE_PLATFORM_OHOS
  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetMemoryNativeBufferOHOS(VkDevice device, const VkMemoryGetNativeBufferInfoOHOS* pInfo, struct OH_NativeBuffer** pBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetMemoryNativeBufferOHOS(VkDevice device, const VkMemoryGetNativeBufferInfoOHOS* pInfo, struct OH_NativeBuffer** pBuffer) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


#endif // VK_USE_PLATFORM_OHOS
  VKAPI_ATTR VkResult VKAPI_CALL pvr_QueueSetPerfHintQCOM(VkQueue queue, const VkPerfHintInfoQCOM*  pPerfHintInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_QueueSetPerfHintQCOM(VkQueue queue, const VkPerfHintInfoQCOM*  pPerfHintInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetComputeOccupancyPriorityNV(VkCommandBuffer commandBuffer, const VkComputeOccupancyPriorityParametersNV* pParameters) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetComputeOccupancyPriorityNV(VkCommandBuffer commandBuffer, const VkComputeOccupancyPriorityParametersNV* pParameters) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WriteSamplerDescriptorsEXT(VkDevice                                            device, uint32_t                                            samplerCount, const VkSamplerCreateInfo*       pSamplers, const VkHostAddressRangeEXT*     pDescriptors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WriteSamplerDescriptorsEXT(VkDevice                                            device, uint32_t                                            samplerCount, const VkSamplerCreateInfo*       pSamplers, const VkHostAddressRangeEXT*     pDescriptors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_WriteResourceDescriptorsEXT(VkDevice                                                device, uint32_t                                                resourceCount, const VkResourceDescriptorInfoEXT*  pResources, const VkHostAddressRangeEXT*        pDescriptors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_WriteResourceDescriptorsEXT(VkDevice                                                device, uint32_t                                                resourceCount, const VkResourceDescriptorInfoEXT*  pResources, const VkHostAddressRangeEXT*        pDescriptors) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindSamplerHeapEXT(VkCommandBuffer                   commandBuffer, const VkBindHeapInfoEXT*                            pBindInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindSamplerHeapEXT(VkCommandBuffer                   commandBuffer, const VkBindHeapInfoEXT*                            pBindInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindResourceHeapEXT(VkCommandBuffer                   commandBuffer, const VkBindHeapInfoEXT*                            pBindInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindResourceHeapEXT(VkCommandBuffer                   commandBuffer, const VkBindHeapInfoEXT*                            pBindInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdPushDataEXT(VkCommandBuffer                   commandBuffer, const VkPushDataInfoEXT*                            pPushDataInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdPushDataEXT(VkCommandBuffer                   commandBuffer, const VkPushDataInfoEXT*                            pPushDataInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_RegisterCustomBorderColorEXT(VkDevice                                            device, const VkSamplerCustomBorderColorCreateInfoEXT*      pBorderColor, VkBool32                                            requestIndex, uint32_t*                                           pIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_RegisterCustomBorderColorEXT(VkDevice                                            device, const VkSamplerCustomBorderColorCreateInfoEXT*      pBorderColor, VkBool32                                            requestIndex, uint32_t*                                           pIndex) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_UnregisterCustomBorderColorEXT(VkDevice                                            device, uint32_t                                            index) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_UnregisterCustomBorderColorEXT(VkDevice                                            device, uint32_t                                            index) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetImageOpaqueCaptureDataEXT(VkDevice                                            device, uint32_t                                            imageCount, const VkImage*                     pImages, VkHostAddressRangeEXT*             pDatas) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetImageOpaqueCaptureDataEXT(VkDevice                                            device, uint32_t                                            imageCount, const VkImage*                     pImages, VkHostAddressRangeEXT*             pDatas) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_GetTensorOpaqueCaptureDataARM(VkDevice                                            device, uint32_t                                            tensorCount, const VkTensorARM*                pTensors, VkHostAddressRangeEXT*            pDatas) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_GetTensorOpaqueCaptureDataARM(VkDevice                                            device, uint32_t                                            tensorCount, const VkTensorARM*                pTensors, VkHostAddressRangeEXT*            pDatas) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyDeviceMemoryInfoKHR* pCopyMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyDeviceMemoryInfoKHR* pCopyMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyMemoryToImageKHR(VkCommandBuffer commandBuffer, const VkCopyDeviceMemoryImageInfoKHR* pCopyMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyMemoryToImageKHR(VkCommandBuffer commandBuffer, const VkCopyDeviceMemoryImageInfoKHR* pCopyMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyImageToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyDeviceMemoryImageInfoKHR* pCopyMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyImageToMemoryKHR(VkCommandBuffer commandBuffer, const VkCopyDeviceMemoryImageInfoKHR* pCopyMemoryInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdUpdateMemoryKHR(VkCommandBuffer   commandBuffer, const VkDeviceAddressRangeKHR*      pDstRange, VkAddressCommandFlagsKHR dstFlags, VkDeviceSize                        dataSize, const void*          pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdUpdateMemoryKHR(VkCommandBuffer   commandBuffer, const VkDeviceAddressRangeKHR*      pDstRange, VkAddressCommandFlagsKHR dstFlags, VkDeviceSize                        dataSize, const void*          pData) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdFillMemoryKHR(VkCommandBuffer   commandBuffer, const VkDeviceAddressRangeKHR*      pDstRange, VkAddressCommandFlagsKHR dstFlags, uint32_t                            data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdFillMemoryKHR(VkCommandBuffer   commandBuffer, const VkDeviceAddressRangeKHR*      pDstRange, VkAddressCommandFlagsKHR dstFlags, uint32_t                            data) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdCopyQueryPoolResultsToMemoryKHR(VkCommandBuffer   commandBuffer, VkQueryPool                         queryPool, uint32_t                            firstQuery, uint32_t                            queryCount, const VkStridedDeviceAddressRangeKHR* pDstRange, VkAddressCommandFlagsKHR    dstFlags, VkQueryResultFlags  queryResultFlags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdCopyQueryPoolResultsToMemoryKHR(VkCommandBuffer   commandBuffer, VkQueryPool                         queryPool, uint32_t                            firstQuery, uint32_t                            queryCount, const VkStridedDeviceAddressRangeKHR* pDstRange, VkAddressCommandFlagsKHR    dstFlags, VkQueryResultFlags  queryResultFlags) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginConditionalRendering2EXT(VkCommandBuffer   commandBuffer, const VkConditionalRenderingBeginInfo2EXT* pConditionalRenderingBegin) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginConditionalRendering2EXT(VkCommandBuffer   commandBuffer, const VkConditionalRenderingBeginInfo2EXT* pConditionalRenderingBegin) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindTransformFeedbackBuffers2EXT(VkCommandBuffer   commandBuffer, uint32_t                            firstBinding, uint32_t                            bindingCount, const VkBindTransformFeedbackBuffer2InfoEXT* pBindingInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindTransformFeedbackBuffers2EXT(VkCommandBuffer   commandBuffer, uint32_t                            firstBinding, uint32_t                            bindingCount, const VkBindTransformFeedbackBuffer2InfoEXT* pBindingInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBeginTransformFeedback2EXT(VkCommandBuffer   commandBuffer, uint32_t                            firstCounterRange, uint32_t            counterRangeCount, const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBeginTransformFeedback2EXT(VkCommandBuffer   commandBuffer, uint32_t                            firstCounterRange, uint32_t            counterRangeCount, const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdEndTransformFeedback2EXT(VkCommandBuffer   commandBuffer, uint32_t                            firstCounterRange, uint32_t            counterRangeCount, const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdEndTransformFeedback2EXT(VkCommandBuffer   commandBuffer, uint32_t                            firstCounterRange, uint32_t            counterRangeCount, const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirectByteCount2EXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfo, uint32_t counterOffset, uint32_t vertexStride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirectByteCount2EXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, const VkBindTransformFeedbackBuffer2InfoEXT* pCounterInfo, uint32_t counterOffset, uint32_t vertexStride) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdWriteMarkerToMemoryAMD(VkCommandBuffer   commandBuffer, const VkMemoryMarkerInfoAMD*         pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdWriteMarkerToMemoryAMD(VkCommandBuffer   commandBuffer, const VkMemoryMarkerInfoAMD*         pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindIndexBuffer3KHR(VkCommandBuffer   commandBuffer, const VkBindIndexBuffer3InfoKHR*    pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindIndexBuffer3KHR(VkCommandBuffer   commandBuffer, const VkBindIndexBuffer3InfoKHR*    pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdBindVertexBuffers3KHR(VkCommandBuffer commandBuffer, uint32_t                            firstBinding, uint32_t                            bindingCount, const VkBindVertexBuffer3InfoKHR* pBindingInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdBindVertexBuffers3KHR(VkCommandBuffer commandBuffer, uint32_t                            firstBinding, uint32_t                            bindingCount, const VkBindVertexBuffer3InfoKHR* pBindingInfos) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirect2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirect2InfoKHR*       pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirect2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirect2InfoKHR*       pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndexedIndirect2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirect2InfoKHR*       pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndexedIndirect2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirect2InfoKHR*       pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndirectCount2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirectCount2InfoKHR*  pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndirectCount2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirectCount2InfoKHR*  pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawIndexedIndirectCount2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirectCount2InfoKHR*  pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawIndexedIndirectCount2KHR(VkCommandBuffer   commandBuffer, const VkDrawIndirectCount2InfoKHR*  pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksIndirect2EXT(VkCommandBuffer   commandBuffer, const VkDrawIndirect2InfoKHR*       pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksIndirect2EXT(VkCommandBuffer   commandBuffer, const VkDrawIndirect2InfoKHR*       pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDrawMeshTasksIndirectCount2EXT(VkCommandBuffer   commandBuffer, const VkDrawIndirectCount2InfoKHR*  pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDrawMeshTasksIndirectCount2EXT(VkCommandBuffer   commandBuffer, const VkDrawIndirectCount2InfoKHR*  pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdDispatchIndirect2KHR(VkCommandBuffer   commandBuffer, const VkDispatchIndirect2InfoKHR*   pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdDispatchIndirect2KHR(VkCommandBuffer   commandBuffer, const VkDispatchIndirect2InfoKHR*   pInfo) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR VkResult VKAPI_CALL pvr_CreateAccelerationStructure2KHR(VkDevice                                     device, const VkAccelerationStructureCreateInfo2KHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR*                  pAccelerationStructure) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR VkResult VKAPI_CALL pvr_rogue_CreateAccelerationStructure2KHR(VkDevice                                     device, const VkAccelerationStructureCreateInfo2KHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkAccelerationStructureKHR*                  pAccelerationStructure) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;


  VKAPI_ATTR void VKAPI_CALL pvr_CmdSetDispatchParametersARM(VkCommandBuffer commandBuffer, const VkDispatchParametersARM*    pDispatchParameters) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;
  VKAPI_ATTR void VKAPI_CALL pvr_rogue_CmdSetDispatchParametersARM(VkCommandBuffer commandBuffer, const VkDispatchParametersARM*    pDispatchParameters) VK_ENTRY_WEAK VK_ENTRY_HIDDEN;



#ifdef __cplusplus
}
#endif

#endif /* PVR_ENTRYPOINTS_H */
