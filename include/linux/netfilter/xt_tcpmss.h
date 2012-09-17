#ifndef _XT_TCPMSS_H
#define _XT_TCPMSS_H

#include <linux/types.h>

struct xt_tcpmss_match_info {
    __u16 mss_min, mss_max;
    __u8 invert;
};

#define XT_TCPMSS_CLAMP_PMTU 0xffff

#endif /* _XT_TCPMSS_H */
