using namespace SC;
using namespace SC::Game;

using namespace System;
using namespace System::Threading::Tasks;
using namespace System::Collections::Generic;
using namespace System::Numerics;

using namespace std;

ref class TaskLambda
{
public:
	String^ Path;

	GameObject^ Task()
	{
		cli::array<wchar_t>^ sep = gcnew cli::array<wchar_t>{ L'.' };
		auto split = Path->Split( sep );

		if ( split[split->Length - 1] == L"mdl" )
		{
			return AssetBundle::CreateGameObjectFromMDL( Path );
		}
		else
		{
			return nullptr;
		}
	}
};

Task<GameObject^>^ AssetBundle::LoadAssetAsync( String^ filepath )
{
	auto taskLambda = gcnew TaskLambda();
	taskLambda->Path = filepath;
	return Task<GameObject^>::Run( gcnew Func<GameObject^>( taskLambda, &TaskLambda::Task ) );
}

GameObject^ AssetBundle::CreateGameObjectFromMDL( String^ filepath )
{
	//auto wstr = filepath.filename().wstring();
	//auto head = AssetBundle::GetItemAs<GameObject>( wstr );
	//if ( !head )
	{
		auto sep = gcnew cli::array<wchar_t>{ L'/', L'\\' };
		auto split = filepath->Split( sep );

		String^ string = "";
		for ( int i = 0; i < split->Length - 1; ++i )
		{
			string += split[i] + "/";
		}

		MDLParser parser( filepath );
		auto head = parser.CreateGameObject( filepath, string );
		if ( parser.sequences.size() != 0 )
		{
			auto& sequences = parser.sequences;
			auto& bones = parser.bones;
			auto& pivots = parser.pivots;

			int numAnimationClips = ( int )sequences.size();
			int numBones = ( int )bones.size();
			List<AnimationClip^>^ clips = gcnew List<AnimationClip^>();

			for ( int i = 0; i < numAnimationClips; ++i )
			{
				auto clip = gcnew AnimationClip( String::Format( "{0}:{1}", filepath, msclr::interop::marshal_context().marshal_as<String^>( sequences[i].Anim.c_str() ) ) );

				auto& seq = sequences[i];

				for ( int i = 0; i < numBones; ++i )
				{
					auto& bone = bones[i];

					Keyframes keyf;
					auto boneName = bones[i].Name;

					MDLParser::tag_Keyframe<XMFLOAT3> translation;
					MDLParser::tag_Keyframe<XMFLOAT3> scale;
					MDLParser::tag_Keyframe<XMFLOAT4> rotation;
					bone.Export( seq.Interval, translation, scale, rotation );

					keyf.Translation = gcnew List<Keyframe>( ( int )translation.Keyframes.size() );
					keyf.Scaling = gcnew List<Keyframe>( ( int )scale.Keyframes.size() );
					keyf.Rotation = gcnew List<KeyframeQ>( ( int )rotation.Keyframes.size() );

					XMFLOAT3 pivotdel_ = pivots[i];
					if ( bone.Parent != -1 )
					{
						pivotdel_.x -= pivots[bone.Parent].x;
						pivotdel_.y -= pivots[bone.Parent].y;
						pivotdel_.z -= pivots[bone.Parent].z;
					}

					auto pivotdel = Vector3( -pivotdel_.y, pivotdel_.z, pivotdel_.x );

					if ( translation.Keyframes.empty() )
					{
						keyf.Translation->Add( Keyframe( 0.0f, pivotdel ) );
					}
					else
					{
						for ( int i = 0; i < ( int )translation.Keyframes.size(); ++i )
						{
							auto tp = ( translation.Keyframes[i].IntervalPos - seq.Interval.Begin ) / 1000.0f;
							auto value = translation.Keyframes[i].Value;
							auto value1 = Vector3( -value.y, value.z, value.x ) + pivotdel;

							keyf.Translation->Add( Keyframe( tp, value1 ) );
						}
					}

					for ( int i = 0; i < ( int )scale.Keyframes.size(); ++i )
					{
						auto tp = ( scale.Keyframes[i].IntervalPos - seq.Interval.Begin ) / 1000.0f;
						auto value = scale.Keyframes[i].Value;
						auto value1 = Vector3( -value.y, value.z, value.x );

						keyf.Scaling->Add( Keyframe( tp, value1 ) );
					}

					for ( int i = 0; i < ( int )rotation.Keyframes.size(); ++i )
					{
						auto tp = ( rotation.Keyframes[i].IntervalPos - seq.Interval.Begin ) / 1000.0f;

						auto rot = rotation.Keyframes[i].Value;
						auto rot1 = Quaternion( -rot.y, rot.z, rot.x, -rot.w );

						keyf.Rotation->Add( KeyframeQ( tp, rot1 ) );
					}

					clip->AddKeyframes( msclr::interop::marshal_context().marshal_as<String^>( boneName.c_str() ), keyf );
				}

				//AddItem( clip );
				clip->IsLoop = !seq.NonLooping;

				clips->Add( clip );
			}

			if ( numAnimationClips != 0 )
			{
				auto animatorController = gcnew AnimatorController( String::Format( "{0}:AnimatorController", filepath ) );

				for ( int i = 0; i < numAnimationClips; ++i )
				{
					auto ptr = gcnew AnimationState( msclr::interop::marshal_context().marshal_as<String^>( sequences[i].Anim.c_str() ) );
					ptr->Clip = clips[i];
					animatorController->AddState( ptr, i == 0 );
				}

				auto animator = head->AddComponent<Animator^>();
				animator->Controller = animatorController;
			}
		}

		//AddItem( head );

		return head;
	}

	//auto gameObject = head->Clone().As<GameObject>();
	//asyncLoad->Progress = 1.0;
	//return gameObject;
}