#ifndef _CGEOM_DISPL_H_
#define _CGEOM_DISPL_H_

/**
 * @date 2011-08-16
 */

inline double displ(const point &p, const line &l) {
    return abs(cross(l.vec(), p - l.a)) / l.len();
}

#endif /* _CGEOM_DISPL_H_ */
