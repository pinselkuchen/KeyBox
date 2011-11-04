#ifndef SITOBJECT_H
#define SITOBJECT_H

#include "boost/smart_ptr.hpp"
#include "sitLog.h"

namespace sit{

#define sitObjectMacro( object )\
    typedef boost::shared_ptr<object> Pointer;\
    typedef boost::scoped_ptr<object> ScpPointer;\
    typedef boost::weak_ptr<object> Weakpointer;

}



#endif // SITOBJECT_H
