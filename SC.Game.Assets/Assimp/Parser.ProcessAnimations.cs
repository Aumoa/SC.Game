using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Assimp;

using SDK = Assimp;

namespace SC.Game.Assets.Assimp
{
	partial class Parser
	{
		void ProcessAnimations()
		{
			if ( scene.HasAnimations )
			{
				controller = new AnimatorController( string.Format( "{0}:DefaultController", name ) );
				clips = new AnimationClip[scene.AnimationCount];
			}

			for ( int i = 0; i < scene.AnimationCount; ++i )
			{
				var animation = scene.Animations[i];
				var tps = animation.TicksPerSecond;

				if ( tps == 0 ) tps = 24.0;
				var clip = new AnimationClip( string.Format( "{0}:{1}", filename, animation.Name ) );

				for ( int j = 0; j < animation.NodeAnimationChannelCount; ++j )
				{
					var channel = animation.NodeAnimationChannels[j];

					Keyframes keyframes;
					keyframes.Translation = new List<Keyframe>();
					keyframes.Scaling = new List<Keyframe>();
					keyframes.Rotation = new List<KeyframeQ>();

					for ( int k = 0; k < channel.PositionKeyCount; ++k )
					{
						var keyf = new Keyframe();
						var key = channel.PositionKeys[k];

						keyf.TimePos = ( float )( key.Time / tps );
						Assign( out keyf.Value, key.Value );

						keyframes.Translation.Add( keyf );
					}

					for ( int k = 0; k < channel.ScalingKeyCount; ++k )
					{
						var keyf = new Keyframe();
						var key = channel.ScalingKeys[k];

						keyf.TimePos = ( float )( key.Time / tps );
						Assign( out keyf.Value, key.Value );

						keyframes.Scaling.Add( keyf );
					}

					for ( int k = 0; k < channel.RotationKeyCount; ++k )
					{
						var keyf = new KeyframeQ();
						var key = channel.RotationKeys[k];

						keyf.TimePos = ( float )( key.Time / tps );
						Assign( out keyf.Value, key.Value );

						keyframes.Rotation.Add( keyf );
					}
				}

				clip.IsLoop = true;
				var animationState = new AnimationState( animation.Name );
				animationState.Clip = clip;

				controller.AddState( animationState );
				clips[i] = clip;
			}
		}
	}
}
