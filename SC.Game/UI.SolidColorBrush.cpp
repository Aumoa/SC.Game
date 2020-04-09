using namespace SC;
using namespace SC::Game::UI;

using namespace System;
using namespace System::Drawing;

using namespace std;

SolidColorBrush::SolidColorBrush( System::Drawing::Color color ) : Brush( 0 )
{
	mConstants->Attribute0[0] = color.R / 255.0f;
	mConstants->Attribute0[1] = color.G / 255.0f;
	mConstants->Attribute0[2] = color.B / 255.0f;
	mConstants->Attribute0[3] = color.A / 255.0f;

	UpdateBuffer();
}

Color SolidColorBrush::Color::get()
{
	int r = ( int )( mConstants->Attribute0[0] * 255.0f );
	int g = ( int )( mConstants->Attribute0[1] * 255.0f );
	int b = ( int )( mConstants->Attribute0[2] * 255.0f );
	int a = ( int )( mConstants->Attribute0[3] * 255.0f );

	return System::Drawing::Color::FromArgb( a, r, g, b );
}

void SolidColorBrush::Color::set( System::Drawing::Color value )
{
	if ( IsFreezed ) throw gcnew System::AccessViolationException( "Brush 개체가 동결되었습니다. 값을 수정하는 것은 접근 위반에 해당합니다." );

	mConstants->Attribute0[0] = value.R / 255.0f;
	mConstants->Attribute0[1] = value.G / 255.0f;
	mConstants->Attribute0[2] = value.B / 255.0f;
	mConstants->Attribute0[3] = value.A / 255.0f;

	UpdateBuffer();
}