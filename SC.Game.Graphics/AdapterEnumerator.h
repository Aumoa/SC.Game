#pragma once

namespace SC::Game::Graphics::DXGI
{
	ref class AdapterEnumerator : System::Collections::Generic::IEnumerator<Adapter^>
	{
	internal:
		Factory^ mFactory;
		int mCurrent = -1;
		Adapter^ mCurrentValue;

		AdapterEnumerator( Factory^ factory );

	public:
		~AdapterEnumerator();
		!AdapterEnumerator();

		System::String^ ToString() override;

		virtual bool MoveNext();
		virtual void Reset();

		property Adapter^ Current
		{
			virtual Adapter^ get();
		}

		property Object^ Current2
		{
			virtual Object^ get() sealed = System::Collections::IEnumerator::Current::get;
		};
	};
}