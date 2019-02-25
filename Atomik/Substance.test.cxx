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

// Catch includes
#include <catch2/catch.hpp>

// Atomik includes
#include <Atomik/ChemicalFormula.hpp>
#include <Atomik/Elements.hpp>
#include <Atomik/Extract.hpp>
#include <Atomik/Substance.hpp>
using namespace Atomik;

TEST_CASE("Testing Substance class", "[Substance]")
{
    Substance substance;

    // Test Substance::Substance(formula) constructor
    substance = Substance("H2O");
    REQUIRE(substance.formula() == "H2O");
    REQUIRE(substance.name() == "H2O");
    REQUIRE(substance.type() == "");
    REQUIRE(substance.tags().empty());
    REQUIRE(substance.molarMass() == Approx(0.01801528));
    REQUIRE(substance.charge() == 0);
    REQUIRE(substance.symbols().size() == 2);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("H") == 2);
    REQUIRE(substance.coefficient("O") == 1);

    // Test Substance::Substance(attributes) constructor
    substance = Substance({"Na+", "Na+(aq)", "aqueous", {"cation", "charged"}});
    REQUIRE(substance.formula() == "Na+");
    REQUIRE(substance.name() == "Na+(aq)");
    REQUIRE(substance.type() == "aqueous");
    REQUIRE(substance.tags().size() == 2);
    REQUIRE(substance.tags().count("cation"));
    REQUIRE(substance.tags().count("charged"));
    REQUIRE(substance.molarMass() == Approx(0.022989769));
    REQUIRE(substance.charge() == 1);
    REQUIRE(substance.symbols().size() == 2);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("Na") == 1);
    REQUIRE(substance.coefficient("Z") == 1);

    // Test Substance::Substance(attributes) constructor
    substance = Substance({"Cl-", "Cl-(aq)", "aqueous", {"anion", "charged"}});
    REQUIRE(substance.formula() == "Cl-");
    REQUIRE(substance.name() == "Cl-(aq)");
    REQUIRE(substance.type() == "aqueous");
    REQUIRE(substance.tags().size() == 2);
    REQUIRE(substance.tags().count("anion"));
    REQUIRE(substance.tags().count("charged"));
    REQUIRE(substance.molarMass() == Approx(0.035453));
    REQUIRE(substance.charge() == -1);
    REQUIRE(substance.symbols().size() == 2);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("Cl") == 1);
    REQUIRE(substance.coefficient("Z") == -1);

    // Test Substance::Substance(attributes) constructor
    substance = Substance({"CO3--", "CO3--(aq)", "aqueous", {"anion", "charged"}});
    REQUIRE(substance.formula() == "CO3-2");
    REQUIRE(substance.name() == "CO3--(aq)");
    REQUIRE(substance.type() == "aqueous");
    REQUIRE(substance.tags().size() == 2);
    REQUIRE(substance.tags().count("anion"));
    REQUIRE(substance.tags().count("charged"));
    REQUIRE(substance.molarMass() == Approx(0.0600092));
    REQUIRE(substance.charge() == -2);
    REQUIRE(substance.symbols().size() == 3);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("C") == 1);
    REQUIRE(substance.coefficient("O") == 3);
    REQUIRE(substance.coefficient("Z") == -2);

    // Test Substance::withFormula method with Substance::Substance(formula) constructor
    substance = Substance("CaCO3").withFormula("Ca(CO3)");
    REQUIRE(substance.formula() == "Ca(CO3)");
    REQUIRE(substance.name() == "CaCO3");
    REQUIRE(substance.type() == "");
    REQUIRE(substance.tags().empty());
    REQUIRE(substance.molarMass() == Approx(0.1000869));
    REQUIRE(substance.charge() == 0);
    REQUIRE(substance.symbols().size() == 3);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("C") == 1);
    REQUIRE(substance.coefficient("Ca") == 1);
    REQUIRE(substance.coefficient("O") == 3);

    // Test Substance::withName method with Substance::Substance(formula) constructor
    substance = Substance("H+").withName("H+(aq)");
    REQUIRE(substance.formula() == "H+");
    REQUIRE(substance.name() == "H+(aq)");
    REQUIRE(substance.type() == "");
    REQUIRE(substance.tags().empty());
    REQUIRE(substance.molarMass() == Approx(0.00100794));
    REQUIRE(substance.charge() == 1);
    REQUIRE(substance.symbols().size() == 2);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("H") == 1);
    REQUIRE(substance.coefficient("Z") == 1);

    // Test Substance::withType method with Substance::Substance(formula) constructor
    substance = Substance("HCO3-").withType("aqueous");
    REQUIRE(substance.formula() == "HCO3-");
    REQUIRE(substance.name() == "HCO3-");
    REQUIRE(substance.type() == "aqueous");
    REQUIRE(substance.tags().empty());
    REQUIRE(substance.molarMass() == Approx(0.0610168));
    REQUIRE(substance.charge() == -1);
    REQUIRE(substance.symbols().size() == 4);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("C") == 1);
    REQUIRE(substance.coefficient("H") == 1);
    REQUIRE(substance.coefficient("O") == 3);
    REQUIRE(substance.coefficient("Z") == -1);

    // Test Substance::withTags method with Substance::Substance(formula) constructor
    substance = Substance("Fe+++").withTags({"cation", "charged", "iron"});
    REQUIRE(substance.formula() == "Fe+3");
    REQUIRE(substance.name() == "Fe+++");
    REQUIRE(substance.type() == "");
    REQUIRE(substance.tags().size() == 3);
    REQUIRE(substance.tags().count("cation"));
    REQUIRE(substance.tags().count("charged"));
    REQUIRE(substance.tags().count("iron"));
    REQUIRE(substance.molarMass() == Approx(0.055847));
    REQUIRE(substance.charge() == 3);
    REQUIRE(substance.symbols().size() == 2);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("Fe") == 1);
    REQUIRE(substance.coefficient("Z") == 3);

    Elements elements = Elements::PeriodicTable();
    elements.append( Element({"Aa"}) );
    elements.append( Element({"Bb"}) );

    substance = Substance("AaBb2+", elements);
    REQUIRE(substance.formula() == "AaBb2+");
    REQUIRE(substance.name() == "AaBb2+");
    REQUIRE(substance.type() == "");
    REQUIRE(substance.tags().empty());
    REQUIRE(substance.molarMass() == Approx(0.0));
    REQUIRE(substance.charge() == 1);
    REQUIRE(substance.symbols().size() == 3);
    REQUIRE(substance.symbols() == Extract::symbols(substance.elements()));
    REQUIRE(substance.coefficient("Aa") == 1);
    REQUIRE(substance.coefficient("Bb") == 2);
    REQUIRE(substance.coefficient("Z") == 1);
}
