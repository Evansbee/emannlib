//
//  Easing.cpp
//  goldenduckLib
//
//  Created by Evan Ackmann on 5/7/14.
//
//

#include "Easing.hpp"
#include "Math.hpp"
#include <math.h>

namespace goldenduck
{
    
        
        double LinearEasingFunction(double p)
		{
			return p;
		}
      
        
        /// Modeled after the parabola: y = x^2
        double QuadraticEaseInFunction(double p) 
		{ 
			return p * p; 
		}
        
        /// Modeled after the parabola: y = -x^2 + 2x
        double QuadraticEaseOutFunction(double p) 
		{ 
			return -(p * (p - 2)); 
		}
        
        /// Modeled after the piecewise quadratic: y = (1/2)((2x)^2) [0, 0.5] | y = -(1/2)((2x-1)*(2x-3) - 1) [0.5, 1]
        double QuadraticEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 2 * p * p : (-2 * p * p) + (4 * p) - 1; 
		}
     
        
        /// Modeled after the cubic: y = x^3
        double CubicEaseInFunction(double p) 
		{ 
			return p * p * p; 
		}
        
        /// Modeled after the cubic: y = (x - 1)^3 + 1
        double CubicEaseOutFunction(double p) 
		{ 
			return (p - 1) * (p - 1) * (p - 1) + 1; 
		}
        
        /// Modeled after the piecewise cubic: y = (1/2)((2x)^3) [0, 0.5) | y = (1/2)((2x-2)^3 + 2) [0.5, 1]
        double CubicEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 4 * p * p * p : 0.5 * ((2 * p) - 2) * ((2 * p) - 2) * ((2 * p) - 2) + 1; 
		}
        
     
        
        
        
        /* ***** Quartic easing p^4 ***** */
        
        /// Modeled after the quartic: y = x^4
        double QuarticEaseInFunction(double p) 
		{ 
			return p * p * p * p; 
		}
        
        /// Modeled after the quartic: y = 1 - (x - 1)^4
        double QuarticEaseOutFunction(double p) 
		{ 
			return (p - 1) * (p - 1) * (p - 1) * (1 - p) + 1; 
		}
        
        /// Modeled after the piecewise quartic: y = (1/2)((2x)^4) [0, 0.5] | y = -(1/2)((2x-2)^4 - 2) [0.5, 1]
        double QuarticEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 8 * p * p * p * p : -8 * (p - 1) * (p - 1) * (p - 1) * (p - 1) + 1; 
		}
        
        
        
        
        /// Modeled after the quintic: y = x^5
        double QuinticEaseInFunction(double p) 
		{ 
			return p * p * p * p * p; 
		}
        
        /// Modeled after the quintic: y = (x - 1)^5 + 1
        double QuinticEaseOutFunction(double p) 
		{ 
			return (p - 1) * (p - 1) * (p - 1) * (p - 1) * (p - 1) + 1; 
		}
        
        /// Modeled after the piecewise quintic: y = (1/2)((2x)^5) [0, 0.5] | y = (1/2)((2x-2)^5 + 2) [0.5, 1]
        double QuinticEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 16 * p * p * p * p * p : 0.5 * ((2 * p) - 2) * ((2 * p) - 2) * ((2 * p) - 2) * ((2 * p) - 2) * ((2 * p) - 2) + 1; 
		}
        

        
        
        
        /// Modeled after quarter-cycle of sine wave
		double SineEaseInFunction(double p) 
		{ 
			return goldenduck::Math<double>::Sin((p - 1) * goldenduck::Math<double>::HALF_PI) + 1; 
		}
        
        /// Modeled after quarter-cycle of sine wave (different phase)
		double SineEaseOutFunction(double p) 
		{ 
			return goldenduck::Math<double>::Sin(p * goldenduck::Math<double>::HALF_PI);
		}
        
        /// Modeled after half sine wave
		double SineEaseInOutFunction(double p) 
		{ 
			return 0.5 * (1 - goldenduck::Math<double>::Cos(p * goldenduck::Math<double>::PI));
		}
        
    
        
        
        /* ***** Circular easing sqrt(1 - p^2) ***** */
        
        /// Modeled after shifted quadrant IV of unit circle
		double CircularEaseInFunction(double p) 
		{ 
			return 1 - goldenduck::Math<double>::Sqrt(1 - (p * p));
		}
        
        /// Modeled after shifted quadrant II of unit circle
		double CircularEaseOutFunction(double p) 
		{ 
			return goldenduck::Math<double>::Sqrt((2 - p) * p);
		}
        
        /// Modeled after the piecewise circular function: y = (1/2)(1 - sqrt(1 - 4x^2)) [0, 0.5] | y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) [0.5, 1]
		double CircularEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 0.5 * (1 - goldenduck::Math<double>::Sqrt(1 - 4 * (p * p))) : 0.5 * (goldenduck::Math<double>::Sqrt(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
		}
       
        
        
        /* ***** Exponential easing, base 2 ***** */
        
        /// Modeled after the exponential function: y = 2^(10(x - 1))
		double ExponentialEaseInFunction(double p) 
		{ 
			return (p == 0.0) ? p : goldenduck::Math<double>::Pow(2, 10 * (p - 1));
		}
        
        /// Modeled after the exponential function: y = -2^(-10x) + 1
		double ExponentialEaseOutFunction(double p) 
		{ 
			return (p == 1.0) ? p : 1 - goldenduck::Math<double>::Pow(2, -10 * p);
		}
        
        /// Modeled after the piecewise exponential: y = (1/2)2^(10(2x - 1)) [0,0.5] | y = -(1/2)*2^(-10(2x - 1))) + 1 [0.5,1]
		double ExponentialEaseInOutFunction(double p) 
		{ 
			return (p == 0.0 || p == 1.0) ? p : (p < 0.5) ? 0.5 * goldenduck::Math<double>::Pow(2, (20 * p) - 10) : -0.5 * goldenduck::Math<double>::Pow(2, (-20 * p) + 10) + 1;
		}
        

        
        /* ***** Exponentially-damped sine wave easing ***** */
        
        /// Modeled after the damped sine wave: y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
		double ElasticEaseInFunction(double p) 
		{ 
			return goldenduck::Math<double>::Sin(13 * goldenduck::Math<double>::HALF_PI * p) * goldenduck::Math<double>::Pow(2, 10 * (p - 1));
		}
        
        /// Modeled after the damped sine wave: y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
		double ElasticEaseOutFunction(double p) 
		{ 
			return goldenduck::Math<double>::Sin(-13 * goldenduck::Math<double>::HALF_PI * (p + 1)) * goldenduck::Math<double>::Pow(2, -10 * p) + 1;
		}
        
        /// Modeled after the piecewise exponentially-damped sine wave: y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1)) [0,0.5] | y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) [0.5, 1]
		double ElasticEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 0.5 *  goldenduck::Math<double>::Sin(13 * goldenduck::Math<double>::HALF_PI * (2 * p)) * goldenduck::Math<double>::Pow(2, 10 * ((2 * p) - 1)) : 0.5 * (goldenduck::Math<double>::Sin(-13 * goldenduck::Math<double>::HALF_PI * ((2 * p - 1) + 1)) * goldenduck::Math<double>::Pow(2, -10 * (2 * p - 1)) + 2);
		}
        
      
        
        
        /* ***** Overshooting cubic easing ***** */
        /// Modeled after the overshooting cubic: y = x^3-x*sin(x*pi)
		double BackEaseInFunction(double p) 
		{ 
			return p * p * p - p * goldenduck::Math<double>::Sin(p * goldenduck::Math<double>::PI);
		}
        
        /// Modeled after overshooting cubic: y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
		double BackEaseOutFunction(double p) 
		{ 
			return 1 - ((1 - p) * (1 - p) * (1 - p) - (1 - p) * goldenduck::Math<double>::Sin((1 - p) * goldenduck::Math<double>::PI));
		}
        
        /// Modeled after the piecewise overshooting cubic function: y = (1/2)*((2x)^3-(2x)*sin(2*x*pi)) [0, 0.5] | y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) [0.5, 1]
		double BackEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 0.5 * (8 * p * p * p - (2 * p) * goldenduck::Math<double>::Sin((2 * p) * goldenduck::Math<double>::PI)) : 0.5 * (1 - ((1 - (2 * p - 1)) * (1 - (2 * p - 1)) * (1 - (2 * p - 1)) - (1 - (2 * p - 1)) * goldenduck::Math<double>::Sin((1 - (2 * p - 1)) * goldenduck::Math<double>::PI))) + 0.5;
		}
        
   
        
        

        ///
        double BounceEaseInFunction(double p) 
		{
			return 1 - BounceEaseOutFunction(1 - p); 
		}
        
        ///
        double BounceEaseOutFunction(double p) 
		{ 
			return (p < 4/11.0) ? (121 * p * p)/16.0 : (p < 8/11.0) ? (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0 : (p < 9/10.0) ? (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0 : (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0; 
		}
        
        ///
        double BounceEaseInOutFunction(double p) 
		{ 
			return (p < 0.5) ? 0.5 * BounceEaseInFunction(p*2) : 0.5 * BounceEaseOutFunction(p * 2 - 1) + 0.5; 
		}
        
    
}
