using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;

namespace SC.Game.Assets.MDL
{
	struct Bone
	{
		public string Name;
		public int Parent;
		public Keyframes<Vector3> Translation;
		public Keyframes<Vector3> Scale;
		public Keyframes<Quaternion> Rotation;

		public override string ToString()
		{
			return "<Name: " + Name + ", Parent: " + Parent + ">";
		}

		public void Export( Interval interval, out Keyframes<Vector3> translation, out Keyframes<Vector3> scale, out Keyframes<Quaternion> rotation )
		{
			translation = new Keyframes<Vector3>();
			scale = new Keyframes<Vector3>();
			rotation = new Keyframes<Quaternion>();

			translation.Keys = new List<Keyframe<Vector3>>();
			scale.Keys = new List<Keyframe<Vector3>>();
			rotation.Keys = new List<Keyframe<Quaternion>>();

			translation.Keys = new List<Keyframe<Vector3>>();
			scale.Keys = new List<Keyframe<Vector3>>();
			rotation.Keys = new List<Keyframe<Quaternion>>();

			int numKeyf;

			if ( Translation.Keys != null )
			{
				numKeyf = Translation.Keys.Count;
				translation.Method = Translation.Method;
				for ( int i = 0; i < numKeyf; ++i )
				{
					if ( Translation.Keys[i].IntervalPos >= interval.Begin && Translation.Keys[i].IntervalPos <= interval.End )
					{
						translation.Keys.Add( Translation.Keys[i] );
					}
				}
			}

			if ( Scale.Keys != null )
			{
				numKeyf = Scale.Keys.Count;
				scale.Method = Scale.Method;
				for ( int i = 0; i < numKeyf; ++i )
				{
					if ( Scale.Keys[i].IntervalPos >= interval.Begin && Scale.Keys[i].IntervalPos <= interval.End )
					{
						scale.Keys.Add( Scale.Keys[i] );
					}
				}
			}

			if ( Rotation.Keys != null )
			{
				numKeyf = Rotation.Keys.Count;
				rotation.Method = Rotation.Method;
				for ( int i = 0; i < numKeyf; ++i )
				{
					if ( Rotation.Keys[i].IntervalPos >= interval.Begin && Rotation.Keys[i].IntervalPos <= interval.End )
					{
						rotation.Keys.Add( Rotation.Keys[i] );
					}
				}
			}
		}
	}
}
