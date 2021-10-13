// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from loader.djinni
#ifdef __cplusplus

#include "VectorTileHolderInterface.h"
#include <memory>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@protocol MCVectorTileHolderInterface;

namespace djinni_generated {

class VectorTileHolderInterface
{
public:
    using CppType = std::shared_ptr<::VectorTileHolderInterface>;
    using CppOptType = std::shared_ptr<::VectorTileHolderInterface>;
    using ObjcType = id<MCVectorTileHolderInterface>;

    using Boxed = VectorTileHolderInterface;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCppOpt(const CppOptType& cpp);
    static ObjcType fromCpp(const CppType& cpp) { return fromCppOpt(cpp); }

private:
    class ObjcProxy;
};

}  // namespace djinni_generated

#endif
