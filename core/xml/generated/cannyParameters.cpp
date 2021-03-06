/**
 * \file cannyParameters.cpp
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 */

#include <vector>
#include <stddef.h>
#include "cannyParameters.h"

/**
 *  Looks extremely unsafe because it depends on the order of static initialization.
 *  Should check standard if this is ok
 *
 *  Also it's not clear why removing "= Reflection()" breaks the code;
 **/

namespace corecvs {
template<>
Reflection BaseReflection<CannyParameters>::reflection = Reflection();
template<>
int BaseReflection<CannyParameters>::dummy = CannyParameters::staticInit();
} // namespace corecvs 

SUPPRESS_OFFSET_WARNING_BEGIN

int CannyParameters::staticInit()
{

    ReflectionNaming &nameing = naming();
    nameing = ReflectionNaming(
        "Canny Parameters",
        "Canny Parameters",
        ""
    );
     

    fields().push_back(
        new BoolField
        (
          CannyParameters::SHOULD_EDGE_DETECT_ID,
          offsetof(CannyParameters, mShouldEdgeDetect),
          false,
          "Should edge detect",
          "Should edge detect",
          "Should edge detect"
        )
    );
    fields().push_back(
        new IntField
        (
          CannyParameters::MINIMUM_THRESHOLD_ID,
          offsetof(CannyParameters, mMinimumThreshold),
          500,
          "Minimum threshold",
          "Minimum threshold",
          "Minimum threshold"
        )
    );
    fields().push_back(
        new IntField
        (
          CannyParameters::MAXIMUM_THRESHOLD_ID,
          offsetof(CannyParameters, mMaximumThreshold),
          1500,
          "Maximum threshold",
          "Maximum threshold",
          "Maximum threshold"
        )
    );
   return 0;
}

SUPPRESS_OFFSET_WARNING_END


