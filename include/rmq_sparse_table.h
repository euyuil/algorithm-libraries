#ifndef _RMQ_SPARSE_TABLE_
#define _RMQ_SPARSE_TABLE_

/**
 * Is it really RMQ? This data structure can do only range query but not
 * modify.
 * 2013-03-24
 */

#include <vector>

template <typename Comparator>
class RMQSparseTable
{
public:

    RMQSparseTable()
    {
    }

    virtual ~RMQSparseTable()
    {
    }

private:

    std::vector<std::vector> dp;

};

#endif /* _RMQ_SPARSE_TABLE_ */
