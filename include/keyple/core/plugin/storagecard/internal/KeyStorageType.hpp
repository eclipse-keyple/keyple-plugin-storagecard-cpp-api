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
namespace internal {

/**
 * Enumeration defining the memory types available for key storage in the
 * reader.
 *
 * @since 1.1.0
 */
enum class KeyStorageType {
    /**
     * Volatile memory (RAM).
     *
     * <p>Keys stored here are lost when the reader is powered off or reset.
     * This is generally faster and supports unlimited write cycles.
     *
     * @since 1.1.0
     */
    VOLATILE,

    /**
     * Non-volatile memory (EEPROM/Flash).
     *
     * <p>Keys stored here persist across power cycles. Note that
     * non-volatile memory typically has a limited number of write cycles.
     *
     * @since 1.1.0
     */
    NON_VOLATILE
};

} /* namespace internal */
} /* namespace storagecard */
} /* namespace plugin */
} /* namespace core */
} /* namespace keyple */
