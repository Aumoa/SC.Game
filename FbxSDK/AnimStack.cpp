using namespace FbxSDK;

using namespace System;

AnimStack::AnimStack( FbxAnimStack* animStack )
{
	mAnimStack = animStack;

	mName = gcnew String( mAnimStack->GetName() );
}

String^ AnimStack::Name::get()
{
	return mName;
}