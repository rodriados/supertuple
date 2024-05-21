/**
 * SuperTuple: A powerful and light-weight C++ tuple implementation.
 * @file The project's main header file.
 * @author Rodrigo Siqueira <rodriados@gmail.com>
 * @copyright 2024-present Rodrigo Siqueira
 */
#pragma once

#include <supertuple/version.h>
#include <supertuple/environment.h>

#include <supertuple/tuple.hpp>

#include <supertuple/operation/get.hpp>
#include <supertuple/operation/set.hpp>
#include <supertuple/operation/tie.hpp>
#include <supertuple/operation/head.hpp>
#include <supertuple/operation/last.hpp>
#include <supertuple/operation/init.hpp>
#include <supertuple/operation/tail.hpp>
#include <supertuple/operation/reverse.hpp>
#include <supertuple/operation/append.hpp>
#include <supertuple/operation/prepend.hpp>
#include <supertuple/operation/concat.hpp>
#include <supertuple/operation/apply.hpp>
#include <supertuple/operation/forward.hpp>
#include <supertuple/operation/foreach.hpp>
#include <supertuple/operation/fold.hpp>
#include <supertuple/operation/scan.hpp>
#include <supertuple/operation/zip.hpp>
#include <supertuple/operation/zipwith.hpp>
#include <supertuple/operation/convert.hpp>
