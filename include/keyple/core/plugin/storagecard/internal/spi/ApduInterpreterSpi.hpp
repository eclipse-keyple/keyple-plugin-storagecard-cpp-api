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

#include <cstdint>
#include <memory>
#include <vector>

#include "keyple/core/plugin/storagecard/internal/CommandProcessorApi.hpp"

namespace keyple {
namespace core {
namespace plugin {
namespace storagecard {
namespace internal {
namespace spi {

using keyple::core::plugin::storagecard::internal::CommandProcessorApi;

/**
 * Interface defining an APDU interpreter for processing commands sent to
 * storage cards.
 *
 * <p>Its implementation is provided by ApduInterpreterFactorySpi.
 *
 * <p>Upon calling processApdu, implementations determine how to invoke the
 * appropriate methods of CommandProcessorApi based on the APDU class byte
 * (CLA) and instruction (INS).
 *
 * <h3>APDU Processing Strategy</h3>
 *
 * <p>The interpreter follows a two-pathway processing model:
 *
 * <ul>
 *   <li><strong>Standard ISO 7816-4 APDUs</strong> (CLA != 0xFF): Directly
 *       transmitted via CommandProcessorApi::transmitIsoApdu(const
 *       std::vector<uint8_t>&) without interpretation.
 *   <li><strong>Storage Card APDUs</strong> (CLA = 0xFF): Interpreted and
 *       translated into CommandProcessorApi method calls based on the
 *       instruction byte:
 *       <ul>
 *         <li>INS 0xCA &rarr; CommandProcessorApi::getUID() - Get card UID
 *         <li>INS 0xB0 &rarr; CommandProcessorApi::readBlock(int, int) -
 *             Read binary data
 *         <li>INS 0xD6 &rarr; CommandProcessorApi::writeBlock(int, const
 *             std::vector<uint8_t>&) - Write binary data
 *         <li>INS 0x82 &rarr; CommandProcessorApi::loadKey(KeyStorageType,
 *             int, const std::vector<uint8_t>&) - Load authentication key
 *         <li>INS 0x86 &rarr; CommandProcessorApi::generalAuthenticate(int,
 *             int, int) - Authenticate with key
 *       </ul>
 * </ul>
 *
 * <h3>Error Handling Strategy</h3>
 *
 * <p>This interface follows a <strong>trust-based validation</strong>
 * approach:
 *
 * <ul>
 *   <li><strong>Validation</strong> is performed upstream by the card
 *       extension that generates the APDUs. Since this extension is part
 *       of the same ecosystem, its output is trusted.
 *   <li><strong>CommandProcessorApi</strong> does not perform parameter
 *       validation and trusts the incoming data to be correct.
 *   <li><strong>Exceptions propagate</strong> to the caller unless they
 *       represent normal protocol conditions (e.g., authentication
 *       failure, unsupported instruction).
 *   <li><strong>Status words</strong> are returned only for
 *       protocol-level conditions, not validation errors.
 * </ul>
 *
 * <h3>Status Words Usage</h3>
 *
 * <p>Implementations return ISO 7816-4 / PC/SC compliant status words for
 * the following conditions:
 *
 * <table border="1">
 *   <caption>Status Words returned by implementations</caption>
 *   <tr><th>Status Word</th><th>Code</th><th>Usage</th></tr>
 *   <tr><td>Success</td><td>0x9000</td><td>Successful execution</td></tr>
 *   <tr><td>Security status not satisfied</td><td>0x6982</td><td>
 *   Authentication failed (PC/SC compliant)</td></tr>
 *   <tr><td>INS not supported</td><td>0x6D00</td><td>Unknown instruction
 *   code</td></tr>
 * </table>
 *
 * <h3>Exception Propagation</h3>
 *
 * <p>The following error conditions may result in exceptions:
 *
 * <ul>
 *   <li><strong>Hardware/communication errors</strong> (card not
 *       responding, transmission failure) - thrown by CommandProcessorApi
 *   <li><strong>Protocol-level errors</strong> that cannot be represented
 *       by status words - may be thrown by implementations
 * </ul>
 *
 * <p><strong>Note:</strong> Parameter validation (P1/P2 values, data
 * lengths, key numbers, etc.) is the responsibility of the card extension
 * generating the APDUs, not this interface or its implementations.
 *
 * <h3>PC/SC Compliance</h3>
 *
 * <p>Storage card commands (CLA=0xFF) follow the PC/SC v2.01.09
 * specification:
 *
 * <ul>
 *   <li>LOAD KEY: FF 82 [P1] [P2] 06 [6-byte key]
 *   <li>GENERAL AUTHENTICATE: FF 86 00 00 05
 *       [version][addr-MSB][addr-LSB][key-type][key-num]
 *   <li>GET DATA (UID): FF CA 00 00 [Le]
 *   <li>READ BINARY: FF B0 [P1] [P2] [Le]
 *   <li>UPDATE BINARY: FF D6 [P1] [P2] [Lc] [data]
 * </ul>
 *
 * @see CommandProcessorApi
 * @see ApduInterpreterFactorySpi
 * @since 1.0.0
 */
class ApduInterpreterSpi {
public:
    /**
     * Virtual destructor.
     */
    virtual ~ApduInterpreterSpi() = default;

    /**
     * Sets the command processor responsible for handling APDU execution.
     *
     * @param commandProcessor The CommandProcessorApi instance used for
     * APDU communication.
     * @since 1.0.0
     */
    virtual void setCommandProcessor(
        const std::shared_ptr<CommandProcessorApi>& commandProcessor)
        = 0;

    /**
     * Processes an APDU command by invoking the corresponding methods of
     * CommandProcessorApi based on the card type.
     *
     * <p>If the card supports standard ISO 7816-4 APDUs, this method calls
     * CommandProcessorApi::transmitIsoApdu(const std::vector<uint8_t>&).
     * Otherwise, it interprets the APDU and executes the required read or
     * write operations through CommandProcessorApi::readBlock(int, int) or
     * CommandProcessorApi::writeBlock(int, const std::vector<std::uint8_t>&).
     *
     * @param apdu The APDU command as a byte array.
     * @return The response as a byte array.
     * @throw std::invalid_argument if the APDU is empty or invalid.
     * @throw std::exception if the transmission fails or a communication
     * error occurs.
     * @since 1.0.0
     */
    virtual std::vector<uint8_t> processApdu(
        const std::vector<std::uint8_t>& apdu) = 0;
};

} /* namespace spi */
} /* namespace internal */
} /* namespace storagecard */
} /* namespace plugin */
} /* namespace core */
} /* namespace keyple */
