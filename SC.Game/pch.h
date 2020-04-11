#pragma once

#pragma push_macro( "_MANAGED" )
#undef _MANAGED

#include <vcclr.h>

#pragma unmanaged
#include <Windows.h>
#include <crtdbg.h>
#include <wrl/client.h>

#include <dxgi1_6.h>
#include <d3d12.h>
#include <d3d11.h>
#include <d3d11on12.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <DirectXMath.h>

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
#include "GlyphBuffer.h"
#include "Vertex.h"
#include "UI.GlyphRenderer.h"
#include "UI.RichTextColorUnknown.h"

/* Buffers */
#include "GeometryBuffer.h"
#include "HDRBuffer.h"

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

inline std::string FormatMessage( HRESULT hr )
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
	case E_ACCESSDENIED:
		return "E_ACCESSDENIED(0x80070005): General access denied error.";
	case DXGI_ERROR_DEVICE_REMOVED:
		return "DXGI_ERROR_DEVICE_REMOVED(0x887A0005): The GPU device instance has been suspended. Use GetDeviceRemovedReason to determine the appropriate action.";
	case DXGI_ERROR_DEVICE_HUNG:
		return "DXGI_ERROR_DEVICE_HUNG(0x887A0006): The GPU will not respond to more commands, most likely because of an invalid command passed by the calling application.";
	case DXGI_ERROR_DEVICE_RESET:
		return "DXGI_ERROR_DEVICE_RESET(0x887A0007): The GPU will not respond to more commands, most likely because some other application submitted invalid commands. The calling application should re-create the device and continue.";
	default:
		return "Unknown HRESULT Error: "s + to_string( hr );
	}
}

inline void HR( HRESULT hr )
{
	using namespace SC;

	if ( FAILED( hr ) )
	{
		if ( hr == DXGI_ERROR_DEVICE_REMOVED )
		{
			throw new std::exception( FormatMessage( hr ).c_str() );
		}
		else
		{
			throw new std::exception( FormatMessage( hr ).c_str() );
		}
	}
}

#pragma managed

#pragma pop_macro( "_MANAGED" )

#include <msclr/marshal.h>

/* Enum */
#include "KeyCode.h"
#include "UI.Anchor.h"
#include "UI.TextAlignment.h"
#include "UI.TextVerticalAlignment.h"

/* Struct */
#include "Ray.h"
#include "UI.DependencyProperty.h"
#include "UI.Thickness.h"

/* EventArgs */
#include "UI.NavigationEventArgs.h"

/* Class */
#include "AppConfiguration.h"
#include "Application.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Time.h"
#include "Input.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Behaviour.h"
#include "Asset.h"
#include "Mesh.h"
#include "UI.DependencyObject.h"
#include "UI.Element.h"
#include "UI.Page.h"
#include "UI.Brush.h"
#include "UI.SolidColorBrush.h"
#include "UI.Shapes.Shape.h"
#include "UI.Shapes.Rectangle.h"
#include "UI.Panel.h"
#include "UI.RelativePanel.h"
#include "UI.TextFormat.h"
#include "UI.TextBlock.h"

inline void Assign( XMFLOAT4X4& left, System::Numerics::Matrix4x4% right )
{
	left._11 = right.M11;
	left._12 = right.M12;
	left._13 = right.M13;
	left._14 = right.M14;

	left._21 = right.M21;
	left._22 = right.M22;
	left._23 = right.M23;
	left._24 = right.M24;

	left._31 = right.M31;
	left._32 = right.M32;
	left._33 = right.M33;
	left._34 = right.M34;

	left._41 = right.M41;
	left._42 = right.M42;
	left._43 = right.M43;
	left._44 = right.M44;
}

inline void Assign( XMFLOAT3& left, System::Numerics::Vector3% right )
{
	left.x = right.X;
	left.y = right.Y;
	left.z = right.Z;
}