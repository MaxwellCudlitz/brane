//
// Created by max on 3/27/18.
//

#pragma once

namespace algs
{
namespace activation
{

class square
{
public:

	float operator()(float f)
	{
		if (f > 0.5f)
			return 1;
		return 0;
	}
};

}
}