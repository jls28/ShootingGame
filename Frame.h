#pragma once
class Frame
{
public:
	int nowFrame, endFrame, startFrame;
	float delay, frameSkip;
public:
	Frame();
	~Frame();

	inline bool OnFrame()
	{
		if (frameSkip <= GetNowTime())
		{
			nowFrame++;

			if (nowFrame > endFrame)
				nowFrame = startFrame;

			frameSkip = GetNowTime() + delay;
			return true;
		}
		return false;
	}

	void SetFrame(int start, int end, float del)
	{
		startFrame = nowFrame = start;
		endFrame = end;
		delay = del;
		frameSkip = GetNowTime() + del;
	}
};

