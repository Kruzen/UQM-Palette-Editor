// Ur-Quan Masters Palette Editor

/*
 *	This program is created as a tool to view/modify/create
 *	Ur-Quan Masters .ct (color table) files. No source code from
 *	the original game was used. Program algorithms are based on dev doc
 *	file (see ..\doc\devel\strtab file in Ur-Quan Masters repository).
 *
 *	"Ur-Quan Masters" was originally created by Fred Ford and Paul Reiche III.
 *	Copyright Paul Reiche, Fred Ford. 1992-2002
 *	All trademarks belong to their respective owners.
 *
 *	This is a FREE software. DO NOT use it for financial profit.
 *	Created by Kruzen. 2022
 */

// Info from UQM source code
#pragma once
#include <string>
#include "constdef.h"


typedef struct
{
	int algo;
	int num_faults;
	int fault_depth;
	int num_blemishes;
	int base_elevation;
}TopoFrame;

typedef struct
{
	int x_top, x_bot;
	short x_incr, delta_x, error_term;
}Line_UQM;

const TopoFrame planet_array[NUMBER_OF_PLANET_TYPES] =
{
	{ /* OOLITE_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* YTTRIC_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* QUASI_DEGENERATE_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* LANTHANIDE_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* TREASURE_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* UREA_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* METAL_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* RADIOACTIVE_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* OPALESCENT_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* CYANIC_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* ACID_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* ALKALI_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* HALIDE_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* GREEN_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* COPPER_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* CARBIDE_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* ULTRAMARINE_WORLD */
		CRATERED_ALGO,
		200, 2, 100, 100,
	},
	{ /* NOBLE_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* AZURE_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* CHONDRITE_WORLD */
		CRATERED_ALGO,
		500, 1, 100, 190,
	},
	{ /* PURPLE_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* SUPER_DENSE_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* PELLUCID_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* DUST_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* CRIMSON_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* CIMMERIAN_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* INFRARED_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* SELENIC_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* AURIC_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* FLUORESCENT_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* ULTRAVIOLET_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* PLUTONIC_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* RAINBOW_WORLD */
		TOPO_ALGO,
		500, 1, 20, 100,
	},
	{ /* SHATTERED_WORLD */
		CRATERED_ALGO,
		500, 1, 0, 185,
	},
	{ /* SAPPHIRE_WORLD */
		TOPO_ALGO,
		80, 1, 0, 128,
	},
	{ /* ORGANIC_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* XENOLITHIC_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* REDUX_WORLD */
		CRATERED_ALGO,
		500, 1, 0, 190,
	},
	{ /* PRIMORDIAL_WORLD */
		CRATERED_ALGO,
		250, 2, 10, 200,
	},
	{ /* EMERALD_WORLD */
		TOPO_ALGO,
		80, 1, 0, 128,
	},
	{ /* CHLORINE_WORLD */
		CRATERED_ALGO,
		500, 1, 0, 190,
	},
	{ /* MAGNETIC_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* WATER_WORLD */
		CRATERED_ALGO,
		500, 1, 0, 190,
	},
	{ /* TELLURIC_WORLD */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* HYDROCARBON_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* IODINE_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* VINYLOGOUS_WORLD */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* RUBY_WORLD */
		TOPO_ALGO,
		80, 1, 0, 128,
	},
	{ /* MAGMA_WORLD */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* MAROON_WORLD */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* ANY_GAS_GIANT */
		GAS_GIANT_ALGO,
		10, 2, 8, 29,
	},
};

const std::string planet_name_array[NUMBER_OF_PLANET_TYPES + 1] =
{
	"-",
	"Oolite",
	"Yttric",
	"Quasi-Degenerate",
	"Lanthanide",
	"Treasure",
	"Urea",
	"Metal",
	"Radioactive",
	"Opalescent",
	"Cyanic",
	"Acid",
	"Alkali",
	"Halide",
	"Green",
	"Copper",
	"Carbide",
	"Ultramarine",
	"Noble",
	"Azure",
	"Chondrite",
	"Purple",
	"Super-Dense",
	"Pellucid",
	"Dust",
	"Crimson",
	"Cimmerian",
	"Infrared",
	"Selenic",
	"Auric",
	"Fluorescent",
	"Ultraviolet",
	"Plutonic",
	"Rainbow",
	"Shattered",
	"Sapphire",
	"Organic",
	"Xenolithic",
	"Redux",
	"Primordial",
	"Emerald",
	"Chlorine",
	"Magnetic",
	"Water",
	"Telluric",
	"Hydrocarbon",
	"Iodine",
	"Vinylogous",
	"Ruby",
	"Magma",
	"Maroon",
	"Gas Giant",
};
