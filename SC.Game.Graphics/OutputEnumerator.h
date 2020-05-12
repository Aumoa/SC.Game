#pragma once

namespace SC::Game::Graphics::DXGI
{
	ref class OutputEnumerator : System::Collections::Generic::IEnumerator<Output^>
	{
	internal:
		Adapter^ mAdapter;
		int mCurrent = -1;
		Output^ mCurrentValue;

		OutputEnumerator( Adapter^ adapter );

	public:
		~OutputEnumerator();
		!OutputEnumerator();

		System::String^ ToString() override;

		virtual bool MoveNext();
		virtual void Reset();

		property Output^ Current
		{
			virtual Output^ get();
		}

		property Object^ Current2
		{
			virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
		};
	};
}