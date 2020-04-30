using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai.BasicField
{
	class GaugeLinker : Behaviour
	{
		BasicProperties properties;

		public GaugeLinker() : base()
		{

		}

		public override void Start()
		{
			properties = GetComponent<BasicProperties>();
		}

		public override void Update()
		{
			PropertyPair hppair = new PropertyPair();
			hppair.MinValue = properties.MinHealth;
			hppair.MaxValue = properties.MaxHealth;
			hppair.Value = properties.Health;

			BasicGaugeBar.Instance.HPValue = hppair;
		}
	}
}
