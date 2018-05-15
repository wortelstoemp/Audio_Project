#pragma once

inline double Mixer2(double sample1, double sample2, 
	double a1 = 0.5, double a2 = 0.5)
{
	return sample1 * a1 + sample2 * a2;
}

inline double Mixer3(double sample1, double sample2, double sample3, 
	double a1 = 1.0 / 3.0, double a2 = 1.0 / 3.0, double a3 = 1.0 / 3.0)
{
	return sample1 * a1 + sample2 * a2 + sample3 * a3;
}

inline double Mixer4(double sample1, double sample2, 
	double sample3, double sample4,
	double a1 = 0.25, double a2 = 0.25, double a3 = 0.25, double a4 = 0.25)
{
	return sample1 * a1 + sample2 * a2 + sample3 * a3 + sample4 * a4;
}

inline double Mixer5(double sample1, double sample2, double sample3, 
	double sample4, double sample5,
	double a1 = 0.2, double a2 = 0.2, double a3 = 0.2, 
	double a4 = 0.2, double a5 = 0.2)
{
	return sample1 * a1 + sample2 * a2 + sample3 * a3 
		+ sample4 * a4 + sample5 * a5;
}

inline double Mixer6(double sample1, double sample2, double sample3, 
	double sample4, double sample5, double sample6,
	double a1 = 1.0 / 6.0, double a2 = 1.0 / 6.0, double a3 = 1.0 / 6.0, 
	double a4 = 1.0 / 6.0, double a5 = 1.0 / 6.0, double a6 = 1.0 / 6.0)
{
	return sample1 * a1 + sample2 * a2 + sample3 * a3 
		+ sample4 * a4 + sample5 * a5 + sample6 * a6;
}

inline double Mixer7(double sample1, double sample2, double sample3,
	double sample4, double sample5, double sample6, double sample7,
	double a1 = 1.0 / 7.0, double a2 = 1.0 / 7.0, double a3 = 1.0 / 7.0,
	double a4 = 1.0 / 7.0, double a5 = 1.0 / 7.0, double a6 = 1.0 / 7.0,
	double a7 = 1.0 / 7.0)
{
	return sample1 * a1 + sample2 * a2 + sample3 * a3
		+ sample4 * a4 + sample5 * a5 + sample6 * a6 + sample7 * a7;
}

inline double Mixer8(double sample1, double sample2, 
	double sample3,double sample4, double sample5, 
	double sample6, double sample7, double sample8,
	double a1 = 0.125, double a2 = 0.125, double a3 = 0.125,
	double a4 = 0.125, double a5 = 0.125, double a6 = 0.125,
	double a7 = 0.125, double a8 = 0.125)
{
	return sample1 * a1 + sample2 * a2 + sample3 * a3
		+ sample4 * a4 + sample5 * a5
		+ sample6 * a6 + sample7 * a7 + sample8 * a8;
}