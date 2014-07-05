//
//  Easing.h
//  emannlibLib
//
//  Created by Evan Ackmann on 5/6/14.
//
//

#ifndef emannlibLib_Easing_h
#define emannlibLib_Easing_h

#include <vector>

namespace emannlib
{
	enum EasingType
	{
		EASING_LINEAR,

		EASING_QUADRATIC_IN,
		EASING_QUADRATIC_OUT,
		EASING_QUADRATIC_INOUT,

		EASING_CUBIC_IN,
		EASING_CUBIC_OUT,
		EASING_CUBIC_INOUT,

		EASING_QUARTIC_IN,
		EASING_QUARTIC_OUT,
		EASING_QUARTIC_INOUT,

		EASING_QUINTIC_IN,
		EASING_QUINTIC_OUT,
		EASING_QUINTIC_INOUT,

		EASING_SINE_IN,
		EASING_SINE_OUT,
		EASING_SINE_INOUT,

		EASING_CIRCULAR_IN,
		EASING_CIRCULAR_OUT,
		EASING_CIRCULAR_INOUT,

		EASING_EXPONENTIAL_IN,
		EASING_EXPONENTIAL_OUT,
		EASING_EXPONENTIAL_INOUT,

		EASING_ELASTIC_IN,
		EASING_ELASTIC_OUT,
		EASING_ELASTIC_INOUT,

		EASING_BACK_IN,
		EASING_BACK_OUT,
		EASING_BACK_INOUT,

		EASING_BOUNCE_IN,
		EASING_BOUNCE_OUT,
		EASING_BOUNCE_INOUT,

		EASING_END
	};
	//returns [0,1] order is start, end, current

	//template<double(*m_EasingFunction)(double)>
	//class Easing
	//{
	//public:
	//	Easing(double start, double end) :
	//		m_StartTime(start),
	//		m_EndTime(end)
	//	{

	//	}

	//	~Easing(){}

	//	double GetValue(double currentTime) const
	//	{
	//		double percentage = (currentTime - m_StartTime) / (m_EndTime - m_StartTime);
	//		return m_EasingFunction(percentage);
	//	}

	//	std::vector<double> PreComputeValues(size_t numValues)
	//	{
	//		std::vector<double> values;
	//		values.reserve(numValues);

	//		double step = 1.0 / (double) (numValues - 1);
	//		double counter = 0.0;
	//		for (size_t i = 0; i < numValues; ++i)
	//		{
	//			values.push_back(m_EasingFunction(counter));
	//			counter += step;
	//		}
	//		return values;
	//	}

	//	bool IsComplete(double currentTime) const
	//	{
	//		return (currentTime >= m_EndTime);
	//	}

	//private:
	//	double m_StartTime;
	//	double m_EndTime;
	//};

	double LinearEasingFunction(double p);

	//typedef Easing<LinearEasingFunction> LinearEase;

	double QuadraticEaseInFunction(double p);
	double QuadraticEaseOutFunction(double p);
	double QuadraticEaseInOutFunction(double p);

	//typedef Easing<QuadraticEaseInFunction> QuadraticEaseIn;
	//typedef Easing<QuadraticEaseOutFunction> QuadraticEaseOut;
	//typedef Easing<QuadraticEaseInOutFunction> QuadraticEaseInOut;


	double CubicEaseInFunction(double p);
	double CubicEaseOutFunction(double p);
	double CubicEaseInOutFunction(double p);

	//typedef Easing<CubicEaseInFunction> CubicEaseIn;
	//typedef Easing<CubicEaseOutFunction> CubicEaseOut;
	//typedef Easing<CubicEaseInOutFunction> CubicEaseInOut;


	double QuarticEaseInFunction(double p);
	double QuarticEaseOutFunction(double p);
	double QuarticEaseInOutFunction(double p);

	//typedef Easing<QuarticEaseInFunction> QuarticEaseIn;
	//typedef Easing<QuarticEaseOutFunction> QuarticEaseOut;
	//typedef Easing<QuarticEaseInOutFunction> QuarticEaseInOut;



	double QuinticEaseInFunction(double p);
	double QuinticEaseOutFunction(double p);
	double QuinticEaseInOutFunction(double p);

	//typedef Easing<QuinticEaseInFunction> QuinticEaseIn;
	//typedef Easing<QuinticEaseOutFunction> QuinticEaseOut;
	//typedef Easing<QuinticEaseInOutFunction> QuinticEaseInOut;


	double SineEaseInFunction(double p);
	double SineEaseOutFunction(double p);
	double SineEaseInOutFunction(double p);

	//typedef Easing<SineEaseInFunction> SineEaseIn;
	//typedef Easing<SineEaseOutFunction> SineEaseOut;
	//typedef Easing<SineEaseInOutFunction> SineEaseInOut;


	double CircularEaseInFunction(double p);
	double CircularEaseOutFunction(double p);
	double CircularEaseInOutFunction(double p);

	//typedef Easing<CircularEaseInFunction> CircularEaseIn;
	//typedef Easing<CircularEaseOutFunction> CircularEaseOut;
	//typedef Easing<CircularEaseInOutFunction> CircularEaseInOut;


	double ExponentialEaseInFunction(double p);
	double ExponentialEaseOutFunction(double p);
	double ExponentialEaseInOutFunction(double p);

	//typedef Easing<ExponentialEaseInFunction> ExponentialEaseIn;
	//typedef Easing<ExponentialEaseOutFunction> ExponentialEaseOut;
	//typedef Easing<ExponentialEaseInOutFunction> ExponentialEaseInOut;


	double ElasticEaseInFunction(double p);
	double ElasticEaseOutFunction(double p);
	double ElasticEaseInOutFunction(double p);

	//typedef Easing<ElasticEaseInFunction> ElasticEaseIn;
	//typedef Easing<ElasticEaseOutFunction> ElasticEaseOut;
	//typedef Easing<ElasticEaseInOutFunction> ElasticEaseInOut;


	double BackEaseInFunction(double p);
	double BackEaseOutFunction(double p);
	double BackEaseInOutFunction(double p);

	//typedef Easing<BackEaseInFunction> BackEaseIn;
	//typedef Easing<BackEaseOutFunction> BackEaseOut;
	//typedef Easing<BackEaseInOutFunction> BackEaseInOut;


	double BounceEaseInFunction(double p);
	double BounceEaseOutFunction(double p);
	double BounceEaseInOutFunction(double p);

	//typedef Easing<BounceEaseInFunction> BounceEaseIn;
	//typedef Easing<BounceEaseOutFunction> BounceEaseOut;
	//typedef Easing<BounceEaseInOutFunction> BounceEaseInOut;


	class Easing
	{
	public:
		Easing(double start, double end, EasingType type) :
			m_StartTime(start),
			m_EndTime(end),
			m_EasingType(type)
		{

		}

		~Easing(){}

		double GetValue(double currentTime) const
		{
			double percentage = (currentTime - m_StartTime) / (m_EndTime - m_StartTime);
			switch (m_EasingType)
			{
				case EASING_LINEAR: return LinearEasingFunction(percentage);

				case EASING_QUADRATIC_IN: return QuadraticEaseInFunction(percentage);
				case EASING_QUADRATIC_OUT: return QuadraticEaseOutFunction(percentage);
				case EASING_QUADRATIC_INOUT:return QuadraticEaseInOutFunction(percentage);

				case EASING_CUBIC_IN: return CubicEaseInFunction(percentage);
				case EASING_CUBIC_OUT:return CubicEaseOutFunction(percentage);
				case EASING_CUBIC_INOUT:return CubicEaseInOutFunction(percentage);

				case EASING_QUARTIC_IN: return QuarticEaseInFunction(percentage);
				case EASING_QUARTIC_OUT: return QuarticEaseOutFunction(percentage);
				case EASING_QUARTIC_INOUT: return QuarticEaseInOutFunction(percentage);

				case EASING_QUINTIC_IN: return QuinticEaseInFunction(percentage);
				case EASING_QUINTIC_OUT:return QuinticEaseOutFunction(percentage);
				case EASING_QUINTIC_INOUT:return QuinticEaseInOutFunction(percentage);

				case EASING_SINE_IN:return SineEaseInFunction(percentage);
				case EASING_SINE_OUT:return SineEaseOutFunction(percentage);
				case EASING_SINE_INOUT:return SineEaseInOutFunction(percentage);

				case EASING_CIRCULAR_IN: return CircularEaseInFunction(percentage);
				case EASING_CIRCULAR_OUT:return CircularEaseOutFunction(percentage);
				case EASING_CIRCULAR_INOUT:return CircularEaseInOutFunction(percentage);

				case EASING_EXPONENTIAL_IN: return ExponentialEaseInFunction(percentage);
				case EASING_EXPONENTIAL_OUT: return ExponentialEaseOutFunction(percentage);
				case EASING_EXPONENTIAL_INOUT: return ExponentialEaseInOutFunction(percentage);

				case EASING_ELASTIC_IN: return ElasticEaseInFunction(percentage);
				case EASING_ELASTIC_OUT: return ElasticEaseOutFunction(percentage);
				case EASING_ELASTIC_INOUT:return ElasticEaseInOutFunction(percentage);

				case EASING_BACK_IN: return BackEaseInFunction(percentage);
				case EASING_BACK_OUT:return BackEaseOutFunction(percentage);
				case EASING_BACK_INOUT:return BackEaseInOutFunction(percentage);

				case EASING_BOUNCE_IN: return BounceEaseInFunction(percentage);
				case EASING_BOUNCE_OUT: return BounceEaseOutFunction(percentage);
				case EASING_BOUNCE_INOUT:return BounceEaseInOutFunction(percentage);
                    
                case EASING_END:
                default:
                    LinearEasingFunction(percentage);
			}
			return LinearEasingFunction(percentage);
		}

		std::vector<double> PreComputeValues(size_t numValues)
		{
			std::vector<double> values;
			values.reserve(numValues);

			double step = (m_EndTime - m_StartTime) / (double) (numValues - 1);
			double counter = m_StartTime;
			for (size_t i = 0; i < numValues; ++i)
			{
				values.push_back(GetValue(counter));
				counter += step;
			}
			return values;
		}

		bool IsComplete(double currentTime) const
		{
			return (currentTime >= m_EndTime);
		}

	private:
		double m_StartTime;
		double m_EndTime;
		EasingType m_EasingType;
	};

	

}

#endif

