#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
/*******************************************************************************
*   (c) 2019 ZondaX GmbH
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
********************************************************************************/

#include <gmock/gmock.h>
#include "utils/testcases.h"

#include <iostream>
#include <memory>
#include "parser.h"
#include "utils/common.h"

using ::testing::TestWithParam;
using ::testing::Values;

void check_testcase(const testcase_t &testcase) {
    auto tc = ReadTestCaseData(testcase.testcases, testcase.index);

    parser_context_t ctx;
    parser_error_t err;

    // Define mainnet or testnet through derivation path
    // FIXME: Change based on testnet / mainnet
//    bip44Path[0] = BIP44_0_DEFAULT;
//    bip44Path[1] = BIP44_1_DEFAULT;
//    if (tc.testnet) {
//        bip44Path[0] = BIP44_0_TESTNET;
//        bip44Path[1] = BIP44_1_TESTNET;
//    }

    err = parser_parse(&ctx, tc.blob.data(), tc.blob.size());
    if (tc.valid) {
        ASSERT_EQ(err, parser_ok) << parser_getErrorDescription(err);
    } else {
        ASSERT_NE(err, parser_ok) << parser_getErrorDescription(err);
        return;
    }

    const bool_t isMainnet = tc.testnet ? bool_false : bool_true;
    err = parser_validate(&ctx, isMainnet);
    if (tc.valid) {
        EXPECT_EQ(err, parser_ok) << parser_getErrorDescription(err);
    } else {
        EXPECT_NE(err, parser_ok) << parser_getErrorDescription(err);
        return;
    }

    auto output = dumpUI(&ctx, 40, 40);

    std::cout << std::endl;
    for (const auto &i : output) {
        std::cout << i << std::endl;
    }

    std::cout << " EXPECTED ============" << std::endl;
    for (const auto &i : tc.expected_ui_output) {
        std::cout << i << std::endl;
    }

    EXPECT_EQ(output.size(), tc.expected_ui_output.size());
    for (size_t i = 0; i < tc.expected_ui_output.size(); i++) {
        if (i < output.size()) {
            EXPECT_THAT(output[i], testing::Eq(tc.expected_ui_output[i]));
        }
    }
}

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////

class VerifyTestVectors : public ::testing::TestWithParam<testcase_t> {
public:
    struct PrintToStringParamName {
        template<class ParamType>
        std::string operator()(const testing::TestParamInfo<ParamType> &info) const {
            auto p = static_cast<testcase_t>(info.param);
            std::stringstream ss;
            ss << std::setfill('0') << std::setw(5) << p.index << "_" << p.description;
            return ss.str();
        }
    };
};

INSTANTIATE_TEST_SUITE_P(
        KnownIssues,
        VerifyTestVectors,
        ::testing::ValuesIn(GetJsonTestCases("testvectors/known_issues.json")), VerifyTestVectors::PrintToStringParamName()
);

INSTANTIATE_TEST_SUITE_P(
        SendTx,
        VerifyTestVectors,
        ::testing::ValuesIn(GetJsonTestCases("testvectors/sendtx_tests.json")), VerifyTestVectors::PrintToStringParamName()
);

INSTANTIATE_TEST_SUITE_P(
        Multisig,
        VerifyTestVectors,
        ::testing::ValuesIn(GetJsonTestCases("testvectors/sendtx_multisig_tests.json")), VerifyTestVectors::PrintToStringParamName()
);

INSTANTIATE_TEST_SUITE_P(
        Votetx,
        VerifyTestVectors,
        ::testing::ValuesIn(GetJsonTestCases("testvectors/votetx_tests.json")), VerifyTestVectors::PrintToStringParamName()
);

INSTANTIATE_TEST_SUITE_P(
        Updatetx,
        VerifyTestVectors,
        ::testing::ValuesIn(GetJsonTestCases("testvectors/updatemultisigtx_tests.json")), VerifyTestVectors::PrintToStringParamName()
);

INSTANTIATE_TEST_SUITE_P(
        CreateProposaltx,
        VerifyTestVectors,
        ::testing::ValuesIn(GetJsonTestCases("testvectors/updateelectoratetx_tests.json")), VerifyTestVectors::PrintToStringParamName()
);

TEST_P(VerifyTestVectors, CheckUIOutput_Manual) { check_testcase(GetParam()); }

#pragma clang diagnostic pop
