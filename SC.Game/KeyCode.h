#pragma once

namespace SC::Game
{
	/// <summary>
	/// 게임 입력 시스템에서 사용하는 가상 키 코드를 표현합니다.
	/// </summary>
	public enum class KeyCode
	{
		/// <summary> 키가 눌리지 않은 상태를 나타냅니다. </summary>
		None,
		Mouse0 = 0x01, Mouse1, Cancel, Mouse2, Mouse3, Mouse4, Mouse5 /* Reserved Mouse5 in Windows */,
		Backspace = 0x08, Tab,
		Clear = 0x0C, Return,
		Menu = 0x12, Pause, CapsLock,
		Escape = 0x1B,
		Space = 0x20, PageUp, PageDown, End, Home, LeftArrow, UpArrow, RightArrow, DownArrow,
		Print = 0x2C, Insert, Delete, Help,
		Alpha0 = 0x30, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		Keypad0 = 0x60, Keypad1, Keypad2, Keypad3, Keypad4, Keypad5, Keypad6, Keypad7, Keypad8, Keypad9,
		KeypadMultiply = 0x6A, KeypadPlus,
		KeypadMinus = 0x6D, KeypadPeriod, KeypadDivide,
		F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
		NumLock = 0x90, ScrollLock,
		LeftShift = 0xA0, RightShift, LeftControl, RightControl,
		Semicolon = 0xBA, Plus, Comma, Minus, Period, Slash, GraveAccent,
		LeftBracket = 0xDB, Backslash, RightBracket, Quote
	};
}