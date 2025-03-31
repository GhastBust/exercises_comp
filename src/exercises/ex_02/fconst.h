#ifndef __FCONST_H__
#define __FCONST_H__

static const double R = 1.93;
static const double Mn = 939.565;
static const double Mp = 938.272;
// static const double c = 299792458;
static const double uc2 = Mn*Mp/(Mn+Mp);
static const double hc = 197.327;
static const double V0 = 38.5;
static const double lambda = hc*hc/2/uc2/R/R;
static const double v = V0 / lambda;

static const double E = -0.190408573835450875 * lambda;

#endif //__FCONST_H__