using System.Collections.Generic;
using System.IO;
using FbxSDK;

namespace SC.Game.Assets.FBX
{
	partial class Parser : IParser
	{
		string filepath;

		string name;
		string filename;
		string directory;

		FbxSDK.Scene scene;

		GameObject head;
		List<Mesh> meshes = new List<Mesh>();
		Material[] materials;
		IList<FbxSDK.Joint> joints;

		List<FbxSDK.Mesh> fbxMeshes = new List<FbxSDK.Mesh>();
		Dictionary<string, string> texturePaths = new Dictionary<string, string>();
		Dictionary<string, Texture2D> textures = new Dictionary<string, Texture2D>();
		bool isSkinned = false;

		public Parser( string filepath )
		{
			this.filepath = filepath;

			name = Path.GetFileNameWithoutExtension( filepath );
			filename = Path.GetFileName( filepath );
			directory = Path.GetDirectoryName( filepath );

			head = new GameObject( name );
		}

		public virtual LoadedInfo Compose()
		{
			var loadedInfo = new LoadedInfo();
			loadedInfo.Meshes = meshes;
			loadedInfo.Materials = materials;
			loadedInfo.Composed = head;

			if ( scene.NumAnimationClips != 0 )
			{
				loadedInfo.AnimationClips = new AnimationClip[scene.NumAnimationClips];

				for ( int i = 0; i < scene.NumAnimationClips; ++i )
				{
					loadedInfo.AnimationClips[i] = scene.GetAnimationClip( i );
				}
			}

			if ( isSkinned )
			{
				var animator = head.AddComponent<Animator>();

				if ( scene.NumAnimationClips != 0 )
				{
					var animatorController = new AnimatorController( filename + ":baseAnimatorController" );
					animator.Controller = animatorController;

					for ( int i = 0; i < scene.NumAnimationClips; ++i )
					{
						var state = new AnimationState( loadedInfo.AnimationClips[i].Name );
						state.Clip = loadedInfo.AnimationClips[i];
						animatorController.AddState( state );
					}
				}
			}

			return loadedInfo;
		}

		public virtual void TryParse()
		{
			var importer = new Importer();
			scene = importer.Import( filepath );
			joints = scene.Joints;

			ReadTextures();
			ProcessMaterials();
			ProcessNode( scene.RootNode, head, -1 );

			scene.Release();
		}

		void ReadTextures()
		{
			var files = Directory.GetFiles( directory, "*", SearchOption.AllDirectories );

			foreach ( var file in files )
			{
				var filename = Path.GetFileName( file );
				var ext = Path.GetExtension( file );

				if ( ext == ".png" || ext == ".jpg" || ext == ".jpeg" )
				{
					texturePaths.Add( filename, file );
				}
				else if ( ext == ".tga" )
				{
					var changed = Path.ChangeExtension( file, ".png" );
					texturePaths.Add( filename, changed );
				}
			}
		}
	}
}
