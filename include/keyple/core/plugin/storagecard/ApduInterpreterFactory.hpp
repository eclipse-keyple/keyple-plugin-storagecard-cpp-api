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

namespace keyple {
namespace core {
namespace plugin {
namespace storagecard {

/**
 * Factory interface for creating instances of APDU interpreters.
 *
 * <p>The purpose of this interface is to provide an APDU interpreter factory
 * designed to be supplied to plugins capable of handling storage-type smart
 * card processing functionalities.
 *
 * <p>This interface is designed to be implemented by card APDU interpreter
 * libraries, enabling the creation of specific APDU interpreter instances
 * tailored to handle APDU commands and their processing requirements.
 *
 * <p>Implementations must be instances of
 * keyple::core::plugin::storagecard::internal::spi::ApduInterpreterFactorySpi
 * providing the logic for a concrete APDU interpreter.
 *
 * @since 1.0.0
 */
class ApduInterpreterFactory {
public:
    /**
     * Virtual destructor.
     */
    virtual ~ApduInterpreterFactory() = default;
};

} /* namespace storagecard */
} /* namespace plugin */
} /* namespace core */
} /* namespace keyple */
