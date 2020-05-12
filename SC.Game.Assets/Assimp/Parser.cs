using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Security.Cryptography;
using Assimp;

using SDK = Assimp;

namespace SC.Game.Assets.Assimp
{
	partial class Parser : IParser
	{
		string filepath;

		string name;
		string filename;
		string directory;
		SDK.Scene scene;

		List<Texture2D> textures = new List<Texture2D>();
		Material[] materials;
		Mesh[] meshes;
		List<Joint> joints = new List<Joint>();
		AnimationClip[] clips;
		AnimatorController controller;

		GameObject head;

		public Parser( string filepath )
		{
			this.filepath = filepath;
		}

		public virtual LoadedInfo Compose()
		{
			var loadedInfo = new LoadedInfo();
			loadedInfo.Textures = textures;
			loadedInfo.Materials = materials;
			loadedInfo.Composed = head;
			loadedInfo.Meshes = new Game.Mesh[meshes.Length];
			for ( int i = 0; i < meshes.Length; ++i )
			{
				loadedInfo.Meshes[i] = meshes[i].pMesh;
			}
			loadedInfo.AnimationClips = clips;
			return loadedInfo;
		}

		public virtual void TryParse()
		{
			name = Path.GetFileNameWithoutExtension( filepath );
			filename = Path.GetFileName( filepath );
			directory = Path.GetDirectoryName( filepath );

			head = new GameObject( "name" );

			var importer = new AssimpContext();
			scene = importer.ImportFile( filepath,
				PostProcessSteps.LimitBoneWeights |
				PostProcessSteps.Triangulate |
				PostProcessSteps.MakeLeftHanded |
				PostProcessSteps.FlipUVs
				);

			ProcessMaterials();
			ProcessMeshes();
			ProcessJointHierarchy( head, scene.RootNode, -1 );
			ProcessAnimations();

			if ( scene.HasAnimations )
			{
				var animator = head.AddComponent<Animator>();
				animator.Controller = controller;
			}
		}
	}
}
