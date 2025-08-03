#include "pch.h"
#include "CustomCameraTransition.h"

void CustomCameraTransition::RenderSettings()
{
	ImGui::SliderFloat("Blend Time", &blendTime, 0.f, 10.f);
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
}