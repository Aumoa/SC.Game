using namespace FbxSDK;

NodeAttribute::NodeAttribute( FbxNodeAttribute* nodeAttribute )
{
	mNodeAttribute = nodeAttribute;
	mType = ( NodeAttributeType )nodeAttribute->GetAttributeType();
}

NodeAttributeType NodeAttribute::AttributeType::get()
{
	return mType;
}