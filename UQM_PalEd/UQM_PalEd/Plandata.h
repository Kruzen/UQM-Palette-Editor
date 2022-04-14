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

const TopoFrame xlat_tables[NUMBERS_OF_XLTS] =
{
	{ /* 0 BANDED */
		TOPO_ALGO,
		500, 1, 0, 160,
	},
	{ /* 1 CHONDRITE */
		CRATERED_ALGO,
		500, 1, 100, 190,
	},
	{ /* 2 CONTINENTS */
		CRATERED_ALGO,
		500, 1, 0, 190,
	},
	{ /* 3 CRYSTAL */
		TOPO_ALGO,
		80, 1, 0, 128,
	},
	{ /* 4 DENTED */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* 5 GAS_GIANT */
		GAS_GIANT_ALGO,
		10, 2, 8, 29,
	},
	{ /* 6 ICE */
		CRATERED_ALGO,
		400, 1, 100, 190,
	},
	{ /* 7 METAL */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* 8 OOLITE */
		CRATERED_ALGO,
		230, 2, 200, 150,
	},
	{ /* 9 RAINBOW */
		TOPO_ALGO,
		500, 1, 20, 100,
	},
	{ /* 10 REDUX */
		CRATERED_ALGO,
		500, 1, 0, 190,
	},
	{ /* 11 RUSTED */
		CRATERED_ALGO,
		250, 2, 80, 200,
	},
	{ /* 12 RUSTED_PRIMORDIAL */
		CRATERED_ALGO,
		250, 2, 10, 200,
	},
	{ /* 13 SHATTERED */
		CRATERED_ALGO,
		500, 1, 0, 185,
	},
	{ /* 14 DENTED_ULTRAMARINE */
		CRATERED_ALGO,
		200, 2, 100, 100,
	},
};

const std::string xlts_name_array[NUMBERS_OF_XLTS + 1] =
{
	"-",
	"Banded",
	"Chondrite",
	"Continents",
	"Crystal",
	"Dented",
	"Gas Giant",
	"Ice",
	"Metal",
	"Oolite",
	"Rainbow",
	"Redux",
	"Rusted",
	"Rusted (Primordial)",
	"Shattered",
	"Dented (Ultramarine)",
};

const int planet_array[NUMBER_OF_PLANET_TYPES] =
{
	8,	/* OOLITE_WORLD */
	11,	/* YTTRIC_WORLD */
	0,	/* QUASI_DEGENERATE_WORLD */
	11,	/* LANTHANIDE_WORLD */
	0,	/* TREASURE_WORLD */
	4,	/* UREA_WORLD */
	7,	/* METAL_WORLD */
	11, /* RADIOACTIVE_WORLD */
	6,	/* OPALESCENT_WORLD */
	0,	/* CYANIC_WORLD */
	11,	/* ACID_WORLD */
	11,	/* ALKALI_WORLD */
	11,	/* HALIDE_WORLD */
	4,	/* GREEN_WORLD */
	0,	/* COPPER_WORLD */
	6,	/* CARBIDE_WORLD */
	14,	/* ULTRAMARINE_WORLD */
	11,	/* NOBLE_WORLD */
	4,	/* AZURE_WORLD */
	1,	/* CHONDRITE_WORLD */
	4,	/* PURPLE_WORLD */
	0,	/* SUPER_DENSE_WORLD */
	6,	/* PELLUCID_WORLD */
	11,	/* DUST_WORLD */
	4,	/* CRIMSON_WORLD */
	0,	/* CIMMERIAN_WORLD */
	6,	/* INFRARED_WORLD */
	4,	/* SELENIC_WORLD */
	0,	/* AURIC_WORLD */
	6,	/* FLUORESCENT_WORLD */
	11,	/* ULTRAVIOLET_WORLD */
	11,	/* PLUTONIC_WORLD */
	9,	/* RAINBOW_WORLD */
	13,	/* SHATTERED_WORLD */
	3,	/* SAPPHIRE_WORLD */
	0,	/* ORGANIC_WORLD */
	6,	/* XENOLITHIC_WORLD */
	10,	/* REDUX_WORLD */
	12,	/* PRIMORDIAL_WORLD */
	3,	/* EMERALD_WORLD */
	2,	/* CHLORINE_WORLD */
	6,	/* MAGNETIC_WORLD */
	2,	/* WATER_WORLD */
	11,	/* TELLURIC_WORLD */
	0,	/* HYDROCARBON_WORLD */
	4,	/* IODINE_WORLD */
	6,	/* VINYLOGOUS_WORLD */
	3,	/* RUBY_WORLD */
	0,	/* MAGMA_WORLD */
	4,	/* MAROON_WORLD */
	5,	/* BLUE_GAS_GIANT */
	5,	/* CYAN_GAS_GIANT */
	5,	/* GRAY_GAS_GIANT */
	5,	/* GREEN_GAS_GIANT */
	5,	/* RED_GAS_GIANT */
	5,	/* PURPLE_GAS_GIANT */
	5,	/* ORANGE_GAS_GIANT */
	5,	/* VIOLET_GAS_GIANT */
	5,	/* YELLOW_GAS_GIANT */
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
	"Blue Gas Giant",
	"Cyan Gas Giant",
	"Gray Gas Giant",
	"Green Gas Giant",
	"Red Gas Giant",
	"Purple Gas Giant",
	"Orange Gas Giant",
	"Violet Gas Giant",
	"Yellow Gas Giant",
};
