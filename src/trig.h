#ifndef __FAST_SIN__
#define __FAST_SIN__

#include <stdbool.h>

// Constants used for speedy calculation of the (next) approximation
static const double FAST_SIN_PI = 3.141592653589793;
static const double PI_DIV_2 = 3.141592653589793 / 2.0;
static const double PI_MULT_3_DIV_2 = 3.141592653589793 * 3.0 / 2.0;
static const double PI_MULT_2 = 2.0 * 3.141592653589793;
static const double PI_MULT_4 = 4.0 * 3.141592653589793;

typedef struct FastSin
{
    // Variables to store information about the previous Sine calculation. These
    // can then be used to calculate fast the next Sine value.
    bool m_hasValidPreviousAngle;
    double m_previousAngle;
    int m_previousFullCyckles;
    double m_previousFullCycklesAngle;
} FastSin;

// In C, we need an explicit initialization function to set default values
// that were defined in the C++ class body.
void FastSin_Init(FastSin* self)
{
    self->m_hasValidPreviousAngle = false;
    self->m_previousAngle = 0.0;
    self->m_previousFullCyckles = 0;
    self->m_previousFullCycklesAngle = 0.0;
}

// Internal helper to handle the angle logic shared between Degree 7 and 9
static void FastSin_UpdateAngle(FastSin* self, double angle, double* angleShort, bool* sign)
{
    // If previous angle is "near" (near is about 2*Pi) use it as an 
    // advantage to calculate the new angle - it is faster to calculate
    // knowing the information about the last angle values.
    if (self->m_hasValidPreviousAngle)
    {
        const double diff = angle - self->m_previousAngle;
        *angleShort = angle - self->m_previousFullCycklesAngle;
        if (diff > 0.0)
        {
            if (*angleShort > PI_MULT_2)
            {
                if (*angleShort <= PI_MULT_4)
                {
                    ++self->m_previousFullCyckles;
                    self->m_previousFullCycklesAngle = self->m_previousFullCyckles * PI_MULT_2;
                    *angleShort = angle - self->m_previousFullCycklesAngle;
                }
                else
                    self->m_hasValidPreviousAngle = false;
            }
        }
        else
        {
            if (*angleShort < 0.0)
            {
                if (*angleShort >= -PI_MULT_2)
                {
                    --self->m_previousFullCyckles;
                    self->m_previousFullCycklesAngle = self->m_previousFullCyckles * PI_MULT_2;
                    *angleShort = angle - self->m_previousFullCycklesAngle;
                }
                else
                    self->m_hasValidPreviousAngle = false;
            }
        }
    }
    // If we do not have previous angle (to calculate fast), just use a formula
    // which works for all angles but is slower.
    if (!self->m_hasValidPreviousAngle)
    {
        const double div = angle / PI_MULT_2; // quite slow
        self->m_previousFullCyckles = (int)div;
        self->m_previousFullCycklesAngle = self->m_previousFullCyckles * PI_MULT_2;
        *angleShort = (div - (int)div) * PI_MULT_2; // quite slow
    }

    // The polynomial approximation only knows the values from the first quarter section (0 - Pi/2) of the radians unit
    // circle (0 - 2*Pi), so if the angle is on the other 3 quarter sections of the unit circle (Pi/2 - 2*Pi) we need
    // to find the corresponding value (or its negation value) on the first section. Note: If we know all the values 
    // from the first quarter or the unit circle, then we can get the value also for other sections 
    // (Pi/2 - 2*Pi).
    *sign = true; // true for positive, false for negative
    if (*angleShort > PI_DIV_2 && *angleShort <= FAST_SIN_PI)
        *angleShort = FAST_SIN_PI - *angleShort;
    else if (*angleShort > FAST_SIN_PI && *angleShort <= PI_MULT_3_DIV_2)
    {
        *angleShort = *angleShort - FAST_SIN_PI;
        *sign = false;
    }
    else if (*angleShort > PI_MULT_3_DIV_2 && *angleShort <= PI_MULT_2)
    {
        *angleShort = PI_MULT_2 - *angleShort;
        *sign = false;
    }

    self->m_previousAngle = angle;
    self->m_hasValidPreviousAngle = true;
}

// Equivalent to FastSin<double, 7>::operator()(double angle)
double FastSin_Calculate7(FastSin* self, const double angle)
{
    double angleShort;
    bool signPositive;
    FastSin_UpdateAngle(self, angle, &angleShort, &signPositive);

    const double x1 = angleShort;
    const double x2 = angleShort * angleShort;
    double sign = signPositive ? 1.0 : -1.0;

    // degree 7 - Maximum error (*): 9.39101e-07
    return sign * x1 * (0.999999060898976 + x2 * (-0.166655540927576 +
        x2 * (0.00831189980138987 - 0.000184881402886071 * x2)));
}

// Equivalent to FastSin<double, 9>::operator()(double angle)
double FastSin_Calculate9(FastSin* self, const double angle)
{
    double angleShort;
    bool signPositive;
    FastSin_UpdateAngle(self, angle, &angleShort, &signPositive);

    const double x1 = angleShort;
    const double x2 = angleShort * angleShort;
    double sign = signPositive ? 1.0 : -1.0;

    // degree 9 - Maximum error (*): 5.31399e-09
    return sign * x1 * (0.999999994686007 + x2 * (-0.166666566840071 +
        x2 * (0.00833302513896936 + x2 * (-0.000198074187274269 +
            2.601903067651460e-6 * x2))));
}

// Float version of Degree 7 calculation
float FastSin_Calculate7f(FastSin* self, const float angle)
{
    double angleShort;
    bool signPositive;
    FastSin_UpdateAngle(self, (double)angle, &angleShort, &signPositive);

    const float x1 = (float)angleShort;
    const float x2 = (float)(angleShort * angleShort);
    float sign = signPositive ? 1.0f : -1.0f;

    return sign * x1 * (0.999999060898976f + x2 * (-0.166655540927576f +
        x2 * (0.00831189980138987f - 0.000184881402886071f * x2)));
}

// Float version of Degree 9 calculation
float FastSin_Calculate9f(FastSin* self, const float angle)
{
    double angleShort;
    bool signPositive;
    FastSin_UpdateAngle(self, (double)angle, &angleShort, &signPositive);

    const float x1 = (float)angleShort;
    const float x2 = (float)(angleShort * angleShort);
    float sign = signPositive ? 1.0f : -1.0f;

    return sign * x1 * (0.999999994686007f + x2 * (-0.166666566840071f +
        x2 * (0.00833302513896936f + x2 * (-0.000198074187274269f +
            2.601903067651460e-6f * x2))));
}

#endif // __FAST_SIN__
