#include "all_nodes.h"
#include "../surface_provider.h"

std::vector<std::string> get_all_idnames()
{
	std::vector<std::string> out;

	// output_spn.h (Disabled, it's default node)
	// out.push_back("Output");

	// input_spn.h (Disabled, it's a default node)
	// out.push_back("Input");

	// constant_spn.h
	out.push_back("Constant");

	// math_spn.h
	out.push_back("Math");

	// noise_spn.h
	out.push_back("Noise");

	// pack_spn.h
	out.push_back("Pack");

	// unpack_spn.h
	out.push_back("Unpack");

	// preview_spn.h
	out.push_back("Preview");

	return out;
}

SurfaceProviderNode* create_new_node(const std::string& idname, SurfaceProvider* provider, int index_override)
{
	SurfaceProviderNode* out;

	if (idname == "Output")
	{
		out = new OutputSPN();
	}
	else if (idname == "Input")
	{
		out = new InputSPN();
	}
	else if (idname == "Constant")
	{
		out = new ConstantSPN();
	}
	else if (idname == "Math")
	{
		out = new MathSPN();
	}
	else if (idname == "Noise")
	{
		out = new NoiseSPN();
	}
	else if(idname == "Pack")
	{
		out = new PackSPN();
	}
	else if (idname == "Unpack")
	{
		out = new UnpackSPN();
	}
	else if (idname == "Preview")
	{
		out = new PreviewSPN();
	}
	else
	{
		out = NULL;
	}

	if (out != NULL)
	{
		if (index_override >= 0)
		{
			out->id = index_override;
			// Don't create
		}
		else
		{
			out->id = provider->get_id();
			out->create(provider);
		}
		
	}

	return out;
}