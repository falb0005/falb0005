/**
* \class Timer.h
* \brief A class that manages the timing for the game
* \author Justin Wilkinson
* \date January 29, 2014
*/

#pragma once // Preprocessor directive to ensure that this header will only be included once. -- Generally used on Windows

class Timer;

typedef void(Timer::*TimerInstanceEvent)();
typedef void(*TimerEvent)();

class Timer
{
public:
	enum TimerState
	{
		STOPPED,
		RUNNING,
		PAUSED
	};

	/**
	* \fn void Timer::Timer()
	* \brief Timer Default Constructor
	*/
	Timer();

	/**
	* \fn void Timer::Update()
	* \brief 
	*/
	void Update();

	/**
	* \fn void Timer::Start()
	* \brief
	*/
	void Start();
	/**
	* \fn void Timer::Pause()
	* \brief pauses the game
	*/
	void Pause();
	/**
	* \fn void Timer::Stop()
	* \brief stops the game
	*/
	void Stop();
	/**
	* \fn void Timer::Reset()
	* \brief resets the game
	*/
	void Reset();

	/**
	* \fn float Timer::GetElapsedTime()
	* \brief resets the game
	*/
	float GetElapsedTime();
	/**
	* \fn float Timer::GetDeltaTime()
	* \brief resets the game
	* \return float the change in time since last tick
	*/
	float GetDeltaTime();
	/**
	* \fn float Timer::GetDuration()
	* \brief gets duration
	* \return float duration
	*/
	float GetDuration();

	/**
	* \fn void Timer::GetDuration()
	* \brief sets duration
	* \param duration
	*/
	void SetDuration(float duration);

	/**
	* \fn void Timer::SetTimerEvent(TimerEvent evt)
	* \brief sets timer event
	* \param evt TimerEvent 
	*/
	void SetTimerEvent(TimerEvent evt);
	/**
	* \fn void Timer::(TimerInstanceEvent evt)
	* \brief sets timer event
	* \param evt TimerInstanceEvent
	*/
	void SetTimerEvent(TimerInstanceEvent evt);

protected:
	float _oldTime, _currentTime, _deltaTime;
	float _duration, _elapsedTime;
	bool _paused;

	TimerState _state;
	TimerEvent _timerEvt;
	TimerInstanceEvent _timerInstEvt;
};