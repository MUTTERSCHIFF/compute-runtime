/*
 * Copyright (c) 2017, Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "unit_tests/global_environment.h"
#include "unit_tests/helpers/kernel_binary_helper.h"
#include "unit_tests/helpers/test_files.h"

#include <string>

extern PRODUCT_FAMILY productFamily;

const std::string KernelBinaryHelper::BUILT_INS("15895692906525787409");

KernelBinaryHelper::KernelBinaryHelper(const std::string &name, bool appendOptionsToFileName) {
    // set mock compiler to return expected kernel
    MockCompilerDebugVars fclDebugVars;
    MockCompilerDebugVars igcDebugVars;

    std::string builtInFileRoot = testFiles + name + "_";
    std::string builtInBcFile = builtInFileRoot;
    std::string builtInGenFile = builtInFileRoot;

    auto product = hardwarePrefix[productFamily];
    builtInBcFile.append(product);
    builtInGenFile.append(product);
    builtInBcFile.append(".bc");
    builtInGenFile.append(".gen");

    fclDebugVars.fileName = builtInBcFile;
    igcDebugVars.fileName = builtInGenFile;

    fclDebugVars.appendOptionsToFileName = appendOptionsToFileName;
    igcDebugVars.appendOptionsToFileName = appendOptionsToFileName;

    gEnvironment->fclPushDebugVars(fclDebugVars);
    gEnvironment->igcPushDebugVars(igcDebugVars);
}

KernelBinaryHelper::~KernelBinaryHelper() {
    gEnvironment->igcPopDebugVars();
    gEnvironment->fclPopDebugVars();
}
