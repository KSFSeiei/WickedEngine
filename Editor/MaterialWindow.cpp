#include "stdafx.h"
#include "MaterialWindow.h"
#include "Editor.h"

#include <sstream>

using namespace std;
using namespace wiGraphics;
using namespace wiECS;
using namespace wiScene;

void MaterialWindow::Create(EditorComponent* editor)
{
	wiWindow::Create("Material Window");
	SetSize(XMFLOAT2(720, 600));

	float x = 670, y = 0;
	float hei = 18;
	float step = hei + 2;

	shadowCasterCheckBox.Create("Cast Shadow: ");
	shadowCasterCheckBox.SetTooltip("The subset will contribute to the scene shadows if enabled.");
	shadowCasterCheckBox.SetPos(XMFLOAT2(670, y += step));
	shadowCasterCheckBox.SetSize(XMFLOAT2(hei, hei));
	shadowCasterCheckBox.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetCastShadow(args.bValue);
	});
	AddWidget(&shadowCasterCheckBox);

	useVertexColorsCheckBox.Create("Use vertex colors: ");
	useVertexColorsCheckBox.SetTooltip("Enable if you want to render the mesh with vertex colors (must have appropriate vertex buffer)");
	useVertexColorsCheckBox.SetPos(XMFLOAT2(670, y += step));
	useVertexColorsCheckBox.SetSize(XMFLOAT2(hei, hei));
	useVertexColorsCheckBox.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetUseVertexColors(args.bValue);
	});
	AddWidget(&useVertexColorsCheckBox);

	specularGlossinessCheckBox.Create("Specular-glossiness workflow: ");
	specularGlossinessCheckBox.SetTooltip("If enabled, surface map will be viewed like it contains specular color (RGB) and smoothness (A)");
	specularGlossinessCheckBox.SetPos(XMFLOAT2(670, y += step));
	specularGlossinessCheckBox.SetSize(XMFLOAT2(hei, hei));
	specularGlossinessCheckBox.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetUseSpecularGlossinessWorkflow(args.bValue);
		SetEntity(entity);
	});
	AddWidget(&specularGlossinessCheckBox);

	occlusionPrimaryCheckBox.Create("Occlusion - Primary: ");
	occlusionPrimaryCheckBox.SetTooltip("If enabled, surface map's RED channel will be used as occlusion map");
	occlusionPrimaryCheckBox.SetPos(XMFLOAT2(670, y += step));
	occlusionPrimaryCheckBox.SetSize(XMFLOAT2(hei, hei));
	occlusionPrimaryCheckBox.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetOcclusionEnabled_Primary(args.bValue);
	});
	AddWidget(&occlusionPrimaryCheckBox);

	occlusionSecondaryCheckBox.Create("Occlusion - Secondary: ");
	occlusionSecondaryCheckBox.SetTooltip("If enabled, occlusion map's RED channel will be used as occlusion map");
	occlusionSecondaryCheckBox.SetPos(XMFLOAT2(670, y += step));
	occlusionSecondaryCheckBox.SetSize(XMFLOAT2(hei, hei));
	occlusionSecondaryCheckBox.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetOcclusionEnabled_Secondary(args.bValue);
	});
	AddWidget(&occlusionSecondaryCheckBox);

	windCheckBox.Create("Wind: ");
	windCheckBox.SetTooltip("If enabled, vertex wind weights will affect how much wind offset affects the subset.");
	windCheckBox.SetPos(XMFLOAT2(670, y += step));
	windCheckBox.SetSize(XMFLOAT2(hei, hei));
	windCheckBox.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetUseWind(args.bValue);
		});
	AddWidget(&windCheckBox);



	x = 520;
	float wid = 170;


	shaderTypeComboBox.Create("Shader: ");
	shaderTypeComboBox.SetTooltip("Select a shader for this material. \nCustom shaders (*) will also show up here (see wiRenderer:RegisterCustomShader() for more info.)\nNote that custom shaders (*) can't select between blend modes, as they are created with an explicit blend mode.");
	shaderTypeComboBox.SetPos(XMFLOAT2(x, y += step));
	shaderTypeComboBox.SetSize(XMFLOAT2(wid, hei));
	shaderTypeComboBox.OnSelect([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			if (args.iValue >= MaterialComponent::SHADERTYPE_COUNT)
			{
				material->SetCustomShaderID(args.iValue - MaterialComponent::SHADERTYPE_COUNT);
				blendModeComboBox.SetEnabled(false);
			}
			else
			{
				material->shaderType = (MaterialComponent::SHADERTYPE)args.userdata;
				material->SetCustomShaderID(-1);
				blendModeComboBox.SetEnabled(true);
			}
		}
		});
	shaderTypeComboBox.AddItem("PBR", MaterialComponent::SHADERTYPE_PBR);
	shaderTypeComboBox.AddItem("PBR + Planar reflections", MaterialComponent::SHADERTYPE_PBR_PLANARREFLECTION);
	shaderTypeComboBox.AddItem("PBR + Par. occl. mapping", MaterialComponent::SHADERTYPE_PBR_PARALLAXOCCLUSIONMAPPING);
	shaderTypeComboBox.AddItem("PBR + Anisotropic", MaterialComponent::SHADERTYPE_PBR_ANISOTROPIC);
	shaderTypeComboBox.AddItem("PBR + Cloth", MaterialComponent::SHADERTYPE_PBR_CLOTH);
	shaderTypeComboBox.AddItem("PBR + Clear coat", MaterialComponent::SHADERTYPE_PBR_CLEARCOAT);
	shaderTypeComboBox.AddItem("PBR + Cloth + Clear coat", MaterialComponent::SHADERTYPE_PBR_CLOTH_CLEARCOAT);
	shaderTypeComboBox.AddItem("Water", MaterialComponent::SHADERTYPE_WATER);
	shaderTypeComboBox.AddItem("Cartoon", MaterialComponent::SHADERTYPE_CARTOON);
	shaderTypeComboBox.AddItem("Unlit", MaterialComponent::SHADERTYPE_UNLIT);
	for (auto& x : wiRenderer::GetCustomShaders())
	{
		shaderTypeComboBox.AddItem("*" + x.name);
	}
	shaderTypeComboBox.SetEnabled(false);
	shaderTypeComboBox.SetMaxVisibleItemCount(5);
	AddWidget(&shaderTypeComboBox);

	blendModeComboBox.Create("Blend mode: ");
	blendModeComboBox.SetPos(XMFLOAT2(x, y += step));
	blendModeComboBox.SetSize(XMFLOAT2(wid, hei));
	blendModeComboBox.OnSelect([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr && args.iValue >= 0)
		{
			material->userBlendMode = (BLENDMODE)args.iValue;
		}
		});
	blendModeComboBox.AddItem("Opaque");
	blendModeComboBox.AddItem("Alpha");
	blendModeComboBox.AddItem("Premultiplied");
	blendModeComboBox.AddItem("Additive");
	blendModeComboBox.SetEnabled(false);
	blendModeComboBox.SetTooltip("Set the blend mode of the material.");
	AddWidget(&blendModeComboBox);

	shadingRateComboBox.Create("Shading Rate: ");
	shadingRateComboBox.SetTooltip("Select shading rate for this material. \nSelecting larger shading rate will decrease rendering quality of this material, \nbut increases performance.\nRequires hardware support for variable shading rate");
	shadingRateComboBox.SetPos(XMFLOAT2(x, y += step));
	shadingRateComboBox.SetSize(XMFLOAT2(wid, hei));
	shadingRateComboBox.OnSelect([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->shadingRate = (SHADING_RATE)args.iValue;
		}
		});
	shadingRateComboBox.AddItem("1X1");
	shadingRateComboBox.AddItem("1X2");
	shadingRateComboBox.AddItem("2X1");
	shadingRateComboBox.AddItem("2X2");
	shadingRateComboBox.AddItem("2X4");
	shadingRateComboBox.AddItem("4X2");
	shadingRateComboBox.AddItem("4X4");
	shadingRateComboBox.SetEnabled(false);
	shadingRateComboBox.SetMaxVisibleItemCount(4);
	AddWidget(&shadingRateComboBox);




	// Sliders:
	wid = 150;

	normalMapSlider.Create(0, 4, 1, 4000, "Normalmap: ");
	normalMapSlider.SetTooltip("How much the normal map should distort the face normals (bumpiness).");
	normalMapSlider.SetSize(XMFLOAT2(wid, hei));
	normalMapSlider.SetPos(XMFLOAT2(x, y += step));
	normalMapSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetNormalMapStrength(args.fValue);
	});
	AddWidget(&normalMapSlider);

	roughnessSlider.Create(0, 1, 0.5f, 1000, "Roughness: ");
	roughnessSlider.SetTooltip("Adjust the surface roughness. Rough surfaces are less shiny, more matte.");
	roughnessSlider.SetSize(XMFLOAT2(wid, hei));
	roughnessSlider.SetPos(XMFLOAT2(x, y += step));
	roughnessSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetRoughness(args.fValue);
	});
	AddWidget(&roughnessSlider);

	reflectanceSlider.Create(0, 1, 0.5f, 1000, "Reflectance: ");
	reflectanceSlider.SetTooltip("Adjust the overall surface reflectivity.\nNote: this is not available in specular-glossiness workflow");
	reflectanceSlider.SetSize(XMFLOAT2(wid, hei));
	reflectanceSlider.SetPos(XMFLOAT2(x, y += step));
	reflectanceSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetReflectance(args.fValue);
	});
	AddWidget(&reflectanceSlider);

	metalnessSlider.Create(0, 1, 0.0f, 1000, "Metalness: ");
	metalnessSlider.SetTooltip("The more metal-like the surface is, the more the its color will contribute to the reflection color.\nNote: this is not available in specular-glossiness workflow");
	metalnessSlider.SetSize(XMFLOAT2(wid, hei));
	metalnessSlider.SetPos(XMFLOAT2(x, y += step));
	metalnessSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetMetalness(args.fValue);
	});
	AddWidget(&metalnessSlider);

	alphaRefSlider.Create(0, 1, 1.0f, 1000, "AlphaRef: ");
	alphaRefSlider.SetTooltip("Adjust the alpha cutoff threshold. Alpha cutout can affect performance");
	alphaRefSlider.SetSize(XMFLOAT2(wid, hei));
	alphaRefSlider.SetPos(XMFLOAT2(x, y += step));
	alphaRefSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetAlphaRef(args.fValue);
	});
	AddWidget(&alphaRefSlider);

	emissiveSlider.Create(0, 1, 0.0f, 1000, "Emissive: ");
	emissiveSlider.SetTooltip("Adjust the light emission of the surface. The color of the light emitted is that of the color of the material.");
	emissiveSlider.SetSize(XMFLOAT2(wid, hei));
	emissiveSlider.SetPos(XMFLOAT2(x, y += step));
	emissiveSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetEmissiveStrength(args.fValue);
	});
	AddWidget(&emissiveSlider);

	transmissionSlider.Create(0, 1.0f, 0.02f, 1000, "Transmission: ");
	transmissionSlider.SetTooltip("Adjust the transmissiveness. More transmissiveness means more diffuse light is transmitted instead of absorbed.");
	transmissionSlider.SetSize(XMFLOAT2(wid, hei));
	transmissionSlider.SetPos(XMFLOAT2(x, y += step));
	transmissionSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetTransmissionAmount(args.fValue);
		});
	AddWidget(&transmissionSlider);

	refractionSlider.Create(0, 1, 0, 1000, "Refraction: ");
	refractionSlider.SetTooltip("Adjust the refraction amount for transmissive materials.");
	refractionSlider.SetSize(XMFLOAT2(wid, hei));
	refractionSlider.SetPos(XMFLOAT2(x, y += step));
	refractionSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetRefractionAmount(args.fValue);
		});
	AddWidget(&refractionSlider);

	pomSlider.Create(0, 0.1f, 0.0f, 1000, "Parallax Occlusion Mapping: ");
	pomSlider.SetTooltip("Adjust how much the bump map should modulate the surface parallax effect. \nOnly works with PBR + Parallax shader.");
	pomSlider.SetSize(XMFLOAT2(wid, hei));
	pomSlider.SetPos(XMFLOAT2(x, y += step));
	pomSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetParallaxOcclusionMapping(args.fValue);
	});
	AddWidget(&pomSlider);

	displacementMappingSlider.Create(0, 0.1f, 0.0f, 1000, "Displacement Mapping: ");
	displacementMappingSlider.SetTooltip("Adjust how much the bump map should modulate the geometry when using tessellation.");
	displacementMappingSlider.SetSize(XMFLOAT2(wid, hei));
	displacementMappingSlider.SetPos(XMFLOAT2(x, y += step));
	displacementMappingSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetDisplacementMapping(args.fValue);
	});
	AddWidget(&displacementMappingSlider);

	subsurfaceScatteringSlider.Create(0, 2, 0.0f, 1000, "Subsurface Scattering: ");
	subsurfaceScatteringSlider.SetTooltip("Subsurface scattering amount. \nYou can also adjust the subsurface color by selecting it in the color picker");
	subsurfaceScatteringSlider.SetSize(XMFLOAT2(wid, hei));
	subsurfaceScatteringSlider.SetPos(XMFLOAT2(x, y += step));
	subsurfaceScatteringSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
			material->SetSubsurfaceScatteringAmount(args.fValue);
	});
	AddWidget(&subsurfaceScatteringSlider);

	texAnimFrameRateSlider.Create(0, 60, 0, 60, "Texcoord anim FPS: ");
	texAnimFrameRateSlider.SetTooltip("Adjust the texture animation frame rate (frames per second). Any value above 0 will make the material dynamic.");
	texAnimFrameRateSlider.SetSize(XMFLOAT2(wid, hei));
	texAnimFrameRateSlider.SetPos(XMFLOAT2(x, y += step));
	texAnimFrameRateSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->texAnimFrameRate = args.fValue;
		}
	});
	AddWidget(&texAnimFrameRateSlider);

	texAnimDirectionSliderU.Create(-0.05f, 0.05f, 0, 1000, "Texcoord anim U: ");
	texAnimDirectionSliderU.SetTooltip("Adjust the texture animation speed along the U direction in texture space.");
	texAnimDirectionSliderU.SetSize(XMFLOAT2(wid, hei));
	texAnimDirectionSliderU.SetPos(XMFLOAT2(x, y += step));
	texAnimDirectionSliderU.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->texAnimDirection.x = args.fValue;
		}
	});
	AddWidget(&texAnimDirectionSliderU);

	texAnimDirectionSliderV.Create(-0.05f, 0.05f, 0, 1000, "Texcoord anim V: ");
	texAnimDirectionSliderV.SetTooltip("Adjust the texture animation speed along the V direction in texture space.");
	texAnimDirectionSliderV.SetSize(XMFLOAT2(wid, hei));
	texAnimDirectionSliderV.SetPos(XMFLOAT2(x, y += step));
	texAnimDirectionSliderV.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->texAnimDirection.y = args.fValue;
		}
	});
	AddWidget(&texAnimDirectionSliderV);

	texMulSliderX.Create(0.01f, 10.0f, 0, 1000, "Texture TileSize X: ");
	texMulSliderX.SetTooltip("Adjust the texture mapping size.");
	texMulSliderX.SetSize(XMFLOAT2(wid, hei));
	texMulSliderX.SetPos(XMFLOAT2(x, y += step));
	texMulSliderX.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetDirty();
			material->texMulAdd.x = args.fValue;
		}
	});
	AddWidget(&texMulSliderX);

	texMulSliderY.Create(0.01f, 10.0f, 0, 1000, "Texture TileSize Y: ");
	texMulSliderY.SetTooltip("Adjust the texture mapping size.");
	texMulSliderY.SetSize(XMFLOAT2(wid, hei));
	texMulSliderY.SetPos(XMFLOAT2(x, y += step));
	texMulSliderY.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetDirty();
			material->texMulAdd.y = args.fValue;
		}
	});
	AddWidget(&texMulSliderY);


	sheenRoughnessSlider.Create(0, 1, 0, 1000, "Sheen Roughness: ");
	sheenRoughnessSlider.SetTooltip("This affects roughness of sheen layer for cloth shading.");
	sheenRoughnessSlider.SetSize(XMFLOAT2(wid, hei));
	sheenRoughnessSlider.SetPos(XMFLOAT2(x, y += step));
	sheenRoughnessSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetSheenRoughness(args.fValue);
		}
		});
	AddWidget(&sheenRoughnessSlider);

	clearcoatSlider.Create(0, 1, 0, 1000, "Clearcoat: ");
	clearcoatSlider.SetTooltip("This affects clearcoat layer blending.");
	clearcoatSlider.SetSize(XMFLOAT2(wid, hei));
	clearcoatSlider.SetPos(XMFLOAT2(x, y += step));
	clearcoatSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetClearcoatFactor(args.fValue);
		}
		});
	AddWidget(&clearcoatSlider);

	clearcoatRoughnessSlider.Create(0, 1, 0, 1000, "Clearcoat Roughness: ");
	clearcoatRoughnessSlider.SetTooltip("This affects roughness of clear coat layer.");
	clearcoatRoughnessSlider.SetSize(XMFLOAT2(wid, hei));
	clearcoatRoughnessSlider.SetPos(XMFLOAT2(x, y += step));
	clearcoatRoughnessSlider.OnSlide([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetClearcoatRoughness(args.fValue);
		}
		});
	AddWidget(&clearcoatRoughnessSlider);


	// Textures:

	x = 10;
	y = 0;
	hei = 20;
	step = hei + 2;
	float uvset_offset = 385;

	materialNameField.Create("MaterialName");
	materialNameField.SetTooltip("Set a name for the material...");
	materialNameField.SetPos(XMFLOAT2(10, y += step));
	materialNameField.SetSize(XMFLOAT2(300, hei));
	materialNameField.OnInputAccepted([=](wiEventArgs args) {
		NameComponent* name = wiScene::GetScene().names.GetComponent(entity);
		if (name != nullptr)
		{
			*name = args.sValue;

			editor->RefreshSceneGraphView();
		}
	});
	AddWidget(&materialNameField);

	newMaterialButton.Create("New Material");
	newMaterialButton.SetPos(XMFLOAT2(10 + 5 + 300, y));
	newMaterialButton.SetSize(XMFLOAT2(100, hei));
	newMaterialButton.OnClick([=](wiEventArgs args) {
		Scene& scene = wiScene::GetScene();
		Entity entity = scene.Entity_CreateMaterial("editorMaterial");
		editor->ClearSelected();
		editor->AddSelected(entity);
		editor->RefreshSceneGraphView();
		SetEntity(entity);
	});
	AddWidget(&newMaterialButton);

	texture_baseColor_Label.Create("BaseColorMap: ");
	texture_baseColor_Label.SetPos(XMFLOAT2(x, y += step));
	texture_baseColor_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_baseColor_Label);

	texture_baseColor_Button.Create("BaseColor");
	texture_baseColor_Button.SetText("");
	texture_baseColor_Button.SetTooltip("Load the basecolor texture. RGB: Albedo Base Color, A: Opacity");
	texture_baseColor_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_baseColor_Button.SetSize(XMFLOAT2(260, 20));
	texture_baseColor_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->baseColorMap != nullptr)
		{
			material->baseColorMap = nullptr;
			material->baseColorMapName = "";
			material->SetDirty();
			texture_baseColor_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->baseColorMap = wiResourceManager::Load(fileName);
					material->baseColorMapName = fileName;
					material->SetDirty();
					texture_baseColor_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
				});
			});
		}
	});
	AddWidget(&texture_baseColor_Button);

	texture_baseColor_uvset_Field.Create("uvset_baseColor");
	texture_baseColor_uvset_Field.SetText("");
	texture_baseColor_uvset_Field.SetTooltip("uv set number");
	texture_baseColor_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_baseColor_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_baseColor_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_BaseColorMap(args.iValue);
		}
	});
	AddWidget(&texture_baseColor_uvset_Field);



	texture_normal_Label.Create("NormalMap: ");
	texture_normal_Label.SetPos(XMFLOAT2(x, y += step));
	texture_normal_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_normal_Label);

	texture_normal_Button.Create("NormalMap");
	texture_normal_Button.SetText("");
	texture_normal_Button.SetTooltip("Load the normalmap texture. RGB: Normal");
	texture_normal_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_normal_Button.SetSize(XMFLOAT2(260, 20));
	texture_normal_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->normalMap != nullptr)
		{
			material->normalMap = nullptr;
			material->normalMapName = "";
			material->SetDirty();
			texture_normal_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->normalMap = wiResourceManager::Load(fileName);
					material->normalMapName = fileName;
					material->SetDirty();
					texture_normal_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
				});
			});
		}
	});
	AddWidget(&texture_normal_Button);

	texture_normal_uvset_Field.Create("uvset_normal");
	texture_normal_uvset_Field.SetText("");
	texture_normal_uvset_Field.SetTooltip("uv set number");
	texture_normal_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_normal_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_normal_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_NormalMap(args.iValue);
		}
	});
	AddWidget(&texture_normal_uvset_Field);



	texture_surface_Label.Create("SurfaceMap: ");
	texture_surface_Label.SetPos(XMFLOAT2(x, y += step));
	texture_surface_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_surface_Label);

	texture_surface_Button.Create("SurfaceMap");
	texture_surface_Button.SetText("");
	texture_surface_Button.SetTooltip("Load the surface property texture.\nDefault workflow: R: Occlusion, G: Roughness, B: Metalness, A: Reflectance\nSpecular-glossiness workflow: RGB: Specular color (f0), A: smoothness");
	texture_surface_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_surface_Button.SetSize(XMFLOAT2(260, 20));
	texture_surface_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->surfaceMap != nullptr)
		{
			material->surfaceMap = nullptr;
			material->surfaceMapName = "";
			material->SetDirty();
			texture_surface_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->surfaceMap = wiResourceManager::Load(fileName);
					material->surfaceMapName = fileName;
					material->SetDirty();
					texture_surface_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
				});
			});
		}
	});
	AddWidget(&texture_surface_Button);

	texture_surface_uvset_Field.Create("uvset_surface");
	texture_surface_uvset_Field.SetText("");
	texture_surface_uvset_Field.SetTooltip("uv set number");
	texture_surface_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_surface_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_surface_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_SurfaceMap(args.iValue);
		}
	});
	AddWidget(&texture_surface_uvset_Field);



	texture_emissive_Label.Create("EmissiveMap: ");
	texture_emissive_Label.SetPos(XMFLOAT2(x, y += step));
	texture_emissive_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_emissive_Label);

	texture_emissive_Button.Create("EmissiveMap");
	texture_emissive_Button.SetText("");
	texture_emissive_Button.SetTooltip("Load the emissive map texture.");
	texture_emissive_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_emissive_Button.SetSize(XMFLOAT2(260, 20));
	texture_emissive_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->emissiveMap != nullptr)
		{
			material->emissiveMap = nullptr;
			material->emissiveMapName = "";
			material->SetDirty();
			texture_emissive_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->emissiveMap = wiResourceManager::Load(fileName);
					material->emissiveMapName = fileName;
					material->SetDirty();
					texture_emissive_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
				});
			});
		}
	});
	AddWidget(&texture_emissive_Button);

	texture_emissive_uvset_Field.Create("uvset_emissive");
	texture_emissive_uvset_Field.SetText("");
	texture_emissive_uvset_Field.SetTooltip("uv set number");
	texture_emissive_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_emissive_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_emissive_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_EmissiveMap(args.iValue);
		}
		});
	AddWidget(&texture_emissive_uvset_Field);



	texture_displacement_Label.Create("DisplacementMap: ");
	texture_displacement_Label.SetPos(XMFLOAT2(x, y += step));
	texture_displacement_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_displacement_Label);

	texture_displacement_Button.Create("DisplacementMap");
	texture_displacement_Button.SetText("");
	texture_displacement_Button.SetTooltip("Load the displacement map texture.");
	texture_displacement_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_displacement_Button.SetSize(XMFLOAT2(260, 20));
	texture_displacement_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->displacementMap != nullptr)
		{
			material->displacementMap = nullptr;
			material->displacementMapName = "";
			material->SetDirty();
			texture_displacement_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->displacementMap = wiResourceManager::Load(fileName);
					material->displacementMapName = fileName;
					material->SetDirty();
					texture_displacement_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
				});
			});
		}
	});
	AddWidget(&texture_displacement_Button);

	texture_displacement_uvset_Field.Create("uvset_displacement");
	texture_displacement_uvset_Field.SetText("");
	texture_displacement_uvset_Field.SetTooltip("uv set number");
	texture_displacement_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_displacement_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_displacement_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_DisplacementMap(args.iValue);
		}
	});
	AddWidget(&texture_displacement_uvset_Field);




	texture_occlusion_Label.Create("OcclusionMap: ");
	texture_occlusion_Label.SetPos(XMFLOAT2(x, y += step));
	texture_occlusion_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_occlusion_Label);

	texture_occlusion_Button.Create("OcclusionMap");
	texture_occlusion_Button.SetText("");
	texture_occlusion_Button.SetTooltip("Load the occlusion map texture. R: occlusion factor");
	texture_occlusion_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_occlusion_Button.SetSize(XMFLOAT2(260, 20));
	texture_occlusion_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->occlusionMap != nullptr)
		{
			material->occlusionMap = nullptr;
			material->occlusionMapName = "";
			material->SetDirty();
			texture_occlusion_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->occlusionMap = wiResourceManager::Load(fileName);
					material->occlusionMapName = fileName;
					material->SetDirty();
					texture_occlusion_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
				});
			});
		}
	});
	AddWidget(&texture_occlusion_Button);

	texture_occlusion_uvset_Field.Create("uvset_occlusion");
	texture_occlusion_uvset_Field.SetText("");
	texture_occlusion_uvset_Field.SetTooltip("uv set number");
	texture_occlusion_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_occlusion_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_occlusion_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_OcclusionMap(args.iValue);
		}
	});
	AddWidget(&texture_occlusion_uvset_Field);




	texture_transmission_Label.Create("TransmissionMap: ");
	texture_transmission_Label.SetPos(XMFLOAT2(x, y += step));
	texture_transmission_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_transmission_Label);

	texture_transmission_Button.Create("TransmissionMap");
	texture_transmission_Button.SetText("");
	texture_transmission_Button.SetTooltip("Load the transmission map texture. R: transmission factor");
	texture_transmission_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_transmission_Button.SetSize(XMFLOAT2(260, 20));
	texture_transmission_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->transmissionMap != nullptr)
		{
			material->transmissionMap = nullptr;
			material->transmissionMapName = "";
			material->SetDirty();
			texture_transmission_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->transmissionMap = wiResourceManager::Load(fileName);
					material->transmissionMapName = fileName;
					material->SetDirty();
					texture_transmission_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
					});
				});
		}
		});
	AddWidget(&texture_transmission_Button);

	texture_transmission_uvset_Field.Create("uvset_transmission");
	texture_transmission_uvset_Field.SetText("");
	texture_transmission_uvset_Field.SetTooltip("uv set number");
	texture_transmission_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_transmission_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_transmission_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_TransmissionMap(args.iValue);
		}
		});
	AddWidget(&texture_transmission_uvset_Field);




	texture_sheenColor_Label.Create("SheenColorMap: ");
	texture_sheenColor_Label.SetPos(XMFLOAT2(x, y += step));
	texture_sheenColor_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_sheenColor_Label);

	texture_sheenColor_Button.Create("SheenColorMap");
	texture_sheenColor_Button.SetText("");
	texture_sheenColor_Button.SetTooltip("Load the sheen color texture (for cloth shader). RGB: sheen color");
	texture_sheenColor_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_sheenColor_Button.SetSize(XMFLOAT2(260, 20));
	texture_sheenColor_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->sheenColorMap != nullptr)
		{
			material->sheenColorMap = nullptr;
			material->sheenColorMapName = "";
			material->SetDirty();
			texture_sheenColor_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->sheenColorMap = wiResourceManager::Load(fileName);
					material->sheenColorMapName = fileName;
					material->SetDirty();
					texture_sheenColor_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
					});
				});
		}
		});
	AddWidget(&texture_sheenColor_Button);

	texture_sheenColor_uvset_Field.Create("uvset_sheenColor");
	texture_sheenColor_uvset_Field.SetText("");
	texture_sheenColor_uvset_Field.SetTooltip("uv set number");
	texture_sheenColor_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_sheenColor_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_sheenColor_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_SheenColorMap(args.iValue);
		}
		});
	AddWidget(&texture_sheenColor_uvset_Field);




	texture_sheenRoughness_Label.Create("SheenRoughMap: ");
	texture_sheenRoughness_Label.SetPos(XMFLOAT2(x, y += step));
	texture_sheenRoughness_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_sheenRoughness_Label);

	texture_sheenRoughness_Button.Create("SheenRoughnessMap");
	texture_sheenRoughness_Button.SetText("");
	texture_sheenRoughness_Button.SetTooltip("Load the sheen roughness texture. A: roughness");
	texture_sheenRoughness_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_sheenRoughness_Button.SetSize(XMFLOAT2(260, 20));
	texture_sheenRoughness_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->sheenRoughnessMap != nullptr)
		{
			material->sheenRoughnessMap = nullptr;
			material->sheenRoughnessMapName = "";
			material->SetDirty();
			texture_sheenRoughness_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->sheenRoughnessMap = wiResourceManager::Load(fileName);
					material->sheenRoughnessMapName = fileName;
					material->SetDirty();
					texture_sheenRoughness_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
					});
				});
		}
		});
	AddWidget(&texture_sheenRoughness_Button);

	texture_sheenRoughness_uvset_Field.Create("uvset_sheenRoughness");
	texture_sheenRoughness_uvset_Field.SetText("");
	texture_sheenRoughness_uvset_Field.SetTooltip("uv set number");
	texture_sheenRoughness_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_sheenRoughness_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_sheenRoughness_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_SheenRoughnessMap(args.iValue);
		}
		});
	AddWidget(&texture_sheenRoughness_uvset_Field);




	texture_clearcoat_Label.Create("ClearcoatMap: ");
	texture_clearcoat_Label.SetPos(XMFLOAT2(x, y += step));
	texture_clearcoat_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_clearcoat_Label);

	texture_clearcoat_Button.Create("ClearcoatMap");
	texture_clearcoat_Button.SetText("");
	texture_clearcoat_Button.SetTooltip("Load the clearcoat factor texture. R: clearcoat factor");
	texture_clearcoat_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_clearcoat_Button.SetSize(XMFLOAT2(260, 20));
	texture_clearcoat_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->clearcoatMap != nullptr)
		{
			material->clearcoatMap = nullptr;
			material->clearcoatMapName = "";
			material->SetDirty();
			texture_clearcoat_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->clearcoatMap = wiResourceManager::Load(fileName);
					material->clearcoatMapName = fileName;
					material->SetDirty();
					texture_clearcoat_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
					});
				});
		}
		});
	AddWidget(&texture_clearcoat_Button);

	texture_clearcoat_uvset_Field.Create("uvset_clearcoat");
	texture_clearcoat_uvset_Field.SetText("");
	texture_clearcoat_uvset_Field.SetTooltip("uv set number");
	texture_clearcoat_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_clearcoat_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_clearcoat_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_ClearcoatMap(args.iValue);
		}
		});
	AddWidget(&texture_clearcoat_uvset_Field);




	texture_clearcoatRoughness_Label.Create("ClearcoatRoughMap: ");
	texture_clearcoatRoughness_Label.SetPos(XMFLOAT2(x, y += step));
	texture_clearcoatRoughness_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_clearcoatRoughness_Label);

	texture_clearcoatRoughness_Button.Create("ClearcoatRoughnessMap");
	texture_clearcoatRoughness_Button.SetText("");
	texture_clearcoatRoughness_Button.SetTooltip("Load the clearcoat roughness texture. G: roughness");
	texture_clearcoatRoughness_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_clearcoatRoughness_Button.SetSize(XMFLOAT2(260, 20));
	texture_clearcoatRoughness_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->clearcoatRoughnessMap != nullptr)
		{
			material->clearcoatRoughnessMap = nullptr;
			material->clearcoatRoughnessMapName = "";
			material->SetDirty();
			texture_clearcoatRoughness_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->clearcoatRoughnessMap = wiResourceManager::Load(fileName);
					material->clearcoatRoughnessMapName = fileName;
					material->SetDirty();
					texture_clearcoatRoughness_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
					});
				});
		}
		});
	AddWidget(&texture_clearcoatRoughness_Button);

	texture_clearcoatRoughness_uvset_Field.Create("uvset_clearcoatRoughness");
	texture_clearcoatRoughness_uvset_Field.SetText("");
	texture_clearcoatRoughness_uvset_Field.SetTooltip("uv set number");
	texture_clearcoatRoughness_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_clearcoatRoughness_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_clearcoatRoughness_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_ClearcoatRoughnessMap(args.iValue);
		}
		});
	AddWidget(&texture_clearcoatRoughness_uvset_Field);




	texture_clearcoatNormal_Label.Create("ClearcoatNormMap: ");
	texture_clearcoatNormal_Label.SetPos(XMFLOAT2(x, y += step));
	texture_clearcoatNormal_Label.SetSize(XMFLOAT2(120, 20));
	AddWidget(&texture_clearcoatNormal_Label);

	texture_clearcoatNormal_Button.Create("ClearcoatNormalMap");
	texture_clearcoatNormal_Button.SetText("");
	texture_clearcoatNormal_Button.SetTooltip("Load the clearcoat normal map texture. RGB: normal");
	texture_clearcoatNormal_Button.SetPos(XMFLOAT2(x + 122, y));
	texture_clearcoatNormal_Button.SetSize(XMFLOAT2(260, 20));
	texture_clearcoatNormal_Button.OnClick([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material == nullptr)
			return;

		if (material->clearcoatNormalMap != nullptr)
		{
			material->clearcoatNormalMap = nullptr;
			material->clearcoatNormalMapName = "";
			material->SetDirty();
			texture_clearcoatNormal_Button.SetText("");
		}
		else
		{
			wiHelper::FileDialogParams params;
			params.type = wiHelper::FileDialogParams::OPEN;
			params.description = "Texture";
			params.extensions.push_back("dds");
			params.extensions.push_back("png");
			params.extensions.push_back("jpg");
			params.extensions.push_back("jpeg");
			params.extensions.push_back("tga");
			params.extensions.push_back("bmp");
			wiHelper::FileDialog(params, [this, material](std::string fileName) {
				wiEvent::Subscribe_Once(SYSTEM_EVENT_THREAD_SAFE_POINT, [=](uint64_t userdata) {
					material->clearcoatNormalMap = wiResourceManager::Load(fileName);
					material->clearcoatNormalMapName = fileName;
					material->SetDirty();
					texture_clearcoatNormal_Button.SetText(wiHelper::GetFileNameFromPath(fileName));
					});
				});
		}
		});
	AddWidget(&texture_clearcoatNormal_Button);

	texture_clearcoatNormal_uvset_Field.Create("uvset_clearcoatNormal");
	texture_clearcoatNormal_uvset_Field.SetText("");
	texture_clearcoatNormal_uvset_Field.SetTooltip("uv set number");
	texture_clearcoatNormal_uvset_Field.SetPos(XMFLOAT2(x + uvset_offset, y));
	texture_clearcoatNormal_uvset_Field.SetSize(XMFLOAT2(20, 20));
	texture_clearcoatNormal_uvset_Field.OnInputAccepted([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			material->SetUVSet_ClearcoatNormalMap(args.iValue);
		}
		});
	AddWidget(&texture_clearcoatNormal_uvset_Field);






	colorComboBox.Create("Color picker mode: ");
	colorComboBox.SetSize(XMFLOAT2(120, hei));
	colorComboBox.SetPos(XMFLOAT2(x + 150, y += step));
	colorComboBox.AddItem("Base color");
	colorComboBox.AddItem("Specular color");
	colorComboBox.AddItem("Emissive color");
	colorComboBox.AddItem("Subsurface color");
	colorComboBox.AddItem("Sheen color");
	colorComboBox.SetTooltip("Choose the destination data of the color picker.");
	AddWidget(&colorComboBox);

	colorPicker.Create("Color", false);
	colorPicker.SetPos(XMFLOAT2(10, y += step));
	colorPicker.SetVisible(true);
	colorPicker.SetEnabled(true);
	colorPicker.OnColorChanged([&](wiEventArgs args) {
		MaterialComponent* material = wiScene::GetScene().materials.GetComponent(entity);
		if (material != nullptr)
		{
			switch (colorComboBox.GetSelected())
			{
			default:
			case 0:
				material->SetBaseColor(args.color.toFloat4());
				break;
			case 1:
				material->SetSpecularColor(args.color.toFloat4());
				break;
			case 2:
			{
				XMFLOAT3 col = args.color.toFloat3();
				material->SetEmissiveColor(XMFLOAT4(col.x, col.y, col.z, material->GetEmissiveStrength()));
			}
			break;
			case 3:
				material->SetSubsurfaceScatteringColor(args.color.toFloat3());
			break;
			case 4:
				material->SetSheenColor(args.color.toFloat3());
				break;
			}
		}
	});
	AddWidget(&colorPicker);


	Translate(XMFLOAT3((float)wiRenderer::GetDevice()->GetScreenWidth() - 880, 120, 0));
	SetVisible(false);

	SetEntity(INVALID_ENTITY);
}



void MaterialWindow::SetEntity(Entity entity)
{
	this->entity = entity;

	Scene& scene = wiScene::GetScene();
	MaterialComponent* material = scene.materials.GetComponent(entity);

	if (material != nullptr)
	{
		SetEnabled(true);

		const NameComponent& name = *scene.names.GetComponent(entity);

		materialNameField.SetValue(name.name);
		shadowCasterCheckBox.SetCheck(material->IsCastingShadow());
		useVertexColorsCheckBox.SetCheck(material->IsUsingVertexColors());
		specularGlossinessCheckBox.SetCheck(material->IsUsingSpecularGlossinessWorkflow());
		occlusionPrimaryCheckBox.SetCheck(material->IsOcclusionEnabled_Primary());
		occlusionSecondaryCheckBox.SetCheck(material->IsOcclusionEnabled_Secondary());
		windCheckBox.SetCheck(material->IsUsingWind());
		normalMapSlider.SetValue(material->normalMapStrength);
		roughnessSlider.SetValue(material->roughness);
		reflectanceSlider.SetValue(material->reflectance);
		metalnessSlider.SetValue(material->metalness);
		transmissionSlider.SetValue(material->transmission);
		refractionSlider.SetValue(material->refraction);
		emissiveSlider.SetValue(material->emissiveColor.w);
		pomSlider.SetValue(material->parallaxOcclusionMapping);
		displacementMappingSlider.SetValue(material->displacementMapping);
		subsurfaceScatteringSlider.SetValue(material->subsurfaceScattering.w);
		texAnimFrameRateSlider.SetValue(material->texAnimFrameRate);
		texAnimDirectionSliderU.SetValue(material->texAnimDirection.x);
		texAnimDirectionSliderV.SetValue(material->texAnimDirection.y);
		texMulSliderX.SetValue(material->texMulAdd.x);
		texMulSliderY.SetValue(material->texMulAdd.y);
		alphaRefSlider.SetValue(material->alphaRef);
		blendModeComboBox.SetSelected((int)material->userBlendMode);
		if (material->GetCustomShaderID() >= 0)
		{
			shaderTypeComboBox.SetSelected(MaterialComponent::SHADERTYPE_COUNT + material->GetCustomShaderID());
		}
		else
		{
			shaderTypeComboBox.SetSelectedByUserdata(material->shaderType);
		}
		shadingRateComboBox.SetSelected((int)material->shadingRate);

		texture_baseColor_Button.SetText(wiHelper::GetFileNameFromPath(material->baseColorMapName));
		texture_normal_Button.SetText(wiHelper::GetFileNameFromPath(material->normalMapName));
		texture_surface_Button.SetText(wiHelper::GetFileNameFromPath(material->surfaceMapName));
		texture_displacement_Button.SetText(wiHelper::GetFileNameFromPath(material->displacementMapName));
		texture_emissive_Button.SetText(wiHelper::GetFileNameFromPath(material->emissiveMapName));
		texture_occlusion_Button.SetText(wiHelper::GetFileNameFromPath(material->occlusionMapName));
		texture_transmission_Button.SetText(wiHelper::GetFileNameFromPath(material->transmissionMapName));
		texture_sheenColor_Button.SetText(wiHelper::GetFileNameFromPath(material->sheenColorMapName));
		texture_sheenRoughness_Button.SetText(wiHelper::GetFileNameFromPath(material->sheenRoughnessMapName));
		texture_clearcoat_Button.SetText(wiHelper::GetFileNameFromPath(material->clearcoatMapName));
		texture_clearcoatRoughness_Button.SetText(wiHelper::GetFileNameFromPath(material->clearcoatRoughnessMapName));
		texture_clearcoatNormal_Button.SetText(wiHelper::GetFileNameFromPath(material->clearcoatNormalMapName));

		texture_baseColor_uvset_Field.SetText(std::to_string(material->uvset_baseColorMap));
		texture_normal_uvset_Field.SetText(std::to_string(material->uvset_normalMap));
		texture_surface_uvset_Field.SetText(std::to_string(material->uvset_surfaceMap));
		texture_displacement_uvset_Field.SetText(std::to_string(material->uvset_displacementMap));
		texture_emissive_uvset_Field.SetText(std::to_string(material->uvset_emissiveMap));
		texture_occlusion_uvset_Field.SetText(std::to_string(material->uvset_occlusionMap));
		texture_transmission_uvset_Field.SetText(std::to_string(material->uvset_transmissionMap));
		texture_sheenColor_uvset_Field.SetText(std::to_string(material->uvset_sheenColorMap));
		texture_sheenRoughness_uvset_Field.SetText(std::to_string(material->uvset_sheenRoughnessMap));
		texture_clearcoat_uvset_Field.SetText(std::to_string(material->uvset_clearcoatMap));
		texture_clearcoatRoughness_uvset_Field.SetText(std::to_string(material->uvset_clearcoatRoughnessMap));
		texture_clearcoatNormal_uvset_Field.SetText(std::to_string(material->uvset_clearcoatNormalMap));


		colorComboBox.SetEnabled(true);
		colorPicker.SetEnabled(true);
		
		switch (colorComboBox.GetSelected())
		{
		default:
		case 0:
			colorPicker.SetPickColor(wiColor::fromFloat4(material->baseColor));
			break;
		case 1:
			colorPicker.SetPickColor(wiColor::fromFloat4(material->specularColor));
			break;
		case 2:
			colorPicker.SetPickColor(wiColor::fromFloat3(XMFLOAT3(material->emissiveColor.x, material->emissiveColor.y, material->emissiveColor.z)));
			break;
		case 3:
			colorPicker.SetPickColor(wiColor::fromFloat3(XMFLOAT3(material->subsurfaceScattering.x, material->subsurfaceScattering.y, material->subsurfaceScattering.z)));
			break;
		case 4:
			colorPicker.SetPickColor(wiColor::fromFloat3(XMFLOAT3(material->sheenColor.x, material->sheenColor.y, material->sheenColor.z)));
			break;
		}

		switch (material->shaderType)
		{
		case MaterialComponent::SHADERTYPE_PBR_ANISOTROPIC:
			pomSlider.SetText("Anisotropy: ");
			pomSlider.SetTooltip("Adjust anisotropy specular effect. \nOnly works with PBR + Anisotropic shader.");
			pomSlider.SetRange(0, 0.99f);
			break;
		case MaterialComponent::SHADERTYPE_PBR_PARALLAXOCCLUSIONMAPPING:
			pomSlider.SetText("Parallax Occlusion Mapping: ");
			pomSlider.SetTooltip("Adjust how much the bump map should modulate the surface parallax effect. \nOnly works with PBR + Parallax shader.");
			pomSlider.SetRange(0, 0.1f);
			break;
		default:
			pomSlider.SetEnabled(false);
			break;
		}

		sheenRoughnessSlider.SetEnabled(false);
		clearcoatSlider.SetEnabled(false);
		clearcoatRoughnessSlider.SetEnabled(false);
		texture_sheenColor_Button.SetEnabled(false);
		texture_sheenColor_uvset_Field.SetEnabled(false);
		texture_sheenRoughness_Button.SetEnabled(false);
		texture_sheenRoughness_uvset_Field.SetEnabled(false);
		texture_clearcoat_Button.SetEnabled(false);
		texture_clearcoat_uvset_Field.SetEnabled(false);
		texture_clearcoatRoughness_Button.SetEnabled(false);
		texture_clearcoatRoughness_uvset_Field.SetEnabled(false);
		texture_clearcoatNormal_Button.SetEnabled(false);
		texture_clearcoatNormal_uvset_Field.SetEnabled(false);
		switch (material->shaderType)
		{
		case MaterialComponent::SHADERTYPE_PBR_CLOTH:
			sheenRoughnessSlider.SetEnabled(true);
			texture_sheenColor_Button.SetEnabled(true);
			texture_sheenColor_uvset_Field.SetEnabled(true);
			texture_sheenRoughness_Button.SetEnabled(true);
			texture_sheenRoughness_uvset_Field.SetEnabled(true);
			break;
		case MaterialComponent::SHADERTYPE_PBR_CLEARCOAT:
			clearcoatSlider.SetEnabled(true);
			clearcoatRoughnessSlider.SetEnabled(true);
			texture_clearcoat_Button.SetEnabled(true);
			texture_clearcoat_uvset_Field.SetEnabled(true);
			texture_clearcoatRoughness_Button.SetEnabled(true);
			texture_clearcoatRoughness_uvset_Field.SetEnabled(true);
			texture_clearcoatNormal_Button.SetEnabled(true);
			texture_clearcoatNormal_uvset_Field.SetEnabled(true);
			break;
		case MaterialComponent::SHADERTYPE_PBR_CLOTH_CLEARCOAT:
			sheenRoughnessSlider.SetEnabled(true);
			clearcoatSlider.SetEnabled(true);
			clearcoatRoughnessSlider.SetEnabled(true);
			texture_sheenColor_Button.SetEnabled(true);
			texture_sheenColor_uvset_Field.SetEnabled(true);
			texture_sheenRoughness_Button.SetEnabled(true);
			texture_sheenRoughness_uvset_Field.SetEnabled(true);
			texture_clearcoat_Button.SetEnabled(true);
			texture_clearcoat_uvset_Field.SetEnabled(true);
			texture_clearcoatRoughness_Button.SetEnabled(true);
			texture_clearcoatRoughness_uvset_Field.SetEnabled(true);
			texture_clearcoatNormal_Button.SetEnabled(true);
			texture_clearcoatNormal_uvset_Field.SetEnabled(true);
			break;
		}
		sheenRoughnessSlider.SetValue(material->sheenRoughness);
		clearcoatSlider.SetValue(material->clearcoat);
		clearcoatRoughnessSlider.SetValue(material->clearcoatRoughness);

		shadingRateComboBox.SetEnabled(wiRenderer::GetDevice()->CheckCapability(GRAPHICSDEVICE_CAPABILITY_VARIABLE_RATE_SHADING));

		if (material->IsUsingSpecularGlossinessWorkflow())
		{
			reflectanceSlider.SetEnabled(false);
			metalnessSlider.SetEnabled(false);
		}
	}
	else
	{
		materialNameField.SetValue("No material selected");
		SetEnabled(false);
		colorComboBox.SetEnabled(false);
		colorPicker.SetEnabled(false);

		texture_baseColor_Button.SetText("");
		texture_normal_Button.SetText("");
		texture_surface_Button.SetText("");
		texture_displacement_Button.SetText("");
		texture_emissive_Button.SetText("");
		texture_occlusion_Button.SetText("");

		texture_baseColor_uvset_Field.SetText("");
		texture_normal_uvset_Field.SetText("");
		texture_surface_uvset_Field.SetText("");
		texture_displacement_uvset_Field.SetText("");
		texture_emissive_uvset_Field.SetText("");
		texture_occlusion_uvset_Field.SetText("");
		texture_transmission_uvset_Field.SetText("");
		texture_sheenColor_uvset_Field.SetText("");
		texture_sheenRoughness_uvset_Field.SetText("");
		texture_clearcoat_uvset_Field.SetText("");
		texture_clearcoatRoughness_uvset_Field.SetText("");
		texture_clearcoatNormal_uvset_Field.SetText("");
	}

	newMaterialButton.SetEnabled(true);
}
