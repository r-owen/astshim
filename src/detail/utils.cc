#include "astshim/detail/utils.h"

namespace ast {
namespace detail {

void astBadToNan(ast::Array2D & arr) {
    for (auto i = arr.begin(); i != arr.end(); ++i) {
        for (auto j = i->begin(); j != i->end(); ++j) {
            if (*j == AST__BAD) {
                *j = std::numeric_limits<double>::quiet_NaN();
            }
        }
    }
}

std::string getClassName(AstObject * rawObj) {
    std::string name = astGetC(rawObj, "Class");
    assertOK();
    if (name != "CmpName") {
        return name;
    }
    bool series = isSeries(reinterpret_cast<AstCmpMap *>(rawObj));
    return series ? "SeriesMap" : "ParallelMap";
}

bool isSeries(AstCmpMap * cmpMap) {
    AstMapping * rawMap1;
    AstMapping * rawMap2;
    int series, invert1, invert2;
    astDecompose(cmpMap, &rawMap1, &rawMap2, &series, &invert1, &invert2);
    assertOK();
    return series;
}

}  // detail
}  // ast