#pragma once

namespace SC::Game
{
	class TextParser
	{
		std::vector<char> sep;

		const char* textBlock = nullptr;
		int seekpos = 0;

	public:
		TextParser( const std::string& separates = " ,{}[]()+-/*\n" );

		void SetBuffer( const char* textBlock );

		char ReadChar();
		std::string ReadString( bool removeQuotes = true );
		int ReadInt();
		float ReadDouble();

		__declspec( property( get = Seekpos_get, put = Seekpos_set ) ) int Seekpos;
		int Seekpos_get();
		void Seekpos_set( int value );
		__declspec( property( get = Eof_get ) ) bool Eof;
		bool Eof_get();

	private:
		void _NextSeekpos();
		void _FindStoppos();
		bool _CheckIfSep( char ch );
	};
}