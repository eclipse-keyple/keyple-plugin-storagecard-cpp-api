/******************************************************************************
 * Copyright (c) 2026 Calypso Networks Association https://calypsonet.org/    *
 *                                                                            *
 * This program and the accompanying materials are made available under the   *
 * terms of the MIT License which is available at                             *
 * https://opensource.org/licenses/MIT.                                       *
 *                                                                            *
 * SPDX-License-Identifier: MIT                                               *
 ******************************************************************************/

#pragma once

#include <memory>

#include "keyple/core/plugin/storagecard/ApduInterpreterFactory.hpp"
#include "keyple/core/plugin/storagecard/internal/spi/ApduInterpreterSpi.hpp"

namespace keyple {
namespace core {
namespace plugin {
namespace storagecard {
namespace internal {
namespace spi {

using keyple::core::plugin::storagecard::ApduInterpreterFactory;

/**
 * Factory interface for creating instances of ApduInterpreterSpi.
 *
 * <p>To be implemented by the storage card APDU interpreter.
 *
 * @since 1.0.0
 */
class ApduInterpreterFactorySpi : public ApduInterpreterFactory {
public:
    /**
     * Creates a new instance of an APDU interpreter.
     *
     * @return A new instance of ApduInterpreterSpi.
     * @since 1.0.0
     */
    virtual std::unique_ptr<ApduInterpreterSpi> createApduInterpreter() = 0;
};

} /* namespace spi */
} /* namespace internal */
} /* namespace storagecard */
} /* namespace plugin */
} /* namespace core */
} /* namespace keyple */
