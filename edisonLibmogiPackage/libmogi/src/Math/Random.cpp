/******************************************************************************
 *                                                                            *
 *             Copyright (C) 2016 Mogi, LLC - All Rights Reserved             *
 *                            Author: Matt Bunting                            *
 *                                                                            *
 *            This program is distributed under the LGPL, version 2           *
 *                                                                            *
 *   This program is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU Lesser General Public License              *
 *   version 2.1 as published by the Free Software Foundation;                *
 *                                                                            *
 *   See license in root directory for terms.                                 *
 *   https://github.com/mogillc/nico/tree/master/edisonLibmogiPackage/libmogi *
 *                                                                            *
 *****************************************************************************/

#include "systems.h"

#include <math.h>

#ifdef UNIX
#include <iostream>
#endif

#include <stdlib.h>

namespace Mogi {
namespace Math {

Random::Random() {
	srand(time(NULL));
}

double Random::uniform(double min, double max) {
	return (max - min) * ((double) rand() / (double) RAND_MAX) + min;
}

double Random::normal(double mean, double variance) {
	// from http://en.wikipedia.org/wiki/Box–Muller_transform
	static bool haveSpare = false;
	static double rand1, rand2;

	if (haveSpare) {
		haveSpare = false;
		return sqrt(variance * rand1) * sin(rand2) + mean;
	}

	haveSpare = true;

	rand1 = rand() / ((double) RAND_MAX);
	if (rand1 < 1e-100)
		rand1 = 1e-100;
	rand1 = -2 * log(rand1);
	rand2 = (rand() / ((double) RAND_MAX)) * 2 * MOGI_PI;

	return sqrt(variance * rand1) * cos(rand2) + mean;
}
}
}
