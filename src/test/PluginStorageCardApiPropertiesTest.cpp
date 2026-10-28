/******************************************************************************
 * Copyright (c) 2026 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#include <regex>
#include <string>

#include "gtest/gtest.h"

#include "keyple/core/plugin/storagecard/PluginStorageCardApiProperties.hpp"

using keyple::core::plugin::storagecard::PluginStorageCardApiProperties_VERSION;

TEST(PluginStorageCardApiPropertiesTest, versionIsCorrectlyWritten)
{
    const std::string& apiVersion = PluginStorageCardApiProperties_VERSION;
    const std::regex r("\\d+\\.\\d+");

    ASSERT_TRUE(std::regex_match(apiVersion, r));
}
