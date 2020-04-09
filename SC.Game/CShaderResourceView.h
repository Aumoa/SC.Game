#pragma once

namespace SC::Game
{
	class CShaderResourceView
	{
		CShaderResourceView( const CShaderResourceView& ) = delete;
		CShaderResourceView& operator=( const CShaderResourceView& ) = delete;

	public:
		UINT mIndex = -1;

	public:
		CShaderResourceView();
		CShaderResourceView( UINT index );
		CShaderResourceView( CShaderResourceView&& right );
		~CShaderResourceView();

		CShaderResourceView& operator=( CShaderResourceView&& right );
	};
}