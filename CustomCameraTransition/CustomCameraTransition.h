#pragma once

#include "GuiBase.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "bakkesmod/plugin/PluginSettingsWindow.h"

#include "version.h"
constexpr auto plugin_version = stringify(VERSION_MAJOR) "." stringify(VERSION_MINOR) "." stringify(VERSION_PATCH) "." stringify(VERSION_BUILD);

enum class ViewTargetBlendFunction : uint8_t
{
	VTBlend_Linear = 0,
	VTBlend_Cubic = 1,
	VTBlend_EaseIn = 2,
	VTBlend_EaseOut = 3,
	VTBlend_EaseInOut = 4,
	VTBlend_MidwayStep = 5
};

class CustomCameraTransition: public BakkesMod::Plugin::BakkesModPlugin
	,public SettingsWindowBase // Uncomment if you wanna render your own tab in the settings menu
	//,public PluginWindowBase // Uncomment if you want to render your own plugin window
{
	std::map<ViewTargetBlendFunction, std::string> blendFunctionMap = {
		{ViewTargetBlendFunction::VTBlend_Linear, "Linear"},
		{ViewTargetBlendFunction::VTBlend_Cubic, "Cubic"},
		{ViewTargetBlendFunction::VTBlend_EaseIn, "Ease In"},
		{ViewTargetBlendFunction::VTBlend_EaseOut, "Ease Out"},
		{ViewTargetBlendFunction::VTBlend_EaseInOut, "Ease In Out"},
		{ViewTargetBlendFunction::VTBlend_MidwayStep, "Midway Step"}
	};

	float blendTime = 0.5;
	ViewTargetBlendFunction blendFunction = ViewTargetBlendFunction::VTBlend_Linear;
	float blendExp = 2.f;
	bool lockOutgoing = false;

	float remainingTime = 0.5f;

	//Boilerplate
	void onLoad() override;
	//void onUnload() override; // Uncomment and implement if you need a unload method

	void OnCameraBlenderTransition(const CameraStateBlenderWrapper& blender);

public:
	void RenderSettings() override; // Uncomment if you wanna render your own tab in the settings menu
	//void RenderWindow() override; // Uncomment if you want to render your own plugin window
};
