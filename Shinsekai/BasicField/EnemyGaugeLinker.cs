using System;
using System.Collections.Generic;
using System.Text;
using SC.Game;

namespace Shinsekai.BasicField
{
	class EnemyGaugeLinker : Behaviour
	{
		BasicProperties properties;

		public EnemyGaugeLinker() : base()
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

			EnemyGaugeBar.Instance.HPValue = hppair;
		}
	}
}
