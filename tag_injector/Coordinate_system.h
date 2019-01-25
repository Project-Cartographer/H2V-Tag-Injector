#include "stdafx.h"
#pragma once

struct cartessian_co_ord
{
	//absolute
	float cam_x, cam_y, cam_z;//camera coords
	float alpha, beta, gamma;//camera rotations

	
	float obj_x, obj_y, obj_z;//object coords

	float i_obj_X, i_obj_Y, i_obj_Z;	
};