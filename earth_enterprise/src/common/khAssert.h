/*
 * Copyright 2017 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __khAssert_h
#define __khAssert_h

// ****************************************************************************
// ***  This Compile Time Assertion idiom comes from:
// ***  "Modern C++ Design" Chapter 2
// ***
// ***  Usage:
// ***  Use like a statement anywhere you would use 'assert()'
// ***  COMPILE_TIME_ASSERT(expr, MsgAsAnItentifier);
// ***  The expression can be any compile time resolvable expression
// ***  The error message must be in the form of a C++ Identifier
// ***
// ***  Examples:
// ***  COMPILE_TIME_ASSERT(sizeof(FFRecHeader) == 32, InvalidFFRecHeaderSize);
// ***  COMPILE_TIME_ASSERT(RasterProductTileResolution == 1024,
// ***                     SomebodyMessedWithTheTileSize);
// ***
// ***  The error messages generated by the compiler are a bit cryptic, but
// ***  they at least contain the supplied message.
// ***  foo2.cpp:42: error: no matching function for call to `CompileTimeChecker<false>::CompileTimeChecker(main(int, char**)::ERROR_InvalidFFRecHeaderSize*&)'
// ****************************************************************************
template <bool>
struct CompileTimeChecker {
  CompileTimeChecker(...);
};

template <>
struct CompileTimeChecker<false> { };

#define COMPILE_TIME_ASSERT(expr, msg)                                  \
{                                                                       \
    class ERROR_##msg { };                                              \
    (void)sizeof(CompileTimeChecker<(expr) != 0>(new ERROR_##msg()));   \
}

// ****************************************************************************
// ***  Like COMPILE_TIME_ASSERT but can also be used outsize of functions (if
// ***  you're careful). Unlike COMPILE_TIME_ASSERT, this one pollutes the
// ***  namespace. ERROR_##msg and DummyTypedef_##msg are defined into the
// ***  current namespace. So placing two COMPILE_TILE_CHECK's with the same
// ***  msg identifier will result in redefinition errors.
// ****************************************************************************
template<class chk> struct ERROR_dummy { };

#define COMPILE_TIME_CHECK(expr, msg)    \
struct ERROR_##msg { };    \
typedef ERROR_dummy<typeof(CompileTimeChecker<((expr) != 0)>(new ERROR_##msg()))> DummyTypedef_##msg;





#endif /* __khAssert_h */
