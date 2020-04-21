using System;
using System.Drawing;
using SC.Game;
using SC.Game.UI;
using SC.Diagnostics;

namespace THHourai
{
	public delegate void ScriptEndedDelegate();

	class OnlyScriptPage : BasePage
	{
		static TextFormat textFormatContinue;
		static TextFormat textFormatScript;

		int numScripts;
		StepTimer dropdownTick;
		bool dropdownState;

		TextBlock[] textSequences;
		string[] textScripts;
		TextBlock dropdownText;
		TextBlock helpText;

		SolidColorBrush textColor;

		TextBlock currentText;
		int currentSeqIndex = 0;

		public OnlyScriptPage( string xName, int numScripts ) : base( xName )
		{
			this.numScripts = numScripts;

			textSequences = new TextBlock[numScripts];
			textScripts = new string[numScripts];

			InitializeComponents();
		}

		public override void Update( RectangleF clientRect )
		{
			if ( dropdownTick == null )
			{
				dropdownTick = new StepTimer();
				dropdownTick.IsFixedTimeStep = true;
				dropdownTick.TargetElapsedSeconds = 0.3;
			}

			dropdownTick.Tick( () =>
			{
				dropdownState = !dropdownState;
				dropdownText.Opacity = dropdownState ? 1.0f : 0f;
			} );

			dropdownText.RemoveDependencyProperty( RelativePanel.ClassName );
			dropdownText.AddDependencyProperty( string.Format( "RelativePanel.AlignTopWith={0}", currentText.Name ) );
			dropdownText.AddDependencyProperty( string.Format( "RelativePanel.RightOf={0}", currentText.Name ) );
			dropdownText.AddDependencyProperty( string.Format( "RelativePanel.AlignBottomWith={0}", currentText.Name ) );

			if ( Input.GetKeyDown( KeyCode.Mouse0 ) || Input.GetKeyDown( KeyCode.Mouse1 ) )
			{
				MoveNext();
			}

			base.Update( clientRect );
		}

		public string this[int index]
		{
			get
			{
				return textScripts[index];
			}
			set
			{
				textScripts[index] = value;
				textSequences[index].Content = value;
			}
		}

		public event ScriptEndedDelegate ScriptEnded;

		void MoveNext()
		{
			if ( currentSeqIndex == numScripts - 1 )
			{
				ScriptEnded?.Invoke();
			}
			else
			{
				currentSeqIndex += 1;
				currentText = textSequences[currentSeqIndex];
				currentText.Opacity = 1.0f;
			}
		}

		void InitializeComponents()
		{
			if ( textFormatContinue == null || textFormatScript == null )
			{
				textFormatContinue = new TextFormat( "", 22.0f );
				textFormatScript = new TextFormat( "", 20.0f );

				App.Disposing += () =>
				{
					textFormatContinue = null;
					textFormatScript = null;
				};
			}

			textColor = new SolidColorBrush( Color.White );

			var relativePanel = Content as RelativePanel;
			{
				for ( int i = 0; i < numScripts; ++i )
				{
					var text = new TextBlock( string.Format( "textSequences[{0}]", i ) );
					text.Content = "";
					text.Margin = new Thickness( 30, i == 0 ? 100 : 16, 30, 0 );
					text.Fill = textColor;
					text.Alignment = TextAlignment.Left;
					text.Format = textFormatScript;
					if ( i != 0 )
					{
						text.AddDependencyProperty( string.Format( "RelativePanel.Below={0}", textSequences[i - 1].Name ) );
						text.Opacity = 0;
					}
					relativePanel.Add( text );
					textSequences[i] = text;
				}

				dropdownText = new TextBlock( "dropdownText" );
				dropdownText.Content = " ▼";
				dropdownText.Fill = textColor;
				dropdownText.VerticalAlignment = TextVerticalAlignment.Center;
				dropdownText.AutoSizing = false;
				relativePanel.Add( dropdownText );

				helpText = new TextBlock( "helpText" );
				helpText.Format = textFormatContinue;
				helpText.Content = "아무 키나 눌러 계속 진행";
				helpText.Margin = new Thickness( 25.0f );
				helpText.Anchor = Anchor.RightBottom;
				helpText.Fill = textColor;
				relativePanel.Add( helpText );

				currentText = textSequences[0];
			}
		}
	}
}