/* -*- c++ -*- */
/* 
 * Copyright 2024 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */


#pragma once

#include <uhd/config.hpp>
#include <uhd/rfnoc/noc_block_base.hpp>

namespace uhd {
    namespace rfnoc {

/*! \brief Block controller for the standard copy RFNoC block.
 *
 */
class UHD_API gain_block_ctrl : public noc_block_base
{
public:
    RFNOC_DECLARE_BLOCK(gain_block_ctrl)

    static const uint32_t REG_MUL_ADDR;
    static const uint32_t REG_MUL_DEFAULT;

    static const uint32_t REG_DIV_ADDR;
    static const uint32_t REG_DIV_DEFAULT;

    static const uint32_t REG_EN_ADDR;
    static const uint32_t REG_EN_DEFAULT;

}; /* class gain_block_ctrl*/

}} /* namespace uhd::rfnoc */

