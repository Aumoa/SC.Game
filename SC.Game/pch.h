//
// Copyright (c) 2019-2020 Aumoa.lib. All right reserved.
#pragma once

#pragma push_macro( "_MANAGED" )
#undef _MANAGED

#include <vcclr.h>

#pragma unmanaged
#include <Windows.h>
#include <crtdbg.h>
#include <wrl/client.h>

#pragma warning( disable: 4635 )

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3d11.h>
#include <d3d11on12.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <DirectXMath.h>
#include "physx/PxPhysicsAPI.h"

using namespace DirectX;

#include <exception>
#include <functional>
#include <string>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <chrono>
#include <filesystem>
#include <variant>
#include <fstream>

using Microsoft::WRL::ComPtr;

#undef CreateWindow

#define vs_property( t, n ) __declspec( property( get = n ## _get, put = n ## _set ) ) t n
#define vs_property_get( t, n ) __declspec( property( get = n ## _get ) ) t n
#define debug_name( x ) x->SetName( L## #x )

/* WinHelper */
#include "Mutex.h"
#include "HEvent.h"

/* DXHelper */
#include "CDevice.h"
#include "CSwapChain.h"
#include "CCommandQueue.h"
#include "CDeviceContext.h"
#include "CRootSignatureDesc.h"
#include "CGraphicsPipelineStateDesc.h"
#include "IntegratedFactory.h"
#include "LargeHeap.h"
#include "Heap.h"
#include "ImmutableHeap.h"
#include "CShaderResourceView.h"

/* Unmanaged */
#include "tag_ShaderInfo.h"
#include "RaycastCallback.h"
#include "GlyphBuffer.h"
#include "Vertex.h"
#include "ContactCallback.h"
#include "Bezier.h"
#include "TextParser.h"
#include "MDLParser.h"
#include "SkinnedMeshRendererQueue.h"
#include "ControllerBehaviourCallback.h"
#include "UI.GlyphRenderer.h"
#include "UI.RichTextColorUnknown.h"
#include "DirectX.Geometry.h"

/* Buffers */
#include "GeometryBuffer.h"
#include "HDRBuffer.h"
#include "HDRComputedBuffer.h"

/* Packages */
#include "App.h"
#include "GameLogic.h"
#include "Graphics.h"
#include "UISystem.h"
#include "ShaderBuilder.h"
#include "GC.h"
#include "HeapAllocator.h"
#include "DescriptorAllocator.h"
#include "VisibleDescriptorAllocator.h"

#pragma managed
inline System::String^ FormatMessage( HRESULT hr )
{
	using namespace std;

	switch ( hr )
	{
	case S_OK:
		return "S_OK(0x00000000): ";
	case E_FAIL:
		return "E_FAIL(0x80004005): Unspecified error.";
	case E_INVALIDARG:
		return "E_INVALIDARG(0x80070057): One or more arguments are invalid.";
	case WINCODEC_ERR_WRONGSTATE:
		return "WINCODEC_ERR_WRONGSTATE(0x88982F04): The codec is in the wrong state.";
	case __HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ):
		return "HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND): The system cannot find the file specified.";
	case __HRESULT_FROM_WIN32( ERROR_PATH_NOT_FOUND ):
		return "HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND): The system cannot find the path specified.";
	case E_ACCESSDENIED:
		return "E_ACCESSDENIED(0x80070005): General access denied error.";
	case DXGI_ERROR_DEVICE_REMOVED:
		return "DXGI_ERROR_DEVICE_REMOVED(0x887A0005): The GPU device instance has been suspended. Use GetDeviceRemovedReason to determine the appropriate action.";
	case DXGI_ERROR_DEVICE_HUNG:
		return "DXGI_ERROR_DEVICE_HUNG(0x887A0006): The GPU will not respond to more commands, most likely because of an invalid command passed by the calling application.";
	case DXGI_ERROR_DEVICE_RESET:
		return "DXGI_ERROR_DEVICE_RESET(0x887A0007): The GPU will not respond to more commands, most likely because some other application submitted invalid commands. The calling application should re-create the device and continue.";
	case 0x8007007B:
		return "(0x8007007B): The filename, directory name or volume label syntax is incorrect.";
	default:
		return System::String::Format( "Unknown HRESULT Error: {0}", hr );
	}
}

inline void ThrowHR( HRESULT hr )
{
	auto exception = gcnew System::Exception( FormatMessage( hr ) );
	exception->HResult = ( int )hr;
	throw exception;
}

#pragma unmanaged
inline void HR( HRESULT hr )
{
	using namespace SC;

	if ( FAILED( hr ) )
	{
		ThrowHR( hr );
	}
}

#pragma managed

#pragma pop_macro( "_MANAGED" )

#include <msclr/marshal.h>
#undef min
#undef max

/* Enum */
#include "KeyCode.h"
#include "TextureFormat.h"
#include "RigidbodyConstraints.h"
#include "CursorLockMode.h"
#include "Tag.h"
#include "CharacterCollisionFlags.h"
#include "UI.Anchor.h"
#include "UI.TextAlignment.h"
#include "UI.TextVerticalAlignment.h"

/* Struct */
#include "Ray.h"
#include "Keyframe.h"
#include "KeyframeQ.h"
#include "KeyframePair.h"
#include "Keyframes.h"
#include "Collision.h"
#include "ContactPoint.h"
#include "Trigger.h"
#include "AnimationTransitionCondition.h"
#include "StateMachine.h"
#include "RaycastHit.h"
#include "UI.DependencyProperty.h"
#include "UI.Thickness.h"

/* EventArgs */
#include "UI.NavigationEventArgs.h"

/* Class */
#include "AppConfiguration.h"
#include "Application.h"
#include "SceneManager.h"
#include "Time.h"
#include "Input.h"
#include "Scene.h"
#include "Cursor.h"

#include "Asset.h"
#include "Mesh.h"
#include "Texture2D.h"
#include "Material.h"
#include "PhysicsMaterial.h"
#include "AnimationClip.h"
#include "AnimationState.h"
#include "AnimatorController.h"
#include "AssetBundle.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Light.h"
#include "Bone.h"
#include "SkinnedMeshRenderer.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "SphereCollider.h"
#include "MeshCollider.h"
#include "ThreadDispatcher.h"
#include "Animator.h"
#include "CharacterController.h"
#include "Behaviour.h"

#include "UI.DependencyObject.h"
#include "UI.Element.h"
#include "UI.Page.h"
#include "UI.Brush.h"
#include "UI.SolidColorBrush.h"
#include "UI.RevealBrush.h"
#include "UI.Shapes.Shape.h"
#include "UI.Shapes.Rectangle.h"
#include "UI.Panel.h"
#include "UI.RelativePanel.h"
#include "UI.TextFormat.h"
#include "UI.TextBlock.h"
#include "UI.Border.h"
#include "UI.Image.h"

/* Exceptions */
#include "ComponentDisconnectedException.h"

/* Packages */
#include "Physics.h"

#include "Assignable.h"

#undef min
#undef max