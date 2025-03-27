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


#include <tutorial/gain_block_ctrl.hpp>
#include <uhd/rfnoc/registry.hpp>

using namespace uhd::rfnoc;

// Note: Register addresses should increment by 4
const uint32_t gain_block_ctrl::REG_MUL_ADDR    = 0;
const uint32_t gain_block_ctrl::REG_MUL_DEFAULT = 2;

const uint32_t gain_block_ctrl::REG_DIV_ADDR    = 4;
const uint32_t gain_block_ctrl::REG_DIV_DEFAULT = 1;

const uint32_t gain_block_ctrl::REG_EN_ADDR    = 8;
const uint32_t gain_block_ctrl::REG_EN_DEFAULT = 1;

class gain_block_ctrl_impl : public gain_block_ctrl
{
public:
    RFNOC_BLOCK_CONSTRUCTOR(gain_block_ctrl)
    {
        _register_props();
    }
private:
    void _register_props()
    {
        register_property(&_reg_mul, [this]() {
            int reg_mul = this->_reg_mul.get();
            this->regs().poke32(REG_MUL_ADDR, reg_mul);
        });

        register_property(&_reg_div, [this]() {
            int reg_div = this->_reg_div.get();
            this->regs().poke32(REG_DIV_ADDR, reg_div);
        });

        register_property(&_reg_en, [this]() {
            int reg_en = this->_reg_en.get();
            this->regs().poke32(REG_EN_ADDR, reg_en);
        });

        // register edge properties
        register_property(&_type_in);
        register_property(&_type_out);

        // add resolvers for type (keeps it constant)
        add_property_resolver({&_type_in}, {&_type_in}, [& type_in = _type_in]() {
            type_in.set(IO_TYPE_SC16);
        });
        add_property_resolver({&_type_out}, {&_type_out}, [& type_out = _type_out]() {
            type_out.set(IO_TYPE_SC16);
        });
    }

    property_t<int> _reg_mul{"reg_mul", REG_MUL_DEFAULT, {res_source_info::USER}};
    property_t<int> _reg_div{"reg_div", REG_DIV_DEFAULT, {res_source_info::USER}};
    property_t<int> _reg_en {"reg_en",  REG_EN_DEFAULT,  {res_source_info::USER}};

    property_t<std::string> _type_in = property_t<std::string>{
        PROP_KEY_TYPE, IO_TYPE_SC16, {res_source_info::INPUT_EDGE}};
    property_t<std::string> _type_out = property_t<std::string>{
        PROP_KEY_TYPE, IO_TYPE_SC16, {res_source_info::OUTPUT_EDGE}};

};

UHD_RFNOC_BLOCK_REGISTER_DIRECT(gain_block_ctrl, 0x00001234, "gain", CLOCK_KEY_GRAPH, "bus_clk");
