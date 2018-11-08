// Atomik is a library for parsing chemical formulas.
//
// Copyright (C) 2018 Allan Leal
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#include "Substance.hpp"

namespace Atomik {
namespace internal {

/// The default database of elements
const Elements default_elementdb;

// Throw a runtime error if the substance name has spaces.
auto checkSubstanceIdentifierHasNoSpaces(std::string name, std::string nametype) -> void
{
    // Check the name provided has no spaces
    if(name.find(' ') != std::string::npos)
        throw std::runtime_error("***ERROR***: The given substance " + nametype + " `" + name + "` "
            "violates the naming rule for substance names and uid, which must have no spaces.");
}

} // namespace internal

Substance::Substance()
{}

Substance::Substance(std::string formula)
: Substance(formula, internal::default_elementdb)
{}

Substance::Substance(std::string formula, const Elements& elementdb)
: m_uid(formula), m_name(formula), m_formula(formula)
{
    // Initialize the chemical elements of the chemical substance
    m_elements.clear();
    for(const auto& pair : m_formula.elements())
        m_elements.emplace_back(elementdb(pair.first), pair.second);

    // Initialize the molar mass of the chemical substance
    m_molarmass = 0.0;
    for(const auto& pair : m_elements)
        m_molarmass += std::get<1>(pair) * std::get<0>(pair).atomicWeight();
}

auto Substance::uid(std::string uid) -> Substance&
{
    // Check if provided uid has space and throws a runtime error if true
    internal::checkSubstanceIdentifierHasNoSpaces(uid, "uid");
    m_uid = uid;
    return *this;
}

auto Substance::uid() const -> std::string
{
    return m_uid;
}

auto Substance::name(std::string name) -> Substance&
{
    // Check if provided name has space and throws a runtime error if true
    internal::checkSubstanceIdentifierHasNoSpaces(name, "name");
    m_name = name;
    return *this;
}

auto Substance::name() const -> std::string
{
    return m_name;
}

auto Substance::formula() const -> const ChemicalFormula&
{
    return m_formula;
}

auto Substance::elements() const -> const std::vector<std::pair<Element, double>>&
{
    return m_elements;
}

auto Substance::charge() const -> double
{
    return m_formula.charge();
}

auto Substance::molarMass() const -> double
{
    return m_molarmass;
}

auto Substance::coefficient(std::string symbol) const -> double
{
    return m_formula.coefficient(symbol);
}

auto operator<(const Substance& lhs, const Substance& rhs) -> bool
{
    return lhs.uid() < rhs.uid();
}

auto operator==(const Substance& lhs, const Substance& rhs) -> bool
{
    return lhs.uid() == rhs.uid() &&
           lhs.name() == rhs.name() &&
           lhs.formula() == rhs.formula() &&
           lhs.elements() == rhs.elements() &&
           lhs.charge() == rhs.charge();
}

} // namespace Atomik
