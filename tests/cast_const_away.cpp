#include "test.hpp"
#include <zxshady/extra_traits/casts.hpp>

extern int i;
extern const int ci;
extern volatile int              vi;
extern const volatile int        cvi;

extern const int* pci;
extern int* const cpi;
extern const int*const cpci;

extern volatile int* pvi;
extern int* volatile vpi;
extern volatile int* volatile vpvi;

extern const volatile int* pcvi;
extern int* const volatile      cvpi;
extern const volatile int* const volatile cvpcvi;

IS_SAME(decltype(zxshady::tmp::cast_const_away(i)), int&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(ci)), int&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(vi)), volatile int&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(cvi)), volatile int&);

IS_SAME(decltype(zxshady::tmp::cast_const_away(cpi)), int*&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(pci)), const int*&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(cpci)), const int*&);

IS_SAME(decltype(zxshady::tmp::cast_const_away(vpi)), int* volatile&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(pvi)), volatile int*&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(vpvi)), volatile int* volatile&);

IS_SAME(decltype(zxshady::tmp::cast_const_away(cvpi)), int* volatile&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(pcvi)), const volatile int*&);
IS_SAME(decltype(zxshady::tmp::cast_const_away(cvpcvi)), const volatile int* volatile&);
