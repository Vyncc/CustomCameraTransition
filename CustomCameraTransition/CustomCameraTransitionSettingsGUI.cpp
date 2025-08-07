#include "pch.h"
#include "CustomCameraTransition.h"

void CustomCameraTransition::RenderSettings()
{
	/*ImGui::SliderFloat("Blend Time", &blendTime, 0.f, 10.f);
	ImGui::SliderFloat("Remaining Time", &remainingTime, 0.f, 10.f);

	std::string selectedBlendFunction = blendFunctionMap[blendFunction];
	if(ImGui::BeginCombo("Blend Function", selectedBlendFunction.c_str()))
	{
		for (const auto& [value, name] : blendFunctionMap)
		{
			bool isSelected = (selectedBlendFunction == name);
			if (ImGui::Selectable(name.c_str(), isSelected))
			{
				blendFunction = value;
			}
		}

		ImGui::EndCombo();
	}

	ImGui::SliderFloat("Blend Exp", &blendExp, 0.f, 10.f);
	ImGui::Checkbox("Lock Outgoing", &lockOutgoing);

	ImGui::Separator();*/

	ImGui::Text("Set the camera transition to custom values.");
	ImGui::Text("Usage: SetNextCamTransition <Blend Time> <Remaining Time> <Blend Function (Linear, Cubic, Ease In, EaseOut, EaseInOut, MidwayStep)> <Blend Exp> <Lock Outgoing (true or false)>");
	ImGui::Text("Example:");
	ImGui::SameLine();
	static std::string exampleCommand = "SetCameraTransition 1.000 1.000 EaseInOut 2.000 true";
	ImGui::SetNextItemWidth(330.f);
	ImGui::InputText("##ExampleCommand", &exampleCommand, ImGuiInputTextFlags_ReadOnly);

	ImGui::NewLine();

	ImGui::Text("Use the command");
	ImGui::SameLine();
	static std::string resetCameraTransitionCommand = "ResetCameraTransition";
	ImGui::SetNextItemWidth(140.f);
	ImGui::InputText("##ResetCameraTransitionCommand", &resetCameraTransitionCommand, ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	ImGui::Text("when you're done with the camera transition you wanted to override");
}