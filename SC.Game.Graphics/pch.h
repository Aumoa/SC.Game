#pragma once

#undef _MANAGED

#include <dxgi1_6.h>
#include <d3d12.h>
#include <wrl/client.h>

using Microsoft::WRL::ComPtr;

inline void HR( HRESULT hr )
{
	switch ( hr )
	{
	case E_FAIL:
		throw gcnew System::Exception( "E_FAIL(0x80004005): �ý��ۿ��� ��ó�� �� �� ���� ���ܰ� �߻��Ǿ����ϴ�." );
	default:
		throw gcnew System::Exception( hr.ToString() );
	}
}

namespace SC::Game::Graphics::DXGI
{
	ref class Object;
	ref class Factory;
	ref class Adapter;
	ref class Output;
}

#include "RotationMode.h"

#include "AdapterInfo.h"
#include "OutputQueryInfo.h"

#include "Object.h"
#include "Factory.h"
#include "Adapter.h"
#include "AdapterEnumerator.h"
#include "Output.h"
#include "OutputEnumerator.h"