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

	ImGui::Text("Command usage: SetNextCamTransition <Blend Time> <Remaining Time> <Blend Function (Values: Linear, Cubic, Ease In, Ease Out, Ease In Out, Midway Step)> <Blend Exp> <Lock Outgoing (true or false)>");
	ImGui::Text("Example:");
	ImGui::SameLine();
	static std::string exampleCommand = "SetNextCamTransition 1.000 1.000 \"Ease In Out\" 2.000 true";
	ImGui::SetNextItemWidth(450.f);
	ImGui::InputText("##ExampleCommand", &exampleCommand, ImGuiInputTextFlags_ReadOnly);
}