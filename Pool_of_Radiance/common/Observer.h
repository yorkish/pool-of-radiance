#pragma once

// The Abstract Observer
class Observer
{
  public:
		virtual void update(bool bPause) = 0;
};
