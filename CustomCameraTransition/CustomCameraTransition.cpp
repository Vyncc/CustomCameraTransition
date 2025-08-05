#include "pch.h"
#include "CustomCameraTransition.h"
#include "bakkesmod/wrappers/Engine/WorldInfoWrapper.h"


BAKKESMOD_PLUGIN(CustomCameraTransition, "CustomCameraTransition", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CustomCameraTransition::onLoad()
{
	_globalCvarManager = cvarManager;

	cvarManager->registerNotifier("SetNextCamTransition", std::bind(&CustomCameraTransition::SetNextTransition, this, std::placeholders::_1), "It will set the next camera transition to custom values. Usage: SetNextCamTransition <Blend Time> <Remaining Time> <Blend Function (Linear, Cubic, Ease In, Ease Out, Ease In Out, Midway Step)> <Blend Exp> <Lock Outgoing (true or false)>", 0);

    gameWrapper->HookEventWithCallerPost<ActorWrapper>(
        "Function ProjectX.CameraStateBlender_X.TransitionToState",
        [this](const ActorWrapper& caller, ...) {
            OnCameraBlenderTransition(CameraStateBlenderWrapper{ caller.memory_address });
        });
}

void CustomCameraTransition::OnCameraBlenderTransition(const CameraStateBlenderWrapper& blender)
{
    if (overrideTransition)
    {
        transitionCount++;

        auto transition = blender.GetTransition();
        transition.blend_params.blend_time = blendTime;
        transition.blend_params.blend_exp = blendExp;
        transition.blend_params.lock_outgoing = lockOutgoing;
        transition.blend_params.blend_function = static_cast<unsigned char>(blendFunction);
        transition.remaining_time = remainingTime;
        blender.SetTransition(transition);

        //LOG("override transition");

        if (transitionCount == 2)
        {
            overrideTransition = false;
            transitionCount = 0;
        }
    }
}

//SetNextCamTransition <Blend Time> <Remaining Time> <Blend Function (Linear, Cubic, Ease In, Ease Out, Ease In Out, Midway Step)> <Blend Exp> <Lock Outgoing (true or false)>
void CustomCameraTransition::SetNextTransition(std::vector<std::string> args)
{
    if (args.size() < 6)
    {
        cvarManager->log("Not enough arguments provided. Usage: SetNextCamTransition <Blend Time> <Remaining Time> <Blend Function (Linear, Cubic, Ease In, Ease Out, Ease In Out, Midway Step)> <Blend Exp> <Lock Outgoing (true or false)>");
        return;
    }

    blendTime = std::stof(args[1]);
    remainingTime = std::stof(args[2]);
    blendFunction = StringToBlendFunction(args[3]);
    blendExp = std::stof(args[4]);
    lockOutgoing = (args[5] == "true");

    overrideTransition = true;
    transitionCount = 0;
}

ViewTargetBlendFunction CustomCameraTransition::StringToBlendFunction(const std::string& str)
{
	for (const auto& [value, name] : blendFunctionMap)
    {
		if (name == str)
            return value;
	}

	LOG("[ERROR]Couldn't find blend function: {}, using default Linear", str);
	return ViewTargetBlendFunction::VTBlend_Linear;
}
