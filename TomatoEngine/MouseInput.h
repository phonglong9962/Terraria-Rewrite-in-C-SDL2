#pragma once

#include "SDL.h"

#include <iostream>

class MouseInput
{
public:
	bool leftClick = false, rightClick = false;

	///--- Mouse button states
	bool IsButtonTrigered(const Uint32 uButton) const;
	bool IsButtonPressed(const Uint32 uButton) const;
	bool IsButtonReleased(const Uint32 uButton) const;

	///--- Wheel state
	int GetWheelX()
	{
		return m_iWheelX;
	}
	int GetWheelY()
	{
		return m_iWheelY;
	}
	int GetCoordX()
	{
		return m_iPreviousCoordX;
	}
	int GetCoordY()
	{
		return m_iPreviousCoordY;
	}
private:
	/// Information about the state of the mouse
	int m_iCurrentCoordX;
	int m_iCurrentCoordY;
	Uint32 m_uCurrentMouseState;

	int m_iPreviousCoordX;
	int m_iPreviousCoordY;
	Uint32 m_uPreviousMouseState;

	///information about the state of thw wheel
	Sint32 m_iWheelX;
	Sint32 m_iWheelY;

public:
	static MouseInput *get() { return instance = (instance != nullptr ? instance : new MouseInput()); }

	void update()
	{
		///--- Store the current information to the previous 
		m_iPreviousCoordX = m_iCurrentCoordX;
		m_iPreviousCoordY = m_iCurrentCoordY;
		m_uPreviousMouseState = m_uCurrentMouseState;

		///--- Update the current state of the mouse
		m_uCurrentMouseState = SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

		///--- Set the wheel back to 0
		m_iWheelX = 0;
		m_iWheelY = 0;
	}

	void updateEvent(SDL_Event e)
	{
		switch (e.type)
		{
		case SDL_MOUSEMOTION:
			m_iCurrentCoordX = e.motion.x;
			m_iCurrentCoordY = e.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				leftClick = true;
				break;
			case SDL_BUTTON_RIGHT:
				rightClick = true;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				leftClick = false;
				break;
			case SDL_BUTTON_RIGHT:
				rightClick = false;
				break;
			default:
				break;
			}
			break;
		case SDL_MOUSEWHEEL:
			m_iWheelX = e.wheel.x;
			m_iWheelY = e.wheel.y;
			break;
		}
	}	
	
	///--- Mouse position fucntions
	void GetMousePosition(int& iCoordX, int& iCoordY)
	{
		iCoordX = m_iCurrentCoordX;
		iCoordY = m_iCurrentCoordY;
	}
	void GetMouseDiff(int& iDiffX, int& iDiffY)
	{
		iDiffX = m_iCurrentCoordX - m_iPreviousCoordX;
		iDiffY = m_iCurrentCoordY - m_iPreviousCoordY;
	}

private:
	MouseInput() 
	{
		///--- Last frame information to 0
		m_iPreviousCoordX = 0;
		m_iPreviousCoordY = 0;
		m_uPreviousMouseState = 0;

		///--- Get the current state of the mouse
		m_uCurrentMouseState = SDL_GetMouseState(&m_iCurrentCoordX, &m_iCurrentCoordY);

		///--- initialize the wheel to 0 to avoid problems
		m_iWheelX = 0;
		m_iWheelY = 0;
	}
	static MouseInput *instance;
};