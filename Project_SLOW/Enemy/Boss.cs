using System;
using System.Numerics;
using SC.Game;
using SC.Game.Assets;

namespace Project_SLOW
{
	class Boss : SingletonGameObject<Boss>
	{
		GameObject modelAsset;

		GameObject rightHandJoint;
		GameObject weaponJoint;

		public Boss() : base( "Boss" )
		{
			LoadAssets();

			var go = modelAsset.Clone() as GameObject;
			go.Transform.Parent = Transform;

			var testSphere = new GameObject( "testSphere" );
			testSphere.AddComponent<MeshFilter>().Mesh = Mesh.CreateGeosphere( "test", 4 );
			testSphere.AddComponent<MeshRenderer>();
			testSphere.Transform.LocalScale = new Vector3( 10.0f );

			rightHandJoint = go.GetChildRecursive( "Bip001 R Hand" );
			testSphere.Transform.Parent = rightHandJoint.Transform;

			weaponJoint = new GameObject( "weaponJoint" );
			weaponJoint.AddComponent<MeshFilter>().Mesh = Mesh.CreateGeosphere( "test", 4 );
			weaponJoint.AddComponent<MeshRenderer>();
			weaponJoint.Transform.Parent = rightHandJoint.Transform;
			weaponJoint.Transform.LocalPosition = new Vector3( 6.04f, 2.31f, 22.87f );
			weaponJoint.Transform.LocalScale = new Vector3( 10.0f );
		}

		void LoadAssets()
		{
			var loaded = AssetBundle.LoadAsset( @"Assets/Model/Boss/bull_king.fbx" );
			modelAsset = loaded.Composed;
			modelAsset.Transform.LocalScale = new Vector3( -1.0f, 1.0f, 1.0f );
			modelAsset.Transform.Parent = Transform;

			var texture = new Texture2D( "bull_king_s", @"Assets\Model\Boss\texture\bull_king_s.png", TextureFormat.PRGBA_32bpp );
			modelAsset.GetComponentInChildren<SkinnedMeshRenderer>().Material.DiffuseMap = texture;

			loaded = AssetBundle.LoadAsset( @"Assets\Model\Boss\bull_king@attack_01.fbx" );
			var clip = loaded.AnimationClips[0];

			var animatorController = new AnimatorController( "boss_controller" );
			var state = new AnimationState( "Stand" );
			state.Clip = clip;

			animatorController.AddState( state );
			var animator = modelAsset.GetComponentInChildren<Animator>();
			animator.Controller = animatorController;
		}
	}
}
