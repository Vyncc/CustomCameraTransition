#include "pch.h"
#include "CustomCameraTransition.h"
#include "bakkesmod/wrappers/Engine/WorldInfoWrapper.h"


BAKKESMOD_PLUGIN(CustomCameraTransition, "CustomCameraTransition", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

void CustomCameraTransition::onLoad()
{
	_globalCvarManager = cvarManager;

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	LOG("Hello notifier!");
	//}, "", 0);

    gameWrapper->HookEventWithCallerPost<ActorWrapper>(
        "Function ProjectX.CameraStateBlender_X.TransitionToState",
        [this](const ActorWrapper& caller, ...) {
            OnCameraBlenderTransition(CameraStateBlenderWrapper{ caller.memory_address });
        });
}

void CustomCameraTransition::OnCameraBlenderTransition(const CameraStateBlenderWrapper& blender)
{
    auto transition = blender.GetTransition();
    transition.blend_params.blend_time = blendTime;
    transition.blend_params.blend_exp = blendExp;
    transition.blend_params.lock_outgoing = lockOutgoing;
	transition.blend_params.blend_function = static_cast<unsigned char>(blendFunction);
    transition.remaining_time = remainingTime;
    blender.SetTransition(transition);
}