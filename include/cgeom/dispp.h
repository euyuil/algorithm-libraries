#ifndef _CGEOM_DISPP_H_
#define _CGEOM_DISPP_H_

/**
 * @date 2011-08-16
 */

inline double dispp(const point &a, const point &b) {
    return (b - a).mag();
}

#endif /* _CGEOM_DISPP_H_ */
