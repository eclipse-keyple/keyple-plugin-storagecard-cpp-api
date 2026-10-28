# *****************************************************************************
# Copyright (c) 2026 Calypso Networks Association https://calypsonet.org/     *
#                                                                             *
# This program and the accompanying materials are made available under the    *
# terms of the MIT License which is available at                              *
# https://opensource.org/licenses/MIT.                                        *
#                                                                             *
# SPDX-License-Identifier: MIT                                                *
# *****************************************************************************/

SET(EXECTUABLE_NAME keypluginstoragecardcppapi_ut)

INCLUDE_DIRECTORIES(

    ${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_EXECUTABLE(

    ${EXECTUABLE_NAME}

    ${CMAKE_CURRENT_SOURCE_DIR}/MainTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/PluginStorageCardApiPropertiesTest.cpp
)

# Add necessary deps
INCLUDE(CMakeLists.txt.googletest)

TARGET_LINK_LIBRARIES(

    ${EXECTUABLE_NAME}

    PRIVATE

    gtest
    gmock
    Keyple::Plugin::StorageCard
)
