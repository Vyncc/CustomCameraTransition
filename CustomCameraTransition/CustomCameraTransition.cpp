#include "pch.h"
#include "CustomCameraTransition.h"
#include "bakkesmod/wrappers/Engine/WorldInfoWrapper.h"


BAKKESMOD_PLUGIN(CustomCameraTransition, "CustomCameraTransition", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CustomCameraTransition::onLoad()
{
	_globalCvarManager = cvarManager;

	cvarManager->registerNotifier("SetCameraTransition", std::bind(&CustomCameraTransition::SetNextTransition, this, std::placeholders::_1), "Set the camera transition to custom values. Usage: SetCameraTransition <Blend Time> <Remaining Time> <Blend Function (Linear, Cubic, Ease In, EaseOut, EaseInOut, MidwayStep)> <Blend Exp> <Lock Outgoing (true or false)>", 0);
	cvarManager->registerNotifier("ResetCameraTransition", std::bind(&CustomCameraTransition::ResetCameraTransition, this, std::placeholders::_1), "Reset camera transition values", 0);

    gameWrapper->HookEventWithCallerPost<ActorWrapper>(
        "Function ProjectX.CameraStateBlender_X.TransitionToState",
        [this](const ActorWrapper& caller, ...) {
            OnCameraBlenderTransition(CameraStateBlenderWrapper{ caller.memory_address });
        });
}

void CustomCameraTransition::OnCameraBlenderTransition(const CameraStateBlenderWrapper& blender)
{
    //LOG("transition");

    if (overrideTransition)
    {
        auto transition = blender.GetTransition();
        transition.blend_params.blend_time = blendTime;
        transition.blend_params.blend_exp = blendExp;
        transition.blend_params.lock_outgoing = lockOutgoing;
        transition.blend_params.blend_function = static_cast<unsigned char>(blendFunction);
        transition.remaining_time = remainingTime;
        blender.SetTransition(transition);

        //LOG("override transition");
    }
}

//SetCameraTransition <Blend Time> <Remaining Time> <Blend Function (Linear, Cubic, Ease In, EaseOut, EaseInOut, MidwayStep)> <Blend Exp> <Lock Outgoing (true or false)>
void CustomCameraTransition::SetNextTransition(std::vector<std::string> args)
{
    if (args.size() < 6)
    {
        LOG("[ERROR]Not enough arguments provided. Usage: SetCameraTransition <Blend Time> <Remaining Time> <Blend Function (Linear, Cubic, Ease In, EaseOut, EaseInOut, MidwayStep)> <Blend Exp> <Lock Outgoing (true or false)>");
        return;
    }

    blendTime = std::stof(args[1]);
    remainingTime = std::stof(args[2]);
    blendFunction = StringToBlendFunction(args[3]);
    blendExp = std::stof(args[4]);
    lockOutgoing = (args[5] == "true");

    overrideTransition = true;
}

ViewTargetBlendFunction CustomCameraTransition::StringToBlendFunction(const std::string& str)
{
	if (str == "Linear")
		return ViewTargetBlendFunction::VTBlend_Linear;
    else if (str == "Cubic")
		return ViewTargetBlendFunction::VTBlend_Cubic;
    else if (str == "EaseIn")
		return ViewTargetBlendFunction::VTBlend_EaseIn;
    else if (str == "EaseOut")
		return ViewTargetBlendFunction::VTBlend_EaseOut;
    else if (str == "EaseInOut")
		return ViewTargetBlendFunction::VTBlend_EaseInOut;
    else if (str == "MidwayStep")
		return ViewTargetBlendFunction::VTBlend_MidwayStep;
    else
    {
        LOG("[ERROR]Couldn't find blend function: {}, using default: Linear", str);
        return ViewTargetBlendFunction::VTBlend_Linear;
    }
}

void CustomCameraTransition::ResetCameraTransition(std::vector<std::string> args)
{
	blendTime = 0.f;
	remainingTime = 0.f;
	blendFunction = ViewTargetBlendFunction::VTBlend_Linear;
	blendExp = 2.f;
	lockOutgoing = false;

	overrideTransition = false;

	LOG("Camera transition values reset to default");
}
