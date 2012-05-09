#ifndef _CGEOM_SIMTRTR_H_
#define _CGEOM_SIMTRTR_H_

inline bool simtrtr(const triangle &u, const triangle &v) {
    return eq(u.x / v.x, u.y / v.y, u.z / v.z);
}

#endif /* _CGEOM_SIMTRTR_H_ */
