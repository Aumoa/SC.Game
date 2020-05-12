using System;
using System.Collections.Generic;
using System.Numerics;
using SC.Game;
using SC.Game.Assets;
using System.IO;

namespace Project_SLOW
{
	class Arisa : Unit
	{
		static GameObject modelAsset;

		Dictionary<string, Texture2D> textures = new Dictionary<string, Texture2D>();
		Dictionary<string, Material> materials = new Dictionary<string, Material>();

		public Arisa( string xName ) : base( xName )
		{
			LoadAssets();

			var go = modelAsset.Clone() as GameObject;
			go.Transform.Parent = Transform;
			go.Transform.LocalScale = new Vector3( -1.0f, 1.0f, 1.0f );
			go.Transform.LocalRotation = Quaternion.CreateFromAxisAngle( Vector3.UnitX, ( float )Math.PI * 0.5f );
			//go.Transform.LocalPosition = new Vector3( 0.0f, 3.0f, 0.0f );

			InitializeAnimator();
			LoadComponents();
		}

		void LoadAssets()
		{
			var loaded = AssetBundle.LoadAsset( @"Assets/Model/ArisaNew/ArisaNew.fbx" );
			modelAsset = loaded.Composed;

			var animationClips = new Dictionary<string, AnimationClip>();
			var names = new string[]
			{
				"Idle",
				"Running",
			};

			for ( int i = 0; i < names.Length; ++i )
			{
				loaded = AssetBundle.LoadAsset( string.Format( "Assets/Model/ArisaNew/ArisaNew@{0}.fbx", names[i] ) );
				animationClips[names[i]] = loaded.AnimationClips[0];
			}

			var stand = new AnimationState( "Stand" );
			stand.Clip = animationClips[names[0]];

			var running = new AnimationState( "Walk" );
			running.Clip = animationClips[names[1]];

			var controller = new AnimatorController( "arisa_controller" );
			controller.AddState( stand, true );
			controller.AddState( running );

			var animator = modelAsset.GetComponent<Animator>();
			animator.Controller = controller;
		}

		void LoadComponents()
		{
			AddComponent<MokouAttackWeapon>();
			AddComponent<AttackAbility>();
		}
	}
}
