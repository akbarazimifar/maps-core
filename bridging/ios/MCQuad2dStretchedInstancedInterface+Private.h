// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from graphicsobjects.djinni
#ifdef __cplusplus

#include "Quad2dStretchedInstancedInterface.h"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol MCQuad2dStretchedInstancedInterface;

namespace djinni_generated {

class Quad2dStretchedInstancedInterface
{
public:
    using CppType = std::shared_ptr<::Quad2dStretchedInstancedInterface>;
    using CppOptType = std::shared_ptr<::Quad2dStretchedInstancedInterface>;
    using ObjcType = id<MCQuad2dStretchedInstancedInterface>;

    using Boxed = Quad2dStretchedInstancedInterface;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

} // namespace djinni_generated

#endif
