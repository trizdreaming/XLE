// Copyright 2015 XLGAMES Inc.
//
// Distributed under the MIT License (See
// accompanying file "LICENSE" or the website
// http://www.opensource.org/licenses/mit-license.php)

#include "../Utility/ParameterBox.h"
#include "../Utility/SystemUtils.h"
#include "../Utility/StringFormat.h"
#include "../Math/Vector.h"
#include <CppUnitTest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
    TEST_CLASS(Utilities)
    {
    public:
        TEST_METHOD(ParameterBoxTest)
        {
            ParameterBox test(
                {
                    std::make_pair("SomeParam", "1ul"),
                    std::make_pair("SomeParam1", ".4f"),
                    std::make_pair("SomeParam2", "344.f"),
                    std::make_pair("SomeParam3", ".56f"),
                    std::make_pair("VectorParam", "{4.5f, 7.5f, 9.5f}v"),
                    std::make_pair("ColorParam", "{.5f, .5f, .5f}c")
                });

            Assert::AreEqual(test.GetParameter<unsigned>("SomeParam").second, 1u, L"String parsing and constructor");
            Assert::AreEqual(test.GetParameter<float>("SomeParam1").second, .4f, L"String parsing and constructor");
            Assert::AreEqual(test.GetParameter<float>("SomeParam2").second, 344.f, 0.001f, L"String parsing and constructor");
            Assert::AreEqual(test.GetParameter<float>("SomeParam3").second, .56f, 0.001f, L"String parsing and constructor");

            test.SetParameter("AParam", false);
            test.SetParameter("AParam", 5);
            test.SetParameter("AParam", 5.f);
            test.SetParameter("AParam", 500.f);
            Assert::AreEqual(test.GetParameter<float>("AParam").second, 500.f, 0.001f, L"Changing parameter types");

            test.SetParameter("ShouldBeTrue", true);
            Assert::AreEqual(test.GetParameter<bool>("ShouldBeTrue").second, true, L"Store/retrieve boolean");

            std::vector<std::pair<const char*, std::string>> stringTable;
            test.BuildStringTable(stringTable);

            for (auto i=stringTable.begin(); i!=stringTable.end(); ++i) {
                XlOutputDebugString(
                    StringMeld<256>() << i->first << " = " << i->second << "\n");
            }

        }

        TEST_METHOD(ImpliedTypingTest)
        {
            auto t0 = ImpliedTyping::Parse<Float4>("{.5f, 10, true}");
            Assert::IsTrue(
                t0.first && Equivalent(t0.second, Float4(.5f, 10.f, 1.f, 1.f), 0.001f),
                L"Parse with array element cast");
            
            auto t1 = ImpliedTyping::Parse<Float4>("23");
            Assert::IsTrue(
                t1.first && Equivalent(t1.second, Float4(23.f, 0.f, 0.f, 1.f), 0.001f),
                L"Scalar to array cast");

            Assert::AreEqual(ImpliedTyping::Parse<signed>("true").second, 1, L"bool to signed cast");
            Assert::AreEqual(ImpliedTyping::Parse<signed>("{true, 60, 1.f}").second, 1, L"bool array to signed cast");
        }
    };
}
