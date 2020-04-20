#pragma once

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

inline void Assign( System::Numerics::Matrix4x4% left, XMFLOAT4X4& right )
{
	left.M11 = right._11;
	left.M12 = right._12;
	left.M13 = right._13;
	left.M14 = right._14;

	left.M21 = right._21;
	left.M22 = right._22;
	left.M23 = right._23;
	left.M24 = right._24;

	left.M31 = right._31;
	left.M32 = right._32;
	left.M33 = right._33;
	left.M34 = right._34;

	left.M41 = right._41;
	left.M42 = right._42;
	left.M43 = right._43;
	left.M44 = right._44;
}

inline void Assign( XMFLOAT4X4& left, System::Numerics::Matrix3x2% right )
{
	left._11 = right.M11;
	left._12 = right.M12;

	left._21 = right.M21;
	left._22 = right.M22;

	left._31 = right.M31;
	left._32 = right.M32;
}

inline void Assign( System::Numerics::Matrix3x2& left, XMFLOAT4X4% right )
{
	left.M11 = right._11;
	left.M12 = right._12;

	left.M21 = right._21;
	left.M22 = right._22;

	left.M31 = right._31;
	left.M32 = right._32;
}

inline void Assign( XMFLOAT3& left, System::Numerics::Vector3% right )
{
	left.x = right.X;
	left.y = right.Y;
	left.z = right.Z;
}

inline void Assign( System::Drawing::Color% left, XMFLOAT3& right )
{
	left = System::Drawing::Color::FromArgb(
		( int )( right.x * 255.0f ),
		( int )( right.y * 255.0f ),
		( int )( right.z * 255.0f )
	);
}

inline void Assign( XMFLOAT3& left, System::Drawing::Color% right )
{
	left.x = ( float )right.R / 255.0f;
	left.y = ( float )right.G / 255.0f;
	left.z = ( float )right.B / 255.0f;
}

inline void Assign( physx::PxVec3& left, System::Numerics::Vector3% right )
{
	left.x = right.X;
	left.y = right.Y;
	left.z = right.Z;
}

inline void Assign( physx::PxQuat& left, System::Numerics::Quaternion% right )
{
	left.x = right.X;
	left.y = right.Y;
	left.z = right.Z;
	left.w = right.W;
}

inline void Assign( System::Numerics::Vector3% left, physx::PxVec3& right )
{
	left.X = right.x;
	left.Y = right.y;
	left.Z = right.z;
}

inline void Assign( System::Numerics::Quaternion% left, physx::PxQuat& right )
{
	left.X = right.x;
	left.Y = right.y;
	left.Z = right.z;
	left.W = right.w;
}

#pragma managed( push, off )
inline XMFLOAT4X4 XMLookToLH( float eyex, float eyey, float eyez, float dirx, float diry, float dirz, float upx, float upy, float upz )
{
	auto look = XMMatrixLookToLH( XMVectorSet( eyex, eyey, eyez, 0.0f ), XMVectorSet( dirx, diry, dirz, 1.0f ), XMVectorSet( upx, upy, upz, 1.0f ) );
	XMFLOAT4X4 result;
	XMStoreFloat4x4( &result, look );
	return result;
}

inline XMFLOAT4X4 XMPerspectiveFovLH( float fov, float asp, float mind, float maxd )
{
	auto proj = XMMatrixPerspectiveFovLH( fov, asp, mind, maxd );
	XMFLOAT4X4 result;
	XMStoreFloat4x4( &result, proj );
	return result;
}

inline XMFLOAT4X4 XMOrthographicLH( float width, float height, float nearZ, float farZ )
{
	auto proj = XMMatrixOrthographicLH( width, height, nearZ, farZ );
	XMFLOAT4X4 result;
	XMStoreFloat4x4( &result, proj );
	return result;
}

inline XMFLOAT4X4 XMMatrixScaling( float scaleX, float scaleY, float scaleZ )
{
	XMFLOAT4X4 dest;
	auto scaling = DirectX::XMMatrixScaling( scaleX, scaleY, scaleZ );
	XMStoreFloat4x4( &dest, scaling );
	return dest;
}

inline XMFLOAT4X4 XMMatrixRotationQuaternion( float x, float y, float z, float w )
{
	XMFLOAT4X4 dest;
	auto quat = DirectX::XMMatrixRotationQuaternion( XMVectorSet( x, y, z, w ) );
	XMStoreFloat4x4( &dest, quat );
	return dest;
}

inline XMFLOAT4X4 XMMatrixTranslation( float x, float y, float z )
{
	XMFLOAT4X4 dest;
	auto trans = DirectX::XMMatrixTranslation( x, y, z );
	XMStoreFloat4x4( &dest, trans );
	return dest;
}
#pragma managed( pop )

inline System::Numerics::Matrix4x4 LookToLH( System::Numerics::Vector3% eye, System::Numerics::Vector3% dir, System::Numerics::Vector3% up )
{
	System::Numerics::Matrix4x4 look;
	Assign( look, XMLookToLH( eye.X, eye.Y, eye.Z, dir.X, dir.Y, dir.Z, up.X, up.Y, up.Z ) );
	return look;
}

inline System::Numerics::Matrix4x4 PerspectiveFovLH( float fov, float asp, float nearZ, float farZ )
{
	System::Numerics::Matrix4x4 proj;
	Assign( proj, XMPerspectiveFovLH( fov, asp, nearZ, farZ ) );
	return proj;
}

inline System::Numerics::Matrix4x4 OrthographicLH( float width, float height, float nearZ, float farZ )
{
	System::Numerics::Matrix4x4 proj;
	Assign( proj, XMOrthographicLH( width, height, nearZ, farZ ) );
	return proj;
}

inline System::Numerics::Matrix4x4 Scaling( float x, float y, float z )
{
	System::Numerics::Matrix4x4 scale;
	Assign( scale, ::XMMatrixScaling( x, y, z ) );
	return scale;
}

inline System::Numerics::Matrix4x4 RotationQuaternion( float x, float y, float z, float w )
{
	System::Numerics::Matrix4x4 quat;
	Assign( quat, ::XMMatrixRotationQuaternion( x, y, z, w ) );
	return quat;
}

inline System::Numerics::Matrix4x4 Translation( float x, float y, float z )
{
	System::Numerics::Matrix4x4 trans;
	Assign( trans, ::XMMatrixTranslation( x, y, z ) );
	return trans;
}

inline void Assign( System::Drawing::Color% left, XMFLOAT4& right )
{
	int r = ( int )( right.x * 255.0f );
	int g = ( int )( right.y * 255.0f );
	int b = ( int )( right.z * 255.0f );
	int a = ( int )( right.w * 255.0f );

	left = System::Drawing::Color::FromArgb(
		a,
		r,
		g,
		b
	);
}

inline void Assign( XMFLOAT4& left, System::Drawing::Color% right )
{
	left.x = right.R / 255.0f;
	left.y = right.G / 255.0f;
	left.z = right.B / 255.0f;
	left.w = right.A / 255.0f;
}