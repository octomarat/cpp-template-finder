#ifndef __TEMPLATE_FINDER_H__
#define __TEMPLATE_FINDER_H__

#include <vector>
#include <string>

#include "clang/Tooling/Tooling.h"

#include "collected_data.h"

namespace template_finder {

CollectedData FindTemplates(
    const std::vector<std::string> &src_paths,
    const clang::tooling::CompilationDatabase &compilations
);

}

#endif
