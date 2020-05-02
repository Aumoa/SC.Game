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
#include "tag_Vertex.h"
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

/* Exceptions */
#include "ComponentDisconnectedException.h"
#include "WinCodecWrongState.h"
#include "DxgiDeviceRemovedException.h"
#include "DxgiDeviceHungException.h"
#include "DxgiDeviceResetException.h"
#include "PathInvalidException.h"

inline void HR( HRESULT hr )
{
	if ( hr >= 0 ) return;
	switch ( hr )
	{
	case E_FAIL:
		throw gcnew System::Exception( "Unspecified error." );
	case E_INVALIDARG:
		throw gcnew System::ArgumentException( "One or more arguments are invalid." );
	case WINCODEC_ERR_WRONGSTATE:
		throw gcnew SC::Game::WinCodecWrongState( "The codec is in the wrong state." );
	case __HRESULT_FROM_WIN32( ERROR_FILE_NOT_FOUND ):
		throw gcnew System::IO::FileNotFoundException( "The system cannot find the file specified." );
	case __HRESULT_FROM_WIN32( ERROR_PATH_NOT_FOUND ):
		throw gcnew System::IO::FileNotFoundException( "The system cannot find the path specified." );
	case E_ACCESSDENIED:
		throw gcnew System::AccessViolationException( "General access denied error." );
	case DXGI_ERROR_DEVICE_REMOVED:
		throw gcnew SC::Game::DxgiDeviceRemovedException();
	case DXGI_ERROR_DEVICE_HUNG:
		throw gcnew SC::Game::DxgiDeviceHungException();
	case DXGI_ERROR_DEVICE_RESET:
		throw gcnew SC::Game::DxgiDeviceResetException();
	case 0x8007007B:
		throw gcnew SC::Game::PathInvalidException();
	default:
		throw gcnew System::Exception( System::String::Format( "Unknown exception: {0}", hr ) );
	}
}

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
#include "Vertex.h"
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

/* Packages */
#include "Physics.h"

#include "Assignable.h"

#undef min
#undef max