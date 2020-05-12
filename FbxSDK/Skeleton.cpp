using namespace FbxSDK;

using namespace System;

Skeleton::Skeleton( Node^ nodeRef, FbxSkeleton* skeleton )
{
	mNodeRef = nodeRef;

	mName = gcnew String( skeleton->GetName() );
	mNameOnly = gcnew String( skeleton->GetNameOnly() );
}

String^ Skeleton::Name::get()
{
	return mName;
}

String^ Skeleton::NameOnly::get()
{
	return mNameOnly;
}