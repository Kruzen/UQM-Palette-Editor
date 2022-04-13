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
#include "GenPlanet.h"
#include "constdef.h"
#include <cstring>


void GenPlanet::deltaTopography(int num_iterations, char* depthArray, RECT_UQM* pRect, int depth_delta)
{// based of UQM source code
	short width, height, delta_y;
	struct
	{
		short x_top, x_bot;
		short x_incr, delta_x, error_term;
	} LineDDA0, LineDDA1;

	width = pRect->width;
	height = pRect->height;
	delta_y = (height - 1) << 1;
	do
	{
		short d;
		unsigned short h, w1, w2;
		int rand_val;
		char* lpDst;

		if ((r->getUQMRandomValue() & 1) == 0)
			depth_delta = -depth_delta;

		rand_val = r->getUQMRandomValue();
		w1 = LOWORD(rand_val);
		w2 = HIWORD(rand_val);

		LineDDA0.x_top = (LOBYTE(w1) % MAP_WIDTH)
			* width / MAP_WIDTH;
		LineDDA0.x_bot = (HIBYTE(w1) % MAP_WIDTH)
			* width / MAP_WIDTH;

		LineDDA0.delta_x = (LineDDA0.x_bot - LineDDA0.x_top) << 1;
		if (LineDDA0.delta_x >= 0)
			LineDDA0.x_incr = 1;
		else
		{
			LineDDA0.x_incr = -1;
			LineDDA0.delta_x = -LineDDA0.delta_x;
		}
		if (LineDDA0.delta_x > delta_y)
			LineDDA0.error_term = -(LineDDA0.delta_x >> 1);
		else
			LineDDA0.error_term = -(delta_y >> 1);

		LineDDA1.x_top = (LOBYTE(w2) % (MAP_WIDTH - 1))
			* width / MAP_WIDTH + LineDDA0.x_top + 1;
		LineDDA1.x_bot = (HIBYTE(w2) % (MAP_WIDTH - 1))
			* width / MAP_WIDTH + LineDDA0.x_bot + 1;
		LineDDA1.delta_x = (LineDDA1.x_bot - LineDDA1.x_top) << 1;
		if (LineDDA1.delta_x >= 0)
			LineDDA1.x_incr = 1;
		else
		{
			LineDDA1.x_incr = -1;
			LineDDA1.delta_x = -LineDDA1.delta_x;
		}
		if (LineDDA1.delta_x > delta_y)
			LineDDA1.error_term = -(LineDDA1.delta_x >> 1);
		else
			LineDDA1.error_term = -(delta_y >> 1);

		lpDst = &depthArray[LineDDA0.x_top];
		h = height;
		do
		{
			short w;

			w1 = LineDDA1.x_top - LineDDA0.x_top;
			w2 = width - w1;

			if ((int)(LineDDA0.x_top + w1) > (int)width)
				w = width - LineDDA0.x_top;
			else
			{
				w = w1;
				LineDDA0.x_top += w1;
			}
			w1 -= w;
			while (w--)
			{
				d = *lpDst + depth_delta;
				if (d >= -128 && d <= 127)
					*lpDst = (char)d;
				++lpDst;
			}
			if (w1 == 0)
			{
				if (LineDDA0.x_top == width)
				{
					LineDDA0.x_top = 0;
					lpDst -= width;
				}
			}
			else
			{
				LineDDA0.x_top = w1;
				lpDst -= width;
				do
				{
					d = *lpDst + depth_delta;
					if (d >= -128 && d <= 127)
						*lpDst = (char)d;
					++lpDst;
				} while (--w1);
			}

			if ((int)(LineDDA0.x_top + w2) > (int)width)
				w = width - LineDDA0.x_top;
			else
			{
				w = w2;
				LineDDA0.x_top += w2;
			}
			w2 -= w;
			while (w--)
			{
				d = *lpDst - depth_delta;
				if (d >= -128 && d <= 127)
					*lpDst = (char)d;
				++lpDst;
			}
			if (w2 == 0)
			{
				if (LineDDA0.x_top == width)
				{
					LineDDA0.x_top = 0;
					lpDst -= width;
				}
			}
			else
			{
				LineDDA0.x_top = w2;
				lpDst -= width;
				do
				{
					d = *lpDst - depth_delta;
					if (d >= -128 && d <= 127)
						*lpDst = (char)d;
					++lpDst;
				} while (--w2);
			}

			lpDst += pRect->width;

			if (delta_y >= LineDDA0.delta_x)
			{
				if ((LineDDA0.error_term += LineDDA0.delta_x) >= 0)
				{
					lpDst += LineDDA0.x_incr;
					LineDDA0.x_top += LineDDA0.x_incr;
					LineDDA0.error_term -= delta_y;
				}
			}
			else
			{
				do
				{
					lpDst += LineDDA0.x_incr;
					LineDDA0.x_top += LineDDA0.x_incr;
				} while ((LineDDA0.error_term += delta_y) < 0);
				LineDDA0.error_term -= LineDDA0.delta_x;
			}

			if (delta_y >= LineDDA1.delta_x)
			{
				if ((LineDDA1.error_term += LineDDA1.delta_x) >= 0)
				{
					LineDDA1.x_top += LineDDA1.x_incr;
					LineDDA1.error_term -= delta_y;
				}
			}
			else
			{
				do
				{
					LineDDA1.x_top += LineDDA1.x_incr;
				} while ((LineDDA1.error_term += delta_y) < 0);
				LineDDA1.error_term -= LineDDA1.delta_x;
			}
		} while (--h);
	} while (--num_iterations);
}

void GenPlanet::ditherMap(char* depthArray, short width, short height)
{// based of UQM source code
	int i;
	int rand_val = 0;
	char* elev;

	for (i = 0, elev = depthArray; i < (int)(width * height); ++i, ++elev)
	{
		// Use up the random value byte by byte
		if ((i & 3) == 0)
			rand_val = r->getUQMRandomValue();
		else
			rand_val >>= 8;

		// Bring the elevation point up or down
		*elev += DITHER_VARIANCE / 2 - (rand_val & (DITHER_VARIANCE - 1));
	}
}

void GenPlanet::validateMap(char* depthArray, short width, short height)
{// based of UQM source code
	char state;
	char pixel_count[2], lb[2];
	char last_byte;
	int i;
	char* lpDst;

	i = width - 1;
	lpDst = depthArray;
	last_byte = *lpDst++;
	state = pixel_count[0] = pixel_count[1] = 0;
	do
	{
		if (pixel_count[state]++ == 0)
			lb[state] = last_byte;

		if (last_byte > *lpDst)
		{
			if (last_byte - *lpDst > 128)
				state ^= 1;
		}
		else
		{
			if (*lpDst - last_byte > 128)
				state ^= 1;
		}
		last_byte = *lpDst++;
	} while (--i);

	i = width * height;
	lpDst = depthArray;
	if (pixel_count[0] > pixel_count[1])
		last_byte = lb[0];
	else
		last_byte = lb[1];
	do
	{
		if (last_byte > *lpDst)
		{
			if (last_byte - *lpDst > 128)
				*lpDst = last_byte;
		}
		else
		{
			if (*lpDst - last_byte > 128)
				*lpDst = last_byte;
		}
		last_byte = *lpDst++;
	} while (--i);
}

void GenPlanet::makeCrater(RECT_UQM* pRect, char* depthArray, short rim_delta, short crater_delta, bool SetDepth, unsigned short width)
{// based of UQM source code
	short x, y, lf_x, rt_x;
	short a, b;
	long Asquared, TwoAsquared, Bsquared, TwoBsquared;
	long d, dx, dy;
	int TopIndex, BotIndex, rim_pixels;


	a = pRect->width >> 1;
	b = pRect->height >> 1;

	x = 0;
	y = b;

	Asquared = (int)a * a;
	TwoAsquared = Asquared << 1;
	Bsquared = (int)b * b;
	TwoBsquared = Bsquared << 1;

	dx = 0;
	dy = TwoAsquared * b;
	d = Bsquared - (dy >> 1) + (Asquared >> 2);

	a += pRect->x;
	b += pRect->y;
	TopIndex = (b - y) * width;
	BotIndex = (b + y) * width;
	rim_pixels = 1;
	while (dx < dy)
	{
		if (d > 0)
		{
			lf_x = a - x;
			rt_x = a + x;
			if (SetDepth)
			{
				std::memset(&depthArray[TopIndex + lf_x], 0, sizeof(char)*(rt_x - lf_x + 1));
				std::memset(&depthArray[BotIndex + lf_x], 0, sizeof(char)*(rt_x - lf_x + 1));
			}
			if (lf_x == rt_x)
			{
				depthArray[TopIndex + lf_x] += rim_delta;
				depthArray[BotIndex + lf_x] += rim_delta;
				rim_pixels = 0;
			}
			else
			{
				do
				{
					depthArray[TopIndex + lf_x] += rim_delta;
					depthArray[BotIndex + lf_x] += rim_delta;
					if (lf_x != rt_x)
					{
						depthArray[TopIndex + rt_x] += rim_delta;
						depthArray[BotIndex + rt_x] += rim_delta;
					}
					++lf_x;
					--rt_x;
				} while (--rim_pixels);

				while (lf_x < rt_x)
				{
					depthArray[TopIndex + lf_x] += crater_delta;
					depthArray[BotIndex + lf_x] += crater_delta;
					depthArray[TopIndex + rt_x] += crater_delta;
					depthArray[BotIndex + rt_x] += crater_delta;
					++lf_x;
					--rt_x;
				}

				if (lf_x == rt_x)
				{
					depthArray[TopIndex + lf_x] += crater_delta;
					depthArray[BotIndex + lf_x] += crater_delta;
				}
			}

			--y;
			TopIndex += width;
			BotIndex -= width;
			dy -= TwoAsquared;
			d -= dy;
		}

		++rim_pixels;
		++x;
		dx += TwoBsquared;
		d += Bsquared + dx;
	}

	d += ((((Asquared - Bsquared) * 3) >> 1) - (dx + dy)) >> 1;

	while (y > 0)
	{
		lf_x = a - x;
		rt_x = a + x;
		if (SetDepth)
		{
			std::memset(&depthArray[TopIndex + lf_x], 0, sizeof(char)*(rt_x - lf_x + 1));
			std::memset(&depthArray[BotIndex + lf_x], 0, sizeof(char)*(rt_x - lf_x + 1));
		}
		if (lf_x == rt_x)
		{
			depthArray[TopIndex + lf_x] += rim_delta;
			depthArray[BotIndex + lf_x] += rim_delta;
		}
		else
		{
			do
			{
				depthArray[TopIndex + lf_x] += rim_delta;
				depthArray[BotIndex + lf_x] += rim_delta;
				if (lf_x != rt_x)
				{
					depthArray[TopIndex + rt_x] += rim_delta;
					depthArray[BotIndex + rt_x] += rim_delta;
				}
				++lf_x;
				--rt_x;
			} while (--rim_pixels);

			while (lf_x < rt_x)
			{
				depthArray[TopIndex + lf_x] += crater_delta;
				depthArray[BotIndex + lf_x] += crater_delta;
				depthArray[TopIndex + rt_x] += crater_delta;
				depthArray[BotIndex + rt_x] += crater_delta;
				++lf_x;
				--rt_x;
			}

			if (lf_x == rt_x)
			{
				depthArray[TopIndex + lf_x] += crater_delta;
				depthArray[BotIndex + lf_x] += crater_delta;
			}
		}

		if (d < 0)
		{
			++x;
			dx += TwoBsquared;
			d += dx;
		}

		rim_pixels = 1;
		--y;
		TopIndex += width;
		BotIndex -= width;
		dy -= TwoAsquared;
		d += Asquared - dy;
	}

	lf_x = a - x;
	rt_x = a + x;
	if (SetDepth)
		std::memset(&depthArray[TopIndex + lf_x], 0, sizeof(char)*(rt_x - lf_x + 1));
	if (lf_x == rt_x)
	{
		depthArray[TopIndex + lf_x] += rim_delta;
	}
	else
	{
		do
		{
			depthArray[TopIndex + lf_x] += rim_delta;
			if (lf_x != rt_x)
				depthArray[TopIndex + rt_x] += rim_delta;
			++lf_x;
			--rt_x;
		} while (--rim_pixels);

		while (lf_x < rt_x)
		{
			depthArray[TopIndex + lf_x] += crater_delta;
			depthArray[TopIndex + rt_x] += crater_delta;
			++lf_x;
			--rt_x;
		}

		if (lf_x == rt_x)
		{
			depthArray[TopIndex + lf_x] += crater_delta;
		}
	}
}

void GenPlanet::makeStorms(short storm_count, char* depthArray, short width, short height)
{// based of UQM source code 
	short i;
	RECT_UQM storm_r[MAX_STORMS];
	RECT_UQM* pstorm_r;

	pstorm_r = &storm_r[i = storm_count];
	while (i--)
	{
		bool intersect;
		int rand_val;
		unsigned int loword, hiword;
		short band_delta;

		--pstorm_r;
		do
		{
			short j;

			intersect = false;

			rand_val = r->getUQMRandomValue();
			loword = LOWORD(rand_val);
			hiword = HIWORD(rand_val);
			switch (HIBYTE(hiword) & 31)
			{
			case 0:
				pstorm_r->height =
					(LOBYTE(hiword) % (MAP_HEIGHT >> 2))
					+ (MAP_HEIGHT >> 2);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				pstorm_r->height =
					(LOBYTE(hiword) % (MAP_HEIGHT >> 3))
					+ (MAP_HEIGHT >> 3);
				break;
			default:
				pstorm_r->height =
					(LOBYTE(hiword) % (MAP_HEIGHT >> 4))
					+ 4;
				break;
			}

			if (pstorm_r->height <= 4)
				pstorm_r->height += 4;

			rand_val = r->getUQMRandomValue();
			loword = LOWORD(rand_val);
			hiword = HIWORD(rand_val);

			pstorm_r->width = pstorm_r->height
				+ (LOBYTE(loword) % pstorm_r->height);

			pstorm_r->x = HIBYTE(loword)
				% (MAP_WIDTH - pstorm_r->width);
			pstorm_r->y = LOBYTE(loword)
				% (MAP_HEIGHT - pstorm_r->height);

			pstorm_r->x = pstorm_r->x * width / MAP_WIDTH;
			pstorm_r->width = pstorm_r->width * width / MAP_WIDTH;
			pstorm_r->y = pstorm_r->y * height / MAP_HEIGHT;
			pstorm_r->height = pstorm_r->height * height / MAP_HEIGHT;

			for (j = i + 1; j < storm_count; ++j)
			{
				short x, y;
				short w, h;

				x = storm_r[j].x - pstorm_r->x;
				y = storm_r[j].y - pstorm_r->y;
				w = x + storm_r[j].width + 4;
				h = y + storm_r[j].height + 4;
				intersect = (bool)(w > 0 && h > 0
					&& x < pstorm_r->width + 4
					&& y < pstorm_r->height + 4);
				if (intersect)
					break;
			}

		} while (intersect);

		this->makeCrater(pstorm_r, depthArray, 6, 6, false, width);
		++pstorm_r->x;
		++pstorm_r->y;
		pstorm_r->width -= 2;
		pstorm_r->height -= 2;

		band_delta = HIBYTE(loword) & ((3 << RANGE_SHIFT) + 20);

		this->makeCrater(pstorm_r, depthArray,
			band_delta, band_delta, true, width);
		++pstorm_r->x;
		++pstorm_r->y;
		pstorm_r->width -= 2;
		pstorm_r->height -= 2;

		band_delta += 2;
		if (pstorm_r->width > 2 && pstorm_r->height > 2)
		{
			this->makeCrater(pstorm_r, depthArray,
				band_delta, band_delta, true, width);
			++pstorm_r->x;
			++pstorm_r->y;
			pstorm_r->width -= 2;
			pstorm_r->height -= 2;
		}

		band_delta += 2;
		if (pstorm_r->width > 2 && pstorm_r->height > 2)
		{
			this->makeCrater(pstorm_r, depthArray,
				band_delta, band_delta, true, width);
			++pstorm_r->x;
			++pstorm_r->y;
			pstorm_r->width -= 2;
			pstorm_r->height -= 2;
		}

		band_delta += 4;
		this->makeCrater(pstorm_r, depthArray,
			band_delta, band_delta, true, width);
	}
}

void GenPlanet::makeGasGiant(short num_bands, char* depthArray, RECT_UQM* pRect, short depth_delta)
{// based of UQM source code
	short last_y, next_y;
	short band_error, band_bump, band_delta;
	short i, j, band_height;
	char* lpDst;
	unsigned int loword, hiword;
	int rand_val;

	band_height = MAP_HEIGHT / num_bands;
	band_bump = MAP_HEIGHT % num_bands;
	band_error = num_bands >> 1;
	lpDst = depthArray;

	band_delta = ((LOWORD(r->getUQMRandomValue())
		& (NUM_BAND_COLORS - 1)) << RANGE_SHIFT)
		+ (1 << (RANGE_SHIFT - 1));
	last_y = next_y = 0;
	for (i = num_bands; i > 0; --i)
	{
		short cur_y;

		rand_val = r->getUQMRandomValue();
		loword = LOWORD(rand_val);
		hiword = HIWORD(rand_val);

		next_y += band_height;
		if ((band_error -= band_bump) < 0)
		{
			++next_y;
			band_error += num_bands;
		}
		if (i == 1)
			cur_y = pRect->height;
		else
		{
			RECT_UQM r;

			cur_y = next_y
				+ ((band_height - 2) >> 1)
				- ((LOBYTE(hiword) % (band_height - 2)) + 1);
			cur_y = cur_y * pRect->height / MAP_HEIGHT;
			r.x = r.y = 0;
			r.width = pRect->width;
			r.height = 5 * pRect->height / MAP_HEIGHT;
			this->deltaTopography(50,
				&depthArray[(cur_y - (r.height >> 1)) * r.width],
				&r, depth_delta);
		}

		for (j = cur_y - last_y; j > 0; --j)
		{
			short k;

			for (k = pRect->width; k > 0; --k)
				*lpDst++ += band_delta;
		}

		last_y = cur_y;
		band_delta = (band_delta
			+ ((((LOBYTE(loword) & 1) << 1) - 1) << RANGE_SHIFT))
			& (((1 << RANGE_SHIFT) * NUM_BAND_COLORS) - 1);
	}

	this->makeStorms(4 + (r->getUQMRandomValue() & 3) + 1,
		depthArray, pRect->width, pRect->height);

	this->ditherMap(depthArray, pRect->width, pRect->height);
}

GenPlanet::GenPlanet(void)
{
	r = new RandomUQM();
}

GenPlanet::GenPlanet(int r)
{
	this->r = new RandomUQM(r);
}

GenPlanet::~GenPlanet(void)
{
	delete r;
}

void GenPlanet::generatePlanetSurface(char* depthArray, TopoFrame* desc)
{// based of UQM source code
	RECT_UQM rect;
	int i, y;
	int width = 840;
	int height = 268;

	rect.x = rect.y = 0;
	rect.width = width;
	rect.height = height;
	{
		//std::memset(depthArray, 0, width * height);
		switch (desc->algo)
		{
		case GAS_GIANT_ALGO:
			this->makeGasGiant(desc->num_faults,
				depthArray, &rect, desc->fault_depth);
			break;
		case TOPO_ALGO:
		case CRATERED_ALGO:
			if (desc->num_faults)
				this->deltaTopography(desc->num_faults,
					depthArray, &rect,
					desc->fault_depth);

			for (i = 0; i < desc->num_blemishes; ++i)
			{
				RECT_UQM crater_r;
				unsigned int loword;

				loword = LOWORD(r->getUQMRandomValue());
				switch (HIBYTE(loword) & 31)
				{
				case 0:
					crater_r.width =
						(LOBYTE(loword)
							% (MAP_HEIGHT >> 2))
						+ (MAP_HEIGHT >> 2);
					break;
				case 1:
				case 2:
				case 3:
				case 4:
					crater_r.width =
						(LOBYTE(loword)
							% (MAP_HEIGHT >> 3))
						+ (MAP_HEIGHT >> 3);
					break;
				default:
					crater_r.width =
						(LOBYTE(loword)
							% (MAP_HEIGHT >> 4))
						+ 4;
					break;
				}

				loword = LOWORD(r->getUQMRandomValue());
				crater_r.height = crater_r.width;
				crater_r.x = HIBYTE(loword)
					% (MAP_WIDTH
						- crater_r.width);
				crater_r.y = LOBYTE(loword)
					% (MAP_HEIGHT
						- crater_r.height);

				crater_r.width = crater_r.width
					* (height / MAP_HEIGHT);
				crater_r.height = crater_r.width;
				crater_r.x = crater_r.x
					* (width / MAP_WIDTH);
				crater_r.y = crater_r.y
					* (height / MAP_HEIGHT);

				this->makeCrater(&crater_r, depthArray,
					desc->fault_depth << 2,
					-(desc->fault_depth << 2),
					false, width);
			}
			if (desc->algo == CRATERED_ALGO)
				this->ditherMap(depthArray, width, height);
			this->validateMap(depthArray, width, height);
			break;
		}
	}
}
