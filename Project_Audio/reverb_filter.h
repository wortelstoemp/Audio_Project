#pragma once

#include "allpass_filter.h"
#include "feedback_comb_filter.h"
#include "feedforward_comb_filter.h"

// Reverberator based only on all-pass filters.
class ReverberatorAP
{
private:
	AllPassFilter ap1;
	AllPassFilter ap2;
	AllPassFilter ap3;

public:
	ReverberatorAP()
		: ap1(1051.0, 0.7),
		ap2(337.0, 0.7),
		ap3(113.0, 0.7)
	{
	}

	double Filter(double input)
	{
		double output = 0.0;

		output = ap1.Filter(input);
		output = ap2.Filter(output);
		output = ap3.Filter(output);

		//output = output;
		output *= 0.8;

		return output;
	}
};

// Based and improved on the original Schroeder Reverberator described in: 
// https://ccrma.stanford.edu/~jos/pasp/Schroeder_Reverberators.html#14652
// https://ccrma.stanford.edu/~jos/pasp/Example_Schroeder_Reverberators.html
class ReverberatorJCREV
{
private:
	AllPassFilter ap1;
	AllPassFilter ap2;
	AllPassFilter ap3;
	FeedforwardCombFilter ffcf1;
	FeedforwardCombFilter ffcf2;
	FeedforwardCombFilter ffcf3;
	FeedforwardCombFilter ffcf4;

public:
	ReverberatorJCREV()
		: ap1(1051.0, 0.7),
		ap2(337.0, 0.7),
		ap3(113.0, 0.7),
		ffcf1(100.0, 0.742),
		ffcf2(200.0, 0.733),
		ffcf3(300.0, 0.715),
		ffcf4(581.0, 0.697)
	{
	}

	double Filter(double input)
	{
		double output = 0.0;


		output = ap1.Filter(input);
		output = ap2.Filter(output);
		output = ap3.Filter(output);


		double output1 = ffcf1.Filter(output);
		double output2 = ffcf2.Filter(output);
		double output3 = ffcf3.Filter(output);

		output = output1 + output2 + output3;
		output *= 0.5;

		return output;
	}
};